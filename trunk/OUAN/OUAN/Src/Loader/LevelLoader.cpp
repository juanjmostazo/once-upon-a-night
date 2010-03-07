#include "LevelLoader.h"
#include "XMLGameObjectParser.h"
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
	this->mGameWorldManager=app->getGameWorldManager();

	this->mXMLGameObjectParser.init();
}

void LevelLoader::loadLevel(String level)
{
	Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading level "+level);

	//TODO: CLEAR OLD LEVEL FROM GAME WORLD MANAGER
	mXMLGameObjectParser.clearLevel();

	//Parse Level's GameObjects
	mXMLGameObjectParser.parseLevel(level);

	//Process Level's GameObjects
	processGameObjects();

	//We do not need this information anymore so we clear it.
	mXMLGameObjectParser.clearLevel();

	Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading level "+level+" Done!");
}

void LevelLoader::processGameObjects()
{
	XMLGameObjectContainerIterator it;

	for(it = mXMLGameObjectParser.XMLGameObjectContainer.begin(); it !=mXMLGameObjectParser.XMLGameObjectContainer.end(); it++)
	{
		processGameObject(&it->second);
	}

}

void LevelLoader::processGameObject(XMLGameObject* gameObject)
{
	String gameObjectType;

	try
	{
		gameObjectType=gameObject->gameObjectType;

		if( gameObjectType.compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			processGameObjectOny(gameObject);
		}
		//else if( gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
		//{
		//	processGameObjectScene(gameObject);
		//}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLO)==0)
		{
			processGameObjectTripollo(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TERRAIN)==0)
		{
			processGameObjectTerrain(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_LIGHT)==0)
		{
			processGameObjectLight(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_PARTICLESYSTEM)==0)
		{
			processGameObjectParticleSystem(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BILLBOARDSET)==0)
		{
			processGameObjectBillboardSet(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_EYE)==0)
		{
			processGameObjectEye(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_ITEM_1UP)==0)
		{
			processGameObjectItem1UP(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_ITEM_MAXHP)==0)
		{
			processGameObjectItemMaxHP(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_PORTAL)==0)
		{
			processGameObjectPortal(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CAMERA)==0)
		{
			processGameObjectCamera(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_VOLUMEBOX)==0)
		{
			processGameObjectVolumeBox(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_VOLUMECAPSULE)==0)
		{
			processGameObjectVolumeCapsule(gameObject);
		}
		//else if( gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
		//{
		//	processGameObjectViewport(gameObject);
		//}
		else
		{
			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error processing Game Object with type "+gameObjectType+" , the specified type does not exist");
		}
	}
	catch( std::string error )
	{
		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error processing Game Object "+gameObject->name+": "+error);
	}

}


void LevelLoader::processGameObjectScene(XMLGameObject* gameObject)
{
	////Get OctreeSceneManager name
	//tSceneManagerParameters.name = getAttrib(XMLNode, "name");

	////Get SceneManager properties
	//tSceneManagerParameters.TRenderComponentSceneParameters.ambient=

	//cre
	//mGameWorldManager->createSceneManager(tSceneManagerParameters);
}

void LevelLoader::processGameObjectOny(XMLGameObject* gameObject)
{
	OUAN::TGameObjectOnyParameters tGameObjectOnyParameters;

	try
	{
		//Get name
		tGameObjectOnyParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectOnyParameters.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectOnyParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		tGameObjectOnyParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectOny(tGameObjectOnyParameters);

}

void LevelLoader::processGameObjectTripollo(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTripolloParameters tGameObjectTripolloParameters;

	try
	{
		//Get name
		tGameObjectTripolloParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTripolloParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTripolloParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectTripolloParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams);
		tGameObjectTripolloParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares);

		//Get RenderComponentPositional
		tGameObjectTripolloParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTripollo(tGameObjectTripolloParameters);
}

