#include "RenderSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Physics/PhysicsSubsystem.h"
#include "CameraControllerFirstPerson.h"

#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentSceneNode.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"

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
	this->debugMessage = "";

	createRoot(config);
	defineResources(config);
	setupRenderSystem(config);
	createRenderWindow(config);
	initialiseResourceGroups(config);
	defaultSetupScene(config);
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
	mNxOgreVisualDebugger->setVisualisationMode(mApp->getDebugMode()!=DEBUGMODE_NONE?
		NxOgre::Enums::VisualDebugger_ShowAll:
		NxOgre::Enums::VisualDebugger_ShowNone);	
}

void RenderSubsystem::createDebugFloor(ConfigurationPtr config)
{
	//Initializing main floor
	Ogre::Plane *plane = new Ogre::Plane;
	plane->normal = Ogre::Vector3::UNIT_Y;
	plane->d = 0;

	Ogre::MeshManager::getSingleton().createPlane("debugFloorPlane",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, *plane,
		200, 200, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneManager->createEntity("debugFloorEntity", "debugFloorPlane");
	pPlaneEnt->setCastShadows(false);
	pPlaneEnt->setMaterialName("GrassFloor");
	mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(pPlaneEnt);
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

void RenderSubsystem::defaultSetupScene(ConfigurationPtr config)
{
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
	createCameras();
	createViewports();	
	createScene();
	//createOverlays();
}
void RenderSubsystem::createCameras()
{
	mCamera= mSceneManager->createCamera(MAIN_CAMERA_NAME);
	mCamera->setNearClipDistance( 0.01 );
	mCamera->setPosition(0,30,50);
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
	//Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay")->show();
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

Ogre::Viewport* RenderSubsystem::createViewport(Ogre::String name,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	// Set the Viewport parameters
	mViewport->setBackgroundColour(tRenderComponentViewportParameters.colour);
	mViewport->setOverlaysEnabled(tRenderComponentViewportParameters.overlays);
	mViewport->setShadowsEnabled(tRenderComponentViewportParameters.shadows);
	mViewport->setSkiesEnabled(tRenderComponentViewportParameters.skies);

	return mViewport;
}

Ogre::SceneManager * RenderSubsystem::createSceneManager(Ogre::String name,TRenderComponentSceneParameters tRenderComponentSceneParameters)
{
	try
	{
		//Set SceneManager parameters
		mSceneManager->setAmbientLight(tRenderComponentSceneParameters.ambient);
		//Create SkyBox
		createSkyBox(tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.active,
			tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.material,
			tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.distance);
		//Create SkyDome
		createSkyDome(tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.active,
			tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.material);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneManager!");
	}
	return mSceneManager;
}

Ogre::Light* RenderSubsystem::createLight(Ogre::String name,TRenderComponentLightParameters tRenderComponentLightParameters)
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
		pLight->setType(tRenderComponentLightParameters.lighttype);
		pLight->setDiffuseColour(tRenderComponentLightParameters.diffuse);
		pLight->setSpecularColour(tRenderComponentLightParameters.specular);
		pLight->setDirection(tRenderComponentLightParameters.direction);
		pLight->setCastShadows(tRenderComponentLightParameters.castshadows);
		pLight->setAttenuation(
			tRenderComponentLightParameters.attenuation.x, 
			tRenderComponentLightParameters.attenuation.y, 
			tRenderComponentLightParameters.attenuation.z, 
			tRenderComponentLightParameters.attenuation.w);

		pLight->setPowerScale(tRenderComponentLightParameters.power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Light!");
	}
	return pLight;
}


Ogre::Camera* RenderSubsystem::createCamera(Ogre::String name,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{

	SceneNode *cameraNode=0;
	Camera *pCamera=0;
	// Set light parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		pCamera->setPolygonMode(tRenderComponentCameraParameters.polygonmode);
		//Set Camera Parameters
		//set polygon mode
		
		pCamera->setPosition(tRenderComponentCameraParameters.position);
		pCamera->setOrientation(tRenderComponentCameraParameters.orientation);
		pCamera->setAutoAspectRatio(tRenderComponentCameraParameters.autoaspectratio);
		pCamera->setNearClipDistance(tRenderComponentCameraParameters.clipdistance.x);
		pCamera->setFarClipDistance(tRenderComponentCameraParameters.clipdistance.y);
		
		//set FOV
		//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
		Real FOVy=tRenderComponentCameraParameters.FOVy*55.0f;
		if(FOVy>180.0) FOVy=179.99;
		else if(FOVy<=0) FOVy=0.01;
		pCamera->setFOVy(Angle(FOVy));

		//set autotracktarget
		if(tRenderComponentCameraParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(tRenderComponentCameraParameters.autotracktarget);
			pCamera->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
	}

	return pCamera;
}

Ogre::SceneNode * RenderSubsystem::createSceneNode(Ogre::String name,TRenderComponentSceneNodeParameters tRenderComponentSceneNodeParameters)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(tRenderComponentSceneNodeParameters.parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneManager->getRootSceneNode();
		}
		else
		{
			pParentSceneNode = mSceneManager->getSceneNode(tRenderComponentSceneNodeParameters.parentSceneNodeName);
		}

		//Create SceneNode
		sceneNode = pParentSceneNode->createChildSceneNode(name);

		//Set SceneNode parameters
		sceneNode->setPosition(tRenderComponentSceneNodeParameters.position);
		sceneNode->setOrientation(tRenderComponentSceneNodeParameters.orientation);
		sceneNode->setScale(tRenderComponentSceneNodeParameters.scale);
		if(tRenderComponentSceneNodeParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(tRenderComponentSceneNodeParameters.autotracktarget);
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

Ogre::Entity* RenderSubsystem::createEntity(Ogre::String name,TRenderComponentEntityParameters tRenderComponentEntityParameters)
{
	unsigned int i;
	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//Create meshfile
		createMeshFile(tRenderComponentEntityParameters.meshfile);

		//create entity and set its parameters
		pEntity = mSceneManager->createEntity(name, tRenderComponentEntityParameters.meshfile);
		pEntity->setCastShadows(tRenderComponentEntityParameters.castshadows);

		//set subentities parameters
		for(i=0;i<tRenderComponentEntityParameters.tRenderComponentSubEntityParameters.size();i++)
		{
			createSubEntity(pEntity,
				i,
				tRenderComponentEntityParameters.tRenderComponentSubEntityParameters[i].material,
				tRenderComponentEntityParameters.tRenderComponentSubEntityParameters[i].visible);
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

Ogre::ParticleSystem* RenderSubsystem::createParticleSystem(Ogre::String name,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters)
{
	ParticleSystem *pParticleSystem = 0;
	SceneNode *particleSystemNode = 0;
	
	try
	{
		// Create ParticleSystem
		pParticleSystem = mSceneManager->createParticleSystem(name, tRenderComponentParticleSystemParameters.particle);

		// Attach ParticleSystem to SceneManager
		particleSystemNode=mSceneManager->getSceneNode(name);
		particleSystemNode->attachObject(pParticleSystem);

		// Set ParticleSystem parameters
		pParticleSystem->setCastShadows(tRenderComponentParticleSystemParameters.castshadows);

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

Ogre::BillboardSet * RenderSubsystem::createBillboardSet(Ogre::String name,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters)
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
		billBoardSet->setMaterialName(tRenderComponentBillboardSetParameters.material);
		billBoardSet->setDefaultHeight(tRenderComponentBillboardSetParameters.defaultheight);
		billBoardSet->setDefaultWidth(tRenderComponentBillboardSetParameters.defaultwidth);
		billBoardSet->setPointRenderingEnabled(tRenderComponentBillboardSetParameters.pointrendering);
		billBoardSet->setRenderingDistance(tRenderComponentBillboardSetParameters.renderdistance);
		billBoardSet->setSortingEnabled(tRenderComponentBillboardSetParameters.sorting);
		billBoardSet->setBillboardType(tRenderComponentBillboardSetParameters.billboardtype);
		billBoardSet->setBillboardOrigin(tRenderComponentBillboardSetParameters.billboardorigin);
		billBoardSet->setBillboardRotationType(tRenderComponentBillboardSetParameters.billboardrotation);

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

Ogre::String RenderSubsystem::getDebugMessage()
{
	return debugMessage;
}

void RenderSubsystem::setDebugMessage(Ogre::String debugMessage)
{
	this->debugMessage = debugMessage;
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
	}
	catch(...) { /* ignore */ }
}

void RenderSubsystem::updateDebugInfo()
{
	try {
		Ogre::OverlayElement* guiDbg = Ogre::OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
		guiDbg->setTop(0);
		//Ogre::StringConverter::toString(x);
		guiDbg->setCaption(debugMessage);
	}
	catch(...) { /* ignore */ }
}

void RenderSubsystem::showDebugOverlay()
{
	Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay")->show();
}
void RenderSubsystem::hideDebugOverlay()
{
	Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay")->hide();
}
void RenderSubsystem::showVisualDebugger()
{
	if (mNxOgreVisualDebugger)
		mNxOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowAll);		
}
void RenderSubsystem::hideVisualDebugger()
{
	if (mNxOgreVisualDebugger)
		mNxOgreVisualDebugger->setVisualisationMode(NxOgre::Enums::VisualDebugger_ShowNone);		
}