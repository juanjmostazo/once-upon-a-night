#include "MainMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../GUI/GUISubsystem.h"

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
	mApp->getGUISubsystem()->createGUI("OUAN_MainMenu.layout");

	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Quit",
		CEGUI::Event::Subscriber(&MainMenuState::onQuit,this));

	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Play",
		CEGUI::Event::Subscriber(&MainMenuState::onPlay,this));

	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Options",
		CEGUI::Event::Subscriber(&MainMenuState::onOptions,this));
	mApp->getGUISubsystem()->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANMainMenu/Extras",
		CEGUI::Event::Subscriber(&MainMenuState::onExtras,this));

}

/// Clean up main menu's resources
void MainMenuState::cleanUp()
{
	//Unsubscribe from events
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

bool MainMenuState::onQuit(const CEGUI::EventArgs& args)
{
	mApp->mExitRequested=true;
	return true;
}

bool MainMenuState::onPlay(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new GameRunningState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}

bool MainMenuState::onOptions(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new GameOptionsState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}
bool MainMenuState::onExtras(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new ExtrasState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}