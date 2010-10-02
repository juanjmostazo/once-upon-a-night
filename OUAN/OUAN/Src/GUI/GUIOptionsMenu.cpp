#include "OUAN_Precompiled.h"

#include "GUIOptionsMenu.h"
#include "GUISubsystem.h"
#include "../Application.h"
#include "../Core/GameOptionsState.h"
using namespace OUAN;

void GUIOptionsMenu::initGUI(GameStatePtr parentGameState)
{
	GUIWindow::initGUI(parentGameState);
	ApplicationPtr app = mParentGameState->getApp();
	app->getInputMappings(mCurrentConfig);
	mNewConfig=mCurrentConfig;
	mButtonTextStrings=app->getMenusTextStrings();
	bindEvents();
	mCurrentlyEditedDevice=DEVICE_KEYB_MOUSE;
	mCurrentlyEditedMapping="";
	initTabs();
	initControlsTab();
	app->getAudioConfig(mCurrentAudioConfig);
	mNewAudioConfig=mCurrentAudioConfig;
	initSoundTab();

	mOldLanguage = mCurrentLanguage = app->getCurrentLanguage();
	mOldFullscreen = mCurrentFullscreen = app->getCurrentFullscreen();
	mOldResolution = mCurrentResolution = app->getCurrentResolution();
	mOldAA = mCurrentAA = app->getCurrentAntialiasing();
	mOldVSync= mCurrentVSync= app->getCurrentVsync();
	mOldSkip= mCurrentSkip = app->getCurrentSkip();
	initGraphicsTab();
	setStrings();


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
	ConfigurationPtr menuStrings=mParentGameState->getApp()->getMenusTextStrings();
	menuStrings->getOption("OPTIONS_CONTROLS_COMBO_DEFAULT",itemName);
	combo->setText(itemName);
	menuStrings->getOption(COMBO_ITEM_DEVICE_MOUSEKEYBOARD,itemName);	
	ListboxTextItem* lti = new ListboxTextItem(itemName,0);
	lti->setSelected(true);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	menuStrings->getOption(COMBO_ITEM_DEVICE_PSXPAD,itemName);
	lti= new ListboxTextItem(itemName,1);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);

	initTextButtons();
}
void GUIOptionsMenu::changeControlsComboTexts()
{
	using namespace CEGUI;
	CEGUI::Combobox* combo=(CEGUI::Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Controls/DeviceSelect");
	std::string itemName="";
	mButtonTextStrings->getOption("OPTIONS_CONTROLS_COMBO_DEFAULT",itemName);
	combo->setText(itemName);
	mButtonTextStrings->getOption(COMBO_ITEM_DEVICE_MOUSEKEYBOARD,itemName);	
	ListboxTextItem* lti = dynamic_cast<ListboxTextItem*> (combo->getListboxItemFromIndex(0));
	if (lti)
		lti->setText(itemName);
	
	mButtonTextStrings->getOption(COMBO_ITEM_DEVICE_PSXPAD,itemName);
	lti= dynamic_cast<ListboxTextItem*> (combo->getListboxItemFromIndex(1));
	if (lti)
		lti->setText(itemName);

}
void GUIOptionsMenu::changeLanguageSelectorTexts()
{
	using namespace CEGUI;
	CEGUI::Combobox* combo=(CEGUI::Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Graphics/LanguageSelector");
	std::string itemName="";
	int selectedLang=combo->getSelectedItem()->getID();	
	std::string upperKey=mLanguageComboMappings[selectedLang];
	std::transform(upperKey.begin(),upperKey.end(),upperKey.begin(),toupper);

	std::string defaultLanguage="OPTIONS_LANGUAGE_";
	std::string key=defaultLanguage;
	key.append(upperKey);
	mButtonTextStrings->getOption(key,itemName);
	combo->setText(itemName);

	int itemIndex;
	ListboxTextItem* lti = dynamic_cast<ListboxTextItem*> (combo->getListboxItemFromIndex(0));
	for (unsigned int i=0;i<combo->getItemCount();i++)
	{
		lti = dynamic_cast<ListboxTextItem*> (combo->getListboxItemFromIndex(i));
		if (lti)
		{
			itemIndex=lti->getID();
			upperKey=mLanguageComboMappings[itemIndex];
			std::transform(upperKey.begin(),upperKey.end(),
				upperKey.begin(),toupper);
			key=defaultLanguage;
			key.append(upperKey);
			mButtonTextStrings->getOption(key,itemName);
			lti->setText(itemName);
		}
	}
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
	using namespace CEGUI;

	initLanguageCombo();
	initResolutionCombo();	
	initAAComboTexts();
	
	Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/FullscreenCheck");
	if (check)
	{
		check->setSelected(mCurrentFullscreen.compare(OPTION_YES)==0);
	}
	
	check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/SkipIntro");
	if (check)
		check->setSelected(mCurrentSkip);

	check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/VSync");
	if (check)
		check->setSelected(mCurrentVSync.compare(OPTION_YES)==0);


}

void GUIOptionsMenu::initLanguageCombo()
{
	using namespace CEGUI;
	ApplicationPtr app = mParentGameState->getApp();
	//Get language combo
	Combobox* combo=(Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Graphics/LanguageSelector");
	std::string itemName="";
	ConfigurationPtr menuStrings=app->getMenusTextStrings();
	mLanguageComboMappings.clear();

	//Set default value: Pick the default language, make it uppercase
	// and  retrieve the i18n key
	std::string defaultLanguagePrefix = app->getCurrentLanguage();
	std::transform(defaultLanguagePrefix.begin(),defaultLanguagePrefix.end(),defaultLanguagePrefix.begin(),toupper);

	std::string defaultLanguage="OPTIONS_LANGUAGE_";
	defaultLanguage.append(defaultLanguagePrefix);

	menuStrings->getOption(defaultLanguage,itemName);
	combo->setText(itemName);

	//Initialize the combo items:
	std::vector<std::string> languages=mParentGameState->getApp()->getSupportedLanguages();
	std::string currentLangPrefix;
	std::string currentLang;
	ListboxTextItem* lti;
	int ltiIndex=0;
	//Loop through the available languages list
	for (std::vector<std::string>::iterator it=languages.begin();it!=languages.end();++it)
	{
		mLanguageComboMappings[ltiIndex]=*it;
		currentLangPrefix=*it;
		std::transform(currentLangPrefix.begin(),currentLangPrefix.end(),currentLangPrefix.begin(),toupper);
		currentLang="OPTIONS_LANGUAGE_";
		currentLang.append(currentLangPrefix);
		menuStrings->getOption(currentLang,itemName);

		lti = new ListboxTextItem(itemName,ltiIndex++);
		lti->setSelected(currentLangPrefix.compare(defaultLanguagePrefix)==0);
		lti->setAutoDeleted(true);
		lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
		combo->addItem(lti);
	}
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
		BUTTON_NAME_LROTATE,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_RROTATE,
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onRadioButtonStateChange,this));
	guiSS->bindEvent(CEGUI::RadioButton::EventSelectStateChanged,
		BUTTON_NAME_WALK,
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

	//Graphics
	guiSS->bindEvent(CEGUI::Combobox::EventListSelectionAccepted,
		"OUANOptions/Graphics/LanguageSelector",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onLanguageSelectorChanged,this));
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Graphics/Apply",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onApplyGraphics,this));
	guiSS->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Graphics/Reset",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onCancelGraphics,this));

	guiSS->bindEvent(CEGUI::Combobox::EventListSelectionAccepted,
		"OUANOptions/Graphics/ResolutionSelector",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onResolutionSelectorChanged,this));
	guiSS->bindEvent(CEGUI::Combobox::EventListSelectionAccepted,
		"OUANOptions/Graphics/AntiAliasing",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onAASelectorChanged,this));	

	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		"OUANOptions/Graphics/FullscreenCheck",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onFullscreenChange,this));
	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		"OUANOptions/Graphics/VSync",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onVSyncChange,this));
	guiSS->bindEvent(CEGUI::Checkbox::EventCheckStateChanged,
		"OUANOptions/Graphics/SkipIntro",
		CEGUI::Event::Subscriber(&GUIOptionsMenu::onSkipChange,this));


}
void GUIOptionsMenu::initTextButtons()
{
	mButtonData.clear();
	initButton(BUTTON_NAME_FORWARD,BUTTON_TEXT_FORWARD,KEY_FORWARD,mButtonData);
	initButton(BUTTON_NAME_BACKWARDS,BUTTON_TEXT_BACKWARDS,KEY_BACKWARDS,mButtonData);
	initButton(BUTTON_NAME_LEFT,BUTTON_TEXT_LEFT,KEY_LEFT,mButtonData);
	initButton(BUTTON_NAME_RIGHT,BUTTON_TEXT_RIGHT,KEY_RIGHT,mButtonData);

	initButton(BUTTON_NAME_JUMP,BUTTON_TEXT_JUMP,KEY_JUMP,mButtonData);
	initButton(BUTTON_NAME_ACTION,BUTTON_TEXT_ACTION,KEY_CENTER_CAMERA,mButtonData);
	initButton(BUTTON_NAME_USEWEAPON,BUTTON_TEXT_USEWEAPON,KEY_USEWEAPON,mButtonData);

	initButton(BUTTON_NAME_LROTATE,BUTTON_TEXT_LROTATE,KEY_ROTATELEFT,mButtonData);
	initButton(BUTTON_NAME_RROTATE,BUTTON_TEXT_RROTATE,KEY_ROTATERIGHT,mButtonData);
	initButton(BUTTON_NAME_WALK,BUTTON_TEXT_WALK,KEY_WALK,mButtonData);

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
		keyName=(mCurrentConfig[mappingName].keyCode<0)
		?mParentGameState->getApp()->getMouseButtonName(mCurrentConfig[mappingName].keyCode)
		:mParentGameState->getApp()->getAsString(static_cast<OIS::KeyCode>(mCurrentConfig[mappingName].keyCode));
	else
		keyName=mParentGameState->getApp()->getPadButtonName(mCurrentConfig[mappingName].padId);
	ConfigurationPtr menuTexts = mParentGameState->getApp()->getMenusTextStrings();
	std::string actionName="";
	menuTexts->getOption(mCurrentConfig[mappingName].stringKey,actionName);
	stream<<actionName<<' '<<keyName;
	radio->setText(stream.str().c_str());		
}
void GUIOptionsMenu::destroy()
{
	GUIWindow::destroy();	
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
	onCancelGraphics(args);
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
			ConfigurationPtr strings = mParentGameState->getApp()->getMenusTextStrings();
			stream.str("");
			std::string stringVal;
			strings->getOption(mCurrentConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].stringKey,stringVal);
			stream<<stringVal<<mParentGameState->getApp()->getAsString(kc);
			radio->setText(stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].keyCode=(int)e.key;

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
			ConfigurationPtr strings = mParentGameState->getApp()->getMenusTextStrings();
			stream.str("");
			std::string stringVal;
			strings->getOption(mCurrentConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].stringKey,stringVal);
			stream<<stringVal<<mParentGameState->getApp()->getMouseButtonName(buttonPressed);
