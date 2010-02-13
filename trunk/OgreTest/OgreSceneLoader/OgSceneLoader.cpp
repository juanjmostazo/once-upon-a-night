#include "OgSceneLoader.h"
#include "tinyxml.h"
#include <Ogre.h>

using namespace std;
using namespace Ogre;

void OgSceneLoader::parseOgScene(const String &SceneName, const String &groupName, SceneManager *yourSceneMgr, SceneNode *pAttachNode, const String &sPrependNode)
{
	// set up shared object values
	m_sGroupName = groupName;
	mSceneMgr = yourSceneMgr;
	m_sPrependNode = sPrependNode;
	staticObjects.clear();
	dynamicObjects.clear();

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

	// Close the XML File
	delete XMLDoc;
}

void OgSceneLoader::processScene(TiXmlElement *XMLRoot)
{
	// Process the scene parameters
	String version = getAttrib(XMLRoot, "version", "unknown");

	String message = "[OgSceneLoader] Parsing ogScene file with version " + version;
	//if(XMLRoot->Attribute("ID"))
	//	message += ", id " + String(XMLRoot->Attribute("ID"));
	//if(XMLRoot->Attribute("sceneManager"))
	//	message += ", scene manager " + String(XMLRoot->Attribute("sceneManager"));
	//if(XMLRoot->Attribute("minOgreVersion"))
	//	message += ", min. Ogre version " + String(XMLRoot->Attribute("minOgreVersion"));
	//if(XMLRoot->Attribute("author"))
	//	message += ", author " + String(XMLRoot->Attribute("author"));

	LogManager::getSingleton().logMessage(message);

	TiXmlElement *pElement;

	// Process PROJECT (?)
	pElement = XMLRoot->FirstChildElement("PROJECT");
	if(pElement)
		processProject(pElement);

	// Process OBJECT (?)
	pElement = XMLRoot->FirstChildElement("OBJECT");
	while(pElement)
	{
		processObject(pElement);
		pElement = pElement->NextSiblingElement("OBJECT");
	}
		

}

void OgSceneLoader::processProject(TiXmlElement *XMLNode)
{
	//TiXmlElement *pElement;
	//// Process resourceLocations (?)
	//pElement = XMLNode->FirstChildElement("resourceLocations");
	//if(pElement)
	//	processResourceLocations(pElement);


	//// Process environment (?)
	//pElement = XMLNode->FirstChildElement("environment");
	//if(pElement)
	//	processEnvironment(pElement);
}

