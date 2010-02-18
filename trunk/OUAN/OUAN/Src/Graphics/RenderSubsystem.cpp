#include "RenderSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Physics/PhysicsSubsystem.h"
#include "CameraControllerFirstPerson.h"

using namespace OUAN;
using namespace Ogre;

RenderSubsystem::RenderSubsystem(std::string windowName)
: mWindow( NULL )
, mSceneManager( NULL )
, mCamera( NULL ) 
, mViewport( NULL )
, mWindowName(windowName)
{
}

RenderSubsystem::~RenderSubsystem()
{
}

void RenderSubsystem::initialise(ApplicationPtr app,ConfigurationPtr config)
{
	this->mApp=app;

	createRoot(config);
	defineResources(config);
	setupRenderSystem(config);
	createRenderWindow(config);
	//createVisualDebugger(config);
	initialiseResourceGroups(config);
}

void RenderSubsystem::cleanUp()
{
}

void RenderSubsystem::createRoot(ConfigurationPtr config)
{
	std::string pluginsPath=DEFAULT_OGRE_PLUGINS_PATH;
	std::string configPath=DEFAULT_OGRE_CONFIG_PATH;
	std::string logPath=DEFAULT_OGRE_LOG_PATH;
	if (config.get())
	{
		if(config->hasOption(CONFIG_KEYS_OGRE_PLUGINS_PATH))
			config->getOption(CONFIG_KEYS_OGRE_PLUGINS_PATH,pluginsPath);
		if(config->hasOption(CONFIG_KEYS_OGRE_CONFIG_PATH))
			config->getOption(CONFIG_KEYS_OGRE_CONFIG_PATH,configPath);
		if(config->hasOption(CONFIG_KEYS_OGRE_LOG_PATH))
			config->getOption(CONFIG_KEYS_OGRE_LOG_PATH,logPath);
	}
	mRoot.reset(new Ogre::Root(pluginsPath,configPath,logPath));
}

void RenderSubsystem::defineResources(ConfigurationPtr config)
{
	Ogre::String sectionName, typeName, resName;
	Ogre::ConfigFile cFile;
	std::string resourcesPath;

	if(config.get() && config->hasOption(CONFIG_KEYS_OGRE_RESOURCES_PATH))
		config->getOption(CONFIG_KEYS_OGRE_RESOURCES_PATH,resourcesPath);
	else resourcesPath=DEFAULT_OGRE_RESOURCES_PATH;

	cFile.load(resourcesPath);
	Ogre::ConfigFile::SectionIterator secIt = cFile.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		sectionName = secIt.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it=settings->begin();it!=settings->end();++it)
		{
			typeName= it->first;
			resName = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resName,typeName,sectionName);
		}
	}
}

void RenderSubsystem::setupRenderSystem(ConfigurationPtr config)
{
	//[TODO - Get rid of config dialog]
	if(!mRoot->showConfigDialog());
}

void RenderSubsystem::createRenderWindow(ConfigurationPtr config)
{
	mRoot->initialise(true,mWindowName);
	mWindow=mRoot->getAutoCreatedWindow();
}

void RenderSubsystem::createVisualDebugger(ConfigurationPtr config)
{	
	mNxOgreVisualDebugger = mApp->getPhysicsSubsystem()->getNxOgreWorld()->getVisualDebugger();
	mNxOgreVisualDebuggerRenderable = new OGRE3DRenderable(NxOgre::Enums::RenderableType_VisualDebugger);
	mNxOgreVisualDebugger->setRenderable(mNxOgreVisualDebuggerRenderable);
	mNxOgreVisualDebuggerNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	mNxOgreVisualDebuggerNode->attachObject(mNxOgreVisualDebuggerRenderable);
	mNxOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowAll);	
}

void RenderSubsystem::initialiseResourceGroups(ConfigurationPtr config)
{
	std::string mipmapNumber;
	if(config.get() && config->hasOption(CONFIG_KEYS_OGRE_DEFAULT_MIPMAPS_NUMBER))
	{
		config->getOption(CONFIG_KEYS_OGRE_DEFAULT_MIPMAPS_NUMBER,mipmapNumber);
	}
	else mipmapNumber=DEFAULT_OGRE_MIPMAPS_NUMBER;
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(DEFAULT_OGRE_MIPMAPS_NUMBER);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void RenderSubsystem::setupScene(ConfigurationPtr config)
{
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
	createCameras();
	createViewports();	
	createScene();
	createOverlays();
}
void RenderSubsystem::createCameras()
{
	mCamera= mSceneManager->createCamera(MAIN_CAMERA_NAME);
	mCamera->setNearClipDistance( 0.01 );
	mCamera->setPosition(-100,30,50);
	mCameraControllerFirstPerson = new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->initialise(mSceneManager);
	mCameraControllerFirstPerson->setCamera(mCamera);
}

void RenderSubsystem::createViewports()
{
	mViewport= mRoot->getAutoCreatedWindow()->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);
}

