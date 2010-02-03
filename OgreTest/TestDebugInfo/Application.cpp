#include "Application.h"

#include "OrbitCameraController.h"
#include <Ogre.h>

#define INIT_CAM_DISTANCE 5
#define INIT_CAM_Y_DEGREES -30

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

	setupCEGUI();

	setupOverlay();
}

void Application::loadResources()
{
	// You can specify as many locations as you want, or have several resource groups that you
	// load/unload when you need.
	// You may also wish to read the resource locations from a configuration file instead of
	// having them hard-coded.
	Ogre::ResourceGroupManager& resourceManager = Ogre::ResourceGroupManager::getSingleton();
	
	Ogre::String secName, typeName, archName;
	Ogre::ConfigFile cf;
    cf.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }

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
	m_cameraController->setOrientation( -180, INIT_CAM_Y_DEGREES );
	m_cameraController->setDistance( INIT_CAM_DISTANCE );
	m_cameraController->setLookAtPosition( 0, 0.5, 0 );
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
		updateAnimations( elapsedSeconds );
		
		bool windowClosed = m_window->isClosed();
		continueRunning &= ! windowClosed;

		updateStats();

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

	if ( m_keyboard->isKeyDown( OIS::KC_LEFT ) )
	{
		m_sceneNode->yaw( Ogre::Degree( -TURN_DEGREES_PER_SECOND * elapsedSeconds ) );

		Ogre::Quaternion nodeOri = m_sceneNode->getOrientation();
		m_cameraController->addOrientation(nodeOri.getYaw().valueDegrees(), nodeOri.getPitch().valueDegrees());
	}

	if ( m_keyboard->isKeyDown( OIS::KC_RIGHT ) )
	{
		m_sceneNode->yaw( Ogre::Degree( -TURN_DEGREES_PER_SECOND * elapsedSeconds ) );
		
		Ogre::Quaternion nodeOri = m_sceneNode->getOrientation();
		m_cameraController->addOrientation(nodeOri.getYaw().valueDegrees(), nodeOri.getPitch().valueDegrees());
	}

	if ( m_keyboard->isKeyDown( OIS::KC_UP ) )
	{
		m_sceneNode->translate( Ogre::Vector3::UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds, Ogre::Node::TS_LOCAL );
		m_movingDirection++;

		Ogre::Vector3 nodePos = m_sceneNode->getPosition();
		m_cameraController->setLookAtPosition(nodePos.x, nodePos.y, nodePos.z);
	}

	if ( m_keyboard->isKeyDown( OIS::KC_DOWN ) )
	{
		m_sceneNode->translate( Ogre::Vector3::NEGATIVE_UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds, Ogre::Node::TS_LOCAL );
		m_movingDirection--;		
	
		Ogre::Vector3 nodePos = m_sceneNode->getPosition();
		m_cameraController->setLookAtPosition(nodePos.x, nodePos.y, nodePos.z);
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

void Application::setupCEGUI()
{
	// CEGUI setup
	m_renderer = new CEGUI::OgreCEGUIRenderer(m_window, Ogre::RENDER_QUEUE_OVERLAY, false, 3000, m_sceneManager);
	m_system = new CEGUI::System(m_renderer);

	CEGUI::SchemeManager::getSingleton().loadScheme((CEGUI::utf8*)"TaharezLookSkin.scheme");

	m_system->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", (CEGUI::utf8*)"MouseArrow");
	m_system->setDefaultFont((CEGUI::utf8*)"BlueHighway-12");

	CEGUI::WindowManager *win = CEGUI::WindowManager::getSingletonPtr();
	CEGUI::Window *sheet = win->createWindow("DefaultGUISheet", "Sheet");

	float distanceBorder = 0.01;
	float sizeX = 0.2;
	float sizeY = 0.05;
	float posX = distanceBorder;
	float posY = distanceBorder;

	debugWindow = win->createWindow("TaharezLook/StaticText", "Widget1");
	debugWindow->setPosition(CEGUI::UVector2(CEGUI::UDim(posX, 0), CEGUI::UDim(posY, 0)));
	debugWindow->setSize(CEGUI::UVector2(CEGUI::UDim(sizeX, 0), CEGUI::UDim(sizeY, 0)));
	debugWindow->setText("Debug Info!");

	sheet->addChildWindow(debugWindow);
	m_system->setGUISheet(sheet);
}

void Application::setupOverlay()
{
	m_debugOverlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
	m_debugOverlay->show();
}

void Application::updateStats()
{
	static Ogre::String currFps = "Current FPS: ";
	static Ogre::String avgFps = "Average FPS: ";
	static Ogre::String bestFps = "Best FPS: ";
	static Ogre::String worstFps = "Worst FPS: ";
	static Ogre::String tris = "Triangle Count: ";
	static Ogre::String batches = "Batch Count: ";

	// update stats when necessary
	try {
		Ogre::OverlayElement* guiAvg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
		Ogre::OverlayElement* guiCurr = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
		Ogre::OverlayElement* guiBest = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
		Ogre::OverlayElement* guiWorst = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

		const Ogre::RenderTarget::FrameStats& stats = m_window->getStatistics();
		guiAvg->setCaption(avgFps + Ogre::StringConverter::toString(stats.avgFPS));
		guiCurr->setCaption(currFps + Ogre::StringConverter::toString(stats.lastFPS));
		guiBest->setCaption(bestFps + Ogre::StringConverter::toString(stats.bestFPS)
			+" "+Ogre::StringConverter::toString(stats.bestFrameTime)+" ms");
		guiWorst->setCaption(worstFps + Ogre::StringConverter::toString(stats.worstFPS)
			+" "+Ogre::StringConverter::toString(stats.worstFrameTime)+" ms");

		Ogre::OverlayElement* guiTris = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
		guiTris->setCaption(tris + Ogre::StringConverter::toString(stats.triangleCount));

		Ogre::OverlayElement* guiBatches = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
		guiBatches->setCaption(batches + Ogre::StringConverter::toString(stats.batchCount));

		/////////////////////////
		
		Ogre::Vector3 camPos = m_camera->getPosition();
		Ogre::Quaternion camOri = m_camera->getOrientation();
		Ogre::Vector3 freddyPos = m_sceneNode->getPosition();
		Ogre::Quaternion freddyOri = m_sceneNode->getOrientation();
		
		Ogre::OverlayElement* guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setTop(0);

		Ogre::String message = 
			"Camera Position: x: "+Ogre::StringConverter::toString(camPos.x)+", y: "+Ogre::StringConverter::toString(camPos.y)+", z:"+Ogre::StringConverter::toString(camPos.z) + "\n" + 
			"Camera orientation: yaw: "+Ogre::StringConverter::toString(camOri.getYaw())+", pitch: "+Ogre::StringConverter::toString(camOri.getPitch())+", roll:"+Ogre::StringConverter::toString(camOri.getRoll()) + "\n" + 
			"Freddy position: x: "+Ogre::StringConverter::toString(freddyPos.x)+", y: "+Ogre::StringConverter::toString(freddyPos.y)+", z:"+Ogre::StringConverter::toString(freddyPos.z) + "\n" + 
			"Freddy orientation: yaw: "+Ogre::StringConverter::toString(freddyOri.getYaw())+", pitch: "+Ogre::StringConverter::toString(freddyOri.getPitch())+", roll:"+Ogre::StringConverter::toString(freddyOri.getRoll());
		
		guiDbg->setCaption(message);
		debugWindow->setText("This is a demo!");
	}
	catch(...) { /* ignore */ }
}