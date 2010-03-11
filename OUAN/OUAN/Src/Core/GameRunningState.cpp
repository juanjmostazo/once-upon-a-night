#include "GameRunningState.h"

#include "GameStateManager.h"
#include "GameOverState.h"
#include "GamePausedState.h"

#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../GUI/GUISubsystem.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectOny.h"

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
	mApp->getPhysicsSubsystem()->initLevel(LEVEL_TEST);
	// Set the initial world before the level loading, and then
	// just as game objects are created, they're initialized with the correct
	// world information.
	mApp->getGameWorldManager()->setWorld(DREAMS);
	mApp->getGameWorldManager()->loadLevel(LEVEL_TEST);
	
	mApp->mKeyBuffer=-1;
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_INGAME_HUD);
	mApp->getRenderSubsystem()->hideOverlay(OVERLAY_DEBUG_PANEL);
	mApp->getGameWorldManager()->unloadLevel();
	mApp->getGUISubsystem()->cleanUp();
	mApp->getPhysicsSubsystem()->resetLevel();
	mApp->getRenderSubsystem()->resetScene();
	mApp->getGUISubsystem()->init(mApp);
	mApp->mKeyBuffer=-1;
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
		mApp->mKeyBuffer=500000; //0.5s
	}
	else if (mApp->isPressedPause() && mApp->mKeyBuffer<0)
	{
		GameStatePtr nextState(new GamePausedState());
		// Notice how pushState is called instead of changeState.
		// The reason to use push this time is to prevent unnecessary cleanup and initialisation, since
		// after the pause the application flow will come back to "GameRunning"
		mApp->getGameStateManager()->pushState(nextState,mApp);
		mApp->mKeyBuffer=500000; //0.5s
	}
	//TODO: REMOVE THIS STATEMENT when we can respond to a collision and simulate
	// a gameOver event
	else if(mApp->isPressedAutoPoint() && mApp->mKeyBuffer<0)
	{
		mApp->getGameWorldManager()->setGameOver(true);
		mApp->mKeyBuffer=500000;
	}
	else if (mApp->isPressedToggleDebugPerformance() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPerformance IN");
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
		
		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleDebugPhysics() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPhysics IN");
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

		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleChangeCamera() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->changeCamera();

		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleChangeCameraController() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->changeCameraController();

		if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIXED_FIRST_PERSON)
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityDreams()->setVisible(false);
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityNightmares()->setVisible(false);
		}
		else
		{
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityDreams()->setVisible(true);
			mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentEntityNightmares()->setVisible(true);

		}
		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleChangeWorld() && mApp->mKeyBuffer<0)
	{
		mApp->getGameWorldManager()->changeWorld();

		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleChangeLevel() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleChangeLevel IN");
		if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_TEST)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_SANDBOX);
		}
		else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_SANDBOX)==0)
		{
			mApp->getGameWorldManager()->loadLevel(LEVEL_CLOCK);
		}
		else if(mApp->getGameWorldManager()->getCurrentLevel().compare(LEVEL_CLOCK)==0)
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
		mApp->mKeyBuffer = 500000;
	}
		
	///////////////////////////////////////////////////////////
	// ONY (or first person camera): TYPE OF MOVEMENT
	int movementFlags = 0;
	if (mApp->isPressedGoForward())
	{
		movementFlags |= MOV_GO_FORWARD;	
	}

	if (mApp->isPressedGoBack())
	{
		movementFlags |= MOV_GO_BACK;
	}

	if (mApp->isPressedGoLeft())
	{
		movementFlags |= MOV_GO_LEFT;
	}

	if (mApp->isPressedGoRight())
	{
		movementFlags |= MOV_GO_RIGHT;
	}

	if (mApp->isPressedJump())
	{
		movementFlags |= MOV_JUMP;
	}

	if (mApp->isPressedWalk())
	{
		movementFlags |= MOV_WALK;
	}

	if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()==CAMERA_FIRST_PERSON)
	{
		mApp->getRenderSubsystem()->getCameraManager()->processSimpleTranslation(movementFlags);
	}
	else if(mApp->getRenderSubsystem()->getCameraManager()->getActiveCameraControllerType()!=CAMERA_FIXED_FIRST_PERSON)
	{
		//Access to [0] because there's only one Ony, otherwise it should be a loop
		mApp->getGameWorldManager()->getGameObjectOny()->setMovementFlags(movementFlags);
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
	double xRel,yRel,zRel;	
	mApp->getMouseStateRelValues(&xRel,&yRel,&zRel);
	mApp->getRenderSubsystem()->moveCamera(xRel,yRel,zRel);
}

void GameRunningState::update(long elapsedTime)
{
	double elapsedSeconds=(double)elapsedTime * 0.000001f;

	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTimeDebug = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);

	//Ogre::LogManager::getSingleton().logMessage("Updating Game World Manager");
	mApp->getGameWorldManager()->update(elapsedSeconds);	

	//Ogre::LogManager::getSingleton().logMessage("Updating Physics Subsystem");
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);

	//Ogre::LogManager::getSingleton().logMessage("Updating Camera Params");
	mApp->getRenderSubsystem()->updateCameraParams(elapsedSeconds);
	
	//Ogre::LogManager::getSingleton().logMessage("Other stuff");
	mApp->mKeyBuffer-=elapsedTime;

	if (mApp.get() && mApp->getGameWorldManager().get() && mApp->getGameWorldManager()->isGameOver())
	{
		mApp->getRenderSubsystem()->captureScene(SAVED_RTT_FILENAME);
		GameStatePtr nextState(new GameOverState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
	}
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
	renderSubsystem->showOverlay(OVERLAY_INGAME_HUD);
	
	return renderSubsystem->render();
}