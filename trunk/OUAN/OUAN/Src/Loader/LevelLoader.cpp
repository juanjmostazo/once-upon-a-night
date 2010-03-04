#include "LevelLoader.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Component/Component.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectLight.h"
#include "../Game/GameObject/GameObjectBillboardSet.h"
#include "../Game/GameObject/GameObjectParticleSystem.h"
#include "../Game/GameObject/GameObjectTerrain.h"
#include "../Game/GameObject/GameObjectScene.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectCamera.h"
#include "../Game/GameObject/GameObjectVolumeBox.h"
#include "../Game/GameObject/GameObjectVolumeCapsule.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Physics/PhysicsComponent/PhysicsComponent.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimple.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"

using namespace OUAN;

LevelLoader::LevelLoader(){}
LevelLoader::~LevelLoader(){}

void LevelLoader::init(OUAN::ApplicationPtr app)
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
	processLevel(XMLRoot);

	Ogre::LogManager::getSingleton().logMessage( "[LevelLoader] Done!" );

	// Close the XML File
	delete XMLDoc;
}

void LevelLoader::processLevel(TiXmlElement *XMLNode)
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

std::string LevelLoader::getGameObjectType(TiXmlElement *XMLNode)
{
	String type = getAttrib(XMLNode, "typename");
	String name = getAttrib(XMLNode, "name");

	if( type.compare("OctreeSceneManager")==0)
	{
		return GAME_OBJECT_TYPE_SCENE;
	}
	else if( type.compare("Viewport Object")==0)
	{
		return GAME_OBJECT_TYPE_VIEWPORT;
	}
	//else if( type.compare("Node Object")==0)
	//{
	//	processSceneNode(XMLNode);
	//}
	//else if( type.compare("Marker Object")==0)
	//{
	//	processSceneNode(XMLNode);
	//}
	else if( type.compare("Light Object")==0)
	{
		if(name.substr(0,GAME_OBJECT_TYPE_LIGHT.size()).compare(GAME_OBJECT_TYPE_LIGHT)==0)
		{
			return GAME_OBJECT_TYPE_LIGHT;
		}
	}
	else if( type.compare("Entity Object")==0)
	{
		if(name.substr(0,GAME_OBJECT_TYPE_ONY.size()).compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			return GAME_OBJECT_TYPE_ONY;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_TRIPOLLO.size()).compare(GAME_OBJECT_TYPE_TRIPOLLO)==0)
		{
			return GAME_OBJECT_TYPE_TRIPOLLO;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_TERRAIN.size()).compare(GAME_OBJECT_TYPE_TERRAIN)==0)
		{
			return GAME_OBJECT_TYPE_TERRAIN;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_PORTAL.size()).compare(GAME_OBJECT_TYPE_PORTAL)==0)
		{
			return GAME_OBJECT_TYPE_PORTAL;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_EYE.size()).compare(GAME_OBJECT_TYPE_EYE)==0)
		{
			return GAME_OBJECT_TYPE_EYE;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_ITEM_1UP.size()).compare(GAME_OBJECT_TYPE_ITEM_1UP)==0)
		{
			return GAME_OBJECT_TYPE_ITEM_1UP;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_ITEM_MAXHP.size()).compare(GAME_OBJECT_TYPE_ITEM_MAXHP)==0)
		{
			return GAME_OBJECT_TYPE_ITEM_MAXHP;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_VOLUMEBOX.size()).compare(GAME_OBJECT_TYPE_VOLUMEBOX)==0)
		{
			return GAME_OBJECT_TYPE_VOLUMEBOX;
		}
		else if(name.substr(0,GAME_OBJECT_TYPE_VOLUMECAPSULE.size()).compare(GAME_OBJECT_TYPE_VOLUMECAPSULE)==0)
		{
			return GAME_OBJECT_TYPE_VOLUMECAPSULE;
		}
	}
	else if( type.compare("Camera Object")==0)
	{
		return GAME_OBJECT_TYPE_CAMERA;
	}
	else if( type.compare("Particle Object")==0)
	{
		return GAME_OBJECT_TYPE_PARTICLESYSTEM;
	}
	else if( type.compare("BillboardSet Object")==0)
	{
		return GAME_OBJECT_TYPE_BILLBOARDSET;
	}
	else
	{
		//Ogre::LogManager::getSingleton().logMessage("Error reading "+type+" OBJECT");
		return type;
	}
	return type;
}

