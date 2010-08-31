#include "OUAN_Precompiled.h"

#include "CutsceneState.h"
#include "GameStateManager.h"
#include "../Application.h"
#include "../Audio/AudioSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Logic/LogicSubsystem.h"
#include "../Physics/PhysicsSubsystem.h"
using namespace OUAN;

CutsceneState* CutsceneState::mInst=NULL;

/// Default constructor
CutsceneState::CutsceneState()
:mCutsceneFile("")
,mCutsceneFunction("")
,mCutsceneLaunched(false)
,mChangeWorldElapsedTime(0)
,mSkippingCutscene(false)
,mIsChangingWorld(false)
{
	mInst=this;
}
/// Destructor
CutsceneState::~CutsceneState()
{

}

void CutsceneState::init(ApplicationPtr app)
{
	GameState::init(app);

	mApp->setPlayingCutscene(true);
	mApp->mAudioFrameCnt=0;
	mApp->getRenderSubsystem()->resumeRendering();
	//mApp->getAudioSubsystem()->stopAllSounds();
}

/// Clean up extras screen's resources
void CutsceneState::cleanUp()
{
	GameState::cleanUp();

	mApp->getLogicSubsystem()->resetCutsceneFinished();
	mApp->setPlayingCutscene(false);
}

/// pause state
void CutsceneState::pause()
{

}
/// resume state
void CutsceneState::resume()
{

}

