#include "GameRunningState.h"

#include "GameStateManager.h"
#include "GameOverState.h"
#include "GamePausedState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/HUD/HUDInGame.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIConsole.h"
#include "../Logic/LogicSubsystem.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectOny.h"
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
	LogicComponentPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponent();
	mHUD->init(onyLogic->getHealthPoints(),onyLogic->getNumLives());
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
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
	if (mApp->isPressedQuickExit() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedQuickExit IN");
		mApp->mExitRequested=true;
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER; //0.5s
	}
	else if (mApp->isPressedPause() && mApp->mKeyBuffer<0)
	{
		GameStatePtr nextState(new GamePausedState());
		// Notice how pushState is called instead of changeState.
		// The reason to use push this time is to prevent unnecessary cleanup and initialisation, since
		// after the pause the application flow will come back to "GameRunning"
		mApp->getGameStateManager()->pushState(nextState,mApp);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER; //0.5s
	}
	else if(mApp->isPressedAutoPoint() && mApp->mKeyBuffer<0)
	{
		//GameOverEventPtr evt= GameOverEventPtr(new GameOverEvent(true));
		//mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
		//mGUI->hideConsole();
	}
	else if (mApp->isPressedToggleDebugPerformance() && mApp->mKeyBuffer<0)
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
		
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleDebugPhysics() && mApp->mKeyBuffer<0)
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

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeCamera() && mApp->mKeyBuffer<0)
	{
		Ogre::LogManager::getSingleton().logMessage("ToggleChangeCamera key pressed");

		mApp->getRenderSubsystem()->changeCamera();

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeCameraController() && mApp->mKeyBuffer<0)
	{
		Ogre::LogManager::getSingleton().logMessage("ToggleChangeCameraController key pressed");

		mApp->getRenderSubsystem()->changeCameraController();

		if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIXED_FIRST_PERSON)
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntity()->setVisible(false);
		}
		else
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntity()->setVisible(true);

		}
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeWorld() && mApp->mKeyBuffer<0)
	{
		Ogre::LogManager::getSingleton().logMessage("ToggleChangeWorld key pressed");

		mApp->getGameWorldManager()->changeWorld();

		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleChangeLevel() && mApp->mKeyBuffer<0)
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
		mApp->mKeyBuffer = DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedRotateLeft() && mApp->mKeyBuffer<0)
	{
		mHUD->spinRoulette(true);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedRotateRight() && mApp->mKeyBuffer<0)
	{
		mHUD->spinRoulette(false);
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleConsole() && mApp->mKeyBuffer<0)
	{
		Ogre::LogManager::getSingleton().logMessage("ToggleConsole key pressed");

		if (mGUI->isVisible())
			mGUI->hideConsole();
		else
			mGUI->showConsole();
		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
	}
	else if (mApp->isPressedToggleVolumes() && mApp->mKeyBuffer<0)
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

		mApp->mKeyBuffer=DEFAULT_KEY_BUFFER;
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

	if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIRST_PERSON)
	{
		mApp->getRenderSubsystem()->getCameraManager()->processSimpleTranslation(nextMovement);
	}
	else if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()!=CAMERA_FIXED_FIRST_PERSON)
	{
		//Access to [0] because there's only one Ony, otherwise it should be a loop
		//rotate movement vector using the current camera direction
		nextMovement=mApp->getRenderSubsystem()->getCameraManager()->rotateMovementVector(nextMovement);
		mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacter()->setNextMovement(nextMovement);
	}

	//[TODO: This will also have to be refactored somehow as soon as
	// a camera manager system has been implemented. 
	// The render subsystem shouldn't move cameras at this point: it will
	// all be managed internally from the body of a hypothetic CameraComponent
	// 
	// The main idea would be something like:
	// - Poll mouse/joystick right axis using the mApp methods inherited
	//   from ControlInputManager and retrieve the relative increments
	// - Then ask the gameWorldManager to update the current active camera accordingly,
	//	 or switch to the user-controlled camera mode and then update that one, whatever.
	//   The current active camera would be a GameObject using a CameraComponent.
	//]
	Vector2 cameraRotation;
	cameraRotation=mApp->getCameraRotation();
	mApp->getRenderSubsystem()->moveCamera(cameraRotation);
}

void GameRunningState::update(long elapsedTime)
{
	double elapsedSeconds=(double)elapsedTime * 0.000001f;

	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTimeDebug = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);

	//Ogre::LogManager::getSingleton().logMessage("* Updating Game World Manager");
	mApp->getGameWorldManager()->update(elapsedSeconds);	

	//Ogre::LogManager::getSingleton().logMessage("* Updating Physics Subsystem");
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);

	//Ogre::LogManager::getSingleton().logMessage("* Updating Camera Params");
	mApp->getRenderSubsystem()->updateCameraParams(elapsedSeconds);

	mApp->getLogicSubsystem()->update(elapsedSeconds);

	//TODO: update GameObjects if necessary after the logic update has updated their state.

	//Ogre::LogManager::getSingleton().logMessage("Other stuff");
	mApp->mKeyBuffer-=elapsedTime;

	if (mApp.get() && mApp->getGameWorldManager().get() && mApp->getGameWorldManager()->isGameOver())
	{
		mApp->getRenderSubsystem()->captureScene(SAVED_RTT_FILENAME);
		GameStatePtr nextState(new GameOverState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}
	LogicComponentPtr onyLogic = mApp->getGameWorldManager()->getGameObjectOny()->getLogicComponent();
	mHUD->update(elapsedTime,onyLogic->getHealthPoints(),onyLogic->getNumLives());
	mGUI->update(elapsedSeconds);
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
