#include "Application.h"

#include "OrbitCameraController.h"
#include <Ogre.h>

Application::Application()
: m_root( NULL )
, m_window( NULL )
, m_sceneManager( NULL )
, m_camera( NULL )
, m_viewport( NULL )
, m_cameraController( NULL )
, m_exitRequested( false )
{

}

Application::~Application()
{
	delete m_cameraController;

	SimpleInputManager::finalise();
	delete m_root;
}

void Application::initialise()
{
	//m_root = new Ogre::Root( "ogre_plugins.txt", "ogre_configuration.txt", "ogre_log.txt" );
	m_root = new Ogre::Root();

	Ogre::ConfigFile cf;
    cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	std::string secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

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

	m_viewport->setBackgroundColour( Ogre::ColourValue( 0, 0, 0 ) );

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

	//resourceManager.addResourceLocation( "../data", "FileSystem" );
	//resourceManager.addResourceLocation( "../media", "FileSystem" );

	resourceManager.initialiseAllResourceGroups();
}

void Application::createScene()
{
	Ogre::Entity* groundEntity = m_sceneManager->createEntity( "Ground", "ground.mesh" );
	Ogre::SceneNode* groundSceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	groundSceneNode->attachObject( groundEntity );
	groundSceneNode->setScale( 500, 1, 500 );

	Ogre::ParticleSystem* particleTest = m_sceneManager->createParticleSystem("particleTest", "Examples/Smoke");
	Ogre::SceneNode* particleTestSceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	particleTestSceneNode->attachObject(particleTest);
	particleTestSceneNode->setPosition(Ogre::Vector3(0, 1, 0));
	//particleTestSceneNode->setScale(Ogre::Vector3(0.01, 0.01, 0.01));

	m_cameraController = new OrbitCameraController( m_camera );
	m_cameraController->setOrientation( -45, -15 );
	m_cameraController->setDistance( 500 );
	m_cameraController->setLookAtPosition( 0, 10, 0 );
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
		float elapsedSeconds = loopTimer.getMicroseconds() * 1.0 / 1000000;
		updateLogic( elapsedSeconds );

		// Update graphics stuff
		
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
	float distanceFactor = 0.2;
	assert( m_cameraController != NULL );

	bool leftMouseButtonPressed = e.state.buttonDown( OIS::MB_Left );
	if ( leftMouseButtonPressed )
	{
		m_cameraController->addOrientation( -e.state.X.rel, -e.state.Y.rel );
	}
	m_cameraController->addDistance( -e.state.Z.rel * distanceFactor );

	return true;
}