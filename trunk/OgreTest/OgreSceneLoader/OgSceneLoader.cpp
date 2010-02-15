#include "OgSceneLoader.h"
#include "tinyxml.h"
#include <Ogre.h>

using namespace std;
using namespace Ogre;

void OgSceneLoader::parseOgScene(const String &SceneName, const String &groupName, SceneManager *pSceneMgr, SceneNode *pAttachNode, Viewport *pViewport)
{
	// set up shared object values
	m_sGroupName = groupName;
	mSceneMgr = pSceneMgr;
	mViewport = pViewport;

	TiXmlDocument   *XMLDoc = 0;
	TiXmlElement   *XMLRoot;

	LogManager::getSingleton().logMessage("[OgSceneLoader] Parsing "+SceneName);

	try
	{
		// Strip the path
		Ogre::String basename, path;
		Ogre::StringUtil::splitFilename(SceneName, basename, path);

		DataStreamPtr pStream = ResourceGroupManager::getSingleton().
			openResource( basename, groupName );

		String data = pStream->getAsString();
		// Open the .scene File
		XMLDoc = new TiXmlDocument();
		XMLDoc->Parse( data.c_str() );
		pStream->close();
		pStream.setNull();

		if( XMLDoc->Error() )
		{
			//We'll just log, and continue on gracefully
			LogManager::getSingleton().logMessage("[OgSceneLoader] The TiXmlDocument reported an error");
			delete XMLDoc;
			return;
		}
	}
	catch(...)
	{
		//We'll just log, and continue on gracefully
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating TiXmlDocument");
		delete XMLDoc;
		return;
	}

	// Validate the File
	XMLRoot = XMLDoc->RootElement();
	if( String( XMLRoot->Value()) != "OGITORSCENE"  ) {
		LogManager::getSingleton().logMessage( "[OgSceneLoader] Error: Invalid .ogscene File. Missing <OGITORSCENE>" );
		delete XMLDoc;      
		return;
	}

	// figure out where to attach any nodes we create
	mAttachNode = pAttachNode;
	if(!mAttachNode)
		mAttachNode = mSceneMgr->getRootSceneNode();

	// Process the scene
	processScene(XMLRoot);

	LogManager::getSingleton().logMessage( "[OgSceneLoader] Done!" );

	// Close the XML File
	delete XMLDoc;
}

void OgSceneLoader::processScene(TiXmlElement *XMLNode)
{

	// Process the scene parameters
	String version = getAttrib(XMLNode, "version", "unknown");

	String message = "[OgSceneLoader] Parsing ogScene file with version " + version;

	LogManager::getSingleton().logMessage(message);

	//Process project
	processProject(XMLNode);
	
	//Process scene objects
	processObjects(XMLNode,"OctreeSceneManager");
	processObjects(XMLNode,"Viewport Object");
	processObjects(XMLNode,"Node Object");
	processObjects(XMLNode,"Light Object");
	processObjects(XMLNode,"Entity Object");
	processObjects(XMLNode,"Camera Object");
	processObjects(XMLNode,"Particle Object");
	processObjects(XMLNode,"BillboardSet Object");

}

void OgSceneLoader::processProject(TiXmlElement *XMLNode)
{
	TiXmlElement *pElement;

	// Process PROJECT
	pElement = XMLNode->FirstChildElement("PROJECT");
	if(pElement)
		processProject(pElement);
}

void OgSceneLoader::processObjects(TiXmlElement *XMLNode, String type)
{	
	TiXmlElement *pElement;

	// Process OBJECTs of selected type
	pElement = XMLNode->FirstChildElement("OBJECT");
	while(pElement)
	{
		String current_object_type = getAttrib(pElement, "typename");
		if( type.compare(current_object_type)==0)
		{
			processObject(pElement);
		}
		pElement = pElement->NextSiblingElement("OBJECT");
	}
}

