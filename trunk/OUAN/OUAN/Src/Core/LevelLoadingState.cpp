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

using namespace OUAN;

TLoadingStage gStages[]=
{
	//{&LevelLoadingState::unloadAll, "UNLOAD_EVERYTHING", 0.01},
	{&LevelLoadingState::initPhysics, "INIT_PHYSICS",0.015},
	{&LevelLoadingState::resetTrajectories, "RESET_TRAJECTORIES",0.0025},
	{&LevelLoadingState::initParser, "INIT_PARSER",0.05},
	{&LevelLoadingState::processGameObjects, "PROCESS_GAME_OBJECTS",0.8},
	{&LevelLoadingState::processGameObject, "PROCESS_GAME_OBJECT",-1.0},
	{&LevelLoadingState::processFractalClouds, "PROCESS_FRACTAL_CLOUDS",0.02},
	{&LevelLoadingState::processBillboardClouds, "PROCESS_BILLBOARD_CLOUDS",0.02},
	{&LevelLoadingState::processTrajectories, "PROCESS_TRAJECTORIES",0.04},
	{&LevelLoadingState::processWalkabilityMap, "PROCESS_WALKABILITY_MAP",0.04},
	{&LevelLoadingState::initMaterials, "INIT_MATERIALS",0.005},
	{&LevelLoadingState::initMusic, "INIT_MUSIC",0.0025},
	{&LevelLoadingState::initScripts, "INIT_SCRIPTS",0.0025},
	{&LevelLoadingState::clearParser, "CLEAR_PARSER",0.0025}
};
int gNumStages=13;

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
	mApp=app;
	mApp->getGameWorldManager()->unloadLevel();
	mApp->getGameWorldManager()->setWorld(DREAMS);

	mTimeToGo=5;
	mScreen= new Ogre::Rectangle2D(true);
	mScreen->setCorners(-1.0, 1.0, 1.0, -1.0);	//Full screen
	mScreen->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
	mScreen->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(LEVELLOAD_MATERIAL_NAME,
		LEVELLOAD_GROUP);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(LEVELLOAD_IMG);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mScreen->setMaterial(LEVELLOAD_MATERIAL_NAME);

	RenderSubsystemPtr renderSS =mApp->getRenderSubsystem(); 
	Ogre::SceneNode* screenNode;
	if (!renderSS->getSceneManager()->hasSceneNode(LEVELLOAD_SCREENNODE))
	{
		screenNode= renderSS->getSceneManager()->getRootSceneNode()->createChildSceneNode(LEVELLOAD_SCREENNODE);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(LEVELLOAD_SCREENNODE);
	}
	screenNode ->attachObject(mScreen);

	leftCorner=-0.8;
	topCorner=-0.4;
	rightCorner=0.8;
	bottomCorner=-0.6;
	currentRightCorner=-0.8;

	currentStage=0;

	mTotalWidth=rightCorner-leftCorner;
	mBar= new Ogre::Rectangle2D(true);
	mBar->setCorners(leftCorner,topCorner,currentRightCorner,bottomCorner);
	mBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
	mBar->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
	// Create background material
	material = Ogre::MaterialManager::getSingleton().create(LEVELLOAD_BAR_MATERIAL_NAME,
		LEVELLOAD_GROUP);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(LEVELLOAD_BAR_IMG);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mBar->setMaterial(LEVELLOAD_BAR_MATERIAL_NAME);

	if (!renderSS->getSceneManager()->hasSceneNode(LEVELLOAD_BAR_NODE))
	{
		screenNode= renderSS->getSceneManager()->getRootSceneNode()->createChildSceneNode(LEVELLOAD_BAR_NODE);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(LEVELLOAD_BAR_NODE);
	}	
	screenNode->attachObject(mBar);

	mIteratorInUse=false;
	mProcessingGameObjects=false;
}

/// Clean up main menu's resources
void LevelLoadingState::cleanUp()
{	
	if (Ogre::MaterialManager::getSingleton().resourceExists(LEVELLOAD_MATERIAL_NAME))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(LEVELLOAD_MATERIAL_NAME);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(Ogre::String(""));
		if (mScreen)
		{
			std::string sceneNodeName=mScreen->getParentSceneNode()->getName();
			mScreen->detatchFromParent();
			mApp->getRenderSubsystem()->getSceneManager()->destroySceneNode(sceneNodeName);
			delete mScreen;
			mScreen=NULL;
			Ogre::MaterialManager::getSingleton().remove(LEVELLOAD_MATERIAL_NAME);
		}
	}


	if (Ogre::MaterialManager::getSingleton().resourceExists(LEVELLOAD_BAR_MATERIAL_NAME))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(LEVELLOAD_BAR_MATERIAL_NAME);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(Ogre::String(""));
		if (mBar)
		{
			std::string sceneNodeName=mBar->getParentSceneNode()->getName();
			mBar->detatchFromParent();
			mApp->getRenderSubsystem()->getSceneManager()->destroySceneNode(sceneNodeName);
			delete mBar;
			mBar=NULL;
			Ogre::MaterialManager::getSingleton().remove(LEVELLOAD_BAR_MATERIAL_NAME);	
		}
	}

}

/// pause state
void LevelLoadingState::pause()
{


}
/// resume state
void LevelLoadingState::resume()
{
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
	mBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
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
		mApp->getPhysicsSubsystem()->initLevel(mLevelFilename);
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
	}
	else 
	{
		mProcessingGameObjects=false;
		if (mIteratorInUse) mIteratorInUse=false;
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
void LevelLoadingState::processWalkabilityMap()
{
	//Process Level's Walkability Maps
	mApp->getLevelLoader()->processWalkabilityMaps();//clear information, as we do not need it anymore
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