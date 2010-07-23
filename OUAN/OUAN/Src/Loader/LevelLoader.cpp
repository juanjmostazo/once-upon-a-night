#include "OUAN_Precompiled.h"

#include "LevelLoader.h"
#include "XMLParser.h"
#include "XMLTrajectory.h"
#include "XMLWalkabilityMap.h"
#include "XMLGameObject.h"
#include "XMLSceneNode.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObjectFactory.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
#include "../Graphics/TrajectoryManager/TrajectoryNode.h"
#include "../Graphics/TrajectoryManager/WalkabilityMap.h"
#include "../Component/Component.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectBee_Butterfly.h"
#include "../Game/GameObject/GameObjectBillboardSet.h"
#include "../Game/GameObject/GameObjectTraspasable.h"
#include "../Game/GameObject/GameObjectCarnivorousPlant.h"
#include "../Game/GameObject/GameObjectClockPiece.h"
#include "../Game/GameObject/GameObjectCloud.h"
#include "../Game/GameObject/GameObjectCryKing.h"
#include "../Game/GameObject/GameObjectDiamond.h"
#include "../Game/GameObject/GameObjectDiamondTree.h"
#include "../Game/GameObject/GameObjectDoor.h"
#include "../Game/GameObject/GameObjectBoss.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectFlashLight.h"
#include "../Game/GameObject/GameObjectFog.h"
#include "../Game/GameObject/GameObjectHeart.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectLight.h"
#include "../Game/GameObject/GameObjectMagicClock.h"
#include "../Game/GameObject/GameObjectNest.h"
#include "../Game/GameObject/GameObjectNightGoblin.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectParticleSystem.h"
#include "../Game/GameObject/GameObjectPillow.h"
#include "../Game/GameObject/GameObjectPlane.h"
#include "../Game/GameObject/GameObjectPlataform.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectProvisionalEntity.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectScene.h"
#include "../Game/GameObject/GameObjectScepter.h"
#include "../Game/GameObject/GameObjectSignpost.h"
#include "../Game/GameObject/GameObjectSkyBody.h"
#include "../Game/GameObject/GameObjectSnakeCreeper.h"
#include "../Game/GameObject/GameObjectSound.h"
#include "../Game/GameObject/GameObjectStoryBook.h"
#include "../Game/GameObject/GameObjectTenteTieso.h"
#include "../Game/GameObject/GameObjectTerrainTriangle.h"
#include "../Game/GameObject/GameObjectTerrainConvex.h"
#include "../Game/GameObject/GameObjectTree.h"
#include "../Game/GameObject/GameObjectTreeComplex.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectCameraTrigger.h"
#include "../Game/GameObject/GameObjectTripolloNightmares.h"
#include "../Game/GameObject/GameObjectTripolloDreams.h"
#include "../Game/GameObject/GameObjectTower.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Game/GameObject/GameObjectWoodBox.h"
#include "../Game/GameObject/GameObjectWater.h"
#include "../Game/GameObject/GameObjectBomb.h"
#include "../Game/GameObject/GameObjectSwitch.h"
#include "../Game/GameObject/GameObjectTotem.h"
#include "../Game/GameObject/GameObjectLevelEntrance.h"

#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"
#include "../Graphics/CameraManager/CameraTrigger.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Graphics/RenderComponent/RenderComponentWater.h"
#include "../Graphics/RenderComponent/RenderComponentPlane.h"
#include "../Physics/PhysicsComponent/PhysicsComponent.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimple.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../RayCasting/RayCasting.h"
#include "../Utils/Utils.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../Logic/LogicComponent/LogicComponent.h"
#include "../Logic/LogicComponent/LogicComponentOny.h"
#include "../Logic/LogicComponent/LogicComponentItem.h"
#include "../Logic/LogicComponent/LogicComponentBreakable.h"
#include "../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../Logic/LogicComponent/LogicComponentUsable.h"
#include "../Logic/LogicComponent/LogicComponentProp.h"

using namespace OUAN;

LevelLoader::LevelLoader()
{
	mGameObjectFactory = GameObjectFactoryPtr(new GameObjectFactory());
}

LevelLoader::~LevelLoader(){
	if (mGameObjectFactory.get())
	{
		mGameObjectFactory.reset();
	}

	if (mGameWorldManager.get())
	{
		mGameWorldManager.reset();
	}
}

void LevelLoader::init(OUAN::ApplicationPtr app)
{
	mGameWorldManager=app->getGameWorldManager();
	mGameObjectFactory->init(app);
	mXMLParser.init();
}

//void LevelLoader::loadLevel(String level)
//{
//	Logger::getInstance()->log("[LevelLoader] Loading level "+level);
//
//	//IMPORTANT: THIS METHOD ISN'T CALLED ANYMORE. THE LOADING PROCESS IS NOW
//	//MANAGED AT THE LEVEL LOADING STATE, CALLING THESE METHODS ONE BY ONE AT EACH
//	//LOADING STAGE
//
//	//clear parser content
//	mXMLParser.clearLevelInfo();
//
//	//Parse Level's GameObjects
//	mXMLParser.parseLevel(level);
//
//	//Process Level's Scene Nodes
//	processSceneNodes();
//
//	//Process Level's GameObjects
//	processGameObjects();
//
//	//Process Level's GameObjectClouds
//	if (Ogre::StringUtil::match(level, "Level2"))
//	{
//		processGameObjectFractalClouds();
//		processGameObjectBillboardClouds();
//	}
//	
//	//Process Level's Trajectories
//	processTrajectories();
//
//	//Process Level's Walkability Maps
//	processWalkabilityMaps();
//
//	//clear information, as we do not need it anymore
//	mXMLParser.clearLevelInfo();
//
//	Logger::getInstance()->log("[LevelLoader] Loading level "+level+" Done!");
//}

void LevelLoader::processSceneNodes()
{
	unsigned int i;
	for(i=0;i<mXMLParser.mXMLSceneNodeContainer.size();i++)
	{
		processSceneNode(&mXMLParser.mXMLSceneNodeContainer[i]);
	}
}

void LevelLoader::processSceneNode(XMLSceneNode* sceneNode)
{
	mGameWorldManager->createSceneNode(sceneNode->name,processRenderComponentPositional(sceneNode->XMLNode));
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

		Logger::getInstance()->log("[LevelLoader] Loading GameObject "+gameObject->name);

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
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLO_DREAMS)==0)
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
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BOSS)==0)
		{
			processGameObjectBoss(gameObject);
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
			processGameObjectDiamond(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SCAREDPLANT)==0)
		{
			processGameObjectScaredPlant(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CLOCKPIECE)==0)
		{
			processGameObjectClockPiece(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRIPOLLO_NIGHTMARES)==0)
		{
			processGameObjectTripolloNightmares(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_SKYBODY)==0)
		{
			processGameObjectSkyBody(gameObject);
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
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_PLANE)==0)
		{
			processGameObjectPlane(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRASPASABLE)==0)
		{
			processGameObjectTraspasable(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRASPASABLE1)==0)
		{
			processGameObjectTraspasable(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRASPASABLE2)==0)
		{
			processGameObjectTraspasable(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TRASPASABLE3)==0)
		{
			processGameObjectTraspasable(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_CLOUD)==0)
		{
			//DO NOTHING, CLOUDS ARE GENERATED FROM CODE
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_WOODBOX)==0)
		{
			//processGameObjectWoodBox(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_WATER)==0)
		{
			processGameObjectWater(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_SOUND)==0)
		{
			processGameObjectSound(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_TOWER)==0)
		{
			processGameObjectTower(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_FOG)==0)
		{
			processGameObjectFog(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_TRIGGER_CAMERA)==0)
		{
			processGameObjectCameraTrigger(gameObject);
		}
		else if (gameObjectType.compare(GAME_OBJECT_TYPE_SIGNPOST)==0)
		{
			processGameObjectSignPost(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_NEST)==0)
		{
			processGameObjectNest(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_SWITCH)==0)
		{
			processGameObjectSwitch(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_TOTEM)==0)
		{
			processGameObjectTotem(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_BOMB)==0)
		{
			processGameObjectBomb(gameObject);
		}
		else if( gameObjectType.compare(GAME_OBJECT_TYPE_LEVEL_ENTRANCE)==0)
		{
			processGameObjectLevelEntrance(gameObject);
		}
		else
		{
			//processGameObjectProvisionalEntity(gameObject);
			Logger::getInstance()->log("[LevelLoader] Error processing Game Object with type "+gameObjectType+" , the specified type does not exist");
		}
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("ERROR! [LevelLoader] Error processing Game Object "+gameObject->name+": "+error);
	}

}