void OgSceneLoader::processObject(TiXmlElement *XMLNode)
{
	String type = getAttrib(XMLNode, "typename");
	if( type.compare("OctreeSceneManager")==0)
	{
		processOctreeSceneManager(XMLNode);
	}
	else if( type.compare("Viewport Object")==0)
	{
		processViewport(XMLNode);
	}
	else if( type.compare("Node Object")==0)
	{
		processSceneNode(XMLNode);
	}
	else if( type.compare("Light Object")==0)
	{
		processLight(XMLNode);
	}
	else if( type.compare("Entity Object")==0)
	{
		processEntity(XMLNode);
	}
	else if( type.compare("Camera Object")==0)
	{
		processCamera(XMLNode);
	}
	else if( type.compare("Particle Object")==0)
	{
		processParticleSystem(XMLNode);
	}
	else if( type.compare("BillboardSet Object")==0)
	{
		processBillboardSet(XMLNode);
	}
	else
	{
		LogManager::getSingleton().logMessage("Error reading "+type+" OBJECT");
	}
}

void OgSceneLoader::createResourceLocations()
{
	//TODO
}

void OgSceneLoader::processResourceLocations(TiXmlElement *XMLNode)
{
	//TODO
}

void OgSceneLoader::processViewportCamera(TiXmlElement *XMLNode)
{
	Quaternion orientation;
	Vector3 position;
	Vector2 clipdistance;
	Real fov;
	int polygonmode;
	int viewmode;

	//Get Camera properties
	orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
	position = getPropertyVector3(XMLNode,"camera::position");
	clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
	fov = getPropertyReal(XMLNode,"camera::fov");
	polygonmode = getPropertyInt(XMLNode,"camera::polymode");
	viewmode = getPropertyInt(XMLNode,"camera::viewmode");

	//Create Camera
	createCamera("Ogitor",position,orientation,"None",true,clipdistance,fov,polygonmode,viewmode);
}

void OgSceneLoader::createViewport(String name,ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies)
{
	// Set the Viewport parameters
	mViewport->setBackgroundColour(colour);
	mViewport->setOverlaysEnabled(overlays);
	mViewport->setShadowsEnabled(shadows);
	mViewport->setSkiesEnabled(skies);

}

void OgSceneLoader::processViewport(TiXmlElement *XMLNode)
{
	String name;
	ColourValue colour;
	int compositorcount;
	int index;
	bool overlays;
	bool shadows;
	bool skies;

	//Get Viewport name
	name = getAttrib(XMLNode, "name");

	//Get Viewport properties
	colour = getPropertyColourValue(XMLNode,"colour");
	compositorcount = getPropertyInt(XMLNode,"compositorcount");
	index = getPropertyInt(XMLNode,"index");
	overlays = getPropertyBool(XMLNode,"overlays");
	shadows = getPropertyBool(XMLNode,"shadows");
	skies = getPropertyBool(XMLNode,"skies");

	//Create Viewport
	createViewport(name,colour,compositorcount,index,overlays,shadows,skies);

	//Process Viewport camera
	processViewportCamera(XMLNode);
	
}

void OgSceneLoader::createOctreeSceneManager(String name,ColourValue ambient)
{
	try
	{
		//Set SceneManager parameters
		mSceneMgr->setAmbientLight(ColourValue(0.5,0.5,0.5));
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" SceneManager!");
	}
}

void OgSceneLoader::processOctreeSceneManager(TiXmlElement *XMLNode)
{
	String name;
	ColourValue ambient;

	//Get OctreeSceneManager name
	name = getAttrib(XMLNode, "name");

	//Get SceneManager properties
	ambient=getPropertyColourValue(XMLNode,"ambient");
	//Set SceneManager parameters
	createOctreeSceneManager(name,ambient);

	//Process SkyBox
	processSkyBox(XMLNode);

	//Process SkyDome
	processSkyDome(XMLNode);

	//Process Fog
	processFog(XMLNode);

	//Process Shadows
	processShadows(XMLNode);

}

