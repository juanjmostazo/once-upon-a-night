#include "OUAN_Precompiled.h"
#include "FullInputManager.h"

using namespace OUAN;

FullInputManager::FullInputManager()
: m_inputManager( NULL )
, m_keyboard( NULL )
, m_mouse( NULL )
{

}

FullInputManager::~FullInputManager()
{

}

void FullInputManager::init( Ogre::RenderWindow* window, bool showDefaultMousePointer )
{
	size_t windowHandle = 0;
	window->getCustomAttribute( "WINDOW", &windowHandle );

	std::ostringstream windowHandleString;
	windowHandleString << windowHandle;

	OIS::ParamList parameters;
	parameters.insert( std::make_pair( std::string( "WINDOW" ), windowHandleString.str() ) );
	if ( showDefaultMousePointer )
	{
		parameters.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_FOREGROUND" ) ) );
		parameters.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );
		parameters.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_FOREGROUND" ) ) );
		parameters.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );
		parameters.insert( std::make_pair( std::string( "x11_mouse_grab" ), std::string( "false" ) ) );
		parameters.insert( std::make_pair( std::string( "x11_mouse_hide" ), std::string( "false" ) ) );
		parameters.insert( std::make_pair( std::string( "x11_keyboard_grab" ), std::string( "false" ) ) );
		parameters.insert( std::make_pair( std::string( "XAutoRepeatOn" ), std::string( "true" ) ) );
	}

	m_inputManager = OIS::InputManager::createInputSystem( parameters );

	m_keyboard = static_cast< OIS::Keyboard* >( m_inputManager->createInputObject( OIS::OISKeyboard, true ) );
	m_mouse = static_cast< OIS::Mouse* >( m_inputManager->createInputObject( OIS::OISMouse, true ) );

	if (m_inputManager->numJoySticks() > 0) {
        m_joysticks.resize( m_inputManager->numJoySticks() );

        it_joystick    = m_joysticks.begin();
        it_joystickEnd = m_joysticks.end();
        for(; it_joystick != it_joystickEnd; ++it_joystick ) {
            (*it_joystick) = static_cast<OIS::JoyStick*>( m_inputManager->createInputObject( OIS::OISJoyStick, true ) );
            (*it_joystick)->setEventCallback( this );
        }
    }

	const OIS::MouseState& mouseState = m_mouse->getMouseState();

	mouseState.width = window->getWidth();
	mouseState.height = window->getHeight();

	m_mouse->setEventCallback( this );
	m_keyboard->setEventCallback( this );

	loadConfig();
	loadStrings();
}


//////////////////////////////////////////////////////////////

bool FullInputManager::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	// Load key mappings for mouse-keyboard input
	loadDefaultInputConfig(DEFAULTINPUT_CFG);

	// Load common joystick factors
	if (config.loadFromFile(INPUTCOMMONJOYSTICK_CFG))
	{
		config.getOption(PAD_CAMERA_JOYSTICK_SCALE_FACTOR, value); 
		padCameraJoystickScaleFactor = atof(value.c_str());
		config.getOption(PAD_JOYSTICK_BORDER, value); 
		padJoystickBorder = atof(value.c_str());

	}

	// Same for a pad
	if (config.loadFromFile(PSXPAD_CFG))
	{
		config.getOption(DEFAULT_PAD_ID, value); 
		defaultPadId = atoi(value.c_str());

		config.getOption(PAD_BUTTON_NAME_SELECT, value); 
		padSelect = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_START, value); 
		padStart = atoi(value.c_str());

		config.getOption(PAD_BUTTON_NAME_UP, value); 
		padUp = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_DOWN, value); 
		padDown = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_LEFT, value); 
		padLeft = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_RIGHT, value); 
		padRight = atoi(value.c_str());

		config.getOption(PAD_BUTTON_NAME_TRIANGLE, value); 
		padTriangle = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_X, value); 
		padX = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_SQUARE, value); 
		padSquare = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_CIRCLE, value); 
		padCircle = atoi(value.c_str());

		config.getOption(PAD_BUTTON_NAME_L1, value); 
		padL1 = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_L2, value); 
		padL2 = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_R1, value); 
		padR1 = atoi(value.c_str());
		config.getOption(PAD_BUTTON_NAME_R2, value); 
		padR2 = atoi(value.c_str());

		config.getOption(PAD_LEFT_JOYSTICK_X, value); 
		padLeftJoystickX = atoi(value.c_str());
		config.getOption(PAD_LEFT_JOYSTICK_Y, value); 
		padLeftJoystickY = atoi(value.c_str());

		config.getOption(PAD_RIGHT_JOYSTICK_X, value); 
		padRightJoystickX = atoi(value.c_str());
		config.getOption(PAD_RIGHT_JOYSTICK_Y, value); 
		padRightJoystickY = atoi(value.c_str());

		success = true;
	} 
	else 
	{
		//Logger::getInstance()->log(PSXPAD_CFG + " COULD NOT BE LOADED!");

		defaultPadId = -1;
		padSelect = -1, padStart = -1;
		padUp = -1, padDown = -1, padLeft = -1, padRight = -1;
		padTriangle = -1, padX = -1, padSquare = -1, padCircle = -1;
		padL1 = -1, padL2 = -1, padR1 = -1, padR2 = -1;

		success = false;
	}
 
