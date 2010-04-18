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

#include <fstream>

using namespace OUAN;

/// Default constructor
GameRunningState::GameRunningState()
:GameState()
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

	mApp->mKeyBuffer=-1;
	
	mGUI = boost::dynamic_pointer_cast<GUIConsole>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_CONSOLE));
	mGUI->initGUI(shared_from_this());
	mGUI->hideConsole();

	//create HUD
	mHUD.reset(new HUDInGame());
	LogicComponentOnyPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponentOny();
	mHUD->init(onyLogic->getHealthPoints(),onyLogic->getNumLives(),mApp->getGameWorldManager()->getWorld());
	mApp->getGameWorldManager()->getGameObjectOny()->setWeaponMode(convertRouletteValue(mHUD->getCurrentState()));

	mHUD->registerEventHandlers(mApp->getGameWorldManager()->getEventManager());
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
	
	//Destroy HUD
	mHUD->destroy();
}

/// pause state
void GameRunningState::pause()
{
	//the following method is called to stop 
	//particle systems and other automatically animated
	//elements
	mApp->getRenderSubsystem()->pauseRendering();
}
/// resume state
void GameRunningState::resume()
{
	mApp->getRenderSubsystem()->resumeRendering();
}
void GameRunningState::handleEvents()
{
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
	}
	if (mApp->isPressedUseWeapon())
	{
		mApp->getGameWorldManager()->useWeapon();
	}
	else
	{
		mApp->getGameWorldManager()->stopUsingWeapon();
	}

			
	///////////////////////////////////////////////////////////
	// ONY (or first person camera): TYPE OF MOVEMENT
	//TODO: separate jump from movement?
	Vector2 nextMovementXZ=mApp->getMovement();

	Vector3 nextMovement;
	nextMovement.x=nextMovementXZ.x;
	nextMovement.y=0;
	nextMovement.z=nextMovementXZ.y;

	if (mApp->isPressedJump())
	{
		nextMovement+=Vector3::UNIT_Y;	
	}	

	if (mApp->isPressedWalk())
	{
		//TODO: this should be loaded from config
		nextMovement=nextMovement/2;	
	}

	if(mApp->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIRST_PERSON)
	{
		mApp->getCameraManager()->processSimpleTranslation(nextMovement);
	}
	else if(mApp->getCameraManager()->getActiveCameraControllerType()!=CAMERA_FIXED_FIRST_PERSON)
	{
		//Access to [0] because there's only one Ony, otherwise it should be a loop
		//rotate movement vector using the current camera direction
		nextMovement=mApp->getCameraManager()->rotateMovementVector(nextMovement);
		mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->setNextMovement(nextMovement);
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
			mApp->getTrajectoryManager()->toggleDebugMode();
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
			toggleVolumes();		
			mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		}
	}
}

void GameRunningState::update(long elapsedTime)
{
	double elapsedSeconds=(double)elapsedTime * 0.000001f;

	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTimeDebug = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);
	//Ogre::LogManager::getSingleton().logMessage("* Updating Game World Manager");

	//Ogre::LogManager::getSingleton().logMessage("* Updating Camera Params");

	//NOTE (Aniol) I CHANGED THE ORDER SO CAMERA UPDATES BEFORE GAMEWORLDMANAGER TO GET FLASHLIGHT VOLUME POSITION RIGHT
	mApp->getCameraManager()->update(elapsedSeconds);

	mApp->getGameWorldManager()->update(elapsedSeconds);	
	//Ogre::LogManager::getSingleton().logMessage("* Updating Physics Subsystem");
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);


	mApp->getLogicSubsystem()->update(elapsedSeconds);


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
		mHUD->update(elapsedTime,onyLogic->getHealthPoints(),onyLogic->getNumLives());
		if (mHUD->isSelectedModeChanged())
		{
			TWeaponMode newWeaponMode = convertRouletteValue(mHUD->getCurrentState());
			mHUD->setSelectedModeChanged(false);
			WeaponModeChangedEventPtr evt(new WeaponModeChangedEvent(newWeaponMode));
			mApp->getGameWorldManager()->addEvent(evt);
		}
	}
	mGUI->update(elapsedSeconds);
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

	TGameObjectTriggerBoxContainer cBox = mApp->getGameWorldManager()->getGameObjectTriggerBoxContainer();
	for(unsigned int i=0; i<cBox.size(); i++)
	{
		cBox[i]->changeVisibility();
	}

	TGameObjectTriggerCapsuleContainer cCapsule = mApp->getGameWorldManager()->getGameObjectTriggerCapsuleContainer();
	for(unsigned int i=0; i<cCapsule.size(); i++)
	{
		cCapsule[i]->changeVisibility();
	}
}
TWeaponMode GameRunningState::getCurrentWeaponMode()
{
	if (mHUD.get())
		return convertRouletteValue(mHUD->getCurrentState());
	return WEAPON_MODE_INVALID;
}