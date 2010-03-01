#include "GameOptionsState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "GameStateManager.h"

using namespace OUAN;


/// Default constructor
GameOptionsState::GameOptionsState()
:GameState()
{

}
/// Destructor
GameOptionsState::~GameOptionsState()
{

}

/// init main menu's resources
void GameOptionsState::init(ApplicationPtr app)
{
	mApp=app;	
}

/// Clean up main menu's resources
void GameOptionsState::cleanUp()
{
	mApp->getGUISubsystem()->destroyGUI();
}

/// pause state
void GameOptionsState::pause()
{

}
/// resume state
void GameOptionsState::resume()
{

}

/// process input events
/// @param app	the parent application
void GameOptionsState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void GameOptionsState::update(long elapsedTime)
{

}
