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
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		"OUANOptions/Controls/ForwardBtn",
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
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

	
	Combobox* combo=(Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Controls/DeviceSelect");
	ListboxTextItem* lti = new ListboxTextItem("Mouse 'n' Keyboard",0,(void*)DEVICE_KEYB_MOUSE);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	lti= new ListboxTextItem("Psx pad",1,(void*)DEVICE_PAD_PSX);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
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
bool GameOptionsState::onRadioButtonStateChange(const CEGUI::EventArgs& args)
{
	const CEGUI::WindowEventArgs& evtArgs = static_cast<const CEGUI::WindowEventArgs&> (args);
	CEGUI::RadioButton*changedWindow =static_cast<CEGUI::RadioButton*>(evtArgs.window);
	if (changedWindow)
	{		
		if (changedWindow->isSelected())
		{
			mExpectingPress=true;
			mCurrentlyEditedMapping=std::string(changedWindow->getName().c_str());
		}
		else // if the event triggers only when one is deselected, not when by selecting an item the rest trigger the event as well
		{
			mExpectingPress=false;
		}
	}
	return true;
}
bool GameOptionsState::keyPressed( const OIS::KeyEvent& e )
{
	if (mExpectingPress)
	{
		//OIS::KeyCode kc=e.key;
		//std::string kc=e.text;
		//inputConfig->setNewMapping(mCurrentlyEditedDevice,mCurrentlyEditedMapping,key);
		//GetWindow(mCurrentlyEditedMapping)->setText("..."+" "+text);
		//mCurrentlyEditedMapping="";
		//mExpectingPress=false;
		//setSelected(mCurrentlyEditedMapping)=false;
	}	
	return true;
}