#ifndef __CONTROL_INPUT_MANAGER__H__
#define __CONTROL_INPUT_MANAGER__H__

#include "InputDefs.h"
#include "FullInputManager.h"
#include "../Loader/Configuration.h"

namespace OUAN
{
	const std::string PSXPAD_CFG="../../Config/psxpad-cfg.xml";
	const std::string DEFAULTINPUT_CFG = "../../Config/defaultinput-cfg.xml";
	const std::string INPUTSTRINGS_CFG = "../../Config/input-strings_en.xml";
	// Config FILE keys
	const std::string KEY_MENU  = "Menu";
	const std::string KEY_PAUSE = "Pause";
	const std::string KEY_FORWARD = "Forward";
	const std::string KEY_BACKWARDS = "Backwards";
	const std::string KEY_LEFT = "Left";
	const std::string KEY_RIGHT = "Right";
	const std::string KEY_JUMP = "Jump";
	const std::string KEY_ACTION = "Action";
	const std::string KEY_RELOADWEAPON = "Reload";
	const std::string KEY_USEWEAPON = "UseWeapon";
	const std::string KEY_WALK = "Walk";
	const std::string KEY_ROTATELEFT = "LRotate";
	const std::string KEY_ROTATERIGHT = "RRotate";
	const std::string KEY_AUTOTARGET = "AutoTarget";

	const std::string KEY_QUICKEXIT = "QuickExit";
	const std::string KEY_DEBUG_PERFORMANCE = "DebugPerformance";
	const std::string KEY_DEBUG_PHYSICS = "DebugPhysics";
	const std::string KEY_CHANGE_CAMERA = "ChangeCamera";
	const std::string KEY_CHANGE_CAMERA_CONTROLLER = "ChangeCameraController";
	const std::string KEY_CHANGE_WORLD = "ChangeWorld";
	const std::string KEY_CHANGE_LEVEL = "ChangeLevel";
	const std::string KEY_TOGGLE_CONSOLE = "ToggleConsole";
	const std::string KEY_TOGGLE_VOLUMES = "ToggleVolumes";

	//...for the PSX file
	const std::string DEFAULT_PAD_ID="DEFAULT_PAD_ID"; 
	const std::string PAD_SELECT="PAD_SELECT"; 
	const std::string PAD_START="PAD_START";
	const std::string PAD_UP="PAD_UP"; 
	const std::string PAD_DOWN="PAD_DOWN"; 
	const std::string PAD_LEFT="PAD_LEFT";
	const std::string PAD_RIGHT="PAD_RIGHT";
	const std::string PAD_TRIANGLE="PAD_TRIANGLE";
	const std::string PAD_SQUARE="PAD_SQUARE";
	const std::string PAD_CIRCLE="PAD_CIRCLE";
	const std::string PAD_X="PAD_X";
	const std::string PAD_L1="PAD_L1";
	const std::string PAD_R1="PAD_R1";
	const std::string PAD_L2="PAD_L2";
	const std::string PAD_R2="PAD_R2";

	//Text file keys
	const std::string PAD_BUTTON_NAME_UP="PAD_BUTTON_NAME_UP";
	const std::string PAD_BUTTON_NAME_DOWN="PAD_BUTTON_NAME_DOWN";
	const std::string PAD_BUTTON_NAME_LEFT="PAD_BUTTON_NAME_LEFT";
	const std::string PAD_BUTTON_NAME_RIGHT="PAD_BUTTON_NAME_RIGHT";

	const std::string PAD_BUTTON_NAME_SQUARE="PAD_BUTTON_NAME_SQUARE";
	const std::string PAD_BUTTON_NAME_CIRCLE="PAD_BUTTON_NAME_CIRCLE";
	const std::string PAD_BUTTON_NAME_TRIANGLE="PAD_BUTTON_NAME_TRIANGLE";
	const std::string PAD_BUTTON_NAME_X="PAD_BUTTON_NAME_X";

	const std::string PAD_BUTTON_NAME_L1="PAD_BUTTON_NAME_L1";
	const std::string PAD_BUTTON_NAME_R1="PAD_BUTTON_NAME_R1";
	const std::string PAD_BUTTON_NAME_L2="PAD_BUTTON_NAME_L2";
	const std::string PAD_BUTTON_NAME_R2="PAD_BUTTON_NAME_R2";

