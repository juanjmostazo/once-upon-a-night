#include "Application.h"

Application::Application()
{
	m_root = NULL;
	m_window = NULL;
	m_sceneMgr = NULL;
	m_viewport = NULL;
	m_camera = NULL;

	m_NXOgreWorld = NULL;
	m_NXOgreScene = NULL;
	m_NXOgreRenderSystem = NULL;
	m_NXOgreTimeController = NULL;

	m_exitRequested = false;
	m_showInfo = false;
}

Application::~Application()
{
	SimpleInputManager::finalise();
	delete m_root;
}

bool Application::initialise()
{
	//m_root = new Ogre::Root("ogre_plugins.txt", "ogre_config.txt", "ogre_log.txt");
	m_root = new Ogre::Root();
	
	bool configDialogUserContinue = m_root->showConfigDialog();
	if ( ! configDialogUserContinue )
	{
		throw std::exception( "User closed/canceled config dialog" );
	}

	m_window = m_root->initialise(true, "NxOgre Basic Demo");

	m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC);
	
	loadResources();
	
	m_camera = m_sceneMgr->createCamera("FixedCamera");
	m_camera->setNearClipDistance(0.1f);
	m_camera->setPosition(Ogre::Vector3(0, 5, 20));

	m_viewport = m_window->addViewport(m_camera);
    
	SimpleInputManager::initialise(m_window);
	
	m_NXOgreWorld = NxOgre::World::createWorld();

	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = NxOgre::Vec3(0, -9.8f, 0);
	sceneDesc.mName = "NxOgreScene";

	m_NXOgreScene = m_NXOgreWorld->createScene(sceneDesc);
	
	m_NXOgreRenderSystem = new OGRE3DRenderSystem(m_NXOgreScene);

	m_NXOgreTimeController = NxOgre::TimeController::getSingleton();	
	
	return true;
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

bool Application::setup()
{
	Ogre::OverlayManager::getSingleton().getByName("InfoPanel")->show();

	m_NXOgreScene->getMaterial(0)->setStaticFriction(0.5);
	m_NXOgreScene->getMaterial(0)->setDynamicFriction(0.5);
	m_NXOgreScene->getMaterial(0)->setRestitution(0.1);

	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 20, 0),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(-1, 30, 0),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 25, 0),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(5, 20, 0),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(-5, 20, 0),"cube.1m.mesh");
	
	m_NXOgreScene->createSceneGeometry(new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0)), Matrix44_Identity);
	
	Ogre::Plane *plane = new Ogre::Plane;
	plane->normal = Ogre::Vector3::UNIT_Y;
	plane->d = 0;

	Ogre::MeshManager::getSingleton().createPlane("ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *plane,
		150, 150, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = m_sceneMgr->createEntity("groundInstance", "ground");
	pPlaneEnt->setCastShadows(false);
	pPlaneEnt->setMaterialName("Examples/GrassFloor");
	m_sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(pPlaneEnt);
	
	return true;
}

void Application::update()
{
	Ogre::Timer loopTimer;

	bool continueRunning = true;
	
	while (continueRunning)
	{
		Ogre::WindowEventUtilities::messagePump();

		SimpleInputManager::capture();
		
		float elapsedSeconds = loopTimer.getMicroseconds() * 1.0 / 1000000;

		m_NXOgreTimeController->advance(elapsedSeconds);
	
		loopTimer.reset();

		updateOverlayInfo();

		bool renderFrameSuccess = m_root->renderOneFrame();
		
		if (!renderFrameSuccess || m_exitRequested)
		{
			continueRunning = false;
		}
	}
}

void Application::updateOverlayInfo()
{
	if (m_showInfo)
	{
		Ogre::OverlayElement* overlay  = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelFps");
		overlay->setCaption("Current FPS: "+Ogre::StringConverter::toString(m_window->getLastFPS()));
		overlay = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelNTriangles");
		overlay->setCaption("Triangle count: "+Ogre::StringConverter::toString(m_window->getTriangleCount()));
	}
	else 
	{
		Ogre::OverlayElement* overlay  = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelFps");
		overlay->setCaption("Press I to view Statistics");
		overlay = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelNTriangles");
		overlay->setCaption("");
	}
}

bool Application::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
	{
		m_exitRequested = true;
	}
	if ( e.key == OIS::KC_I )
	{
		m_showInfo = !m_showInfo;
	}
	
	return true;
}

bool Application::mouseMoved( const OIS::MouseEvent& e )
{
	return true;
}