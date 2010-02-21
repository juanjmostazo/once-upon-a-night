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

/// process input events
/// @param app	the parent application
void GameRunningState::handleEvents()
{

}

void GameRunningState::update(long elapsedTime)
{

	mApp->getRenderSubsystem()->updateCameraParams((float)elapsedTime*0.001);
	mApp->getRenderSubsystem()->relativeMoveCam();

	float elapsedSeconds=elapsedTime*0.001f;
	mApp->getPhysicsSubsystem()->update(elapsedSeconds);
	mApp->mKeyBuffer-=elapsedTime;

}

bool GameRunningState::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
		mApp->mExitRequested= true;
	
	if (e.key == OIS::KC_G && mApp->mKeyBuffer<0)
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
	return true;
}
bool GameRunningState::mouseMoved(const OIS::MouseEvent &e)
{
	mApp->getRenderSubsystem()->moveCamera(e);
	return true;
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