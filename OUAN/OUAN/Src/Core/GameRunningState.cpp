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

/// Initialise main menu's resources
void GameRunningState::init(ApplicationPtr app)
{
	mApp=app;	
	//TODO: Do this at proper location
	mApp->getGameWorldManager()->loadLevel("TestLevel.ogscene");
	mApp->mKeyBuffer=-1;

	mApp->getPhysicsSubsystem()->resetLevel();
	mApp->getPhysicsSubsystem()->initialiseLevel("TestLevel");
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
		mApp->mExitRequested=true;
	}
	if (mApp->isPressedToggleDebug() && mApp->mKeyBuffer<0)
	{
		if (mApp->getDebugMode()==DEBUGMODE_PHYSICS)
		{
			mApp->setDebugMode(DEBUGMODE_NONE);
			mApp->getRenderSubsystem()->hideDebugOverlay();
			mApp->getRenderSubsystem()->hideVisualDebugger();
		}
		else
		{
			mApp->setDebugMode(DEBUGMODE_PHYSICS);
			mApp->getRenderSubsystem()->showDebugOverlay();
			mApp->getRenderSubsystem()->showVisualDebugger();
		}
		mApp->mKeyBuffer = 500;
	}

	// TODO: Correct this checks so that they perform their supposed functions
	// i.e, move the player character, instead of translating the camera
	// At the moment they're just here so we can move around the scene in the initial
	// stages of development.
	if (mApp->isPressedGoForward())
	{
		mApp->getRenderSubsystem()->translateCamera(AXIS_NEG_Z); //For some reason, axis seem inverted :S
	}
	if (mApp->isPressedGoBack())
	{
		mApp->getRenderSubsystem()->translateCamera(AXIS_POS_Z);
	}
	if (mApp->isPressedGoLeft())
	{
		mApp->getRenderSubsystem()->translateCamera(AXIS_NEG_X);
	}
	if (mApp->isPressedGoRight())
	{
		mApp->getRenderSubsystem()->translateCamera(AXIS_POS_X);
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
	float xRel,yRel,zRel;	
	mApp->getMouseStateRelValues(&xRel,&yRel,&zRel);
	mApp->getRenderSubsystem()->moveCamera(xRel,yRel,zRel);
}

void GameRunningState::update(long elapsedTime)
{
	//mApp->getRenderSubsystem()->updateCameraParams((float)elapsedTime*0.001);
	
	float elapsedSeconds=elapsedTime*0.001f;
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