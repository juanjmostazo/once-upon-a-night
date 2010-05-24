#include "GameRunningState.h"

#include "GameStateManager.h"
#include "GameOverState.h"
#include "GamePausedState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
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
#include "../Audio/AudioSubsystem.h"
#include "../Utils/Utils.h"

#include <fstream>

using namespace OUAN;

/// Default constructor
GameRunningState::GameRunningState()
:GameState()
,mIsChangingWorld(false)
{

}

/// Destructor
GameRunningState::~GameRunningState()
{

}

/// init game running state's resources
void GameRunningState::init(ApplicationPtr app)
{
	mApp=app;	

	mApp->getGameWorldManager()->setWorld(DREAMS);
	mApp->getGameWorldManager()->loadLevel(LEVEL_2);

	//mApp->getRenderSubsystem()->getCameraManager()->setCameraType(CAMERA_TRAJECTORY);
	mApp->getLogicSubsystem()->loadScripts();

	//...and initialise the active weapon according to the current world
	mApp->getGameWorldManager()->getGameObjectOny()->setInitialWeaponComponent(mApp->getGameWorldManager()->getWorld());

	mApp->mKeyBuffer=-1;
	
	mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
	mGUI->initGUI(shared_from_this());
	mGUI->hideConsole();

	//create HUD
	mHUD.reset(new HUDInGame());
	LogicComponentOnyPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponentOny();
	mHUD->init(onyLogic->getHealthPoints(),onyLogic->getNumLives(),mApp->getGameWorldManager()->getWorld());
	mApp->getGameWorldManager()->getGameObjectOny()->setAttack(convertRouletteValue(mHUD->getCurrentState()));

	mHUD->registerEventHandlers(mApp->getGameWorldManager()->getEventManager());

	mMusicChannels.clear();
	loadMusic();
	mApp->getAudioSubsystem()->playMusic(mMusicChannels[mApp->getGameWorldManager()->getWorld()].id,
		mMusicChannels[mApp->getGameWorldManager()->getWorld()].channelId,
		true);
	mAudioFrameCnt=0;
	mAudioFrameSkip=mApp->getAudioSubsystem()->getFrameSkip();
	
	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		boost::shared_ptr<GameRunningState> this_ = shared_from_this();
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<GameRunningState,ChangeWorldEvent>(this_,&GameRunningState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->registerHandler(eh,EVENT_TYPE_CHANGEWORLD);

	}
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
	mHUD->unregisterEventHandlers(mApp->getGameWorldManager()->getEventManager());
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
	mApp->getGameWorldManager()->unloadLevel();
	mApp->getGUISubsystem()->cleanUp();	
	mApp->getGUISubsystem()->init(mApp);
	mApp->mKeyBuffer=-1;

	if (mApp->getGameWorldManager()->getEventManager().get())
	{
		boost::shared_ptr<GameRunningState> this_ = shared_from_this();
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<GameRunningState,ChangeWorldEvent>(this_,&GameRunningState::processChangeWorld));
		mApp->getGameWorldManager()->getEventManager()->unregisterHandler(eh,EVENT_TYPE_CHANGEWORLD);
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
}

