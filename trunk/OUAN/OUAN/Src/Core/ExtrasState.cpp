#include "ExtrasState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
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
	mApp->getGUISubsystem()->createGUI("OUAN_ExtrasMenu.layout");
	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANExtras/Back",
		CEGUI::Event::Subscriber(&ExtrasState::onBackToMenu,this));
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
bool ExtrasState::onBackToMenu(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}