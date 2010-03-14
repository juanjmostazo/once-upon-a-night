#include "MainMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIMainMenu.h"
#include "GameStateManager.h"
#include "GameRunningState.h"
#include "GameOptionsState.h"
#include "ExtrasState.h"

using namespace OUAN;


/// Default constructor
MainMenuState::MainMenuState()
:GameState()
{

}
/// Destructor
MainMenuState::~MainMenuState()
{

}

/// init main menu's resources
void MainMenuState::init(ApplicationPtr app)
{
	mApp=app;	
	//mApp->getGUISubsystem()->loadScheme("OUANLookSkin.scheme","OUANLook");
	mGUI= boost::dynamic_pointer_cast<GUIMainMenu>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_MAINMENU));
	mGUI->initGUI(shared_from_this());
}

/// Clean up main menu's resources
void MainMenuState::cleanUp()
{
	//Unsubscribe from events
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	//mApp->getGUISubsystem()->unbindAllEvents();
}

/// pause state
void MainMenuState::pause()
{

}
/// resume state
void MainMenuState::resume()
{

}

/// process input events
/// @param app	the parent application
void MainMenuState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void MainMenuState::update(long elapsedTime)
{

}
void MainMenuState::gotoPlay()
{
	//TODO: Change to ProfileSelectState when it's implemented
	GameStatePtr nextState(new GameRunningState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}
void MainMenuState::gotoOptions()
{
	GameStatePtr nextState(new GameOptionsState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}
void MainMenuState::gotoExtras()
{
	GameStatePtr nextState(new ExtrasState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
}
void MainMenuState::quit()
{
	mApp->mExitRequested=true;
}
