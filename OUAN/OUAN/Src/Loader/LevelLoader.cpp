#include "LevelLoader.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"

using namespace OUAN;

LevelLoader::LevelLoader(){}
LevelLoader::~LevelLoader(){}

void LevelLoader::initialise(OUAN::ApplicationPtr app)
{
	this->pGameWorldManager=app->getGameWorldManager();
}

void LevelLoader::loadLevel(String level,String resourceGroupName)
{

	//TODO: CLEAR OLD LEVEL FROM GAME WORLD MANAGER

	TiXmlDocument   *XMLDoc = 0;
	TiXmlElement   *XMLRoot;

	Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Parsing level "+level);

	// Strip the path
	Ogre::String basename, path;
	Ogre::StringUtil::splitFilename(level, basename, path);

	Ogre::DataStreamPtr pStream = Ogre::ResourceGroupManager::getSingleton().openResource( basename, resourceGroupName );

	String data = pStream->getAsString();
	// Open the .ogscene File
	XMLDoc = new TiXmlDocument();
	XMLDoc->Parse( data.c_str() );
	pStream->close();
	pStream.setNull();

	// Validate the File
	XMLRoot = XMLDoc->RootElement();
	if( String( XMLRoot->Value()) != "OGITORSCENE"  ) {
		Ogre::LogManager::getSingleton().logMessage( "[LevelLoader] Error: Invalid .ogscene File. Missing <OGITORSCENE>" );
		delete XMLDoc;      
		return;
	}

	// Process the scene
	processScene(XMLRoot);

	Ogre::LogManager::getSingleton().logMessage( "[LevelLoader] Done!" );

	// Close the XML File
	delete XMLDoc;
}

void LevelLoader::processScene(TiXmlElement *XMLNode)
{

	// Process the scene parameters
	String version = getAttrib(XMLNode, "version", "unknown");

	String message = "[LevelLoader] Parsing ogScene file with version " + version;

	//LogManager::getSingleton().logMessage(message);

	//Process project
	processProject(XMLNode);
	
	//Process scene objects
	processObjects(XMLNode,"OctreeSceneManager");
	processObjects(XMLNode,"Viewport Object");
	processObjects(XMLNode,"Node Object");
	processObjects(XMLNode,"Marker Object");
	processObjects(XMLNode,"Light Object");
	processObjects(XMLNode,"Entity Object");
	processObjects(XMLNode,"Camera Object");
	processObjects(XMLNode,"Particle Object");
	processObjects(XMLNode,"BillboardSet Object");

}

void LevelLoader::processProject(TiXmlElement *XMLNode)
{
	TiXmlElement *pElement;

	// Process PROJECT
	pElement = XMLNode->FirstChildElement("PROJECT");
	if(pElement)
		processProject(pElement);
}

void LevelLoader::processObjects(TiXmlElement *XMLNode, String type)
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

void LevelLoader::processObject(TiXmlElement *XMLNode)
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
	else if( type.compare("Marker Object")==0)
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
		Ogre::LogManager::getSingleton().logMessage("Error reading "+type+" OBJECT");
	}
}

void LevelLoader::processResourceLocations(TiXmlElement *XMLNode)
{
	//TODO
}

void LevelLoader::processViewportCamera(TiXmlElement *XMLNode)
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

	Ogre::PolygonMode ogrePolygonMode;

	//PolygonMode conversion
	switch(polygonmode)
	{
			case OGITOR_PM_POINTS:
				ogrePolygonMode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_SOLID:
				ogrePolygonMode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_WIREFRAME:
				ogrePolygonMode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Viewport Camera has unrecognised Camera Type");
				break;
	}


	//Create Camera
	pGameWorldManager->createCamera("Ogitor",position,orientation,"None",true,clipdistance,fov,ogrePolygonMode,viewmode);
}



void LevelLoader::processViewport(TiXmlElement *XMLNode)
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
	pGameWorldManager->createViewport(name,colour,compositorcount,index,overlays,shadows,skies);

	//Process Viewport camera
	processViewportCamera(XMLNode);
	
}