void RenderSubsystem::createOverlays()
{
	mDebugOverlay = Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay");
	//mDebugOverlay->show();
}

void RenderSubsystem::createScene()
{

}

RenderWindow* RenderSubsystem::getWindow() const
{
	return mWindow;
}

Camera* RenderSubsystem::getCamera() const
{
	return mCamera;
}

Viewport* RenderSubsystem::getViewport() const
{
	return mViewport;
}

CameraControllerFirstPerson* RenderSubsystem::getCameraControllerFirstPerson() const
{
	return mCameraControllerFirstPerson;
}

/// Translate/Rotate camera's position with mouse
void RenderSubsystem::moveCamera(const OIS::MouseEvent &e)
{
	mCameraControllerFirstPerson->processMouseInput(e);
}	

void RenderSubsystem::updateVisualDebugger()
{
	mNxOgreVisualDebugger->draw();
	mNxOgreVisualDebuggerNode->needUpdate();
}

bool RenderSubsystem::render()
{
	updateVisualDebugger();
	updateStats();

	return mRoot->renderOneFrame();
}

bool RenderSubsystem::isWindowClosed() const
{
	return !mWindow || mWindow->isClosed();
}

void RenderSubsystem::relativeMoveCam(const int& ratio)
{
	if(mCamera)
		mCamera->moveRelative(mTranslateVector / ratio);
}

void RenderSubsystem::updateCameraParams(float elapsedTime)
{
	mMoveScale = mMoveSpeed   * elapsedTime;
	mRotScale  = mRotateSpeed * elapsedTime;
	mTranslateVector = Ogre::Vector3::ZERO;

	mCameraControllerFirstPerson->processKeyboardInput(mApp->getKeyboard(),elapsedTime);
}

void RenderSubsystem::translateCam(const TCoordinateAxis& coordAxis)
{
	Vector3 axisVector;
	switch(coordAxis)
	{
		case AXIS_NEG_X: axisVector=Ogre::Vector3::NEGATIVE_UNIT_X;
			break;
		case AXIS_POS_X: axisVector=Ogre::Vector3::UNIT_X;
			break;
		case AXIS_NEG_Z: axisVector=Ogre::Vector3::NEGATIVE_UNIT_Z;
			break;
		case AXIS_POS_Z: axisVector=Ogre::Vector3::UNIT_Z;
			break;
		case AXIS_NEG_Y: axisVector=Ogre::Vector3::NEGATIVE_UNIT_Y;
			break;
		case AXIS_POS_Y: axisVector=Ogre::Vector3::UNIT_Y;
			break;
		default:break;
	}
	mTranslateVector=mMoveScale*axisVector;
}

Ogre::SceneManager* RenderSubsystem::getSceneManager() const
{
	return mSceneManager;
}

Ogre::Viewport* RenderSubsystem::createViewport(Ogre::String name,TViewportRenderParameters tViewportRenderParameters)
{
	// Set the Viewport parameters
	mViewport->setBackgroundColour(tViewportRenderParameters.colour);
	mViewport->setOverlaysEnabled(tViewportRenderParameters.overlays);
	mViewport->setShadowsEnabled(tViewportRenderParameters.shadows);
	mViewport->setSkiesEnabled(tViewportRenderParameters.skies);

	return mViewport;
}

Ogre::SceneManager * RenderSubsystem::createSceneManager(Ogre::String name,TSceneManagerRenderParameters tSceneManagerRenderParameters)
{
	try
	{
		//Set SceneManager parameters
		mSceneManager->setAmbientLight(tSceneManagerRenderParameters.ambient);
		//Create SkyBox
		createSkyBox(tSceneManagerRenderParameters.tSkyBoxRenderParameters.active,
			tSceneManagerRenderParameters.tSkyBoxRenderParameters.material,
			tSceneManagerRenderParameters.tSkyBoxRenderParameters.distance);
		//Create SkyDome
		createSkyDome(tSceneManagerRenderParameters.tSkyDomeRenderParameters.active,
			tSceneManagerRenderParameters.tSkyDomeRenderParameters.material);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneManager!");
	}
	return mSceneManager;
}