/// process input events
/// @param app	the parent application
void CutsceneState::handleEvents()
{
	int pad1,pad2;
	int key1,key2;

	if (mApp->isPressedMenu(&pad1,&key1) || mApp->isPressedJump(&pad2,&key2))
	{
		mSkippingCutscene=true;
	}
}
/// Update game according to the current state
/// @param app	the parent app
void CutsceneState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
	LogicSubsystemPtr logicSS = mApp->getLogicSubsystem();

	double elapsedSeconds=(double)elapsedTime * 0.000001f;
	//BREAKPOINT HIT CHECK
	if (elapsedSeconds>1)
		elapsedSeconds=1/30.0f;
	if (!mCutsceneFile.empty() && !mCutsceneFunction.empty())
	{
		//Check if cutscene launched. If not, do it. Otherwise, 
		//call the update method to resume the cutscene.
		if (!mCutsceneLaunched)
		{
			logicSS->initCutsceneScript(mCutsceneFile);
			logicSS->invokeCutsceneFunction(mCutsceneFunction);
			mCutsceneLaunched=true;
		}
		else logicSS->updateCutsceneFunction(mCutsceneFunction,elapsedSeconds);
		do 
		{

			if(mIsChangingWorld)
			{
				mChangeWorldElapsedTime+=elapsedSeconds;
				if(mChangeWorldElapsedTime>=mChangeWorldTotalTime)
				{
					changeToWorld(mApp->getWorld(),1);
					changeWorldFinished(mApp->getWorld());
					mIsChangingWorld=false;
				}
				else
				{
					changeToWorld(mApp->getWorld(),mChangeWorldElapsedTime/mChangeWorldTotalTime);
				}
			}

			//Game update
			mApp->getCameraManager()->update(elapsedSeconds);

			mApp->getGameWorldManager()->update(elapsedSeconds);	

			mApp->getPhysicsSubsystem()->update(elapsedSeconds);

			//mApp->getLogicSubsystem()->update(elapsedSeconds);

			mApp->getTrajectoryManager()->updateDebugNodes();

			mApp->getGameWorldManager()->postUpdate();

			Ogre::Camera* activeCam = mApp->getCameraManager()->getCamera();
			if (activeCam)
			{
				mApp->getAudioSubsystem()->set3DAttributes(activeCam->getPosition(),Ogre::Vector3::ZERO,
					activeCam->getOrientation()*Ogre::Vector3::UNIT_Z,Ogre::Vector3::UNIT_Y);
			}

			if (mApp->mAudioFrameSkip==0 || mApp->mAudioFrameCnt==0)
			{
				mApp->getAudioSubsystem()->update(elapsedSeconds);
			}
			if ((mApp->mAudioFrameCnt++)>mApp->mAudioFrameSkip)
				mApp->mAudioFrameCnt=0;
			
			if (mSkippingCutscene)
				logicSS->updateCutsceneFunction(mCutsceneFunction,elapsedSeconds);

		} while (!logicSS->isCutsceneFinished(mCutsceneFunction) && mSkippingCutscene);
		
		if (logicSS->isCutsceneFinished(mCutsceneFunction))
		{
			mApp->getCameraManager()->setDefaultThirdPersonCamera(false);
			mApp->getGameStateManager()->popState();
		}
	}
}
void CutsceneState::changeWorld(int world)
{
	mInst->doChangeWorld(world);
}
void CutsceneState::doChangeWorld(int world)
{
	Configuration config;
	std::string value;
	if (config.loadFromFile(GAMEWORLDMANAGER_CFG))
	{
		mChangeWorldTotalTime = config.parseFloat("CHANGE_WORLD_TIME");
		mRandomChangeWorld= config.parseBool("CHANGE_WORLD_TREES_RANDOM");
		CHANGE_WORLD_RADIUM= config.parseFloat("CHANGE_WORLD_RADIUM");
	}
	mApp->setWorld(world);
	activateChangeWorld();
}
void CutsceneState::activateChangeWorld()
{
	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime=mChangeWorldTotalTime-mChangeWorldElapsedTime;
	}
	else
	{
		mChangeWorldElapsedTime=0;
		mIsChangingWorld=true;
		changeWorldStarted(mApp->getWorld());
	}
}
void CutsceneState::changeWorldStarted(int newWorld)
{
	mApp->getGameWorldManager()->setChangeWorldRender();

	switch(newWorld)
	{
	case DREAMS:
		mApp->setOldWorld(NIGHTMARES);
		mApp->getGameWorldManager()->setChangeWorldFactor(1);
		break;
	case NIGHTMARES:
		mApp->setOldWorld(DREAMS);
		mApp->getGameWorldManager()->setChangeWorldFactor(0);
		break;
	default:
		break;
	}

	mCurrentChangeWorldFrame=0;
}
bool CutsceneState::isWorldChangeFinished() const
{
	return mIsChangingWorld;
}
bool CutsceneState::hasFinishedChangingWorld()
{
	return mInst->mIsChangingWorld;
}
void CutsceneState::changeToWorld(int newWorld, double percent)
{
	switch(newWorld)
	{
	case DREAMS:
		mApp->getGameWorldManager()->setChangeWorldFactor(1-percent);
		break;
	case NIGHTMARES:
		mApp->getGameWorldManager()->setChangeWorldFactor(percent);
		break;
	default:
		break;
	}
}
void CutsceneState::changeWorldFinished(int newWorld)
{

	mApp->setWorld(newWorld);

	switch(newWorld)
	{
	case DREAMS:
		mApp->setOldWorld(NIGHTMARES);
		mApp->getGameWorldManager()->setChangeWorldFactor(1);
		break;
	case NIGHTMARES:
		mApp->setOldWorld(DREAMS);
		mApp->getGameWorldManager()->setChangeWorldFactor(0);
		break;
	default:
		break;
	}
	int world=mApp->getWorld();
	switch(world)
	{
	case DREAMS:
		mApp->getGameWorldManager()->setDreamsRender();
		break;
	case NIGHTMARES:
		mApp->getGameWorldManager()->setNightmaresRender();
		break;
	default:
		break;
	}
	mIsChangingWorld=false;
	mApp->getGameWorldManager()->setWorld(world);
}

bool CutsceneState::render()
{
	if (!mSkippingCutscene)
	{
		GameState::render();
	}
	return true;
}

void CutsceneState::setCutsceneFile(const std::string& file)
{
	mCutsceneFile=file;
}
void CutsceneState::setCutsceneFunction (const std::string& function)
{
	mCutsceneFunction=function;
}

bool CutsceneState::isSkippingCutscene()
{
	return mInst->mSkippingCutscene;
}