void LevelLoader::processObject(TiXmlElement *XMLNode)
{
	String gameObjectType=getGameObjectType(XMLNode);
	if( gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
	{
		processGameObjectScene(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		processGameObjectOny(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLO)==0)
	{
		processGameObjectTripollo(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_TERRAIN)==0)
	{
		processGameObjectTerrain(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_LIGHT)==0)
	{
		processGameObjectLight(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_PARTICLESYSTEM)==0)
	{
		processGameObjectParticleSystem(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_BILLBOARDSET)==0)
	{
		processGameObjectBillboardSet(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_EYE)==0)
	{
		processGameObjectEye(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_ITEM_1UP)==0)
	{
		processGameObjectItem1UP(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_ITEM_MAXHP)==0)
	{
		processGameObjectItemMaxHP(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_PORTAL)==0)
	{
		processGameObjectPortal(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_CAMERA)==0)
	{
		processGameObjectCamera(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_VOLUMEBOX)==0)
	{
		processGameObjectVolumeBox(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_VOLUMECAPSULE)==0)
	{
		processGameObjectVolumeCapsule(XMLNode);
	}
	else if( gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
	{
		processGameObjectViewport(XMLNode);
	}
	else
	{
		//Ogre::LogManager::getSingleton().logMessage("Error reading "+gameObjectType+" OBJECT");
	}
}

void LevelLoader::processGameObjectScene(TiXmlElement *XMLNode)
{
	////Get OctreeSceneManager name
	//tSceneManagerParameters.name = getAttrib(XMLNode, "name");

	////Get SceneManager properties
	//tSceneManagerParameters.TRenderComponentSceneParameters.ambient=

	//cre
	//pGameWorldManager->createSceneManager(tSceneManagerParameters);
}

void LevelLoader::processGameObjectOny(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectOnyParameters tGameObjectOnyParameters;
	
	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_ONY);

	//Get name
	tGameObjectOnyParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectOnyParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectOnyParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentCharacter
	tGameObjectOnyParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(XMLCustomProperties);
	
	//Create GameObject
	pGameWorldManager->createGameObjectOny(tGameObjectOnyParameters);


}

void LevelLoader::processGameObjectTripollo(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectTripolloParameters tGameObjectTripolloParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_TRIPOLLO);

	//Get name
	tGameObjectTripolloParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectTripolloParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectTripolloParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentCharacter
	tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters =  processPhysicsComponentCharacter(XMLCustomProperties);

	//Create GameObject
	pGameWorldManager->createGameObjectTripollo(tGameObjectTripolloParameters);
}

void LevelLoader::processGameObjectTerrain(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectTerrainParameters  tGameObjectTerrainParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_TERRAIN);

	//Get name
	tGameObjectTerrainParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectTerrainParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectTerrainParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentComplexConvex
	tGameObjectTerrainParameters.tPhysicsComponentComplexTriangleParameters = processPhysicsComponentComplexTriangle(XMLCustomProperties);
	//tGameObjectTerrainParameters.tPhysicsComponentComplexConvexParameters = processPhysicsComponentComplexConvex(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectTerrain(tGameObjectTerrainParameters);
}

void LevelLoader::processGameObjectCamera(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectCameraParameters  tGameObjectCameraParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_CAMERA);

	//Get name
	tGameObjectCameraParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentCamera
	tGameObjectCameraParameters.tRenderComponentCameraParameters=processRenderComponentCamera(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectCamera(tGameObjectCameraParameters);
}