//	config.~Configuration();
	return success;
}

void FullInputManager::readOption(Configuration cfg,const std::string& key, int& value)
{
	try
	{
		std::string strValue;
		std::istringstream valueReader;
		cfg.getOption(key,strValue);
		valueReader.str(strValue);
		valueReader>>std::hex>>value;
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("ERROR! [FullInputManager] Error reading key "+key);
	}
}

bool FullInputManager::loadDefaultInputConfig(const std::string& configFilePath)
{
	Configuration config;
	if (config.loadFromFile(configFilePath))
	{
		readOption(config,KEY_MENU,mDefaultInputData.keyMenu);
		readOption(config,KEY_PAUSE,mDefaultInputData.keyPause);

		readOption(config,KEY_USEWEAPON,mDefaultInputData.keyUseWeapon);
		readOption(config,KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon);
		readOption(config,KEY_ACTION,mDefaultInputData.keyAction);
		readOption(config,KEY_JUMP,mDefaultInputData.keyJump);
		readOption(config,KEY_WALK,mDefaultInputData.keyWalk);

		readOption(config,KEY_FORWARD,mDefaultInputData.keyForward);			
		readOption(config,KEY_BACKWARDS,mDefaultInputData.keyBackwards);
		readOption(config,KEY_LEFT,mDefaultInputData.keyLeft);
		readOption(config,KEY_RIGHT,mDefaultInputData.keyRight);

		readOption(config,KEY_AUTOTARGET,mDefaultInputData.keyAutoTarget);
		readOption(config,KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft);
		readOption(config,KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight);

		readOption(config,KEY_QUICKEXIT,mDefaultInputData.keyQuickExit);
		readOption(config,KEY_DEBUG_PERFORMANCE,mDefaultInputData.keyDebugPerformance);
		readOption(config,KEY_DEBUG_PHYSICS,mDefaultInputData.keyDebugPhysics);
		readOption(config,KEY_DEBUG_TRAJECTORY,mDefaultInputData.keyDebugTrajectory);
		readOption(config,KEY_CHANGE_CAMERA_CONTROLLER,mDefaultInputData.keyChangeCameraController);
		readOption(config,KEY_CHANGE_CAMERA,mDefaultInputData.keyChangeCamera);
		readOption(config,KEY_CHANGE_WORLD,mDefaultInputData.keyChangeWorld);
		readOption(config,KEY_CHANGE_LEVEL,mDefaultInputData.keyChangeLevel);
		readOption(config,KEY_TOGGLE_CONSOLE,mDefaultInputData.keyToggleConsole);
		readOption(config,KEY_TOGGLE_VOLUMES,mDefaultInputData.keyToggleVolumes);
		readOption(config,KEY_TOGGLE_GOD_MODE,mDefaultInputData.keyToggleGodMode);
		readOption(config,KEY_TOGGLE_CHANGEWORLD_DEBUG,mDefaultInputData.keyToggleChangeWorldDebug);
		readOption(config,KEY_TOGGLE_SHOW_SCENE_NODES,mDefaultInputData.keyToggleShowSceneNodes);
		return true;
	}
	else
	{
		//Logger::getInstance()->log(configFilePath + " COULD NOT BE LOADED!");

		mDefaultInputData.keyAction=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyAutoTarget=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyBackwards=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyReloadWeapon=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyForward=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyJump=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyLeft=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyMenu=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyPause=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRight=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRotateLeft=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRotateRight=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyWalk=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyUseWeapon=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyQuickExit=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyDebugPerformance=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyDebugPhysics=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyDebugTrajectory=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeCamera=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeCameraController=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeWorld=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeLevel=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyToggleConsole=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyToggleVolumes=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyToggleGodMode=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyToggleChangeWorldDebug=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyToggleShowSceneNodes=OIS::KC_UNASSIGNED;
		return false;
	}
}

