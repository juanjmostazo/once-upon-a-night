#include "GameOptionsState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"

#include "MainMenuState.h"
#include <sstream>

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
	mButtonTextStrings.reset(new Configuration());
	mButtonTextStrings->loadFromFile(MENUSTRINGS_CFG);

	using namespace CEGUI;
	mApp=app;		
	mApp->getGUISubsystem()->createGUI("OUAN_OptionsMenu.layout");
	bindEvents();
	
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
	ListboxTextItem* lti = new ListboxTextItem("Mouse 'n' Keyboard",0);
	lti->setSelected(true);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	lti= new ListboxTextItem("Psx pad",1);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);

	mApp->getInputMappings(mCurrentConfig);
	mNewConfig=mCurrentConfig;
	mCurrentlyEditedDevice=DEVICE_KEYB_MOUSE;
	mCurrentlyEditedMapping="";

	initTextButtons();
}

/// Clean up main menu's resources
void GameOptionsState::cleanUp()
{
	//mApp->getGUISubsystem()->unbindAllEvents();
	mApp->getGUISubsystem()->destroyGUI();
	mButtonTextStrings.reset();
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
	if (mExpectingPress && mCurrentlyEditedDevice== DEVICE_KEYB_MOUSE && !mCurrentlyEditedMapping.empty())
	{
		OIS::KeyCode kc=e.key;
		if (!mappingAlreadyFound(kc))
		{
			std::ostringstream stream;
			//inputConfig->setNewMapping(mCurrentlyEditedDevice,mCurrentlyEditedMapping,key);
			CEGUI::RadioButton* radio=(CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(mCurrentlyEditedMapping);
			stream.str("");
			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mApp->getAsString(kc);
			radio->setText((CEGUI::utf8*)stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].first=(int)e.key;

			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			radio->setSelected(false);
		}

	}	
	return true;
}
void GameOptionsState::initTextButtons()
{
	mButtonData.clear();
	initButton(BUTTON_NAME_FORWARD,BUTTON_TEXT_FORWARD,KEY_FORWARD,mButtonData);
	initButton(BUTTON_NAME_BACKWARDS,BUTTON_TEXT_BACKWARDS,KEY_BACKWARDS,mButtonData);
	initButton(BUTTON_NAME_LEFT,BUTTON_TEXT_LEFT,KEY_LEFT,mButtonData);
	initButton(BUTTON_NAME_RIGHT,BUTTON_TEXT_RIGHT,KEY_RIGHT,mButtonData);

	initButton(BUTTON_NAME_JUMP,BUTTON_TEXT_JUMP,KEY_JUMP,mButtonData);
	initButton(BUTTON_NAME_ACTION,BUTTON_TEXT_ACTION,KEY_ACTION,mButtonData);
	initButton(BUTTON_NAME_RELOAD,BUTTON_TEXT_RELOAD,KEY_RELOADWEAPON,mButtonData);
	initButton(BUTTON_NAME_USEWEAPON,BUTTON_TEXT_USEWEAPON,KEY_USEWEAPON,mButtonData);

	initButton(BUTTON_NAME_LROTATE,BUTTON_TEXT_LROTATE,KEY_ROTATELEFT,mButtonData);
	initButton(BUTTON_NAME_RROTATE,BUTTON_TEXT_RROTATE,KEY_ROTATERIGHT,mButtonData);
	initButton(BUTTON_NAME_WALK,BUTTON_TEXT_WALK,KEY_WALK,mButtonData);
	initButton(BUTTON_NAME_AUTOTARGET,BUTTON_TEXT_AUTOTARGET,KEY_AUTOTARGET,mButtonData);

	initButton(BUTTON_NAME_PAUSE,BUTTON_TEXT_PAUSE,KEY_PAUSE,mButtonData);
	initButton(BUTTON_NAME_MENU,BUTTON_TEXT_INGAME_MENU,KEY_MENU,mButtonData);	
}
void GameOptionsState::bindEvents()
{
	using namespace CEGUI;
	mApp->getGUISubsystem()->bindEvent(PushButton::EventClicked,
		"OUANOptions/Back",
		CEGUI::Event::Subscriber(&GameOptionsState::onBackToMenu,this));
	mApp->getGUISubsystem()->bindEvent(PushButton::EventClicked,
		"OUANOptions/Controls/Apply",
		CEGUI::Event::Subscriber(&GameOptionsState::onApply,this));
	mApp->getGUISubsystem()->bindEvent(PushButton::EventClicked,
		"OUANOptions/Controls/Cancel",
		CEGUI::Event::Subscriber(&GameOptionsState::onCancel,this));
	mApp->getGUISubsystem()->bindEvent(Combobox::EventListSelectionAccepted,
		"OUANOptions/Controls/DeviceSelect",
		CEGUI::Event::Subscriber(&GameOptionsState::onDeviceSelectionChanged,this));

	mApp->getGUISubsystem()->bindEvent(RadioButton::EventMouseButtonDown,
		BUTTON_NAME_FORWARD,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonDown,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_FORWARD,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));

	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_BACKWARDS,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_LEFT,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RIGHT,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_JUMP,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_ACTION,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_USEWEAPON,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RELOAD,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_LROTATE,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RROTATE,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_WALK,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_AUTOTARGET,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_PAUSE,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
	mApp->getGUISubsystem()->bindEvent(RadioButton::EventSelectStateChanged,
		BUTTON_NAME_MENU,
		CEGUI::Event::Subscriber(&GameOptionsState::onRadioButtonStateChange,this));
}
bool GameOptionsState::onApply (const CEGUI::EventArgs& args)
{
	if (mApp)
	{
		mApp->replaceConfig(mNewConfig,true);
		mCurrentConfig=mNewConfig;
		return true;
	}
	return false;
}
bool GameOptionsState::onCancel (const CEGUI::EventArgs& args)
{
	mNewConfig=mCurrentConfig;
	mExpectingPress=false;
	mCurrentlyEditedMapping="";
	mCurrentlyEditedDevice=DEVICE_KEYB_MOUSE;
	initTextButtons();
	CEGUI::Combobox* combo=(CEGUI::Combobox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Controls/DeviceSelect");
	combo->clearAllSelections();
	combo->getListboxItemFromIndex(0)->setSelected(true);
	return true;
}
bool GameOptionsState::onDeviceSelectionChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Combobox* combo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingletonPtr()->
		getWindow((CEGUI::utf8*)"OUANOptions/Controls/DeviceSelect"));
	if (combo)
	{		
		CEGUI::ListboxItem* selection = static_cast<CEGUI::ListboxItem*>(combo->getSelectedItem());
		if (selection)
		mCurrentlyEditedDevice=static_cast<TInputDevice>(selection->getID());
		return true;
	}
	return false;
}
void GameOptionsState::initButton(const std::string& buttonName, const std::string& buttonText, 
								  const std::string& mappingName, TButtonDataMapping& buttonData)
{
	std::ostringstream stream;
	stream.str("");
	CEGUI::RadioButton* radio = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(buttonName);
	mButtonTextStrings->getOption(buttonText,mButtonData[buttonName].buttonText);
	mButtonData[buttonName].keyMapping=mappingName;
	stream.str("");
	std::string keyName=(mCurrentConfig[mappingName].first<0)
		?mApp->getMouseButtonName(mCurrentConfig[mappingName].first)
		:mApp->getAsString(static_cast<OIS::KeyCode>(mCurrentConfig[mappingName].first));
	stream<<mButtonData[buttonName].buttonText<<' '<<keyName;
	radio->setText((CEGUI::utf8*)stream.str().c_str());		
}
bool GameOptionsState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (mExpectingPress && mCurrentlyEditedDevice== DEVICE_KEYB_MOUSE && !mCurrentlyEditedMapping.empty())
	{
		TInputCfgMouseButtonMapper buttonPressed =mApp->convertMouseButtonId(id);
		if (!mappingAlreadyFound(buttonPressed))
		{
			std::ostringstream stream;
			//inputConfig->setNewMapping(mCurrentlyEditedDevice,mCurrentlyEditedMapping,key);
			CEGUI::RadioButton* radio=(CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(mCurrentlyEditedMapping);
			stream.str("");
			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mApp->getMouseButtonName(buttonPressed);
			radio->setText((CEGUI::utf8*)stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].first=(int)buttonPressed;

			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			radio->setSelected(false);
		}
	}	
	return true;
}
bool GameOptionsState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return false;
}
bool GameOptionsState::onRadioButtonDown(const CEGUI::EventArgs& args)
{
	const CEGUI::MouseEventArgs& evtArgs = static_cast<const CEGUI::MouseEventArgs&> (args);
	CEGUI::MouseButton pressedButton=evtArgs.button;
	CEGUI::RadioButton*changedWindow =static_cast<CEGUI::RadioButton*>(evtArgs.window);
	if (changedWindow)
	{		
		if (changedWindow->isSelected())
		{
			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			changedWindow->setSelected(false);
		}
	}
	return true;
}
bool GameOptionsState::mappingAlreadyFound(int code)
{
	TControlInputMapping::iterator it=mNewConfig.begin();
	bool found=false;
	while (it!=mNewConfig.end() && !found)
	{
		if (mCurrentlyEditedDevice==DEVICE_KEYB_MOUSE)
			found=(it->second.first==code);
		else if (mCurrentlyEditedDevice==DEVICE_PAD_PSX)
			found=(it->second.second==code);
		if (!found) ++it;
	}
	return found;
}