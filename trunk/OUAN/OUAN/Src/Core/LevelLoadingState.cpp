#include "OUAN_Precompiled.h"

#include "LevelLoadingState.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"

#include "../Logic/LogicSubsystem.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"

#include "../Loader/XMLGameObject.h"

#include "GameStateManager.h"
#include "GameRunningState.h"

#include "../Audio/AudioDefs.h"
#include "../Audio/AudioSubsystem.h"

#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"

#include "../Utils/Utils.h"

using namespace OUAN;

TLoadingStage gStages[]=
{
	//{&LevelLoadingState::unloadAll, "UNLOAD_EVERYTHING", 0.01},
	{&LevelLoadingState::initPhysics, "INIT_PHYSICS",0.015},
	{&LevelLoadingState::resetTrajectories, "RESET_TRAJECTORIES",0.0025},
	{&LevelLoadingState::initParser, "INIT_PARSER",0.04},
	{&LevelLoadingState::processSceneNodes, "PROCESS_SCENE_NODES",0.01},
	{&LevelLoadingState::processGameObjects, "PROCESS_GAME_OBJECTS",0.8},
	{&LevelLoadingState::processGameObject, "PROCESS_GAME_OBJECT",-1.0},
	{&LevelLoadingState::processFractalClouds, "PROCESS_FRACTAL_CLOUDS",0.02},
	{&LevelLoadingState::processBillboardClouds, "PROCESS_BILLBOARD_CLOUDS",0.02},
	{&LevelLoadingState::processTrajectories, "PROCESS_TRAJECTORIES",0.04},
	{&LevelLoadingState::processWalkabilityMap, "PROCESS_WALKABILITY_MAP",0.035},
	{&LevelLoadingState::resolveLinks, "RESOLVE_LINKS",0.005},
	{&LevelLoadingState::initMaterials, "INIT_MATERIALS",0.0010},
	{&LevelLoadingState::loadFlashlightDecalMaterials, "LOAD_MATERIALS",0.0015},
	{&LevelLoadingState::initMusic, "INIT_MUSIC",0.0025},
	{&LevelLoadingState::initScripts, "INIT_SCRIPTS",0.0025},
	{&LevelLoadingState::setCameraTarget, "SET_CAMERA_TARGET",0.0010},
	{&LevelLoadingState::clearParser, "CLEAR_PARSER",0.0015},
};
const int gNumStages=17;

/// Default constructor
LevelLoadingState::LevelLoadingState()
:GameState()
{
	mMusicChannel=-1;
}
/// Destructor
LevelLoadingState::~LevelLoadingState()
{

}