void LevelLoader::processGameObjectLight(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectLightParameters  tGameObjectLightParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_LIGHT);

	//Get name
	tGameObjectLightParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentLight
	tGameObjectLightParameters.tRenderComponentLightParameters=processRenderComponentLight(XMLNode);

	//Get RenderComponentPositional
	tGameObjectLightParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectLight(tGameObjectLightParameters);
}

void LevelLoader::processGameObjectParticleSystem(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectParticleSystemParameters  tGameObjectParticleSystemParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_PARTICLESYSTEM);

	//Get name
	tGameObjectParticleSystemParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentParticleSystem
	tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters=processRenderComponentParticleSystem(XMLNode);

	//Get RenderComponentPositional
	tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectParticleSystem(tGameObjectParticleSystemParameters);
}
void LevelLoader::processGameObjectBillboardSet(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectBillboardSetParameters  tGameObjectBillboardSetParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_BILLBOARDSET);

	//Get name
	tGameObjectBillboardSetParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentBillboardSet
	tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters=processRenderComponentBillboardSet(XMLNode);

	//Get RenderComponentPositional
	tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectBillboardSet(tGameObjectBillboardSetParameters);
}

void LevelLoader::processGameObjectEye(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectEyeParameters tGameObjectEyeParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_EYE);

	//Get name
	tGameObjectEyeParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectEyeParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectEyeParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentCharacter
	tGameObjectEyeParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(XMLCustomProperties);
	
	//Create GameObject
	pGameWorldManager->createGameObjectEye(tGameObjectEyeParameters);
}

void LevelLoader::processGameObjectItem1UP(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectItem1UPParameters tGameObjectItem1UPParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_ITEM_1UP);

	//Get name
	tGameObjectItem1UPParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectItem1UPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectItem1UPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectItem1UP(tGameObjectItem1UPParameters);
}

void LevelLoader::processGameObjectItemMaxHP(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_ITEM_MAXHP);

	//Get name
	tGameObjectItemMaxHPParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectItemMaxHP(tGameObjectItemMaxHPParameters);
}

void LevelLoader::processGameObjectPortal(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectPortalParameters tGameObjectPortalParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_PORTAL);

	//Get name
	tGameObjectPortalParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectPortalParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectPortalParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectPortal(tGameObjectPortalParameters);
}

void LevelLoader::processGameObjectVolumeBox(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectVolumeBoxParameters tGameObjectVolumeBoxParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_VOLUMEBOX);

	//Get name
	tGameObjectVolumeBoxParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectVolumeBoxParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectVolumeBoxParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentVolumeBox
	tGameObjectVolumeBoxParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(XMLCustomProperties);

	//Create GameObject
	pGameWorldManager->createGameObjectVolumeBox(tGameObjectVolumeBoxParameters);
}

void LevelLoader::processGameObjectVolumeCapsule(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectVolumeCapsuleParameters tGameObjectVolumeCapsuleParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_VOLUMECAPSULE);

	//Get name
	tGameObjectVolumeCapsuleParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentEntity
	tGameObjectVolumeCapsuleParameters.tRenderComponentEntityParameters=processRenderComponentEntity(XMLNode);

	//Get RenderComponentPositional
	tGameObjectVolumeCapsuleParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(XMLNode);

	//Get PhysicsComponentVolumeCapsule
	tGameObjectVolumeCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters=processPhysicsComponentVolumeCapsule(XMLCustomProperties);

	//Create GameObject
	pGameWorldManager->createGameObjectVolumeCapsule(tGameObjectVolumeCapsuleParameters);
}

void LevelLoader::processGameObjectViewport(TiXmlElement *XMLNode)
{
	OUAN::TGameObjectViewportParameters tGameObjectViewportParameters;

	//Get Custom Properties
	TiXmlElement *XMLCustomProperties =parseCustomPropertiesFile(GAME_OBJECT_TYPE_VIEWPORT);

	//Get name
	tGameObjectViewportParameters.name = getAttrib(XMLNode, "name");

	//Get RenderComponentViewport
	tGameObjectViewportParameters.tRenderComponentViewportParameters=processRenderComponentViewport(XMLNode);

	//Create GameObject
	pGameWorldManager->createGameObjectViewport(tGameObjectViewportParameters);
}

