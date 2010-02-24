#include "MainMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../GUI/GUISubsystem.h"

#include "GameStateManager.h"
#include "GameRunningState.h"

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
	std::string mainMenuLayout;
	mApp->getGUISubsystem()->createGUI("ogregui.layout");
	//TODO: Refactor this to a container of connections, so
	//the cleanup function can disconnect a full batch of conns.
	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OgreGuiDemo/TabCtrl/Page1/QuitButton",
		CEGUI::Event::Subscriber(&MainMenuState::onQuit,this));
	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OgreGuiDemo/TabCtrl/Page1/NewButton",
		CEGUI::Event::Subscriber(&MainMenuState::onNew,this));
	//app->getConfiguration()->getOption(MAIN_MENU_LAYOUT,mainMenuLayout)
	//app->getGUISubsystem()->createGUI(mainMenuLayout));
	//app->getGUISubsystem()->bindEvents();

}

/// Clean up main menu's resources
void MainMenuState::cleanUp()
{
	mApp->getGUISubsystem()->destroyGUI();
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
bool MainMenuState::onQuit(const CEGUI::EventArgs& args)
{
	mApp->mExitRequested=true;
	return true;
}
bool MainMenuState::onNew(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new GameRunningState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}