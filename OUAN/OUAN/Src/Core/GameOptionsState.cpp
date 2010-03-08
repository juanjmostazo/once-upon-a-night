#include "GameOptionsState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"

#include "MainMenuState.h"

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
	using namespace CEGUI;
	mApp=app;		
	mApp->getGUISubsystem()->createGUI("OUAN_OptionsMenu.layout");
	mApp->getGUISubsystem()->bindEvent(PushButton::EventClicked,
		"OUANOptions/Back",
		CEGUI::Event::Subscriber(&GameOptionsState::onBackToMenu,this));
	//TODO for next revision: Refactor GUI initialization to its own OptionsMenuGUI Class
	TabControl* ctrl= (TabControl*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/TabCtrl");
	ctrl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/ControlsTab"));
	ctrl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/SoundTab"));
	ctrl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/GraphicsTab"));
	ctrl->setSelectedTab(0);
	Slider* slider = (Slider*) WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Sound/MasterSlider");
	slider->setMaxValue(100);
	slider->setCurrentValue(80);
	slider->setClickStep(10.0f);
	slider = (Slider*) WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Sound/SfxSlider");
	slider->setMaxValue(100);
	slider->setCurrentValue(80);
	slider->setClickStep(10.0f);
	slider = (Slider*) WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Sound/MusicSlider");
	slider->setMaxValue(100);
	slider->setCurrentValue(80);
	slider->setClickStep(10.0f);
}

/// Clean up main menu's resources
void GameOptionsState::cleanUp()
{
	//mApp->getGUISubsystem()->unbindAllEvents();
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

bool GameOptionsState::onBackToMenu(const CEGUI::EventArgs& args)
{
	GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);
	return true;
}