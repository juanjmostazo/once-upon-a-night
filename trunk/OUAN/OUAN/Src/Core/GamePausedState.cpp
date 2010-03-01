#include "GamePausedState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
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
}

/// Clean up main menu's resources
void GamePausedState::cleanUp()
{
	mApp->getGUISubsystem()->destroyGUI();
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

}

/// Update game according to the current state
/// @param app	the parent app
void GamePausedState::update(long elapsedTime)
{

}