/*			stream<<mButtonData[mCurrentlyEditedMapping].buttonText<<mParentGameState->getApp()->getMouseButtonName(buttonPressed)*/;
			radio->setText(stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].keyCode=(int)buttonPressed;

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
			ConfigurationPtr strings = mParentGameState->getApp()->getMenusTextStrings();
			stream.str("");
			std::string stringVal;
			strings->getOption(mCurrentConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].stringKey,stringVal);
			stream<<stringVal<<mParentGameState->getApp()->getPadButtonName(button);
			radio->setText(stream.str().c_str());		
			mNewConfig[mButtonData[mCurrentlyEditedMapping].keyMapping].padId=button;

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
			found=(it->second.keyCode==code);
		else if (mCurrentlyEditedDevice==DEVICE_PAD_PSX)
			found=(it->second.padId==code);
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

bool GUIOptionsMenu::onLanguageSelectorChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Combobox* combo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingletonPtr()->
		getWindow((CEGUI::utf8*)"OUANOptions/Graphics/LanguageSelector"));
	if (combo)
	{		
		CEGUI::ListboxItem* selection = static_cast<CEGUI::ListboxItem*>(combo->getSelectedItem());
		if (selection)
			changeLanguage(mLanguageComboMappings[selection->getID()]);

		return true;
	}
	return false;
}
bool GUIOptionsMenu::onApplyGraphics(const CEGUI::EventArgs& args)
{
	mOldLanguage=mCurrentLanguage;
	mOldAA = mCurrentAA;
	mOldFullscreen = mCurrentFullscreen;
	mOldVSync = mCurrentVSync;
	mOldSkip = mCurrentSkip;
	mOldResolution = mCurrentResolution;
	mParentGameState->getApp()->saveSystemConfig(mCurrentLanguage,
		mCurrentResolution, mCurrentFullscreen, mCurrentAA, mCurrentVSync,mCurrentSkip);
	return true;
}
bool GUIOptionsMenu::onCancelGraphics(const CEGUI::EventArgs& args)
{
	if (mCurrentLanguage.compare(mOldLanguage))
	{		
		mParentGameState->getApp()->changeCurrentLanguage(mOldLanguage);
		changeLanguage(mOldLanguage);
	}
	if (mCurrentResolution.compare(mOldResolution))
		mCurrentResolution=mOldResolution;
	if (mCurrentFullscreen.compare(mOldFullscreen))
		mCurrentFullscreen=mOldFullscreen;
	if (mCurrentAA.compare(mOldAA))
		mCurrentAA=mOldAA;
	if (mCurrentVSync.compare(mOldVSync))
		mCurrentVSync=mOldVSync;
	if (mCurrentSkip!=mOldSkip)
		mCurrentSkip=mOldSkip;
	return true;
}
void GUIOptionsMenu::changeLanguage(const std::string& newLang)
{
	mParentGameState->getApp()->changeCurrentLanguage(newLang);
	mCurrentLanguage=newLang;
	mButtonTextStrings=mParentGameState->getApp()->getMenusTextStrings();

	setStrings();
	initTextButtons();
	changeControlsComboTexts();
	changeLanguageSelectorTexts();
}
void GUIOptionsMenu::setStrings()
{
	ConfigurationPtr texts=mParentGameState->getApp()->getMenusTextStrings();
	if (mButtonTextStrings.get())
	{

		std::string windowNames[] = {
			OPTIONS_CEGUI_ID_CONTROLS_APPLY,OPTIONS_CEGUI_ID_CONTROLS_RESET,
			OPTIONS_CEGUI_ID_CONTROLS_INFO,OPTIONS_CEGUI_ID_CONTROLS_TAB,
			OPTIONS_CEGUI_ID_GRAPHICS_TAB,OPTIONS_CEGUI_ID_GRAPHICS_UNAVAILABLE,	
			OPTIONS_CEGUI_ID_MASTERDISABLELABEL,OPTIONS_CEGUI_ID_MASTERVOLUMELABEL,
			OPTIONS_CEGUI_ID_MUSICDISABLELABEL,OPTIONS_CEGUI_ID_MUSICVOLUMELABEL,
			OPTIONS_CEGUI_ID_SFXDISABLELABEL,OPTIONS_CEGUI_ID_SFXVOLUMELABEL,
			OPTIONS_CEGUI_ID_SOUND_APPLY,OPTIONS_CEGUI_ID_SOUND_CANCEL,
			OPTIONS_CEGUI_ID_SOUND_INFO,OPTIONS_CEGUI_ID_SOUND_TAB,
			OPTIONS_CEGUI_ID_BACK,OPTIONS_CEGUI_ID_TITLE,
			OPTIONS_CEGUI_ID_LANGUAGE,OPTIONS_CEGUI_ID_RESOLUTION,
			OPTIONS_CEGUI_ID_FULLSCREEN,OPTIONS_CEGUI_ID_ANTIALIASING,
			OPTIONS_CEGUI_ID_VSYNC,OPTIONS_CEGUI_ID_SKIPINTRO,
			OPTIONS_CEGUI_ID_APPLY,OPTIONS_CEGUI_ID_RESET
		};

		std::string defaultValues[]=
		{
			"OPTIONS_APPLY","OPTIONS_RESET",
			"OPTION_CONTROLS_INFO",
			"OPTIONS_CONTROLS_TAB",
			"OPTIONS_GRAPHICS_TAB",
			"OPTIONS_GRAPHICS_INFO",			
			"OPTIONS_SOUND_ENABLED",
			"OPTIONS_SOUND_MASTER_VOL",			
			"OPTIONS_SOUND_ENABLED",
			"OPTIONS_SOUND_MUSIC_VOL",
			"OPTIONS_SOUND_ENABLED",
			"OPTIONS_SOUND_SFX_VOL",
			"OPTIONS_APPLY",
			"OPTIONS_RESET",
			"OPTIONS_SOUND_INFO",
			"OPTIONS_SOUND_TAB",
			"OPTIONS_SCREEN_BACK",
			"OPTIONS_SCREEN_TITLE",
			"OPTIONS_GRAPHICS_LANGUAGE",
			"OPTIONS_GRAPHICS_RESOLUTION",
			"OPTIONS_GRAPHICS_FULLSCREEN",
			"OPTIONS_GRAPHICS_AA",
			"OPTIONS_GRAPHICS_VSYNC",
			"OPTIONS_GRAPHICS_SKIPINTRO",
			"OPTIONS_APPLY",
			"OPTIONS_RESET"
		};

		int windowNamesLen=26;
		std::string stringKey="";
		std::string stringVal="";
		CEGUI::Window* win=NULL;
		for (int i=0;i<windowNamesLen;i++)
		{
			stringVal="";
			win=CEGUI::WindowManager::getSingletonPtr()->getWindow(windowNames[i]);
			if (win)
			{
				if (windowNames[i].compare(OPTIONS_CEGUI_ID_CONTROLS_INFO)==0)				
					stringKey="OPTIONS_CONTROLS_INFO";
				else
					stringKey=win->getText().c_str();
				mButtonTextStrings->getOption(stringKey,stringVal);
				if (stringVal.empty())
				{
					mButtonTextStrings->getOption(defaultValues[i],stringVal);
				}
				win->setText(stringVal);
			}
		}
	}	 
}

