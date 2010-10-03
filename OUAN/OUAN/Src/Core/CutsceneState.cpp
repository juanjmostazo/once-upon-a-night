#include "OUAN_Precompiled.h"

#include "CutsceneState.h"
#include "GameStateManager.h"
#include "../Application.h"
#include "../Audio/AudioSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectOny.h"
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
	mApp->rescaleViewport(0,0.15,1,0.7);

	//Register events
	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		EventHandlerPtr eh;
		boost::shared_ptr<CutsceneState> this_ = shared_from_this();
		eh = EventHandlerPtr(new EventHandler<CutsceneState,ChangeWorldEvent>(this_,&CutsceneState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->registerHandler(eh,EVENT_TYPE_CHANGEWORLD);
	}

	mWorldAfterCutscene=mApp->getGameWorldManager()->getWorld();
	mReturningToGameTransition=false;
	mFinishedChangeWorld=true;
}

/// Clean up extras screen's resources
void CutsceneState::cleanUp()
{
	GameState::cleanUp();

	mApp->getLogicSubsystem()->resetCutsceneFinished();
	mApp->setPlayingCutscene(false);
	mCutsceneLaunched=false;
	mApp->rescaleViewport(0,0,1,1);

	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		EventHandlerPtr eh;
		boost::shared_ptr<CutsceneState> this_ = shared_from_this();
		eh = EventHandlerPtr(new EventHandler<CutsceneState,ChangeWorldEvent>(this_,&CutsceneState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->unregisterHandler(eh,EVENT_TYPE_CHANGEWORLD);
	}
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
	int pad1,pad2,pad3;
	int key1,key2,key3;

	if (mApp->isPressedMenu(&pad1,&key1) || mApp->isPressedJump(&pad2,&key2) || mApp->isPressedToggleCutScenesDebug(&pad3,&key3))
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
			logicSS->loadScript(SCRIPTS_PATH+"/"+SCRIPT_COMMON_FUNCTIONS);
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
			GameObjectOnyPtr ony = mApp->getGameWorldManager()->getGameObjectOny();
			if (ony.get())
			{
				ony->hideMessage();
			}
	
			mApp->getGameWorldManager()->setWorld(mWorldAfterCutscene);
			mApp->getGameWorldManager()->dispatchEvents();
			mIsChangingWorld=false;

			if(!mApp->getGameWorldManager()->hasExecutedLevelEvent(CUTSCENE_9_FINAL_BOSS_START)
				|| mApp->getGameWorldManager()->hasExecutedLevelEvent(CUTSCENE_10_3_FINAL_BOSS_HIT_3)
				)
			{
				mApp->getCameraManager()->setDefaultThirdPersonCamera(mReturningToGameTransition);
			}
			mApp->getGameStateManager()->popState();
			logicSS->terminateCutsceneFunction(mCutsceneFunction);
		}
	}
}

void CutsceneState::setMyReturningToGameTransitionLUA(bool transition)
{
	mInst->setMyReturningToGameTransition(transition);
}

void CutsceneState::setMyReturningToGameTransition(bool transition)
{
	mReturningToGameTransition=transition;
}


void CutsceneState::changeWorld(int world)
{
	mInst->doChangeWorld(world);
}
void CutsceneState::doChangeWorld(int world)
{
	mApp->getGameWorldManager()->changeWorld();
	mApp->getGameWorldManager()->dispatchEvents();
	mWorldAfterCutscene=world;
	mFinishedChangeWorld=false;
}

void CutsceneState::processChangeWorld(ChangeWorldEventPtr evt)
{
	mApp->setWorld(evt->getNewWorld());
	mChangeWorldTotalTime=evt->time;
	if (evt->fast)
	{
		activateChangeWorldFast();
	}
	else
	{
		activateChangeWorld();
	}
}

void CutsceneState::activateChangeWorldFast()
{
	mIsChangingWorld=false;
	changeWorldFinished(mApp->getGameWorldManager()->getWorld());
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

bool CutsceneState::isWorldChangeFinished() const
{
	return mFinishedChangeWorld;
}

bool CutsceneState::hasFinishedChangingWorld()
{
	return mInst->mFinishedChangeWorld;
}

void CutsceneState::changeWorldFinished(int newWorld)
{
	//endMusicFading(newWorld);

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

	mFinishedChangeWorld=true;
}

void CutsceneState::changeWorldStarted(int newWorld)
{
	//initMusicFading(newWorld);

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

	//currentChangeWorldFrame=0;
}

void CutsceneState::changeToWorld(int newWorld, double perc)
{
	//advanceMusicFading(newWorld,perc);

	switch(newWorld)
	{
		case DREAMS:
			mApp->getGameWorldManager()->setChangeWorldFactor(1-perc);
			break;
		case NIGHTMARES:
			mApp->getGameWorldManager()->setChangeWorldFactor(perc);
			break;
		default:
			break;
	}
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