Ogre::Light* RenderSubsystem::createLight(Ogre::String name,TLightRenderParameters tLightRenderParameters)
{
	SceneNode *lightNode=0;
	Light *pLight=0;
	// Set light parameters and create it
	try
	{
		// Create the light
		pLight = mSceneManager->createLight(name);

		// Attach to Scene Manager
		lightNode=mSceneManager->getSceneNode(name);
		lightNode->attachObject(pLight);

		//Set Light Parameters
		pLight->setType(tLightRenderParameters.lighttype);
		pLight->setDiffuseColour(tLightRenderParameters.diffuse);
		pLight->setSpecularColour(tLightRenderParameters.specular);
		pLight->setDirection(tLightRenderParameters.direction);
		pLight->setCastShadows(tLightRenderParameters.castshadows);
		pLight->setAttenuation(
			tLightRenderParameters.attenuation.x, 
			tLightRenderParameters.attenuation.y, 
			tLightRenderParameters.attenuation.z, 
			tLightRenderParameters.attenuation.w);

		pLight->setPowerScale(tLightRenderParameters.power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Light!");
	}
	return pLight;
}


Ogre::Camera* RenderSubsystem::createCamera(Ogre::String name,TCameraRenderParameters tCameraRenderParameters)
{

	SceneNode *cameraNode=0;
	Camera *pCamera=0;
	// Set light parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		pCamera->setPolygonMode(tCameraRenderParameters.polygonmode);
		//Set Camera Parameters
		//set polygon mode
		
		pCamera->setPosition(tCameraRenderParameters.position);
		pCamera->setOrientation(tCameraRenderParameters.orientation);
		pCamera->setAutoAspectRatio(tCameraRenderParameters.autoaspectratio);
		pCamera->setNearClipDistance(tCameraRenderParameters.clipdistance.x);
		pCamera->setFarClipDistance(tCameraRenderParameters.clipdistance.y);
		
		//set FOV
		//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
		Real FOVy=tCameraRenderParameters.FOVy*55.0f;
		if(FOVy>180.0) FOVy=179.99;
		else if(FOVy<=0) FOVy=0.01;
		pCamera->setFOVy(Angle(FOVy));

		//set autotracktarget
		if(tCameraRenderParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(tCameraRenderParameters.autotracktarget);
			pCamera->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
	}

	return pCamera;
}

Ogre::SceneNode * RenderSubsystem::createSceneNode(Ogre::String name,TSceneNodeRenderParameters tSceneNodeRenderParameters)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(tSceneNodeRenderParameters.parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneManager->getRootSceneNode();
		}
		else
		{
			pParentSceneNode = mSceneManager->getSceneNode(tSceneNodeRenderParameters.parentSceneNodeName);
		}

		//Create SceneNode
		sceneNode = pParentSceneNode->createChildSceneNode(name);

		//Set SceneNode parameters
		sceneNode->setPosition(tSceneNodeRenderParameters.position);
		sceneNode->setOrientation(tSceneNodeRenderParameters.orientation);
		sceneNode->setScale(tSceneNodeRenderParameters.scale);
		if(tSceneNodeRenderParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(tSceneNodeRenderParameters.autotracktarget);
			sceneNode->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneNode!");
	}
	return sceneNode;
}

void RenderSubsystem::createMeshFile(OUAN::String meshfile)
{
	try
	{
		//Create the mesh file
		if (!MeshManager::getSingleton().resourceExists(meshfile))
		{
			//LogManager::getSingleton().logMessage("[LevelLoader] creating "+meshfile+" meshfile");
			MeshManager::getSingleton().load(meshfile,"General");
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+meshfile+" mesh!");
	}
}

Ogre::Entity* RenderSubsystem::createEntity(Ogre::String name,TEntityRenderParameters tEntityRenderParameters)
{
	unsigned int i;
	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//Create meshfile
		createMeshFile(tEntityRenderParameters.meshfile);

		//create entity and set its parameters
		pEntity = mSceneManager->createEntity(name, tEntityRenderParameters.meshfile);
		pEntity->setCastShadows(tEntityRenderParameters.castshadows);

		//set subentities parameters
		for(i=0;i<tEntityRenderParameters.tSubEntityRenderParameters.size();i++)
		{
			createSubEntity(pEntity,
				i,
				tEntityRenderParameters.tSubEntityRenderParameters[i].material,
				tEntityRenderParameters.tSubEntityRenderParameters[i].visible);
		}

		//attach to Scene Manager
		pEntityNode=mSceneManager->getSceneNode(name);
		pEntityNode->attachObject(pEntity);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Entity!");
	}
	return pEntity;
}

void RenderSubsystem::createSubEntity(Ogre::Entity *pEntity,int num,OUAN::String material,bool visible)
{
	SubEntity *pSubEntity = 0;
		
	try
	{
		//get the SubEntity
		pSubEntity=pEntity->getSubEntity(num);

		//set SubEntity attributes
		pSubEntity->setMaterialName(material);
		pSubEntity->setVisible(visible);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+pEntity->getName()+"'s SubEntity #"+StringConverter::toString(num)+"!");
	}
}

