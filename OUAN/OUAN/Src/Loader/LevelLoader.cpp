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
//
//void LevelLoader::processResourceLocations(TiXmlElement *XMLNode)
//{
//	//TODO
//}

void LevelLoader::processViewportCamera(TiXmlElement *XMLNode)
{
	TCameraParameters tCameraParameters;

	tCameraParameters.name="Viewport#1";

	//Get Camera properties
	tCameraParameters.tCameraRenderParameters.orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
	tCameraParameters.tCameraRenderParameters.position = getPropertyVector3(XMLNode,"camera::position");
	tCameraParameters.tCameraRenderParameters.clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
	tCameraParameters.tCameraRenderParameters.FOVy = getPropertyReal(XMLNode,"camera::fov");
	tCameraParameters.tCameraRenderParameters.viewmode = getPropertyInt(XMLNode,"camera::viewmode");

		//PolygonMode conversion
	int polygonmode = getPropertyInt(XMLNode,"camera::polymode");
	switch(polygonmode)
	{
			case OGITOR_PM_POINTS:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_SOLID:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_WIREFRAME:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Viewport Camera has unrecognised Camera Type");
				break;
	}


	//Create Camera
	pGameWorldManager->createCamera(tCameraParameters);
}



void LevelLoader::processViewport(TiXmlElement *XMLNode)
{
	TViewportParameters tViewPortParameters;

	//Get Viewport name
	tViewPortParameters.name = getAttrib(XMLNode, "name");

	//Get Viewport properties
	tViewPortParameters.tViewPortRenderParameters.colour = getPropertyColourValue(XMLNode,"colour");
	tViewPortParameters.tViewPortRenderParameters.compositorcount = getPropertyInt(XMLNode,"compositorcount");
	tViewPortParameters.tViewPortRenderParameters.index = getPropertyInt(XMLNode,"index");
	tViewPortParameters.tViewPortRenderParameters.overlays = getPropertyBool(XMLNode,"overlays");
	tViewPortParameters.tViewPortRenderParameters.shadows = getPropertyBool(XMLNode,"shadows");
	tViewPortParameters.tViewPortRenderParameters.skies = getPropertyBool(XMLNode,"skies");

	//Create Viewport
	pGameWorldManager->createViewport(tViewPortParameters);

	//Process Viewport camera
	processViewportCamera(XMLNode);
	
}

void LevelLoader::processOctreeSceneManager(TiXmlElement *XMLNode)
{
	TSceneManagerParameters tSceneManagerParameters;

	//Get OctreeSceneManager name
	tSceneManagerParameters.name = getAttrib(XMLNode, "name");

	//Get SceneManager properties
	tSceneManagerParameters.tSceneManagerRenderParameters.ambient=getPropertyColourValue(XMLNode,"ambient");

	//Process SkyBox
	tSceneManagerParameters.tSceneManagerRenderParameters.tSkyBoxRenderParameters=processSkyBox(XMLNode);

	//Process SkyDome
	tSceneManagerParameters.tSceneManagerRenderParameters.tSkyDomeRenderParameters=processSkyDome(XMLNode);

	//TODO: Process Fog
	//processFog(XMLNode);

	//TODO: Process Shadows
	//processShadows(XMLNode);

	//Set SceneManager parameters
	pGameWorldManager->createSceneManager(tSceneManagerParameters);

}

//void LevelLoader::processTerrain(TiXmlElement *XMLNode)
//{
//	//! @todo Implement this
//}

void LevelLoader::processSceneNodeNoScale(TiXmlElement *XMLNode)
{
	TSceneNodeParameters tSceneNodeParameters;

	//Get SceneNode name
	tSceneNodeParameters.name = getAttrib(XMLNode, "name");

	//Get parent SceneNode name
	tSceneNodeParameters.tSceneNodeRenderParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tSceneNodeParameters.tSceneNodeRenderParameters.position = getPropertyVector3(XMLNode,"position");
	tSceneNodeParameters.tSceneNodeRenderParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");

	tSceneNodeParameters.tSceneNodeRenderParameters.scale=Vector3(0,0,0);
	tSceneNodeParameters.tSceneNodeRenderParameters.autotracktarget="None";
	
	//create SceneNode
	pGameWorldManager->createSceneNode(tSceneNodeParameters);
}

