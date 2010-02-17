#include "RenderSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
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

void RenderSubsystem::createViewport(OUAN::String name,OUAN::ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies)
{
	// Set the Viewport parameters
	mViewport->setBackgroundColour(colour);
	mViewport->setOverlaysEnabled(overlays);
	mViewport->setShadowsEnabled(shadows);
	mViewport->setSkiesEnabled(skies);

}

void RenderSubsystem::createOctreeSceneManager(OUAN::String name,OUAN::ColourValue ambient)
{
	try
	{
		//Set SceneManager parameters
		mSceneManager->setAmbientLight(ColourValue(0.5,0.5,0.5));
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneManager!");
	}
}

Light* RenderSubsystem::createLight(OUAN::String name,Ogre::Light::LightTypes lighttype,OUAN::ColourValue diffuse,OUAN::ColourValue specular,OUAN::Vector3 direction,bool castshadows,OUAN::Vector3 lightrange,OUAN::Vector4 attenuation,OUAN::Real power)
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
		pLight->setType(lighttype);
		pLight->setDiffuseColour(diffuse);
		pLight->setSpecularColour(specular);
		pLight->setDirection(direction);
		pLight->setCastShadows(castshadows);
		pLight->setAttenuation(attenuation.x, attenuation.y, attenuation.z, attenuation.w);
		pLight->setPowerScale(power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Light!");
	}
	return pLight;
}


Camera* RenderSubsystem::createCamera(OUAN::String name,OUAN::Vector3 position,OUAN::Quaternion orientation,OUAN::String autotracktarget,bool autoaspectratio,OUAN::Vector2 clipdistance,OUAN::Real fov,Ogre::PolygonMode polygonmode,int viewmode)
{

	SceneNode *cameraNode=0;
	Camera *pCamera=0;
	// Set light parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		pCamera->setPolygonMode(polygonmode);
		//Set Camera Parameters
		//set polygon mode
		
		pCamera->setPosition(position);
		pCamera->setOrientation(orientation);
		pCamera->setAutoAspectRatio(autoaspectratio);
		pCamera->setNearClipDistance(clipdistance.x);
		pCamera->setFarClipDistance(clipdistance.y);
		
		//set FOV
		//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
		Real AngleFOV=fov*55.0f;
		if(AngleFOV>180.0) AngleFOV=179.99;
		else if(AngleFOV<=0) AngleFOV=0.01;
		pCamera->setFOVy(Angle(AngleFOV));

		//set autotracktarget
		if(autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(autotracktarget);
			pCamera->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
	}

	return pCamera;
}

SceneNode * RenderSubsystem::createSceneNode(OUAN::String name,OUAN::String parentSceneNodeName,OUAN::Vector3 position,OUAN::Quaternion orientation,OUAN::Vector3 scale,OUAN::String autotracktarget)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneManager->getRootSceneNode();
		}
		else
		{
			pParentSceneNode = mSceneManager->getSceneNode(parentSceneNodeName);
		}

		//Create SceneNode
		sceneNode = pParentSceneNode->createChildSceneNode(name);

		//Set SceneNode parameters
		sceneNode->setPosition(position);
		sceneNode->setOrientation(orientation);
		sceneNode->setScale(scale);
		if(autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(autotracktarget);
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

Entity* RenderSubsystem::createEntity(OUAN::String name,OUAN::String meshfile,bool castshadows)
{

	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//Create meshfile
		createMeshFile(meshfile);

		//create entity and set its parameters
		pEntity = mSceneManager->createEntity(name, meshfile);
		pEntity->setCastShadows(castshadows);

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

void RenderSubsystem::createSubEntity(OUAN::String name,int num,OUAN::String material,bool visible)
{
	SubEntity *pSubEntity = 0;
	Entity *pEntity = 0;
		
	try
	{
		//get the Entity
		pEntity=mSceneManager->getEntity(name);

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

ParticleSystem* RenderSubsystem::createParticleSystem(OUAN::String name,OUAN::String particle,bool castshadows)
{
	ParticleSystem *pParticleSystem = 0;
	SceneNode *particleSystemNode = 0;
	
	try
	{
		// Create ParticleSystem
		pParticleSystem = mSceneManager->createParticleSystem(name, particle);

		// Attach ParticleSystem to SceneManager
		particleSystemNode=mSceneManager->getSceneNode(name);
		particleSystemNode->attachObject(pParticleSystem);

		// Set ParticleSystem parameters
		pParticleSystem->setCastShadows(castshadows);

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" ParticleSystem!");
	}
	return pParticleSystem;
}

void RenderSubsystem::createBillboard(OUAN::String billBoardSetName,OUAN::ColourValue colour,OUAN::Vector2 dimensions,OUAN::Vector3 position,OUAN::Real rotation,int texcoordindex,OUAN::Vector4 texrect)
{

	Billboard *pBillboard = 0;
	BillboardSet *pBillboardSet = 0;
		
	try
	{
		//get the BillboardSet
		pBillboardSet=mSceneManager->getBillboardSet(billBoardSetName);

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
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+billBoardSetName+"'s Billboard!");
	}
}

BillboardSet * RenderSubsystem::createBillboardSet(OUAN::String name,OUAN::String material,Ogre::BillboardOrigin billboardorigin,Ogre::BillboardRotationType billboardrotation,Ogre::BillboardType billboardtype,OUAN::Real defaultheight,OUAN::Real defaultwidth,bool pointrendering,OUAN::Real renderdistance,bool sorting)
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
		billBoardSet->setMaterialName(material);
		billBoardSet->setDefaultHeight(defaultheight);
		billBoardSet->setDefaultWidth(defaultwidth);
		billBoardSet->setPointRenderingEnabled(pointrendering);
		billBoardSet->setRenderingDistance(renderdistance);
		billBoardSet->setSortingEnabled(sorting);
		billBoardSet->setBillboardType(billboardtype);
		billBoardSet->setBillboardOrigin(billboardorigin);
		billBoardSet->setBillboardRotationType(billboardrotation);

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