void OgSceneLoader::processTerrain(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void OgSceneLoader::processSceneNodeNoScale(TiXmlElement *XMLNode)
{
	String name;
	String parentnode;
	Vector3 position;
	Quaternion orientation;

	//Get SceneNode name
	name = getAttrib(XMLNode, "name");

	//Get parent SceneNode name
	parentnode = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	position = getPropertyVector3(XMLNode,"position");
	orientation = getPropertyQuaternion(XMLNode,"orientation");

	//create SceneNode
	createSceneNode(name,parentnode,position,orientation,Vector3(0,0,0),"None");
}

void OgSceneLoader::createLight(String name,int lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power)
{
	SceneNode *lightNode=0;
	Light *pLight=0;
	// Set light parameters and create it
	try
	{
		// Create the light
		pLight = mSceneMgr->createLight(name);

		// Attach to Scene Manager
		lightNode=mSceneMgr->getSceneNode(name);
		lightNode->attachObject(pLight);

		//Set Light Parameters
		switch(lighttype)
		{
			case OGITOR_LT_POINT:
				pLight->setType(Light::LT_POINT);
				break;
			case OGITOR_LT_DIRECTIONAL:
				pLight->setType(Light::LT_DIRECTIONAL);
				break;
			case OGITOR_LT_SPOTLIGHT:
				pLight->setType(Light::LT_SPOTLIGHT);
				pLight->setSpotlightRange(Angle(lightrange.x), Angle(lightrange.y), lightrange.z);
				break;
			default:
				LogManager::getSingleton().logMessage("Light "+name+" has unrecognised light type!");
				break;
		}
		pLight->setDiffuseColour(diffuse);
		pLight->setSpecularColour(specular);
		pLight->setDirection(direction);
		pLight->setCastShadows(castshadows);
		LogManager::getSingleton().logMessage("attenuation :"+StringConverter::toString(attenuation));
		//TODO FIX THAT
		//pLight->setAttenuation(attenuation.x, attenuation.y, attenuation.z, attenuation.w);
		pLight->setPowerScale(power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" Light!");
	}
}

void OgSceneLoader::processLight(TiXmlElement *XMLNode)
{
	String name;
	int lighttype;
	ColourValue diffuse;
	ColourValue specular;
	Vector3 direction;
	bool castshadows;
	Vector3 lightrange;
	Vector4 attenuation;
	Real power;

	//Parse and create Scene node
	processSceneNodeNoScale(XMLNode);

	//Get Light name
	name = getAttrib(XMLNode, "name");

	//Get Light properties
	lighttype = getPropertyInt(XMLNode,"lighttype");
	diffuse = getPropertyColourValue(XMLNode,"diffuse");
	specular = getPropertyColourValue(XMLNode,"specular");
	direction = getPropertyVector3(XMLNode,"direction");
	castshadows = getPropertyBool(XMLNode,"castshadows");
	lightrange = getPropertyVector3(XMLNode,"lightrange");
	attenuation = getPropertyVector4(XMLNode,"attenuation");
	power = getPropertyReal(XMLNode,"power");

	//Create Light
	createLight(name,lighttype,diffuse,specular,direction,castshadows,lightrange,attenuation,power);

}

void OgSceneLoader::createCamera(String name,Vector3 position,Quaternion orientation,String autotracktarget,bool autoaspectratio,Vector2 clipdistance,Real fov,int polygonmode,int viewmode)
{

	SceneNode *cameraNode=0;
	Camera *pCamera=0;
	// Set light parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneMgr->createCamera(name);

		//Set Camera Parameters
		//set polygon mode
		switch(polygonmode)
		{
			case OGITOR_PM_SOLID:
				pCamera->setPolygonMode(PM_SOLID);
				break;
			case OGITOR_PM_POINTS:
				pCamera->setPolygonMode(PM_POINTS);
				break;
			case OGITOR_PM_WIREFRAME:
				pCamera->setPolygonMode(PM_WIREFRAME);
				break;
			default:
				LogManager::getSingleton().logMessage("Camera "+name+" has unrecognised PolygonMode!");
				break;
		}
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
			trackTarget=mSceneMgr->getSceneNode(autotracktarget);
			pCamera->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" Camera!");
	}
}

void OgSceneLoader::processCamera(TiXmlElement *XMLNode)
{
	String name;
	String autotracktarget;
	Quaternion orientation;
	Vector3 position;
	bool autoaspectratio;
	Vector2 clipdistance;
	Real fov;
	int polygonmode;
	int viewmode;

	//Get Camera name
	name = getAttrib(XMLNode, "name");

	//Get Camera properties
	autotracktarget = getPropertyString(XMLNode,"autotracktarget");
	orientation = getPropertyQuaternion(XMLNode,"orientation");
	position = getPropertyVector3(XMLNode,"position");
	autoaspectratio = getPropertyBool(XMLNode,"autoaspectratio");
	clipdistance = getPropertyVector2(XMLNode,"clipdistance");
	fov = getPropertyReal(XMLNode,"fov");
	polygonmode = getPropertyInt(XMLNode,"polygonmode");
	viewmode = getPropertyInt(XMLNode,"viewmode");

	//Create Camera
	createCamera(name,position,orientation,autotracktarget,autoaspectratio,clipdistance,fov,polygonmode,viewmode);
}

