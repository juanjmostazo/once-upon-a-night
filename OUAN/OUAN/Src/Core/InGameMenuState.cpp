#include "InGameMenuState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "GameStateManager.h"

using namespace OUAN;


/// Default constructor
InGameMenuState::InGameMenuState()
:GameState()
{

}
/// Destructor
InGameMenuState::~InGameMenuState()
{

}

/// init main menu's resources
void InGameMenuState::init(ApplicationPtr app)
{
	mApp=app;	
}

/// Clean up main menu's resources
void InGameMenuState::cleanUp()
{
	mApp->getGUISubsystem()->destroyGUI();
}

/// pause state
void InGameMenuState::pause()
{

}
/// resume state
void InGameMenuState::resume()
{

}

/// process input events
/// @param app	the parent application
void InGameMenuState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void InGameMenuState::update(long elapsedTime)
{

}
