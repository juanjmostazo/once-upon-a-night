#ifndef GUIOPTIONSMENUH_H
#define GUIOPTIONSMENUH_H
#include "GUIDefs.h"
#include "GUIWindow.h"
#include "../Input/InputDefs.h"
#include "../Audio/AudioDefs.h"

namespace OUAN
{
	typedef struct 
	{
		std::string keyMapping;
		std::string buttonText;
	} TButtonData;

	typedef std::map<std::string, TButtonData> TButtonDataMapping;
	const std::string MENUSTRINGS = "../../Resources/Text/en/menu-strings.xml";

	// Keys for the button texts
	const std::string BUTTON_TEXT_FORWARD="BUTTON_TEXT_FORWARD";
	const std::string BUTTON_TEXT_BACKWARDS="BUTTON_TEXT_BACKWARDS";
	const std::string BUTTON_TEXT_LEFT="BUTTON_TEXT_LEFT";
	const std::string BUTTON_TEXT_RIGHT="BUTTON_TEXT_RIGHT";

	const std::string BUTTON_TEXT_JUMP="BUTTON_TEXT_JUMP";
	const std::string BUTTON_TEXT_USEWEAPON="BUTTON_TEXT_USEWEAPON";
	const std::string BUTTON_TEXT_ACTION="BUTTON_TEXT_ACTION";
	const std::string BUTTON_TEXT_RELOAD="BUTTON_TEXT_RELOAD";

	const std::string BUTTON_TEXT_LROTATE="BUTTON_TEXT_LROTATE";
	const std::string BUTTON_TEXT_RROTATE="BUTTON_TEXT_RROTATE";
	const std::string BUTTON_TEXT_WALK="BUTTON_TEXT_WALK";
	const std::string BUTTON_TEXT_AUTOTARGET="BUTTON_TEXT_AUTOTARGET";

	const std::string BUTTON_TEXT_PAUSE="BUTTON_TEXT_PAUSE";
	const std::string BUTTON_TEXT_INGAME_MENU="BUTTON_TEXT_MENU";

	const std::string COMBO_ITEM_DEVICE_MOUSEKEYBOARD ="COMBO_ITEM_DEVICE_MOUSEKEYBOARD";
	const std::string COMBO_ITEM_DEVICE_PSXPAD ="COMBO_ITEM_DEVICE_PSXPAD";
	// Button names in the layout
	const std::string BUTTON_NAME_FORWARD="OUANOptions/Controls/ForwardBtn";
	const std::string BUTTON_NAME_BACKWARDS="OUANOptions/Controls/BackwardsBtn";
	const std::string BUTTON_NAME_LEFT="OUANOptions/Controls/LeftBtn";
	const std::string BUTTON_NAME_RIGHT="OUANOptions/Controls/RightBtn";

	const std::string BUTTON_NAME_JUMP="OUANOptions/Controls/JumpBtn";
	const std::string BUTTON_NAME_ACTION="OUANOptions/Controls/ActionBtn";
	const std::string BUTTON_NAME_USEWEAPON="OUANOptions/Controls/WeaponBtn";
	const std::string BUTTON_NAME_RELOAD="OUANOptions/Controls/AutoTargetBtn";

	const std::string BUTTON_NAME_LROTATE="OUANOptions/Controls/RotateLeftBtn";
	const std::string BUTTON_NAME_RROTATE="OUANOptions/Controls/RotateRightBtn";
	const std::string BUTTON_NAME_WALK="OUANOptions/Controls/WalkBtn";
	const std::string BUTTON_NAME_AUTOTARGET="OUANOptions/Controls/AutoTargetBtn";

	const std::string BUTTON_NAME_PAUSE="OUANOptions/Controls/PauseBtn";
	const std::string BUTTON_NAME_MENU="OUANOptions/Controls/MenuBtn";

	const std::string SLIDER_NAME_MASTER="OUANOptions/Sound/MasterSlider";
	const std::string SLIDER_NAME_MUSIC="OUANOptions/Sound/MusicSlider";
	const std::string SLIDER_NAME_SFX="OUANOptions/Sound/SfxSlider";

	const std::string CHECKBOX_NAME_MASTER="OUANOptions/SoundMasterCheck";
	const std::string CHECKBOX_NAME_MUSIC="OUANOptions/MusicCheck";
	const std::string CHECKBOX_NAME_SFX="OUANOptions/SfxCheck";

	const std::string OPTIONS_CEGUI_ID_CONTROLS_TAB="OUANOptions/ControlsTab";
	const std::string 
OPTIONS_CEGUI_ID_DEVICESELECT="OUANOptions/Controls/DeviceSelect";
	const std::string OPTIONS_CEGUI_ID_CONTROLS_APPLY="OUANOptions/Controls/Apply";
	const std::string OPTIONS_CEGUI_ID_CONTROLS_RESET="OUANOptions/Controls/Cancel";
	const std::string OPTIONS_CEGUI_ID_CONTROLS_INFO="OUANOptions/Controls/Explanation";
	const std::string OPTIONS_CEGUI_ID_SOUND_TAB="OUANOptions/SoundTab";
	const std::string OPTIONS_CEGUI_ID_MASTERDISABLELABEL="OUANOptions/Sound/MasterDisableLabel";
	const std::string OPTIONS_CEGUI_ID_SFXDISABLELABEL="OUANOptions/Sound/SfxDisableLabel";
	const std::string OPTIONS_CEGUI_ID_MUSICDISABLELABEL="OUANOptions/Sound/MusicDisableLabel";

