#include "FullInputManager.h"
#include <OgreRenderWindow.h>
#include <math.h>

FullInputManager::FullInputManager()
: m_inputManager( NULL )
, m_keyboard( NULL )
, m_mouse( NULL )
{

}

FullInputManager::~FullInputManager()
{
}

void FullInputManager::initialise( Ogre::RenderWindow* window, bool showDefaultMousePointer )
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

void FullInputManager::getMouseStateRelValues(float* x, float* y, float* z)
{
	*x = getMouse()->getMouseState().X.rel;
	*y = getMouse()->getMouseState().Y.rel;
	*z = getMouse()->getMouseState().Z.rel;
}

int FullInputManager::getNumOfJoysticks( void ) {
    // Cast to keep compiler happy ^^
    return (int) m_joysticks.size();
}

void FullInputManager::getJoystickStateAxes(unsigned int index, float* leftX, float* leftY, float* rightX, float* rightY){
	int maxAxis = getJoystick(index)->MAX_AXIS;
	int errorBorder = maxAxis / 4; //25%
	OIS::JoyStickState state = getJoystick(index)->getJoyStickState();
	
	*leftX = getJoystickNormalisedAxe(state.mAxes[0].abs, maxAxis, errorBorder);
	*leftY = getJoystickNormalisedAxe(state.mAxes[1].abs, maxAxis, errorBorder);
	*rightX = getJoystickNormalisedAxe(state.mAxes[2].abs, maxAxis, errorBorder);
	*rightY = getJoystickNormalisedAxe(state.mAxes[3].abs, maxAxis, errorBorder);
}

float FullInputManager::getJoystickNormalisedAxe(int axeState, int maxAxis, int border){
	float value = 0.0f;
	float scaleValue = ((float)maxAxis - (float)border) / (float)maxAxis;
	int absAxeState = abs(axeState);

	if (absAxeState >= border){
		value = (absAxeState - border) * scaleValue * (axeState < 0 ? 1.0f : -1.0f);
	} 

	return value;
}

