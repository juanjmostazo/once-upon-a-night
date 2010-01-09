#include "Application.h"

#include <Ogre.h>

Application::Application()
: m_root( NULL )
, m_window( NULL )
, m_sceneManager( NULL )
, m_camera( NULL )
, m_viewport( NULL )
, m_sceneNode( NULL )
, m_entity( NULL )
, m_exitRequested( false )
{

}

Application::~Application()
{
	SimpleInputManager::finalise();
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

	SimpleInputManager::initialise( m_window );

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

	m_sceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	m_sceneNode->attachObject( m_entity );

	m_camera->setPosition( -2, 2, 2 );
	m_camera->lookAt( 0, 0.5, 0 );
	m_camera->setNearClipDistance( 0.01 );
}

void Application::go()
{
	Ogre::Timer loopTimer;

	bool continueRunning = true;
	while ( continueRunning )
	{
		Ogre::WindowEventUtilities::messagePump();
		
		SimpleInputManager::capture();

		// Update logic stuff

		// Update graphics stuff
		
		bool windowClosed = m_window->isClosed();
		continueRunning &= ! windowClosed;

		loopTimer.reset();
		bool renderFrameSuccess = m_root->renderOneFrame();
		continueRunning &= renderFrameSuccess;

		continueRunning &= ! m_exitRequested;		
	}
}

bool Application::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
	{
		m_exitRequested = true;
	}
	return true;
}