void LevelLoader::processTrajectories()
{
	XMLTrajectoryContainerIterator it;

	try
	{
		for(it = mXMLParser.mXMLTrajectoryContainer.begin(); it !=mXMLParser.mXMLTrajectoryContainer.end(); it++)
		{
			Logger::getInstance()->log("[LevelLoader] Loading Trajectory "+it->first);

			processTrajectory(&it->second);
		}

		Application::getInstance()->getCameraManager()->setCameraTrajectoryNames(mXMLParser.mCameraTrajectoryNames);
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[LevelLoader] Error processing Trajectory "+it->first+": "+error);
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
		tTrajectoryNodeParameters.speed=mGameWorldManager->DEFAULT_TRAJECTORY_SPEED;
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
	for(i=0;i<pXMLTrajectory->mTrajectoryNodes.size();i++)
	{
		//Process Trajectory Node
		tTrajectoryParameters.tTrajectoryNodeParameters.push_back(processTrajectoryNode(pXMLTrajectory->mTrajectoryNodes[i]));
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
			Logger::getInstance()->log("[LevelLoader] Loading Walkability Map "+it->first);

			processWalkabilityMap(&it->second);

		}
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[LevelLoader] Error processing Walkability Map "+it->first+": "+error);
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

		//Logger::getInstance()->log("[LevelLoader] currentNeighborName" +currentNeighborName);

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
	tGameObjectBee_ButterflyParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectBee_ButterflyParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBee_ButterflyParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBee_ButterflyParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBee_ButterflyParameters.name = gameObject->name;
	
		//Get Logic component
		tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters = processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectBee_ButterflyParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		if(tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectBee_ButterflyParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
			//Get PhysicsComponentCharacterDreams
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterDreamsParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties,"Dreams");
		}

		if(tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectBee_ButterflyParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,NIGHTMARES,gameObject->XMLNodeCustomProperties);
			//Get PhysicsComponentCharacterNightmares
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterNightmaresParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties,"Nightmares");
		}
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->addGameObjectBee_Butterfly(mGameObjectFactory->createGameObjectBee_Butterfly(
		tGameObjectBee_ButterflyParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectBillboardSet(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBillboardSetParameters  tGameObjectBillboardSetParameters;
	tGameObjectBillboardSetParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectBillboardSetParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		if(tGameObjectBillboardSetParameters.tLogicComponentParameters.existsInDreams)
		{
			tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters=processRenderComponentBillboardSet(gameObject->XMLNodeDreams);
		}
		
		if(tGameObjectBillboardSetParameters.tLogicComponentParameters.existsInNightmares)
		{
			tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters=processRenderComponentBillboardSet(gameObject->XMLNodeNightmares);
		}

		//Get RenderComponentPositional
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
		
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->addGameObjectBillboardSet
		(mGameObjectFactory->createGameObjectBillboardSet(tGameObjectBillboardSetParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTraspasable(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTraspasableParameters tGameObjectTraspasableParameters;
	tGameObjectTraspasableParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTraspasableParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTraspasableParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTraspasableParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTraspasableParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTraspasableParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectTraspasableParameters.tLogicComponentParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectTraspasableParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS, gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectTraspasableParameters.tLogicComponentParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectTraspasableParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectTraspasableParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTraspasable(tGameObjectTraspasableParameters);
	mGameWorldManager->addGameObjectTraspasable(
		mGameObjectFactory->createGameObjectTraspasable(tGameObjectTraspasableParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectCarnivorousPlant(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters;
	tGameObjectCarnivorousPlantParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectCarnivorousPlantParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters);
	mGameWorldManager->addGameObjectCarnivorousPlant(mGameObjectFactory->createGameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters,
		mGameWorldManager));
}

void LevelLoader::processGameObjectClockPiece(XMLGameObject* gameObject)
{
	OUAN::TGameObjectClockPieceParameters tGameObjectClockPieceParameters;
	tGameObjectClockPieceParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectClockPieceParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		//Get RenderComponentGlow
		tGameObjectClockPieceParameters.tRenderComponentGlowParameters=processRenderComponentGlow(gameObject->XMLNodeCustomProperties);

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
	//mGameWorldManager->createGameObjectClockPiece(tGameObjectClockPieceParameters);
	mGameWorldManager->addGameObjectClockPiece(mGameObjectFactory->createGameObjectClockPiece(
		tGameObjectClockPieceParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectCryKing(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCryKingParameters tGameObjectCryKingParameters;
	tGameObjectCryKingParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectCryKingParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectCryKing(tGameObjectCryKingParameters);
	mGameWorldManager->addGameObjectCryKing(mGameObjectFactory->createGameObjectCryKing(tGameObjectCryKingParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectDiamond(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDiamondParameters tGameObjectDiamondParameters;
	tGameObjectDiamondParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectDiamondParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(
			gameObject->XMLNodeCustomProperties);
		
		//Process simple box initial velocity per instance
		try
		{
			Vector3 initialVelocity = getPropertyVector3(gameObject->getMainXMLNode(), 
				"PhysicsComponentSimpleBox::initialVelocity");
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityX=initialVelocity.x;
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityY=initialVelocity.y;
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityZ=initialVelocity.z;
		}
		catch (const std::string&)
		{
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityX=0;
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityY=0;
			tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters.initVelocityZ=0;
		}

		try
		{
			tGameObjectDiamondParameters.tParentDiamondTree=getPropertyString(gameObject->getMainXMLNode(),"ParentDiamondTree",false);
		}
		catch (const std::string&)
		{
			tGameObjectDiamondParameters.tParentDiamondTree="";
		}

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectDiamond(tGameObjectDiamondParameters);
	mGameWorldManager->addGameObjectDiamond(mGameObjectFactory->createGameObjectDiamond(tGameObjectDiamondParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectDiamondTree(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters;
	tGameObjectDiamondTreeParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectDiamondTreeParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectDiamondTreeParameters.dreamsName = gameObject->dreamsName;
		tGameObjectDiamondTreeParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectDiamondTreeParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectDiamondTreeParameters.tLogicComponentParameters=processLogicComponentProp(gameObject->XMLNodeDreams,
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
		tGameObjectDiamondTreeParameters.tPhysicsComponentCharacterParameters=processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);		
		//tGameObjectDiamondTreeParameters.tPhysicsComponentSimpleBoxParameters = processPhysicsComponentSimpleBox(
		//	gameObject->XMLNodeCustomProperties);
		//tGameObjectDiamondTreeParameters.tPhysicsComponentVolumeBoxParameters = processPhysicsComponentVolumeBox(
		//	gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectDiamondTree(tGameObjectDiamondTreeParameters);
	mGameWorldManager->addGameObjectDiamondTree(mGameObjectFactory->createGameObjectDiamondTree(tGameObjectDiamondTreeParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectDoor(XMLGameObject* gameObject)
{
	OUAN::TGameObjectDoorParameters tGameObjectDoorParameters;
	tGameObjectDoorParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectDoorParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectDoor(tGameObjectDoorParameters);
	mGameWorldManager->addGameObjectDoor(mGameObjectFactory->createGameObjectDoor(tGameObjectDoorParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectBoss(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBossParameters tGameObjectBossParameters;
	tGameObjectBossParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectBossParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeNightmares) throw NIGHTMARES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBossParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBossParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBossParameters.name = gameObject->name;

		//Get logic component
		tGameObjectBossParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectBossParameters.tRenderComponentEntityDreamsParameters = processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS,gameObject->XMLNodeCustomProperties);
		//Get RenderComponentEntityNightmares
		tGameObjectBossParameters.tRenderComponentEntityNightmaresParameters = processRenderComponentEntity(gameObject->XMLNodeNightmares,
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectBossParameters.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectBossParameters.tPhysicsComponentCharacterParameters = processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);
	
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectBoss(tGameObjectBossParameters);
	mGameWorldManager->addGameObjectBoss(mGameObjectFactory->createGameObjectBoss(tGameObjectBossParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectEye(XMLGameObject* gameObject)
{
	OUAN::TGameObjectEyeParameters tGameObjectEyeParameters;
	tGameObjectEyeParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectEyeParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectEye(tGameObjectEyeParameters);
	mGameWorldManager->addGameObjectEye(mGameObjectFactory->createGameObjectEye(tGameObjectEyeParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectFlashLight(XMLGameObject* gameObject)
{
	OUAN::TGameObjectFlashLightParameters flashlightParams;
	flashlightParams.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(
		gameObject);
	flashlightParams.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(
		gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		flashlightParams.dreamsName = gameObject->dreamsName;
		flashlightParams.nightmaresName = gameObject->nightmaresName;
		flashlightParams.name = gameObject->name;

		//Get logic component
		flashlightParams.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		flashlightParams.tRenderComponentEntityParameters = processRenderComponentEntity(gameObject->getMainXMLNode(),
			NIGHTMARES,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		flashlightParams.tRenderComponentPositionalParameters = processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeConvex
		flashlightParams.tPhysicsComponentVolumeConvexParameters = processPhysicsComponentVolumeConvex(gameObject->XMLNodeCustomProperties);

		flashlightParams.attackComponentParameters=processAttackComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	initFlashlightConeEntity(flashlightParams.tConeParams);

	//Create GameObject
	mGameWorldManager->addGameObjectFlashLight(mGameObjectFactory->createGameObjectFlashLight(flashlightParams,mGameWorldManager, 
		mGameWorldManager->getParent()->getRenderSubsystem()));
}
void LevelLoader::initFlashlightConeEntity(TRenderComponentEntityParameters& coneParams)
{
	coneParams.castshadows=false;
	coneParams.meshfile=CONE_MESH_NAME;
	coneParams.queueID=Ogre::RENDER_QUEUE_MAIN;
	coneParams.tRenderComponentEntityAnimParams.clear();
	coneParams.tRenderComponentSubEntityParameters.clear();
	TRenderComponentSubEntityParameters subEnt;
	subEnt.material=CONE_MATERIAL_NAME;
	subEnt.visible=true;
	coneParams.tRenderComponentSubEntityParameters.push_back(subEnt);		
	//Process Query flags
	coneParams.cameraCollisionType=QUERYFLAGS_NONE;
}
void LevelLoader::processGameObjectFog(XMLGameObject* gameObject)
{
	OUAN::TGameObjectFogParameters tGameObjectFogParameters;
	tGameObjectFogParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectFogParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectFogParameters.dreamsName = gameObject->dreamsName;
		tGameObjectFogParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectFogParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectFogParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectFogParameters.tLogicComponentParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectFogParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS, gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectFogParameters.tLogicComponentParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectFogParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectFogParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectFog(tGameObjectFogParameters);
	mGameWorldManager->addGameObjectFog(
		mGameObjectFactory->createGameObjectFog(tGameObjectFogParameters,mGameWorldManager));
}


void LevelLoader::processGameObjectHeart(XMLGameObject* gameObject)
{
	OUAN::TGameObjectHeartParameters tGameObjectHeartParameters;
	tGameObjectHeartParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectHeartParameters.parentNest=processCustomAttributeParentNest(gameObject);
	tGameObjectHeartParameters.spawnProbability=processCustomAttributeSpawnProbability(gameObject);
	tGameObjectHeartParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectHeart(tGameObjectHeartParameters);
	mGameWorldManager->addGameObjectHeart(mGameObjectFactory->createGameObjectHeart(tGameObjectHeartParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectItem1UP(XMLGameObject* gameObject)
{
	OUAN::TGameObjectItem1UPParameters tGameObjectItem1UPParameters;
	tGameObjectItem1UPParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectItem1UPParameters.parentNest=processCustomAttributeParentNest(gameObject);
	tGameObjectItem1UPParameters.spawnProbability=processCustomAttributeSpawnProbability(gameObject);
	tGameObjectItem1UPParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectItem1UP(tGameObjectItem1UPParameters);
	mGameWorldManager->addGameObjectItem1UP(mGameObjectFactory->createGameObjectItem1UP(tGameObjectItem1UPParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectItemMaxHP(XMLGameObject* gameObject)
{
	OUAN::TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters;
	tGameObjectItemMaxHPParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectItemMaxHPParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectItemMaxHP(tGameObjectItemMaxHPParameters);
	mGameWorldManager->addGameObjectItemMaxHP(mGameObjectFactory->createGameObjectItemMaxHP(tGameObjectItemMaxHPParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectLight(XMLGameObject* gameObject)
{
	OUAN::TGameObjectLightParameters  tGameObjectLightParameters;
	tGameObjectLightParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectLightParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectLight(tGameObjectLightParameters);
	mGameWorldManager->addGameObjectLight(mGameObjectFactory->createGameObjectLight(tGameObjectLightParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectMagicClock(XMLGameObject* gameObject)
{
	OUAN::TGameObjectMagicClockParameters tGameObjectMagicClockParameters;
	tGameObjectMagicClockParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectMagicClockParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectMagicClock(tGameObjectMagicClockParameters);
	mGameWorldManager->addGameObjectMagicClock(mGameObjectFactory->createGameObjectMagicClock(tGameObjectMagicClockParameters,mGameWorldManager));
}
void LevelLoader::processGameObjectNest(XMLGameObject* gameObject)
{
	OUAN::TGameObjectNestParameters params;
	params.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);	
	params.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(gameObject->XMLNodeNightmares) throw NIGHTMARES_SHOULD_NOT_EXIST;

		//Get names
		params.dreamsName = gameObject->dreamsName;
		params.nightmaresName = gameObject->nightmaresName;
		params.name = gameObject->name;

		//Get Logic component
		params.tLogicComponentParameters=processLogicComponentProp(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		params.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		params.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		params.tPhysicsComponentCharacterParameters= processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->addGameObjectNest(mGameObjectFactory->createGameObjectNest(params,mGameWorldManager));
}
void LevelLoader::processGameObjectNightGoblin(XMLGameObject* gameObject)
{
	OUAN::TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters;
	tGameObjectNightGoblinParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectNightGoblinParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectNightGoblin(tGameObjectNightGoblinParameters);
	mGameWorldManager->addGameObjectNightGoblin(mGameObjectFactory->createGameObjectNightGoblin(tGameObjectNightGoblinParameters,mGameWorldManager));
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
		tGameObjectOnyParameters.mMaxUpdateRadium = -1;
		tGameObjectOnyParameters.mMaxRenderRadium = -1;

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

		//Get RenderComponentQuadHalo
		tGameObjectOnyParameters.tRenderComponentQuadHaloParameters = processRenderComponentQuadHalo(gameObject->XMLNodeCustomProperties);

		//Get PhysicsComponentCharacter
		tGameObjectOnyParameters.tPhysicsComponentCharacterOnyParameters = processPhysicsComponentCharacterOny(gameObject->XMLNodeCustomProperties);

		//Get AudioComponent
		tGameObjectOnyParameters.tAudioComponentParameters = processAudioComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectOny(tGameObjectOnyParameters);
	mGameWorldManager->addGameObjectOny(mGameObjectFactory->createGameObjectOny(tGameObjectOnyParameters,mGameWorldManager,
		mGameWorldManager->getParent()->getCameraManager()));
}

void LevelLoader::processGameObjectParticleSystem(XMLGameObject* gameObject)
{
	OUAN::TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters;
	tGameObjectParticleSystemParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectParticleSystemParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectParticleSystem(tGameObjectParticleSystemParameters);
	mGameWorldManager->addGameObjectParticleSystem(mGameObjectFactory->createGameObjectParticleSystem(tGameObjectParticleSystemParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectPillow(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPillowParameters tGameObjectPillowParameters;
	tGameObjectPillowParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectPillowParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
		//Get attack component
		tGameObjectPillowParameters.attackComponentParameters=processAttackComponent(gameObject->XMLNodeCustomProperties);

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
	//mGameWorldManager->createGameObjectPillow(tGameObjectPillowParameters);
	mGameWorldManager->addGameObjectPillow(mGameObjectFactory->createGameObjectPillow(tGameObjectPillowParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectPlane(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPlaneParameters  tGameObjectPlaneParameters;
	tGameObjectPlaneParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectPlaneParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectPlaneParameters.dreamsName = gameObject->dreamsName;
		tGameObjectPlaneParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectPlaneParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectPlaneParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPlane
		tGameObjectPlaneParameters.tRenderComponentPlaneParameters=processRenderComponentPlane(gameObject->getMainXMLNode());

		//Get RenderComponentPositional
		tGameObjectPlaneParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->addGameObjectPlane
		(mGameObjectFactory->createGameObjectPlane(tGameObjectPlaneParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectPlataform(XMLGameObject* gameObject)
{
	std::string meshfile;

	OUAN::TGameObjectPlataformParameters tGameObjectPlataformParameters;
	tGameObjectPlataformParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectPlataformParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
		tGameObjectPlataformParameters.tPhysicsComponentComplexConvexParameters = processPhysicsComponentComplexConvex(gameObject->getMainXMLNode(),
			gameObject->XMLNodeCustomProperties,
			complexConvex);

		tGameObjectPlataformParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
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
	//mGameWorldManager->createGameObjectPlataform(tGameObjectPlataformParameters);
	mGameWorldManager->addGameObjectPlataform(mGameObjectFactory->createGameObjectPlataform(tGameObjectPlataformParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectPortal(XMLGameObject* gameObject)
{
	OUAN::TGameObjectPortalParameters tGameObjectPortalParameters;
	tGameObjectPortalParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectPortalParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		//Get RenderComponentGlow
		tGameObjectPortalParameters.tRenderComponentGlowDreamsParameters=processRenderComponentGlow(gameObject->XMLNodeCustomProperties, DREAMS);
		tGameObjectPortalParameters.tRenderComponentGlowNightmaresParameters=processRenderComponentGlow(gameObject->XMLNodeCustomProperties, NIGHTMARES);

		//Get RenderComponentPositional
		tGameObjectPortalParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
		
		//Get PhysicsComponentSimpleBox
		tGameObjectPortalParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

		tGameObjectPortalParameters.tAudioComponentParameters = processAudioComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectPortal(tGameObjectPortalParameters);
	mGameWorldManager->addGameObjectPortal(mGameObjectFactory->createGameObjectPortal(tGameObjectPortalParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectProvisionalEntity(XMLGameObject* gameObject)
{
	OUAN::TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters;
	tGameObjectProvisionalEntityParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectProvisionalEntityParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters);
	mGameWorldManager->addGameObjectProvisionalEntity(mGameObjectFactory->createGameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters,
		mGameWorldManager));
}

void LevelLoader::processGameObjectScaredPlant(XMLGameObject* gameObject)
{
	OUAN::TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters;
	tGameObjectScaredPlantParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectScaredPlantParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
		tGameObjectScaredPlantParameters.tLogicComponentParameters=processLogicComponentProp(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectScaredPlantParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectScaredPlantParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		tGameObjectScaredPlantParameters.tPhysicsComponentSimpleBoxParameters = processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectScaredPlant(tGameObjectScaredPlantParameters);
	mGameWorldManager->addGameObjectScaredPlant(mGameObjectFactory->createGameObjectScaredPlant(tGameObjectScaredPlantParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectScene(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSceneParameters tGameObjectSceneParameters;
	tGameObjectSceneParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectSceneParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectScene(tGameObjectSceneParameters);
	mGameWorldManager->addGameObjectScene(mGameObjectFactory->createGameObjectScene(tGameObjectSceneParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectScepter(XMLGameObject* gameObject)
{
	OUAN::TGameObjectScepterParameters tGameObjectScepterParameters;
	tGameObjectScepterParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectScepterParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectScepter(tGameObjectScepterParameters);
	mGameWorldManager->addGameObjectScepter(mGameObjectFactory->createGameObjectScepter(tGameObjectScepterParameters,mGameWorldManager));
}
void LevelLoader::processGameObjectSignPost(XMLGameObject* gameObject)
{
	TGameObjectSignPostParameters params;
	params.mMaxUpdateRadium=processCustomAttributeMaxUpdateRadium(gameObject);
	params.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);


	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;
		if(!gameObject->XMLNodeDreams) throw DREAMS_NODE_NOT_FOUND;
		if(gameObject->XMLNodeNightmares) throw NIGHTMARES_SHOULD_NOT_EXIST;

		//Get names
		params.dreamsName = gameObject->dreamsName;
		params.nightmaresName = gameObject->nightmaresName;
		params.name = gameObject->name;

		params.signpostMessage=getPropertyString(gameObject->getMainXMLNode(),"SignpostCustomProperty::message",false);

		//Get Logic component
		params.tLogicComponentParameters=processLogicComponentProp(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		params.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		params.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->XMLNodeDreams);

		//Get PhysicsComponentCharacter
		params.tPhysicsComponentCharacterParameters= processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectScaredPlant(tGameObjectScaredPlantParameters);
	mGameWorldManager->addGameObjectSignPost(mGameObjectFactory->createGameObjectSignPost(params,mGameWorldManager));
}
void LevelLoader::processGameObjectSkyBody(XMLGameObject* gameObject)
{
	TGameObjectSkyBodyParameters params;
	params.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	params.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		params.dreamsName = gameObject->dreamsName;
		params.nightmaresName = gameObject->nightmaresName;
		params.name = gameObject->name;

		params.useEntityDreams = getPropertyBool(gameObject->XMLNodeCustomProperties, "GameObjectSkyBody::useEntityDreams",false);
		params.useEntityNightmares = getPropertyBool(gameObject->XMLNodeCustomProperties, "GameObjectSkyBody::useEntityNightmares",false);

		//Get Logic component
		params.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(params.tLogicComponentParameters.existsInDreams)
		{
			//Init light properties
			params.lightDreamsParams.lighttype=Ogre::Light::LT_SPOTLIGHT;
			params.lightDreamsParams.diffuse=Ogre::ColourValue(1.0,1.0,0.9);
			params.lightDreamsParams.specular=Ogre::ColourValue::Black;
			params.lightDreamsParams.direction = Ogre::Vector3(0,-1,-1);
			params.lightDreamsParams.castshadows = true;
			params.lightDreamsParams.lightrange = Ogre::Vector3(45,80,1);
			params.lightDreamsParams.attenuation = Ogre::Vector4(10000,1,0,0);
			params.lightDreamsParams.power = 1;

			if (params.useEntityDreams)
				//Get RenderComponentEntityDreams
				params.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
					DREAMS, gameObject->XMLNodeCustomProperties);
			else
				params.bbsDreamsParams=processRenderComponentBillboardSet(gameObject->XMLNodeDreams);
		}
		if(params.tLogicComponentParameters.existsInNightmares)
		{
			params.lightNightmaresParams.lighttype=Ogre::Light::LT_SPOTLIGHT;
			params.lightNightmaresParams.diffuse=Ogre::ColourValue(0.9,0.9,1.0);
			params.lightNightmaresParams.specular=Ogre::ColourValue::Black;			
			params.lightNightmaresParams.direction = Ogre::Vector3(0,-1,-1);
			params.lightNightmaresParams.castshadows = true;
			params.lightNightmaresParams.lightrange = Ogre::Vector3(45,80,1);
			params.lightNightmaresParams.attenuation = Ogre::Vector4(10000,1,0,0);
			params.lightNightmaresParams.power = 1;

			if (params.useEntityNightmares)
			{
				//Get RenderComponentEntityNightmares
				params.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
					NIGHTMARES,gameObject->XMLNodeCustomProperties);
			}
			else
			{
				params.bbsNightmaresParams=processRenderComponentBillboardSet(gameObject->XMLNodeNightmares);
			}
		}

		//Get RenderComponentGlow
		params.tRenderComponentGlowDreamsParameters=processRenderComponentGlow(gameObject->XMLNodeCustomProperties, DREAMS);
		params.tRenderComponentGlowNightmaresParameters=processRenderComponentGlow(gameObject->XMLNodeCustomProperties, NIGHTMARES);

		//Get RenderComponentPositional
		params.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	mGameWorldManager->addGameObjectSkyBody(
		mGameObjectFactory->createGameObjectSkyBody(params,mGameWorldManager, 
		mGameWorldManager->getParent()->getCameraManager(),
		mGameWorldManager->getParent()->getRenderSubsystem()->getSceneManager()));
}
void LevelLoader::processGameObjectSnakeCreeper(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters;
	tGameObjectSnakeCreeperParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectSnakeCreeperParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters);
	mGameWorldManager->addGameObjectSnakeCreeper(mGameObjectFactory->createGameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectStoryBook(XMLGameObject* gameObject)
{
	OUAN::TGameObjectStoryBookParameters tGameObjectStoryBookParameters;
	tGameObjectStoryBookParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectStoryBookParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectStoryBook(tGameObjectStoryBookParameters);
	mGameWorldManager->addGameObjectStoryBook(mGameObjectFactory->createGameObjectStoryBook(tGameObjectStoryBookParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTentetieso(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters;
	tGameObjectTentetiesoParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTentetiesoParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectTentetieso(tGameObjectTentetiesoParameters);
	mGameWorldManager->addGameObjectTentetieso(mGameObjectFactory->createGameObjectTentetieso(tGameObjectTentetiesoParameters,mGameWorldManager));
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
			tGameObjectTerrainConvexParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
			tGameObjectTerrainConvexParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

			try
			{
				//Get names
				tGameObjectTerrainConvexParameters.dreamsName = gameObject->dreamsName;
				tGameObjectTerrainConvexParameters.nightmaresName = gameObject->nightmaresName;
				tGameObjectTerrainConvexParameters.name = gameObject->name;

				tGameObjectTerrainConvexParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
					gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

				tGameObjectTerrainConvexParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
				
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

				//Get PhysicsComponentComplexConvex
				tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters = processPhysicsComponentComplexConvex(gameObject->getMainXMLNode(),
					gameObject->XMLNodeCustomProperties,
					complexConvex, "Convex");

				//Logger::getInstance()->log("@@@ "  + gameObject->name + " ### " + Ogre::StringConverter::toString(Ogre::Real(tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters.balanceRadiumX)) + " " + Ogre::StringConverter::toString(Ogre::Real(tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters.balanceRadiumY)) + " " + Ogre::StringConverter::toString(Ogre::Real(tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters.balanceRadiumZ)) + " -> " + Ogre::StringConverter::toString(Ogre::Real(tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters.balanceRadiumTime)));	

			}
			catch( std::string error )
			{
				throw error;
				return;
			}

			//Create GameObject
			//mGameWorldManager->createGameObjectTerrainConvex(tGameObjectTerrainConvexParameters);
			mGameWorldManager->addGameObjectTerrainConvex(mGameObjectFactory->createGameObjectTerrainConvex(tGameObjectTerrainConvexParameters,
				mGameWorldManager));

			Logger::getInstance()->log("[LevelLoader] "+gameObject->name+" uses .nxs complex physics file "+complexConvex);

		}
		else if(Ogre::ResourceGroupManager::getSingleton().resourceExists(DEFAULT_OGRE_RESOURCE_MANAGER_GROUP,complexTriangle))
		{
			OUAN::TGameObjectTerrainTriangleParameters  tGameObjectTerrainTriangleParameters;
			tGameObjectTerrainTriangleParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
			tGameObjectTerrainTriangleParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

				tGameObjectTerrainTriangleParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
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
			//mGameWorldManager->createGameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters);
			mGameWorldManager->addGameObjectTerrainTriangle(mGameObjectFactory->createGameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters,
				mGameWorldManager));

			Logger::getInstance()->log("[LevelLoader] "+gameObject->name+" uses .nxs complex physics file "+complexTriangle);
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
	tGameObjectTreeParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTreeParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectTree(tGameObjectTreeParameters);
	mGameWorldManager->addGameObjectTree(mGameObjectFactory->createGameObjectTree(tGameObjectTreeParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTreeComplex(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTreeComplexParameters tGameObjectTreeComplexParameters;
	tGameObjectTreeComplexParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTreeComplexParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTreeComplexParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTreeComplexParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTreeComplexParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTreeComplexParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectTreeComplexParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectTreeComplexParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentComplexConvex
		std::string nxsfile = "CONVEX_"+tGameObjectTreeComplexParameters.tRenderComponentEntityParameters.meshfile.substr(0,
			tGameObjectTreeComplexParameters.tRenderComponentEntityParameters.meshfile.size()-5)+".nxs";
		tGameObjectTreeComplexParameters.tPhysicsComponentComplexConvexParameters=processPhysicsComponentComplexConvex(gameObject->getMainXMLNode(),
			gameObject->XMLNodeCustomProperties,nxsfile);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTreeComplex(tGameObjectTreeComplexParameters);
	mGameWorldManager->addGameObjectTreeComplex(mGameObjectFactory->createGameObjectTreeComplex(tGameObjectTreeComplexParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTower(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTowerParameters tGameObjectTowerParameters;
	tGameObjectTowerParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTowerParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTowerParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTowerParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTowerParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTowerParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectTowerParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectTowerParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			DREAMS, gameObject->XMLNodeCustomProperties);


		//Get RenderComponentPositional
		tGameObjectTowerParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentComplexTriangle
		std::string nxsfile = "TRIANGLE_"+tGameObjectTowerParameters.tRenderComponentEntityDreamsParameters.meshfile.substr(0,
			tGameObjectTowerParameters.tRenderComponentEntityDreamsParameters.meshfile.size()-5)+".nxs";
		tGameObjectTowerParameters.tPhysicsComponentComplexTriangleParameters=processPhysicsComponentComplexTriangle(gameObject->XMLNodeCustomProperties,nxsfile);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTower(tGameObjectTowerParameters);
	mGameWorldManager->addGameObjectTower(mGameObjectFactory->createGameObjectTower(tGameObjectTowerParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTriggerBox(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters;
	tGameObjectTriggerBoxParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTriggerBoxParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectTriggerBox(tGameObjectTriggerBoxParameters);
	mGameWorldManager->addGameObjectTriggerBox(mGameObjectFactory->createGameObjectTriggerBox(tGameObjectTriggerBoxParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTriggerCapsule(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters;
	tGameObjectTriggerCapsuleParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTriggerCapsuleParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters);
	mGameWorldManager->addGameObjectTriggerCapsule(mGameObjectFactory->createGameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters,
		mGameWorldManager));
}

void LevelLoader::processGameObjectCameraTrigger(XMLGameObject* gameObject)
{
	OUAN::TGameObjectCameraTriggerParameters tGameObjectCameraTriggerParameters;
	tGameObjectCameraTriggerParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectCameraTriggerParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectCameraTriggerParameters.dreamsName = gameObject->dreamsName;
		tGameObjectCameraTriggerParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectCameraTriggerParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectCameraTriggerParameters.tLogicComponentCameraTriggerParameters=processLogicComponentCameraTrigger(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntity
		tGameObjectCameraTriggerParameters.tRenderComponentEntityParameters=processRenderComponentEntity(gameObject->getMainXMLNode(),
			BOTH_WORLDS,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentPositional
		tGameObjectCameraTriggerParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentVolumeBox
		tGameObjectCameraTriggerParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBoxUsingScale(gameObject->XMLNodeCustomProperties,gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}
	//Create GameObject
	//mGameWorldManager->createGameObjectCameraTrigger(tGameObjectCameraTriggerParameters);
	mGameWorldManager->addGameObjectCameraTrigger(mGameObjectFactory->createGameObjectCameraTrigger(tGameObjectCameraTriggerParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTripolloNightmares(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTripolloNightmaresParameters tGameObjectTripolloNightmaresParameters;
	tGameObjectTripolloNightmaresParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTripolloNightmaresParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTripolloNightmaresParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTripolloNightmaresParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTripolloNightmaresParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTripolloNightmaresParameters.tLogicComponentEnemyParameters=processLogicComponentEnemy(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		if(tGameObjectTripolloNightmaresParameters.tLogicComponentEnemyParameters.existsInDreams)
		{
			//Get RenderComponentEntityDreams
			tGameObjectTripolloNightmaresParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}
		if(tGameObjectTripolloNightmaresParameters.tLogicComponentEnemyParameters.existsInNightmares)
		{
			//Get RenderComponentEntityNightmares
			tGameObjectTripolloNightmaresParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		//Get RenderComponentPositional
		tGameObjectTripolloNightmaresParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentCharacter
		tGameObjectTripolloNightmaresParameters.tPhysicsComponentCharacterParameters =  processPhysicsComponentCharacter(gameObject->XMLNodeCustomProperties);	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTripolloNightmares(tGameObjectTripolloNightmaresParameters);
	mGameWorldManager->addGameObjectTripolloNightmares(mGameObjectFactory->createGameObjectTripolloNightmares(tGameObjectTripolloNightmaresParameters,
		mGameWorldManager));
}

void LevelLoader::processGameObjectTripolloDreams(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters;
	tGameObjectTripolloDreamsParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTripolloDreamsParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		tGameObjectTripolloDreamsParameters.tAudioComponentParameters = processAudioComponent(gameObject->XMLNodeCustomProperties);

		//Get Trajectory Component
		tGameObjectTripolloDreamsParameters.tTrajectoryComponentParameters=processTrajectoryComponent(gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTripolloDreams(tGameObjectTripolloDreamsParameters);
	mGameWorldManager->addGameObjectTripolloDreams(mGameObjectFactory->createGameObjectTripolloDreams(tGameObjectTripolloDreamsParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectViewport(XMLGameObject* gameObject)
{
	OUAN::TGameObjectViewportParameters tGameObjectViewportParameters;
	tGameObjectViewportParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectViewportParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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
	//mGameWorldManager->createGameObjectViewport(tGameObjectViewportParameters);
	mGameWorldManager->addGameObjectViewport(mGameObjectFactory->createGameObjectViewport(tGameObjectViewportParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectWoodBox(XMLGameObject* gameObject)
{
	std::string meshfile;

	OUAN::TGameObjectWoodBoxParameters tGameObjectWoodBoxParameters;
	tGameObjectWoodBoxParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectWoodBoxParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

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

		//Get names
		tGameObjectWoodBoxParameters.dreamsName = gameObject->dreamsName;
		tGameObjectWoodBoxParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectWoodBoxParameters.name = gameObject->name;

		//Get PhysicsComponentSimpleBox
		tGameObjectWoodBoxParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

		//Get PhysicsComponentVolumeBox
		tGameObjectWoodBoxParameters.tPhysicsComponentVolumeBoxParameters=processPhysicsComponentVolumeBox(gameObject->XMLNodeCustomProperties);
		
		tGameObjectWoodBoxParameters.tLogicComponentBreakableParameters=processLogicComponentBreakable(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		tGameObjectWoodBoxParameters.tRenderComponentPositionalParameters= processRenderComponentPositional(gameObject->getMainXMLNode());

		if(tGameObjectWoodBoxParameters.tLogicComponentBreakableParameters.existsInDreams)
		{
			tGameObjectWoodBoxParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
				DREAMS,gameObject->XMLNodeCustomProperties);
		}

		if(tGameObjectWoodBoxParameters.tLogicComponentBreakableParameters.existsInNightmares)
		{
			tGameObjectWoodBoxParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
				NIGHTMARES,gameObject->XMLNodeCustomProperties);
		}

		tGameObjectWoodBoxParameters.tRenderComponentAdditionalParameters=processRenderComponentEntity(
			gameObject->XMLNodeCustomProperties,
			-1,gameObject->XMLNodeCustomProperties);
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectWoodBox(tGameObjectWoodBoxParameters);
	mGameWorldManager->addGameObjectWoodBox(mGameObjectFactory->createGameObjectWoodBox(tGameObjectWoodBoxParameters,mGameWorldManager));
}
void LevelLoader::processGameObjectSound(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSoundParameters  params;
	params.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	params.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		params.dreamsName = gameObject->dreamsName;
		params.nightmaresName = gameObject->nightmaresName;
		params.name = gameObject->name;
		
		try
		{
			params.soundType = static_cast<TGameObjectSoundType> (getPropertyInt(gameObject->getMainXMLNode(),"gameObjectSound::type",false));
		}
		catch(std::string&)
		{
			params.soundType=SOUNDTYPE_POSITIONAL;
		}

		try
		{
			params.currentDreamsSoundID= getPropertyString(gameObject->XMLNodeDreams,
				"gameObjectSound::currentSoundID",false);
		}
		catch(std::string&)
		{
			params.currentDreamsSoundID="";
		}

		try
		{
			params.currentNightmaresSoundID= getPropertyString(gameObject->XMLNodeNightmares,
				"gameObjectSound::currentSoundID",false);
		}
		catch(std::string&)
		{
			params.currentNightmaresSoundID="";
		}

		if (gameObject->XMLNodeDreams)
			params.tAudioComponentDreamsParameters=processAudioComponent(gameObject->XMLNodeDreams);
		if (gameObject->XMLNodeNightmares)
			params.tAudioComponentNightmaresParameters=processAudioComponent(gameObject->XMLNodeNightmares);

		//Get RenderComponentPositional
		params.tRenderComponentPositionalParameters=processRenderComponentPositionalNoScale(gameObject->getMainXMLNode());
	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectLight(tGameObjectLightParameters);
	mGameWorldManager->addGameObjectSound(mGameObjectFactory->createGameObjectSound(params,mGameWorldManager));
}

void LevelLoader::processGameObjectWater(XMLGameObject* gameObject)
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

		std::string volumeConvex="CONVEX_"+meshfile.substr(0,meshfile.size()-5)+".nxs";
		if(Ogre::ResourceGroupManager::getSingleton().resourceExists(DEFAULT_OGRE_RESOURCE_MANAGER_GROUP,volumeConvex))
		{
			OUAN::TGameObjectWaterParameters  tGameObjectWaterParameters;
			tGameObjectWaterParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
			tGameObjectWaterParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

			//Get names
			tGameObjectWaterParameters.dreamsName = gameObject->dreamsName;
			tGameObjectWaterParameters.nightmaresName = gameObject->nightmaresName;
			tGameObjectWaterParameters.name = gameObject->name;

			//Get PhysicsComponentComplexConvex
			tGameObjectWaterParameters.tPhysicsComponentVolumeConvexParameters = processPhysicsComponentVolumeConvex(gameObject->XMLNodeCustomProperties,
				volumeConvex);

			tGameObjectWaterParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
				gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

			tGameObjectWaterParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());
			
			if(tGameObjectWaterParameters.tLogicComponentParameters.existsInDreams)
			{
				tGameObjectWaterParameters.tRenderComponentWaterDreamsParameters.tRenderComponentEntityParameters=processRenderComponentEntity(
					gameObject->XMLNodeDreams, DREAMS, gameObject->XMLNodeCustomProperties);
			}
			
			if(tGameObjectWaterParameters.tLogicComponentParameters.existsInNightmares)
			{
				tGameObjectWaterParameters.tRenderComponentWaterNightmaresParameters.tRenderComponentEntityParameters=processRenderComponentEntity(
					gameObject->XMLNodeNightmares,NIGHTMARES, gameObject->XMLNodeCustomProperties);
			}

			//Create GameObject
			//mGameWorldManager->createGameObjectTerrainConvex(tGameObjectWaterParameters);
			mGameWorldManager->addGameObjectWater(mGameObjectFactory->createGameObjectWater(tGameObjectWaterParameters,
				mGameWorldManager));

			Logger::getInstance()->log("[LevelLoader] "+gameObject->name+" uses .nxs convex physics file "+volumeConvex);
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

void LevelLoader::processGameObjectSwitch(XMLGameObject* gameObject)
{
	OUAN::TGameObjectSwitchParameters tGameObjectSwitchParameters;
	tGameObjectSwitchParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectSwitchParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectSwitchParameters.dreamsName = gameObject->dreamsName;
		tGameObjectSwitchParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectSwitchParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectSwitchParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectSwitchParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectSwitchParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			DREAMS, gameObject->XMLNodeCustomProperties);


		//Get RenderComponentPositional
		tGameObjectSwitchParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectSwitchParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectSwitch(tGameObjectSwitchParameters);
	mGameWorldManager->addGameObjectSwitch(mGameObjectFactory->createGameObjectSwitch(tGameObjectSwitchParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectBomb(XMLGameObject* gameObject)
{
	OUAN::TGameObjectBombParameters tGameObjectBombParameters;
	tGameObjectBombParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectBombParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectBombParameters.dreamsName = gameObject->dreamsName;
		tGameObjectBombParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectBombParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectBombParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectBombParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectBombParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			DREAMS, gameObject->XMLNodeCustomProperties);


		//Get RenderComponentPositional
		tGameObjectBombParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentSimpleBox
		tGameObjectBombParameters.tPhysicsComponentSimpleBoxParameters=processPhysicsComponentSimpleBox(gameObject->XMLNodeCustomProperties);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectBomb(tGameObjectBombParameters);
	mGameWorldManager->addGameObjectBomb(mGameObjectFactory->createGameObjectBomb(tGameObjectBombParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectTotem(XMLGameObject* gameObject)
{
	OUAN::TGameObjectTotemParameters tGameObjectTotemParameters;
	tGameObjectTotemParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectTotemParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectTotemParameters.dreamsName = gameObject->dreamsName;
		tGameObjectTotemParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectTotemParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectTotemParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectTotemParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectTotemParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			DREAMS, gameObject->XMLNodeCustomProperties);


		//Get RenderComponentPositional
		tGameObjectTotemParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentComplexTriangle
		std::string nxsfile = "TRIANGLE_"+tGameObjectTotemParameters.tRenderComponentEntityDreamsParameters.meshfile.substr(0,
			tGameObjectTotemParameters.tRenderComponentEntityDreamsParameters.meshfile.size()-5)+".nxs";
		tGameObjectTotemParameters.tPhysicsComponentComplexTriangleParameters=processPhysicsComponentComplexTriangle(gameObject->XMLNodeCustomProperties,nxsfile);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectTotem(tGameObjectTotemParameters);
	mGameWorldManager->addGameObjectTotem(mGameObjectFactory->createGameObjectTotem(tGameObjectTotemParameters,mGameWorldManager));
}

void LevelLoader::processGameObjectLevelEntrance(XMLGameObject* gameObject)
{
	OUAN::TGameObjectLevelEntranceParameters tGameObjectLevelEntranceParameters;
	tGameObjectLevelEntranceParameters.mMaxUpdateRadium = processCustomAttributeMaxUpdateRadium(gameObject);
	tGameObjectLevelEntranceParameters.mMaxRenderRadium = processCustomAttributeMaxRenderRadium(gameObject);

	try
	{
		//Check parsing errors
		if(!gameObject->XMLNodeCustomProperties) throw CUSTOM_PROPERTIES_NODE_NOT_FOUND;

		//Get names
		tGameObjectLevelEntranceParameters.dreamsName = gameObject->dreamsName;
		tGameObjectLevelEntranceParameters.nightmaresName = gameObject->nightmaresName;
		tGameObjectLevelEntranceParameters.name = gameObject->name;

		//Get Logic component
		tGameObjectLevelEntranceParameters.tLogicComponentParameters=processLogicComponent(gameObject->XMLNodeDreams,
			gameObject->XMLNodeNightmares,gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityDreams
		tGameObjectLevelEntranceParameters.tRenderComponentEntityDreamsParameters=processRenderComponentEntity(gameObject->XMLNodeDreams,
			DREAMS, gameObject->XMLNodeCustomProperties);

		//Get RenderComponentEntityNightmares
		tGameObjectLevelEntranceParameters.tRenderComponentEntityNightmaresParameters=processRenderComponentEntity(gameObject->XMLNodeNightmares,
			DREAMS, gameObject->XMLNodeCustomProperties);


		//Get RenderComponentPositional
		tGameObjectLevelEntranceParameters.tRenderComponentPositionalParameters=processRenderComponentPositional(gameObject->getMainXMLNode());

		//Get PhysicsComponentComplexTriangle
		std::string nxsfile = "TRIANGLE_"+tGameObjectLevelEntranceParameters.tRenderComponentEntityDreamsParameters.meshfile.substr(0,
			tGameObjectLevelEntranceParameters.tRenderComponentEntityDreamsParameters.meshfile.size()-5)+".nxs";
		tGameObjectLevelEntranceParameters.tPhysicsComponentComplexTriangleParameters=processPhysicsComponentComplexTriangle(gameObject->XMLNodeCustomProperties,nxsfile);

	}
	catch( std::string error )
	{
		throw error;
		return;
	}

	//Create GameObject
	//mGameWorldManager->createGameObjectLevelEntrance(tGameObjectLevelEntranceParameters);
	mGameWorldManager->addGameObjectLevelEntrance(mGameObjectFactory->createGameObjectLevelEntrance(tGameObjectLevelEntranceParameters,mGameWorldManager));
}

TRenderComponentFogParameters LevelLoader::processRenderComponentFog(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentFogParameters tRenderComponentFogParameters;
	int fogMode;
	fogMode=getPropertyInt(XMLNode,"fog::mode");
	switch(fogMode)
	{
	case OGITOR_FM_NONE:
		tRenderComponentFogParameters.fogMode=Ogre::FOG_NONE;
		break;
	case OGITOR_FM_LINEAR:
		tRenderComponentFogParameters.fogMode=Ogre::FOG_LINEAR;
		break;
	case OGITOR_FM_EXP:
		tRenderComponentFogParameters.fogMode=Ogre::FOG_EXP;
		break;
	case OGITOR_FM_EXP2:
		tRenderComponentFogParameters.fogMode=Ogre::FOG_EXP2;
		break;
	default:
		break;
	}
	tRenderComponentFogParameters.colour=getPropertyColourValue(XMLNode,"fog::colour");
	tRenderComponentFogParameters.density=getPropertyReal(XMLNode,"fog::density");
	tRenderComponentFogParameters.start=getPropertyReal(XMLNode,"fog::start");
	tRenderComponentFogParameters.end=getPropertyReal(XMLNode,"fog::end");

	return tRenderComponentFogParameters;
}

TRenderComponentSceneParameters LevelLoader::processRenderComponentScene(TiXmlElement *XMLOgitorNode,TiXmlElement *XMLCustomPropertiesNode)
{
	OUAN::TRenderComponentSceneParameters tRenderComponentSceneParameters;

	tRenderComponentSceneParameters.ambient=getPropertyColourValue(XMLOgitorNode,"ambient");

	//Process SkyDome
	tRenderComponentSceneParameters.tRenderComponentSkyDomeParameters=processRenderComponentSkyDome(XMLCustomPropertiesNode);

	//TODO: Process Fog
	tRenderComponentSceneParameters.tRenderComponentFogParameters=processRenderComponentFog(XMLOgitorNode);

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

//TRenderComponentCameraParameters LevelLoader::processRenderComponentCamera(TiXmlElement *XMLNode)
//{
//	OUAN::TRenderComponentCameraParameters tRenderComponentCameraParameters;
//
//	//Get Camera properties
//	tRenderComponentCameraParameters.autotracktarget = getPropertyString(XMLNode,"autotracktarget");
//	tRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"orientation");
//	tRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"position");
//	tRenderComponentCameraParameters.autoaspectratio = false;//getPropertyBool(XMLNode,"autoaspectratio");
//	tRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"clipdistance");
//	tRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"viewmode");
//
//	//set FOVy
//	//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
//	Real FOVy = getPropertyReal(XMLNode,"fov");
//	FOVy=FOVy*55.0f;
//	if(FOVy>180.0) FOVy=179.99;
//	else if(FOVy<=0) FOVy=0.01;
//	tRenderComponentCameraParameters.FOVy=FOVy;
//
//		//PolygonModeConversion
//	int polygonmode = getPropertyInt(XMLNode,"polygonmode");
//	switch(polygonmode)
//		{
//			case OGITOR_PM_SOLID:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
//				break;
//			case OGITOR_PM_POINTS:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
//				break;
//			case OGITOR_PM_WIREFRAME:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
//				break;
//			default:
//				Logger::getInstance()->log("Camera has unrecognised PolygonMode!");
//				break;
//		}
//
//	return tRenderComponentCameraParameters;
//}
//TRenderComponentCameraParameters LevelLoader::processRenderComponentCameraViewport(TiXmlElement *XMLNode)
//{
//
//	OUAN::TRenderComponentCameraParameters tRenderComponentCameraParameters;
//
//	//Get Camera properties
//	tRenderComponentCameraParameters.autotracktarget = "None";
//	tRenderComponentCameraParameters.orientation = getPropertyQuaternion(XMLNode,"camera::orientation");
//	tRenderComponentCameraParameters.position = getPropertyVector3(XMLNode,"camera::position");
//	tRenderComponentCameraParameters.autoaspectratio = false;
//	tRenderComponentCameraParameters.clipdistance = getPropertyVector2(XMLNode,"camera::clipdistance");
//	tRenderComponentCameraParameters.viewmode = getPropertyInt(XMLNode,"camera::viewmode");
//
//	//set FOVy
//	//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
//	Real FOVy = getPropertyReal(XMLNode,"camera::fov");
//	FOVy=FOVy*55.0f;
//	if(FOVy>180.0) FOVy=179.99;
//	else if(FOVy<=0) FOVy=0.01;
//	tRenderComponentCameraParameters.FOVy=FOVy;
//
//		//PolygonModeConversion
//	int polygonmode = getPropertyInt(XMLNode,"camera::polymode");
//	switch(polygonmode)
//		{
//			case OGITOR_PM_SOLID:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;
//				break;
//			case OGITOR_PM_POINTS:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_POINTS;
//				break;
//			case OGITOR_PM_WIREFRAME:
//				tRenderComponentCameraParameters.polygonmode=Ogre::PM_WIREFRAME;
//				break;
//			default:
//				Logger::getInstance()->log("Camera has unrecognised PolygonMode!");
//				break;
//		}
//
//	return tRenderComponentCameraParameters;
//}
TRenderComponentPositionalParameters LevelLoader::processRenderComponentPositional(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentPositionalParameters tRenderComponentPositionalParameters;

	//Get parent SceneNode name
	tRenderComponentPositionalParameters.parentSceneNodeName = getAttrib(XMLNode,"parentnode");

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
	tRenderComponentPositionalParameters.parentSceneNodeName = getAttrib(XMLNode,"parentnode");

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

			Logger::getInstance()->log("Parsing animation "+currentAnimParams.name);

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
	
	//Process Query flags
	tRenderComponentEntityParameters.cameraCollisionType=processCameraCollisionType(XMLNode);

	tRenderComponentEntityParameters.queueID=processRenderQueueId(XMLNode);

	return tRenderComponentEntityParameters;
}

QueryFlags LevelLoader::processCameraCollisionType(TiXmlElement *XMLNode)
{
	//process Camera Collision Type
	QueryFlags cameraCollisionType;
	std::string camera_collision_type_string;
	int camera_collision_type_int;
	camera_collision_type_string = getPropertyString(XMLNode,"Camera Collisions::Type",false);
	if(camera_collision_type_string.compare("")!=0)
	{
		camera_collision_type_int=Ogre::StringConverter::parseInt(camera_collision_type_string);
		cameraCollisionType=QUERYFLAGS_NONE;
		switch(camera_collision_type_int)
		{
				case OGITOR_CAMERA_COLLISION_MOVE_TO_TARGET:
					cameraCollisionType=QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET;
					break;
				case OGITOR_NONE:
					cameraCollisionType=QUERYFLAGS_NONE;
					break;
				default:
					cameraCollisionType=QUERYFLAGS_NONE;
					break;
		}
		if(getPropertyBool(XMLNode,"Camera Collisions::Enable Translucid"))
		{
			cameraCollisionType=QueryFlags(
				Ogre::uint32(cameraCollisionType) | 
				Ogre::uint32(QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID));
		}
	}
	else
	{
		cameraCollisionType=QUERYFLAGS_NONE;
	}

	return cameraCollisionType;
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
				Logger::getInstance()->log("Light has unrecognised light type!");
				break;
	}

	return tRenderComponentLightParameters;

}

TRenderComponentParticleSystemParameters LevelLoader::processRenderComponentParticleSystem(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	//Process ParticleSystem properties
	tRenderComponentParticleSystemParameters.templateName = getPropertyString(XMLNode, "templateName");
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = 1;

	tRenderComponentParticleSystemParameters.queueID=processRenderQueueId(XMLNode);
	
	return tRenderComponentParticleSystemParameters;
}

TRenderComponentQuadHaloParameters LevelLoader::processRenderComponentQuadHalo(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentQuadHaloParameters tRenderComponentQuadHaloParameters;

	//Process Quad Halo properties
	tRenderComponentQuadHaloParameters.quadMaterial = getPropertyString(XMLNode, "RenderComponentQuadHalo::quadMaterial");
	tRenderComponentQuadHaloParameters.haloRadium = getPropertyReal(XMLNode, "RenderComponentQuadHalo::haloRadio");
	tRenderComponentQuadHaloParameters.totalQuads = getPropertyReal(XMLNode, "RenderComponentQuadHalo::totalQuads");
	tRenderComponentQuadHaloParameters.quadSize = getPropertyReal(XMLNode, "RenderComponentQuadHalo::quadSize");
	tRenderComponentQuadHaloParameters.speedScale = getPropertyReal(XMLNode, "RenderComponentQuadHalo::speedScale");
	tRenderComponentQuadHaloParameters.offsetX = getPropertyReal(XMLNode, "RenderComponentQuadHalo::offsetX");
	tRenderComponentQuadHaloParameters.offsetY = getPropertyReal(XMLNode, "RenderComponentQuadHalo::offsetY");
	tRenderComponentQuadHaloParameters.offsetZ = getPropertyReal(XMLNode, "RenderComponentQuadHalo::offsetZ");;

	return tRenderComponentQuadHaloParameters;
}

TRenderComponentGlowParameters LevelLoader::processRenderComponentGlow(TiXmlElement *XMLNode)
{
	return processRenderComponentGlow(XMLNode, BOTH_WORLDS);
}

TRenderComponentGlowParameters LevelLoader::processRenderComponentGlow(TiXmlElement *XMLNode, int world)
{
	OUAN::TRenderComponentGlowParameters tRenderComponentGlowParameters;

	std::string attributeHeader;

	switch (world)
	{
	case DREAMS:		attributeHeader = "RenderComponentGlowDreams";		break;
	case NIGHTMARES:	attributeHeader = "RenderComponentGlowNightmares";	break;
	default:			attributeHeader = "RenderComponentGlow";			break;
	}

	//Process Glow properties
	tRenderComponentGlowParameters.material = getPropertyString(XMLNode, attributeHeader + "::material");
	tRenderComponentGlowParameters.time_scale = getPropertyReal(XMLNode, attributeHeader + "::time_scale");
	tRenderComponentGlowParameters.size_scale = getPropertyReal(XMLNode, attributeHeader + "::size_scale");
	tRenderComponentGlowParameters.expand_width = getPropertyReal(XMLNode, attributeHeader + "::expand_width");
	tRenderComponentGlowParameters.expand_grow = getPropertyReal(XMLNode, attributeHeader + "::expand_grow");
	tRenderComponentGlowParameters.alpha = getPropertyReal(XMLNode, attributeHeader + "::alpha");
	tRenderComponentGlowParameters.color_r = getPropertyReal(XMLNode, attributeHeader + "::color_r");
	tRenderComponentGlowParameters.color_g = getPropertyReal(XMLNode, attributeHeader + "::color_g");
	tRenderComponentGlowParameters.color_b = getPropertyReal(XMLNode, attributeHeader + "::color_b");

	return tRenderComponentGlowParameters;
}

TRenderComponentFractalVolumeParameters LevelLoader::processRenderComponentFractalVolume(TiXmlElement *XMLNode)
{
	OUAN::TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeParameters;

	//Process Fractal Volume properties
	tRenderComponentFractalVolumeParameters.texture3D = getPropertyString(XMLNode, "RenderComponentFractalVolume::texture3D");
	tRenderComponentFractalVolumeParameters.juliaGlobalReal = getPropertyReal(XMLNode, "RenderComponentFractalVolume::juliaGlobalReal");
	tRenderComponentFractalVolumeParameters.juliaGlobalImag = getPropertyReal(XMLNode, "RenderComponentFractalVolume::juliaGlobalImag");
	tRenderComponentFractalVolumeParameters.juliaGlobalTheta = getPropertyReal(XMLNode, "RenderComponentFractalVolume::juliaGlobalTheta");
	tRenderComponentFractalVolumeParameters.vScale = getPropertyReal(XMLNode, "RenderComponentFractalVolume::vScale");
	tRenderComponentFractalVolumeParameters.vCut = getPropertyReal(XMLNode, "RenderComponentFractalVolume::vCut");
	tRenderComponentFractalVolumeParameters.vSlices = getPropertyReal(XMLNode, "RenderComponentFractalVolume::vSlices");
	tRenderComponentFractalVolumeParameters.vSize = getPropertyReal(XMLNode, "RenderComponentFractalVolume::vSize");
	tRenderComponentFractalVolumeParameters.offsetX = getPropertyReal(XMLNode, "RenderComponentFractalVolume::offsetX");
	tRenderComponentFractalVolumeParameters.offsetY = getPropertyReal(XMLNode, "RenderComponentFractalVolume::offsetY");
	tRenderComponentFractalVolumeParameters.offsetZ = getPropertyReal(XMLNode, "RenderComponentFractalVolume::offsetZ");
	tRenderComponentFractalVolumeParameters.rotationDegreesInitialX = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesInitialX");
	tRenderComponentFractalVolumeParameters.rotationDegreesInitialY = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesInitialY");
	tRenderComponentFractalVolumeParameters.rotationDegreesInitialZ = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesInitialZ");
	tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondX = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesPerSecondX");
	tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondY = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesPerSecondY");
	tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondZ = getPropertyReal(XMLNode, "RenderComponentFractalVolume::rotationDegreesPerSecondZ");
	tRenderComponentFractalVolumeParameters.initColorR = getPropertyReal(XMLNode, "RenderComponentFractalVolume::initColorR");
	tRenderComponentFractalVolumeParameters.initColorG = getPropertyReal(XMLNode, "RenderComponentFractalVolume::initColorG");
	tRenderComponentFractalVolumeParameters.initColorB = getPropertyReal(XMLNode, "RenderComponentFractalVolume::initColorB");
	tRenderComponentFractalVolumeParameters.endColorR = getPropertyReal(XMLNode, "RenderComponentFractalVolume::endColorR");
	tRenderComponentFractalVolumeParameters.endColorG = getPropertyReal(XMLNode, "RenderComponentFractalVolume::endColorG");
	tRenderComponentFractalVolumeParameters.endColorB = getPropertyReal(XMLNode, "RenderComponentFractalVolume::endColorB");

	return tRenderComponentFractalVolumeParameters;
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
			Logger::getInstance()->log("Billboard has unrecognised BillboardType!");
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
			Logger::getInstance()->log("Billboard has unrecognised BillboardOrigin!");
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
			Logger::getInstance()->log("Billboard has unrecognised BillboardRotationType!");
			break;
	}

	//process BillboardSet's Billboards
	processRenderComponentBillboards(tRenderComponentBillboardSetParameters.tRenderComponentBillboardParameters,XMLNode);

	tRenderComponentBillboardSetParameters.queueID=processRenderQueueId(XMLNode);

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

TRenderComponentPlaneParameters LevelLoader::processRenderComponentPlane(TiXmlElement *XMLNode)
{
	TRenderComponentPlaneParameters tRenderComponentPlaneParameters;

	// Process plane parameters
	tRenderComponentPlaneParameters.material=getPropertyString(XMLNode, "material");
	tRenderComponentPlaneParameters.hasNormals=getPropertyBool(XMLNode, "hasnormals");
	tRenderComponentPlaneParameters.distance=getPropertyReal(XMLNode, "distance");
	tRenderComponentPlaneParameters.height=getPropertyReal(XMLNode, "height");
	tRenderComponentPlaneParameters.width=getPropertyReal(XMLNode, "width");
	tRenderComponentPlaneParameters.normal=getPropertyVector3(XMLNode, "normal");
	tRenderComponentPlaneParameters.numCoordSets=getPropertyInt(XMLNode, "numcoordsets");
	tRenderComponentPlaneParameters.Utile=getPropertyInt(XMLNode, "utile");
	tRenderComponentPlaneParameters.Vtile=getPropertyInt(XMLNode, "vtile");
	tRenderComponentPlaneParameters.Xsegments=getPropertyInt(XMLNode, "xsegments");
	tRenderComponentPlaneParameters.Ysegments=getPropertyInt(XMLNode, "ysegments");
	tRenderComponentPlaneParameters.queueID=processRenderQueueId(XMLNode);

	//Process Query flags
	tRenderComponentPlaneParameters.cameraCollisionType=processCameraCollisionType(XMLNode);

	return tRenderComponentPlaneParameters;
}

CameraTriggerPtr LevelLoader::processCameraTrigger(TiXmlElement *XMLNode)
{
	CameraTriggerPtr pCameraTrigger;

	pCameraTrigger.reset(new CameraTrigger());

	//CameraTriggerType Conversion
	int cameraTriggerType = getPropertyInt(XMLNode, "CameraTrigger::type");
	switch(cameraTriggerType)
	{
		case OGITOR_CTT_FREE:
			pCameraTrigger->mCameraTriggerType=CTT_FREE;
			break;
		case OGITOR_CTT_TRACKING:
			pCameraTrigger->mCameraTriggerType=CTT_TRACKING;
			break;
		case OGITOR_CTT_AUTO_ROTATION:
			pCameraTrigger->mCameraTriggerType=CTT_AUTO_ROTATION;
			break;
		case OGITOR_CTT_AUTO_CENTER:
			pCameraTrigger->mCameraTriggerType=CTT_AUTO_CENTER;
			break;
		case OGITOR_CTT_TRAJECTORY:
			pCameraTrigger->mCameraTriggerType=CTT_TRAJECTORY;
			break;
		default:
			Logger::getInstance()->log("CameraTrigger has unrecognised CameraTriggerType!");
			break;
	}
	
	pCameraTrigger->mTransition=getPropertyBool(XMLNode, "CameraTrigger::transition");
	pCameraTrigger->mCameraParameters.reset(new CameraParameters());
	pCameraTrigger->mCameraParameters->setDirection(getPropertyVector3(XMLNode, "CameraTrigger::direction"));
	pCameraTrigger->mCameraParameters->setDistance(getPropertyReal(XMLNode, "CameraTrigger::distance"));
	pCameraTrigger->mCameraParameters->setTarget(getPropertyString(XMLNode, "CameraTrigger::target"));
	pCameraTrigger->mCameraParameters->setTargetOffset(getPropertyVector3(XMLNode, "CameraTrigger::targetoffset"));
	pCameraTrigger->mTrajectory=getPropertyString(XMLNode, "CameraTrigger::trajectory");
	pCameraTrigger->mTrajectoryLookAtTarget=getPropertyBool(XMLNode, "CameraTrigger::trajectory-look_at_target");
	pCameraTrigger->mRotX=getPropertyReal(XMLNode, "CameraTrigger::rotx");
	pCameraTrigger->mRotY=getPropertyReal(XMLNode, "CameraTrigger::roty");

	return pCameraTrigger;
}

TPhysicsComponentCharacterParameters LevelLoader::processPhysicsComponentCharacter(TiXmlElement *XMLNode,std::string suffix)
{
	TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters;

	//Get Component properties
	tPhysicsComponentCharacterParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::mass");
	tPhysicsComponentCharacterParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::radius");
	tPhysicsComponentCharacterParameters.height= getPropertyReal(XMLNode, "PhysicsComponentCharacter"+suffix+"::height");
	try
	{
		tPhysicsComponentCharacterParameters.position_correction=getPropertyVector3(XMLNode,"PhysicsComponentCharacter"+suffix+"::position_correction");
	}
	catch(std::string error)
	{
		tPhysicsComponentCharacterParameters.position_correction=Vector3::ZERO;
	}
	try
	{
		tPhysicsComponentCharacterParameters.scale_correction=getPropertyVector3(XMLNode,"PhysicsComponentCharacter"+suffix+"::scale_correction");
	}
	catch(std::string error)
	{
		tPhysicsComponentCharacterParameters.scale_correction=Vector3(1,1,1);
	}

	return tPhysicsComponentCharacterParameters;
}

TPhysicsComponentCharacterOnyParameters LevelLoader::processPhysicsComponentCharacterOny(TiXmlElement *XMLNode,std::string suffix)
{
	TPhysicsComponentCharacterOnyParameters tPhysicsComponentCharacterOnyParameters;

	//Get Component properties
	tPhysicsComponentCharacterOnyParameters.mass= getPropertyReal(XMLNode, "PhysicsComponentCharacterOny"+suffix+"::mass");
	tPhysicsComponentCharacterOnyParameters.radius= getPropertyReal(XMLNode, "PhysicsComponentCharacterOny"+suffix+"::radius");
	tPhysicsComponentCharacterOnyParameters.height= getPropertyReal(XMLNode, "PhysicsComponentCharacterOny"+suffix+"::height");
	try
	{
		tPhysicsComponentCharacterOnyParameters.position_correction=getPropertyVector3(XMLNode,"PhysicsComponentCharacterOny"+suffix+"::position_correction");
	}
	catch(std::string error)
	{
		tPhysicsComponentCharacterOnyParameters.position_correction=Vector3::ZERO;
	}
	try
	{
		tPhysicsComponentCharacterOnyParameters.scale_correction=getPropertyVector3(XMLNode,"PhysicsComponentCharacterOny"+suffix+"::scale_correction");
	}
	catch(std::string error)
	{
		tPhysicsComponentCharacterOnyParameters.scale_correction=Vector3(1,1,1);
	}

	return tPhysicsComponentCharacterOnyParameters;
}

TPhysicsComponentComplexConvexParameters LevelLoader::processPhysicsComponentComplexConvex(TiXmlElement *OgitorNode,TiXmlElement *CTPNode,std::string nxsFile,std::string suffix)
{
	TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters;
	
	//Get Component properties
	try 
	{
		tPhysicsComponentComplexConvexParameters.mass = getPropertyReal(CTPNode, "PhysicsComponentComplex"+suffix+"::mass");
	}
	catch( std::string error )
	{
		tPhysicsComponentComplexConvexParameters.mass = 0;
	}

	try 
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumX = getPropertyReal(OgitorNode, "PhysicsComponentComplex"+suffix+"::balanceRadiumX");
	} 
	catch ( std::string error )
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumX = 0;
	}

	try 
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumY = getPropertyReal(OgitorNode, "PhysicsComponentComplex"+suffix+"::balanceRadiumY");
	} 
	catch ( std::string error )
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumY = 0;
	}

	try 
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumZ = getPropertyReal(OgitorNode, "PhysicsComponentComplex"+suffix+"::balanceRadiumZ");
	} 
	catch ( std::string error )
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumZ = 0;
	}

	try 
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumTime = getPropertyReal(OgitorNode, "PhysicsComponentComplex"+suffix+"::balanceRadiumTime");
	} 
	catch ( std::string error )
	{
		tPhysicsComponentComplexConvexParameters.balanceRadiumTime = 0;
	}

	//Set nxs file
	tPhysicsComponentComplexConvexParameters.nxsFile="nxs:"+nxsFile;

	return tPhysicsComponentComplexConvexParameters;
}

TPhysicsComponentComplexTriangleParameters LevelLoader::processPhysicsComponentComplexTriangle(TiXmlElement *XMLNode,std::string nxsFile,std::string suffix)
{
	TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters;
	
	//Get Component properties
	try 
	{
		tPhysicsComponentComplexTriangleParameters.mass = getPropertyReal(XMLNode, "PhysicsComponentComplex"+suffix+"::mass");	
	}
	catch( std::string error )
	{
		tPhysicsComponentComplexTriangleParameters.mass = 0;
	}

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

TPhysicsComponentVolumeConvexParameters LevelLoader::processPhysicsComponentVolumeConvex(TiXmlElement *XMLCustomPropertiesNode)
{
	TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters;

	//Get Component properties
	tPhysicsComponentVolumeConvexParameters.mass= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeConvex::mass");
	tPhysicsComponentVolumeConvexParameters.nxsFile="nxs:"+getPropertyString(XMLCustomPropertiesNode, "PhysicsComponentVolumeConvex::nxsFile");

	return tPhysicsComponentVolumeConvexParameters;
}

TPhysicsComponentVolumeConvexParameters LevelLoader::processPhysicsComponentVolumeConvex(TiXmlElement *XMLCustomPropertiesNode,std::string nxsFile)
{
	TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters;

	//Get Component properties
	tPhysicsComponentVolumeConvexParameters.mass= getPropertyReal(XMLCustomPropertiesNode, "PhysicsComponentVolumeConvex::mass");
	tPhysicsComponentVolumeConvexParameters.nxsFile="nxs:"+nxsFile;

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

TTrajectoryComponentParameters LevelLoader::processTrajectoryComponent(TiXmlElement *XMLCustomPropertiesNode)
{
	TTrajectoryComponentParameters tTrajectoryComponentParameters;

	//Get Component properties
	tTrajectoryComponentParameters.twoDimensions = getPropertyBool(XMLCustomPropertiesNode, "TrajectoryComponent::twodimensions");
	tTrajectoryComponentParameters.defaultSpeed = getPropertyReal(XMLCustomPropertiesNode, "TrajectoryComponent::defaultspeed");

	return tTrajectoryComponentParameters;
}

TLogicComponentBreakableParameters LevelLoader::processLogicComponentBreakable(TiXmlElement *XMLNodeDreams,
																	 TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentBreakableParameters logicComponentBreakableParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentBreakableParameters.existsInDreams=true;
		logicComponentBreakableParameters.existsInNightmares=true;
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentBreakableParameters.existsInDreams=true;
		logicComponentBreakableParameters.existsInNightmares=false;
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentBreakableParameters.existsInDreams=false;
		logicComponentBreakableParameters.existsInNightmares=true;
	}
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentBreakableParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentBreakableParameters.scriptFilename="";
		}
		try{
			logicComponentBreakableParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentBreakableParameters.scriptFunction="";
		}
		try{
			logicComponentBreakableParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentBreakableParameters.defaultState=0;
		}
	}
	return logicComponentBreakableParameters;
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
TLogicComponentPropParameters LevelLoader::processLogicComponentProp(TiXmlElement *XMLNodeDreams,
																		 TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentPropParameters logicComponentPropParameters;
	logicComponentPropParameters.existsInDreams=XMLNodeDreams;
	logicComponentPropParameters.existsInNightmares=XMLNodeNightmares;
	if (XMLNodeCustomProperties)
	{
		try{
			logicComponentPropParameters.scriptFilename=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFilename");
		}
		catch(std::string error)
		{
			logicComponentPropParameters.scriptFilename="";
		}
		try{
			logicComponentPropParameters.scriptFunction=getPropertyString(XMLNodeCustomProperties,
				"LogicComponent::scriptFunction");
		}
		catch(std::string error)
		{
			logicComponentPropParameters.scriptFunction="";
		}
		try{
			logicComponentPropParameters.defaultState=getPropertyInt(XMLNodeCustomProperties,
				"LogicComponent::defaultState");
		}
		catch (std::string error)
		{
			logicComponentPropParameters.defaultState=0;
		}
		try{
			logicComponentPropParameters.approachDistance=getPropertyReal(XMLNodeCustomProperties,
				"LogicComponent::approachDistance");
		}
		catch (std::string error)
		{
			logicComponentPropParameters.approachDistance=0.0f;
		}
		try{
			logicComponentPropParameters.delay=getPropertyReal(XMLNodeCustomProperties,
				"LogicComponent::delay");
		}
		catch (std::string error)
		{
			logicComponentPropParameters.delay=0.0f;
		}
	}
	return logicComponentPropParameters;
}

TLogicComponentCameraTriggerParameters LevelLoader::processLogicComponentCameraTrigger(TiXmlElement *XMLNodeDreams,
			TiXmlElement *XMLNodeNightmares, TiXmlElement* XMLNodeCustomProperties)
{
	TLogicComponentCameraTriggerParameters logicComponentCameraTriggerParameters;
	//Object exists both in dreams and nightmares
	if(XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentCameraTriggerParameters.existsInDreams=true;
		logicComponentCameraTriggerParameters.existsInNightmares=true;
		logicComponentCameraTriggerParameters.pCameraTrigger=processCameraTrigger(XMLNodeDreams);
		logicComponentCameraTriggerParameters.triggerOnlyOnce=getPropertyBool(XMLNodeDreams,"LogicComponentTriggerCamera::TriggerOnce");
	}
	//Object exists only in dreams
	else if(XMLNodeDreams && !XMLNodeNightmares)
	{
		logicComponentCameraTriggerParameters.existsInDreams=true;
		logicComponentCameraTriggerParameters.existsInNightmares=false;
		logicComponentCameraTriggerParameters.pCameraTrigger=processCameraTrigger(XMLNodeDreams);
		logicComponentCameraTriggerParameters.triggerOnlyOnce=getPropertyBool(XMLNodeDreams,"LogicComponentTriggerCamera::TriggerOnce");
	}
	//Object exists only in nightmares
	else if(!XMLNodeDreams && XMLNodeNightmares)
	{
		logicComponentCameraTriggerParameters.existsInDreams=false;
		logicComponentCameraTriggerParameters.existsInNightmares=true;
		logicComponentCameraTriggerParameters.pCameraTrigger=processCameraTrigger(XMLNodeNightmares);
		logicComponentCameraTriggerParameters.triggerOnlyOnce=getPropertyBool(XMLNodeNightmares,"LogicComponentTriggerCamera::TriggerOnce");
	}

	return logicComponentCameraTriggerParameters;
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
		try
		{
			logicComponentTriggerParameters.mDreamsExecuteEachFrame=		(XMLNodeDreams)
				?getPropertyBool(XMLNodeDreams,"LogicComponent::executeEachFrame")
				:false;
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mDreamsExecuteEachFrame=false;
		} 
		try
		{
			logicComponentTriggerParameters.mNightmaresExecuteEachFrame=		(XMLNodeNightmares)
				?getPropertyBool(XMLNodeNightmares,"LogicComponent::executeEachFrame")
				:false;
		}
		catch (std::string error) 
		{
			logicComponentTriggerParameters.mNightmaresExecuteEachFrame=false;
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
				currentAttack=AttackDataPtr(new PillowAttackData());
				break;
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
					Logger::getInstance()->log("Couldn't parse RGB value: defaulting to 0x000000ff");
					std::string msg="Exception message: ";
					msg.append(e.what());
					Logger::getInstance()->log(msg);
					rgb=0x000000ff;
				}
				boost::dynamic_pointer_cast<FlashlightAttackData>(currentAttack)->rgb=rgb;
				boost::dynamic_pointer_cast<FlashlightAttackData>(currentAttack)->coneRadius=getPropertyReal(XMLNode,
					"AttackComponent::attack"+StringConverter::toString(i)+"#coneRadius",
					false);
			}
			else if (static_cast<TAttackType>(type)==ATTACK_TYPE_PILLOW && 
				(boost::dynamic_pointer_cast<PillowAttackData>(currentAttack)))
			{				
				try{
					boost::dynamic_pointer_cast<PillowAttackData>(currentAttack)->comboDelay=
						getPropertyReal(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#comboDelay",
						false);
				}
				catch(std::string error)
				{
					boost::dynamic_pointer_cast<PillowAttackData>(currentAttack)->comboDelay=-1.0f;
				}				
				try{
					boost::dynamic_pointer_cast<PillowAttackData>(currentAttack)->nextComboAttack=
						getPropertyString(XMLNode,"AttackComponent::attack"+StringConverter::toString(i)+"#nextComboAttack",
						false);
				}
				catch(std::string error)
				{
					boost::dynamic_pointer_cast<PillowAttackData>(currentAttack)->nextComboAttack="";
				}				
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
TAudioComponentMap LevelLoader::processAudioComponent(TiXmlElement* XMLNode)
{
	TAudioComponentMap audioComponentSounds;
	audioComponentSounds.clear();
	int i=0;
	std::string soundId;
	while(true)
	{
		soundId=getPropertyString(XMLNode,"AudioComponent::soundID#"+StringConverter::toString(i),
			false);		
		if (soundId.compare("")==0) break;
	
		Logger::getInstance()->log("Adding soundID: "+soundId);

		audioComponentSounds[soundId]=-1;//No channel assigned yet (Careful on how FMOD processes access attempts with negative channels)
		++i;
	}
	return audioComponentSounds;
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

Ogre::uint8 LevelLoader::processRenderQueueId(TiXmlElement *XMLNode)
{
	Ogre::uint8 renderQueueId;
	try
	{
		renderQueueId=getPropertyInt(XMLNode, "RenderQueue::id");
	}
	catch(std::string error)
	{
		renderQueueId=Ogre::RENDER_QUEUE_MAIN;
	}
	return renderQueueId;
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

			//Logger::getInstance()->log("[LevelLoader] parsing "+propertyName+" property!");

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

				//Logger::getInstance()->log("[LevelLoader] parsing "+propertyName+" property! -> Comparing it to " + attrib_name);

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

int LevelLoader::getGameObjectsNumber()
{
	if (!mXMLParser.mXMLGameObjectContainer.empty())
	{
		return mXMLParser.mXMLGameObjectContainer.size();
	}

	return 0;
}

void LevelLoader::initializeParser(const std::string& levelFilename)
{
	//clear parser content
	mXMLParser.clearLevelInfo();

	//Parse Level's GameObjects
	mXMLParser.parseLevel(levelFilename);
}

XMLGameObjectContainerIterator LevelLoader::getGameObjectIterator()
{
	return mXMLParser.mXMLGameObjectContainer.begin();
}

XMLGameObjectContainerIterator LevelLoader::getGameObjectIteratorEnd()
{
	return mXMLParser.mXMLGameObjectContainer.end();
}

void LevelLoader::clearXMLParser()
{
	mXMLParser.clearLevelInfo();
}

void LevelLoader::processGameObjectBillboardClouds()
{
	std::string dreamsClouds[] = {"cloud1_d", "cloud2_d", "cloud3_d"} ;
	std::string nightmaresClouds[] = {"cloud1_n", "cloud2_n", "cloud3_n"} ;
	int numTypeClouds = 3;
	int numIteration = 0;
	int maxIterations = 10;

	Configuration config;
	std::string value;

	if (config.loadFromFile(BILLBOARD_CLOUDS_CFG))
	{
		std::string dreamsName = "billboard_cloud_d#";
		std::string nightmaresName = "billboard_cloud_n#";
		std::string name = "billboard_cloud#";

		config.getOption("NUM_CLOUDS", value); 
		double numClouds = atoi(value.c_str());

		config.getOption("GENERATION_RADIO_XZ_MIN", value); 
		double generationRadiumXZMIN = atof(value.c_str());

		config.getOption("GENERATION_RADIO_XZ_MAX", value); 
		double generationRadiumXZMAX = atof(value.c_str());

		config.getOption("GENERATION_RADIO_Y", value); 
		double generationRadiumY = atof(value.c_str());

		config.getOption("CENTER_POSITION_X", value); 
		double centerPositionX = atoi(value.c_str());

		config.getOption("CENTER_POSITION_Y", value); 
		double centerPositionY = atoi(value.c_str());

		config.getOption("CENTER_POSITION_Z", value); 
		double centerPositionZ = atoi(value.c_str());

		config.getOption("WIDTH", value); 
		double width = atoi(value.c_str());

		config.getOption("HEIGHT", value); 
		double height = atoi(value.c_str());

		config.getOption("SIZE_RANDOM_OFFSET", value); 
		double sizeRandomOffset = atoi(value.c_str());

		config.getOption("BILLBOARD_TYPE", value); 
		Ogre::BillboardType billboardType = Ogre::BBT_POINT;
		if (value.compare("POINT") == 0)
		{
			billboardType = Ogre::BBT_POINT;
		}
		else if (value.compare("ORIENTED_COMMON") == 0)
		{
			billboardType = Ogre::BBT_ORIENTED_COMMON;
		}
		else if (value.compare("ORIENTED_SELF") == 0)
		{
			billboardType = Ogre::BBT_ORIENTED_SELF;
		}
		else if (value.compare("PERPENDICULAR_COMMON") == 0)
		{
			billboardType = Ogre::BBT_PERPENDICULAR_COMMON;
		}
		else if (value.compare("PERPENDICULAR_SELF") == 0)
		{
			billboardType = Ogre::BBT_PERPENDICULAR_SELF;
		}

		config.getOption("BILLBOARD_ROTATION", value); 
		Ogre::BillboardRotationType billboardRotation = Ogre::BBR_TEXCOORD;
		if (value.compare("VERTEX") == 0)
		{
			billboardRotation = Ogre::BBR_VERTEX;
		}
		else if (value.compare("TEXCOORD") == 0)
		{
			billboardRotation = Ogre::BBR_TEXCOORD;
		}

		///////////////////////

		OUAN::TGameObjectBillboardSetParameters  tGameObjectBillboardSetParameters;

		tGameObjectBillboardSetParameters.tLogicComponentParameters.scriptFilename = "";
		tGameObjectBillboardSetParameters.tLogicComponentParameters.scriptFunction = "";

		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.parentSceneNodeName = "SceneManager";
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.position = Ogre::Vector3(centerPositionX, centerPositionY, centerPositionZ);
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.scale = Ogre::Vector3(1,1,1);
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.orientation = Ogre::Quaternion(1,0,0,0);
		tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.autotracktarget = "None";

		///////////////////////

		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.queueID=Ogre::RENDER_QUEUE_4;

		///////////////////////

		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.defaultheight = 1;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.defaultwidth = 1;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.pointrendering = false;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.renderdistance = 0;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.sorting = false;

		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.billboardtype=billboardType;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.billboardorigin=Ogre::BBO_CENTER;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.billboardrotation=billboardRotation;

		///////////////////////

		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters.resize(1);

		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].colour=ColourValue::White;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].position=Ogre::Vector3(0,0,0);
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].rotation=0;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].texcoordindex=0;
		tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].texrect=Ogre::Vector4(0,0,1,1);

		///////////////////////

		for (int i=0; i<numClouds; i++)
		{
			double positionX, positionY, positionZ, distance, randomOffset;

			positionY = centerPositionY + 
				Utils::Random::getInstance()->getRandomDouble(-generationRadiumY, generationRadiumY);
			randomOffset = Utils::Random::getInstance()->getRandomDouble(-sizeRandomOffset, sizeRandomOffset);

			numIteration = 0;
			do 
			{
				numIteration++;

				positionX = centerPositionX + 
					Utils::Random::getInstance()->getRandomDouble(-generationRadiumXZMAX, generationRadiumXZMAX);
				positionZ = centerPositionZ + 
					Utils::Random::getInstance()->getRandomDouble(-generationRadiumXZMAX, generationRadiumXZMAX);

				distance = Ogre::Math::Sqrt(Ogre::Math::Sqr(positionX) + Ogre::Math::Sqr(positionZ));

			} while (distance < generationRadiumXZMIN && numIteration < maxIterations);

			tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.position.x = positionX;
			tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.position.y = positionY;
			tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.position.z = positionZ;

			tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.tRenderComponentBillboardParameters[0].dimensions=
				Ogre::Vector2(width+randomOffset, height+randomOffset);

			///////////////////

			tGameObjectBillboardSetParameters.tLogicComponentParameters.defaultState = DREAMS;
			tGameObjectBillboardSetParameters.tLogicComponentParameters.existsInDreams = true;
			tGameObjectBillboardSetParameters.tLogicComponentParameters.existsInNightmares = true;

			//copy parameters for nightmares entity
		    tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters=tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters;

			//set materials
			tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters.material = dreamsClouds[i%numTypeClouds];
			tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters.material = nightmaresClouds[i%numTypeClouds];

			tGameObjectBillboardSetParameters.dreamsName = dreamsName + Ogre::StringConverter::toString(Ogre::Real(i));
			tGameObjectBillboardSetParameters.nightmaresName = nightmaresName + Ogre::StringConverter::toString(Ogre::Real(i));
			tGameObjectBillboardSetParameters.name = name + Ogre::StringConverter::toString(Ogre::Real(i));

			try 
			{
				mGameWorldManager->addGameObjectBillboardSet(mGameObjectFactory->createGameObjectBillboardSet(
					tGameObjectBillboardSetParameters,mGameWorldManager));

				Logger::getInstance()->log("[LevelLoader] CREATING BILLBOARD CLOUD " + tGameObjectBillboardSetParameters.name + " in " + 
					Ogre::StringConverter::toString(tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters.position));
			} 
			catch( std::string error )
			{
				Logger::getInstance()->log("ERROR! [LevelLoader] Error processing BILLBOARD CLOUD " + tGameObjectBillboardSetParameters.name + ": " + error);
			}
		}
	} 
	else 
	{
		Logger::getInstance()->log("ERROR! [LevelLoader] Error processing BILLBOARD CLOUD CFG FILE");
	}
}

void LevelLoader::processGameObjectFractalClouds()
{
	std::vector<Ogre::Vector3> cloudsPositions;
	Ogre::Vector3 cloudPosition;
	int maxIterations = 10;
	int numIteration = 0;
	bool cloudFoundSoClose = false;

	Configuration config;
	std::string value;

	if (config.loadFromFile(FRACTAL_CLOUDS_CFG))
	{
		std::string dreamsName = "fractal_cloud_d#";
		std::string nightmaresName = "fractal_cloud_n#";
		std::string name = "fractal_cloud#";

		config.getOption("NUM_CLOUDS", value); 
		double numClouds = atoi(value.c_str());

		config.getOption("GENERATION_RADIO_X", value); 
		double generationRadiumX = atof(value.c_str());

		config.getOption("GENERATION_RADIO_Y", value); 
		double generationRadiumY = atof(value.c_str());

		config.getOption("GENERATION_RADIO_Z", value); 
		double generationRadiumZ = atof(value.c_str());

		config.getOption("CENTER_POSITION_X", value); 
		double centerPositionX = atoi(value.c_str());

		config.getOption("CENTER_POSITION_Y", value); 
		double centerPositionY = atoi(value.c_str());

		config.getOption("CENTER_POSITION_Z", value); 
		double centerPositionZ = atoi(value.c_str());

		config.getOption("MIN_DISTANCE_TO_ANOTHER", value); 
		double minDistanceToAnother = atoi(value.c_str());

		///////////////////////

		OUAN::TGameObjectCloudParameters tGameObjectCloudParameters;

		tGameObjectCloudParameters.tLogicComponentParameters.defaultState = DREAMS;
		tGameObjectCloudParameters.tLogicComponentParameters.existsInDreams = true;
		tGameObjectCloudParameters.tLogicComponentParameters.existsInNightmares = true;
		tGameObjectCloudParameters.tLogicComponentParameters.scriptFilename = "";
		tGameObjectCloudParameters.tLogicComponentParameters.scriptFunction = "";

		tGameObjectCloudParameters.tRenderComponentPositionalParameters.parentSceneNodeName = "SceneManager";
		tGameObjectCloudParameters.tRenderComponentPositionalParameters.position = Ogre::Vector3(centerPositionX, centerPositionY, centerPositionZ);
		tGameObjectCloudParameters.tRenderComponentPositionalParameters.scale = Ogre::Vector3(1,1,1);
		tGameObjectCloudParameters.tRenderComponentPositionalParameters.orientation = Ogre::Quaternion(1,0,0,0);
		tGameObjectCloudParameters.tRenderComponentPositionalParameters.autotracktarget = "None";

		///////////////////////

		config.getOption("DREAMS_TEXTURE_3D", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.texture3D = value;

		config.getOption("DREAMS_JULIA_GLOBAL_REAL", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.juliaGlobalReal = atof(value.c_str());

		config.getOption("DREAMS_JULIA_GLOBAL_IMAG", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.juliaGlobalImag = atof(value.c_str());

		config.getOption("DREAMS_JULIA_GLOBAL_THETA", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.juliaGlobalTheta = atof(value.c_str());

		config.getOption("DREAMS_V_SCALE", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.vScale = atof(value.c_str());

		config.getOption("DREAMS_V_CUT", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.vCut = atof(value.c_str());

		config.getOption("DREAMS_V_SLICES", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.vSlices = atof(value.c_str());

		config.getOption("DREAMS_V_SIZE", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.vSize = atof(value.c_str());

		config.getOption("DREAMS_OFFSET_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetX = atof(value.c_str());

		config.getOption("DREAMS_OFFSET_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetY = atof(value.c_str());

		config.getOption("DREAMS_OFFSET_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetZ = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_INITIAL_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesInitialX = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_INITIAL_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesInitialY = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_INITIAL_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesInitialZ = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_PER_SECOND_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesPerSecondX = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_PER_SECOND_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesPerSecondY = atof(value.c_str());

		config.getOption("DREAMS_ROTATION_DEGREES_PER_SECOND_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.rotationDegreesPerSecondZ = atof(value.c_str());

		config.getOption("DREAMS_INIT_COLOR_R", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.initColorR = atof(value.c_str());

		config.getOption("DREAMS_INIT_COLOR_G", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.initColorG = atof(value.c_str());

		config.getOption("DREAMS_INIT_COLOR_B", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.initColorB = atof(value.c_str());

		config.getOption("DREAMS_END_COLOR_R", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.endColorR = atof(value.c_str());

		config.getOption("DREAMS_END_COLOR_G", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.endColorG = atof(value.c_str());

		config.getOption("DREAMS_END_COLOR_B", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.endColorB = atof(value.c_str());

		config.getOption("DREAMS_SEPARATION_PROPORTION", value); 
		tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation = 
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.vSize / atof(value.c_str());

		///////////////////////

		config.getOption("NIGHTMARES_TEXTURE_3D", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.texture3D = value;

		config.getOption("NIGHTMARES_JULIA_GLOBAL_REAL", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.juliaGlobalReal = atof(value.c_str());

		config.getOption("NIGHTMARES_JULIA_GLOBAL_IMAG", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.juliaGlobalImag = atof(value.c_str());

		config.getOption("NIGHTMARES_JULIA_GLOBAL_THETA", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.juliaGlobalTheta = atof(value.c_str());

		config.getOption("NIGHTMARES_V_SCALE", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.vScale = atof(value.c_str());

		config.getOption("NIGHTMARES_V_CUT", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.vCut = atof(value.c_str());

		config.getOption("NIGHTMARES_V_SLICES", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.vSlices = atof(value.c_str());

		config.getOption("NIGHTMARES_V_SIZE", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.vSize = atof(value.c_str());

		config.getOption("NIGHTMARES_OFFSET_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetX = atof(value.c_str());

		config.getOption("NIGHTMARES_OFFSET_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetY = atof(value.c_str());

		config.getOption("NIGHTMARES_OFFSET_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetZ = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_INITIAL_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesInitialX = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_INITIAL_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesInitialY = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_INITIAL_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesInitialZ = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_PER_SECOND_X", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesPerSecondX = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_PER_SECOND_Y", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesPerSecondY = atof(value.c_str());

		config.getOption("NIGHTMARES_ROTATION_DEGREES_PER_SECOND_Z", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.rotationDegreesPerSecondZ = atof(value.c_str());

		config.getOption("NIGHTMARES_INIT_COLOR_R", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.initColorR = atof(value.c_str());

		config.getOption("NIGHTMARES_INIT_COLOR_G", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.initColorG = atof(value.c_str());

		config.getOption("NIGHTMARES_INIT_COLOR_B", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.initColorB = atof(value.c_str());

		config.getOption("NIGHTMARES_END_COLOR_R", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.endColorR = atof(value.c_str());

		config.getOption("NIGHTMARES_END_COLOR_G", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.endColorG = atof(value.c_str());

		config.getOption("NIGHTMARES_END_COLOR_B", value); 
		tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.endColorB = atof(value.c_str());

		config.getOption("NIGHTMARES_SEPARATION_PROPORTION", value); 
		tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation = 
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.vSize / atof(value.c_str());

		///////////////////////

		for (int i=0; i<numClouds; i++)
		{
			tGameObjectCloudParameters.dreamsName = dreamsName + Ogre::StringConverter::toString(Ogre::Real(i));
			tGameObjectCloudParameters.nightmaresName = nightmaresName + Ogre::StringConverter::toString(Ogre::Real(i));
			tGameObjectCloudParameters.name = name + Ogre::StringConverter::toString(Ogre::Real(i));

			numIteration = 0;

			do 
			{
				numIteration++;
				cloudFoundSoClose = false;

				cloudPosition.x = centerPositionX + Utils::Random::getInstance()->getRandomDouble(-generationRadiumX, generationRadiumX);
				cloudPosition.y = centerPositionY + Utils::Random::getInstance()->getRandomDouble(-generationRadiumY, generationRadiumY);
				cloudPosition.z = centerPositionZ + Utils::Random::getInstance()->getRandomDouble(-generationRadiumZ, generationRadiumZ);
							
				for (unsigned int i=0; i<cloudsPositions.size() && !cloudFoundSoClose; i++){
					if (cloudsPositions[i].distance(cloudPosition) < minDistanceToAnother)
					{
						cloudFoundSoClose = true;
					}
				}

			} while (cloudFoundSoClose && numIteration < maxIterations);

			cloudsPositions.push_back(cloudPosition);

			tGameObjectCloudParameters.tRenderComponentPositionalParameters.position.x = cloudPosition.x;
			tGameObjectCloudParameters.tRenderComponentPositionalParameters.position.y = cloudPosition.y;
			tGameObjectCloudParameters.tRenderComponentPositionalParameters.position.z = cloudPosition.z;

			try 
			{
				mGameWorldManager->addGameObjectCloud(mGameObjectFactory->createGameObjectCloud(
					tGameObjectCloudParameters,mGameWorldManager));

				Logger::getInstance()->log("[LevelLoader] CREATING FRACTAL CLOUD " + tGameObjectCloudParameters.name + " in " + 
					Ogre::StringConverter::toString(tGameObjectCloudParameters.tRenderComponentPositionalParameters.position));
			} 
			catch( std::string error )
			{
				Logger::getInstance()->log("ERROR! [LevelLoader] Error processing FRACTAL CLOUD " + tGameObjectCloudParameters.name + ": " + error);
			}
		}
	}
	else
	{
		Logger::getInstance()->log("ERROR! [LevelLoader] Error processing FRACTAL CLOUD CFG FILE");
	}
}

double LevelLoader::processCustomAttributeMaxRenderRadium(XMLGameObject* gameObject)
{
	double mMaxRenderRadium;

	if (gameObject->XMLNodeCustomProperties)
	{
		try
		{
			mMaxRenderRadium = getPropertyReal(gameObject->XMLNodeCustomProperties, "CustomAttribute::maxRenderRadium");
		}
		catch(std::string error)
		{
			 mMaxRenderRadium = mGameWorldManager->DEFAULT_MAX_RENDER_RADIO;
		}
	}
	return mMaxRenderRadium;
}

double LevelLoader::processCustomAttributeMaxUpdateRadium(XMLGameObject* gameObject)
{
	double mMaxUpdateRadium;

	if (gameObject->XMLNodeCustomProperties)
	{
		try
		{
			mMaxUpdateRadium = getPropertyReal(gameObject->XMLNodeCustomProperties, "CustomAttribute::maxUpdateRadium");
		}
		catch(std::string error)
		{
			 mMaxUpdateRadium = mGameWorldManager->DEFAULT_MAX_UPDATE_RADIO;
		}
	}
	return mMaxUpdateRadium;
}
double LevelLoader::processCustomAttributeSpawnProbability(XMLGameObject* gameObject)
{
	double spawnProbability=0.0;
	if (gameObject->getMainXMLNode())
	{
		try
		{
			spawnProbability= getPropertyReal(gameObject->getMainXMLNode(), "SpawnProbability");
		}
		catch (std::string error)
		{
			
		}
	}
	return spawnProbability;
}
std::string LevelLoader::processCustomAttributeParentNest(XMLGameObject* gameObject)
{
	std::string parentNest="";
	if (gameObject->getMainXMLNode())
	{
		try
		{
			parentNest=getPropertyString(gameObject->getMainXMLNode(),"ParentNest");
		}
		catch (std::string error)
		{
		}
	}
	return parentNest;
}

