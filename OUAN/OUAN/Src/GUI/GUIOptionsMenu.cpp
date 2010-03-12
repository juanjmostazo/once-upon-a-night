#include "GUIOptionsMenu.h"
#include "GUISubsystem.h"
#include "../Core/GameOptionsState.h"

void GUIOptionsMenu::init(GameStatePtr parentGameState)
{
	mParentGameState=parentGameState;
	GUISubsystemPtr guiSubsystem =mParentGameState->getApp()->getGUISubsystem();
	guiSubsystem->bindEvent(CEGUI::PushButton::EventClicked,
		"OUANOptions/Back",
		CEGUI::Event::Subscriber(&GameOptionsState::onBackToMenu,mParentGameState));

	initTabs();
	initControlsTab();
	initSoundTab();
	//initGraphicsTab();


}
void GUIOptionsMenu::cleanUp()
{

}
void GUIOptionsMenu::initTabs()
{
	mOptionsControl	= (TabControl*)WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/TabCtrl");
	if (mOptionsControl)
	{
		mOptionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/ControlsTab"));
		mOptionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/SoundTab"));
		mOptionsControl->addTab(WindowManager::getSingletonPtr()->getWindow((utf8*)"OUANOptions/GraphicsTab"));
		mOptionsControl->setSelectedTab(0);
	}
}
void GUIOptionsMenu::initControlsTab()
{


}
void GUIOptionsMenu::initSoundTab()
{
	initVolumeSlider("OUANOptions/Sound/MasterSlider",100,80,10.0, mMasterSoundSlider);
	initVolumeSlider("OUANOptions/Sound/SfxSlider",100,80,10.0,mSfxSoundSlider);
	initVolumeSlider("OUANOptions/Sound/MusicSlider",100,80,10.0,mMusicSoundSlider);
}
void GUIOptionsMenu::initGraphicsTab()
{

}
void GUIOptionsMenu::initVolumeSlider(const std::string& windowName, float maxValue, float defaultValue, float clickStep, CEGUI::Slider* slider)
{
	slider = (CEGUI::Slider*) WindowManager::getSingletonPtr()->getWindow((CEGUI::utf8*)windowName.c_str());
	if (slider)
	{
		slider->setMaxValue(maxValue);
		slider->setCurrentValue(defaultValue);
		slider->setClickStep(clickStep);
	}
}