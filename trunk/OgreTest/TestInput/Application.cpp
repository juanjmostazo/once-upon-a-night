#include "Application.h"

#include "OrbitCameraController.h"
#include <Ogre.h>

#include "tinyxml.h"
#include "cLog.h"

#include "psxpad.h"

Application::Application()
: m_root( NULL )
, m_window( NULL )
, m_sceneManager( NULL )
, m_camera( NULL )
, m_viewport( NULL )
, m_sceneNode( NULL )
, m_entity( NULL )
, m_idleAnimation( NULL )
, m_runAnimation( NULL )
, m_movingDirection( 0 )
, m_cameraController( NULL )
, m_exitRequested( false )
{

}

Application::~Application()
{
	delete m_cameraController;

	ControlInputManager::finalise();
	delete m_root;
}

void Application::initialise()
{

	//m_root = new Ogre::Root( "ogre_plugins.txt", "ogre_configuration.txt", "ogre_log.txt" );
	m_root = new Ogre::Root();

	// Initialise display options.
	// It shows the ugly dialog at start-up, so if you don't want to see it, it's up to you 
	// to remove this line and initialise display options manually ( e.g. reading them from 
	// a text file ).
	bool configDialogUserContinue = m_root->showConfigDialog();
	if ( ! configDialogUserContinue )
	{
		throw std::exception( "User closed/canceled config dialog" );
	}

	// Create window with chosen display options.
	m_window = m_root->initialise( true, "Ogre Window" );

	m_sceneManager = m_root->createSceneManager( Ogre::ST_GENERIC );

	m_camera = m_sceneManager->createCamera( "DefaultCamera" );

	m_viewport = m_window->addViewport( m_camera );

	m_viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 1 ) );

	ControlInputManager::initialise( m_window );

	loadResources();

	createScene();
}

void Application::loadResources()
{
	// You can specify as many locations as you want, or have several resource groups that you
	// load/unload when you need.
	// You may also wish to read the resource locations from a configuration file instead of
	// having them hard-coded.
	Ogre::ResourceGroupManager& resourceManager = Ogre::ResourceGroupManager::getSingleton();
	resourceManager.addResourceLocation( "../data", "FileSystem" );

	resourceManager.initialiseAllResourceGroups();
}

void Application::createScene()
{
	m_entity = m_sceneManager->createEntity( "Freddy", "freddy.mesh" );

	m_idleAnimation = m_entity->getAnimationState( "Idle" );
	m_idleAnimation->setEnabled( true );
	m_runAnimation = m_entity->getAnimationState( "Run" );
	m_runAnimation->setEnabled( true );

	m_sceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	m_sceneNode->attachObject( m_entity );

	Ogre::Entity* groundEntity = m_sceneManager->createEntity( "Ground", "ground.mesh" );
	Ogre::SceneNode* groundSceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	groundSceneNode->attachObject( groundEntity );

	groundSceneNode->setScale( 20, 1, 20 );

	m_cameraController = new OrbitCameraController( m_camera );
	m_cameraController->setOrientation( -180, -15 );
	m_cameraController->setDistance( 3 );
	m_cameraController->setLookAtPosition( 0, 1, 0 );
	m_camera->setNearClipDistance( 0.01 );
}

void Application::go()
{
	Ogre::Timer loopTimer;

	bool continueRunning = true;
	while ( continueRunning )
	{
		Ogre::WindowEventUtilities::messagePump();
		
		ControlInputManager::capture();

		// Update logic stuff
		float elapsedSeconds = loopTimer.getMicroseconds() * 1.0 / 1000000;
		updateLogic( elapsedSeconds );

		// Update graphics stuff
		updateAnimations( elapsedSeconds );
		
		bool windowClosed = m_window->isClosed();
		continueRunning &= ! windowClosed;

		loopTimer.reset();
		bool renderFrameSuccess = m_root->renderOneFrame();
		continueRunning &= renderFrameSuccess;

		continueRunning &= ! m_exitRequested;		
	}
}


void Application::updateLogic( const float elapsedSeconds )
{
	const float TURN_DEGREES_PER_SECOND = 360;
	const float MOVEMENT_UNITS_PER_SECOND = 4;

	m_movingDirection = 0;

	if ( getKeyboard()->isKeyDown( OIS::KC_LEFT ) || getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_LEFT) )
	{
		m_sceneNode->yaw( Ogre::Degree( TURN_DEGREES_PER_SECOND * elapsedSeconds ) );
	}
	if ( getKeyboard()->isKeyDown( OIS::KC_RIGHT ) || getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_RIGHT) )
	{
		m_sceneNode->yaw( Ogre::Degree( -TURN_DEGREES_PER_SECOND * elapsedSeconds ) );
	}
	if ( getKeyboard()->isKeyDown( OIS::KC_UP ) || getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_UP) )
	{
		m_sceneNode->translate( Ogre::Vector3::UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds, Ogre::Node::TS_LOCAL );
		m_movingDirection++;
	}
	if ( getKeyboard()->isKeyDown( OIS::KC_DOWN ) || getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_DOWN) )
	{
		m_sceneNode->translate( Ogre::Vector3::NEGATIVE_UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds, Ogre::Node::TS_LOCAL );
		m_movingDirection--;
	}
}


void Application::updateAnimations( const float elapsedSeconds )
{
	bool moving = ( m_movingDirection != 0 );

	if ( moving )
	{
		m_idleAnimation->setWeight( 0 );
		m_runAnimation->setWeight( 1 );
	}
	else
	{
		m_idleAnimation->setWeight( 1 );
		m_runAnimation->setWeight( 0 );
	}

	m_idleAnimation->addTime( elapsedSeconds );
	m_runAnimation->addTime( elapsedSeconds * m_movingDirection );
}


bool Application::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
	{
		m_exitRequested = true;
	}

	return true;
}

bool Application::mouseMoved( const OIS::MouseEvent& e )
{
	assert( m_cameraController != NULL );

	bool leftMouseButtonPressed = e.state.buttonDown( OIS::MB_Left );
	if ( leftMouseButtonPressed )
	{
		m_cameraController->addOrientation( -e.state.X.rel, -e.state.Y.rel );
	}
	m_cameraController->addDistance( -e.state.Z.rel * 0.002 );

	return true;
}

bool Application::buttonPressed( const OIS::JoyStickEvent& e, int button )
{
	assert( m_cameraController != NULL );

	char msg[128];
	sprintf(msg, "Button: %i, Device ID: %i", button, e.device->getID());
	cLog * log = cLog::Instance();
	log->MsgLine(msg);

	float leftX, leftY, rightX, rightY;
	getJoystickStateAxes(&leftX, &leftY, &rightX, &rightY);

	sprintf(msg, "aLeftX: %f, aLeftY: %f, aRightX: %f, aRightY: %f", leftX, leftY, rightX, rightY);
	log->MsgLine(msg);	

	return true;
}