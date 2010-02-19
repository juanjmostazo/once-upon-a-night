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
	tCameraParameters.TRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
	tCameraParameters.TRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"camera::position");
	tCameraParameters.TRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
	tCameraParameters.TRenderComponentCameraParameters.FOVy = getPropertyReal(XMLNode,"camera::fov");
	tCameraParameters.TRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"camera::viewmode");

		//PolygonMode conversion
	int polygonmode = getPropertyInt(XMLNode,"camera::polymode");
	switch(polygonmode)
	{
			case OGITOR_PM_POINTS:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_SOLID:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_WIREFRAME:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Viewport Camera has unrecognised Camera Type");
				break;
	}


	//Create Camera
//	pGameWorldManager->createCamera(tCameraParameters);
}



void LevelLoader::processViewport(TiXmlElement *XMLNode)
{
	TViewportParameters tViewPortParameters;

	//Get Viewport name
	tViewPortParameters.name = getAttrib(XMLNode, "name");

	//Get Viewport properties
	tViewPortParameters.TRenderComponentViewportParameters.colour = getPropertyColourValue(XMLNode,"colour");
	tViewPortParameters.TRenderComponentViewportParameters.compositorcount = getPropertyInt(XMLNode,"compositorcount");
	tViewPortParameters.TRenderComponentViewportParameters.index = getPropertyInt(XMLNode,"index");
	tViewPortParameters.TRenderComponentViewportParameters.overlays = getPropertyBool(XMLNode,"overlays");
	tViewPortParameters.TRenderComponentViewportParameters.shadows = getPropertyBool(XMLNode,"shadows");
	tViewPortParameters.TRenderComponentViewportParameters.skies = getPropertyBool(XMLNode,"skies");

	//Create Viewport
//	pGameWorldManager->createViewport(tViewPortParameters);

	//Process Viewport camera
	processViewportCamera(XMLNode);
	
}

void LevelLoader::processOctreeSceneManager(TiXmlElement *XMLNode)
{
	TSceneManagerParameters tSceneManagerParameters;

	//Get OctreeSceneManager name
	tSceneManagerParameters.name = getAttrib(XMLNode, "name");

	//Get SceneManager properties
	tSceneManagerParameters.TRenderComponentSceneParameters.ambient=getPropertyColourValue(XMLNode,"ambient");

	//Process SkyBox
	tSceneManagerParameters.TRenderComponentSceneParameters.TRenderComponentSkyBoxParameters=processSkyBox(XMLNode);

	//Process SkyDome
	tSceneManagerParameters.TRenderComponentSceneParameters.TRenderComponentSkyDomeParameters=processSkyDome(XMLNode);

	//TODO: Process Fog
	//processFog(XMLNode);

	//TODO: Process Shadows
	//processShadows(XMLNode);

	//Set SceneManager parameters
//	pGameWorldManager->createSceneManager(tSceneManagerParameters);

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
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.position = getPropertyVector3(XMLNode,"position");
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");

	tSceneNodeParameters.TRenderComponentSceneNodeParameters.scale=Vector3(0,0,0);
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.autotracktarget="None";
	
	//create SceneNode
//	pGameWorldManager->createSceneNode(tSceneNodeParameters);
}

void LevelLoader::processLight(TiXmlElement *XMLNode)
{
	TLightParameters tLightParameters;

	//Parse and create Scene node
	processSceneNodeNoScale(XMLNode);

	//Get Light name
	tLightParameters.name = getAttrib(XMLNode, "name");

	//Get Light properties
	
	tLightParameters.TRenderComponentLightParameters.diffuse = getPropertyColourValue(XMLNode,"diffuse");
	tLightParameters.TRenderComponentLightParameters.specular = getPropertyColourValue(XMLNode,"specular");
	tLightParameters.TRenderComponentLightParameters.direction = getPropertyVector3(XMLNode,"direction");
	tLightParameters.TRenderComponentLightParameters.castshadows = getPropertyBool(XMLNode,"castshadows");
	tLightParameters.TRenderComponentLightParameters.lightrange = getPropertyVector3(XMLNode,"lightrange");
	tLightParameters.TRenderComponentLightParameters.attenuation = getPropertyVector4(XMLNode,"attenuation");
	tLightParameters.TRenderComponentLightParameters.power = getPropertyReal(XMLNode,"power");

		//Lightype conversion
	int lighttype = getPropertyInt(XMLNode,"lighttype");
	switch(lighttype)
	{
			case OGITOR_LT_POINT:
				tLightParameters.TRenderComponentLightParameters.lighttype=Ogre::Light::LT_POINT;
				break;
			case OGITOR_LT_DIRECTIONAL:
				tLightParameters.TRenderComponentLightParameters.lighttype=Ogre::Light::LT_DIRECTIONAL;
				break;
			case OGITOR_LT_SPOTLIGHT:
				tLightParameters.TRenderComponentLightParameters.lighttype=Ogre::Light::LT_SPOTLIGHT;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Light "+tLightParameters.name+" has unrecognised light type!");
				break;
	}

	//Create Light
//	pGameWorldManager->createLight(tLightParameters);

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
	tCameraParameters.TRenderComponentCameraParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");
	tCameraParameters.TRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tCameraParameters.TRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"position");
	tCameraParameters.TRenderComponentCameraParameters.autoaspectratio = getPropertyBool(XMLNode,"autoaspectratio");
	tCameraParameters.TRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"clipdistance");
	tCameraParameters.TRenderComponentCameraParameters.FOVy = getPropertyReal(XMLNode,"fov");
	tCameraParameters.TRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"viewmode");

		//PolygonModeConversion
	int polygonmode = getPropertyInt(XMLNode,"polygonmode");
	switch(polygonmode)
		{
			case OGITOR_PM_SOLID:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_POINTS:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_WIREFRAME:
				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Camera "+tCameraParameters.name+" has unrecognised PolygonMode!");
				break;
		}

	//Create Camera