void LevelLoader::processGameObjectTerrain(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTerrainParameters  tGameObjectTerrainParameters;

	try
	{
		//Get name
		tGameObjectTerrainParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectTerrainParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectTerrainParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentComplexConvex
		tGameObjectTerrainParameters.tPhysicsComponentComplexTriangleParameters = processPhysicsComponentComplexTriangle(gameObject->XMLNodeCustomProperties,
			tGameObjectTerrainParameters.tRenderComponentEntityParameters.meshfile);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTerrain(tGameObjectTerrainParameters);
}

void LevelLoader::processGameObjectCamera(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCameraParameters  tGameObjectCameraParameters;

	try
	{
		//Get name
		tGameObjectCameraParameters.name = gameObject->name;

		//Get RenderComponentCamera
		tGameObjectCameraParameters.tRenderComponentCameraParameters=processRenderComponentCamera(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectCamera(tGameObjectCameraParameters);
}

void LevelLoader::processGameObjectLight(XMLGameObject* gameObject)
{
	OUAN::TGameObjectLightParameters  tGameObjectLightParameters;

	try
	{
		//Get name
		tGameObjectLightParameters.name = gameObject->name;

		//Get RenderComponentLight
		tGameObjectLightParameters.tRenderComponentLightParameters=processRenderComponentLight(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectLightParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectLight(tGameObjectLightParameters);
}

void LevelLoader::processGameObjectParticleSystem(XMLGameObject* gameObject)
{
	OUAN::TGameObjectParticleSystemParameters  tGameObjectParticleSystemParameters;

	try
	{
		//Get name
		tGameObjectParticleSystemParameters.name = gameObject->name;

		//Get RenderComponentParticleSystem
		tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters=processRenderComponentParticleSystem(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectParticleSystem(tGameObjectParticleSystemParameters);
}
void LevelLoader::processGameObjectBillboardSet(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBillboardSetParameters  tGameObjectBillboardSetParameters;

	try
	{
		//Get name
		tGameObjectBillboardSetParameters.name = gameObject->name;

		//Get RenderComponentBillboardSet
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters=processRenderComponentBillboardSet(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectBillboardSet(tGameObjectBillboardSetParameters);
}

void LevelLoader::processGameObjectEye(XMLGameObject* gameObject)
{
	OUAN::TGameObjectEyeParameters tGameObjectEyeParameters;

	try
	{
		//Get name
		tGameObjectEyeParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectEyeParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectEyeParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		tGameObjectEyeParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectEye(tGameObjectEyeParameters);
}

void LevelLoader::processGameObjectItem1UP(XMLGameObject* gameObject)
{
	OUAN::TGameObjectItem1UPParameters tGameObjectItem1UPParameters;

	try
	{
		//Get name
		tGameObjectItem1UPParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectItem1UPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectItem1UPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectItem1UP(tGameObjectItem1UPParameters);
}

void LevelLoader::processGameObjectItemMaxHP(XMLGameObject* gameObject)
{
	OUAN::TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters;
	try
	{
		//Get name
		tGameObjectItemMaxHPParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectItemMaxHP(tGameObjectItemMaxHPParameters);
}

void LevelLoader::processGameObjectPortal(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPortalParameters tGameObjectPortalParameters;
	try
	{
		//Get name
		tGameObjectPortalParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectPortalParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectPortalParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectPortal(tGameObjectPortalParameters);
}

void LevelLoader::processGameObjectVolumeBox(XMLGameObject* gameObject)
{
	OUAN::TGameObjectVolumeBoxParameters tGameObjectVolumeBoxParameters;
	try
	{
		//Get name
		tGameObjectVolumeBoxParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectVolumeBoxParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectVolumeBoxParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentVolumeBox
		tGameObjectVolumeBoxParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties,gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectVolumeBox(tGameObjectVolumeBoxParameters);
}

void LevelLoader::processGameObjectVolumeCapsule(XMLGameObject* gameObject)
{
	OUAN::TGameObjectVolumeCapsuleParameters tGameObjectVolumeCapsuleParameters;
	try
	{
		//Get name
		tGameObjectVolumeCapsuleParameters.name = gameObject->name;

		//Get RenderComponentEntity
		tGameObjectVolumeCapsuleParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams);

		//Get RenderComponentPositional
		tGameObjectVolumeCapsuleParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentVolumeCapsule
		tGameObjectVolumeCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters=processPhysicsComponentVolumeCapsule(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectVolumeCapsule(tGameObjectVolumeCapsuleParameters);
}

void LevelLoader::processGameObjectViewport(XMLGameObject* gameObject)
{
	OUAN::TGameObjectViewportParameters tGameObjectViewportParameters;
	try
	{
		//Get name
		tGameObjectViewportParameters.name = gameObject->name;

		//Get RenderComponentViewport
		tGameObjectViewportParameters.tRenderComponentViewportParameters=processRenderComponentViewport(gameObject->XMLNodeDreams);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectViewport(tGameObjectViewportParameters);
}

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
	tRenderComponentPositionalParameters.parentSceneNodeName = "SceneManager";

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

void LevelLoader::processRenderComponentSubEntities(std::vector<TRenderComponentSubEntityParameters> &tRenderComponentSubEntityParameters,TiXmlElement *XMLNode)
{
		int i;

		TRenderComponentSubEntityParameters currentRenderComponentSubEntityParameters;
 
		//process and load all Entity's SubEntites
		i=0;
		while(true)
		{
			//Process SubEntity
			currentRenderComponentSubEntityParameters.material=getPropertyString(XMLNode,"subentity"+StringConverter::toString(i)+"::material",false);
			currentRenderComponentSubEntityParameters.visible=getPropertyBool(XMLNode,"subentity"+StringConverter::toString(i)+"::visible",false);

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

TPhysicsComponentComplexConvexParameters LevelLoader::processPhysicsComponentComplexConvex(TiXmlElement *XMLNode,std::string meshfile)
{
	TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;

	//Get Component properties
	tPhysicsComponentComplexConvexParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplexConvex::mass");
	tPhysicsComponentComplexConvexParameters.nxsFile = "nxs:CONVEX_"+meshfile.substr(0,meshfile.size()-5)+".nxs";

	return tPhysicsComponentComplexConvexParameters;
}

TPhysicsComponentComplexTriangleParameters LevelLoader::processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode,std::string meshfile)
{
	TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;

	//Get Component properties
	tPhysicsComponentComplexTriangleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplexTriangle::mass");
	tPhysicsComponentComplexTriangleParameters.nxsFile = "nxs:TRIANGLE_"+meshfile.substr(0,meshfile.size()-5)+".nxs";

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

TPhysicsComponentVolumeBoxParameters LevelLoader::processPhysicsComponentVolumeBox(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode)
{
	TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

	//Get Component properties
	tPhysicsComponentVolumeBoxParameters.mass=getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeBox::mass");
	Vector3 length=getPropertyVector3(XMLRenderInfoNode, "scale");
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

String LevelLoader::getPropertyString(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	TiXmlElement *pElement;
	TiXmlElement *XMLNodeCustomProperties;
	String propertyName;
	String result="";
	bool found=false;

	if(!XMLNode)
	{
		throw std::string("Invalid XML Node");
	}
	else
	{

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
			if(logErrors)
			{
				throw std::string("Error parsing "+attrib_name+" attribute!");
			}
		}
	}
	return result;
}

Vector2 LevelLoader::getPropertyVector2(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	return StringConverter::parseVector2(getPropertyString(XMLNode,attrib_name,logErrors));
}

Vector3 LevelLoader::getPropertyVector3(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	return StringConverter::parseVector3(getPropertyString(XMLNode,attrib_name,logErrors));
}

Vector4 LevelLoader::getPropertyVector4(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	return StringConverter::parseVector4(getPropertyString(XMLNode,attrib_name,logErrors));
}

Quaternion LevelLoader::getPropertyQuaternion(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	return StringConverter::parseQuaternion(getPropertyString(XMLNode,attrib_name,logErrors));
}

ColourValue LevelLoader::getPropertyColourValue(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	return StringConverter::parseColourValue(getPropertyString(XMLNode,attrib_name,logErrors));
}

bool LevelLoader::getPropertyBool(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	 return StringConverter::parseBool(getPropertyString(XMLNode,attrib_name,logErrors));
}

int LevelLoader::getPropertyInt(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	 return StringConverter::parseInt(getPropertyString(XMLNode,attrib_name,logErrors));
}

Real LevelLoader::getPropertyReal(TiXmlElement *XMLNode, const String &attrib_name, bool logErrors)
{
	 return StringConverter::parseReal(getPropertyString(XMLNode,attrib_name,logErrors));
}