/// pause state
void GameRunningState::pause()
{
	//the following method is called to stop 
	//particle systems and other automatically animated
	//elements
	mApp->getRenderSubsystem()->pauseRendering();
	pauseMusic();
}
/// resume state
void GameRunningState::resume()
{
	mApp->getRenderSubsystem()->resumeRendering();
	unpauseMusic();
}
void GameRunningState::handleEvents()
{
	bool actionKeyPressed=false;
	bool useWeaponKeyPressed=false;
	bool useSpWeaponKeyPressed=false;
	if (mApp->mKeyBuffer<0)
	{
		checkDebuggingKeys();

		if (mApp->isPressedQuickExit())
		{
			//Ogre::LogManager::getSingleton().logMessage("isPressedQuickExit IN");
			mApp->mExitRequested=true;
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedPause())
		{
			GameStatePtr nextState(new GamePausedState());
			// Notice how pushState is called instead of changeState.
			// The reason to use push this time is to prevent unnecessary cleanup and initialisation, since
			// after the pause the application flow will come back to "GameRunning"
			mApp->getGameStateManager()->pushState(nextState,mApp);
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER; //0.5s
		}
		else if(mApp->isPressedAutoPoint())
		{
			//TODO: Replace with the proper auto-target functionality
			GameOverEventPtr evt= GameOverEventPtr(new GameOverEvent(true));
			mApp->getGameWorldManager()->addEvent(evt);
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
			//mApp->getGameWorldManager()->toggleTreeVisibility();
			mGUI->hideConsole();
		}
		
		else if (mApp->isPressedRotateLeft())
		{
			mHUD->spinRoulette(true);
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedRotateRight())
		{
			mHUD->spinRoulette(false);
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedDoAction())
		{
			actionKeyPressed=true;
			mApp->getGameWorldManager()->useObject();
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
	}
	if (mApp->isPressedUseWeapon() && !mApp->getGameWorldManager()->isOnyDying())
	{
		if (mApp->getGameWorldManager()->getWorld()==NIGHTMARES || mApp->mKeyBuffer<DEFAULT_KEY_BUFFER/2)
		{
			mApp->getGameWorldManager()->useWeapon();
			useWeaponKeyPressed=true;
			if (mApp->getGameWorldManager()->getWorld()==DREAMS)
				mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
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
	if (mApp->isPressedWeaponAction() && !mApp->getGameWorldManager()->isOnyDying())
	{
		useSpWeaponKeyPressed=true;
	}

			
	///////////////////////////////////////////////////////////
	// ONY (or first person camera): TYPE OF MOVEMENT
	//TODO: separate jump from movement?
	
	GameObjectOnyPtr ony=mApp->getGameWorldManager()->getGameObjectOny();
	if (ony.get())
	{
		int newState= ony->getLogicComponentOny()->getNewState();

		newState =actionKeyPressed
			?SET_BIT(newState,ONY_STATE_BIT_FIELD_ACTION)
			:CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_ACTION);

		Vector2 nextMovementXZ=mApp->getMovement();

		Vector3 nextMovement=Ogre::Vector3::ZERO;
		if (!mApp->getGameWorldManager()->isOnyDying())
		{
			nextMovement.x=nextMovementXZ.x;
			//nextMovement.y=0;
			nextMovement.z=nextMovementXZ.y;
		}
		
		
		// TODO: Uncomment when the attack logic is fully implemented
		// as it is now it interferes with returning to IDLE state
		//if (useWeaponKeyPressed && !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_ATTACK))
		//	currentState=SET_BIT(currentState,ONY_STATE_BIT_FIELD_ATTACK);
		//if (useSpWeaponKeyPressed && !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_SP_ATTACK))
		//	currentState=SET_BIT(currentState,ONY_STATE_BIT_FIELD_SP_ATTACK);

		bool zeroMovement=fabs(nextMovement.x)<Utils::DOUBLE_COMPARISON_DELTA && fabs(nextMovement.z)<Utils::DOUBLE_COMPARISON_DELTA;
		newState=zeroMovement
			?CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT)
			:SET_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT);
		if (mApp->isPressedWalk() && !mApp->getGameWorldManager()->isOnyDying())
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->walk();
			newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_WALK);
		}
		else newState=CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_WALK);

		if (mApp->isPressedJump() && !mApp->getGameWorldManager()->isOnyDying())
		{
			ony->getPhysicsComponentCharacter()->jump();
			newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_JUMP);
			
		}	
		//else currentState =CLEAR_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP);
		if(mApp->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIRST_PERSON)
		{
			mApp->getCameraManager()->processSimpleTranslation(nextMovement);
		}
		else if(mApp->getCameraManager()->getActiveCameraControllerType()!=CAMERA_FIXED_FIRST_PERSON)
		{
			//Access to [0] because there's only one Ony, otherwise it should be a loop
			//rotate movement vector using the current camera direction
			nextMovement=mApp->getCameraManager()->rotateMovementVector(nextMovement);
			ony->getPhysicsComponentCharacter()->setNextMovement(nextMovement);
			
			zeroMovement=fabs(nextMovement.x)<Utils::DOUBLE_COMPARISON_DELTA && fabs(nextMovement.z)<Utils::DOUBLE_COMPARISON_DELTA;
			newState =zeroMovement
				?CLEAR_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT)
				:SET_BIT(newState,ONY_STATE_BIT_FIELD_MOVEMENT);
		}

		ony->getLogicComponentOny()->setNewState(newState);
		
	}

	Vector2 cameraRotation;
	cameraRotation=mApp->getCameraRotation();
	mApp->getCameraManager()->processCameraRotation(cameraRotation);
}
void GameRunningState::checkDebuggingKeys()
{
	if (mApp->mKeyBuffer<0)
	{
		if (mApp->isPressedToggleDebugPerformance())
		{
			toggleDebugPerformance();
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleDebugPhysics())
		{		
			toggleDebugPhysics();
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleDebugTrajectory())
		{
			Ogre::LogManager::getSingleton().logMessage("ToggleDebugTrajectory key pressed");
			mApp->getTrajectoryManager()->toggleDebugMode(mApp->getGameWorldManager()->getWorld());
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleChangeCamera())
		{
			Ogre::LogManager::getSingleton().logMessage("ToggleChangeCamera key pressed");
			mApp->getCameraManager()->changeCamera();
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleChangeCameraController())
		{
			changeCameraController();
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleChangeWorld())
		{
			Ogre::LogManager::getSingleton().logMessage("ToggleChangeWorld key pressed");
			mApp->getGameWorldManager()->changeWorld();
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleChangeLevel())
		{
			toggleChangeLevel();		
			mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleConsole())
		{
			Ogre::LogManager::getSingleton().logMessage("ToggleConsole key pressed");
			if (mGUI->isVisible())
				mGUI->hideConsole();
			else
				mGUI->showConsole();
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleVolumes())
		{
			Ogre::LogManager::getSingleton().logMessage("ToggleVolumes key pressed");
			toggleVolumes();		
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
		else if (mApp->isPressedToggleGodMode())
		{	
			Ogre::LogManager::getSingleton().logMessage("ToggleGodMode key pressed");

			mApp->getGameWorldManager()->setGodMode(!mApp->getGameWorldManager()->getGodMode());
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
	}
}

void GameRunningState::update(long elapsedTime)
{
	double elapsedSeconds=(double)elapsedTime * 0.000001f;

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
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);
	//Ogre::LogManager::getSingleton().logMessage("* Updating Game World Manager");

	//Ogre::LogManager::getSingleton().logMessage("* Updating Camera Params");

	//NOTE (Aniol) I CHANGED THE ORDER SO CAMERA UPDATES BEFORE GAMEWORLDMANAGER TO GET FLASHLIGHT VOLUME POSITION RIGHT
	mApp->getCameraManager()->update(elapsedSeconds);

	mApp->getGameWorldManager()->update(elapsedSeconds);	

	mApp->getPhysicsSubsystem()->update(elapsedSeconds);

	mApp->getLogicSubsystem()->update(elapsedSeconds);

	mApp->getGameWorldManager()->postUpdate();


	//Ogre::LogManager::getSingleton().logMessage("Other stuff");
	mApp->mKeyBuffer-=elapsedTime;

	if (mApp.get() && mApp->getGameWorldManager().get() && mApp->getGameWorldManager()->isGameOver())
	{
		mApp->getRenderSubsystem()->captureScene(SAVED_RTT_FILENAME);
		GameStatePtr nextState(new GameOverState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}

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
	mGUI->update(elapsedSeconds);

	if (mAudioFrameSkip==0 || mAudioFrameCnt==0)
	{
		mApp->getAudioSubsystem()->update(elapsedSeconds);
	}
	if ((mAudioFrameCnt++)>mAudioFrameSkip)
		mAudioFrameCnt=0;
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

bool GameRunningState::render()
{
	RenderSubsystemPtr renderSubsystem=mApp->getRenderSubsystem();

	if (mApp->getDebugMode()!=DEBUGMODE_NONE)
	{
		renderSubsystem->updateStats();
		renderSubsystem->updateDebugInfo();
		renderSubsystem->showOverlay(OVERLAY_DEBUG_PANEL);
	}

	renderSubsystem->updateVisualDebugger();

	mHUD->show();

	return renderSubsystem->render();
}

void GameRunningState::toggleDebugPerformance()
{
	Ogre::LogManager::getSingleton().logMessage("ToggleDebugPerformance key pressed");

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
	Ogre::LogManager::getSingleton().logMessage("ToggleDebugPhysics key pressed");

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

void GameRunningState::toggleChangeLevel()
{
	Ogre::LogManager::getSingleton().logMessage("ToggleChangeLevel key pressed");
	Ogre::LogManager::getSingleton().logMessage("isPressedToggleChangeLevel IN");
	if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_TEST)==0)
	{
		mApp->getGameWorldManager()->loadLevel(LEVEL_CLOCK);
	}
	else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_2)==0)
	{
		mApp->getGameWorldManager()->loadLevel(LEVEL_1);
	}
	else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_1)==0)
	{
		mApp->getGameWorldManager()->loadLevel(LEVEL_2);
	}
	else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_2)==0)
	{
		mApp->getGameWorldManager()->loadLevel(LEVEL_TEST);
	}
}

