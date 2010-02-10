#include "SimpleInputManager.h"

#include <OgreRenderWindow.h>

SimpleInputManager::SimpleInputManager()
: m_inputManager( NULL )
, m_keyboard( NULL )
, m_mouse( NULL )
{

}

SimpleInputManager::~SimpleInputManager()
{
}

void SimpleInputManager::initialise( Ogre::RenderWindow* window, bool showDefaultMousePointer )
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

	const OIS::MouseState& mouseState = m_mouse->getMouseState();

	mouseState.width = window->getWidth();
	mouseState.height = window->getHeight();

	m_mouse->setEventCallback( this );
	m_keyboard->setEventCallback( this );
}

void SimpleInputManager::finalise()
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

		OIS::InputManager::destroyInputSystem( m_inputManager );
	}
}

void SimpleInputManager::capture()
{
	m_mouse->capture();
	m_keyboard->capture();
}

bool SimpleInputManager::mouseMoved( const OIS::MouseEvent& e ) 
{
	return true;
}

bool SimpleInputManager::mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID button )
{
	return true;
}

bool SimpleInputManager::mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID button )
{
	return true;
}

bool SimpleInputManager::keyPressed( const OIS::KeyEvent& e )
{
	return true;
}

bool SimpleInputManager::keyReleased( const OIS::KeyEvent& e )
{
	return true;
}