void OgSceneLoader::createSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mAttachNode;
		}
		else
		{
			pParentSceneNode = mSceneMgr->getSceneNode(parentSceneNodeName);
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
			trackTarget=mSceneMgr->getSceneNode(autotracktarget);
			sceneNode->setAutoTracking(true,trackTarget);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" SceneNode!");
	}
}

void OgSceneLoader::processSceneNode(TiXmlElement *XMLNode)
{
	String name;
	String parentnode;
	Vector3 position;
	Quaternion orientation;
	Vector3 scale;
	String autotracktarget;

	//Get SceneNode name
	name = getAttrib(XMLNode, "name");

	//Get parent SceneNode name
	parentnode = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	position = getPropertyVector3(XMLNode,"position");
	orientation = getPropertyQuaternion(XMLNode,"orientation");
	scale = getPropertyVector3(XMLNode,"scale");
	autotracktarget = getPropertyString(XMLNode,"autotracktarget");

	//create SceneNode
	createSceneNode(name,parentnode,position,orientation,scale,autotracktarget);
}

void OgSceneLoader::processTrackTarget(TiXmlElement *XMLNode)
{

	//// Setup the track target
	//try
	//{
	//	SceneNode *pTrackNode = mSceneMgr->getSceneNode(nodeName);
	//	pParent->setAutoTracking(true, pTrackNode, localDirection, offset);
	//}
	//catch(Ogre::Exception &/*e*/)
	//{
	//	LogManager::getSingleton().logMessage("[OgSceneLoader] Error processing a track target!");
	//}
}

void OgSceneLoader::createMeshFile(String meshfile)
{
	try
	{
		//Create the mesh file
		if (!MeshManager::getSingleton().resourceExists(meshfile))
		{
			//LogManager::getSingleton().logMessage("[OgSceneLoader] creating "+meshfile+" meshfile");
			MeshManager::getSingleton().load(meshfile, m_sGroupName);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+meshfile+" mesh!");
	}
}

void OgSceneLoader::createEntity(String name,String meshfile,bool castshadows)
{

	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//Create meshfile
		createMeshFile(meshfile);

		//create entity and set its parameters
		pEntity = mSceneMgr->createEntity(name, meshfile);
		pEntity->setCastShadows(castshadows);

		//attach to Scene Manager
		pEntityNode=mSceneMgr->getSceneNode(name);
		pEntityNode->attachObject(pEntity);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" Entity!");
	}
}

void OgSceneLoader::createSubEntity(String name,int num,String material,bool visible)
{
	SubEntity *pSubEntity = 0;
	Entity *pEntity = 0;
		
	try
	{
		//get the Entity
		pEntity=mSceneMgr->getEntity(name);

		//get the SubEntity
		pSubEntity=pEntity->getSubEntity(num);

		//set SubEntity attributes
		pSubEntity->setMaterialName(material);
		pSubEntity->setVisible(visible);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+pEntity->getName()+"'s SubEntity #"+StringConverter::toString(num)+"!");
	}
}

void OgSceneLoader::processSubentities(String name,TiXmlElement *XMLNode)
{
		int i;
		int numSubEntities;

		String material;
		bool visible;
		
		//get the Entity
		Entity *pEntity = 0;
		pEntity=mSceneMgr->getEntity(name);
		
		//get the number of Entity's SubEntites
		numSubEntities=pEntity->getNumSubEntities();
 
		//process and load all Entity's SubEntites
		for(i=0;i<numSubEntities;i++)
		{
			//Process SubEntity
			material=getPropertyString(XMLNode,"subentity"+StringConverter::toString(i)+"::material");
			visible=getPropertyBool(XMLNode,"subentity"+StringConverter::toString(i)+"::visible");
			//create SubEntity
			createSubEntity(name,i,material,visible);
		}
}