void GameRunningState::changeCameraController()
{
	Ogre::LogManager::getSingleton().logMessage("ToggleChangeCameraController key pressed");

	mApp->getCameraManager()->changeCameraController();
	if(mApp->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIXED_FIRST_PERSON)
		mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntity()->setVisible(false);
	else
		mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntity()->setVisible(true);
}

void GameRunningState::toggleVolumes()
{
	Ogre::LogManager::getSingleton().logMessage("ToggleVolumes key pressed");

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

	
	mApp->getAudioSubsystem()->load("DREAMS00","General");
	mMusicChannels[DREAMS].id="DREAMS00";
	mApp->getAudioSubsystem()->load("NIGHTMARES00","General");
	mMusicChannels[NIGHTMARES].id="NIGHTMARES00";
}

void GameRunningState::changeMusic(int world)
{
	int oldWorld=world==DREAMS?NIGHTMARES:DREAMS;
	mApp->getAudioSubsystem()->stopMusic(mMusicChannels[oldWorld].channelId);
	mApp->getAudioSubsystem()->playMusic(mMusicChannels[world].id,mMusicChannels[world].channelId,true);
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

void GameRunningState::activateChangeWorldFast()
{
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
		Ogre::LogManager::getSingletonPtr()->logMessage("GameRunningState::endMusicFading CRASH");
		Ogre::LogManager::getSingletonPtr()->logMessage(e.what());
	}
}
void GameRunningState::changeWorldFinished(int newWorld)
{
	endMusicFading(newWorld);
	//switch(newWorld)
	//{
	//	case DREAMS:
	//		break;
	//	case NIGHTMARES:
	//		break;
	//	default:
	//		break;
	//}
}

void GameRunningState::changeWorldStarted(int newWorld)
{
	initMusicFading(newWorld);
	//switch(newWorld)
	//{
	//	case DREAMS:
	//		break;
	//	case NIGHTMARES:
	//		break;
	//	default:
	//		break;
	//}
}

void GameRunningState::changeToWorld(int newWorld, double perc)
{
	advanceMusicFading(newWorld,perc);
	//switch(newWorld)
	//{
	//	case DREAMS:
	//		break;
	//	case NIGHTMARES:
	//		break;
	//	default:
	//		break;
	//}
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