void LevelLoader::processOctreeSceneManager(TiXmlElement *XMLNode)
{
	String name;
	ColourValue ambient;

	//Get OctreeSceneManager name
	name = getAttrib(XMLNode, "name");

	//Get SceneManager properties
	ambient=getPropertyColourValue(XMLNode,"ambient");
	//Set SceneManager parameters
	pGameWorldManager->createOctreeSceneManager(name,ambient);

	//Process SkyBox
	processSkyBox(XMLNode);

	//Process SkyDome
	processSkyDome(XMLNode);

	//Process Fog
	processFog(XMLNode);

	//Process Shadows
	processShadows(XMLNode);

}

void LevelLoader::processTerrain(TiXmlElement *XMLNode)
{
	//! @todo Implement this
}

void LevelLoader::processSceneNodeNoScale(TiXmlElement *XMLNode)
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
	pGameWorldManager->createSceneNode(name,parentnode,position,orientation,Vector3(0,0,0),"None");
}

void LevelLoader::processLight(TiXmlElement *XMLNode)
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
	Ogre::Light::LightTypes ogreLightType;

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

	//Lightype conversion
	switch(lighttype)
	{
			case OGITOR_LT_POINT:
				ogreLightType=Ogre::Light::LT_POINT;
				break;
			case OGITOR_LT_DIRECTIONAL:
				ogreLightType=Ogre::Light::LT_DIRECTIONAL;
				break;
			case OGITOR_LT_SPOTLIGHT:
				ogreLightType=Ogre::Light::LT_SPOTLIGHT;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Light "+name+" has unrecognised light type!");
				break;
	}

	//Create Light
	pGameWorldManager->createLight(name,ogreLightType,diffuse,specular,direction,castshadows,lightrange,attenuation,power);

}

void LevelLoader::processTrajectory(TiXmlElement *XMLNode)
{
	//String name;
	//
	////Get Trajectory name
	//name = getAttrib(XMLNode, "name");

	//int i;
	//String node;

	//if(trajectory.trajectoryNodes.size()==0)
	//{
	//	trajectory.initialise(mSceneManager);
	//}

	//i=0;
	//node=getPropertyString(XMLNode,"Trajectory::"+StringConverter::toString(i));
	//while(node.compare("")!=0)
	//{
	//	trajectory.addNode(node);
	//	i++;
	//	node=getPropertyString(XMLNode,"Trajectory::"+StringConverter::toString(i));
	//}

	//
}

void LevelLoader::processCamera(TiXmlElement *XMLNode)
{
	String name;
	String autotracktarget;
	Quaternion orientation;
	Vector3 position;
	bool autoaspectratio;
	Vector2 clipdistance;
	Real fov;
	int polygonmode;
	Ogre::PolygonMode ogrePolygonMode;
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

	switch(polygonmode)
		{
			case OGITOR_PM_SOLID:
				ogrePolygonMode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_POINTS:
				ogrePolygonMode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_WIREFRAME:
				ogrePolygonMode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Camera "+name+" has unrecognised PolygonMode!");
				break;
		}

	//Create Camera
	pGameWorldManager->createCamera(name,position,orientation,autotracktarget,autoaspectratio,clipdistance,fov,ogrePolygonMode,viewmode);
}



void LevelLoader::processSceneNode(TiXmlElement *XMLNode)
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
	pGameWorldManager->createSceneNode(name,parentnode,position,orientation,scale,autotracktarget);
}

void LevelLoader::processTrackTarget(TiXmlElement *XMLNode)
{

	//// Setup the track target
	//try
	//{
	//	SceneNode *pTrackNode = mSceneManager->getSceneNode(nodeName);
	//	pParent->setAutoTracking(true, pTrackNode, localDirection, offset);
	//}
	//catch(Ogre::Exception &/*e*/)
	//{
	//	LogManager::getSingleton().logMessage("[LevelLoader] Error processing a track target!");
	//}
}