//
//void LevelLoader::processResourceLocations(TiXmlElement *XMLNode)
//{
//	//TODO
//}

//void LevelLoader::processViewportCamera(TiXmlElement *XMLNode)
//{
//	TCameraParameters tCameraParameters;
//
//	tCameraParameters.name="Viewport#1";
//
//	//Get Camera properties
//	tCameraParameters.TRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
//	tCameraParameters.TRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"camera::position");
//	tCameraParameters.TRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
//	tCameraParameters.TRenderComponentCameraParameters.FOVy = getPropertyReal(XMLNode,"camera::fov");
//	tCameraParameters.TRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"camera::viewmode");
//
//		//PolygonMode conversion
//	int polygonmode = getPropertyInt(XMLNode,"camera::polymode");
//	switch(polygonmode)
//	{
//			case OGITOR_PM_POINTS:
//				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
//				break;
//			case OGITOR_PM_SOLID:
//				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
//				break;
//			case OGITOR_PM_WIREFRAME:
//				tCameraParameters.TRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
//				break;
//			default:
//				Ogre::LogManager::getSingleton().logMessage("Viewport Camera has unrecognised Camera Type");
//				break;
//	}
//
//
//	//Create Camera
////	pGameWorldManager->createCamera(tCameraParameters);
//}

TRenderComponentViewportParameters LevelLoader::processRenderComponentViewport(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentViewportParameters tRenderComponentViewportParameters;

	//Get Viewport properties
	tRenderComponentViewportParameters.colour = getPropertyColourValue(XMLNode,"colour");
	tRenderComponentViewportParameters.compositorcount = getPropertyInt(XMLNode,"compositorcount");
	tRenderComponentViewportParameters.index = getPropertyInt(XMLNode,"index");
	tRenderComponentViewportParameters.overlays = getPropertyBool(XMLNode,"overlays");
	tRenderComponentViewportParameters.shadows = getPropertyBool(XMLNode,"shadows");
	tRenderComponentViewportParameters.skies = getPropertyBool(XMLNode,"skies");

	return tRenderComponentViewportParameters;
	
}

TRenderComponentSceneParameters LevelLoader::processRenderComponentScene(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentSceneParameters tRenderComponentSceneParameters;

	tRenderComponentSceneParameters.ambient=getPropertyColourValue(XMLNode,"ambient");

	//Process SkyBox
	tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters=processRenderComponentSkyBox(XMLNode);

	//Process SkyDome
	tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters=processRenderComponentSkyDome(XMLNode);

	//TODO: Process Fog
	//processFog(XMLNode);

	//TODO: Process Shadows
	//processShadows(XMLNode);

	return tRenderComponentSceneParameters;
}

//void LevelLoader::processTerrain(TiXmlElement *XMLNode)
//{
//	//! @todo Implement this
//}


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
//	//	trajectory.init(mSceneManager);
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

TRenderComponentCameraParameters LevelLoader::processRenderComponentCamera(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentCameraParameters tRenderComponentCameraParameters;

	//Get Camera properties
	tRenderComponentCameraParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");
	tRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"position");
	tRenderComponentCameraParameters.autoaspectratio = getPropertyBool(XMLNode,"autoaspectratio");
	tRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"clipdistance");
	tRenderComponentCameraParameters.FOVy = getPropertyReal(XMLNode,"fov");
	tRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"viewmode");

		//PolygonModeConversion
	int polygonmode = getPropertyInt(XMLNode,"polygonmode");
	switch(polygonmode)
		{
			case OGITOR_PM_SOLID:
				tRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
				break;
			case OGITOR_PM_POINTS:
				tRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
				break;
			case OGITOR_PM_WIREFRAME:
				tRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Camera has unrecognised PolygonMode!");
				break;
		}

	return tRenderComponentCameraParameters;
}



