#include "GameRunningState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../Game/GameWorldManager.h"

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
	//TODO: Do this at proper location
	mApp->getGameWorldManager()->loadLevel("TestLevel.ogscene");
	mApp->mKeyBuffer=-1;

	mApp->getPhysicsSubsystem()->resetLevel();
	mApp->getPhysicsSubsystem()->initLevel("TestLevel");
}

/// Clean up main menu's resources
void GameRunningState::cleanUp()
{
	mApp->mKeyBuffer=-1;
}

/// pause state
void GameRunningState::pause()
{

}
/// resume state
void GameRunningState::resume()
{

}

void GameRunningState::handleEvents()
{
	if (mApp->isPressedQuickExit())
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedQuickExit IN");
		mApp->mExitRequested=true;
	}
	else if (mApp->isPressedToggleDebugPerformance() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPerformance IN");
		if (mApp->getDebugMode()!=DEBUGMODE_PERFORMANCE)
		{
			mApp->setDebugMode(DEBUGMODE_PERFORMANCE);
			mApp->getRenderSubsystem()->hideVisualDebugger();
			mApp->getRenderSubsystem()->showDebugOverlay();
		}
		else
		{
			mApp->setDebugMode(DEBUGMODE_NONE);
			mApp->getRenderSubsystem()->hideDebugOverlay();
		}
		
		mApp->mKeyBuffer = 500000;
	}
	else if (mApp->isPressedToggleDebugPhysics() && mApp->mKeyBuffer<0)
	{
		//Ogre::LogManager::getSingleton().logMessage("isPressedToggleDebugPhysics IN");
		if (mApp->getDebugMode()!=DEBUGMODE_PHYSICS)
		{
			mApp->setDebugMode(DEBUGMODE_PHYSICS);
			mApp->getRenderSubsystem()->showDebugOverlay();
			mApp->getRenderSubsystem()->showVisualDebugger();
		}
		else 
		{
			mApp->setDebugMode(DEBUGMODE_NONE);
			mApp->getRenderSubsystem()->hideDebugOverlay();
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

		mApp->mKeyBuffer = 500000;
	}
	// TODO: Correct this checks so that they perform their supposed functions
	// i.e, move the player character, instead of translating the camera
	// At the moment they're just here so we can move around the scene in the initial
	// stages of development.
	if (mApp->isPressedGoForward())
	{
		//mApp->getRenderSubsystem()->translateCamera(AXIS_NEG_Z); //For some reason, axis seem inverted :S
	}
	if (mApp->isPressedGoBack())
	{
		//mApp->getRenderSubsystem()->translateCamera(AXIS_POS_Z);
	}
	if (mApp->isPressedGoLeft())
	{
		//mApp->getRenderSubsystem()->translateCamera(AXIS_NEG_X);
	}
	if (mApp->isPressedGoRight())
	{
		//mApp->getRenderSubsystem()->translateCamera(AXIS_POS_X);
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
	mApp->getRenderSubsystem()->updateCameraParams((double)elapsedTime*0.000001);
	
	double elapsedSeconds=elapsedTime*0.000001f;
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);
	mApp->mKeyBuffer-=elapsedTime;
}

bool GameRunningState::render()
{
	RenderSubsystemPtr renderSubsystem=mApp->getRenderSubsystem();
	if (mApp->getDebugMode()!=DEBUGMODE_NONE)
	{
		renderSubsystem->updateStats();
		renderSubsystem->updateDebugInfo();
		renderSubsystem->showDebugOverlay();
	}

	renderSubsystem->updateVisualDebugger();
	renderSubsystem->showHUD();
	return renderSubsystem->render();
}