#include "Application.h"

Application::Application()
: m_root( NULL )
, m_window( NULL )
, m_sceneManager( NULL )
, m_camera( NULL )
, m_viewport( NULL )
{
	application_started=false;
}

Application::~Application()
{
	if(application_started)
	{
		//delete memory pointers initialized after application started
		SimpleInputManager::finalise();
	}

	delete m_root;
}

void Application::initialise()
{
	//create Ogre root
	m_root = new Root( "plugins.txt", "configuration.txt", "ogre_log.txt" );

	//show Configuration dialog
	// if (!mRoot->restoreConfig() && !mRoot->showConfigDialog()) to restore last configuration
    if (!m_root->showConfigDialog())
        exit(0);

	application_started=true;

	// Create window with chosen display options.
	m_window = m_root->initialise( true, "Ogre Window" );
	m_sceneManager = m_root->createSceneManager( ST_GENERIC );
	m_camera = m_sceneManager->createCamera( "DefaultCamera" );
	m_viewport = m_window->addViewport( m_camera );
	m_viewport->setBackgroundColour( ColourValue( 0, 0, 0 ) );

	SimpleInputManager::initialise( m_window );

	defineResources();
	
	loadResources();

	createScene();

}

void Application::defineResources()
{
	//defines resources used by ResourceGroupManager using the file resources.txt

    String secName, typeName, archName;
	secName="Resources";
    ConfigFile cf;
    cf.load("resources.txt");

    ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
}

void Application::loadResources()
{
	// You can specify as many locations as you want, or have several resource groups that you
	// load/unload when you need. 
	ResourceGroupManager& resourceManager = ResourceGroupManager::getSingleton();

	//loads all resources
	resourceManager.initialiseAllResourceGroups();
}

void Application::createScene()
{
	DotSceneLoader dotSceneLoader;
	dotSceneLoader.parseDotScene("TestLevel.xml","General",m_sceneManager,m_sceneManager->getRootSceneNode(),"");

	m_cameraController = new OrbitCameraController( m_camera );
	m_cameraController->setOrientation( -45, -45 );
	m_cameraController->setDistance( 40 );
	m_cameraController->setLookAtPosition( 0, 0, 0 );
	m_camera->setNearClipDistance( 0.01 );
}

void Application::go()
{
	Ogre::Timer loopTimer;

	m_exitRequested=false;

	//initialitze application
	initialise();

	//game loop
	bool continueRunning = true;
	while ( continueRunning )
	{
		Ogre::WindowEventUtilities::messagePump();

		SimpleInputManager::capture();

		float elapsedSeconds = loopTimer.getMicroseconds() * 1.0 / 1000000;
		// Update logic stuff
		updateLogic( elapsedSeconds );

		// Update graphics stuff
		updateGraphics( elapsedSeconds );

		bool windowClosed = m_window->isClosed();
		continueRunning &= !windowClosed;

		loopTimer.reset();
		continueRunning &= m_root->renderOneFrame();

		continueRunning &= ! m_exitRequested;
	}
}

void Application::updateLogic( const float elapsedSeconds )
{


}

void Application::updateGraphics( const float elapsedSeconds )
{

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