void OgSceneLoader::processObject(TiXmlElement *XMLNode)
{
	String type = getAttrib(XMLNode, "typename");
	if( type.compare("SceneManager")==0)
	{
	}
	else if( type.compare("ViewPort Object")==0)
	{
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

void OgSceneLoader::processResourceLocations(TiXmlElement *XMLNode)
{
	//TODO
}

void OgSceneLoader::processExternals(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void OgSceneLoader::processEnvironment(TiXmlElement *XMLNode)
{
	TiXmlElement *pElement;

	// Process fog (?)
	pElement = XMLNode->FirstChildElement("fog");
	if(pElement)
		processFog(pElement);

	// Process skyBox (?)
	pElement = XMLNode->FirstChildElement("skyBox");
	if(pElement)
		processSkyBox(pElement);

	// Process skyDome (?)
	pElement = XMLNode->FirstChildElement("skyDome");
	if(pElement)
		processSkyDome(pElement);

	// Process skyPlane (?)
	pElement = XMLNode->FirstChildElement("skyPlane");
	if(pElement)
		processSkyPlane(pElement);

	// Process clipping (?)
	pElement = XMLNode->FirstChildElement("clipping");
	if(pElement)
		processClipping(pElement);

	// Process colourAmbient (?)
	pElement = XMLNode->FirstChildElement("colourAmbient");
	if(pElement)
//		mSceneMgr->setAmbientLight(parseColour(pElement));

	// Process colourBackground (?)
	//! @todo Set the background colour of all viewports (RenderWindow has to be provided then)
	pElement = XMLNode->FirstChildElement("colourBackground");
	if(pElement)
		;//mSceneMgr->set(parseColour(pElement));

	// Process userDataReference (?)
	pElement = XMLNode->FirstChildElement("userDataReference");

}

void OgSceneLoader::processTerrain(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void OgSceneLoader::processOctree(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void OgSceneLoader::processLightSceneNode(TiXmlElement *XMLNode)
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
	loadSceneNode(name,parentnode,position,orientation,Vector3(0,0,0),"None");
}

void OgSceneLoader::loadLight(String name,int lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power)
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
		//pLight->setAttenuation(attenuation.x, attenuation.y, attenuation.z, attenuation.w);
		//pLight->setPowerScale(power);
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error loading "+name+" Light!");
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
	processLightSceneNode(XMLNode);

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
	loadLight(name,lighttype,diffuse,specular,direction,castshadows,lightrange,attenuation,power);

}

void OgSceneLoader::processCamera(TiXmlElement *XMLNode)
{
	//// Process attributes
	//String name = getAttrib(XMLNode, "name");
	//String id = getAttrib(XMLNode, "id");
	//Real fov = parseReal(getAttrib(XMLNode, "fov"));
	//Real aspectRatio = parseReal(getAttrib(XMLNode, "aspectRatio"));
	//String projectionType = getAttrib(XMLNode, "projectionType", "perspective");

	//// Create the camera
	//Camera *pCamera = mSceneMgr->createCamera(name);
	//if(pParent)
	//	pParent->attachObject(pCamera);
	//
	//// Set the field-of-view
	////! @todo Is this always in degrees?
	//pCamera->setFOVy(Ogre::Degree(fov));

	//// Set the aspect ratio
	//pCamera->setAspectRatio(aspectRatio);
	//
	//// Set the projection type
	//if(projectionType == "perspective")
	//	pCamera->setProjectionType(PT_PERSPECTIVE);
	//else if(projectionType == "orthographic")
	//	pCamera->setProjectionType(PT_ORTHOGRAPHIC);


	//TiXmlElement *pElement;

	//// Process clipping (?)
	//pElement = XMLNode->FirstChildElement("clipping");
	//if(pElement)
	//{
	//	Real nearDist = parseReal(getAttrib(pElement, "near");
	//	pCamera->setNearClipDistance(nearDist);

	//	Real farDist =  parseReal(getAttrib(pElement, "far");
	//	pCamera->setFarClipDistance(farDist);
	//}

	//// Process position (?)
	//pElement = XMLNode->FirstChildElement("position");
	//if(pElement)
	//	pCamera->setPosition(parseVector3(pElement));

	//// Process rotation (?)
	//pElement = XMLNode->FirstChildElement("rotation");
	//if(pElement)
	//	pCamera->setOrientation(parseQuaternion(pElement));

	//// Process normal (?)
	//pElement = XMLNode->FirstChildElement("normal");
	//if(pElement)
	//	;//!< @todo What to do with this element?

	//// Process lookTarget (?)
	//pElement = XMLNode->FirstChildElement("lookTarget");
	//if(pElement)
	//	;//!< @todo Implement the camera look target

	//// Process trackTarget (?)
	//pElement = XMLNode->FirstChildElement("trackTarget");
	//if(pElement)
	//	;//!< @todo Implement the camera track target

	//// Process userDataReference (?)
	//pElement = XMLNode->FirstChildElement("userDataReference");
	//if(pElement)
	//	;//!< @todo Implement the camera user data reference
}

void OgSceneLoader::loadSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget)
{

	SceneNode *pParentSceneNode = 0;
	SceneNode *sceneNode = 0;

	// Set SceneNode parameters and create it
	try
	{
		//Get Parent SceneNode
		if(parentSceneNodeName.compare("SceneManager")==0)
		{
			pParentSceneNode = mSceneMgr->getRootSceneNode();
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
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error loading "+name+" SceneNode!");
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
	loadSceneNode(name,parentnode,position,orientation,scale,autotracktarget);
}

void OgSceneLoader::processLookTarget(TiXmlElement *XMLNode)
{
	////! @todo Is this correct? Cause I don't have a clue actually

	//// Process attributes
	//String nodeName = getAttrib(XMLNode, "nodeName");

	//Node::TransformSpace relativeTo = Node::TS_PARENT;
	//String sValue = getAttrib(XMLNode, "relativeTo");
	//if(sValue == "local")
	//	relativeTo = Node::TS_LOCAL;
	//else if(sValue == "parent")
	//	relativeTo = Node::TS_PARENT;
	//else if(sValue == "world")
	//	relativeTo = Node::TS_WORLD;

	//TiXmlElement *pElement;

	//// Process position (?)
	//Vector3 position;
	//pElement = XMLNode->FirstChildElement("position");
	//if(pElement)
	//	position = parseVector3(pElement);

	//// Process localDirection (?)
	//Vector3 localDirection = Vector3::NEGATIVE_UNIT_Z;
	//pElement = XMLNode->FirstChildElement("localDirection");
	//if(pElement)
	//	localDirection = parseVector3(pElement);

	//// Setup the look target
	//try
	//{
	//	if(!nodeName.empty())
	//	{
	//		SceneNode *pLookNode = mSceneMgr->getSceneNode(nodeName);
	//		position = pLookNode->_getDerivedPosition();
	//	}

	//	pParent->lookAt(position, relativeTo, localDirection);
	//}
	//catch(Ogre::Exception &/*e*/)
	//{
	//	LogManager::getSingleton().logMessage("[OgSceneLoader] Error processing a look target!");
	//}
}

void OgSceneLoader::processTrackTarget(TiXmlElement *XMLNode)
{
	//// Process attributes
	//String nodeName = getAttrib(XMLNode, "nodeName");

	//TiXmlElement *pElement;

	//// Process localDirection (?)
	//Vector3 localDirection = Vector3::NEGATIVE_UNIT_Z;
	//pElement = XMLNode->FirstChildElement("localDirection");
	//if(pElement)
	//	localDirection = parseVector3(pElement);

	//// Process offset (?)
	//Vector3 offset = Vector3::ZERO;
	//pElement = XMLNode->FirstChildElement("offset");
	//if(pElement)
	//	offset = parseVector3(pElement);

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

void OgSceneLoader::loadMeshFile(String meshfile)
{
	try
	{
		//load the mesh file
		if (!MeshManager::getSingleton().resourceExists(meshfile))
		{
			//LogManager::getSingleton().logMessage("[OgSceneLoader] loading "+meshfile+" meshfile");
			MeshManager::getSingleton().load(meshfile, m_sGroupName);
		}
	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error loading "+meshfile+" mesh!");
	}
}

void OgSceneLoader::loadEntity(String name,String meshfile,bool castshadows)
{

	Entity *pEntity = 0;
	SceneNode *pEntityNode = 0;
	try
	{
		//load meshfile
		loadMeshFile(meshfile);

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

void OgSceneLoader::loadSubEntity(String name,int num,String material,bool visible)
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
			loadSubEntity(name,i,material,visible);
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
	//LogManager::getSingleton().logMessage("[OgSceneLoader] loading "+name+" entity");

	//Process entity properties
	meshfile = getPropertyString(XMLNode, "meshfile");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//load Entity
	loadEntity(name,meshfile,castshadows);

	//process Entity's SubEntites
	processSubentities(name,XMLNode);

}

void OgSceneLoader::loadParticleSystem(String name,String particle,bool castshadows)
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
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error loading "+name+" ParticleSystem!");
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
	LogManager::getSingleton().logMessage("[OgSceneLoader] loading "+name+" entity");

	//Process ParticleSystem properties
	particle = getPropertyString(XMLNode, "particle");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//load ParticleSystem
	loadParticleSystem(name,particle,castshadows);

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
		loadBillboard(billBoardSetName,colour,dimensions,position,rotation,texcoordindex,texrect);
	}
	
}

void OgSceneLoader::loadBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect)
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

void OgSceneLoader::loadBillboardSet(String name,String material,int billboardorigin,int billboardrotationtype,int billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting)
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

		switch(billboardrotationtype)
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
		LogManager::getSingleton().logMessage("[OgSceneLoader] Error loading "+name+" BillboardSet!");
	}
}

void OgSceneLoader::processBillboardSet(TiXmlElement *XMLNode)
{
	String name;
	String material;
	int billboardorigin;
	int billboardrotationtype;
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
	LogManager::getSingleton().logMessage("[OgSceneLoader] loading "+name+" BillboardSet");

	//Process BillboardSet properties
	material = getPropertyString(XMLNode, "material");
	billboardorigin = getPropertyInt(XMLNode, "billboardorigin");
	billboardrotationtype = getPropertyInt(XMLNode, "billboardrotationtype");
	billboardtype = getPropertyInt(XMLNode, "billboardtype");
	defaultheight = getPropertyReal(XMLNode, "defaultheight");
	defaultwidth = getPropertyReal(XMLNode, "defaultwidth");
	pointrendering = getPropertyBool(XMLNode, "pointrendering");
	renderdistance = getPropertyReal(XMLNode, "renderdistance");
	sorting = getPropertyBool(XMLNode, "sorting");
	
	//load BillboardSet
	loadBillboardSet(name,material,billboardorigin,billboardrotationtype,billboardtype,defaultheight,defaultwidth,pointrendering,renderdistance,sorting);

	//process BillboardSet's Billboards
	processBillboards(name,XMLNode);
}

void OgSceneLoader::processPlane(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void OgSceneLoader::processFog(TiXmlElement *XMLNode)
{
	//// Process attributes
	//Real expDensity = parseReal(getAttrib(XMLNode, "expDensity", 0.001);
	//Real linearStart = parseReal(getAttrib(XMLNode, "linearStart", 0.0);
	//Real linearEnd = parseReal(getAttrib(XMLNode, "linearEnd", 1.0);

	//FogMode mode = FOG_NONE;
	//String sMode = getAttrib(XMLNode, "mode");
	//if(sMode == "none")
	//	mode = FOG_NONE;
	//else if(sMode == "exp")
	//	mode = FOG_EXP;
	//else if(sMode == "exp2")
	//	mode = FOG_EXP2;
	//else if(sMode == "linear")
	//	mode = FOG_LINEAR;

	//TiXmlElement *pElement;

	//// Process colourDiffuse (?)
	//ColourValue colourDiffuse = ColourValue::White;
	//pElement = XMLNode->FirstChildElement("colourDiffuse");
	//if(pElement)
	//	colourDiffuse = parseColour(pElement);

	//// Setup the fog
	//mSceneMgr->setFog(mode, colourDiffuse, expDensity, linearStart, linearEnd);
}

void OgSceneLoader::processSkyBox(TiXmlElement *XMLNode)
{
	// Process attributes
//	String material = getAttrib(XMLNode, "material");
//	Real distance = parseReal(getAttrib(XMLNode, "distance", 5000);
//	bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);
//
//	TiXmlElement *pElement;
//
//	// Process rotation (?)
//	Quaternion rotation = Quaternion::IDENTITY;
//	pElement = XMLNode->FirstChildElement("rotation");
//	if(pElement)
//		rotation = parseQuaternion(pElement);
//
//	// Setup the sky box
//	;//mSceneMgr->setSkyBox(true, material, distance, drawFirst, rotation, m_sGroupName);
}

void OgSceneLoader::processSkyDome(TiXmlElement *XMLNode)
{
//	// Process attributes
//	String material = XMLNode->Attribute("material");
//	Real curvature = parseReal(getAttrib(XMLNode, "curvature", 10);
//	Real tiling = parseReal(getAttrib(XMLNode, "tiling", 8);
//	Real distance = parseReal(getAttrib(XMLNode, "distance", 4000);
//	bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);
//
//	TiXmlElement *pElement;
//
//	// Process rotation (?)
//	Quaternion rotation = Quaternion::IDENTITY;
//	pElement = XMLNode->FirstChildElement("rotation");
//	if(pElement)
//		rotation = parseQuaternion(pElement);
//
//	// Setup the sky dome
//	;//mSceneMgr->setSkyDome(true, material, curvature, tiling, distance, drawFirst, rotation, 16, 16, -1, m_sGroupName);
}

void OgSceneLoader::processSkyPlane(TiXmlElement *XMLNode)
{
	//// Process attributes
	//String material = getAttrib(XMLNode, "material");
	//Real planeX = parseReal(getAttrib(XMLNode, "planeX", 0);
	//Real planeY = parseReal(getAttrib(XMLNode, "planeY", -1);
	//Real planeZ = parseReal(getAttrib(XMLNode, "planeX", 0);
	//Real planeD = parseReal(getAttrib(XMLNode, "planeD", 5000);
	//Real scale = parseReal(getAttrib(XMLNode, "scale", 1000);
	//Real bow = parseReal(getAttrib(XMLNode, "bow", 0);
	//Real tiling = parseReal(getAttrib(XMLNode, "tiling", 10);
	//bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);

	//// Setup the sky plane
	//Plane plane;
	//plane.normal = Vector3(planeX, planeY, planeZ);
	//plane.d = planeD;
	//mSceneMgr->setSkyPlane(true, plane, material, scale, tiling, drawFirst, bow, 1, 1, m_sGroupName);
}

void OgSceneLoader::processClipping(TiXmlElement *XMLNode)
{
	////! @todo Implement this

	//// Process attributes
	//Real fNear = parseReal(getAttrib(XMLNode, "near", 0);
	//Real fFar = parseReal(getAttrib(XMLNode, "far", 1);
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
