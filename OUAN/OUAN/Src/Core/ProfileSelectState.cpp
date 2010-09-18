#include "OUAN_Precompiled.h"

#include "ProfileSelectState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "GameStateManager.h"
#include "GameRunningState.h"

using namespace OUAN;


/// Default constructor
ProfileSelectState::ProfileSelectState()
:GameState()
{

}
/// Destructor
ProfileSelectState::~ProfileSelectState()
{

}

GameStateType ProfileSelectState::getGameStateType()
{
	return GAME_STATE_PROFILE_SELECT;
}

/// init main menu's resources
void ProfileSelectState::init(ApplicationPtr app)
{
	GameState::init(app);
}

/// Clean up main menu's resources
void ProfileSelectState::cleanUp()
{
	GameState::cleanUp();
	mApp->getGUISubsystem()->destroyGUI();
}

/// pause state
void ProfileSelectState::pause()
{

}
/// resume state
void ProfileSelectState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void ProfileSelectState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void ProfileSelectState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
}