TRenderComponentPositionalParameters LevelLoader::processRenderComponentPositional(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	//Get parent SceneNode name
	tRenderComponentPositionalParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tRenderComponentPositionalParameters.position = getPropertyVector3(XMLNode,"position");
	tRenderComponentPositionalParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tRenderComponentPositionalParameters.scale = getPropertyVector3(XMLNode,"scale");
	tRenderComponentPositionalParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");

	return tRenderComponentPositionalParameters;
}

TRenderComponentPositionalParameters LevelLoader::processRenderComponentPositionalNoScale(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	//Get parent SceneNode name
	tRenderComponentPositionalParameters.parentSceneNodeName = getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tRenderComponentPositionalParameters.position = getPropertyVector3(XMLNode,"position");
	tRenderComponentPositionalParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tRenderComponentPositionalParameters.scale = Vector3(1,1,1);
	tRenderComponentPositionalParameters.autotracktarget = "None";

	return tRenderComponentPositionalParameters;
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

void LevelLoader::processRenderComponentSubEntities(std::vector<TRenderComponentSubEntityParameters> &tRenderComponentSubEntityParameters,TiXmlElement *XMLNode)
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

TRenderComponentEntityParameters LevelLoader::processRenderComponentEntity(TiXmlElement *XMLNode)
{
	TRenderComponentEntityParameters tRenderComponentEntityParameters;

	//Process entity properties
	tRenderComponentEntityParameters.meshfile = getPropertyString(XMLNode, "meshfile");
	tRenderComponentEntityParameters.castshadows = getPropertyBool(XMLNode, "castshadows");

	//process Entity's SubEntites
	processRenderComponentSubEntities(tRenderComponentEntityParameters.tRenderComponentSubEntityParameters,XMLNode);
	
	return tRenderComponentEntityParameters;
}

TRenderComponentLightParameters LevelLoader::processRenderComponentLight(TiXmlElement *XMLNode)
{

	OUAN::TRenderComponentLightParameters tRenderComponentLightParameters;

	//Get Light properties
	
	tRenderComponentLightParameters.diffuse = getPropertyColourValue(XMLNode,"diffuse");
	tRenderComponentLightParameters.specular = getPropertyColourValue(XMLNode,"specular");
	tRenderComponentLightParameters.direction = getPropertyVector3(XMLNode,"direction");
	tRenderComponentLightParameters.castshadows = getPropertyBool(XMLNode,"castshadows");
	tRenderComponentLightParameters.lightrange = getPropertyVector3(XMLNode,"lightrange");
	tRenderComponentLightParameters.attenuation = getPropertyVector4(XMLNode,"attenuation");
	tRenderComponentLightParameters.power = getPropertyReal(XMLNode,"power");

		//Lightype conversion
	int lighttype = getPropertyInt(XMLNode,"lighttype");
	switch(lighttype)
	{
			case OGITOR_LT_POINT:
				tRenderComponentLightParameters.lighttype=Ogre::Light::LT_POINT;
				break;
			case OGITOR_LT_DIRECTIONAL:
				tRenderComponentLightParameters.lighttype=Ogre::Light::LT_DIRECTIONAL;
				break;
			case OGITOR_LT_SPOTLIGHT:
				tRenderComponentLightParameters.lighttype=Ogre::Light::LT_SPOTLIGHT;
				break;
			default:
				Ogre::LogManager::getSingleton().logMessage("Light has unrecognised light type!");
				break;
	}

	return tRenderComponentLightParameters;

}

TRenderComponentParticleSystemParameters LevelLoader::processRenderComponentParticleSystem(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	//Process ParticleSystem properties
	tRenderComponentParticleSystemParameters.particle = getPropertyString(XMLNode, "particle");
	tRenderComponentParticleSystemParameters.castshadows = getPropertyBool(XMLNode, "castshadows");
	
	return tRenderComponentParticleSystemParameters;
}
TRenderComponentBillboardSetParameters LevelLoader::processRenderComponentBillboardSet(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters;

	//Process BillboardSet properties
	tRenderComponentBillboardSetParameters.material = getPropertyString(XMLNode, "material");
	tRenderComponentBillboardSetParameters.defaultheight = getPropertyReal(XMLNode, "defaultheight");
	tRenderComponentBillboardSetParameters.defaultwidth = getPropertyReal(XMLNode, "defaultwidth");
	tRenderComponentBillboardSetParameters.pointrendering = getPropertyBool(XMLNode, "pointrendering");
	tRenderComponentBillboardSetParameters.renderdistance = getPropertyReal(XMLNode, "renderdistance");
	tRenderComponentBillboardSetParameters.sorting = getPropertyBool(XMLNode, "sorting");

		//BillboardType Conversion
	int billboardtype = getPropertyInt(XMLNode, "billboardtype");
	switch(billboardtype)
	{
		case OGITOR_BBT_ORIENTED_COMMON:
			tRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_ORIENTED_COMMON;
			break;
		case OGITOR_BBT_ORIENTED_SELF:
			tRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_ORIENTED_SELF;
			break;
		case OGITOR_BBT_PERPENDICULAR_COMMON:
			tRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_PERPENDICULAR_COMMON;
			break;
		case OGITOR_BBT_PERPENDICULAR_SELF:
			tRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_PERPENDICULAR_SELF;
			break;
		case OGITOR_BBT_POINT:
			tRenderComponentBillboardSetParameters.billboardtype=Ogre::BBT_POINT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard has unrecognised BillboardType!");
			break;
	}
		//BillboardOrigin Conversion
	int billboardorigin = getPropertyInt(XMLNode, "billboardorigin");
	switch(billboardorigin)
	{
		case OGITOR_BBO_BOTTOM_CENTER:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_CENTER;
			break;
		case OGITOR_BBO_BOTTOM_LEFT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_LEFT;
			break;
		case OGITOR_BBO_BOTTOM_RIGHT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_BOTTOM_RIGHT;
			break;
		case OGITOR_BBO_CENTER:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER;
			break;
		case OGITOR_BBO_CENTER_LEFT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER_LEFT;
			break;
		case OGITOR_BBO_CENTER_RIGHT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_CENTER_RIGHT;
			break;
		case OGITOR_BBO_TOP_CENTER:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_CENTER;
			break;
		case OGITOR_BBO_TOP_LEFT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_LEFT;
			break;
		case OGITOR_BBO_TOP_RIGHT:
			tRenderComponentBillboardSetParameters.billboardorigin=Ogre::BBO_TOP_RIGHT;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard has unrecognised BillboardOrigin!");
			break;
	}

	//Billboard Rotation Conversion
	int billboardrotation = getPropertyInt(XMLNode, "billboardrotation");
	switch(billboardrotation)
	{
		case OGITOR_BBR_TEXCOORD:
			tRenderComponentBillboardSetParameters.billboardrotation=Ogre::BBR_TEXCOORD;
			break;
		case OGITOR_BBR_VERTEX:
			tRenderComponentBillboardSetParameters.billboardrotation=Ogre::BBR_VERTEX;
			break;
		default:
			Ogre::LogManager::getSingleton().logMessage("Billboard has unrecognised BillboardRotationType!");
			break;
	}

	//process BillboardSet's Billboards
	processRenderComponentBillboards(tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters,XMLNode);

	return tRenderComponentBillboardSetParameters;
}

void LevelLoader::processRenderComponentBillboards(std::vector<TRenderComponentBillboardParameters>  &tRenderComponentBillboardParameters ,TiXmlElement *XMLNode)
{
	int i;
	OUAN::TRenderComponentBillboardParameters currentTRenderComponentBillboardParameters;

	//get the number of BillboardSet's Billboards
	int billboardcount=getPropertyInt(XMLNode,"billboardcount");

	//process and load all BillboardSet's Billboards
	for(i=0;i<billboardcount;i++)
	{
		//Process Billboards
		currentTRenderComponentBillboardParameters.colour=getPropertyColourValue(XMLNode,"billboard"+StringConverter::toString(i)+"::colour");
		currentTRenderComponentBillboardParameters.dimensions=getPropertyVector2(XMLNode,"billboard"+StringConverter::toString(i)+"::dimensions");
		currentTRenderComponentBillboardParameters.position=getPropertyVector3(XMLNode,"billboard"+StringConverter::toString(i)+"::position");
		currentTRenderComponentBillboardParameters.rotation=getPropertyReal(XMLNode,"billboard"+StringConverter::toString(i)+"::rotation");
		currentTRenderComponentBillboardParameters.texcoordindex=getPropertyInt(XMLNode,"billboard"+StringConverter::toString(i)+"::texcoordindex");
		currentTRenderComponentBillboardParameters.texrect=getPropertyVector4(XMLNode,"billboard"+StringConverter::toString(i)+"::texrect");

		tRenderComponentBillboardParameters.push_back(currentTRenderComponentBillboardParameters);
	}
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

TRenderComponentSkyBoxParameters LevelLoader::processRenderComponentSkyBox(TiXmlElement *XMLNode)
{
	TRenderComponentSkyBoxParameters TRenderComponentSkyBoxParameters;
	// Process SkyBox properties
	TRenderComponentSkyBoxParameters.active = getPropertyBool(XMLNode, "skybox::active");
	TRenderComponentSkyBoxParameters.material = getPropertyString(XMLNode, "skybox::material");
	TRenderComponentSkyBoxParameters.distance = getPropertyReal(XMLNode, "skybox::distance");

	return TRenderComponentSkyBoxParameters;
}

TRenderComponentSkyDomeParameters LevelLoader::processRenderComponentSkyDome(TiXmlElement *XMLNode)
{
	TRenderComponentSkyDomeParameters TRenderComponentSkyDomeParameters;
	// Process SkyDome properties
	TRenderComponentSkyDomeParameters.active = getPropertyBool(XMLNode, "skydome::active");
	TRenderComponentSkyDomeParameters.material = getPropertyString(XMLNode, "skydome::material");
	
	return TRenderComponentSkyDomeParameters;
}

TPhysicsComponentCharacterParameters LevelLoader::processPhysicsComponentCharacter(TiXmlElement *XMLNode)
{
	TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;

	//Get Component properties
	tPhysicsComponentCharacterParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentCharacter::mass");
	tPhysicsComponentCharacterParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentCharacter::radius");
	tPhysicsComponentCharacterParameters.height= getPropertyReal(XMLNode, "PhysicsComponentCharacter::height");

	return tPhysicsComponentCharacterParameters;

}

TPhysicsComponentComplexConvexParameters LevelLoader::processPhysicsComponentComplexConvex(TiXmlElement *XMLNode)
{
	TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;

	//Get Component properties
	tPhysicsComponentComplexConvexParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplexConvex::mass");
	tPhysicsComponentComplexConvexParameters.nxsFile = getPropertyString(XMLNode, "PhysicsComponentComplexConvex::nxsFile");

	return tPhysicsComponentComplexConvexParameters;
}

TPhysicsComponentComplexTriangleParameters LevelLoader::processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode)
{
	TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;

	//Get Component properties
	tPhysicsComponentComplexTriangleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplexTriangle::mass");
	tPhysicsComponentComplexTriangleParameters.nxsFile = getPropertyString(XMLNode, "PhysicsComponentComplexTriangle::nxsFile");

	return tPhysicsComponentComplexTriangleParameters;
}

TPhysicsComponentSimpleBoxParameters LevelLoader::processPhysicsComponentSimpleBox(TiXmlElement *XMLNode)
{
	TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

	//Get Component properties
	tPhysicsComponentSimpleBoxParameters.mass=getPropertyReal(XMLNode, "PhysicsComponentSimpleBox::mass");
	Vector3 length=getPropertyVector3(XMLNode, "PhysicsComponentSimpleBox::length");
	tPhysicsComponentSimpleBoxParameters.lengthX=length.x;
	tPhysicsComponentSimpleBoxParameters.lengthY=length.y;
	tPhysicsComponentSimpleBoxParameters.lengthZ=length.z;

	return tPhysicsComponentSimpleBoxParameters;

}

TPhysicsComponentSimpleCapsuleParameters LevelLoader::processPhysicsComponentSimpleCapsule(TiXmlElement *XMLNode)
{
	TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters;
	//Get Component properties
	tPhysicsComponentSimpleCapsuleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule::mass");
	tPhysicsComponentSimpleCapsuleParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule::radius");
	tPhysicsComponentSimpleCapsuleParameters.height= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule::height");

	return tPhysicsComponentSimpleCapsuleParameters;
}

TPhysicsComponentVolumeBoxParameters LevelLoader::processPhysicsComponentVolumeBox(TiXmlElement *XMLNode)
{
	TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

	//Get Component properties
	tPhysicsComponentVolumeBoxParameters.mass=getPropertyReal(XMLNode, "PhysicsComponentVolumeBox::mass");
	Vector3 length=getPropertyVector3(XMLNode, "PhysicsComponentVolumeBox::scale");
	tPhysicsComponentVolumeBoxParameters.lengthX=length.x;
	tPhysicsComponentVolumeBoxParameters.lengthY=length.y;
	tPhysicsComponentVolumeBoxParameters.lengthZ=length.z;

	return tPhysicsComponentVolumeBoxParameters;

}

TPhysicsComponentVolumeCapsuleParameters LevelLoader::processPhysicsComponentVolumeCapsule(TiXmlElement *XMLNode)
{
	TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;

	//Get Component properties
	tPhysicsComponentVolumeCapsuleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentVolumeCapsule::mass");
	tPhysicsComponentVolumeCapsuleParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentVolumeCapsule::radius");
	tPhysicsComponentVolumeCapsuleParameters.height= getPropertyReal(XMLNode, "PhysicsComponentVolumeCapsule::height");

	return tPhysicsComponentVolumeCapsuleParameters;
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

		//Ogre::LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

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
	if(XMLNodeCustomProperties)
	{
		pElement = XMLNodeCustomProperties->FirstChildElement("PROPERTY");
		while(pElement)
		{
			propertyName = getAttrib(pElement, "id");

			//Ogre::LogManager::getSingleton().logMessage("[LevelLoader] parsing "+propertyName+" property!");

			if(propertyName.compare(attrib_name)==0)
			{
				// Get the attribute value
				result = getAttrib(pElement, "value");
				found=true;
			}
			pElement = pElement->NextSiblingElement("PROPERTY");
		}
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


TiXmlElement * LevelLoader::parseCustomPropertiesFile(std::string gameObjectType)
{
	std::ifstream customPropertiesFile;
	std::string customPropertiesFilePath;
	;

	customPropertiesFilePath=GAME_OBJECT_PARAMETERS_PATH+gameObjectType+".ctp";

	//Open Ony Custom properties file

	// Open the .ctp File
	//customPropertiesFile.open(customPropertiesFilePath.c_str());

	XMLCustomPropertiesDocument = new TiXmlDocument(customPropertiesFilePath.c_str());

	if (!XMLCustomPropertiesDocument->LoadFile()){
		Ogre::LogManager::getSingleton().logMessage("Error reading "+customPropertiesFilePath);
	} 

	//XMLCustomProperties = XMLCustomPropertiesDocument->RootElement();

	TiXmlHandle docHandle(XMLCustomPropertiesDocument);
	TiXmlElement *XMLCustomProperties = docHandle.FirstChildElement().Element();
	if(!XMLCustomProperties)
	{
		Ogre::LogManager::getSingleton().logMessage("Error reading "+customPropertiesFilePath+"FirstElement");
	}


	return XMLCustomProperties;
}