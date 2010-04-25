#include "RenderSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Physics/PhysicsSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "CameraManager/CameraManager.h"
#include "CameraManager/CameraControllerFirstPerson.h"
#include "TrajectoryManager/TrajectoryManager.h"
#include "RenderComponent/RenderComponent.h"
#include "RenderComponent/RenderComponentBillboardSet.h"
#include "RenderComponent/RenderComponentCamera.h"
#include "RenderComponent/RenderComponentEntity.h"
#include "RenderComponent/RenderComponentLight.h"
#include "RenderComponent/RenderComponentParticleSystem.h"
#include "RenderComponent/RenderComponentScene.h"
#include "RenderComponent/RenderComponentPositional.h"
#include "RenderComponent/RenderComponentViewport.h"
#include "RenderComponent/RenderComponentDecal.h"

using namespace OUAN;
using namespace Ogre;

RenderSubsystem::RenderSubsystem(std::string windowName)
: mWindow( NULL )
, mWindowName(windowName)
{
	
}

RenderSubsystem::~RenderSubsystem()
{

}

void RenderSubsystem::init(ApplicationPtr app,ConfigurationPtr config)
{
	this->mApp=app;
	this->debugMessage = "";

	createRoot(config);
	defineResources(config);
	setupRenderSystem(config);
	createRenderWindow(config);
	initResourceGroups(config);

	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
}