void LevelLoader::processSubentities(String name,TiXmlElement *XMLNode)
{
		int i;

		String material;
		bool visible;
 
		//process and load all Entity's SubEntites
		i=0;
		while(true)
		{
			//Process SubEntity
			material=getPropertyString(XMLNode,"subentity"+StringConverter::toString(i)+"::material");
			visible=getPropertyBool(XMLNode,"subentity"+StringConverter::toString(i)+"::visible");

			//there is no more sub entities
			if(material.compare("")==0) break;

			//create SubEntity
			pGameWorldManager->createSubEntity(name,i,material,visible);

			i++;
		}
}

void LevelLoader::processEntity(TiXmlElement *XMLNode)
{
	String name;
	String meshfile;
	bool castshadows;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get Entity name
	name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[LevelLoader] creating "+name+" entity");

	//Process entity properties
	meshfile = getPropertyString(XMLNode, "meshfile");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create Entity
	pGameWorldManager->createEntity(name,meshfile,castshadows);

	//process Entity's SubEntites
	processSubentities(name,XMLNode);

	//process Entity's Trajectory
	processTrajectory(XMLNode);

}

void LevelLoader::processParticleSystem(TiXmlElement *XMLNode)
{

	OUAN::String particle;
	bool castshadows;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get ParticleSystem name
	String name = getAttrib(XMLNode, "name");

	//Process ParticleSystem properties
	particle = getPropertyString(XMLNode, "particle");
	castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create ParticleSystem
	pGameWorldManager->createParticleSystem(name,particle,castshadows);

}

void LevelLoader::processBillboards(OUAN::String billBoardSetName,TiXmlElement *XMLNode)
{

	int i;
	int billboardcount;
	ColourValue colour;
	Vector2 dimensions;
	Vector3 position;
	Real rotation;
	int texcoordindex;
	Vector4 texrect;
	
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
		pGameWorldManager->createBillboard(billBoardSetName,colour,dimensions,position,rotation,texcoordindex,texrect);
	}
	
}

void LevelLoader::processBillboardSet(TiXmlElement *XMLNode)
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
	Ogre::BillboardRotationType ogreBillboardRotationType;
	Ogre::BillboardType ogreBillboardType;
	Ogre::BillboardOrigin ogreBillboardOrigin;

	//Process the BillboardSet scene node
	processSceneNode(XMLNode);
	
	//Get BillboardSet name
	name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[LevelLoader] creating "+name+" BillboardSet");

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

	switch(billboardtype)
	{
		case OGITOR_BBT_ORIENTED_COMMON:
			ogreBillboardType=Ogre::BBT_ORIENTED_COMMON;
			break;
		case OGITOR_BBT_ORIENTED_SELF:
			ogreBillboardType=Ogre::BBT_ORIENTED_SELF;
			break;
		case OGITOR_BBT_PERPENDICULAR_COMMON:
			ogreBillboardType=Ogre::BBT_PERPENDICULAR_COMMON;
			break;
		case OGITOR_BBT_PERPENDICULAR_SELF:
			ogreBillboardType=Ogre::BBT_PERPENDICULAR_SELF;
			break;
		case OGITOR_BBT_POINT:
			ogreBillboardType=Ogre::BBT_POINT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardType!");
			break;
	}

	switch(billboardorigin)
	{
		case OGITOR_BBO_BOTTOM_CENTER:
			ogreBillboardOrigin=Ogre::BBO_BOTTOM_CENTER;
			break;
		case OGITOR_BBO_BOTTOM_LEFT:
			ogreBillboardOrigin=Ogre::BBO_BOTTOM_LEFT;
			break;
		case OGITOR_BBO_BOTTOM_RIGHT:
			ogreBillboardOrigin=Ogre::BBO_BOTTOM_RIGHT;
			break;
		case OGITOR_BBO_CENTER:
			ogreBillboardOrigin=Ogre::BBO_CENTER;
			break;
		case OGITOR_BBO_CENTER_LEFT:
			ogreBillboardOrigin=Ogre::BBO_CENTER_LEFT;
			break;
		case OGITOR_BBO_CENTER_RIGHT:
			ogreBillboardOrigin=Ogre::BBO_CENTER_RIGHT;
			break;
		case OGITOR_BBO_TOP_CENTER:
			ogreBillboardOrigin=Ogre::BBO_TOP_CENTER;
			break;
		case OGITOR_BBO_TOP_LEFT:
			ogreBillboardOrigin=Ogre::BBO_TOP_LEFT;
			break;
		case OGITOR_BBO_TOP_RIGHT:
			ogreBillboardOrigin=Ogre::BBO_TOP_RIGHT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardOrigin!");
			break;
	}

	switch(billboardrotation)
	{
		case OGITOR_BBR_TEXCOORD:
			ogreBillboardRotationType=Ogre::BBR_TEXCOORD;
			break;
		case OGITOR_BBR_VERTEX:
			ogreBillboardRotationType=Ogre::BBR_VERTEX;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+name+" has unrecognised BillboardRotationType!");
			break;
	}
	
	//Create BillboardSet
	pGameWorldManager->createBillboardSet(name,material,ogreBillboardOrigin,ogreBillboardRotationType,ogreBillboardType,defaultheight,defaultwidth,pointrendering,renderdistance,sorting);

	//process BillboardSet's Billboards
	processBillboards(name,XMLNode);
}