/// init main menu's resources
void LevelLoadingState::init(ApplicationPtr app)
{
	GameState::init(app);

	mApp->getGameWorldManager()->unloadLevel();
	//mApp->getGameWorldManager()->setWorld(DREAMS);
	Utils::TTexturedRectangleDesc desc;

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_BACKGROUND;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=LEVELLOAD_BG_MATERIAL_NAME;
	desc.materialGroup=LEVELLOAD_GROUP;
	desc.textureName=LEVELLOAD_BG_IMG;
	desc.sceneNodeName=LEVELLOAD_BG_NODE;

	Utils::createTexturedRectangle(desc,mBg,mApp->getRenderSubsystem());

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_OVERLAY;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=LEVELLOAD_MATERIAL_NAME;
	desc.materialGroup=LEVELLOAD_GROUP;
	desc.textureName=LEVELLOAD_IMG;
	desc.sceneNodeName=LEVELLOAD_SCREENNODE;
	desc.textureAnimation=true;
	desc.texAnimNumFrames=39;
	desc.texAnimDuration=1;

	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());

	desc.textureAnimation=false;
	desc.leftCorner=-0.88;
	desc.rightCorner=0.88;
	desc.topCorner=-0.31;
	desc.bottomCorner=-0.7;
	desc.renderQueue=Ogre::RENDER_QUEUE_OVERLAY;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=LEVELLOAD_BARBG_MATERIAL_NAME;
	desc.materialGroup=LEVELLOAD_GROUP;
	desc.textureName=LEVELLOAD_BARBG_IMG;
	desc.sceneNodeName=LEVELLOAD_BARBG_NODE;
	desc.alphaBlending=true;
	Utils::createTexturedRectangle(desc,mBarBg,mApp->getRenderSubsystem());

	leftCorner=-0.80;
	topCorner=-0.43;
	rightCorner=0.80;
	bottomCorner=-0.57;
	currentRightCorner=-0.79;

	currentStage=0;

	mTotalWidth=rightCorner-leftCorner;

	memset(&desc,0,sizeof(desc));
	desc.bottomCorner=bottomCorner;
	desc.leftCorner=leftCorner;
	desc.topCorner=topCorner;
	desc.rightCorner=currentRightCorner;
	desc.renderQueue=Ogre::RENDER_QUEUE_MAX;
	desc.axisAlignedBox=Ogre::AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE);
	desc.materialGroup=LEVELLOAD_GROUP;
	desc.materialName=LEVELLOAD_BAR_MATERIAL_NAME;
	desc.textureName = LEVELLOAD_BAR_IMG;
	desc.sceneNodeName=LEVELLOAD_BAR_NODE;
	
	Utils::createTexturedRectangle(desc,mBar,mApp->getRenderSubsystem());

	mIteratorInUse=false;
	mProcessingGameObjects=false;
}

/// Clean up main menu's resources
void LevelLoadingState::cleanUp()
{		
	GameState::cleanUp();

	Utils::destroyTexturedRectangle(mScreen,LEVELLOAD_MATERIAL_NAME,mApp->getRenderSubsystem());
	Utils::destroyTexturedRectangle(mBar,LEVELLOAD_BAR_MATERIAL_NAME,mApp->getRenderSubsystem());
	Utils::destroyTexturedRectangle(mBarBg,LEVELLOAD_BARBG_MATERIAL_NAME,mApp->getRenderSubsystem());
	Utils::destroyTexturedRectangle(mBg,LEVELLOAD_BG_MATERIAL_NAME,mApp->getRenderSubsystem());
}

/// pause state
void LevelLoadingState::pause()
{


}
/// resume state
void LevelLoadingState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void LevelLoadingState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void LevelLoadingState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
	/*double secs=elapsedTime*0.000001;
	mApp->getAudioSubsystem()->update(secs);
	mTimeToGo-=secs;*/

	double currentWidth = currentRightCorner-leftCorner;

	if (currentStage==gNumStages)
	{
		Logger::getInstance()->log("FINISHED LOADING!!");
		mApp->getGameWorldManager()->setLevelname(mLevelFilename);
		GameStatePtr nextState(new GameRunningState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}
	else
	{

		processStage(gStages[currentStage]);
		if (!mProcessingGameObjects)
			currentStage++;
	}
	//if (mTimeToGo<=0)
	//{
	//	GameStatePtr nextState(new GameRunningState());
	//	mApp->getGameStateManager()->changeState(nextState,mApp);
	//}
}
void LevelLoadingState::processStage(const TLoadingStage& stage)
{
	(this->*(stage.stageFunction))();
	
	std::stringstream msg("");
	msg<<"LOADING STAGE: "<<gStages[currentStage].stageName;
	Logger::getInstance()->log(msg.str());

	if (stage.stageName.compare("PROCESS_GAME_OBJECTS")==0)
	{
		int numGameObjects=mApp->getLevelLoader()->getGameObjectsNumber();
		mGameObjectWidth= mTotalWidth*stage.stagePercent/(double)numGameObjects;		
	}
	else if (stage.stagePercent<0)
	{
		currentRightCorner+=mGameObjectWidth;
	}
	else
	{
		currentRightCorner+=stage.stagePercent*mTotalWidth;
	}

	mBar->detatchFromParent();
	delete mBar;
	mBar= new Ogre::Rectangle2D(true);
	mBar->setCorners(leftCorner,topCorner,currentRightCorner,bottomCorner);	
	mBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_MAX);
	mBar->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
	mApp->getRenderSubsystem()->getSceneManager()->getSceneNode(LEVELLOAD_BAR_NODE)->attachObject(mBar);
	mBar->setMaterial(LEVELLOAD_BAR_MATERIAL_NAME);
}

