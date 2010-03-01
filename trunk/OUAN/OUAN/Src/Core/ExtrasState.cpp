#include "ExtrasState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "GameStateManager.h"

using namespace OUAN;


/// Default constructor
ExtrasState::ExtrasState()
:GameState()
{

}
/// Destructor
ExtrasState::~ExtrasState()
{

}

/// init main menu's resources
void ExtrasState::init(ApplicationPtr app)
{
	mApp=app;	
}

/// Clean up main menu's resources
void ExtrasState::cleanUp()
{
	mApp->getGUISubsystem()->destroyGUI();
}

/// pause state
void ExtrasState::pause()
{

}
/// resume state
void ExtrasState::resume()
{

}

/// process input events
/// @param app	the parent application
void ExtrasState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void ExtrasState::update(long elapsedTime)
{

}