void RenderSubsystem::cleanUp()
{
	clearScene();
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

RootPtr RenderSubsystem::getRoot() const
{
	return mRoot;
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
	if(!mRoot->showConfigDialog()){
		mApp->mExitRequested=true;
	}
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
		1000, 1000, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneManager->createEntity("debugFloorEntity", "debugFloorPlane");
	pPlaneEnt->setCastShadows(false);
	pPlaneEnt->setMaterialName("GrassFloor");
	SceneNode * pPlaneNode = mSceneManager->getRootSceneNode()->createChildSceneNode();
	pPlaneNode->attachObject(pPlaneEnt);
}

void RenderSubsystem::initResourceGroups(ConfigurationPtr config)
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

void RenderSubsystem::createOverlays()
{
	//Ogre::OverlayManager::getSingleton().getByName("Core/DebugOverlay")->show();
}

void RenderSubsystem::clear()
{
	/// Clear Scene manager
	mSceneManager->clearScene();
}

RenderWindow* RenderSubsystem::getWindow() const
{
	return mWindow;
}

//CameraControllerFirstPerson* RenderSubsystem::getCameraControllerFirstPerson() const
//{
//	return mCameraControllerFirstPerson;
//}


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

//void RenderSubsystem::translateCamera(TCoordinateAxis worldCoordinateAxis)
//{
//	Ogre::Vector3 unitTranslationVector;
//	switch (worldCoordinateAxis)
//	{
//		case AXIS_NEG_X:
//			unitTranslationVector=Ogre::Vector3::NEGATIVE_UNIT_X;
//			break;
//		case AXIS_POS_X:
//			unitTranslationVector=Ogre::Vector3::UNIT_X;
//			break;
//		case AXIS_NEG_Z:
//			unitTranslationVector=Ogre::Vector3::NEGATIVE_UNIT_Z;
//			break;
//		case AXIS_POS_Z:
//			unitTranslationVector=Ogre::Vector3::UNIT_Z;
//			break;
//		case AXIS_NEG_Y:
//			unitTranslationVector=Ogre::Vector3::NEGATIVE_UNIT_Y;
//			break;
//		case AXIS_POS_Y:
//			unitTranslationVector=Ogre::Vector3::UNIT_Y;
//			break;
//	}
//	mCameraManager->processSimpleTranslation(unitTranslationVector);
//}

Ogre::SceneManager* RenderSubsystem::getSceneManager() const
{
	return mSceneManager;
}

Ogre::SceneManager * RenderSubsystem::setSceneParameters(Ogre::String name,TRenderComponentSceneParameters tRenderComponentSceneParameters)
{
	try
	{

		mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

		//Set SceneManager parameters
	//	mSceneManager->setAmbientLight(tRenderComponentSceneParameters.ambient);

		if(tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.active)
		{
			//Set SkyBox Dreams
			mSceneManager->setSkyBox(tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.active,
				tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.materialDreams,
				tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.distance);
			//Set SkyBox Nightmares
			mSceneManager->setSkyBox(tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.active,
				tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.materialNightmares,
				tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters.distance);
		}

		if(tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.active)
		{
			//Set SkyDome Dreams
			mSceneManager->setSkyDome(tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.active,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.materialDreams,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.curvature,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.tiling,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.distance);

			//Set SkyDome Nightmares
			mSceneManager->setSkyDome(tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.active,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.materialNightmares,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.curvature,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.tiling,
				tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters.distance);
		}
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

Ogre::SceneNode * RenderSubsystem::createSceneNode(Ogre::String name,TRenderComponentPositionalParameters tRenderComponentPositionalParameters)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;
	
	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(tRenderComponentPositionalParameters.parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneManager->getRootSceneNode();
		}
		else
		{
			pParentSceneNode = mSceneManager->getSceneNode(tRenderComponentPositionalParameters.parentSceneNodeName);
		}

		//Create SceneNode
		sceneNode = pParentSceneNode->createChildSceneNode(name);

		//Set SceneNode parameters
		sceneNode->setPosition(tRenderComponentPositionalParameters.position);
		sceneNode->setOrientation(tRenderComponentPositionalParameters.orientation);
		sceneNode->setScale(tRenderComponentPositionalParameters.scale);
		if(tRenderComponentPositionalParameters.autotracktarget.compare("None")!=0)
		{
			//TODO test this
			SceneNode *trackTarget;
			trackTarget=mSceneManager->getSceneNode(tRenderComponentPositionalParameters.autotracktarget);
			sceneNode->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &e)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" SceneNode!: "+e.getDescription());
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

void RenderSubsystem::initMaterials()
{
	Ogre::MaterialManager::ResourceMapIterator it = Ogre::MaterialManager::getSingleton().getResourceIterator();
	Ogre::MaterialPtr material;

	while (it.hasMoreElements())
	{
		material=it.getNext();
		if(material->isLoaded())
		{
			material->setLightingEnabled(false);
		}
	}
}

void RenderSubsystem::setLightmaps(Ogre::Entity * pEntity)
{
	unsigned int i;
	Ogre::String materialName = LIGHTMAP_PREFIX+pEntity->getName();
	Ogre::String lightmapName = materialName+".dds";

	if( Ogre::ResourceGroupManager::getSingleton().resourceExists(DEFAULT_OGRE_RESOURCE_MANAGER_GROUP,lightmapName))
	{
		try
		{
			//LogManager::getSingleton().logMessage("[setLightmaps] Adding "+lightmapName+" Lightmap...");
			for ( i = 0; i < pEntity->getNumSubEntities(); ++i)
			{
				// Get the material of this sub entity and build the clone material name
				Ogre::SubEntity* subEnt = pEntity->getSubEntity(i);
				Ogre::MaterialPtr material = subEnt->getMaterial();

				// Get/Create the clone material
				Ogre::MaterialPtr clone;
				if (Ogre::MaterialManager::getSingleton().resourceExists(materialName))
				{
					clone = Ogre::MaterialManager::getSingleton().getByName(materialName);
				}
				else
				{
					// Clone the material and set the fade limits for the shader
					clone = material->clone(materialName);
				}

				// Apply the lightmap
				Ogre::Technique * technique;
				Ogre::Pass * pass;
				Ogre::TextureUnitState * texture_unit;
					//get technique
				technique = clone->getTechnique(0);
					//set current pass attributes
				pass = technique->getPass(0);
				texture_unit = pass->getTextureUnitState(0);
				texture_unit->setTextureCoordSet(0);
				texture_unit->setColourOperationEx(Ogre::LBX_MODULATE);
					//create lightmap pass
				pass = technique->createPass();
				pass->setSceneBlending(Ogre::SBT_MODULATE);
				texture_unit = pass->createTextureUnitState();
				texture_unit->setTextureName(lightmapName);
				texture_unit->setTextureCoordSet(0);
				texture_unit->setColourOperationEx(Ogre::LBX_MODULATE);

				// Apply the cloned material to the sub entity.
				subEnt->setMaterial(clone);
			}
		}
		catch(Ogre::Exception &/*e*/)
		{
			LogManager::getSingleton().logMessage("[setLightmaps] Error adding "+lightmapName+" Lightmap!");
		}
	}
	else
	{
		//LogManager::getSingleton().logMessage("[setLightmaps] Error adding "+lightmapName+" Lightmap!");
	}
}

Ogre::Entity* RenderSubsystem::createEntity(Ogre::String nodeName,Ogre::String name,TRenderComponentEntityParameters tRenderComponentEntityParameters,QueryFlags flags)
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

		//set lightmaps
		setLightmaps(pEntity);

		//set Query flags
		pEntity->setQueryFlags(flags);

		//attach to Scene Manager
		pEntityNode=mSceneManager->getSceneNode(nodeName);
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

		// Create BillboardSet's Billboards
		for(unsigned int i=0;i<tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters.size();i++)
		{
			createBillboard(billBoardSet,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].colour,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].dimensions,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].position,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].rotation,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].texcoordindex,
				tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters[i].texrect);
		}

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" BillboardSet!");
	}
	return billBoardSet;
}
		
