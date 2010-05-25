#include "GamePausedState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"

using namespace OUAN;


/// Default constructor
GamePausedState::GamePausedState()
:GameState()
{

}
/// Destructor
GamePausedState::~GamePausedState()
{

}

/// init main menu's resources
void GamePausedState::init(ApplicationPtr app)
{
	mApp=app;	
	mApp->mKeyBuffer=-1;
}

/// Clean up main menu's resources
void GamePausedState::cleanUp()
{
	mApp->mKeyBuffer=-1;
}

/// pause state
void GamePausedState::pause()
{

}
/// resume state
void GamePausedState::resume()
{

}

/// process input events
/// @param app	the parent application
void GamePausedState::handleEvents()
{
	if (mApp && mApp->isPressedPause() && mApp->mKeyBuffer<0)
	{
		mApp->getRenderSubsystem()->hideOverlay(OVERLAY_PAUSE_SCREEN);
		mApp->mKeyBuffer=500000; //0.5s
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GamePausedState::update(long elapsedTime)
{
	if (mApp.get() && mApp->mKeyBuffer>=0)
		mApp->mKeyBuffer-=elapsedTime;
}
bool GamePausedState::render()
{
	if (mApp.get() && mApp->getRenderSubsystem().get())
	{
		mApp->getRenderSubsystem()->showOverlay(OVERLAY_PAUSE_SCREEN);
		return mApp->getRenderSubsystem()->render();
	}
	return false;
}
