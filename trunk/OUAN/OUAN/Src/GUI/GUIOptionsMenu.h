#ifndef GUIOPTIONSMENUH_H
#define GUIOPTIONSMENUH_H
#include <cegui/CEGUI.h>
#include "../OUAN.h"

namespace OUAN
{
	typedef enum{
		DEVICE_KEYB_MOUSE=0,
		DEVICE_PAD_PSX,
	} TInputDevice;

	class GUIOptionsMenu: public GUIWindow
	{
	private:
		CEGUI::TabControl* mOptionsControl;

		CEGUI::Combobox* mInputDeviceCombo;

		CEGUI::RadioButton* mForwardKeyButton;
		CEGUI::RadioButton* mBackwardsKeyButton;
		CEGUI::RadioButton* mLeftKeyButton;
		CEGUI::RadioButton* mRightKeyButton;
		CEGUI::RadioButton* mReloadKeyButton;
		CEGUI::RadioButton* mWeaponKeyButton;
		CEGUI::RadioButton* mActionKeyButton;
		CEGUI::RadioButton* mJumpKeyButton;

		CEGUI::RadioButton* mWalkKeyButton;
		CEGUI::RadioButton* mAutotargetKeyButton;
		CEGUI::RadioButton* mLRotateKeyButton;
		CEGUI::RadioButton* mRRotateKeyButton;

		CEGUI::RadioButton* mPauseKeyButton;
		CEGUI::RadioButton* mMenuKeyButton;

		CEGUI::PushButton* mApplyKeyButton;
		CEGUI::PushButton* mResetKeyButton;
		
		CEGUI::PushButton* mBackKeyButton;
		
		std::string mCurrentlyEditedMapping;
		TInputDevice mCurrentlyEditedDevice;

		// SOUND TAB
		CEGUI::Slider* mMasterSoundSlider;
		CEGUI::Slider* mSfxSoundSlider;
		CEGUI::Slider* mMusicSoundSlider;
		CEGUI::Checkbox* mMasterSoundDisable;
		CEGUI::Checkbox* mSfxSoundDisable;
		CEGUI::Checkbox* mMusicSoundDisable;

		GameStatePtr mParentGameState;

		// Input configurations
		ConfigurationPtr mOldInputConfig;
		ConfigurationPtr mNewInputConfig;
		// Global configurations
		ConfigurationPtr mOldConfig;
		ConfigurationPtr mNewConfig;

		void initTabs();
		void initControlsTab();
		void initSoundTab();
		void initGraphicsTab();
		void initVolumeSlider(const std::string& windowName, float maxValue, float defaultValue, float clickStep, CEGUI::Slider* slider);

		// TODO: OPTIONS TAB
	public:
		void init(GameStatePtr parentGameState);
		void cleanUp();
	};
}
#endif