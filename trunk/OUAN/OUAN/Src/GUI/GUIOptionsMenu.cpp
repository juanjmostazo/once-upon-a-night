#include "OUAN_Precompiled.h"

#include "GUIOptionsMenu.h"
#include "GUISubsystem.h"
#include "../Application.h"
#include "../Core/GameOptionsState.h"
using namespace OUAN;

void GUIOptionsMenu::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	mParentGameState->getApp()->getInputMappings(mCurrentConfig);
	mNewConfig=mCurrentConfig;
	mButtonTextStrings.reset(new Configuration());
	mButtonTextStrings->loadFromFile(MENUSTRINGS);
	bindEvents();
	mCurrentlyEditedDevice=DEVICE_KEYB_MOUSE;
	mCurrentlyEditedMapping="";
	initTabs();
	initControlsTab();
	mParentGameState->getApp()->getAudioConfig(mCurrentAudioConfig);
	mNewAudioConfig=mCurrentAudioConfig;
	initSoundTab();
	initGraphicsTab();

}
void GUIOptionsMenu::initTabs()
{
	using namespace CEGUI;
	TabControl* optionsControl	= (TabControl*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/TabCtrl");
	if (optionsControl)
	{
		optionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/ControlsTab"));
		optionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/SoundTab"));
		optionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/GraphicsTab"));
		optionsControl->setSelectedTab(0);
	}
}
void GUIOptionsMenu::initControlsTab()
{
	using namespace CEGUI;
	CEGUI::Combobox* combo=(CEGUI::Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Controls/DeviceSelect");
	std::string itemName="";
	mButtonTextStrings->getOption(COMBO_ITEM_DEVICE_MOUSEKEYBOARD,itemName);
	ListboxTextItem* lti = new ListboxTextItem(itemName,0);
	lti->setSelected(true);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	mButtonTextStrings->getOption(COMBO_ITEM_DEVICE_PSXPAD,itemName);
	lti= new ListboxTextItem(itemName,1);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);

	initTextButtons();
}
void GUIOptionsMenu::initSoundTab()
{
	initVolumeSlider(SLIDER_NAME_MASTER,100,(float)mCurrentAudioConfig.mMasterVolume*100,10.0);
	initVolumeSlider(SLIDER_NAME_SFX,100,(float)mCurrentAudioConfig.mSfxVolume*100.0f,10.0);
	initVolumeSlider(SLIDER_NAME_MUSIC,100,(float)mCurrentAudioConfig.mMusicVolume*100.0f,10.0);
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_MASTER.c_str());
	if (check)
	{
		check->setSelected(mCurrentAudioConfig.mMasterVolumeEnabled);
	}
	check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_MUSIC.c_str());
	if (check)
	{
		check->setSelected(mCurrentAudioConfig.mMusicVolumeEnabled);
	}
	check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_SFX.c_str());
	if (check)
	{
		check->setSelected(mCurrentAudioConfig.mSfxVolumeEnabled);
	}
}
void GUIOptionsMenu::initGraphicsTab()
{

}
void GUIOptionsMenu::initVolumeSlider(const std::string& windowName, float maxValue, float defaultValue, float clickStep)
{
	CEGUI::Slider* slider = (CEGUI::Slider*) CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)windowName.c_str());
	if (slider)
	{
		slider->setMaxValue(maxValue);
		slider->setCurrentValue(defaultValue);
		slider->setClickStep(clickStep);
	}
}
void GUIOptionsMenu::bindEvents()
{
	GUISubsystemPtr guiSS= mParentGameState->getApp()->getGUISubsystem();
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Back",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onBackToMenu,this));
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Controls/Apply",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onApply,this));
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Controls/Cancel",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onCancel,this));
	guiSS->bindEvent(CEGUI::Combobox::EventListSelectionAccepted,
		"OUANOptions/Controls/DeviceSelect",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onDeviceSelectionChanged,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventMouseButtonDown,
		BUTTON_NAME_FORWARD,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonDown,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_FORWARD,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));

	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_BACKWARDS,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_LEFT,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RIGHT,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_JUMP,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_ACTION,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_USEWEAPON,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RELOAD,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_LROTATE,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RROTATE,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_WALK,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_AUTOTARGET,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_PAUSE,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_MENU,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));

	//Audio:
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Sound/Apply",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onApplySound,this));
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Sound/Cancel",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onCancelSound,this));
	guiSS->bindEvent(CEGUI::Slider::EventValueChanged,
		SLIDER_NAME_MASTER,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMasterSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Slider::EventThumbTrackEnded,
		SLIDER_NAME_MASTER,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMasterSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Slider::EventValueChanged,
		SLIDER_NAME_MUSIC,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMusicSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Slider::EventThumbTrackEnded,
		SLIDER_NAME_SFX,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMusicSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Slider::EventValueChanged,
		SLIDER_NAME_SFX,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onSfxSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Slider::EventThumbTrackEnded,
		SLIDER_NAME_SFX,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onSfxSliderValueChanged,this));
	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		CHECKBOX_NAME_SFX,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onSfxCheckBoxStateChanged,this));
	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		CHECKBOX_NAME_MUSIC,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMusicCheckBoxStateChanged,this));
	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		CHECKBOX_NAME_MASTER,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onMasterCheckBoxStateChanged,this));

}
void GUIOptionsMenu::initTextButtons()
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
void GUIOptionsMenu::initButton(const std::string& buttonName, const std::string& buttonText, const std::string& mappingName, TButtonDataMapping& buttonData)
{
	std::ostringstream stream;
	stream.str("");
	CEGUI::RadioButton* radio = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(buttonName);
	mButtonTextStrings->getOption(buttonText,mButtonData[buttonName].buttonText);
	mButtonData[buttonName].keyMapping=mappingName;
	stream.str("");
	std::string keyName;
	if (mCurrentlyEditedDevice==DEVICE_KEYB_MOUSE)
		keyName=(mCurrentConfig[mappingName].first<0)
		?mParentGameState->getApp()->getMouseButtonName(mCurrentConfig[mappingName].first)
		:mParentGameState->getApp()->getAsString(static_cast<OIS::KeyCode>(mCurrentConfig[mappingName].first));
	else
		keyName=mParentGameState->getApp()->getPadButtonName(mCurrentConfig[mappingName].second);

	stream<<mButtonData[buttonName].buttonText<<' '<<keyName;
	radio->setText((CEGUI::utf8*)stream.str().c_str());		
}
void GUIOptionsMenu::destroy()
{
	GUIWindow::destroy();
	mButtonTextStrings.reset();
}
bool GUIOptionsMenu::onApply (const CEGUI::EventArgs& args)
{
	if (mParentGameState)
	{
		mParentGameState->getApp()->replaceConfig(mNewConfig,true);
		mCurrentConfig=mNewConfig;
		
		return true;
	}
	return false;
}
bool GUIOptionsMenu::onApplySound(const CEGUI::EventArgs& args )
{
	if (mParentGameState)
	{
		mParentGameState->getApp()->saveAudioConfig(mNewAudioConfig);
		mCurrentAudioConfig=mNewAudioConfig;
		return true;
	}
	return false;
}
bool GUIOptionsMenu::onCancelSound(const CEGUI::EventArgs& args )
{
	mNewAudioConfig=mCurrentAudioConfig;
	//update state
	mParentGameState->getApp()->setAudioConfig(mCurrentAudioConfig);
	initSoundTab();
	return false;
}
bool GUIOptionsMenu::onCancel (const CEGUI::EventArgs& args)
{
	mNewConfig=mCurrentConfig;
	mExpectingPress=false;
	mCurrentlyEditedMapping="";
	mCurrentlyEditedDevice=DEVICE_KEYB_MOUSE;
	initTextButtons();
	CEGUI::Combobox* combo=(CEGUI::Combobox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Controls/DeviceSelect");
	combo->clearAllSelections();
	combo->setItemSelectState((size_t)0,true);
	combo->setText(combo->getSelectedItem()->getText());
	return true;
}
bool GUIOptionsMenu::onDeviceSelectionChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Combobox* combo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingletonPtr()->
		getWindow((CEGUI::utf8*)"OUANOptions/Controls/DeviceSelect"));
	if (combo)
	{		
		CEGUI::ListboxItem* selection = static_cast<CEGUI::ListboxItem*>(combo->getSelectedItem());
		if (selection)
			mCurrentlyEditedDevice=static_cast<TInputDevice>(selection->getID());
		mExpectingPress=false;
		mCurrentlyEditedMapping="";
		initTextButtons();
		return true;
	}
	return false;
}
bool GUIOptionsMenu::onBackToMenu(const CEGUI::EventArgs& args)
{
	(static_cast<GameOptionsState*>(mParentGameState.get()))->backToMenu();
	return true;
}
bool GUIOptionsMenu::onRadioButtonStateChange(const CEGUI::EventArgs& args)
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
bool GUIOptionsMenu::onMasterSliderValueChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Slider* slider = (CEGUI::Slider*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)SLIDER_NAME_MASTER.c_str());
	if (slider)
	{		
		mNewAudioConfig.mMasterVolume=slider->getCurrentValue()/100;
		mParentGameState->getApp()->modifyVolume(SM_CHANNEL_MASTER_GROUP,mNewAudioConfig.mMasterVolume);
	}
	return true;
}
//bool GUIOptionsMenu::onMasterSliderValueStopped(const CEGUI::EventArgs& args)
//{
//	CEGUI::Slider* slider = (CEGUI::Slider*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)SLIDER_NAME_MASTER.c_str());
//	if (slider)
//	{		
//		mNewAudioConfig.mMasterVolume=slider->getCurrentValue();
//		mParentGameState->getApp()->modifyVolume(SM_CHANNEL_MASTER_GROUP,mNewAudioConfig.mMasterVolume);
//	}
//	return true;
//}
bool GUIOptionsMenu::onSfxSliderValueChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Slider* slider = (CEGUI::Slider*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)SLIDER_NAME_SFX.c_str());
	if (slider)
	{		
		mNewAudioConfig.mSfxVolume=slider->getCurrentValue()/100;
		mParentGameState->getApp()->modifyVolume(SM_CHANNEL_SFX_GROUP,mNewAudioConfig.mSfxVolume);
	}
	return true;
}
//bool GUIOptionsMenu::onSfxSliderValueStopped(const CEGUI::EventArgs& args)
//{
//	return true;
//}
bool GUIOptionsMenu::onMusicSliderValueChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Slider* slider = (CEGUI::Slider*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)SLIDER_NAME_MUSIC.c_str());
	if (slider)
	{		
		mNewAudioConfig.mMusicVolume=slider->getCurrentValue()/100;
		mParentGameState->getApp()->modifyVolume(SM_CHANNEL_MUSIC_GROUP,mNewAudioConfig.mMusicVolume);
	}
	return true;

}
//bool GUIOptionsMenu::onMusicSliderValueStopped(const CEGUI::EventArgs& args)
//{
//	return true;
//}
bool GUIOptionsMenu::keyPressed(const OIS::KeyEvent &e)
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
			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mParentGameState->getApp()->getAsString(kc);
			radio->setText((CEGUI::utf8*)stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].first=(int)e.key;

			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			radio->setSelected(false);
		}

	}	
	return true;
}
bool GUIOptionsMenu::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (mExpectingPress && mCurrentlyEditedDevice== DEVICE_KEYB_MOUSE && !mCurrentlyEditedMapping.empty())
	{
		TInputCfgMouseButtonMapper buttonPressed =mParentGameState->getApp()->convertMouseButtonId(id);
		if (!mappingAlreadyFound(buttonPressed))
		{
			std::ostringstream stream;
			//inputConfig->setNewMapping(mCurrentlyEditedDevice,mCurrentlyEditedMapping,key);
			CEGUI::RadioButton* radio=(CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(mCurrentlyEditedMapping);
			stream.str("");
			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mParentGameState->getApp()->getMouseButtonName(buttonPressed);
			radio->setText((CEGUI::utf8*)stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].first=(int)buttonPressed;

			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			radio->setSelected(false);
		}
	}	
	return true;
}
bool GUIOptionsMenu::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	if (mExpectingPress && mCurrentlyEditedDevice== DEVICE_PAD_PSX && !mCurrentlyEditedMapping.empty())
	{
		if (!mappingAlreadyFound(button))
		{
			std::ostringstream stream;
			//inputConfig->setNewMapping(mCurrentlyEditedDevice,mCurrentlyEditedMapping,key);
			CEGUI::RadioButton* radio=(CEGUI::RadioButton*)CEGUI::WindowManager::getSingletonPtr()->getWindow(mCurrentlyEditedMapping);
			stream.str("");
			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mParentGameState->getApp()->getPadButtonName(button);
			radio->setText((CEGUI::utf8*)stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].second=button;

			mCurrentlyEditedMapping="";
			mExpectingPress=false;
			radio->setSelected(false);
		}
	}	
	return true;
}
bool GUIOptionsMenu::onRadioButtonDown(const CEGUI::EventArgs& args)
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
bool GUIOptionsMenu::mappingAlreadyFound(int code)
{
	TControlInputMapping::iterator it=mNewConfig.begin();
	bool found=false;
	while (!found && it!=mNewConfig.end())
	{
		if (mCurrentlyEditedDevice==DEVICE_KEYB_MOUSE)
			found=(it->second.first==code);
		else if (mCurrentlyEditedDevice==DEVICE_PAD_PSX)
			found=(it->second.second==code);
		if (!found) ++it;
	}
	return found;
}
bool GUIOptionsMenu::onMasterCheckBoxStateChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_MASTER.c_str());
	if (check)
	{		
		mNewAudioConfig.mMasterVolumeEnabled=check->isSelected();
		mParentGameState->getApp()->modifyEnable(SM_CHANNEL_MASTER_GROUP,check->isSelected());
	}
	return true;
}
bool GUIOptionsMenu::onMusicCheckBoxStateChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_MUSIC.c_str());
	if (check)
	{		
		mNewAudioConfig.mMusicVolumeEnabled=check->isSelected();
		mParentGameState->getApp()->modifyEnable(SM_CHANNEL_MUSIC_GROUP,check->isSelected());
	}
	return true;
}
bool GUIOptionsMenu::onSfxCheckBoxStateChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)CHECKBOX_NAME_SFX.c_str());
	if (check)
	{		
		mNewAudioConfig.mSfxVolumeEnabled=check->isSelected();
		mParentGameState->getApp()->modifyEnable(SM_CHANNEL_SFX_GROUP,check->isSelected());
	}
	return true;
}