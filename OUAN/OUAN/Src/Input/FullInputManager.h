#ifndef __FULL_INPUT_MANAGER__H__
#define __FULL_INPUT_MANAGER__H__

#include "../Loader/Configuration.h"

namespace Ogre
{
	class RenderWindow;
}

namespace OUAN
{
	const std::string PSXPAD_CFG="../../Config/psxpad-cfg.xml";
	const std::string DEFAULTINPUT_CFG = "../../Config/defaultinput-cfg.xml";
	const std::string INPUTSTRINGS = "../../Resources/Text/en/input-strings.xml";
	const std::string INPUTCOMMONJOYSTICK_CFG = "../../Config/input-common_joystick.xml";
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
	const std::string KEY_DEBUG_TRAJECTORY = "DebugTrajectory";
	const std::string KEY_CHANGE_CAMERA = "ChangeCamera";
	const std::string KEY_CHANGE_CAMERA_CONTROLLER = "ChangeCameraController";
	const std::string KEY_CHANGE_WORLD = "ChangeWorld";
	const std::string KEY_CHANGE_LEVEL = "ChangeLevel";
	const std::string KEY_TOGGLE_CONSOLE = "ToggleConsole";
	const std::string KEY_TOGGLE_VOLUMES = "ToggleVolumes";
	const std::string KEY_TOGGLE_GOD_MODE = "ToggleGodMode";
	const std::string KEY_TOGGLE_CHANGEWORLD_DEBUG = "ToggleChangeWorldDebug";
	const std::string KEY_TOGGLE_SHOW_SCENE_NODES = "ToggleShowSceneNodes";

	//General Joystick Config 
	const std::string DEFAULT_PAD_ID="DEFAULT_PAD_ID";
	const std::string PAD_CAMERA_JOYSTICK_SCALE_FACTOR= "PAD_CAMERA_JOYSTICK_SCALE_FACTOR";
	const std::string PAD_JOYSTICK_BORDER= "PAD_JOYSTICK_BORDER";

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

	//TODO: SOME R2/L2 ARE ANALOG

	const std::string PAD_BUTTON_NAME_START="PAD_BUTTON_NAME_START";
	const std::string PAD_BUTTON_NAME_SELECT="PAD_BUTTON_NAME_SELECT";

	//TODO ADD THIS TO THE CONFIGURATION GUI AND .XML FILE
	const std::string PAD_LEFT_JOYSTICK_Y="PAD_LEFT_JOYSTICK_Y";
	const std::string PAD_LEFT_JOYSTICK_X="PAD_LEFT_JOYSTICK_X";


	const std::string PAD_RIGHT_JOYSTICK_Y="PAD_RIGHT_JOYSTICK_Y";
	const std::string PAD_RIGHT_JOYSTICK_X="PAD_RIGHT_JOYSTICK_X";

	//

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
		int keyQuickExit, keyDebugPerformance, keyDebugPhysics, keyDebugTrajectory;
		int keyChangeCamera, keyChangeCameraController;
		int keyChangeWorld, keyChangeLevel;
		int keyToggleConsole, keyToggleVolumes;
		int keyToggleGodMode, keyToggleChangeWorldDebug;
		int keyToggleShowSceneNodes;
	} TDefaultInputData;


	class FullInputManager
		: public OIS::MouseListener
		, public OIS::KeyListener
		, public OIS::JoyStickListener
	{
	public:
		FullInputManager();
		virtual ~FullInputManager();

		void capture();

		virtual bool mouseMoved( const OIS::MouseEvent& e );
		virtual bool mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID button );
		virtual bool mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID button );

		virtual bool keyPressed( const OIS::KeyEvent& e );
		virtual bool keyReleased( const OIS::KeyEvent& e );

		virtual bool povMoved( const OIS::JoyStickEvent &e, int pov );
		virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis );
		virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
		virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );

		virtual OIS::Mouse*    getMouse( void );
		virtual OIS::Keyboard* getKeyboard( void );
		virtual OIS::JoyStick* getJoystick( unsigned int index );

		virtual void getMouseStateRelValues(double & x, double & y, double & z);

		virtual int getNumOfJoysticks( void );
		virtual void getJoystickStateAxes( int index, double & leftX, double & leftY, double & rightX, double & rightY);
		

		virtual void init( Ogre::RenderWindow* window, bool showDefaultMousePointer = true );
		virtual void finalise();
	protected:

		double getJoystickNormalisedAxe(int axeState, int maxAxis, int border);

		/// Parse configuration files for the input device button mappings
		bool loadConfig();

		/// TODO COMMENT
		bool loadStrings();

		/// Load config file for the default input method, i.e, the good old mouse-keyboard combo
		/// @param configFilePath configuration path
		/// @return true if configuration file was read correctly; false otherwise
		bool loadDefaultInputConfig(const std::string& configFilePath);


		/// Read as an hexadecimal integer the value of the 'key' parameter 
		/// on the specified configuration object
		/// @param cfg		configuration file which will be queried for the key
		/// @param key		option key to read
		/// @param value	output parameter. It will hold the option's value as an integer
		void readOption(Configuration cfg,const std::string& key, int& value);
		
		OIS::InputManager* m_inputManager;
		OIS::Keyboard* m_keyboard;
		OIS::Mouse* m_mouse;

		std::vector<OIS::JoyStick*> m_joysticks;
		std::vector<OIS::JoyStick*>::iterator it_joystick;
		std::vector<OIS::JoyStick*>::iterator it_joystickEnd;

		int defaultPadId;
		int padSelect, padStart;
		int padUp, padDown, padLeft, padRight;
		int padTriangle, padX, padSquare, padCircle;
		int padL1, padL2, padR1, padR2;
		int padLeftJoystickX, padLeftJoystickY;
		int padRightJoystickX, padRightJoystickY;

		double padCameraJoystickScaleFactor, padJoystickBorder;

		ConfigurationPtr mInputTextStrings;

		/// Structure holding the values of the keycodes/mouse button ids for all possible in-game input actions 
		TDefaultInputData mDefaultInputData;


	};
}
#endif