void LevelLoader::processLight(TiXmlElement *XMLNode)
{
	TLightParameters tLightParameters;

	//Parse and create Scene node
	processSceneNodeNoScale(XMLNode);

	//Get Light name
	tLightParameters.name = getAttrib(XMLNode, "name");

	//Get Light properties
	
	tLightParameters.tLightRenderParameters.diffuse = getPropertyColourValue(XMLNode,"diffuse");
	tLightParameters.tLightRenderParameters.specular = getPropertyColourValue(XMLNode,"specular");
	tLightParameters.tLightRenderParameters.direction = getPropertyVector3(XMLNode,"direction");
	tLightParameters.tLightRenderParameters.castshadows = getPropertyBool(XMLNode,"castshadows");
	tLightParameters.tLightRenderParameters.lightrange = getPropertyVector3(XMLNode,"lightrange");
	tLightParameters.tLightRenderParameters.attenuation = getPropertyVector4(XMLNode,"attenuation");
	tLightParameters.tLightRenderParameters.power = getPropertyReal(XMLNode,"power");

		//Lightype conversion
	int lighttype = getPropertyInt(XMLNode,"lighttype");
	switch(lighttype)
	{
			case OGITOR_LT_POINT:
				tLightParameters.tLightRenderParameters.lighttype=Ogre::Light::LT_POINT;
				break;
			case OGITOR_LT_DIRECTIONAL:
				tLightParameters.tLightRenderParameters.lighttype=Ogre::Light::LT_DIRECTIONAL;
				break;
			case OGITOR_LT_SPOTLIGHT:
				tLightParameters.tLightRenderParameters.lighttype=Ogre::Light::LT_SPOTLIGHT;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Light "+tLightParameters.name+" has unrecognised light type!");
				break;
	}

	//Create Light
	pGameWorldManager->createLight(tLightParameters);

}

//void LevelLoader::processTrajectory(TiXmlElement *XMLNode)
//{
//	//String name;
//	//
//	////Get Trajectory name
//	//name = getAttrib(XMLNode, "name");
//
//	//int i;
//	//String node;
//
//	//if(trajectory.trajectoryNodes.size()==0)
//	//{
//	//	trajectory.initialise(mSceneManager);
//	//}
//
//	//i=0;
//	//node=getPropertyString(XMLNode,"Trajectory::"+StringConverter::toString(i));
//	//while(node.compare("")!=0)
//	//{
//	//	trajectory.addNode(node);
//	//	i++;
//	//	node=getPropertyString(XMLNode,"Trajectory::"+StringConverter::toString(i));
//	//}
//
//	//
//}

void LevelLoader::processCamera(TiXmlElement *XMLNode)
{
	TCameraParameters tCameraParameters;

	//Get Camera name
	tCameraParameters.name = getAttrib(XMLNode, "name");

	//Get Camera properties
	tCameraParameters.tCameraRenderParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");
	tCameraParameters.tCameraRenderParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tCameraParameters.tCameraRenderParameters.position = getPropertyVector3(XMLNode,"position");
	tCameraParameters.tCameraRenderParameters.autoaspectratio = getPropertyBool(XMLNode,"autoaspectratio");
	tCameraParameters.tCameraRenderParameters.clipdistance = getPropertyVector2(XMLNode,"clipdistance");
	tCameraParameters.tCameraRenderParameters.FOVy = getPropertyReal(XMLNode,"fov");
	tCameraParameters.tCameraRenderParameters.viewmode = getPropertyInt(XMLNode,"viewmode");

		//PolygonModeConversion
	int polygonmode = getPropertyInt(XMLNode,"polygonmode");
	switch(polygonmode)
		{
			case OGITOR_PM_SOLID:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_POINTS:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_WIREFRAME:
				tCameraParameters.tCameraRenderParameters.polygonmode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Camera "+tCameraParameters.name+" has unrecognised PolygonMode!");
				break;
		}

	//Create Camera
	pGameWorldManager->createCamera(tCameraParameters);
}



void LevelLoader::processSceneNode(TiXmlElement *XMLNode)
{
	TSceneNodeParameters tSceneNodeParameters;

	//Get SceneNode name
	tSceneNodeParameters.name = getAttrib(XMLNode, "name");

	//Get parent SceneNode name
	tSceneNodeParameters.tSceneNodeRenderParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tSceneNodeParameters.tSceneNodeRenderParameters.position = getPropertyVector3(XMLNode,"position");
	tSceneNodeParameters.tSceneNodeRenderParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tSceneNodeParameters.tSceneNodeRenderParameters.scale = getPropertyVector3(XMLNode,"scale");
	tSceneNodeParameters.tSceneNodeRenderParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");

	//create SceneNode
	pGameWorldManager->createSceneNode(tSceneNodeParameters);
}