Ogre::ParticleSystem* RenderSubsystem::createParticleSystem(Ogre::String name,TParticleSystemRenderParameters tParticleSystemRenderParameters)
{
	ParticleSystem *pParticleSystem = 0;
	SceneNode *particleSystemNode = 0;
	
	try
	{
		// Create ParticleSystem
		pParticleSystem = mSceneManager->createParticleSystem(name, tParticleSystemRenderParameters.particle);

		// Attach ParticleSystem to SceneManager
		particleSystemNode=mSceneManager->getSceneNode(name);
		particleSystemNode->attachObject(pParticleSystem);

		// Set ParticleSystem parameters
		pParticleSystem->setCastShadows(tParticleSystemRenderParameters.castshadows);

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" ParticleSystem!");
	}
	return pParticleSystem;
}

void RenderSubsystem::createBillboard(Ogre::BillboardSet * pBillboardSet,OUAN::ColourValue colour,OUAN::Vector2 dimensions,OUAN::Vector3 position,OUAN::Real rotation,int texcoordindex,OUAN::Vector4 texrect)
{
	Billboard *pBillboard = 0;
		
	try
	{
		//create Billboard
		pBillboard = pBillboardSet->createBillboard(position);

		//set Billboard attributes
		pBillboard->setColour(colour);
		pBillboard->setDimensions(dimensions.x,dimensions.y);
		pBillboard->setRotation(Angle(rotation));
		pBillboard->setTexcoordIndex(texcoordindex);
		pBillboard->setTexcoordRect(texrect.x,texrect.y,texrect.z,texrect.w);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+pBillboardSet->getName()+"'s Billboard!");
	}
}

Ogre::BillboardSet * RenderSubsystem::createBillboardSet(Ogre::String name,TBillboardSetRenderParameters tBillboardSetRenderParameters)
{
	BillboardSet *billBoardSet = 0;
	SceneNode *billBoardSetNode = 0;
	try
	{
		//Create BillboardSet
		billBoardSet = mSceneManager->createBillboardSet(name);

		//Attach BillboardSet to SceneNode
		billBoardSetNode = mSceneManager->getSceneNode(name);
		billBoardSetNode->attachObject(billBoardSet);

		//Set BillboardSet Attributes
		billBoardSet->setMaterialName(tBillboardSetRenderParameters.material);
		billBoardSet->setDefaultHeight(tBillboardSetRenderParameters.defaultheight);
		billBoardSet->setDefaultWidth(tBillboardSetRenderParameters.defaultwidth);
		billBoardSet->setPointRenderingEnabled(tBillboardSetRenderParameters.pointrendering);
		billBoardSet->setRenderingDistance(tBillboardSetRenderParameters.renderdistance);
		billBoardSet->setSortingEnabled(tBillboardSetRenderParameters.sorting);
		billBoardSet->setBillboardType(tBillboardSetRenderParameters.billboardtype);
		billBoardSet->setBillboardOrigin(tBillboardSetRenderParameters.billboardorigin);
		billBoardSet->setBillboardRotationType(tBillboardSetRenderParameters.billboardrotation);

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" BillboardSet!");
	}
	return billBoardSet;
}

void RenderSubsystem::createSkyBox(bool active, OUAN::String material, OUAN::Real distance)
{
	try
	{
		// Setup the sky box
		mSceneManager->setSkyBox(active, material, distance);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating SkyBox!");
	}
}

void RenderSubsystem::createSkyDome(bool active, OUAN::String material)
{
	try
	{
		// Setup the sky box
		mSceneManager->setSkyDome(active,material);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating SkyDome!");
	}
}

void RenderSubsystem::updateStats()
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

		const Ogre::RenderTarget::FrameStats& stats = mWindow->getStatistics();
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

		Ogre::OverlayElement* guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setTop(0);
		/*
		Ogre::String message = 
			"Camera Position: x: "+Ogre::StringConverter::toString(camPos.x)+", y: "+Ogre::StringConverter::toString(camPos.y)+", z:"+Ogre::StringConverter::toString(camPos.z) + "\n" + 
			"Camera orientation: yaw: "+Ogre::StringConverter::toString(camOri.getYaw())+", pitch: "+Ogre::StringConverter::toString(camOri.getPitch())+", roll:"+Ogre::StringConverter::toString(camOri.getRoll()) + "\n" + 
			"Freddy position: x: "+Ogre::StringConverter::toString(freddyPos.x)+", y: "+Ogre::StringConverter::toString(freddyPos.y)+", z:"+Ogre::StringConverter::toString(freddyPos.z) + "\n" + 
			"Freddy orientation: yaw: "+Ogre::StringConverter::toString(freddyOri.getYaw())+", pitch: "+Ogre::StringConverter::toString(freddyOri.getPitch())+", roll:"+Ogre::StringConverter::toString(freddyOri.getRoll());
		*/
		guiDbg->setCaption("Test Test Test");

	}
	catch(...) { /* ignore */ }
}