bool FullInputManager::loadStrings()
{
	mInputTextStrings.reset(new Configuration());
	return mInputTextStrings->loadFromFile(INPUTSTRINGS_CFG);
}

void FullInputManager::finalise()
{
	if ( m_inputManager )
	{
		if ( m_mouse )
		{
			m_inputManager->destroyInputObject( m_mouse );
		}

		if ( m_keyboard )
		{
			m_inputManager->destroyInputObject( m_keyboard );
		}

		if( m_joysticks.size() > 0 ) 
		{
            it_joystick    = m_joysticks.begin();
            it_joystickEnd = m_joysticks.end();
            for(; it_joystick != it_joystickEnd; ++it_joystick ) {
                m_inputManager->destroyInputObject( *it_joystick );
            }

            m_joysticks.clear();
        }

		OIS::InputManager::destroyInputSystem( m_inputManager );
	}
}

void FullInputManager::capture()
{
	m_mouse->capture();
	m_keyboard->capture();

	if( m_joysticks.size() > 0 ) {
        it_joystick    = m_joysticks.begin();
        it_joystickEnd = m_joysticks.end();
        for(; it_joystick != it_joystickEnd; ++it_joystick ) {
            (*it_joystick)->capture();
        }
    }
}

bool FullInputManager::mouseMoved( const OIS::MouseEvent& e ) 
{
	return true;
}

bool FullInputManager::mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID button )
{
	return true;
}

bool FullInputManager::mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID button )
{
	return true;
}

bool FullInputManager::keyPressed( const OIS::KeyEvent& e )
{
	return true;
}

bool FullInputManager::keyReleased( const OIS::KeyEvent& e )
{
	return true;
}

bool FullInputManager::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool FullInputManager::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}
	
bool FullInputManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool FullInputManager::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool FullInputManager::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

OIS::Mouse* FullInputManager::getMouse( void ) {
    return m_mouse;
}

OIS::Keyboard* FullInputManager::getKeyboard( void ) {
    return m_keyboard;
}

OIS::JoyStick* FullInputManager::getJoystick( unsigned int index ) {
    // Make sure it's a valid index
    if( index < m_joysticks.size() ) {
        return m_joysticks[ index ];
    }

    return 0;
}

void FullInputManager::getMouseStateRelValues(double & x, double & y, double & z)
{
	x = getMouse()->getMouseState().X.rel;
	y = getMouse()->getMouseState().Y.rel;
	z = getMouse()->getMouseState().Z.rel;
}

int FullInputManager::getNumOfJoysticks( void ) {
    // Cast to keep compiler happy ^^
    return (int) m_joysticks.size();
}

void FullInputManager::getJoystickStateAxes(int index, double & leftX, double & leftY, double & rightX, double & rightY) {
	if(getNumOfJoysticks()>index)
	{
		int maxAxis = getJoystick(index)->MAX_AXIS;
		int errorBorder = maxAxis * padJoystickBorder;

		OIS::JoyStickState state = getJoystick(index)->getJoyStickState();
		
		leftX = getJoystickNormalisedAxe(state.mAxes[padLeftJoystickX].abs, maxAxis, errorBorder);
		leftY = getJoystickNormalisedAxe(state.mAxes[padLeftJoystickY].abs, maxAxis, errorBorder);
		rightX = getJoystickNormalisedAxe(state.mAxes[padRightJoystickX].abs, maxAxis, errorBorder);
		rightY = getJoystickNormalisedAxe(state.mAxes[padRightJoystickY].abs, maxAxis, errorBorder);


		//Logger::getInstance()->log("JOYSTICKS");
		//Logger::getInstance()->log("[leftX] "+Ogre::StringConverter::toString(Ogre::Real(leftX)));
		//Logger::getInstance()->log("[leftY] "+Ogre::StringConverter::toString(Ogre::Real(leftY)));
		//Logger::getInstance()->log("[rightX] "+Ogre::StringConverter::toString(Ogre::Real(rightX)));
		//Logger::getInstance()->log("[rightY] "+Ogre::StringConverter::toString(Ogre::Real(rightY)));
	}
	else
	{
		leftX = 0;
		leftY = 0;
		rightX = 0;
		rightY = 0;
	}
}

double FullInputManager::getJoystickNormalisedAxe(int axeState, int maxAxis, int border){
        double value = 0.0f;
        int absAxeState = abs(axeState);

        if (absAxeState >= border){
                value = (absAxeState - border) * (axeState < 0 ? 1.0f : -1.0f);
				value = double(value)/double(maxAxis - border);
        } 

        return value;
}


