#include "LevelLoader.h"
#include "XMLParser.h"
#include "XMLTrajectory.h"
#include "XMLWalkabilityMap.h"
#include "XMLGameObject.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
#include "../Graphics/TrajectoryManager/TrajectoryNode.h"
#include "../Graphics/TrajectoryManager/WalkabilityMap.h"
#include "../Component/Component.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectBee_Butterfly.h"
#include "../Game/GameObject/GameObjectBillboardSet.h"
#include "../Game/GameObject/GameObjectBush.h"
#include "../Game/GameObject/GameObjectCamera.h"
#include "../Game/GameObject/GameObjectCarnivorousPlant.h"
#include "../Game/GameObject/GameObjectClockPiece.h"
#include "../Game/GameObject/GameObjectCryKing.h"
#include "../Game/GameObject/GameObjectDiamond.h"
#include "../Game/GameObject/GameObjectDiamondTree.h"
#include "../Game/GameObject/GameObjectDoor.h"
#include "../Game/GameObject/GameObjectDragon.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectFlashLight.h"
#include "../Game/GameObject/GameObjectHeart.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectLight.h"
#include "../Game/GameObject/GameObjectMagicClock.h"
#include "../Game/GameObject/GameObjectNightGoblin.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectParticleSystem.h"
#include "../Game/GameObject/GameObjectPillow.h"
#include "../Game/GameObject/GameObjectPlataform.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectProvisionalEntity.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectScene.h"
#include "../Game/GameObject/GameObjectScepter.h"
#include "../Game/GameObject/GameObjectSnakeCreeper.h"
#include "../Game/GameObject/GameObjectStoryBook.h"
#include "../Game/GameObject/GameObjectTenteTieso.h"
#include "../Game/GameObject/GameObjectTerrainTriangle.h"
#include "../Game/GameObject/GameObjectTerrainConvex.h"
#include "../Game/GameObject/GameObjectTree.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectTripollito.h"
#include "../Game/GameObject/GameObjectTripolloDreams.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentInitial.h"
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
#include "../Utils/Utils.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../Logic/LogicComponent/LogicComponent.h"
#include "../Logic/LogicComponent/LogicComponentOny.h"
#include "../Logic/LogicComponent/LogicComponentItem.h"
#include "../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../Logic/LogicComponent/LogicComponentUsable.h"

using namespace OUAN;

LevelLoader::LevelLoader()
{
	DEFAULT_TRAJECTORY_SPEED = 20;
}
LevelLoader::~LevelLoader(){}

void LevelLoader::init(OUAN::ApplicationPtr app)
{
	this->mGameWorldManager=app->getGameWorldManager();
	this->mXMLParser.init();
}

void LevelLoader::loadLevel(String level)
{
	Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading level "+level);

	//clear parser content
	mXMLParser.clearLevelInfo();

	//Parse Level's GameObjects
	mXMLParser.parseLevel(level);

	//Process Level's GameObjects
	processGameObjects();

	//Process Level's Trajectories
	processTrajectories();

	//Process Level's Walkability Maps
	processWalkabilityMaps();

	//clear information, as we do not need it anymore
	mXMLParser.clearLevelInfo();

	Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading level "+level+" Done!");
}

void LevelLoader::processGameObjects()
{
	XMLGameObjectContainerIterator it;

	for(it = mXMLParser.mXMLGameObjectContainer.begin(); it !=mXMLParser.mXMLGameObjectContainer.end(); it++)
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

		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading GameObject "+gameObject->name);

		if( gameObjectType.compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			processGameObjectOny(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SCENE)==0)
		{
			processGameObjectScene(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_VIEWPORT)==0)
		{
			processGameObjectViewport(gameObject);
			//Process Viewport Camera
			processGameObjectViewportCamera(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLO)==0)
		{
			processGameObjectTripolloDreams(gameObject);
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
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIGGERBOX)==0)
		{
			processGameObjectTriggerBox(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIGGERCAPSULE)==0)
		{
			processGameObjectTriggerCapsule(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_NIGHTGOBLIN)==0)
		{
			processGameObjectNightGoblin(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CRYKING)==0)
		{
			processGameObjectCryKing(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_DRAGON)==0)
		{
			processGameObjectDragon(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_MAGICCLOCK)==0)
		{
			processGameObjectMagicClock(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_PILLOW)==0)
		{
			processGameObjectPillow(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0)
		{
			processGameObjectFlashLight(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TENTETIESO)==0)
		{
			processGameObjectTentetieso(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BEE_BUTTERFLY)==0)
		{
			processGameObjectBee_Butterfly(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0)
		{
			processGameObjectDiamondTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_STORYBOOK)==0)
		{
			processGameObjectStoryBook(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_HEART)==0)
		{
			processGameObjectHeart(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_DIAMOND)==0)
		{
			processGameObjectProvisionalEntity(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SCAREDPLANT)==0)
		{
			processGameObjectScaredPlant(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CLOCKPIECE)==0)
		{
			processGameObjectClockPiece(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLITO)==0)
		{
			processGameObjectTripollito(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SNAKECREEPER)==0)
		{
			processGameObjectSnakeCreeper(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CARNIVOROUSPLANT)==0)
		{
			processGameObjectProvisionalEntity(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SCEPTER)==0)
		{
			processGameObjectScepter(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE1)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE2)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE3)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE4)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE5)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE6)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE7)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE8)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE9)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE10)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE11)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TREE12)==0)
		{
			processGameObjectTree(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_DOOR)==0)
		{
			processGameObjectDoor(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_PLATAFORM)==0)
		{
			processGameObjectPlataform(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BUSH)==0)
		{
			processGameObjectBush(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BUSH1)==0)
		{
			processGameObjectBush(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BUSH2)==0)
		{
			processGameObjectBush(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BUSH3)==0)
		{
			processGameObjectBush(gameObject);
		}
		else
		{
			processGameObjectProvisionalEntity(gameObject);
			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error processing Game Object with type "+gameObjectType+" , the specified type does not exist");
		}
	}
	catch( std::string error )
	{
		Ogre::LogManager::getSingleton().logMessage("ERROR! [LevelLoader] Error processing Game Object "+gameObject->name+": "+error);
	}

}

void LevelLoader::processTrajectories()
{
	XMLTrajectoryContainerIterator it;

	try
	{
		for(it = mXMLParser.mXMLTrajectoryContainer.begin(); it !=mXMLParser.mXMLTrajectoryContainer.end(); it++)
		{
			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading Trajectory "+it->first);

			processTrajectory(&it->second);

		}
	}
	catch( std::string error )
	{
		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error processing Trajectory "+it->first+": "+error);
	}

}
TTrajectoryNodeParameters LevelLoader::processTrajectoryNode(TiXmlElement *XMLNode)
{
	TTrajectoryNodeParameters tTrajectoryNodeParameters;

	//Get Trajectory node name
	tTrajectoryNodeParameters.nodeName=getAttrib(XMLNode, "name");

	//Get Trajectory Node properties
	tTrajectoryNodeParameters.position=getPropertyVector3(XMLNode,"position");
	tTrajectoryNodeParameters.orientation=getPropertyQuaternion(XMLNode,"orientation");

	//Ogitor Markers have an offset of 90 degrees for Y axis rotation
	tTrajectoryNodeParameters.orientation=tTrajectoryNodeParameters.orientation*Ogre::Quaternion(Ogre::Math::Sqrt(0.5),0,Ogre::Math::Sqrt(0.5),0);

	try
	{
		tTrajectoryNodeParameters.speed=getPropertyReal(XMLNode,"trajectorynode::speed");
		if(tTrajectoryNodeParameters.speed<0)
		{
			throw "time to next node must be positive";
		}
	}
	catch( std::string error )
	{
		tTrajectoryNodeParameters.speed=DEFAULT_TRAJECTORY_SPEED;
	}

	return tTrajectoryNodeParameters;
}

