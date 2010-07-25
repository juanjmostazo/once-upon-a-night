#include "OUAN_Precompiled.h"

#include "GameRunningState.h"
#include "LevelLoadingState.h"

#include "GameStateManager.h"
#include "MainMenuState.h"
#include "GameOverState.h"
#include "GamePausedState.h"
#include "InGameMenuState.h"
#include "CutsceneState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/ChangeWorldRenderer.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Graphics/HUD/HUDInGame.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIConsole.h"
#include "../Logic/LogicSubsystem.h"
#include "../Logic/LogicComponent/LogicComponentOny.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectFlashLight.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Audio/AudioSubsystem.h"
#include "../Utils/Utils.h"

using namespace OUAN;


GameRunningState* GameRunningState::mInst=NULL;

/// Default constructor
GameRunningState::GameRunningState()
:GameState()
,mIsChangingWorld(false)
,toGameOverTime(TO_GAME_OVER_DEFAULT)
,toGameOverElapsed(0.0)
{
	mInst=this;
	mChangeWorldElapsedTime=0;
	mIsChangingWorld=false;
	mProceedToNextLevel=false;
}

/// Destructor
GameRunningState::~GameRunningState()
{

}

/// init game running state's resources
void GameRunningState::init(ApplicationPtr app)
{
	GameState::init(app);
	firstRender=true;

	mApp->getGameWorldManager()->initGame();

	//...and initialise the active weapon according to the current world
	mApp->getGameWorldManager()->getGameObjectOny()->setInitialWeaponComponent(mApp->getGameWorldManager()->getWorld());
	
	//create GUI
	mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
	mGUI->initGUI(shared_from_this());
	mGUI->hideConsole();

	//create HUD
	mHUD.reset(new HUDInGame());
	LogicComponentOnyPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponentOny();
	mHUD->init(onyLogic->getHealthPoints(),onyLogic->getNumLives(),mApp->getGameWorldManager()->getWorld());
	mApp->getGameWorldManager()->getGameObjectOny()->setAttack(convertRouletteValue(mHUD->getCurrentState()));

	mHUD->registerEventHandlers(mApp->getGameWorldManager()->getEventManager());

	//Load music
	mMusicChannels.clear();
	loadMusic();
	mApp->getAudioSubsystem()->playMusic(mMusicChannels[mApp->getGameWorldManager()->getWorld()].id,
		mMusicChannels[mApp->getGameWorldManager()->getWorld()].channelId,
		true);
	mApp->mAudioFrameCnt=0;
	
	//Register events
	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		EventHandlerPtr eh;
		boost::shared_ptr<GameRunningState> this_ = shared_from_this();
		eh = EventHandlerPtr(new EventHandler<GameRunningState,ChangeWorldEvent>(this_,&GameRunningState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->registerHandler(eh,EVENT_TYPE_CHANGEWORLD);

		eh = EventHandlerPtr(new EventHandler<GameRunningState,OnyDiesEvent>(this_,&GameRunningState::processOnyDies));
		mApp->getGameWorldManager()->getEventManager()->registerHandler(eh,EVENT_TYPE_ONY_DEATH);
		eh=EventHandlerPtr(new EventHandler<GameRunningState,GameOverEvent>(this_,&GameRunningState::processGameOver));
		mApp->getGameWorldManager()->getEventManager()->registerHandler(eh,EVENT_TYPE_GAMEOVER);
	}

	//Set up initial world change
	mIsChangingWorld=false;

	mApp->getRenderSubsystem()->getChangeWorldRenderer()->createDebugMiniScreens();

	changeWorldFinished(mApp->getGameWorldManager()->getWorld());

}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
	GameState::cleanUp();

	mHUD->unregisterEventHandlers(mApp->getGameWorldManager()->getEventManager());
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
	mApp->getRenderSubsystem()->resumeRendering();
	mApp->getGameWorldManager()->unloadLevel();
	mApp->getGUISubsystem()->cleanUp();	
	mApp->getGUISubsystem()->init(mApp);

	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		EventHandlerPtr eh;
		boost::shared_ptr<GameRunningState> this_ = shared_from_this();
		eh = EventHandlerPtr(new EventHandler<GameRunningState,ChangeWorldEvent>(this_,&GameRunningState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->unregisterHandler(eh,EVENT_TYPE_CHANGEWORLD);

		eh = EventHandlerPtr(new EventHandler<GameRunningState,OnyDiesEvent>(this_,&GameRunningState::processOnyDies));
		mApp->getGameWorldManager()->getEventManager()->unregisterHandler(eh,EVENT_TYPE_ONY_DEATH);
		eh=EventHandlerPtr(new EventHandler<GameRunningState,GameOverEvent>(this_,&GameRunningState::processGameOver));
	}
	
	//Destroy HUD
	mHUD->destroy();

	if (mApp->getAudioSubsystem()->isMusicPlaying(mMusicChannels[DREAMS].channelId))
	{
		mApp->getAudioSubsystem()->stopMusic(mMusicChannels[DREAMS].channelId);
	}
	if (mApp->getAudioSubsystem()->isMusicPlaying(mMusicChannels[NIGHTMARES].channelId))
	{
		mApp->getAudioSubsystem()->stopMusic(mMusicChannels[NIGHTMARES].channelId);
	}
	//Unload all sounds: the ones in-game and the interface ones, as well as the music
	//mApp->getAudioSubsystem()->unloadAll();
}

/// pause state
void GameRunningState::pause()
{
	//the following method is called to stop 
	//particle systems and other automatically animated
	//elements
	mApp->getRenderSubsystem()->pauseRendering();
	pauseMusic();
	mApp->setDefaultKeyBufferAll();
	mHUD->hide();
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
}
/// resume state
void GameRunningState::resume()
{	
	mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
	mGUI->initGUI(shared_from_this());
	mGUI->hideConsole();

	if (!mApp->mBackToMenu)
	{
		mApp->getRenderSubsystem()->resumeRendering();
		unpauseMusic();
		mHUD->show();
	}

}
void GameRunningState::handleEvents()
{
	int pad;
	int key;

	bool actionKeyPressed=false;
	bool useWeaponKeyPressed=false;
	bool useSpWeaponKeyPressed=false;

	checkDebuggingKeys();

	if (mApp->isPressedQuickExit(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			//Logger::getInstance()->log("isPressedQuickExit IN");
			//mApp->mExitRequested=true;
			//mApp->getGameWorldManager()->getGameObjectViewport()->disableAllCompositors();
			GameOverEventPtr evt;
			evt.reset(new GameOverEvent(false));
			mApp->getGameWorldManager()->addEvent(evt);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedPause(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			GameStatePtr nextState(new GamePausedState());
			// Notice how pushState is called instead of changeState.
			// The reason to use push this time is to prevent unnecessary cleanup and initialisation, since
			// after the pause the application flow will come back to "GameRunning"
			mApp->getGameStateManager()->pushState(nextState,mApp);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if(mApp->isPressedCameraFixedFirstPerson(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{			
			mApp->getCameraManager()->setCameraFixedFirstPerson(true);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedRotateLeft(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			mHUD->spinRoulette(true);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedRotateRight(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			mHUD->spinRoulette(false);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedCenterCamera(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			mApp->getCameraManager()->centerToTargetBack(true);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedMenu(&pad,&key))
	{
		if (mApp->getKeyBuffer(key) < 0)
		{
			GameStatePtr nextState(new InGameMenuState());
			mApp->getGameStateManager()->pushState(nextState,mApp);
			mApp->setDefaultKeyBuffer(key);
		}
	}
	
	if (mApp->isPressedUseWeapon(&pad,&key) && 
		!mApp->getGameWorldManager()->isOnyDying() && 
		!mApp->getGameWorldManager()->isOnyHit())
	{
		if(mApp->getCameraManager()->targetMovementAllowed())
		{
			if (mApp->getGameWorldManager()->getWorld()==NIGHTMARES || 
				mApp->getKeyBuffer(key) < DEFAULT_KEY_BUFFER/2)
			{
				mApp->getGameWorldManager()->useWeapon();
				useWeaponKeyPressed=true;

				if (mApp->getGameWorldManager()->getWorld()==DREAMS)
				{
					mApp->setDefaultKeyBuffer(key);
				}
			}
		}
	}
	else
	{
		//this method will basically apply to the flashlight, as it'll stop working
		//when the button is not being pressed
		if (!mApp->getGameWorldManager()->isOnyDying())		
		{
			mApp->getGameWorldManager()->stopUsingWeapon();
		}
	}

	if (mApp->isPressedWeaponAction(&pad,&key) && 
		!mApp->getGameWorldManager()->isOnyDying())
	{
		if(mApp->getCameraManager()->targetMovementAllowed())
		{
			useSpWeaponKeyPressed=true;
		}
	}

	///////////////////////////////////////////////////////////
	// ONY (or first person camera): TYPE OF MOVEMENT
	//TODO: separate jump from movement?
	
	GameObjectOnyPtr ony = mApp->getGameWorldManager()->getGameObjectOny();
	if (ony.get())
	{
		int newState = ony->getLogicComponentOny()->getNewState();

		/*
		Ogre::Vector3 outernMovement = !mApp->getGameWorldManager()->isOnyDying() 
				? mApp->getMovement()
				: Ogre::Vector3::ZERO;
		*/

		int movementX;
		int movementZ;

		mApp->getMovementSimple(movementX, movementZ);

		Ogre::Vector3 outernMovement = !mApp->getGameWorldManager()->isOnyDying() 
			    ? Ogre::Vector3(movementX, 0, movementZ)
				: Ogre::Vector3::ZERO;

		if (useWeaponKeyPressed && !CHECK_BIT(newState,ONY_STATE_BIT_FIELD_ATTACK))
		{
			newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_ATTACK);
			//Logger::getInstance()->log("SETTING ATTACK FLAG");
		}
		//if (useSpWeaponKeyPressed && !CHECK_BIT(newState,ONY_STATE_BIT_FIELD_SP_ATTACK))
		//	newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_SP_ATTACK);

		bool zeroMovement = 
			fabs(outernMovement.x) < Utils::DOUBLE_COMPARISON_DELTA && 
			fabs(outernMovement.z) < Utils::DOUBLE_COMPARISON_DELTA;

		newState = zeroMovement
			? CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT)
			: SET_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT);

		if (mApp->isPressedWalk(&pad,&key) && 
			!mApp->getGameWorldManager()->isOnyDying())
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacterOny()->walk();
			newState = SET_BIT(newState,ONY_STATE_BIT_FIELD_WALK);
		}
		else
		{
			newState = CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_WALK);
		}

		if (mApp->isPressedJump(&pad,&key) && 
			!mApp->getGameWorldManager()->isOnyDying())
		{
			if(mApp->getCameraManager()->targetMovementAllowed())
			{
				ony->getPhysicsComponentCharacterOny()->jump();
			}

			newState = SET_BIT(newState,ONY_STATE_BIT_FIELD_JUMP);
		}	
		//else
		//{
		//	currentState = CLEAR_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP);
		//}

		if(mApp->getCameraManager()->getCameraControllerType()==CAMERA_FIRST_PERSON)
		{
			mApp->getCameraManager()->processSimpleTranslation(outernMovement);
		}
		else if(mApp->getCameraManager()->targetMovementAllowed())
		{
			//Access to [0] because there's only one Ony, otherwise it should be a loop
			//rotate movement vector using the current camera direction

			ony->getPhysicsComponentCharacterOny()->setOuternMovement(outernMovement);
			
			zeroMovement = 
				fabs(outernMovement.x) < Utils::DOUBLE_COMPARISON_DELTA && 
				fabs(outernMovement.z) < Utils::DOUBLE_COMPARISON_DELTA;

			newState = zeroMovement
				? CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT)
				: SET_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT);
		}

		ony->getLogicComponentOny()->setNewState(newState);
	}

	mApp->getCameraManager()->processCameraRotation(mApp->getCameraRotation());
}

void GameRunningState::checkDebuggingKeys()
{
	int pad;
	int key;

	if (mApp->isPressedToggleDebugPerformance(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			toggleDebugPerformance();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleDebugPhysics(&pad,&key))
	{		
		if (mApp->getKeyBuffer(key)<0)
		{
			toggleDebugPhysics();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleDebugTrajectory(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleDebugTrajectory key pressed");
			mApp->getTrajectoryManager()->toggleDebugMode(mApp->getGameWorldManager()->getWorld());
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleChangeCamera(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleChangeCamera key pressed");
			mApp->getCameraManager()->changeAutoCamera();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleChangeCameraController(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			changeCameraController();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleChangeWorld(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleChangeWorld key pressed");
			mApp->getGameWorldManager()->changeWorld();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleChangeLevel(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			toggleChangeLevel();		
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleConsole(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleConsole key pressed");

			if (mGUI->isVisible())
			{
				mGUI->hideConsole();
			}
			else
			{
				mGUI->showConsole();
			}

			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleVolumes(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleVolumes key pressed");
			toggleVolumes();		
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleGodMode(&pad,&key))
	{	
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleGodMode key pressed");
			mApp->getGameWorldManager()->setGodMode(!mApp->getGameWorldManager()->isGodMode());
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleChangeWorldDebug(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleChangeWorldDebug key pressed");
			mApp->getRenderSubsystem()->getChangeWorldRenderer()->setDebugScreensActive(
				!mApp->getRenderSubsystem()->getChangeWorldRenderer()->getDebugScreensActive());
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedToggleShowSceneNodes(&pad,&key))
	{	
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("ToggleShowSceneNodes key pressed");
			mApp->getRenderSubsystem()->toggleDisplaySceneNodes();
			mApp->setDefaultKeyBuffer(key);
		}
	}
	else if (mApp->isPressedRunCutscene(&pad,&key))
	{
		if (mApp->getKeyBuffer(key)<0)
		{
			Logger::getInstance()->log("RunCutscene pressed");
			CutsceneStatePtr cutscenestate = CutsceneStatePtr(new CutsceneState());
			cutscenestate->setCutsceneFile("cutscene_engine.lua");
			cutscenestate->setCutsceneFunction("helloWorld");
			mApp->getGameStateManager()->pushState(cutscenestate,mApp);
			mApp->setDefaultKeyBuffer(key);
		}
	}
}

void GameRunningState::update(long elapsedTime)
{
	GameState::update(elapsedTime);

	firstRender=false;

	if(mProceedToNextLevel)
	{
		LevelLoadingState * levelLoadingState = new LevelLoadingState();
		levelLoadingState->setLevelFileName(mNextLevel);
		mApp->getGameWorldManager()->unloadLevel();
		GameStatePtr nextState(levelLoadingState);
		mApp->getGameWorldManager()->getParent()->getGameStateManager()->changeState(nextState,mApp);
	}
	else if (mayProceedToGameOver())
	{
		mApp->getRenderSubsystem()->captureScene(SAVED_RTT_FILENAME);
		GameStatePtr nextState(new GameOverState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}
	else if (mApp->mBackToMenu)
	{
		Logger::getInstance()->log("Back to menu is set!!");
		mApp->mBackToMenu=false;
		GameStatePtr menuState = GameStatePtr(new MainMenuState());
		mApp->getGameStateManager()->changeState(menuState,mApp);
	}
	else
	{
		double elapsedSeconds=(double)elapsedTime * 0.000001f;
		if (!mApp->getGameWorldManager()->isGameOver())
		{
			if(mIsChangingWorld)
			{
				mChangeWorldElapsedTime+=elapsedSeconds;
				if(mChangeWorldElapsedTime>=mChangeWorldTotalTime)
				{
					changeToWorld(mWorld,1);
					changeWorldFinished(mWorld);
					mIsChangingWorld=false;
				}
				else
				{
					changeToWorld(mWorld,mChangeWorldElapsedTime/mChangeWorldTotalTime);
				}
			}

			//std::stringstream out;
			//out << elapsedSeconds;
			//std::string elapsedTimeDebug = out.str();
			//Logger::getInstance()->log("Updating " + elapsedTimeDebug);
			//Logger::getInstance()->log("* Updating Game World Manager");

			//Logger::getInstance()->log("* Updating Camera Params");

		}
		else 
		{
			toGameOverElapsed+=elapsedSeconds;
		}

		if (!mApp->getGameWorldManager()->isGameOver())
		{
			mApp->getGameWorldManager()->update(elapsedSeconds);	

			mApp->getPhysicsSubsystem()->update(elapsedSeconds);

			mApp->getCameraManager()->update(elapsedSeconds);

			mApp->getLogicSubsystem()->update(elapsedSeconds);

			mApp->getTrajectoryManager()->updateDebugNodes();

			mApp->getGameWorldManager()->postUpdate();

			if (mApp.get() && mApp->getGameWorldManager().get() && mApp->getGameWorldManager()->getGameObjectOny().get())
			{
				LogicComponentOnyPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponentOny();
				mHUD->update(elapsedSeconds,onyLogic->getHealthPoints(),onyLogic->getNumLives());

				if (mHUD->isSelectedModeChanged())
				{
					TWeaponMode newWeaponMode = convertRouletteValue(mHUD->getCurrentState());
					mHUD->setSelectedModeChanged(false);
					WeaponModeChangedEventPtr evt(new WeaponModeChangedEvent(newWeaponMode));
					mApp->getGameWorldManager()->addEvent(evt);
				}
			}
			
			// Update 3D sound listener's position
			Ogre::Camera* activeCam = mApp->getCameraManager()->getCamera();
			if (activeCam)
			{
				mApp->getAudioSubsystem()->set3DAttributes(activeCam->getPosition(),Ogre::Vector3::ZERO,
					activeCam->getOrientation()*Ogre::Vector3::UNIT_Z,Ogre::Vector3::UNIT_Y);
			}

		}

		mGUI->update(elapsedSeconds);

		if (mApp->mAudioFrameSkip==0 || mApp->mAudioFrameCnt==0)
		{
			mApp->getAudioSubsystem()->update(elapsedSeconds);
		}
		if ((mApp->mAudioFrameCnt++)>mApp->mAudioFrameSkip)
		{
			mApp->mAudioFrameCnt=0;
		}
	}
}

TWeaponMode GameRunningState::convertRouletteValue(TRouletteState rouletteValue)
{
	TWeaponMode newWeaponMode=WEAPON_MODE_INVALID;
	switch (rouletteValue)
	{
	case ROULETTE_STATE_0:
		newWeaponMode=WEAPON_MODE_0;
		break;
	case ROULETTE_STATE_1:
		newWeaponMode=WEAPON_MODE_1;
		break;
	case ROULETTE_STATE_2:
		newWeaponMode=WEAPON_MODE_2;
	//TODO: Special cases, other modes
	default:
		break;
	}
	return newWeaponMode;
}

void GameRunningState::toggleDebugPerformance()
{
	Logger::getInstance()->log("ToggleDebugPerformance key pressed");

	if (mApp->getDebugMode()!=DEBUGMODE_PERFORMANCE)
	{
		mApp->setDebugMode(DEBUGMODE_PERFORMANCE);
		mApp->getRenderSubsystem()->hideVisualDebugger();
		mApp->getRenderSubsystem()->showOverlay(OVERLAY_DEBUG_PANEL);
	}
	else
	{
		mApp->setDebugMode(DEBUGMODE_NONE);
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
	}
}

void GameRunningState::toggleDebugPhysics()
{
	Logger::getInstance()->log("ToggleDebugPhysics key pressed");

	if (mApp->getDebugMode()!=DEBUGMODE_PHYSICS)
	{
		mApp->setDebugMode(DEBUGMODE_PHYSICS);
		mApp->getRenderSubsystem()->showOverlay(OVERLAY_DEBUG_PANEL);
		mApp->getRenderSubsystem()->showVisualDebugger();
	}
	else 
	{
		mApp->setDebugMode(DEBUGMODE_NONE);
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
		mApp->getRenderSubsystem()->hideVisualDebugger();
	}
}

void GameRunningState::changeLevel(std::string level)
{
	ChangeLevelEventPtr pChangeLevelEvent;

	pChangeLevelEvent.reset(new ChangeLevelEvent());
	pChangeLevelEvent->level=level;

	mInst->getApp()->getGameWorldManager()->addEvent(pChangeLevelEvent);

	mInst->setProceedToNextLevel(true);
	mInst->setNextLevel(level);
}

void GameRunningState::setProceedToNextLevel(bool proceedToNextLevel)
{
	mProceedToNextLevel=proceedToNextLevel;
}

void GameRunningState::setNextLevel(std::string nextLevel)
{
	mNextLevel=nextLevel;
}

void GameRunningState::toggleChangeLevel()
{
	Logger::getInstance()->log("ToggleChangeLevel key pressed");

	if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_CLOCK)==0)
	{
		changeLevel(LEVEL_2);
	}
	else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_2)==0)
	{
		changeLevel(LEVEL_CLOCK);
	}
}

void GameRunningState::changeCameraController()
{
	Logger::getInstance()->log("ToggleChangeCameraController key pressed");

	mApp->getCameraManager()->changeCameraController();
}

void GameRunningState::toggleVolumes()
{
	Logger::getInstance()->log("ToggleVolumes key pressed");

	TGameObjectTriggerBoxContainer * cBox = mApp->getGameWorldManager()->getGameObjectTriggerBoxContainer();
	for(unsigned int i=0; i<cBox->size(); i++)
	{
		cBox->at(i)->changeVisibility();
	}

	TGameObjectTriggerCapsuleContainer * cCapsule = mApp->getGameWorldManager()->getGameObjectTriggerCapsuleContainer();
	for(unsigned int i=0; i<cCapsule->size(); i++)
	{
		cCapsule->at(i)->changeVisibility();
	}
}

TWeaponMode GameRunningState::getCurrentWeaponMode()
{
	if (mHUD.get())
		return convertRouletteValue(mHUD->getCurrentState());
	return WEAPON_MODE_INVALID;
}

void GameRunningState::loadMusic()
{
	
	mApp->getAudioSubsystem()->load("DREAMS00",AUDIO_RESOURCES_GROUP_NAME);
	mMusicChannels[DREAMS].id="DREAMS00";
	mApp->getAudioSubsystem()->load("NIGHTMARES00",AUDIO_RESOURCES_GROUP_NAME);
	mMusicChannels[NIGHTMARES].id="NIGHTMARES00";

	mApp->getAudioSubsystem()->load("SUCCESS",AUDIO_RESOURCES_GROUP_NAME);
	mMusicChannels[-1].id="SUCCESS";
}

void GameRunningState::changeMusic(int world)
{
	int oldWorld=world==DREAMS?NIGHTMARES:DREAMS;
	mApp->getAudioSubsystem()->stopMusic(mMusicChannels[oldWorld].channelId);
	mApp->getAudioSubsystem()->playMusic(mMusicChannels[world].id,mMusicChannels[world].channelId,true);
}
void GameRunningState::playMusic(const std::string& musicID)
{
	int world = mInst->getApp()->getGameWorldManager()->getWorld();
	mInst->getApp()->getAudioSubsystem()->stopMusic(mInst->mMusicChannels[world].channelId);
	
	if (!mInst->getApp()->getAudioSubsystem()->isLoaded(musicID))
		mInst->getApp()->getAudioSubsystem()->load(musicID,AUDIO_RESOURCES_GROUP_NAME);
	mInst->mMusicChannels[-1].id=musicID;
	mInst->getApp()->getAudioSubsystem()->playMusic(musicID, mInst->mMusicChannels[-1].channelId,true);
}
void GameRunningState::playSoundFromGameObject(const std::string& objectName, const std::string& soundID)
{
	mInst->getApp()->getGameWorldManager()->playSoundFromGameObject(objectName,soundID);
}
void GameRunningState::processGameOver(GameOverEventPtr evt)
{
	if (evt->isWin())
	{
		playMusic("SUCCESS");
		playSoundFromGameObject(mApp->getGameWorldManager()->getGameObjectOny()->getName(),"any_triumph");
	}
}
void GameRunningState::processChangeWorld(ChangeWorldEventPtr evt)
{
	mWorld=evt->getNewWorld();
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

void GameRunningState::processOnyDies(OnyDiesEventPtr evt)
{

}

void GameRunningState::activateChangeWorldFast()
{
	mIsChangingWorld=false;
	changeWorldFinished(mApp->getGameWorldManager()->getWorld());
}

void GameRunningState::activateChangeWorld()
{
	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime=mChangeWorldTotalTime-mChangeWorldElapsedTime;
	}
	else
	{
		mChangeWorldElapsedTime=0;
		mIsChangingWorld=true;
		changeWorldStarted(mWorld);
	}
}

void GameRunningState::renderChangeWorldTextures()
{
	RenderSubsystemPtr renderSubsystem=mApp->getRenderSubsystem();

	mApp->getGameWorldManager()->getGameObjectViewport()->setEffect(
		mApp->getRenderSubsystem()->CHANGEWORLD,false);

	if(mIsChangingWorld || renderSubsystem->getChangeWorldRenderer()->getDebugScreensActive())
	{
		mApp->getGameWorldManager()->setChangeWorldRender();
		renderSubsystem->getChangeWorldRenderer()->renderToTextureChangeWorld();

		switch(mWorld)
		{
		case DREAMS:
			if(mWorld!=mOldWorld)
			{
				mApp->getGameWorldManager()->setNightmaresRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureNightmares();
				mApp->getGameWorldManager()->setDreamsRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureDreams();
			}
			else
			{
				mApp->getGameWorldManager()->setDreamsRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureDreams();
				mApp->getGameWorldManager()->setNightmaresRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureNightmares();
			}
			break;
		case NIGHTMARES:
			if(mWorld!=mOldWorld)
			{
				mApp->getGameWorldManager()->setDreamsRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureDreams();
				mApp->getGameWorldManager()->setNightmaresRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureNightmares();
			}
			else
			{
				mApp->getGameWorldManager()->setNightmaresRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureNightmares();
				mApp->getGameWorldManager()->setDreamsRender();
				renderSubsystem->getChangeWorldRenderer()->renderToTextureDreams();
			}
			break;
		default:
			break;
		}
		mApp->getGameWorldManager()->getGameObjectViewport()->setEffect(
			mApp->getRenderSubsystem()->CHANGEWORLD,true);
	}

	currentChangeWorldFrame++;
}

bool GameRunningState::render()
{
	if (!firstRender)
	{
		TGameObjectContainer * container = mApp->getGameWorldManager()->getAllGameObjects();
		
		if (!container->empty())
		{
			for (TGameObjectContainer::iterator it=container->begin();it!=container->end();++it)
			{
				//Logger::getInstance()->log("UPDATE "+it->second->getName());
				if (it->second->isEnabled())
				{
					if(it->second->isWorthRendering())
					{
						it->second->setVisible(true);
					}
					else
					{
						it->second->setVisible(false);
					}
				}
			}
		}

		RenderSubsystemPtr renderSubsystem=mApp->getRenderSubsystem();

		if (mApp->getDebugMode()!=DEBUGMODE_NONE)
		{
			renderSubsystem->updateStats();
			renderSubsystem->updateDebugInfo();
			renderSubsystem->showOverlay(OVERLAY_DEBUG_PANEL);
		}

		renderSubsystem->updateVisualDebugger();

		mHUD->show();

		renderChangeWorldTextures();
		return renderSubsystem->render();
	}
	return true;

}

void GameRunningState::changeWorldFinished(int newWorld)
{
	endMusicFading(newWorld);

	mWorld=newWorld;

	mApp->getRenderSubsystem()->getChangeWorldRenderer()->setChangeWorldFactor(0);
	switch(newWorld)
	{
		case DREAMS:
			mOldWorld=NIGHTMARES;
			mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToNightmares();
			break;
		case NIGHTMARES:
			mOldWorld=DREAMS;
			mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToDreams();
			break;
		default:
			break;
	}

	switch(mWorld)
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
}

void GameRunningState::changeWorldStarted(int newWorld)
{
	initMusicFading(newWorld);
	mApp->getRenderSubsystem()->getChangeWorldRenderer()->setChangeWorldFactor(0);
	switch(newWorld)
	{
		case DREAMS:
			mOldWorld=NIGHTMARES;
			mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToDreams();
			break;
		case NIGHTMARES:
			mOldWorld=DREAMS;
			mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToNightmares();
			break;
		default:
			break;
	}

	currentChangeWorldFrame=0;
}

void GameRunningState::changeToWorld(int newWorld, double perc)
{
	advanceMusicFading(newWorld,perc);

	if(mWorld!=mOldWorld)
	{
		mApp->getRenderSubsystem()->getChangeWorldRenderer()->setChangeWorldFactor(perc);
	}
	else
	{
		mApp->getRenderSubsystem()->getChangeWorldRenderer()->setChangeWorldFactor(1-perc);
	}

	switch(newWorld)
	{
		case DREAMS:
			if(mWorld!=mOldWorld)
			{
				mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToDreams();
			}
			else
			{
				mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToNightmares();
			}
			break;
		case NIGHTMARES:
			if(mWorld!=mOldWorld)
			{
				mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToNightmares();
			}
			else
			{
				mApp->getRenderSubsystem()->getChangeWorldRenderer()->setToDreams();
			}
			break;
		default:
			break;
	}
}

void GameRunningState::initMusicFading(int newWorld)
{
	AudioSubsystemPtr audioSS=mApp->getAudioSubsystem();
	int oldWorld=newWorld==DREAMS?NIGHTMARES:DREAMS;	
	double startVolume=0.0;
	bool mute=false;
	try
	{		
		mute=fabs(audioSS->getMusicVolume(mMusicChannels[oldWorld].channelId)-0.0)<.0000001;
	}
	catch(const std::exception&)
	{

	}
	if (!audioSS->isMusicPlaying(mMusicChannels[oldWorld].channelId) || mute)
		startVolume=1.0;
	audioSS->playMusic(mMusicChannels[newWorld].id,mMusicChannels[newWorld].channelId,true);
	audioSS->setMusicVolume(mMusicChannels[newWorld].channelId,startVolume);
}
void GameRunningState::advanceMusicFading(int newWorld,double percentage)
{
	AudioSubsystemPtr audioSS=mApp->getAudioSubsystem();
	int oldWorld=newWorld==DREAMS?NIGHTMARES:DREAMS;
	if (audioSS->isMusicPlaying(mMusicChannels[oldWorld].channelId))
	{
		audioSS->setMusicVolume(mMusicChannels[oldWorld].channelId,(1-percentage));	
	}
	audioSS->setMusicVolume(mMusicChannels[newWorld].channelId,percentage);
}
void GameRunningState::endMusicFading(int newWorld)
{
	try{
		AudioSubsystemPtr audioSS=mApp->getAudioSubsystem();
		int oldWorld=newWorld==DREAMS?NIGHTMARES:DREAMS;
		audioSS->stopMusic(mMusicChannels[oldWorld].channelId);
		if (!audioSS->isMusicPlaying(mMusicChannels[newWorld].channelId))
		{
			audioSS->playMusic(mMusicChannels[newWorld].id,mMusicChannels[newWorld].channelId,true);
		}	
	}
	catch (const std::exception& e)
	{
		Logger::getInstance()->log("GameRunningState::endMusicFading CRASH");
		Logger::getInstance()->log(e.what());
	}
}

void GameRunningState::clearMusic()
{
	mApp->getAudioSubsystem()->stopMusic(mMusicChannels[DREAMS].channelId);
	mApp->getAudioSubsystem()->unload(mMusicChannels[DREAMS].id);
	mApp->getAudioSubsystem()->stopMusic(mMusicChannels[NIGHTMARES].channelId);
	mApp->getAudioSubsystem()->unload(mMusicChannels[NIGHTMARES].id);
	mMusicChannels.clear();
}

void GameRunningState::pauseMusic()
{
	mApp->getAudioSubsystem()->pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,true);
}

void GameRunningState::unpauseMusic()
{
	mApp->getAudioSubsystem()->pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,false);
}
bool GameRunningState::mayProceedToGameOver()
{
	if (mApp->getGameWorldManager()->isGameOver())
	{
		Logger::getInstance()->log("Game over is set!");
	}
	int channel=mMusicChannels[-1].channelId;
	return mApp->getGameWorldManager()->isGameOver() && 
		(!mApp->getAudioSubsystem()->isMusicPlaying(channel)
		|| toGameOverElapsed>=toGameOverTime);
}