//	pGameWorldManager->createCamera(tCameraParameters);
}



TRenderComponentSceneNodeParameters LevelLoader::processSceneNode(TiXmlElement *XMLNode)
{
	TSceneNodeParameters tSceneNodeParameters;

	//Get SceneNode name
	tSceneNodeParameters.name = getAttrib(XMLNode, "name");

	//Get parent SceneNode name
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.position = getPropertyVector3(XMLNode,"position");
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.scale = getPropertyVector3(XMLNode,"scale");
	tSceneNodeParameters.TRenderComponentSceneNodeParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");

	//create SceneNode
//	pGameWorldManager->createSceneNode(tSceneNodeParameters);

	return tSceneNodeParameters.TRenderComponentSceneNodeParameters;
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

void LevelLoader::processSubentities(std::vector<TRenderComponentSubEntityParameters> &tRenderComponentSubEntityParameters,TiXmlElement *XMLNode)
{
		int i;

		TRenderComponentSubEntityParameters currentRenderComponentSubEntityParameters;
 
		//process and load all Entity's SubEntites
		i=0;
		while(true)
		{
			//Process SubEntity
			currentRenderComponentSubEntityParameters.material=getPropertyString(XMLNode,"subentity"+StringConverter::toString(i)+"::material");
			currentRenderComponentSubEntityParameters.visible=getPropertyBool(XMLNode,"subentity"+StringConverter::toString(i)+"::visible");

			//there is no more sub entities
			if(currentRenderComponentSubEntityParameters.material.compare("")==0) break;

			//create SubEntity
			tRenderComponentSubEntityParameters.push_back(currentRenderComponentSubEntityParameters);

			i++;
		}
}

void LevelLoader::processEntity(TiXmlElement *XMLNode)
{
	TEntityParameters tEntityParameters;

	//Process the entity scene node
	tEntityParameters.TRenderComponentSceneNodeParameters=processSceneNode(XMLNode);
	
	//Get Entity name
	tEntityParameters.name = getAttrib(XMLNode, "name");
	//LogManager::getSingleton().logMessage("[LevelLoader] creating "+name+" entity");

	//Process entity properties
	tEntityParameters.TRenderComponentEntityParameters.meshfile = getPropertyString(XMLNode, "meshfile");
	tEntityParameters.TRenderComponentEntityParameters.castshadows = getPropertyBool(XMLNode, "castshadows");

	//process Entity's SubEntites
	processSubentities(tEntityParameters.TRenderComponentEntityParameters.TRenderComponentSubEntityParameters,XMLNode);

	//process Entity's Trajectory 
	//processTrajectory(XMLNode);//TODO

	
	//Create Entity
	pGameWorldManager->createGameObjectMovableEntity(tEntityParameters);


}

void LevelLoader::processParticleSystem(TiXmlElement *XMLNode)
{

	TParticleSystemParameters tParticleSystemParameters;

	//Process the entity scene node
	processSceneNode(XMLNode);
	
	//Get ParticleSystem name
	tParticleSystemParameters.name = getAttrib(XMLNode, "name");

	//Process ParticleSystem properties
	tParticleSystemParameters.TRenderComponentParticleSystemParameters.particle = getPropertyString(XMLNode, "particle");
	tParticleSystemParameters.TRenderComponentParticleSystemParameters.castshadows = getPropertyBool(XMLNode, "castshadows");
	
	//Create ParticleSystem
//	pGameWorldManager->createParticleSystem(tParticleSystemParameters);

}

void LevelLoader::processBillboards(std::vector<TRenderComponentBillboardParameters> &tRenderComponentBillboardParameters,TiXmlElement *XMLNode)
{

	int i;
	TRenderComponentBillboardParameters currentRenderComponentBillboardParameters;

	//get the number of BillboardSet's Billboards
	int billboardcount=getPropertyInt(XMLNode,"billboardcount");

	//process and load all BillboardSet's Billboards
	for(i=0;i<billboardcount;i++)
	{
		//Process Billboards
		currentRenderComponentBillboardParameters.colour=getPropertyColourValue(XMLNode,"billboard"+StringConverter::toString(i)+"::colour");
		currentRenderComponentBillboardParameters.dimensions=getPropertyVector2(XMLNode,"billboard"+StringConverter::toString(i)+"::dimensions");
		currentRenderComponentBillboardParameters.position=getPropertyVector3(XMLNode,"billboard"+StringConverter::toString(i)+"::position");
		currentRenderComponentBillboardParameters.rotation=getPropertyReal(XMLNode,"billboard"+StringConverter::toString(i)+"::rotation");
		currentRenderComponentBillboardParameters.texcoordindex=getPropertyInt(XMLNode,"billboard"+StringConverter::toString(i)+"::texcoordindex");
		currentRenderComponentBillboardParameters.texrect=getPropertyVector4(XMLNode,"billboard"+StringConverter::toString(i)+"::texrect");

		tRenderComponentBillboardParameters.push_back(currentRenderComponentBillboardParameters);
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
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.material = getPropertyString(XMLNode, "material");
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.defaultheight = getPropertyReal(XMLNode, "defaultheight");
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.defaultwidth = getPropertyReal(XMLNode, "defaultwidth");
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.pointrendering = getPropertyBool(XMLNode, "pointrendering");
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.renderdistance = getPropertyReal(XMLNode, "renderdistance");
	tBillboardSetParameters.TRenderComponentBillboardSetParameters.sorting = getPropertyBool(XMLNode, "sorting");

		//BillboardType Conversion
	int billboardtype = getPropertyInt(XMLNode, "billboardtype");
	switch(billboardtype)
	{
		case OGITOR_BBT_ORIENTED_COMMON:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_ORIENTED_COMMON;
			break;
		case OGITOR_BBT_ORIENTED_SELF:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_ORIENTED_SELF;
			break;
		case OGITOR_BBT_PERPENDICULAR_COMMON:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_PERPENDICULAR_COMMON;
			break;
		case OGITOR_BBT_PERPENDICULAR_SELF:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_PERPENDICULAR_SELF;
			break;
		case OGITOR_BBT_POINT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_POINT;
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
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_CENTER;
			break;
		case OGITOR_BBO_BOTTOM_LEFT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_LEFT;
			break;
		case OGITOR_BBO_BOTTOM_RIGHT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_RIGHT;
			break;
		case OGITOR_BBO_CENTER:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER;
			break;
		case OGITOR_BBO_CENTER_LEFT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER_LEFT;
			break;
		case OGITOR_BBO_CENTER_RIGHT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER_RIGHT;
			break;
		case OGITOR_BBO_TOP_CENTER:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_CENTER;
			break;
		case OGITOR_BBO_TOP_LEFT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_LEFT;
			break;
		case OGITOR_BBO_TOP_RIGHT:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_RIGHT;
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
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardrotation=Ogre::BBR_TEXCOORD;
			break;
		case OGITOR_BBR_VERTEX:
			tBillboardSetParameters.TRenderComponentBillboardSetParameters.billboardrotation=Ogre::BBR_VERTEX;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard "+tBillboardSetParameters.name+" has unrecognised BillboardRotationType!");
			break;
	}

	//process BillboardSet's Billboards
	processBillboards(tBillboardSetParameters.TRenderComponentBillboardSetParameters.TRenderComponentBillboardParameters,XMLNode);

	
	//Create BillboardSet
//	pGameWorldManager->createBillboardSet(tBillboardSetParameters);


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

TRenderComponentSkyBoxParameters LevelLoader::processSkyBox(TiXmlElement *XMLNode)
{
	TRenderComponentSkyBoxParameters TRenderComponentSkyBoxParameters;
	// Process SkyBox properties
	TRenderComponentSkyBoxParameters.active = getPropertyBool(XMLNode, "skybox::active");
	TRenderComponentSkyBoxParameters.material = getPropertyString(XMLNode, "skybox::material");
	TRenderComponentSkyBoxParameters.distance = getPropertyReal(XMLNode, "skybox::distance");

	return TRenderComponentSkyBoxParameters;
}



TRenderComponentSkyDomeParameters LevelLoader::processSkyDome(TiXmlElement *XMLNode)
{
	TRenderComponentSkyDomeParameters TRenderComponentSkyDomeParameters;
	// Process SkyDome properties
	TRenderComponentSkyDomeParameters.active = getPropertyBool(XMLNode, "skydome::active");
	TRenderComponentSkyDomeParameters.material = getPropertyString(XMLNode, "skydome::material");
	
	return TRenderComponentSkyDomeParameters;
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