void OgSceneLoader::processEntity(TiXmlElement *XMLNode)
{
	String name;
	String meshfile;
	bool castshadows;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get Entity name
	name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[OgSceneLoader] creating "+name+" entity");

	//Process entity properties
	meshfile = getPropertyString(XMLNode, "meshfile");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create Entity
	createEntity(name,meshfile,castshadows);

	//process Entity's SubEntites
	processSubentities(name,XMLNode);

}

void OgSceneLoader::createParticleSystem(String name,String particle,bool castshadows)
{
	ParticleSystem *pParticleSystem = 0;
	SceneNode *particleSystemNode = 0;
	
	try
	{
		// Create ParticleSystem
		pParticleSystem = mSceneMgr->createParticleSystem(name, particle);

		// Attach ParticleSystem to SceneManager
		particleSystemNode=mSceneMgr->getSceneNode(name);
		particleSystemNode->attachObject(pParticleSystem);

		// Set ParticleSystem parameters
		pParticleSystem->setCastShadows(castshadows);

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" ParticleSystem!");
	}
}

void OgSceneLoader::processParticleSystem(TiXmlElement *XMLNode)
{

	String particle;
	bool castshadows;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get ParticleSystem name
	String name = getAttrib(XMLNode, "name");

	//Process ParticleSystem properties
	particle = getPropertyString(XMLNode, "particle");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create ParticleSystem
	createParticleSystem(name,particle,castshadows);

}

void OgSceneLoader::processBillboards(String billBoardSetName,TiXmlElement *XMLNode)
{

	int i;
	int billboardcount;
	ColourValue colour;
	Vector2 dimensions;
	Vector3 position;
	Real rotation;
	int texcoordindex;
	Vector4 texrect;

	//get the BillboardSet
	BillboardSet *pBillboardSet = 0;
	pBillboardSet=mSceneMgr->getBillboardSet(billBoardSetName);
	
	//get the number of BillboardSet's Billboards
	billboardcount=getPropertyInt(XMLNode,"billboardcount");

	//process and load all BillboardSet's Billboards
	for(i=0;i<billboardcount;i++)
	{
		//Process Billboards
		colour=getPropertyColourValue(XMLNode,"billboard"+StringConverter::toString(i)+"::colour");
		dimensions=getPropertyVector2(XMLNode,"billboard"+StringConverter::toString(i)+"::dimensions");
		position=getPropertyVector3(XMLNode,"billboard"+StringConverter::toString(i)+"::position");
		rotation=getPropertyReal(XMLNode,"billboard"+StringConverter::toString(i)+"::rotation");
		texcoordindex=getPropertyInt(XMLNode,"billboard"+StringConverter::toString(i)+"::texcoordindex");
		texrect=getPropertyVector4(XMLNode,"billboard"+StringConverter::toString(i)+"::texrect");

		//create Billboards
		createBillboard(billBoardSetName,colour,dimensions,position,rotation,texcoordindex,texrect);
	}
	
}

void OgSceneLoader::createBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect)
{

	Billboard *pBillboard = 0;
	BillboardSet *pBillboardSet = 0;
		
	try
	{
		//get the BillboardSet
		pBillboardSet=mSceneMgr->getBillboardSet(billBoardSetName);

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
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+billBoardSetName+"'s Billboard!");
	}
}