void LevelLoader::processTrajectory(XMLTrajectory *pXMLTrajectory)
{
	OUAN::TTrajectoryParameters tTrajectoryParameters;
	unsigned int i;

	//Get Trajectory name
	tTrajectoryParameters.name=pXMLTrajectory->name;

	//Process Trajectory nodes
	for(i=0;i<pXMLTrajectory->trajectoryNodes.size();i++)
	{
		//Process Trajectory Node
		tTrajectoryParameters.tTrajectoryNodeParameters.push_back(processTrajectoryNode(pXMLTrajectory->trajectoryNodes[i]));
	}

	//Create Trajectory 
	mGameWorldManager->createTrajectory(tTrajectoryParameters);
}

void LevelLoader::processWalkabilityMaps()
{
	XMLWalkabilityMapContainerIterator it;

	try
	{
		for(it = mXMLParser.mXMLWalkabilityMapContainer.begin(); it !=mXMLParser.mXMLWalkabilityMapContainer.end(); it++)
		{
			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Loading Walkability Map "+it->first);

			processWalkabilityMap(&it->second);

		}
	}
	catch( std::string error )
	{
		Ogre::LogManager::getSingleton().logMessage("[LevelLoader] Error processing Walkability Map "+it->first+": "+error);
	}
}

void LevelLoader::processWalkabilityMap(XMLWalkabilityMap * walkabilityMap)
{
	unsigned int i;

	TWalkabilityMapParameters tWalkabilityMapParameters;

	//Get Walkability Map name
	tWalkabilityMapParameters.name=walkabilityMap->name;

	//Get Walkability Map nodes
	for(i=0;i<walkabilityMap->walkabilityMapNodes.size();i++)
	{
		tWalkabilityMapParameters.walkabilityNodes.push_back(
			processWalkabilityMapNode(walkabilityMap->walkabilityMapNodes[i]));
	}

	//Create Walkability Map
	mGameWorldManager->createWalkabilityMap(tWalkabilityMapParameters);
}

TWalkabilityMapNodeParameters LevelLoader::processWalkabilityMapNode(TiXmlElement *XMLNode)
{
	int i;
	String currentNeighborName;

	TWalkabilityMapNodeParameters tWalkabilityMapNodeParameters;

	//Get Walkability Map node name
	tWalkabilityMapNodeParameters.nodeName=getAttrib(XMLNode, "name");

	//Get Walkability Map node properties
	tWalkabilityMapNodeParameters.position=getPropertyVector3(XMLNode,"position");
	tWalkabilityMapNodeParameters.orientation=getPropertyQuaternion(XMLNode,"orientation");

	//process and load all WalkabilityMapNode's Neightbors
	i=1;
	while(true)
	{
		//Process Neightbor
		currentNeighborName=getPropertyString(XMLNode,"walkability::node#"+StringConverter::toString(i),false);


		//Ogre::LogManager::getSingleton().logMessage("[LevelLoader] currentNeighborName" +currentNeighborName);

		//there is no more neighbors
		if(currentNeighborName.compare("")==0) break;

		//Add neighbor
		tWalkabilityMapNodeParameters.neighbors.push_back(currentNeighborName);

		i++;
	}

	return tWalkabilityMapNodeParameters;
}

void LevelLoader::processGameObjectBee_Butterfly(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBee_ButterflyParameters tGameObjectBee_ButterflyParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBee_ButterflyParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBee_ButterflyParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBee_ButterflyParameters.name = gameObject->name;
	
		//Get Logic component
		tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectBee_ButterflyParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		if(tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectBee_ButterflyParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
			//Get PhysicsComponentCharacterDreams
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterDreamsParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties,"Dreams");
		}

		if(tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectBee_ButterflyParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,NIGHTMARES,gameObject->XMLNodeCustomProperties);
			//Get PhysicsComponentCharacterNightmares
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterNightmaresParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties,"Nightmares");
		}
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectBee_Butterfly(tGameObjectBee_ButterflyParameters);
}

void LevelLoader::processGameObjectBillboardSet(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBillboardSetParameters  tGameObjectBillboardSetParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBillboardSetParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBillboardSetParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBillboardSetParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectBillboardSetParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentBillboardSet
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters=processRenderComponentBillboardSet(gameObject->getMainXMLNode());

		//Get RenderComponentPositional
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectBillboardSet(tGameObjectBillboardSetParameters);
}

void LevelLoader::processGameObjectBush(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBushParameters tGameObjectBushParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBushParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBushParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBushParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectBushParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectBushParameters.tLogicComponentParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectBushParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS, gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectBushParameters.tLogicComponentParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectBushParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectBushParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectBush(tGameObjectBushParameters);
}

void LevelLoader::processGameObjectCamera(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCameraParameters  tGameObjectCameraParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectCameraParameters.name = gameObject->name;

		//Get RenderComponentCamera
		tGameObjectCameraParameters.tRenderComponentCameraParameters=processRenderComponentCamera(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectCamera(tGameObjectCameraParameters);
}

void LevelLoader::processGameObjectCarnivorousPlant(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectCarnivorousPlantParameters.dreamsName = gameObject->dreamsName;
		tGameObjectCarnivorousPlantParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectCarnivorousPlantParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectCarnivorousPlantParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectCarnivorousPlantParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectCarnivorousPlantParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectCarnivorousPlantParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectCarnivorousPlantParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares, NIGHTMARES, gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectCarnivorousPlantParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectCarnivorousPlantParameters.tPhysicsComponentCharacterParameters=processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters);
}

void LevelLoader::processGameObjectClockPiece(XMLGameObject* gameObject)
{
	OUAN::TGameObjectClockPieceParameters tGameObjectClockPieceParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectClockPieceParameters.dreamsName = gameObject->dreamsName;
		tGameObjectClockPieceParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectClockPieceParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectClockPieceParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectClockPieceParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(), 
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectClockPieceParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectClockPieceParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectClockPiece(tGameObjectClockPieceParameters);
}

void LevelLoader::processGameObjectCryKing(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCryKingParameters tGameObjectCryKingParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectCryKingParameters.dreamsName = gameObject->dreamsName;
		tGameObjectCryKingParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectCryKingParameters.name = gameObject->name;

		//Get logic component
		tGameObjectCryKingParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectCryKingParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectCryKingParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectCryKingParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectCryKingParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectCryKing(tGameObjectCryKingParameters);
}

void LevelLoader::processGameObjectDiamond(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDiamondParameters tGameObjectDiamondParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectDiamondParameters.dreamsName = gameObject->dreamsName;
		tGameObjectDiamondParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectDiamondParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectDiamondParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectDiamondParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectDiamondParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectDiamondParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectDiamond(tGameObjectDiamondParameters);
}