	const std::string OPTIONS_CEGUI_ID_MASTERVOLUMELABEL="OUANOptions/Sound/MasterVolumeLabel";
	const std::string OPTIONS_CEGUI_ID_MUSICVOLUMELABEL="OUANOptions/Sound/MusicVolumeLabel";
	const std::string OPTIONS_CEGUI_ID_SFXVOLUMELABEL="OUANOptions/Sound/SfxVolumeLabel";
	const std::string OPTIONS_CEGUI_ID_SOUND_INFO="OUANOptions/Sound/Explanation";
		const std::string OPTIONS_CEGUI_ID_SOUND_APPLY="OUANOptions/Sound/Apply";
		const std::string OPTIONS_CEGUI_ID_SOUND_CANCEL="OUANOptions/Sound/Cancel";
		const std::string OPTIONS_CEGUI_ID_GRAPHICS_TAB="OUANOptions/GraphicsTab";
	const std::string OPTIONS_CEGUI_ID_GRAPHICS_UNAVAILABLE="OUANOptions/Graphics/InfoLabel";
	const std::string OPTIONS_CEGUI_ID_BACK="OUANOptions/Back";
	const std::string OPTIONS_CEGUI_ID_TITLE="OUANOptions/OptionsLabel";

	const std::string OPTIONS_CEGUI_ID_LANGUAGE="OUANOptions/Graphics/LanguageLabel";

	const std::string OPTIONS_CEGUI_ID_RESOLUTION="OUANOptions/Graphics/ResolutionLabel";

const std::string OPTIONS_CEGUI_ID_FULLSCREEN="OUANOptions/Graphics/FullscreenLabel";
const std::string OPTIONS_CEGUI_ID_ANTIALIASING="OUANOptions/Graphics/AntiAliasingLabel";
const std::string OPTIONS_CEGUI_ID_VSYNC="OUANOptions/Graphics/VSyncLabel";
const std::string OPTIONS_CEGUI_ID_SKIPINTRO="OUANOptions/Graphics/SkipIntroLabel";
const std::string OPTIONS_CEGUI_ID_APPLY="OUANOptions/Graphics/Apply";
const std::string OPTIONS_CEGUI_ID_RESET="OUANOptions/Graphics/Reset";


	class GUIOptionsMenu: public GUIWindow
	{
	private:
		/// A button has been clicked and the game's
		/// expecting a press to set a mapping
		bool mExpectingPress;
		/// Current input mappings
		TControlInputMapping mCurrentConfig;
		/// Modified input mappings
		TControlInputMapping mNewConfig;
		/// Current audio mappings
		TAudioSubsystemConfigData mCurrentAudioConfig;
		/// Modified audio mappings
		TAudioSubsystemConfigData mNewAudioConfig;

		/// Name of the button for the mapping being edited
		std::string mCurrentlyEditedMapping;
		/// Type of input device
		TInputDevice mCurrentlyEditedDevice;

		/// Text strings for the buttons
		ConfigurationPtr mButtonTextStrings;
		/// Button-name, mapping for every button name
		TButtonDataMapping mButtonData;

		/// Initialise the tab controller
		void initTabs();
		/// Initialise the controls tab window
		void initControlsTab();
		/// Initialise the sound tab window
		void initSoundTab();
		/// Initialise the graphics tab window
		void initGraphicsTab();

		/// Initialise a volume slider
		/// @param windowName	name of the slider
		/// @float maxValue		value corresponding to the slider's max
		/// @float defaultValue	default value the slider thumb will be at
		/// @float clickStep	increase/decrease in the value for every click
		///						on the slider
		void initVolumeSlider(const std::string& windowName, float maxValue, float defaultValue, float clickStep);

		/// Init a radio button
		/// @param buttonName Name of the button in the GUI layout file
		/// @param buttonText key to locate the button's text
		/// @param mappingName mapping
		/// @param buttonData Button data map
		void initButton(const std::string& buttonName, const std::string& buttonText, 
			const std::string& mappingName, TButtonDataMapping& buttonData);
		/// Init all the mapping radio buttons
		void initTextButtons();

		/// Tell if the press under the given code is already
		/// in use
		/// @param code code of the input device press
		/// @return true if the code corresponds to a mapping already
		///			in use
		bool mappingAlreadyFound(int code);		

		// EVENT HANDLERS
		/// Register all event bindings for the GUI
		void bindEvents();

		bool onBackToMenu(const CEGUI::EventArgs& args);
		bool onRadioButtonStateChange(const CEGUI::EventArgs& args);
		bool onApply (const CEGUI::EventArgs& args);
		bool onCancel (const CEGUI::EventArgs& args);
		bool onApplySound(const CEGUI::EventArgs& args);
		bool onCancelSound(const CEGUI::EventArgs& args);
		bool onDeviceSelectionChanged(const CEGUI::EventArgs& args);
		bool onRadioButtonDown(const CEGUI::EventArgs& args);
		//TODO: Generalise this
		bool onMasterSliderValueChanged(const CEGUI::EventArgs& args);
		//bool onMasterSliderValueStopped(const CEGUI::EventArgs& args);
		bool onMasterCheckBoxStateChanged(const CEGUI::EventArgs& args);
		bool onSfxSliderValueChanged(const CEGUI::EventArgs& args);
		//bool onSfxSliderValueStopped(const CEGUI::EventArgs& args);
		bool onSfxCheckBoxStateChanged(const CEGUI::EventArgs& args);
		bool onMusicSliderValueChanged(const CEGUI::EventArgs& args);
		//bool onMusicSliderValueStopped(const CEGUI::EventArgs& args);
		bool onMusicCheckBoxStateChanged(const CEGUI::EventArgs& args);

		void initLanguageCombo();

	public:
		/// Free resources
		void destroy();
		/// Initialise the GUI
		/// @param mParentGameState state owning this window
		void initGUI(GameStatePtr mParentGameState);

		bool keyPressed( const OIS::KeyEvent& e );
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );

		void setStrings();
	};
}
#endif