void GUIOptionsMenu::changeAAComboTexts()
{
	using namespace CEGUI;
	CEGUI::Combobox* combo=
		(CEGUI::Combobox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Graphics/AntiAliasing");
	std::string itemName=mCurrentAA;
	std::string defaultValue=mAAMappings[itemName];
	mButtonTextStrings->getOption(defaultValue,itemName);
	combo->setText(itemName);

	//HARDCODING FOR THE WIN �_�U
	mButtonTextStrings->getOption("OPTIONS_AA_NONE",itemName);
	ListboxTextItem* lti = dynamic_cast<ListboxTextItem*>(combo->getListboxItemFromIndex(0));
	if (lti)
		lti->setText(itemName);

	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL2",itemName);
	lti = dynamic_cast<ListboxTextItem*>(combo->getListboxItemFromIndex(2));
	if (lti)
		lti->setText(itemName);

	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL4",itemName);
	lti = dynamic_cast<ListboxTextItem*>(combo->getListboxItemFromIndex(4));
	if (lti)
		lti->setText(itemName);

	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL8",itemName);
	lti = dynamic_cast<ListboxTextItem*>(combo->getListboxItemFromIndex(8));
	if (lti)
		lti->setText(itemName);
}
void GUIOptionsMenu::initAAComboTexts()
{
	mAAMappings.clear();
	mAAMappings[AA_LEVEL_0]="OPTIONS_AA_NONE";
	mAAMappings[AA_LEVEL_2]="OPTIONS_AA_LEVEL2";
	mAAMappings[AA_LEVEL_4]="OPTIONS_AA_LEVEL4";
	mAAMappings[AA_LEVEL_8]="OPTIONS_AA_LEVEL8";
	
	using namespace CEGUI;
	
	CEGUI::Combobox* combo=(CEGUI::Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Graphics/AntiAliasing");
	std::string itemName;
	std::string defaultValue;
	mButtonTextStrings->getOption(mAAMappings[mCurrentAA],defaultValue);
	combo->setText(defaultValue);

	//HARDCODING FOR THE WIN �_�U
	mButtonTextStrings->getOption("OPTIONS_AA_NONE",itemName);
	ListboxTextItem* lti = new ListboxTextItem(itemName,0);
	lti->setSelected(itemName.compare(defaultValue)==0);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	itemName="";
	
	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL2",itemName);
	lti = new ListboxTextItem(itemName,2);
	lti->setSelected(itemName.compare(defaultValue)==0);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	itemName="";

	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL4",itemName);
	lti = new ListboxTextItem(itemName,4);
	lti->setSelected(itemName.compare(defaultValue)==0);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	itemName="";

	mButtonTextStrings->getOption("OPTIONS_AA_LEVEL8",itemName);
	lti = new ListboxTextItem(itemName,8);
	lti->setSelected(itemName.compare(defaultValue)==0);
	lti->setAutoDeleted(true);
	lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
	combo->addItem(lti);
	itemName="";
}
void GUIOptionsMenu::initResolutionCombo()
{
	using namespace CEGUI;

	CEGUI::Combobox* combo=(CEGUI::Combobox*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/Graphics/ResolutionSelector");
	int suffixIndex;
	std::string defaultValue;
	if ((suffixIndex=mCurrentResolution.find(RESOLUTION_SUFFIX))!=std::string::npos)
	{
		defaultValue=mCurrentResolution.substr(0,suffixIndex);
	}
	combo->setText(defaultValue);

	ListboxTextItem* lti;
	for (int i=0;i<AVAILABLE_RESOLUTIONS_LEN;i++)
	{
		lti = new ListboxTextItem(AVAILABLE_RESOLUTIONS[i],i);
		lti->setSelected(defaultValue.compare(AVAILABLE_RESOLUTIONS[i])==0);
		lti->setAutoDeleted(true);
		lti->setTextColours(colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1),colour(0,0,0,1));
		combo->addItem(lti);
	}	
}
bool GUIOptionsMenu::onAASelectorChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Combobox* combo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingletonPtr()->
		getWindow((CEGUI::utf8*)"OUANOptions/Graphics/AntiAliasing"));
	if (combo)
	{		
		CEGUI::ListboxItem* selection = static_cast<CEGUI::ListboxItem*>(combo->getSelectedItem());
		int currentAAValue=0;
		if (selection)
		{
			currentAAValue = selection->getID();			
		}
		if (currentAAValue==0)
			mCurrentAA=AA_LEVEL_0;
		else 
		{
			std::stringstream currentAAStr;
			currentAAStr<<"Level "<<currentAAValue;
			mCurrentAA=currentAAStr.str();
		}

		return true;
	}
	return false;
}
bool GUIOptionsMenu::onResolutionSelectorChanged(const CEGUI::EventArgs& args)
{
	CEGUI::Combobox* combo = static_cast<CEGUI::Combobox*>(CEGUI::WindowManager::getSingletonPtr()->
		getWindow((CEGUI::utf8*)"OUANOptions/Graphics/ResolutionSelector"));
	if (combo)
	{		
		CEGUI::ListboxItem* selection = static_cast<CEGUI::ListboxItem*>(combo->getSelectedItem());
		int currentVal=0;
		if (selection)
		{
			currentVal = selection->getID();			
			if (currentVal>=0 && currentVal<AVAILABLE_RESOLUTIONS_LEN)
			{
				mCurrentResolution=AVAILABLE_RESOLUTIONS[currentVal]+RESOLUTION_SUFFIX;
			}
		}
		return true;
	}
	return false;
}
bool GUIOptionsMenu::onFullscreenChange(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/FullscreenCheck");
	mCurrentFullscreen=(check && check->isSelected())?OPTION_YES:OPTION_NO;
	return true;
}
bool GUIOptionsMenu::onVSyncChange(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/VSync");
	mCurrentVSync=(check && check->isSelected())?OPTION_YES:OPTION_NO;
	return true;
}
bool GUIOptionsMenu::onSkipChange(const CEGUI::EventArgs& args)
{
	CEGUI::Checkbox* check = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)"OUANOptions/Graphics/SkipIntro");
	mCurrentSkip=(check && check->isSelected());
	return true;
}