RenderComponentDecalPtr RenderSubsystem::createDecal(GameObjectPtr gameObject,TRenderComponentDecalParameters tRenderComponentDecalParameters)
{
	RenderComponentDecalPtr pRenderComponentDecal = RenderComponentDecalPtr(new RenderComponentDecal());

	Frustum * pDecalFrustum;
	SceneNode * pProjectorNode;

	pDecalFrustum = new Frustum();
    pProjectorNode = mSceneManager->getRootSceneNode()->createChildSceneNode("DecalProjectorNode");
    pProjectorNode->attachObject(pDecalFrustum);
    pProjectorNode->setPosition(0,5,0);

	//NOT WORKING YET

	return pRenderComponentDecal;
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


void RenderSubsystem::showOverlay(const std::string& overlayName)
{
	Ogre::Overlay* ovl;
	if (ovl=Ogre::OverlayManager::getSingleton().getByName(overlayName))
		ovl->show();
	else LogManager::getSingleton().logMessage("[ShowOverlay] Error loading "+overlayName+" Overlay!");
}
void RenderSubsystem::hideOverlay(const std::string& overlayName)
{
	Ogre::Overlay* ovl;
	if (ovl=Ogre::OverlayManager::getSingleton().getByName(overlayName))
		ovl->hide();
	else LogManager::getSingleton().logMessage("[ShowOverlay] Error loading "+overlayName+" Overlay!");
}
void RenderSubsystem::pauseRendering()
{
	Ogre::ControllerManager::getSingleton().setTimeFactor(0);
}
void RenderSubsystem::resumeRendering()
{
	Ogre::ControllerManager::getSingleton().setTimeFactor(1.0);
}

void RenderSubsystem::clearScene()
{
	mSceneManager->destroyAllCameras(); 
	mSceneManager->clearScene();
	mRoot->destroySceneManager(mSceneManager);
	mWindow->removeAllViewports();
	//mApp->getGUISubsystem()->clearRenderer();

}

void RenderSubsystem::resetScene()
{
	clearScene();
	mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
}

void RenderSubsystem::captureScene(const std::string& name)
{
	Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual("RttTex",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, PF_R8G8B8,
		TU_RENDERTARGET);
	Ogre::RenderTexture *renderTexture = texture->getBuffer()->getRenderTarget();

	renderTexture->addViewport(mApp->getCameraManager()->getActiveCamera());
	renderTexture->getViewport(0)->setClearEveryFrame(true);
	renderTexture->getViewport(0)->setBackgroundColour(ColourValue::Black);
	renderTexture->getViewport(0)->setOverlaysEnabled(false);		
	renderTexture->update();
	renderTexture->writeContentsToFile(name);
}

void RenderSubsystem::hideOverlayElement(const std::string& overlayName)
{
	Ogre::OverlayElement* overlayElem = Ogre::OverlayManager::getSingleton().getOverlayElement(overlayName);
	if (overlayElem)
		overlayElem->hide();
}
void RenderSubsystem::showOverlayElement(const std::string& overlayName)
{
	Ogre::OverlayElement* overlayElem = Ogre::OverlayManager::getSingleton().getOverlayElement(overlayName);
	if (overlayElem)
		overlayElem->show();

}