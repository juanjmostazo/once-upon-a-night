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
	mDebugOverlay->show();
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

Ogre::Viewport* RenderSubsystem::createViewport(Ogre::String name,TRenderComponentViewportParameters TRenderComponentViewportParameters)
{
	// Set the Viewport parameters
	mViewport->setBackgroundColour(TRenderComponentViewportParameters.colour);
	mViewport->setOverlaysEnabled(TRenderComponentViewportParameters.overlays);
	mViewport->setShadowsEnabled(TRenderComponentViewportParameters.shadows);
	mViewport->setSkiesEnabled(TRenderComponentViewportParameters.skies);

	return mViewport;
}

Ogre::SceneManager * RenderSubsystem::createSceneManager(Ogre::String name,TRenderComponentSceneParameters TRenderComponentSceneParameters)
{
	try
	{
		//Set SceneManager parameters
		mSceneManager->setAmbientLight(TRenderComponentSceneParameters.ambient);
		//Create SkyBox
		createSkyBox(TRenderComponentSceneParameters.TRenderComponentSkyBoxParameters.active,
			TRenderComponentSceneParameters.TRenderComponentSkyBoxParameters.material,
			TRenderComponentSceneParameters.TRenderComponentSkyBoxParameters.distance);
		//Create SkyDome
		createSkyDome(TRenderComponentSceneParameters.TRenderComponentSkyDomeParameters.active,
			TRenderComponentSceneParameters.TRenderComponentSkyDomeParameters.material);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneManager!");
	}
	return mSceneManager;
}

Ogre::Light* RenderSubsystem::createLight(Ogre::String name,TRenderComponentLightParameters TRenderComponentLightParameters)
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
		pLight->setType(TRenderComponentLightParameters.lighttype);
		pLight->setDiffuseColour(TRenderComponentLightParameters.diffuse);
		pLight->setSpecularColour(TRenderComponentLightParameters.specular);
		pLight->setDirection(TRenderComponentLightParameters.direction);
		pLight->setCastShadows(TRenderComponentLightParameters.castshadows);
		pLight->setAttenuation(
			TRenderComponentLightParameters.attenuation.x, 
			TRenderComponentLightParameters.attenuation.y, 
			TRenderComponentLightParameters.attenuation.z, 
			TRenderComponentLightParameters.attenuation.w);

		pLight->setPowerScale(TRenderComponentLightParameters.power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Light!");
	}
	return pLight;
}


Ogre::Camera* RenderSubsystem::createCamera(Ogre::String name,TRenderComponentCameraParameters TRenderComponentCameraParameters)
{

	SceneNode *cameraNode=0;
	Camera *pCamera=0;
	// Set light parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		pCamera->setPolygonMode(TRenderComponentCameraParameters.polygonmode);
		//Set Camera Parameters
		//set polygon mode
		
		pCamera->setPosition(TRenderComponentCameraParameters.position);
		pCamera->setOrientation(TRenderComponentCameraParameters.orientation);
		pCamera->setAutoAspectRatio(TRenderComponentCameraParameters.autoaspectratio);
		pCamera->setNearClipDistance(TRenderComponentCameraParameters.clipdistance.x);
		pCamera->setFarClipDistance(TRenderComponentCameraParameters.clipdistance.y);
		
		//set FOV
		//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
		Real FOVy=TRenderComponentCameraParameters.FOVy*55.0f;
		if(FOVy>180.0) FOVy=179.99;
		else if(FOVy<=0) FOVy=0.01;
		pCamera->setFOVy(Angle(FOVy));

		//set autotracktarget
		if(TRenderComponentCameraParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(TRenderComponentCameraParameters.autotracktarget);
			pCamera->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
	}

	return pCamera;
}

Ogre::SceneNode * RenderSubsystem::createSceneNode(Ogre::String name,TRenderComponentSceneNodeParameters TRenderComponentSceneNodeParameters)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(TRenderComponentSceneNodeParameters.parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneManager->getRootSceneNode();
		}
		else
		{
			pParentSceneNode = mSceneManager->getSceneNode(TRenderComponentSceneNodeParameters.parentSceneNodeName);
		}

		//Create SceneNode
		sceneNode = pParentSceneNode->createChildSceneNode(name);

		//Set SceneNode parameters
		sceneNode->setPosition(TRenderComponentSceneNodeParameters.position);
		sceneNode->setOrientation(TRenderComponentSceneNodeParameters.orientation);
		sceneNode->setScale(TRenderComponentSceneNodeParameters.scale);
		if(TRenderComponentSceneNodeParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(TRenderComponentSceneNodeParameters.autotracktarget);
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

Ogre::Entity* RenderSubsystem::createEntity(Ogre::String name,TRenderComponentEntityParameters TRenderComponentEntityParameters)
{
	unsigned int i;
	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//Create meshfile
		createMeshFile(TRenderComponentEntityParameters.meshfile);

		//create entity and set its parameters
		pEntity = mSceneManager->createEntity(name, TRenderComponentEntityParameters.meshfile);
		pEntity->setCastShadows(TRenderComponentEntityParameters.castshadows);

		//set subentities parameters
		for(i=0;i<TRenderComponentEntityParameters.TRenderComponentSubEntityParameters.size();i++)
		{
			createSubEntity(pEntity,
				i,
				TRenderComponentEntityParameters.TRenderComponentSubEntityParameters[i].material,
				TRenderComponentEntityParameters.TRenderComponentSubEntityParameters[i].visible);
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

Ogre::ParticleSystem* RenderSubsystem::createParticleSystem(Ogre::String name,TRenderComponentParticleSystemParameters TRenderComponentParticleSystemParameters)
{
	ParticleSystem *pParticleSystem = 0;
	SceneNode *particleSystemNode = 0;
	
	try
	{
		// Create ParticleSystem
		pParticleSystem = mSceneManager->createParticleSystem(name, TRenderComponentParticleSystemParameters.particle);

		// Attach ParticleSystem to SceneManager
		particleSystemNode=mSceneManager->getSceneNode(name);
		particleSystemNode->attachObject(pParticleSystem);

		// Set ParticleSystem parameters
		pParticleSystem->setCastShadows(TRenderComponentParticleSystemParameters.castshadows);

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

Ogre::BillboardSet * RenderSubsystem::createBillboardSet(Ogre::String name,TRenderComponentBillboardSetParameters TRenderComponentBillboardSetParameters)
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
		billBoardSet->setMaterialName(TRenderComponentBillboardSetParameters.material);
		billBoardSet->setDefaultHeight(TRenderComponentBillboardSetParameters.defaultheight);
		billBoardSet->setDefaultWidth(TRenderComponentBillboardSetParameters.defaultwidth);
		billBoardSet->setPointRenderingEnabled(TRenderComponentBillboardSetParameters.pointrendering);
		billBoardSet->setRenderingDistance(TRenderComponentBillboardSetParameters.renderdistance);
		billBoardSet->setSortingEnabled(TRenderComponentBillboardSetParameters.sorting);
		billBoardSet->setBillboardType(TRenderComponentBillboardSetParameters.billboardtype);
		billBoardSet->setBillboardOrigin(TRenderComponentBillboardSetParameters.billboardorigin);
		billBoardSet->setBillboardRotationType(TRenderComponentBillboardSetParameters.billboardrotation);

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