void OgSceneLoader::createBillboardSet(String name,String material,int billboardorigin,int billboardrotation,int billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting)
{
	BillboardSet *billBoardSet = 0;
	SceneNode *billBoardSetNode = 0;
	try
	{
		//Create BillboardSet
		billBoardSet = mSceneMgr->createBillboardSet(name);

		//Attach BillboardSet to SceneNode
		billBoardSetNode = mSceneMgr->getSceneNode(name);
		billBoardSetNode->attachObject(billBoardSet);

		//Set BillboardSet Attributes
		billBoardSet->setMaterialName(material);
		billBoardSet->setDefaultHeight(defaultheight);
		billBoardSet->setDefaultWidth(defaultwidth);
		billBoardSet->setPointRenderingEnabled(pointrendering);
		billBoardSet->setRenderingDistance(renderdistance);
		billBoardSet->setSortingEnabled(sorting);

		switch(billboardtype)
		{
			case OGITOR_BBT_ORIENTED_COMMON:
				billBoardSet->setBillboardType(BBT_ORIENTED_COMMON);
				break;
			case OGITOR_BBT_ORIENTED_SELF:
				billBoardSet->setBillboardType(BBT_ORIENTED_SELF);
				break;
			case OGITOR_BBT_PERPENDICULAR_COMMON:
				billBoardSet->setBillboardType(BBT_PERPENDICULAR_COMMON);
				break;
			case OGITOR_BBT_PERPENDICULAR_SELF:
				billBoardSet->setBillboardType(BBT_PERPENDICULAR_SELF);
				break;
			case OGITOR_BBT_POINT:
				billBoardSet->setBillboardType(BBT_POINT);
				break;
			default:
				LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardType!");
				break;
		}

		switch(billboardorigin)
		{
			case OGITOR_BBO_BOTTOM_CENTER:
				billBoardSet->setBillboardOrigin(BBO_BOTTOM_CENTER);
				break;
			case OGITOR_BBO_BOTTOM_LEFT:
				billBoardSet->setBillboardOrigin(BBO_BOTTOM_LEFT);
				break;
			case OGITOR_BBO_BOTTOM_RIGHT:
				billBoardSet->setBillboardOrigin(BBO_BOTTOM_RIGHT);
				break;
			case OGITOR_BBO_CENTER:
				billBoardSet->setBillboardOrigin(BBO_CENTER);
				break;
			case OGITOR_BBO_CENTER_LEFT:
				billBoardSet->setBillboardOrigin(BBO_CENTER_LEFT);
				break;
			case OGITOR_BBO_CENTER_RIGHT:
				billBoardSet->setBillboardOrigin(BBO_CENTER_RIGHT);
				break;
			case OGITOR_BBO_TOP_CENTER:
				billBoardSet->setBillboardOrigin(BBO_TOP_CENTER);
				break;
			case OGITOR_BBO_TOP_LEFT:
				billBoardSet->setBillboardOrigin(BBO_TOP_LEFT);
				break;
			case OGITOR_BBO_TOP_RIGHT:
				billBoardSet->setBillboardOrigin(BBO_TOP_RIGHT);
				break;
			default:
				LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardOrigin!");
				break;
		}

		switch(billboardrotation)
		{
			case OGITOR_BBR_TEXCOORD:
				billBoardSet->setBillboardRotationType(BBR_TEXCOORD);
				break;
			case OGITOR_BBR_VERTEX:
				billBoardSet->setBillboardRotationType(BBR_VERTEX);
				break;
			default:
				LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardRotationType!");
				break;
		}

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating "+name+" BillboardSet!");
	}
}

void OgSceneLoader::processBillboardSet(TiXmlElement *XMLNode)
{
	String name;
	String material;
	int billboardorigin;
	int billboardrotation;
	int billboardtype;
	Real defaultheight;
	Real defaultwidth;
	bool pointrendering;
	Real renderdistance;
	bool sorting;

	//Process the BillboardSet scene node
	processSceneNode(XMLNode);
	
	//Get BillboardSet name
	name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[OgSceneLoader] creating "+name+" BillboardSet");

	//Process BillboardSet properties
	material = getPropertyString(XMLNode, "material");
	billboardorigin = getPropertyInt(XMLNode, "billboardorigin");
	billboardrotation = getPropertyInt(XMLNode, "billboardrotation");
	billboardtype = getPropertyInt(XMLNode, "billboardtype");
	defaultheight = getPropertyReal(XMLNode, "defaultheight");
	defaultwidth = getPropertyReal(XMLNode, "defaultwidth");
	pointrendering = getPropertyBool(XMLNode, "pointrendering");
	renderdistance = getPropertyReal(XMLNode, "renderdistance");
	sorting = getPropertyBool(XMLNode, "sorting");
	
	//Create BillboardSet
	createBillboardSet(name,material,billboardorigin,billboardrotation,billboardtype,defaultheight,defaultwidth,pointrendering,renderdistance,sorting);

	//process BillboardSet's Billboards
	processBillboards(name,XMLNode);
}

void OgSceneLoader::createPlane()
{

}

void OgSceneLoader::processPlane(TiXmlElement *XMLNode)
{

}