//void LevelLoader::processTrackTarget(TiXmlElement *XMLNode)
//{
//
//	//// Setup the track target
//	//try
//	//{
//	//	SceneNode *pTrackNode = mSceneManager->getSceneNode(nodeName);
//	//	pParent->setAutoTracking(true, pTrackNode, localDirection, offset);
//	//}
//	//catch(Ogre::Exception &/*e*/)
//	//{
//	//	LogManager::getSingleton().logMessage("[LevelLoader] Error processing a track target!");
//	//}
//}

void LevelLoader::processSubentities(std::vector<TSubEntityRenderParameters> &tSubEntityRenderParameters,TiXmlElement *XMLNode)
{
		int i;

		TSubEntityRenderParameters currentSubEntityRenderParameters;
 
		//process and load all Entity's SubEntites
		i=0;
		while(true)
		{
			//Process SubEntity
			currentSubEntityRenderParameters.material=getPropertyString(XMLNode,"subentity"+StringConverter::toString(i)+"::material");
			currentSubEntityRenderParameters.visible=getPropertyBool(XMLNode,"subentity"+StringConverter::toString(i)+"::visible");

			//there is no more sub entities
			if(currentSubEntityRenderParameters.material.compare("")==0) break;

			//create SubEntity
			tSubEntityRenderParameters.push_back(currentSubEntityRenderParameters);

			i++;
		}
}

void LevelLoader::processEntity(TiXmlElement *XMLNode)
{
	TEntityParameters tEntityParameters;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get Entity name
	tEntityParameters.name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[LevelLoader] creating "+name+" entity");

	//Process entity properties
	tEntityParameters.tEntityRenderParameters.meshfile = getPropertyString(XMLNode, "meshfile");
	tEntityParameters.tEntityRenderParameters.castshadows = getPropertyBool(XMLNode, "castshadows");

	//process Entity's SubEntites
	processSubentities(tEntityParameters.tEntityRenderParameters.tSubEntityRenderParameters,XMLNode);

	//process Entity's Trajectory 
	//processTrajectory(XMLNode);//TODO

	
	//Create Entity
	pGameWorldManager->createGameObjectEntity(tEntityParameters);


}

void LevelLoader::processParticleSystem(TiXmlElement *XMLNode)
{

	TParticleSystemParameters tParticleSystemParameters;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get ParticleSystem name
	tParticleSystemParameters.name = getAttrib(XMLNode, "name");

	//Process ParticleSystem properties
	tParticleSystemParameters.tParticleSystemRenderParameters.particle = getPropertyString(XMLNode, "particle");
	tParticleSystemParameters.tParticleSystemRenderParameters.castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create ParticleSystem
	pGameWorldManager->createParticleSystem(tParticleSystemParameters);

}

void LevelLoader::processBillboards(std::vector<TBillboardRenderParameters> &tBillboardRenderParameters,TiXmlElement *XMLNode)
{

	int i;
	TBillboardRenderParameters currentTBillboardRenderParameters;

	//get the number of BillboardSet's Billboards
	int billboardcount=getPropertyInt(XMLNode,"billboardcount");

	//process and load all BillboardSet's Billboards
	for(i=0;i<billboardcount;i++)
	{
		//Process Billboards
		currentTBillboardRenderParameters.colour=getPropertyColourValue(XMLNode,"billboard"+StringConverter::toString(i)+"::colour");
		currentTBillboardRenderParameters.dimensions=getPropertyVector2(XMLNode,"billboard"+StringConverter::toString(i)+"::dimensions");
		currentTBillboardRenderParameters.position=getPropertyVector3(XMLNode,"billboard"+StringConverter::toString(i)+"::position");
		currentTBillboardRenderParameters.rotation=getPropertyReal(XMLNode,"billboard"+StringConverter::toString(i)+"::rotation");
		currentTBillboardRenderParameters.texcoordindex=getPropertyInt(XMLNode,"billboard"+StringConverter::toString(i)+"::texcoordindex");
		currentTBillboardRenderParameters.texrect=getPropertyVector4(XMLNode,"billboard"+StringConverter::toString(i)+"::texrect");

		tBillboardRenderParameters.push_back(currentTBillboardRenderParameters);
	}
	
}