	const std::string PAD_BUTTON_NAME_START="PAD_BUTTON_NAME_START";
	const std::string PAD_BUTTON_NAME_SELECT="PAD_BUTTON_NAME_SELECT";

	const std::string MOUSE_BUTTON_NAME_LEFT ="MOUSE_BUTTON_NAME_LEFT";
	const std::string MOUSE_BUTTON_NAME_RIGHT ="MOUSE_BUTTON_NAME_RIGHT";
	const std::string MOUSE_BUTTON_NAME_MIDDLE ="MOUSE_BUTTON_NAME_MIDDLE";

	const std::string MOUSE_BUTTON_NAME_MB3 ="MOUSE_BUTTON_NAME_MB3";
	const std::string MOUSE_BUTTON_NAME_MB4 ="MOUSE_BUTTON_NAME_MB4";
	const std::string MOUSE_BUTTON_NAME_MB5 ="MOUSE_BUTTON_NAME_MB5";
	const std::string MOUSE_BUTTON_NAME_MB6 ="MOUSE_BUTTON_NAME_MB6";
	const std::string MOUSE_BUTTON_NAME_MB7 ="MOUSE_BUTTON_NAME_MB7";

	/// Since some of OIS' key codes and mouse button ids
	/// overlap, negative numbers will be used in the
	/// default input file to represent mouse presses
	/// They'll have to be converted to OIS's 
	/// MouseButtonID equivalent, though
	typedef enum
	{
		INPUTCFG_MOUSEBUTTON_LEFT= -0x01,
		INPUTCFG_MOUSEBUTTON_RIGHT= -0x02,
		INPUTCFG_MOUSEBUTTON_MIDDLE= -0x03,
		INPUTCFG_MOUSEBUTTON_MB3= -0x04,
		INPUTCFG_MOUSEBUTTON_MB4= -0x05,
		INPUTCFG_MOUSEBUTTON_MB5= -0x06,
		INPUTCFG_MOUSEBUTTON_MB6= -0x07,
		INPUTCFG_MOUSEBUTTON_MB7= -0x08,	
	} TInputCfgMouseButtonMapper;

	/// Struct to hold the values of the
	/// key (or mouse button) codes for every possible input
	/// action, after they've been read from the config file
	/// or on the options screen.
	typedef struct
	{
		int keyMenu,keyPause;
		int keyForward,keyBackwards,keyLeft,keyRight;
		int keyJump,keyAction,keyReloadWeapon,keyUseWeapon;
		int keyWalk,keyRotateLeft,keyRotateRight,keyAutoTarget;
		int keyQuickExit, keyDebugPerformance, keyDebugPhysics;
		int keyChangeCamera, keyChangeCameraController;
		int keyChangeWorld, keyChangeLevel;
		int keyToggleConsole, keyToggleVolumes;
	} TDefaultInputData;

	class ControlInputManager : public FullInputManager
	{
	public:
		ControlInputManager();
		virtual ~ControlInputManager();

		/// Load configuration
		void init( Ogre::RenderWindow* window, bool showDefaultMousePointer = true );
		/// Clear resources
		void finalise();

		// Since at the moment there will be no need for a polymorphic redefinition 
		// of these methods, I've taken out the "virtual" specifier to reduce unnecessary overhead

		bool isPressedMenu();			// Go to main menu
		bool isPressedPause();			// Go to pause menu

		bool isPressedJump();			// Jump
		bool isPressedDoAction();		// Perform an action
		bool isPressedUseWeapon();		// Use the pillow (dream) or shoot (nightmare)
		bool isPressedWeaponAction();	// Change holder hand (dream) or recharge (nightmare)

		bool isPressedGoForward();		// Go forward
		bool isPressedGoBack();			// Go back
		bool isPressedGoLeft();			// Go to left
		bool isPressedGoRight();		// Go to right

		bool isPressedWalk();			// Walk mode
		bool isPressedAutoPoint();		// Automatic pointer
		bool isPressedRotateLeft();		// Rotate color to left
		bool isPressedRotateRight();	// Rotate color to right