void OgSceneLoader::createFog()
{
	//// Setup the fog
	//mSceneMgr->setFog(mode, colourDiffuse, expDensity, linearStart, linearEnd);
}

void OgSceneLoader::processFog(TiXmlElement *XMLNode)
{

}

void OgSceneLoader::createSkyBox(bool active, String material, Real distance)
{
	if (!active) return;
	try
	{
		// Setup the sky box
		mSceneMgr->setSkyBox(active, material, distance);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating SkyBox!");
	}
}

void OgSceneLoader::processSkyBox(TiXmlElement *XMLNode)
{
	// Process SkyBox properties
	bool active = getPropertyBool(XMLNode, "skybox::active");
	String material = getPropertyString(XMLNode, "skybox::material");
	Real distance = getPropertyReal(XMLNode, "skybox::distance");

	
	//Create the SkyBox
	createSkyBox(active, material, distance);
}

void OgSceneLoader::createSkyDome(bool active, String material)
{
	if (!active) return;
	try
	{
		// Setup the SkyDome
		mSceneMgr->setSkyDome(active,material);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error creating SkyDome!");
	}
}

void OgSceneLoader::processSkyDome(TiXmlElement *XMLNode)
{
	// Process SkyDome properties
	bool active = getPropertyBool(XMLNode, "skydome::active");
	String material = getPropertyString(XMLNode, "skydome::material");
	
	//Create the SkyDome
	createSkyDome(active, material);
}

void OgSceneLoader::createShadows()
{
	
}

void OgSceneLoader::processShadows(TiXmlElement *XMLNode)
{

}

String OgSceneLoader::getAttrib(TiXmlElement *XMLNode, const String &attrib, const String &defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return XMLNode->Attribute(attrib.c_str());
	else
		return defaultValue;
}


String OgSceneLoader::getPropertyString(TiXmlElement *XMLNode, const String &attrib_name)
{
	TiXmlElement *pElement;
	TiXmlElement *XMLNodeCustomProperties;
	String propertyName;
	String result="";
	bool found=false;

	// Process all PROPERTY of the XML node
	pElement = XMLNode->FirstChildElement("PROPERTY");
	while(pElement)
	{
		propertyName = getAttrib(pElement, "id");

		//LogManager::getSingleton().logMessage("[OgSceneLoader] parsing "+propertyName+" property!");

		if(propertyName.compare(attrib_name)==0)
		{
			// Get the attribute value
			result = getAttrib(pElement, "value");
			found=true;
		}
		pElement = pElement->NextSiblingElement("PROPERTY");
	}

	XMLNodeCustomProperties = XMLNode->FirstChildElement("CUSTOMPROPERTIES");

	// Process all CUSTOMPROPERTIES
	pElement = XMLNodeCustomProperties->FirstChildElement("PROPERTY");
	while(pElement)
	{
		propertyName = getAttrib(pElement, "id");

		//LogManager::getSingleton().logMessage("[OgSceneLoader] parsing "+propertyName+" property!");

		if(propertyName.compare(attrib_name)==0)
		{
			// Get the attribute value
			result = getAttrib(pElement, "value");
			found=true;
		}
		pElement = pElement->NextSiblingElement("PROPERTY");
	}

	if(!found)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error parsing "+attrib_name+" attribute!");
	}
	return result;
}

Vector2 OgSceneLoader::getPropertyVector2(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector2(getPropertyString(XMLNode,attrib_name));
}

Vector3 OgSceneLoader::getPropertyVector3(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector3(getPropertyString(XMLNode,attrib_name));
}

Vector4 OgSceneLoader::getPropertyVector4(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector4(getPropertyString(XMLNode,attrib_name));
}

Quaternion OgSceneLoader::getPropertyQuaternion(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseQuaternion(getPropertyString(XMLNode,attrib_name));
}

ColourValue OgSceneLoader::getPropertyColourValue(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseColourValue(getPropertyString(XMLNode,attrib_name));
}

bool OgSceneLoader::getPropertyBool(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseBool(getPropertyString(XMLNode,attrib_name));
}

int OgSceneLoader::getPropertyInt(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseInt(getPropertyString(XMLNode,attrib_name));
}

Real OgSceneLoader::getPropertyReal(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseReal(getPropertyString(XMLNode,attrib_name));
}