void LevelLoader::processBillboardSet(TiXmlElement *XMLNode)
{
	TBillboardSetParameters tBillboardSetParameters;

	//Process the BillboardSet scene node
	processSceneNode(XMLNode);
	
	//Get BillboardSet name
	tBillboardSetParameters.name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[LevelLoader] creating "+name+" BillboardSet");

	//Process BillboardSet properties
	tBillboardSetParameters.tBillboardSetRenderParameters.material = getPropertyString(XMLNode, "material");
	tBillboardSetParameters.tBillboardSetRenderParameters.defaultheight = getPropertyReal(XMLNode, "defaultheight");
	tBillboardSetParameters.tBillboardSetRenderParameters.defaultwidth = getPropertyReal(XMLNode, "defaultwidth");
	tBillboardSetParameters.tBillboardSetRenderParameters.pointrendering = getPropertyBool(XMLNode, "pointrendering");
	tBillboardSetParameters.tBillboardSetRenderParameters.renderdistance = getPropertyReal(XMLNode, "renderdistance");
	tBillboardSetParameters.tBillboardSetRenderParameters.sorting = getPropertyBool(XMLNode, "sorting");

		//BillboardType Conversion
	int billboardtype = getPropertyInt(XMLNode, "billboardtype");
	switch(billboardtype)
	{
		case OGITOR_BBT_ORIENTED_COMMON:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardtype=Ogre::BBT_ORIENTED_COMMON;
			break;
		case OGITOR_BBT_ORIENTED_SELF:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardtype=Ogre::BBT_ORIENTED_SELF;
			break;
		case OGITOR_BBT_PERPENDICULAR_COMMON:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardtype=Ogre::BBT_PERPENDICULAR_COMMON;
			break;
		case OGITOR_BBT_PERPENDICULAR_SELF:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardtype=Ogre::BBT_PERPENDICULAR_SELF;
			break;
		case OGITOR_BBT_POINT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardtype=Ogre::BBT_POINT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+tBillboardSetParameters.name+" has unrecognised BillboardType!");
			break;
	}
		//BillboardOrigin Conversion
	int billboardorigin = getPropertyInt(XMLNode, "billboardorigin");
	switch(billboardorigin)
	{
		case OGITOR_BBO_BOTTOM_CENTER:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_BOTTOM_CENTER;
			break;
		case OGITOR_BBO_BOTTOM_LEFT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_BOTTOM_LEFT;
			break;
		case OGITOR_BBO_BOTTOM_RIGHT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_BOTTOM_RIGHT;
			break;
		case OGITOR_BBO_CENTER:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_CENTER;
			break;
		case OGITOR_BBO_CENTER_LEFT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_CENTER_LEFT;
			break;
		case OGITOR_BBO_CENTER_RIGHT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_CENTER_RIGHT;
			break;
		case OGITOR_BBO_TOP_CENTER:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_TOP_CENTER;
			break;
		case OGITOR_BBO_TOP_LEFT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_TOP_LEFT;
			break;
		case OGITOR_BBO_TOP_RIGHT:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardorigin=Ogre::BBO_TOP_RIGHT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+tBillboardSetParameters.name+" has unrecognised BillboardOrigin!");
			break;
	}

	//Billboard Rotation Conversion
	int billboardrotation = getPropertyInt(XMLNode, "billboardrotation");
	switch(billboardrotation)
	{
		case OGITOR_BBR_TEXCOORD:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardrotation=Ogre::BBR_TEXCOORD;
			break;
		case OGITOR_BBR_VERTEX:
			tBillboardSetParameters.tBillboardSetRenderParameters.billboardrotation=Ogre::BBR_VERTEX;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+tBillboardSetParameters.name+" has unrecognised BillboardRotationType!");
			break;
	}

	//process BillboardSet's Billboards
	processBillboards(tBillboardSetParameters.tBillboardSetRenderParameters.tBillboardRenderParameters,XMLNode);

	
	//Create BillboardSet
	pGameWorldManager->createBillboardSet(tBillboardSetParameters);


}



//void LevelLoader::processPlane(TiXmlElement *XMLNode)
//{
//
//}
//
//void LevelLoader::processFog(TiXmlElement *XMLNode)
//{
//
//}

TSkyBoxRenderParameters LevelLoader::processSkyBox(TiXmlElement *XMLNode)
{
	TSkyBoxRenderParameters tSkyBoxRenderParameters;
	// Process SkyBox properties
	tSkyBoxRenderParameters.active = getPropertyBool(XMLNode, "skybox::active");
	tSkyBoxRenderParameters.material = getPropertyString(XMLNode, "skybox::material");
	tSkyBoxRenderParameters.distance = getPropertyReal(XMLNode, "skybox::distance");

	return tSkyBoxRenderParameters;
}



TSkyDomeRenderParameters LevelLoader::processSkyDome(TiXmlElement *XMLNode)
{
	TSkyDomeRenderParameters tSkyDomeRenderParameters;
	// Process SkyDome properties
	tSkyDomeRenderParameters.active = getPropertyBool(XMLNode, "skydome::active");
	tSkyDomeRenderParameters.material = getPropertyString(XMLNode, "skydome::material");
	
	return tSkyDomeRenderParameters;
}

//void LevelLoader::processShadows(TiXmlElement *XMLNode)
//{
//
//}

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