void LevelLoader::processGameObjectDiamondTree(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectDiamondTreeParameters.dreamsName = gameObject->dreamsName;
		tGameObjectDiamondTreeParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectDiamondTreeParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectDiamondTreeParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectDiamondTreeParameters.tLogicComponentParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectDiamondTreeParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectDiamondTreeParameters.tLogicComponentParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectDiamondTreeParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectDiamondTreeParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectDiamondTreeParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectDiamondTree(tGameObjectDiamondTreeParameters);
}

void LevelLoader::processGameObjectDoor(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDoorParameters tGameObjectDoorParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectDoorParameters.dreamsName = gameObject->dreamsName;
		tGameObjectDoorParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectDoorParameters.name = gameObject->name;

		//Get logic component
		tGameObjectDoorParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectDoorParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectDoorParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectDoorParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectDoorParameters.tPhysicsComponentSimpleBoxParameters = processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectDoor(tGameObjectDoorParameters);
}

void LevelLoader::processGameObjectDragon(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDragonParameters tGameObjectDragonParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectDragonParameters.dreamsName = gameObject->dreamsName;
		tGameObjectDragonParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectDragonParameters.name = gameObject->name;

		//Get logic component
		tGameObjectDragonParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectDragonParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS,gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectDragonParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectDragonParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectDragonParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectDragon(tGameObjectDragonParameters);
}

void LevelLoader::processGameObjectEye(XMLGameObject* gameObject)
{
	OUAN::TGameObjectEyeParameters tGameObjectEyeParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;
		if(gameObject->XMLNodeDreams) throw DREAMS_SHOULD_NOT_EXIST;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;

		//Get names
		tGameObjectEyeParameters.dreamsName = "None";
		tGameObjectEyeParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectEyeParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectEyeParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectEyeParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectEyeParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeNightmares);

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

void LevelLoader::processGameObjectFlashLight(XMLGameObject* gameObject)
{
	OUAN::TGameObjectFlashLightParameters tGameObjectFlashLightParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectFlashLightParameters.dreamsName = gameObject->dreamsName;
		tGameObjectFlashLightParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectFlashLightParameters.name = gameObject->name;

		//Get logic component
		tGameObjectFlashLightParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectFlashLightParameters.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->getMainXMLNode(),
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectFlashLightParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeConvex
		tGameObjectFlashLightParameters.tPhysicsComponentVolumeConvexParameters = processPhysicsComponentVolumeConvex(gameObject->XMLNodeCustomProperties);

		tGameObjectFlashLightParameters.attackComponentParameters=processAttackComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectFlashLight(tGameObjectFlashLightParameters);
}

void LevelLoader::processGameObjectHeart(XMLGameObject* gameObject)
{
	OUAN::TGameObjectHeartParameters tGameObjectHeartParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectHeartParameters.dreamsName = gameObject->dreamsName;
		tGameObjectHeartParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectHeartParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectHeartParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectHeartParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectHeartParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectHeartParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectHeart(tGameObjectHeartParameters);
}

void LevelLoader::processGameObjectItem1UP(XMLGameObject* gameObject)
{
	OUAN::TGameObjectItem1UPParameters tGameObjectItem1UPParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectItem1UPParameters.dreamsName = gameObject->dreamsName;
		tGameObjectItem1UPParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectItem1UPParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectItem1UPParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectItem1UPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectItem1UPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectItem1UPParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);

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
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectItemMaxHPParameters.dreamsName = gameObject->dreamsName;
		tGameObjectItemMaxHPParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectItemMaxHPParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectItemMaxHPParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectItemMaxHPParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectItemMaxHP(tGameObjectItemMaxHPParameters);
}

void LevelLoader::processGameObjectLight(XMLGameObject* gameObject)
{
	OUAN::TGameObjectLightParameters  tGameObjectLightParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectLightParameters.dreamsName = gameObject->dreamsName;
		tGameObjectLightParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectLightParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectLightParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentLight
		tGameObjectLightParameters.tRenderComponentLightParameters=processRenderComponentLight(gameObject->getMainXMLNode());

		//Get RenderComponentPositional
		tGameObjectLightParameters.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectLight(tGameObjectLightParameters);
}

void LevelLoader::processGameObjectMagicClock(XMLGameObject* gameObject)
{
	OUAN::TGameObjectMagicClockParameters tGameObjectMagicClockParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectMagicClockParameters.dreamsName = gameObject->dreamsName;
		tGameObjectMagicClockParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectMagicClockParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectMagicClockParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectMagicClock(tGameObjectMagicClockParameters);
}

void LevelLoader::processGameObjectNightGoblin(XMLGameObject* gameObject)
{
	OUAN::TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectNightGoblinParameters.dreamsName = gameObject->dreamsName;
		tGameObjectNightGoblinParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectNightGoblinParameters.name = gameObject->name;

		//Get logic component
		tGameObjectNightGoblinParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectNightGoblinParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS,gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectNightGoblinParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectNightGoblinParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectNightGoblinParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectNightGoblin(tGameObjectNightGoblinParameters);
}