		/// Convenience method to provide a quick exit key (essentially for debugging purposes)
		bool isPressedQuickExit();
		/// Convenience method to enable performance debug mode
		bool isPressedToggleDebugPerformance();
		/// Convenience method to enable physics debug mode
		bool isPressedToggleDebugPhysics();
		/// Convenience method to change between cameras
		bool isPressedToggleChangeCamera();
		/// Convenience method to change current camera controller
		bool isPressedToggleChangeCameraController();
		/// Convenience method to change current world
		bool isPressedToggleChangeWorld();
		/// Convenience method to change current level
		bool isPressedToggleChangeLevel();
		/// Detect if the 'toggle-console' key has been pressed
		/// @return true if there has been a 'toggle-console' key press
		bool isPressedToggleConsole();
		/// Detect if the 'toggle-volumes' key has been pressed
		/// @return true if there has been a 'toggle-volumes' key press
		bool isPressedToggleVolumes();

		void getMouseStateRelValues(
			double*, double*, double*);			// Mouse x, y, z coordinate values

		void getJoystickStateAxes(
			double*, double*, double*, double*);	// Joystick left and right axes values (from -1 to 1)

		/// Fill a dictionary containing the keyboard and pad mappings
		/// for a set of key ids
		void getInputMappings (TControlInputMapping& mappings);

		std::string getMouseButtonName(int keyCode) const;
		std::string getAsString(OIS::KeyCode kc) const;
		std::string getPadButtonName(int button) const;
		TInputCfgMouseButtonMapper convertMouseButtonId(OIS::MouseButtonID mouseButtonId);
		
		void replaceConfig(TControlInputMapping& newMapping, bool saveToFile);
		
	protected:
		/// Parse configuration files for the input device button mappings
		bool loadConfig();

		/// TODO COMMENT
		bool loadStrings();

		/// Read as an hexadecimal integer the value of the 'key' parameter 
		/// on the specified configuration object
		/// @param cfg		configuration file which will be queried for the key
		/// @param key		option key to read
		/// @param value	output parameter. It will hold the option's value as an integer
		void readOption(Configuration cfg,const std::string& key, int& value);

		/// Load config file for the default input method, i.e, the good old mouse-keyboard combo
		/// @param configFilePath configuration path
		/// @return true if configuration file was read correctly; false otherwise
		bool loadDefaultInputConfig(const std::string& configFilePath);

		/// Get OIS' mouse button ID equivalent for the specified mouseButtonId as read from
		/// the default input configuration.
		/// @param inputCfgMouseButtonId default input configuration mouse button id.
		/// @return OIS' mouse button identifier.
		OIS::MouseButtonID convertMouseButtonId(TInputCfgMouseButtonMapper inputCfgMouseButtonId);

		/// Convenience method used to reduce massive copy-paste and replace when modifying
		/// the isPressedSOMEACTION() methods to add configurable keyboard/mouse input
		/// The default joystick will check the given button is pressed, and depending on the kind of value
		/// of the defaultInputKey parameter, the keyboard or mouse devices will be queried accordingly.
		/// Positive values will represent keyboard presses, whereas the negative ones will be mapped to
		/// mouse button clicks.
		/// 
		/// @param padButton		joystick button to query
		/// @param defaultInputKey	value from the config file which will be appropriately mapped to an
		///							OIS::KeyCode value or an OIS::MouseButtonID.
		/// @return true if the given joystick button/ default input key was pressed; false otherwise
		bool isPressed(int padButton, int defaultInputKey);

		/// Add to the 'mappings' dictionary a new entry for keyID, where its value will be
		/// a pair consisting of the values given under keyboardMapping and psxPadMapping
		/// @param keyID			key identifier
		/// @param keyboardMapping	keycode for the given mapping
		/// @param psxPadMapping	button id for the given mapping
		/// @param mappings			dictionary containing the input mappings for the given key identifier
		void addPair(std::string keyID,int keyboardMapping, int psxPadMapping, TControlInputMapping& mappings);

		void replacePair(std::string keyID,int& keyboardMapping, int& psxPadMapping, TControlInputMapping& mappings);

		/// Structure holding the values of the keycodes/mouse button ids for all possible in-game input actions 
		TDefaultInputData mDefaultInputData;

		int defaultPadId;
		int padSelect, padStart;
		int padUp, padDown, padLeft, padRight;
		int padTriangle, padX, padSquare, padCircle;
		int padL1, padL2, padR1, padR2;

		ConfigurationPtr mInputTextStrings;

		void ControlInputManager::saveDefaultInput();
		void ControlInputManager::savePsxInput();
	};
}
#endif