void LevelLoader::processPlane(TiXmlElement *XMLNode)
{

}

void LevelLoader::processFog(TiXmlElement *XMLNode)
{

}

void LevelLoader::processSkyBox(TiXmlElement *XMLNode)
{
	// Process SkyBox properties
	bool active = getPropertyBool(XMLNode, "skybox::active");
	String material = getPropertyString(XMLNode, "skybox::material");
	Real distance = getPropertyReal(XMLNode, "skybox::distance");

	
	//Create the SkyBox
	pGameWorldManager->createSkyBox(active, material, distance);
}



void LevelLoader::processSkyDome(TiXmlElement *XMLNode)
{
	// Process SkyDome properties
	bool active = getPropertyBool(XMLNode, "skydome::active");
	String material = getPropertyString(XMLNode, "skydome::material");
	
	//Create the SkyDome
	pGameWorldManager->createSkyDome(active, material);
}

void LevelLoader::processShadows(TiXmlElement *XMLNode)
{

}

String LevelLoader::getAttrib(TiXmlElement *XMLNode, const String &attrib, const String &defaultValue)
{
	if(XMLNode->Attribute(attrib.c_str()))
		return XMLNode->Attribute(attrib.c_str());
	else
		return defaultValue;
}


String LevelLoader::getPropertyString(TiXmlElement *XMLNode, const String &attrib_name)
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

		//LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

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

		//LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

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
		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error parsing "+attrib_name+" attribute!");
	}
	return result;
}

Vector2 LevelLoader::getPropertyVector2(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector2(getPropertyString(XMLNode,attrib_name));
}

Vector3 LevelLoader::getPropertyVector3(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector3(getPropertyString(XMLNode,attrib_name));
}

Vector4 LevelLoader::getPropertyVector4(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseVector4(getPropertyString(XMLNode,attrib_name));
}

Quaternion LevelLoader::getPropertyQuaternion(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseQuaternion(getPropertyString(XMLNode,attrib_name));
}

ColourValue LevelLoader::getPropertyColourValue(TiXmlElement *XMLNode, const String &attrib_name)
{
	return StringConverter::parseColourValue(getPropertyString(XMLNode,attrib_name));
}

bool LevelLoader::getPropertyBool(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseBool(getPropertyString(XMLNode,attrib_name));
}

int LevelLoader::getPropertyInt(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseInt(getPropertyString(XMLNode,attrib_name));
}

Real LevelLoader::getPropertyReal(TiXmlElement *XMLNode, const String &attrib_name)
{
	 return StringConverter::parseReal(getPropertyString(XMLNode,attrib_name));
}