void LevelLoader::processGameObjectOny(XMLGameObject* gameObject)
{
	OUAN::TGameObjectOnyParameters tGameObjectOnyParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectOnyParameters.dreamsName = gameObject->dreamsName;
		tGameObjectOnyParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectOnyParameters.name = gameObject->name;

		//Get logic component
		tGameObjectOnyParameters.tLogicComponentOnyParameters=processLogicComponentOny(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Process weapon component
		tGameObjectOnyParameters.tWeaponComponentParameters=processWeaponComponent(gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectOnyParameters.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectOnyParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

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

void LevelLoader::processGameObjectParticleSystem(XMLGameObject* gameObject)
{
	OUAN::TGameObjectParticleSystemParameters  tGameObjectParticleSystemParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectParticleSystemParameters.dreamsName = gameObject->dreamsName;
		tGameObjectParticleSystemParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectParticleSystemParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectParticleSystemParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentParticleSystem
		tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters=processRenderComponentParticleSystem(gameObject->getMainXMLNode());

		//Get RenderComponentPositional
		tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectParticleSystem(tGameObjectParticleSystemParameters);
}

void LevelLoader::processGameObjectPillow(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPillowParameters tGameObjectPillowParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectPillowParameters.dreamsName = gameObject->dreamsName;
		tGameObjectPillowParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectPillowParameters.name = gameObject->name;

		//Get logic component
		tGameObjectPillowParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectPillowParameters.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->getMainXMLNode(),
			DREAMS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectPillowParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleCapsule
		tGameObjectPillowParameters.tPhysicsComponentSimpleCapsuleParameters = processPhysicsComponentSimpleCapsule(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectPillow(tGameObjectPillowParameters);
}

void LevelLoader::processGameObjectPlataform(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPlataformParameters tGameObjectPlataformParameters;
	std::string meshfile;

	try
	{

		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		if(gameObject->XMLNodeDreams)
		{
			meshfile = getPropertyString(gameObject->XMLNodeDreams, "meshfile");			
		}
		else if(gameObject->XMLNodeNightmares)
		{
			meshfile = getPropertyString(gameObject->XMLNodeNightmares, "meshfile");
		}

		std::string complexConvex="CONVEX_"+meshfile.substr(0,meshfile.size()-5)+".nxs";

		//Get names
		tGameObjectPlataformParameters.dreamsName = gameObject->dreamsName;
		tGameObjectPlataformParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectPlataformParameters.name = gameObject->name;

		//Get PhysicsComponentComplexConvex
		tGameObjectPlataformParameters.tPhysicsComponentComplexConvexParameters = processPhysicsComponentComplexConvex(gameObject->XMLNodeCustomProperties,
			complexConvex);

		tGameObjectPlataformParameters.tLogicComponentParameters= processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		tGameObjectPlataformParameters.tRenderComponentPositionalParameters= processRenderComponentPositional(gameObject->getMainXMLNode());
		
		if(tGameObjectPlataformParameters.tLogicComponentParameters.existsInDreams)
		{
			tGameObjectPlataformParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}
		
		if(tGameObjectPlataformParameters.tLogicComponentParameters.existsInNightmares)
		{
			tGameObjectPlataformParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectPlataform(tGameObjectPlataformParameters);
}

void LevelLoader::processGameObjectPortal(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPortalParameters tGameObjectPortalParameters;
	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectPortalParameters.dreamsName = gameObject->dreamsName;
		tGameObjectPortalParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectPortalParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectPortalParameters.tLogicComponentParameters=processLogicComponentUsable(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectPortalParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectPortalParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectPortalParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
		
		//Get PhysicsComponentSimpleBox
		tGameObjectPortalParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectPortal(tGameObjectPortalParameters);
}

void LevelLoader::processGameObjectProvisionalEntity(XMLGameObject* gameObject)
{
	OUAN::TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters;

	try
	{
		//Get names
		tGameObjectProvisionalEntityParameters.dreamsName = gameObject->dreamsName;
		tGameObjectProvisionalEntityParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectProvisionalEntityParameters.name = gameObject->name;

		//Get Logic Component
		tGameObjectProvisionalEntityParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectProvisionalEntityParameters.tLogicComponentParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectProvisionalEntityParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS, gameObject->XMLNodeCustomProperties);
		}

		if(tGameObjectProvisionalEntityParameters.tLogicComponentParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectProvisionalEntityParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares, NIGHTMARES, gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectProvisionalEntityParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//TODO: EXTRACT PHYSICS PARAMETERS FROM FILE
		tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters.mass=0;
		tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters.lengthX=6;
		tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters.lengthY=20;
		tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters.lengthZ=6;
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters);
}

void LevelLoader::processGameObjectScaredPlant(XMLGameObject* gameObject)
{
	OUAN::TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(gameObject->XMLNodeNightmares) throw NIGHTMARES_SHOULD_NOT_EXIST;

		//Get names
		tGameObjectScaredPlantParameters.dreamsName = gameObject->dreamsName;
		tGameObjectScaredPlantParameters.nightmaresName = "None";
		tGameObjectScaredPlantParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectScaredPlantParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectScaredPlantParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectScaredPlantParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		tGameObjectScaredPlantParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectScaredPlant(tGameObjectScaredPlantParameters);
}

void LevelLoader::processGameObjectScene(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSceneParameters tGameObjectSceneParameters;

	try
	{
		//Check errors
		if(!gameObject->getMainXMLNode()) throw SCENE_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw SCENE_NODE_NOT_FOUND;

		//Get Scene name
		tGameObjectSceneParameters.name = gameObject->name;

		//Get SceneManager properties
		tGameObjectSceneParameters.tRenderComponentSceneParameters = processRenderComponentScene(gameObject->getMainXMLNode(),gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectScene(tGameObjectSceneParameters);
}

void LevelLoader::processGameObjectScepter(XMLGameObject* gameObject)
{
	OUAN::TGameObjectScepterParameters tGameObjectScepterParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectScepterParameters.dreamsName = gameObject->dreamsName;
		tGameObjectScepterParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectScepterParameters.name = gameObject->name;

		//Get logic component
		tGameObjectScepterParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectScepterParameters.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectScepterParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleCapsule
		tGameObjectScepterParameters.tPhysicsComponentSimpleCapsuleParameters = processPhysicsComponentSimpleCapsule(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectScepter(tGameObjectScepterParameters);
}

void LevelLoader::processGameObjectSnakeCreeper(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectSnakeCreeperParameters.dreamsName = gameObject->dreamsName;
		tGameObjectSnakeCreeperParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectSnakeCreeperParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectSnakeCreeperParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectSnakeCreeperParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectSnakeCreeperParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS, gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectSnakeCreeperParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectSnakeCreeperParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties );
		}

		//Get RenderComponentPositional
		tGameObjectSnakeCreeperParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectSnakeCreeperParameters.tPhysicsComponentCharacterParameters=processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters);
}

void LevelLoader::processGameObjectStoryBook(XMLGameObject* gameObject)
{
	OUAN::TGameObjectStoryBookParameters tGameObjectStoryBookParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectStoryBookParameters.dreamsName = gameObject->dreamsName;
		tGameObjectStoryBookParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectStoryBookParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectStoryBookParameters.tLogicComponentItemParameters=processLogicComponentItem(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectStoryBookParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectStoryBookParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectStoryBookParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectStoryBook(tGameObjectStoryBookParameters);
}

void LevelLoader::processGameObjectTentetieso(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTentetiesoParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTentetiesoParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTentetiesoParameters.name = gameObject->name;

		//Get logic component
		tGameObjectTentetiesoParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectTentetiesoParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectTentetiesoParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectTentetiesoParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectTentetiesoParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTentetieso(tGameObjectTentetiesoParameters);
}

void LevelLoader::processGameObjectTerrain(XMLGameObject* gameObject)
{
	std::string meshfile;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		if(gameObject->XMLNodeDreams)
		{
			meshfile = getPropertyString(gameObject->XMLNodeDreams, "meshfile");			
		}
		else if(gameObject->XMLNodeNightmares)
		{
			meshfile = getPropertyString(gameObject->XMLNodeNightmares, "meshfile");
		}

		std::string complexConvex="CONVEX_"+meshfile.substr(0,meshfile.size()-5)+".nxs";
		std::string complexTriangle="TRIANGLE_"+meshfile.substr(0,meshfile.size()-5)+".nxs";

		if(Ogre::ResourceGroupManager::getSingleton().resourceExists(DEFAULT_OGRE_RESOURCE_MANAGER_GROUP,complexConvex))
		{

			OUAN::TGameObjectTerrainConvexParameters  tGameObjectTerrainConvexParameters;
			try
			{
				//Get names
				tGameObjectTerrainConvexParameters.dreamsName = gameObject->dreamsName;
				tGameObjectTerrainConvexParameters.nightmaresName = gameObject->nightmaresName;
				tGameObjectTerrainConvexParameters.name = gameObject->name;

				//Get PhysicsComponentComplexConvex
				tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters = processPhysicsComponentComplexConvex(gameObject->XMLNodeCustomProperties,
					complexConvex);

				tGameObjectTerrainConvexParameters.tLogicComponentParameters= processLogicComponent(gameObject->XMLNodeDreams,
					gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

				tGameObjectTerrainConvexParameters.tRenderComponentPositionalParameters= processRenderComponentPositional(gameObject->getMainXMLNode());
				
				if(tGameObjectTerrainConvexParameters.tLogicComponentParameters.existsInDreams)
				{
					tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(
						gameObject->XMLNodeDreams, DREAMS, gameObject->XMLNodeCustomProperties);
				}
				
				if(tGameObjectTerrainConvexParameters.tLogicComponentParameters.existsInNightmares)
				{
					tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(
						gameObject->XMLNodeNightmares,NIGHTMARES, gameObject->XMLNodeCustomProperties);
				}
			}
			catch( std::string error )
			{
				throw error;
				return;
			}

			//Create GameObject
			mGameWorldManager->createGameObjectTerrainConvex(tGameObjectTerrainConvexParameters);

			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] "+gameObject->name+" uses .nxs complex physics file "+complexConvex);

		}
		else if(Ogre::ResourceGroupManager::getSingleton().resourceExists(DEFAULT_OGRE_RESOURCE_MANAGER_GROUP,complexTriangle))
		{
			OUAN::TGameObjectTerrainTriangleParameters  tGameObjectTerrainTriangleParameters;
			try
			{
				//Check parsing errors
				if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
				if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;

				//Get names
				tGameObjectTerrainTriangleParameters.dreamsName = gameObject->dreamsName;
				tGameObjectTerrainTriangleParameters.nightmaresName = gameObject->nightmaresName;
				tGameObjectTerrainTriangleParameters.name = gameObject->name;

				//Get PhysicsComponentComplexTriangle
				tGameObjectTerrainTriangleParameters.tPhysicsComponentComplexTriangleParameters = processPhysicsComponentComplexTriangle(gameObject->XMLNodeCustomProperties,
					complexTriangle);

				tGameObjectTerrainTriangleParameters.tLogicComponentParameters= processLogicComponent(gameObject->XMLNodeDreams,
					gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

				tGameObjectTerrainTriangleParameters.tRenderComponentPositionalParameters= processRenderComponentPositional(gameObject->getMainXMLNode());
				
				tGameObjectTerrainTriangleParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
					DREAMS, gameObject->XMLNodeCustomProperties);

				tGameObjectTerrainTriangleParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares, NIGHTMARES, gameObject->XMLNodeCustomProperties);
			}
			catch( std::string error )
			{
				throw error;
				return;
			}

			//Create GameObject
			mGameWorldManager->createGameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters);

			Ogre::LogManager::getSingleton().logMessage("[LevelLoader] "+gameObject->name+" uses .nxs complex physics file "+complexTriangle);
		}
		else
		{
			processGameObjectProvisionalEntity(gameObject);
			throw "Error reading .nxs complex physics file for mesh "+meshfile;
		}
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
}

void LevelLoader::processGameObjectTree(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTreeParameters tGameObjectTreeParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTreeParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTreeParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTreeParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTreeParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectTreeParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectTreeParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectTreeParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTree(tGameObjectTreeParameters);
}

void LevelLoader::processGameObjectTriggerBox(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters;
	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTriggerBoxParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTriggerBoxParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTriggerBoxParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTriggerBoxParameters.tLogicComponentParameters=processLogicComponentTrigger(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectTriggerBoxParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectTriggerBoxParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectTriggerBoxParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBoxUsingScale(gameObject->XMLNodeCustomProperties,gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectTriggerBox(tGameObjectTriggerBoxParameters);
}

void LevelLoader::processGameObjectTriggerCapsule(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters;
	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTriggerCapsuleParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTriggerCapsuleParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTriggerCapsuleParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTriggerCapsuleParameters.tLogicComponentParameters=processLogicComponentTrigger(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectTriggerCapsuleParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectTriggerCapsuleParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeCapsule
		tGameObjectTriggerCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters=processPhysicsComponentVolumeCapsuleUsingScale(gameObject->XMLNodeCustomProperties,gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters);
}

void LevelLoader::processGameObjectTripollito(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTripollitoParameters tGameObjectTripollitoParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTripollitoParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTripollitoParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTripollitoParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTripollitoParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectTripollitoParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectTripollitoParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectTripollitoParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectTripollitoParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectTripollitoParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectTripollitoParameters.tPhysicsComponentCharacterParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTripollito(tGameObjectTripollitoParameters);
}

void LevelLoader::processGameObjectTripolloDreams(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters;

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTripolloDreamsParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTripolloDreamsParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTripolloDreamsParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTripolloDreamsParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectTripolloDreamsParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectTripolloDreamsParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,						DREAMS, gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectTripolloDreamsParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectTripolloDreamsParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares, NIGHTMARES, gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectTripolloDreamsParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectTripolloDreamsParameters.tPhysicsComponentCharacterParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

		tGameObjectTripolloDreamsParameters.tAttackComponentParameters = processAttackComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectTripolloDreams(tGameObjectTripolloDreamsParameters);
}


void LevelLoader::processGameObjectViewport(XMLGameObject* gameObject)
{
	OUAN::TGameObjectViewportParameters tGameObjectViewportParameters;
	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw VIEWPORT_NODE_NOT_FOUND;

		//Get name
		tGameObjectViewportParameters.name = gameObject->name;

		//Get RenderComponentViewport
		tGameObjectViewportParameters.tRenderComponentViewportParameters=processRenderComponentViewport(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	mGameWorldManager->createGameObjectViewport(tGameObjectViewportParameters);
}

void LevelLoader::processGameObjectViewportCamera(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCameraParameters  tGameObjectCameraParameters;

	try
	{
		//Get names
		tGameObjectCameraParameters.name = "Camera#Viewport";

		//Get RenderComponentCamera
		tGameObjectCameraParameters.tRenderComponentCameraParameters=processRenderComponentCameraViewport(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->createGameObjectCamera(tGameObjectCameraParameters);
}

TRenderComponentSceneParameters LevelLoader::processRenderComponentScene(TiXmlElement *XMLOgitorNode,TiXmlElement *XMLCustomPropertiesNode)
{
	OUAN::TRenderComponentSceneParameters tRenderComponentSceneParameters;

	tRenderComponentSceneParameters.ambient=getPropertyColourValue(XMLOgitorNode,"ambient");

	//Process SkyBox
	tRenderComponentSceneParameters.tRenderComponentSkyBoxParameters=processRenderComponentSkyBox(XMLCustomPropertiesNode);

	//Process SkyDome
	tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters=processRenderComponentSkyDome(XMLCustomPropertiesNode);

	//TODO: Process Fog
	//processFog(XMLNode);

	//TODO: Process Shadows
	//processShadows(XMLNode);

	return tRenderComponentSceneParameters;
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

TRenderComponentCameraParameters LevelLoader::processRenderComponentCamera(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentCameraParameters tRenderComponentCameraParameters;

	//Get Camera properties
	tRenderComponentCameraParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");
	tRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"position");
	tRenderComponentCameraParameters.autoaspectratio = false;//getPropertyBool(XMLNode,"autoaspectratio");
	tRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"clipdistance");
	tRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"viewmode");

	//set FOVy
	//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
	Real FOVy = getPropertyReal(XMLNode,"fov");
	FOVy=FOVy*55.0f;
	if(FOVy>180.0) FOVy=179.99;
	else if(FOVy<=0) FOVy=0.01;
	tRenderComponentCameraParameters.FOVy=FOVy;

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
TRenderComponentCameraParameters LevelLoader::processRenderComponentCameraViewport(TiXmlElement *XMLNode)
{

	OUAN::TRenderComponentCameraParameters tRenderComponentCameraParameters;

	//Get Camera properties
	tRenderComponentCameraParameters.autotracktarget = "None";
	tRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
	tRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"camera::position");
	tRenderComponentCameraParameters.autoaspectratio = false;
	tRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
	tRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"camera::viewmode");

	//set FOVy
	//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
	Real FOVy = getPropertyReal(XMLNode,"camera::fov");
	FOVy=FOVy*55.0f;
	if(FOVy>180.0) FOVy=179.99;
	else if(FOVy<=0) FOVy=0.01;
	tRenderComponentCameraParameters.FOVy=FOVy;

		//PolygonModeConversion
	int polygonmode = getPropertyInt(XMLNode,"camera::polymode");
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
	tRenderComponentPositionalParameters.parentSceneNodeName = "SceneManager";//getAttrib(XMLNode, "parentnode");

	//Get SceneNode parameters
	tRenderComponentPositionalParameters.position = getPropertyVector3(XMLNode,"position");
	tRenderComponentPositionalParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
	tRenderComponentPositionalParameters.scale = Vector3(1,1,1);
	tRenderComponentPositionalParameters.autotracktarget = "None";

	return tRenderComponentPositionalParameters;
}
void LevelLoader::processRenderComponentEntityAnimParams(std::vector<TRenderComponentEntityAnimParams>& renderComponentEntityAnimParams,
														 TiXmlElement* XMLNode, int world)
{
	if (XMLNode)
	{
		TRenderComponentEntityAnimParams currentAnimParams;

		int i=0;
		std::string worldSuffix=(world==DREAMS)
			?"d"
			:(world==NIGHTMARES)
				?"n"
				:"";
		while(true)
		{
			currentAnimParams.name=getPropertyString(XMLNode,"animation"+StringConverter::toString(i)+worldSuffix+"::name",
				false);
			currentAnimParams.loop=getPropertyBool(XMLNode,"animation"+StringConverter::toString(i)+worldSuffix+"::loop",
				false);
			if (currentAnimParams.name.compare("")==0) break;

			renderComponentEntityAnimParams.push_back(currentAnimParams);
			++i;
		}
	}
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

TRenderComponentEntityParameters LevelLoader::processRenderComponentEntity(TiXmlElement *XMLNode, int world, TiXmlElement* XMLCustomPropertiesNode)
{

	TRenderComponentEntityParameters tRenderComponentEntityParameters;

	//Process entity properties
	tRenderComponentEntityParameters.meshfile = getPropertyString(XMLNode, "meshfile");
	tRenderComponentEntityParameters.castshadows = getPropertyBool(XMLNode, "castshadows");

	//process Entity's SubEntites
	processRenderComponentSubEntities(tRenderComponentEntityParameters.tRenderComponentSubEntityParameters,XMLNode);

	//Process Animation states
	tRenderComponentEntityParameters.tRenderComponentEntityAnimParams.clear();
	processRenderComponentEntityAnimParams(tRenderComponentEntityParameters.tRenderComponentEntityAnimParams,XMLCustomPropertiesNode,world);
	
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

TRenderComponentSkyBoxParameters LevelLoader::processRenderComponentSkyBox(TiXmlElement *XMLCustomPropertiesNode)
{
	TRenderComponentSkyBoxParameters TRenderComponentSkyBoxParameters;
	// Process SkyBox properties
	TRenderComponentSkyBoxParameters.active = getPropertyBool(XMLCustomPropertiesNode, "RenderComponentSkyBox::active");
	TRenderComponentSkyBoxParameters.distance = getPropertyReal(XMLCustomPropertiesNode, "RenderComponentSkyBox::distance");
	// Process SkyBox materials
	TRenderComponentSkyBoxParameters.materialDreams = getPropertyString(XMLCustomPropertiesNode, "RenderComponentSkyBox::materialDreams");
	TRenderComponentSkyBoxParameters.materialNightmares = getPropertyString(XMLCustomPropertiesNode, "RenderComponentSkyBox::materialNightmares");


	return TRenderComponentSkyBoxParameters;
}

TRenderComponentSkyDomeParameters LevelLoader::processRenderComponentSkyDome(TiXmlElement *XMLCustomPropertiesNode)
{
	TRenderComponentSkyDomeParameters TRenderComponentSkyDomeParameters;
	// Process SkyDome properties
	TRenderComponentSkyDomeParameters.active = getPropertyBool(XMLCustomPropertiesNode, "RenderComponentSkyDome::active");
	TRenderComponentSkyDomeParameters.curvature = getPropertyReal(XMLCustomPropertiesNode, "RenderComponentSkyDome::curvature");
	TRenderComponentSkyDomeParameters.tiling = getPropertyReal(XMLCustomPropertiesNode, "RenderComponentSkyDome::tiling");
	TRenderComponentSkyDomeParameters.distance = getPropertyReal(XMLCustomPropertiesNode, "RenderComponentSkyDome::distance");
	// Process SkyDome materials
	TRenderComponentSkyDomeParameters.materialDreams = getPropertyString(XMLCustomPropertiesNode, "RenderComponentSkyDome::materialDreams");
	TRenderComponentSkyDomeParameters.materialNightmares = getPropertyString(XMLCustomPropertiesNode, "RenderComponentSkyDome::materialNightmares");

	return TRenderComponentSkyDomeParameters;
}

TPhysicsComponentCharacterParameters LevelLoader::processPhysicsComponentCharacter(TiXmlElement *XMLNode,std::string suffix)
{
	TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;

	//Get Component properties
	tPhysicsComponentCharacterParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::mass");
	tPhysicsComponentCharacterParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::radius");
	tPhysicsComponentCharacterParameters.height= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::height");

	return tPhysicsComponentCharacterParameters;

}

TPhysicsComponentComplexConvexParameters LevelLoader::processPhysicsComponentComplexConvex(TiXmlElement *XMLNode,std::string nxsFile,std::string suffix)
{
	TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;
	
	//Get Component properties
	tPhysicsComponentComplexConvexParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplex"+suffix+"::mass");

	//Set nxs file
	tPhysicsComponentComplexConvexParameters.nxsFile="nxs:"+nxsFile;

	return tPhysicsComponentComplexConvexParameters;
}

TPhysicsComponentComplexTriangleParameters LevelLoader::processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode,std::string nxsFile,std::string suffix)
{
	TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;
	
	//Get Component properties
	tPhysicsComponentComplexTriangleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentComplex"+suffix+"::mass");

	//Set nxs file
	tPhysicsComponentComplexTriangleParameters.nxsFile="nxs:"+nxsFile;

	return tPhysicsComponentComplexTriangleParameters;
}

TPhysicsComponentSimpleBoxParameters LevelLoader::processPhysicsComponentSimpleBox(TiXmlElement *XMLNode,std::string suffix)
{
	TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters;

	//Get Component properties
	tPhysicsComponentSimpleBoxParameters.mass=getPropertyReal(XMLNode, "PhysicsComponentSimpleBox"+suffix+"::mass");
	Vector3 length=getPropertyVector3(XMLNode, "PhysicsComponentSimpleBox"+suffix+"::length");
	tPhysicsComponentSimpleBoxParameters.lengthX=length.x;
	tPhysicsComponentSimpleBoxParameters.lengthY=length.y;
	tPhysicsComponentSimpleBoxParameters.lengthZ=length.z;

	return tPhysicsComponentSimpleBoxParameters;

}

TPhysicsComponentSimpleCapsuleParameters LevelLoader::processPhysicsComponentSimpleCapsule(TiXmlElement *XMLNode,std::string suffix)
{
	TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters;

	//Get Component properties
	tPhysicsComponentSimpleCapsuleParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule"+suffix+"::mass");
	tPhysicsComponentSimpleCapsuleParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule"+suffix+"::radius");
	tPhysicsComponentSimpleCapsuleParameters.height= getPropertyReal(XMLNode, "PhysicsComponentSimpleCapsule"+suffix+"::height");

	return tPhysicsComponentSimpleCapsuleParameters;
}

TPhysicsComponentVolumeBoxParameters LevelLoader::processPhysicsComponentVolumeBox(TiXmlElement *XMLCustomPropertiesNode,std::string suffix)
{
	TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

	//Get Component properties
	tPhysicsComponentVolumeBoxParameters.mass=getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeBox"+suffix+"::mass");
	Vector3 length=getPropertyVector3(XMLCustomPropertiesNode, "PhysicsComponentVolumeBox"+suffix+"::length");
	tPhysicsComponentVolumeBoxParameters.lengthX=length.x;
	tPhysicsComponentVolumeBoxParameters.lengthY=length.y;
	tPhysicsComponentVolumeBoxParameters.lengthZ=length.z;

	return tPhysicsComponentVolumeBoxParameters;
}

TPhysicsComponentVolumeCapsuleParameters LevelLoader::processPhysicsComponentVolumeCapsule(TiXmlElement *XMLCustomPropertiesNode,std::string suffix)
{
	TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;

	//Get Component properties
	tPhysicsComponentVolumeCapsuleParameters.mass= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeCapsule"+suffix+"::mass");
	tPhysicsComponentVolumeCapsuleParameters.radius= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeCapsule"+suffix+"::radius");
	tPhysicsComponentVolumeCapsuleParameters.height= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeCapsule"+suffix+"::height");

	return tPhysicsComponentVolumeCapsuleParameters;
}

TPhysicsComponentVolumeBoxParameters LevelLoader::processPhysicsComponentVolumeBoxUsingScale(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode,std::string suffix)
{
	TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters;

	//Get Component properties
	tPhysicsComponentVolumeBoxParameters.mass=getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeBox"+suffix+"::mass");
	Vector3 length=getPropertyVector3(XMLRenderInfoNode, "scale");
	tPhysicsComponentVolumeBoxParameters.lengthX=length.x;
	tPhysicsComponentVolumeBoxParameters.lengthY=length.y;
	tPhysicsComponentVolumeBoxParameters.lengthZ=length.z;

	return tPhysicsComponentVolumeBoxParameters;
}

TPhysicsComponentVolumeCapsuleParameters LevelLoader::processPhysicsComponentVolumeCapsuleUsingScale(TiXmlElement *XMLCustomPropertiesNode,TiXmlElement *XMLRenderInfoNode,std::string suffix)
{
	TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters;

	//Get Component properties
	tPhysicsComponentVolumeCapsuleParameters.mass= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeCapsule"+suffix+"::mass");
	Vector3 length=getPropertyVector3(XMLRenderInfoNode, "scale");
	tPhysicsComponentVolumeCapsuleParameters.radius= length.x;
	tPhysicsComponentVolumeCapsuleParameters.height= length.y;

	return tPhysicsComponentVolumeCapsuleParameters;
}

TPhysicsComponentVolumeConvexParameters LevelLoader::processPhysicsComponentVolumeConvex(TiXmlElement *XMLCustomPropertiesNode,std::string suffix)
{
	TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters;

	//Get Component properties
	tPhysicsComponentVolumeConvexParameters.mass= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeConvex"+suffix+"::mass");
	tPhysicsComponentVolumeConvexParameters.nxsFile="nxs:"+getPropertyString(XMLCustomPropertiesNode, "PhysicsComponentVolumeConvex"+suffix+"::nxsFile");

	return tPhysicsComponentVolumeConvexParameters;
}

TLogicComponentItemParameters LevelLoader::processLogicComponentItem(TiXmlElement *XMLNodeDreams,
												TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentItemParameters logicComponentItemParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentItemParameters.existsInDreams=true;
		logicComponentItemParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentItemParameters.existsInDreams=true;
		logicComponentItemParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentItemParameters.existsInDreams=false;
		logicComponentItemParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentItemParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentItemParameters.scriptFilename="";
		}
		try{
			logicComponentItemParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentItemParameters.scriptFunction="";
		}
		try{
			logicComponentItemParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentItemParameters.defaultState=0;
		}
	}
	return logicComponentItemParameters;
}

TLogicComponentOnyParameters LevelLoader::processLogicComponentOny(TiXmlElement *XMLNodeDreams,
												TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentOnyParameters logicComponentOnyParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentOnyParameters.existsInDreams=true;
		logicComponentOnyParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentOnyParameters.existsInDreams=true;
		logicComponentOnyParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentOnyParameters.existsInDreams=false;
		logicComponentOnyParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentOnyParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentOnyParameters.scriptFilename="";
		}
		try{
			logicComponentOnyParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentOnyParameters.scriptFunction="";
		}
		try{
			logicComponentOnyParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentOnyParameters.defaultState=0;
		}
		try{
			logicComponentOnyParameters.healthPoints=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::healthPoints");
		}
		catch (std::string error)
		{
			logicComponentOnyParameters.healthPoints=-1;
		}
		try{
			logicComponentOnyParameters.numLives=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::numLives");
		}
		catch (std::string error)
		{
			logicComponentOnyParameters.numLives=-1;	
		}
		try{
			logicComponentOnyParameters.attackDamage=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::attackDamage");
		}
		catch (std::string error)
		{
			logicComponentOnyParameters.attackDamage=-1;	
		}
	}
	return logicComponentOnyParameters;
}

TLogicComponentEnemyParameters LevelLoader::processLogicComponentEnemy(TiXmlElement *XMLNodeDreams,
												TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentEnemyParameters logicComponentEnemyParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentEnemyParameters.existsInDreams=true;
		logicComponentEnemyParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentEnemyParameters.existsInDreams=true;
		logicComponentEnemyParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentEnemyParameters.existsInDreams=false;
		logicComponentEnemyParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentEnemyParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentEnemyParameters.scriptFilename="";
		}
		try{
			logicComponentEnemyParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentEnemyParameters.scriptFunction="";
		}
		try{
			logicComponentEnemyParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentEnemyParameters.defaultState=0;
		}
		try{
			logicComponentEnemyParameters.healthPoints=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::healthPoints");
		}
		catch (std::string error)
		{
			logicComponentEnemyParameters.healthPoints=-1;
		}
		try{
			logicComponentEnemyParameters.lineOfSight=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::lineOfSight");
		}
		catch (std::string error)
		{
			logicComponentEnemyParameters.lineOfSight=-1;	
		}
			
		try{
			logicComponentEnemyParameters.colourSensitivityMask=getPropertyInt(XMLNodeNightmares,
				"LogicComponent::colourSensitivityMask");
		}
		catch (std::string error)
		{
			logicComponentEnemyParameters.colourSensitivityMask=0;	
		}

	}
	return logicComponentEnemyParameters;
}
TLogicComponentUsableParameters LevelLoader::processLogicComponentUsable(TiXmlElement *XMLNodeDreams,
																	   TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentUsableParameters logicComponentUsableParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentUsableParameters.existsInDreams=true;
		logicComponentUsableParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentUsableParameters.existsInDreams=true;
		logicComponentUsableParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentUsableParameters.existsInDreams=false;
		logicComponentUsableParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentUsableParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentUsableParameters.scriptFilename="";
		}
		try{
			logicComponentUsableParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentUsableParameters.scriptFunction="";
		}
		try{
			logicComponentUsableParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentUsableParameters.defaultState=0;
		}
		try{
			logicComponentUsableParameters.approachDistance=getPropertyReal(XMLNodeCustomProperties,
				"LogicComponent::approachDistance");
		}
		catch (std::string error)
		{
			logicComponentUsableParameters.approachDistance=0.0f;
		}
		try{
			logicComponentUsableParameters.activateDistance=getPropertyReal(XMLNodeCustomProperties,
				"LogicComponent::activateDistance");
		}
		catch (std::string error)
		{
			logicComponentUsableParameters.activateDistance=0.0f;	
		}
	}
	return logicComponentUsableParameters;
}

TLogicComponentTriggerParameters LevelLoader::processLogicComponentTrigger(TiXmlElement *XMLNodeDreams,
																		 TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentTriggerParameters logicComponentTriggerParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentTriggerParameters.existsInDreams=true;
		logicComponentTriggerParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentTriggerParameters.existsInDreams=true;
		logicComponentTriggerParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentTriggerParameters.existsInDreams=false;
		logicComponentTriggerParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentTriggerParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentTriggerParameters.scriptFilename="";
		}
		try{
			logicComponentTriggerParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentTriggerParameters.scriptFunction="";
		}
		try{
			logicComponentTriggerParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentTriggerParameters.defaultState=0;
		}
		try{
			std::string script="";
			if (XMLNodeDreams)
				script=getPropertyString(XMLNodeDreams,
					"LogicComponent::triggerScript");
			if (script.empty() && XMLNodeNightmares)
				script=getPropertyString(XMLNodeNightmares,
				"LogicComponent::triggerScript");
			logicComponentTriggerParameters.mTriggerScript=script;
		}
		catch (std::string error)
		{
			logicComponentTriggerParameters.mTriggerScript="";
		}
		try
		{
			logicComponentTriggerParameters.mDreamsEnterActionFunction=(XMLNodeDreams)
				?getPropertyString(XMLNodeDreams,"LogicComponent::enterActionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mDreamsEnterActionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mDreamsEnterConditionFunction=(XMLNodeDreams)
				?getPropertyString(XMLNodeDreams,"LogicComponent::enterConditionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mDreamsEnterConditionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mDreamsExitActionFunction=(XMLNodeDreams)
				?getPropertyString(XMLNodeDreams,"LogicComponent::exitActionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mDreamsExitActionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mDreamsExitConditionFunction=(XMLNodeDreams)
				?getPropertyString(XMLNodeDreams,"LogicComponent::exitConditionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mDreamsExitConditionFunction="";
		} 
		//
		try
		{
			logicComponentTriggerParameters.mNightmaresEnterActionFunction=(XMLNodeNightmares)
				?getPropertyString(XMLNodeNightmares,"LogicComponent::enterActionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mNightmaresEnterActionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mNightmaresEnterConditionFunction=(XMLNodeNightmares)
				?getPropertyString(XMLNodeNightmares,"LogicComponent::enterConditionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mNightmaresEnterConditionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mNightmaresExitActionFunction=(XMLNodeNightmares)
				?getPropertyString(XMLNodeNightmares,"LogicComponent::exitActionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mNightmaresExitActionFunction="";
		} 
		try
		{
			logicComponentTriggerParameters.mNightmaresExitConditionFunction=(XMLNodeNightmares)
				?getPropertyString(XMLNodeNightmares,"LogicComponent::exitConditionFunction")
				:"";
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mNightmaresExitConditionFunction="";
		} 	
	}
	return logicComponentTriggerParameters;
}

TAttackComponentParameters LevelLoader::processAttackComponent(TiXmlElement* XMLNode)
{
	TAttackComponentParameters params;
	if (XMLNode)
	{
		params.mSelectedAttack=getPropertyString(XMLNode,"AttackComponent::selectedAttack",false);

		int i=0;
		AttackDataPtr currentAttack;
		while(true)
		{
			std::string name=getPropertyString(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#attackName",
				false);
			
			int type=getPropertyInt(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#type",false);
			switch(static_cast<TAttackType>(type))
			{
			case ATTACK_TYPE_FLASHLIGHT:
				currentAttack=AttackDataPtr(new FlashlightAttackData());
				break;
			case ATTACK_TYPE_PILLOW:
			case ATTACK_TYPE_DEFAULT:
				currentAttack=AttackDataPtr(new AttackData());
				break;
			}
			currentAttack->attackName=name;
			currentAttack->animationName=getPropertyString(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#animationName",
				false);
			currentAttack->damage=getPropertyInt(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#damage",
				false);
			currentAttack->attackRange=getPropertyInt(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#attackRange",
				false);
			currentAttack->cooldownDelay=getPropertyReal(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#cooldownDelay",
				false);
			currentAttack->area=getPropertyReal(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#area",
				false);
			currentAttack->powerCost=getPropertyInt(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#powerCost",
				false);
			
			if (static_cast<TAttackType>(type)==ATTACK_TYPE_FLASHLIGHT && 
				(boost::dynamic_pointer_cast<FlashlightAttackData>(currentAttack)))
			{				
				int rgb;
				try{
					rgb=Utils::parseInt(getPropertyString(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#rgb",
						false));
				}
				catch(const std::exception& e)
				{
					Ogre::LogManager::getSingletonPtr()->logMessage("Couldn't parse RGB value: defaulting to 0x000000ff");
					std::string msg="Exception message: ";
					msg.append(e.what());
					Ogre::LogManager::getSingletonPtr()->logMessage(msg);
					rgb=0x000000ff;
				}
				boost::dynamic_pointer_cast<FlashlightAttackData>(currentAttack)->rgb=rgb;
				boost::dynamic_pointer_cast<FlashlightAttackData>(currentAttack)->coneRadius=getPropertyReal(XMLNode,
					"AttackComponent::attack"+StringConverter::toString(i)+"#coneRadius",
					false);
			}
			if (name.compare("")==0) break;

			params.mAttacks[currentAttack->attackName]=currentAttack;
			++i;
		}
	}
	return params;
}
TWeaponComponentParameters LevelLoader::processWeaponComponent(TiXmlElement* XMLNode)
{
	TWeaponComponentParameters params;
	if (XMLNode)
	{
		params.mSelectedWeapon=getPropertyString(XMLNode,"WeaponComponent::selectedWeapon",false);

		int i=0;
		std::string currentWeapon;
		while(true)
		{
			currentWeapon=getPropertyString(XMLNode,"WeaponComponent::weapon"+StringConverter::toString(i),
				false);
			if (currentWeapon.compare("")==0) break;

			params.mWeaponNames.push_back(currentWeapon);
			++i;
		}
	}
	return params;
}
TLogicComponentParameters LevelLoader::processLogicComponent(TiXmlElement *XMLNodeDreams,
												TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentParameters tLogicComponentParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		tLogicComponentParameters.existsInDreams=true;
		tLogicComponentParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		tLogicComponentParameters.existsInDreams=true;
		tLogicComponentParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		tLogicComponentParameters.existsInDreams=false;
		tLogicComponentParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			tLogicComponentParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			tLogicComponentParameters.scriptFilename="";
		}
		try{
			tLogicComponentParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			tLogicComponentParameters.scriptFunction="";
		}
		try{
			tLogicComponentParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			tLogicComponentParameters.defaultState=0;
		}
	}
	return tLogicComponentParameters;
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
		throw std::string("Missing XML Node!");
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