#include "ExtrasState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIExtrasMenu.h"
#include "GameStateManager.h"

#include "MainMenuState.h"

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
	mGUI=boost::dynamic_pointer_cast<GUIExtrasMenu>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_EXTRAS));
	mGUI->initGUI(shared_from_this());
}

/// Clean up main menu's resources
void ExtrasState::cleanUp()
{
	mGUI->destroy();
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
void ExtrasState::backToMenu()
{
	GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}