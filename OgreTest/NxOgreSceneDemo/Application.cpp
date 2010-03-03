#include "Application.h"

Application::Application()
{
	m_root = NULL;
	m_window = NULL;
	m_sceneMgr = NULL;
	m_viewport = NULL;
	m_camera = NULL;
	m_cameraOrbitController = NULL;
	m_character = NULL;
	
	m_NXOgreWorld = NULL;
	m_NXOgreScene = NULL;
	m_NXOgreRenderSystem = NULL;
	m_NXOgreTimeController = NULL;

	m_NXOgreVisualDebugger = NULL;
	m_NXOgreVisualDebuggerRenderable = NULL;
	m_NXOgreVisualDebuggerNode = NULL;

	m_NXOgreControllerManager = NULL;
	m_NXOgreController = NULL;
	m_NXOgreControllerRenderable = NULL;

	m_exitRequested = false;
	m_showInfo = false;
	m_showDebug = true;
}

Application::~Application()
{
	SimpleInputManager::finalise();

	delete m_NXOgreVisualDebugger;
	delete m_NXOgreControllerManager;
	delete m_cameraOrbitController;
	delete m_root;
}

bool Application::initialise()
{
	//m_root = new Ogre::Root("ogre_plugins.txt");
	m_root = new Ogre::Root();
	
	bool configDialogUserContinue = m_root->showConfigDialog();
	if ( ! configDialogUserContinue )
	{
		throw std::exception( "User closed/canceled config dialog" );
	}

	m_window = m_root->initialise(true, "NxOgre Scene Demo");

	m_sceneMgr = m_root->createSceneManager(Ogre::ST_GENERIC);
	
	loadResources();
	
	m_camera = m_sceneMgr->createCamera("Camera");

	m_cameraOrbitController = new OrbitCameraController( m_camera );
	m_cameraOrbitController->setOrientation( -45, -45 );
	m_cameraOrbitController->setDistance( 8 );
	m_cameraOrbitController->setLookAtPosition( 0, 0.5, 0 );
	m_camera->setNearClipDistance( 0.01 );

	m_viewport = m_window->addViewport(m_camera);

	m_viewport->setBackgroundColour( Ogre::ColourValue( 0.5, 0.5, 1 ) );

	SimpleInputManager::initialise(m_window);
	
	m_NXOgreWorld = NxOgre::World::createWorld();

	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = NxOgre::Vec3(0, -9.8f, 0);
	sceneDesc.mName = "NxOgreScene";

	m_NXOgreScene = m_NXOgreWorld->createScene(sceneDesc);
	
	m_NXOgreRenderSystem = new OGRE3DRenderSystem(m_NXOgreScene);

	m_NXOgreTimeController = NxOgre::TimeController::getSingleton();

	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);
	
	m_NXOgreVisualDebugger = m_NXOgreWorld->getVisualDebugger();
	m_NXOgreVisualDebuggerRenderable = new OGRE3DRenderable(NxOgre::Enums::RenderableType_VisualDebugger);
	m_NXOgreVisualDebugger->setRenderable(m_NXOgreVisualDebuggerRenderable);
	m_NXOgreVisualDebuggerNode = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
	m_NXOgreVisualDebuggerNode->attachObject(m_NXOgreVisualDebuggerRenderable);
	m_NXOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowAll);

	m_NXOgreControllerManager = new NxOgre::ControllerManager();

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

	createCharacter();

	createVolume();

	createBasicScenary();

	createTriangleMeshes();

	createConvexes();
	
	return true;
}

bool Application::createCharacter()
{
	m_character = m_sceneMgr->createEntity("ninja","ninja.mesh");
	m_idleAnimation = m_character->getAnimationState( "Idle1" );
	m_idleAnimation->setEnabled( true );
	m_runAnimation = m_character->getAnimationState( "Walk" );
	m_runAnimation->setEnabled( true );

	NxOgre::ControllerDescription desc;
	desc.mPosition.set(0,3,0);
	desc.mCallback = this;

	m_NXOgreControllerRenderable = m_NXOgreRenderSystem->createPointRenderable(m_character);
	m_NXOgreController = m_NXOgreControllerManager->createCapsuleController(desc, NxOgre::Vec2(1,3), m_NXOgreScene, m_NXOgreControllerRenderable );
	
	return true;
}

bool Application::createVolume()
{
	m_volume = m_NXOgreScene->createVolume(new NxOgre::Box(2), NxOgre::Matrix44(NxOgre::Vec3(4, 1, 4)), this, NxOgre::Enums::VolumeCollisionType_All);
	return true;
}

bool Application::createBasicScenary()
{
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 0.5, 5),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 1.5, 5),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 2.5, 5),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 3.5, 5),"cube.1m.mesh");
	m_NXOgreRenderSystem->createBody(new NxOgre::Box(1, 1, 1),NxOgre::Vec3(0, 12.5, 5),"cube.1m.mesh");

	//m_NXOgreRenderSystem->createBody(new NxOgre::Capsule(2, 4),NxOgre::Vec3(0, 25, 5),"cube.1m.mesh");

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