void LevelLoadingState::unloadAll()
{
	mApp->getGameWorldManager()->unloadLevel();
}

void LevelLoadingState::initPhysics()
{
	if (!mLevelFilename.empty())
	{
		mApp->getPhysicsSubsystem()->initLevel(mLevelFilename);
	}
}

void LevelLoadingState::resetTrajectories()
{
	mApp->getTrajectoryManager()->clear();
}

void LevelLoadingState::initParser()
{
	mApp->getLevelLoader()->initializeParser(mLevelFilename);
}

void LevelLoadingState::processGameObjects()
{	
	mGameObjectIterator = mApp->getLevelLoader()->getGameObjectIterator();
	mIteratorInUse=true;
}

void LevelLoadingState::processGameObject()
{	
	if (mIteratorInUse && mGameObjectIterator!=mApp->getLevelLoader()->getGameObjectIteratorEnd())
	{
		if (!mProcessingGameObjects) mProcessingGameObjects=true;
		mApp->getLevelLoader()->processGameObject(&mGameObjectIterator->second);
		++mGameObjectIterator;
		if (mGameObjectIterator==mApp->getLevelLoader()->getGameObjectIteratorEnd())
		{
			mProcessingGameObjects=false;
			mIteratorInUse=false;
		}
	}
}

void LevelLoadingState::processFractalClouds()
{
	//Process Level's GameObjectClouds
	if (Ogre::StringUtil::match(mLevelFilename, "Level2"))
	{
		mApp->getLevelLoader()->processGameObjectFractalClouds();
	}
	
}

void LevelLoadingState::processBillboardClouds()
{
	//Process Level's GameObjectClouds
	if (Ogre::StringUtil::match(mLevelFilename, "Level2"))
	{
		mApp->getLevelLoader()->processGameObjectBillboardClouds();
	}
}

void LevelLoadingState::processTrajectories()
{
	//Process Level's Trajectories
	mApp->getLevelLoader()->processTrajectories();
}

void LevelLoadingState::processSceneNodes()
{
	//Process Level's Trajectories
	mApp->getLevelLoader()->processSceneNodes();
}

void LevelLoadingState::processWalkabilityMap()
{
	//Process Level's Walkability Maps
	mApp->getLevelLoader()->processWalkabilityMaps();//clear information, as we do not need it anymore
}

void LevelLoadingState::resolveLinks()
{
	mApp->getGameWorldManager()->resolveNestLinks();
}
void LevelLoadingState::initMaterials()
{
	/// Set ambient specular and diffuse material components off;
	mApp->getRenderSubsystem()->initMaterials();
}
	
void LevelLoadingState::initMusic()
{
	//TODO!
}
void LevelLoadingState::initScripts()
{
	mApp->getLogicSubsystem()->loadScripts();
}

void LevelLoadingState::setLevelFileName(const std::string& levelFilename)
{
	mLevelFilename=levelFilename;
}
void LevelLoadingState::clearParser()
{
	mApp->getLevelLoader()->clearXMLParser();
}

void LevelLoadingState::setCameraTarget()
{
	Application::getInstance()->getCameraManager()->setDefaultThirdPersonCamera(false);
	Application::getInstance()->getCameraManager()->centerToTargetBack(false);
}

void LevelLoadingState::loadFlashlightDecalMaterials()
{
	GameWorldManagerPtr mgr=mApp->getGameWorldManager();
	mgr->loadFlashlightDecalMaterials();
}