bool Application::createTriangleMeshes()
{
	NxOgre::Mesh* house1Mesh = NxOgre::MeshManager::getSingleton()->load("nxs:tudorhouse.nxs");
	NxOgre::TriangleGeometry* house1TriangleGeometry = new NxOgre::TriangleGeometry(house1Mesh);
	house1TriangleGeometry->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);

	m_NXOgreScene->createSceneGeometry(house1TriangleGeometry, NxOgre::Matrix44(NxOgre::Vec3(-50, 27, 8)));
	
	Ogre::Entity* house1Entity = m_sceneMgr->createEntity("house1Entity", "tudorhouse.mesh");
	Ogre::SceneNode* house1Node = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
	house1Node->attachObject(house1Entity);
	house1Node->setPosition(Ogre::Vector3(-50, 27, 8));

	NxOgre::Mesh* house2Mesh = NxOgre::MeshManager::getSingleton()->load("nxs:tudorhouse.nxs");
	NxOgre::TriangleGeometry* house2TriangleGeometry = new NxOgre::TriangleGeometry(house2Mesh);
	house2TriangleGeometry->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);

	m_NXOgreScene->createSceneGeometry(house2TriangleGeometry, NxOgre::Matrix44(NxOgre::Vec3(50, 27, 8)));
	
	Ogre::Entity* house2Entity = m_sceneMgr->createEntity("house2Entity", "tudorhouse.mesh");
	Ogre::SceneNode* house2Node = m_sceneMgr->getRootSceneNode()->createChildSceneNode();
	house2Node->attachObject(house2Entity);
	house2Node->setPosition(Ogre::Vector3(50, 27, 8));

	return true;
}

bool Application::createConvexes()
{
	NxOgre::Mesh* barrelConvexMesh = NxOgre::MeshManager::getSingleton()->load("nxs:Barrel.nxs");
	NxOgre::Convex* barrelConvex = new NxOgre::Convex(barrelConvexMesh);
	
	OGRE3DBody* barrelConvexBody = m_NXOgreRenderSystem->createBody(barrelConvex, NxOgre::Vec3(15,5,0), "Barrel.mesh");
	barrelConvexBody->setGlobalOrientation(NxOgre::Matrix33(NxOgre::Vec4(0, 45, 0, 45)));

	return true;
}

void Application::update()
{
	bool continueRunning = true;

	Ogre::Timer loopTimer;

	while (continueRunning)
	{
		Ogre::WindowEventUtilities::messagePump();

		SimpleInputManager::capture();

		float elapsedSeconds = loopTimer.getMicroseconds() * 1.0 / 1000000;

		updateLogic( elapsedSeconds );

		updateAnimations( elapsedSeconds );

		updateOverlayInfo();

		m_NXOgreVisualDebugger->draw();

		m_NXOgreVisualDebuggerNode->needUpdate();

		m_NXOgreTimeController->advance(elapsedSeconds);

		loopTimer.reset();

		bool renderFrameSuccess = m_root->renderOneFrame();

		if (!renderFrameSuccess || m_exitRequested)
		{
			continueRunning = false;
		}
	}
}

void Application::updateLogic( const float elapsedSeconds )
{
	const float TURN_DEGREES_PER_SECOND = 360;
	const float MOVEMENT_UNITS_PER_SECOND = 6;

	m_movingDirection = 0;
	
	if ( m_keyboard->isKeyDown( OIS::KC_LEFT ) )
	{
		m_NXOgreController->setDisplayYaw(m_NXOgreController->getDisplayYaw()+TURN_DEGREES_PER_SECOND * elapsedSeconds);
	}
	if ( m_keyboard->isKeyDown( OIS::KC_RIGHT ) )
	{
		m_NXOgreController->setDisplayYaw(m_NXOgreController->getDisplayYaw()-TURN_DEGREES_PER_SECOND * elapsedSeconds);
	}
	if ( m_keyboard->isKeyDown( OIS::KC_DOWN ) )
	{
		unsigned int collisionFlags;
		m_NXOgreController->move(Ogre::Quaternion(Ogre::Degree(m_NXOgreController->getDisplayYaw()), Ogre::Vector3::UNIT_Y) * Ogre::Vector3::UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds,COLLIDABLE_MASK, 0.001f, collisionFlags,1.0f);
		m_movingDirection++;
	}
	if ( m_keyboard->isKeyDown( OIS::KC_UP ) )
	{
		unsigned int collisionFlags;
		m_NXOgreController->move(Ogre::Quaternion(Ogre::Degree(m_NXOgreController->getDisplayYaw()), Ogre::Vector3::UNIT_Y) * Ogre::Vector3::NEGATIVE_UNIT_Z * MOVEMENT_UNITS_PER_SECOND * elapsedSeconds,COLLIDABLE_MASK,0.001f,collisionFlags,1.0f);
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
	if (m_showDebug)
	{
		Ogre::OverlayElement* overlay  = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelDebug");
		overlay->setCaption("Press H to hide Debug graphics");
	}
	else 
	{
		Ogre::OverlayElement* overlay  = Ogre::OverlayManager::getSingleton().getOverlayElement("InfoPanelDebug");
		overlay->setCaption("Press H to show Debug graphics");
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
	if ( e.key == OIS::KC_H )
	{
		m_showDebug = !m_showDebug;
		if(m_showDebug)
			m_NXOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowAll);
		else
			m_NXOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowNone);
	}
	return true;
}

bool Application::mouseMoved( const OIS::MouseEvent& e )
{
	assert( m_cameraOrbitController != NULL );

	bool leftMouseButtonPressed = e.state.buttonDown( OIS::MB_Left );
	if ( leftMouseButtonPressed )
	{
		m_cameraOrbitController->addOrientation( -e.state.X.rel, -e.state.Y.rel );
	}
	m_cameraOrbitController->addDistance( -e.state.Z.rel * 0.05 );

	return true;
}