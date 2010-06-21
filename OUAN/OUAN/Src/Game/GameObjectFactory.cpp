#include "OUAN_Precompiled.h"

#include "GameObjectFactory.h"

#include "GameWorldManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectBee_Butterfly.h"
#include "GameObject/GameObjectBillboardSet.h"
#include "GameObject/GameObjectBush.h"
#include "GameObject/GameObjectCarnivorousPlant.h"
#include "GameObject/GameObjectClockPiece.h"
#include "GameObject/GameObjectCloud.h"
#include "GameObject/GameObjectCryKing.h"
#include "GameObject/GameObjectDiamond.h"
#include "GameObject/GameObjectDiamondTree.h"
#include "GameObject/GameObjectDoor.h"
#include "GameObject/GameObjectDragon.h"
#include "GameObject/GameObjectEye.h"
#include "GameObject/GameObjectFlashLight.h"
#include "GameObject/GameObjectHeart.h"
#include "GameObject/GameObjectItem1UP.h"
#include "GameObject/GameObjectItemMaxHP.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectMagicClock.h"
#include "GameObject/GameObjectNightGoblin.h"
#include "GameObject/GameObjectOny.h"
#include "GameObject/GameObjectParticleSystem.h"
#include "GameObject/GameObjectPillow.h"
#include "GameObject/GameObjectPlane.h"
#include "GameObject/GameObjectPlataform.h"
#include "GameObject/GameObjectPortal.h"
#include "GameObject/GameObjectProvisionalEntity.h"
#include "GameObject/GameObjectScaredPlant.h"
#include "GameObject/GameObjectScene.h"
#include "GameObject/GameObjectScepter.h"
#include "GameObject/GameObjectSkyBody.h"
#include "GameObject/GameObjectSound.h"
#include "GameObject/GameObjectSnakeCreeper.h"
#include "GameObject/GameObjectStoryBook.h"
#include "GameObject/GameObjectTentetieso.h"
#include "GameObject/GameObjectTerrainConvex.h"
#include "GameObject/GameObjectTerrainTriangle.h"
#include "GameObject/GameObjectTree.h"
#include "GameObject/GameObjectTriggerBox.h"
#include "GameObject/GameObjectTriggerCapsule.h"
#include "GameObject/GameObjectTripollito.h"
#include "GameObject/GameObjectTripolloDreams.h"
#include "GameObject/GameObjectViewport.h"
#include "GameObject/GameObjectWoodBox.h"
#include "GameObject/GameObjectWater.h"
#include "GameObject/GameObjectTreeComplex.h"
#include "GameObject/GameObjectTower.h"
#include "GameObject/GameObjectFog.h"
#include "GameObject/GameObjectTriggerCamera.h"

#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/ParticleManager/ParticleTemplates.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"

#include "../Audio/AudioComponent/AudioComponent.h"
#include "../Audio/AudioSubsystem.h"

#include "../Component/ComponentFactory.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../RayCasting/RayCasting.h"

using namespace OUAN;

GameObjectFactory::GameObjectFactory()
{
	mComponentFactory = ComponentFactoryPtr(new ComponentFactory());
}

GameObjectFactory::~GameObjectFactory()
{
	if (mComponentFactory.get())
	{
		mComponentFactory.reset();
	}
}

void GameObjectFactory::init(ApplicationPtr app)
{
	if (mComponentFactory.get())
	{
		mComponentFactory->init(app);
	}
}

GameObjectBee_ButterflyPtr GameObjectFactory::createGameObjectBee_Butterfly(TGameObjectBee_ButterflyParameters tGameObjectBee_ButterflyParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBee_ButterflyPtr pGameObjectBee_Butterfly;

	//Create GameObject
	pGameObjectBee_Butterfly = GameObjectBee_ButterflyPtr(new GameObjectBee_Butterfly(tGameObjectBee_ButterflyParameters.name));
	pGameObjectBee_Butterfly->setMaxUpdateRadio(tGameObjectBee_ButterflyParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectBee_Butterfly->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectBee_Butterfly,
		tGameObjectBee_ButterflyParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectBee_Butterfly->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBee_Butterfly->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBee_Butterfly->getRenderComponentPositional()));

	if(pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectBee_Butterfly->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectBee_ButterflyParameters.dreamsName,
			pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityDreamsParameters));

		//Create PhysicsComponent Dreams
		pGameObjectBee_Butterfly->setPhysicsComponentCharacterDreams(
			mComponentFactory->createPhysicsComponentCharacter(
			pGameObjectBee_Butterfly, 
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterDreamsParameters, 
			pGameObjectBee_Butterfly->getRenderComponentPositional()));
	}
	if(pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectBee_Butterfly->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectBee_ButterflyParameters.nightmaresName,
			pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent Nightmares
		pGameObjectBee_Butterfly->setPhysicsComponentCharacterNightmares(
			mComponentFactory->createPhysicsComponentCharacter(
			pGameObjectBee_Butterfly, 
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterNightmaresParameters, 
			pGameObjectBee_Butterfly->getRenderComponentPositional()));
	}

	//Add reference to this
	pGameObjectBee_Butterfly->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectBee_Butterfly(pGameObjectBee_Butterfly);
	return pGameObjectBee_Butterfly;
}

GameObjectBillboardSetPtr GameObjectFactory::createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBillboardSetPtr pGameObjectBillboardSet;
	
	//Create GameObject
	pGameObjectBillboardSet = GameObjectBillboardSetPtr(new GameObjectBillboardSet(tGameObjectBillboardSetParameters.name));
	pGameObjectBillboardSet->setMaxUpdateRadio(tGameObjectBillboardSetParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectBillboardSet->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectBillboardSet,
		tGameObjectBillboardSetParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectBillboardSet->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBillboardSet->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBillboardSet->getRenderComponentPositional()));

	if(pGameObjectBillboardSet->getLogicComponent()->existsInDreams() && pGameObjectBillboardSet->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentBillboardSetDreams
		pGameObjectBillboardSet->setRenderComponentBillboardSetDreams(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.dreamsName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters));
		//Create RenderComponentBillboardSetNightmares
		pGameObjectBillboardSet->setRenderComponentBillboardSetNightmares(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.nightmaresName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters));
	}
	else if(pGameObjectBillboardSet->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentBillboardSetDreams
		pGameObjectBillboardSet->setRenderComponentBillboardSetDreams(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.dreamsName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters));
	}
	else if(pGameObjectBillboardSet->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentBillboardSetNightmares
		pGameObjectBillboardSet->setRenderComponentBillboardSetNightmares(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.nightmaresName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters));
	}
	// Add a reference to this
	pGameObjectBillboardSet->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectBillboardSet(pGameObjectBillboardSet);
	return pGameObjectBillboardSet;
}

GameObjectBushPtr GameObjectFactory::createGameObjectBush(TGameObjectBushParameters tGameObjectBushParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBushPtr pGameObjectBush;

	//Create GameObject
	pGameObjectBush = GameObjectBushPtr(new GameObjectBush(tGameObjectBushParameters.name));
	pGameObjectBush->setMaxUpdateRadio(tGameObjectBushParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectBush->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectBush,
		tGameObjectBushParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectBush->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBush,tGameObjectBushParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBush->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBush->getRenderComponentPositional()));

	if(pGameObjectBush->getLogicComponent()->existsInDreams() && pGameObjectBush->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectBush->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectBushParameters.dreamsName,
			pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntity Nightmares
		pGameObjectBush->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectBushParameters.nightmaresName,
			pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityNightmaresParameters));

	}
	else if(pGameObjectBush->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectBush->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectBushParameters.dreamsName,
			pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityDreamsParameters));
	}
	else if(pGameObjectBush->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectBush->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectBushParameters.nightmaresName,
			pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Add reference to this
	pGameObjectBush->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectBush(pGameObjectBush);
	return pGameObjectBush;
}


GameObjectCarnivorousPlantPtr GameObjectFactory::createGameObjectCarnivorousPlant(
	TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant;

	//Create GameObject
	pGameObjectCarnivorousPlant = GameObjectCarnivorousPlantPtr(new GameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters.name));
	pGameObjectCarnivorousPlant->setMaxUpdateRadio(tGameObjectCarnivorousPlantParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectCarnivorousPlant->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectCarnivorousPlant,
		tGameObjectCarnivorousPlantParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectCarnivorousPlant->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectCarnivorousPlant->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectCarnivorousPlant->getRenderComponentPositional()));

	if(pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectCarnivorousPlant->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectCarnivorousPlantParameters.dreamsName,
			pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectCarnivorousPlant->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectCarnivorousPlantParameters.nightmaresName,
			pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectCarnivorousPlant->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectCarnivorousPlant, 
		tGameObjectCarnivorousPlantParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectCarnivorousPlant->getRenderComponentPositional()));


	//Add reference to this
	pGameObjectCarnivorousPlant->setGameWorldManager(gameWorldMgr);

	return pGameObjectCarnivorousPlant;
}

GameObjectClockPiecePtr GameObjectFactory::createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectClockPiecePtr pGameObjectClockPiece;

	//Create GameObject
	pGameObjectClockPiece = GameObjectClockPiecePtr(new GameObjectClockPiece(tGameObjectClockPieceParameters.name));
	pGameObjectClockPiece->setMaxUpdateRadio(tGameObjectClockPieceParameters.maxUpdateRadio);

	//Create LogicComponentWorldExistance
	pGameObjectClockPiece->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectClockPiece,
		tGameObjectClockPieceParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectClockPiece->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectClockPiece,tGameObjectClockPieceParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectClockPiece->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectClockPiece->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectClockPiece->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectClockPieceParameters.name,
		pGameObjectClockPiece,tGameObjectClockPieceParameters.tRenderComponentEntityParameters));

	//Create RenderComponentGlowDreams
	pGameObjectClockPiece->setRenderComponentGlow(
		mComponentFactory->createRenderComponentGlow(
			pGameObjectClockPiece,
			tGameObjectClockPieceParameters.tRenderComponentGlowParameters,
			pGameObjectClockPiece->getRenderComponentPositional(),
			pGameObjectClockPiece->getRenderComponentEntity()));

	//Create PhysicsComponent
	pGameObjectClockPiece->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectClockPiece, 
		tGameObjectClockPieceParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectClockPiece->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectClockPiece->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectClockPiece(pGameObjectClockPiece);

	return pGameObjectClockPiece;
}

GameObjectCloudPtr GameObjectFactory::createGameObjectCloud(TGameObjectCloudParameters tGameObjectCloudParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCloudPtr pGameObjectCloud;
	
	//Create GameObject
	pGameObjectCloud = GameObjectCloudPtr(new GameObjectCloud(tGameObjectCloudParameters.name));
	pGameObjectCloud->setMaxUpdateRadio(tGameObjectCloudParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectCloud->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectCloud,
		tGameObjectCloudParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectCloud->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectCloud,tGameObjectCloudParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectCloud->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectCloud->getRenderComponentPositional()));
	
	//Create set of RenderComponentFractalVolume
	Ogre::Vector3 pOffsets[] = {
		Ogre::Vector3(0, 0, -tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation),
		Ogre::Vector3(tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation, 0, 0),
		Ogre::Vector3(0, 0, tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation),
		Ogre::Vector3(-tGameObjectCloudParameters.tFractalVolumeSetInnerSeparation, 0, 0)};

	if(pGameObjectCloud->getLogicComponent()->existsInDreams())
	{
		RenderComponentFractalVolumePtr* pRenderComponentFractalVolumeSet = 
			(RenderComponentFractalVolumePtr*)malloc(sizeof(RenderComponentFractalVolumePtr) * CLOUD_FRACTAL_VOLUME_SET_SIZE);

		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetX = pOffsets[i].x;
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetY = pOffsets[i].y;
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters.offsetZ = pOffsets[i].z;

			pGameObjectCloud->setRenderComponentFractalVolumeDreams(
				mComponentFactory->createRenderComponentFractalVolume(
					pGameObjectCloud,
					tGameObjectCloudParameters.tRenderComponentFractalVolumeSetDreamsParameters,
					pGameObjectCloud->getRenderComponentPositional()),
				i);
		}		
	}

	if(pGameObjectCloud->getLogicComponent()->existsInNightmares())
	{
		RenderComponentFractalVolumePtr* pRenderComponentFractalVolumeSet = 
			(RenderComponentFractalVolumePtr*)malloc(sizeof(RenderComponentFractalVolumePtr) * CLOUD_FRACTAL_VOLUME_SET_SIZE);

		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetX = pOffsets[i].x;
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetY = pOffsets[i].y;
			tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters.offsetZ = pOffsets[i].z;

			pGameObjectCloud->setRenderComponentFractalVolumeNightmares(
				mComponentFactory->createRenderComponentFractalVolume(
					pGameObjectCloud,
					tGameObjectCloudParameters.tRenderComponentFractalVolumeSetNightmaresParameters,
					pGameObjectCloud->getRenderComponentPositional()),
				i);
		}
	}

	//Add reference to this
	pGameObjectCloud->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectCloud(pGameObjectCloud);
	
	return pGameObjectCloud;
}

GameObjectCryKingPtr GameObjectFactory::createGameObjectCryKing(TGameObjectCryKingParameters tGameObjectCryKingParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCryKingPtr pGameObjectCryKing;

	//Create GameObject
	pGameObjectCryKing = GameObjectCryKingPtr(new GameObjectCryKing(tGameObjectCryKingParameters.name));
	pGameObjectCryKing->setMaxUpdateRadio(tGameObjectCryKingParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectCryKing->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectCryKing,
		tGameObjectCryKingParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectCryKing->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectCryKing->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectCryKing->getRenderComponentPositional()));

	if(pGameObjectCryKing->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectCryKing->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectCryKingParameters.dreamsName,
			pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectCryKing->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectCryKing->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectCryKingParameters.nightmaresName,
			pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectCryKing->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectCryKing, 
		tGameObjectCryKingParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectCryKing->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectCryKing->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectCryKing(pGameObjectCryKing);

	return pGameObjectCryKing;
}

GameObjectDiamondPtr GameObjectFactory::createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDiamondPtr pGameObjectDiamond;

	//Create GameObject
	pGameObjectDiamond = GameObjectDiamondPtr(new GameObjectDiamond(tGameObjectDiamondParameters.name));
	pGameObjectDiamond->setMaxUpdateRadio(tGameObjectDiamondParameters.maxUpdateRadio);

	//Create LogicComponentWorldExistance
	pGameObjectDiamond->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectDiamond,
		tGameObjectDiamondParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectDiamond->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectDiamond,tGameObjectDiamondParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectDiamond->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectDiamond->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectDiamond->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectDiamondParameters.name,
		pGameObjectDiamond,tGameObjectDiamondParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectDiamond->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectDiamond, 
		tGameObjectDiamondParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectDiamond->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectDiamond->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectDiamond, 
		tGameObjectDiamondParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectDiamond->getRenderComponentPositional()));

	//pGameObjectDiamond->getPhysicsComponentSimpleBox()->destroy();

	if (!tGameObjectDiamondParameters.tParentDiamondTree.empty())
	{
		pGameObjectDiamond->setParentDiamondTreeName(tGameObjectDiamondParameters.tParentDiamondTree);
		gameWorldMgr->addDiamondTreeLink(pGameObjectDiamond->getName(),
			tGameObjectDiamondParameters.tParentDiamondTree);
	}	

	//Add reference to this
	pGameObjectDiamond->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectDiamond(pGameObjectDiamond);
	return pGameObjectDiamond;
}

GameObjectDiamondTreePtr GameObjectFactory::createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDiamondTreePtr pGameObjectDiamondTree;

	//Create GameObject
	pGameObjectDiamondTree = GameObjectDiamondTreePtr(new GameObjectDiamondTree(tGameObjectDiamondTreeParameters.name));
	pGameObjectDiamondTree->setMaxUpdateRadio(tGameObjectDiamondTreeParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectDiamondTree->setLogicComponent(
		mComponentFactory->createLogicComponentProp(
		pGameObjectDiamondTree,
		tGameObjectDiamondTreeParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectDiamondTree->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectDiamondTree->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectDiamondTree->getRenderComponentPositional()));

	if(pGameObjectDiamondTree->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectDiamondTree->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectDiamondTreeParameters.dreamsName,
			pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectDiamondTree->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectDiamondTree->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectDiamondTreeParameters.nightmaresName,
			pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	//pGameObjectDiamondTree->setPhysicsComponentSimpleBox(
	//	mComponentFactory->createPhysicsComponentSimpleBox(
	//	pGameObjectDiamondTree, 
	//	tGameObjectDiamondTreeParameters.tPhysicsComponentSimpleBoxParameters, 
	//	pGameObjectDiamondTree->getRenderComponentPositional()));

	//pGameObjectDiamondTree->setPhysicsComponentVolumeBox(
	//	mComponentFactory->createPhysicsComponentVolumeBox(
	//	pGameObjectDiamondTree, 
	//	tGameObjectDiamondTreeParameters.tPhysicsComponentVolumeBoxParameters, 
	//	pGameObjectDiamondTree->getRenderComponentPositional()));
						
	//Create PhysicsComponent
	pGameObjectDiamondTree->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectDiamondTree, 
		tGameObjectDiamondTreeParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectDiamondTree->getRenderComponentPositional()));

	pGameObjectDiamondTree->getPhysicsComponentCharacter()->setCyclicCharacter(true);

	//Add reference to this
	pGameObjectDiamondTree->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectDiamondTree(pGameObjectDiamondTree);
	return pGameObjectDiamondTree;
}

GameObjectDoorPtr GameObjectFactory::createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDoorPtr pGameObjectDoor;

	//Create GameObject
	pGameObjectDoor = GameObjectDoorPtr(new GameObjectDoor(tGameObjectDoorParameters.name));
	pGameObjectDoor->setMaxUpdateRadio(tGameObjectDoorParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectDoor->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectDoor,
		tGameObjectDoorParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectDoor->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectDoor->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectDoor->getRenderComponentPositional()));

	if(pGameObjectDoor->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectDoor->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectDoorParameters.dreamsName,
			pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectDoor->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectDoor->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectDoorParameters.nightmaresName,
			pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectDoor->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectDoor, 
		tGameObjectDoorParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectDoor->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDoor->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectDoor(pGameObjectDoor);

	return pGameObjectDoor;
}

GameObjectDragonPtr GameObjectFactory::createGameObjectDragon(TGameObjectDragonParameters tGameObjectDragonParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDragonPtr pGameObjectDragon;

	//Create GameObject
	pGameObjectDragon = GameObjectDragonPtr(new GameObjectDragon(tGameObjectDragonParameters.name));
	pGameObjectDragon->setMaxUpdateRadio(tGameObjectDragonParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectDragon->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectDragon,
		tGameObjectDragonParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectDragon->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectDragon->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectDragon->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectDragon->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectDragonParameters.dreamsName,
		pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectDragon->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectDragonParameters.nightmaresName,
		pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectDragon->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectDragon,
		tGameObjectDragonParameters.tPhysicsComponentCharacterParameters,
		pGameObjectDragon->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDragon->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectDragon(pGameObjectDragon);
	return pGameObjectDragon;
}


GameObjectEyePtr GameObjectFactory::createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectEyePtr pGameObjectEye;

	//Create GameObject
	pGameObjectEye = GameObjectEyePtr(new GameObjectEye(tGameObjectEyeParameters.name));
	pGameObjectEye->setMaxUpdateRadio(tGameObjectEyeParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectEye->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectEye,
		tGameObjectEyeParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectEye->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectEye,tGameObjectEyeParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectEye->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectEye->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectEye->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectEyeParameters.name,
		pGameObjectEye,tGameObjectEyeParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectEye->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectEye,
		tGameObjectEyeParameters.tPhysicsComponentCharacterParameters,
		pGameObjectEye->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectEye->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectEye(pGameObjectEye);

	return pGameObjectEye;
}

GameObjectFogPtr GameObjectFactory::createGameObjectFog(TGameObjectFogParameters tGameObjectFogParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectFogPtr pGameObjectFog;

	//Create GameObject
	pGameObjectFog = GameObjectFogPtr(new GameObjectFog(tGameObjectFogParameters.name));
	pGameObjectFog->setMaxUpdateRadio(tGameObjectFogParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectFog->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectFog,
		tGameObjectFogParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectFog->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectFog,tGameObjectFogParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectFog->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectFog->getRenderComponentPositional()));

	if(pGameObjectFog->getLogicComponent()->existsInDreams() && pGameObjectFog->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectFog->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.dreamsName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntity Nightmares
		pGameObjectFog->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.nightmaresName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityNightmaresParameters));

	}
	else if(pGameObjectFog->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectFog->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.dreamsName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityDreamsParameters));
	}
	else if(pGameObjectFog->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectFog->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.nightmaresName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Add reference to this
	pGameObjectFog->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectFog(pGameObjectFog);
	return pGameObjectFog;
}

GameObjectFlashLightPtr GameObjectFactory::createGameObjectFlashLight(TGameObjectFlashLightParameters tGameObjectFlashLightParameters, 
	GameWorldManagerPtr gameWorldMgr,CameraManagerPtr cameraMgr, RayCastingPtr raycasting, RenderSubsystemPtr renderSubsystem)
{
	GameObjectFlashLightPtr pGameObjectFlashLight;

	//Create GameObject
	pGameObjectFlashLight = GameObjectFlashLightPtr(new GameObjectFlashLight(tGameObjectFlashLightParameters.name,gameWorldMgr,
		cameraMgr,raycasting,renderSubsystem));
	pGameObjectFlashLight->setMaxUpdateRadio(tGameObjectFlashLightParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectFlashLight->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectFlashLight,
		tGameObjectFlashLightParameters.tLogicComponentParameters));

	pGameObjectFlashLight->setAttackComponent(
		mComponentFactory->createAttackComponent(
		pGameObjectFlashLight,
		tGameObjectFlashLightParameters.attackComponentParameters
		));

	//Create RenderComponentPositional
	pGameObjectFlashLight->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectFlashLight,tGameObjectFlashLightParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectFlashLight->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectFlashLight->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectFlashLight->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectFlashLightParameters.name,
		pGameObjectFlashLight,tGameObjectFlashLightParameters.tRenderComponentEntityParameters));
	pGameObjectFlashLight->getRenderComponentEntity()->setVisible(false);

	////Create PhysicsComponent
	pGameObjectFlashLight->setPhysicsComponentVolumeConvex(
		mComponentFactory->createPhysicsComponentVolumeConvex(
		pGameObjectFlashLight, 
		tGameObjectFlashLightParameters.tPhysicsComponentVolumeConvexParameters, 
		pGameObjectFlashLight->getRenderComponentPositional()));

	//Create Flashlight's light

	//Create RenderComponentPositional for Light
	TRenderComponentPositionalParameters lightPositionalComponentParameters;
	lightPositionalComponentParameters.autotracktarget="None";
	lightPositionalComponentParameters.orientation=Quaternion(1,0,0,0);
	lightPositionalComponentParameters.parentSceneNodeName="SceneManager";
	lightPositionalComponentParameters.position=Vector3(0,0,0);
	lightPositionalComponentParameters.scale=Vector3(1,1,1);

	pGameObjectFlashLight->setLightPositionalComponent(mComponentFactory->createRenderComponentPositional(
		pGameObjectFlashLight,lightPositionalComponentParameters,tGameObjectFlashLightParameters.name+"#Light"));

	//Create RenderComponentLight
	TRenderComponentLightParameters tRenderComponentLightParameters;

	tRenderComponentLightParameters.attenuation=Vector4(200,0.15,0,0);
	tRenderComponentLightParameters.castshadows=false;
	tRenderComponentLightParameters.diffuse=Ogre::ColourValue(0.7,0,0,1);
	tRenderComponentLightParameters.direction=Vector3(0,0,1);
	tRenderComponentLightParameters.lightrange=Vector3(60,90,0.1);
	tRenderComponentLightParameters.lighttype=Ogre::Light::LT_SPOTLIGHT;
	tRenderComponentLightParameters.power=1;
	tRenderComponentLightParameters.specular=Ogre::ColourValue(1,0.2,0.2,1);

	pGameObjectFlashLight->setRenderComponentLight(
		mComponentFactory->createRenderComponentLight(tGameObjectFlashLightParameters.name+"#Light",
		pGameObjectFlashLight,tRenderComponentLightParameters));

	pGameObjectFlashLight->setLightConeBBS(
		mComponentFactory->createRenderComponentBillboardSet(
		tGameObjectFlashLightParameters.name+"#light",
		pGameObjectFlashLight,
		tGameObjectFlashLightParameters.lightConeBBSParams
		));
	pGameObjectFlashLight->getLightConeBBS()->setVisible(false);

	//Add reference to this
	pGameObjectFlashLight->setGameWorldManager(gameWorldMgr);
	pGameObjectFlashLight->hide();
	pGameObjectFlashLight->switchOff();

	//Add Object to GameWorldManager
	//addGameObjectFlashLight(pGameObjectFlashLight);
	return pGameObjectFlashLight;
}

GameObjectHeartPtr GameObjectFactory::createGameObjectHeart(TGameObjectHeartParameters tGameObjectHeartParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectHeartPtr pGameObjectHeart;

	//Create GameObject
	pGameObjectHeart = GameObjectHeartPtr(new GameObjectHeart(tGameObjectHeartParameters.name));
	pGameObjectHeart->setMaxUpdateRadio(tGameObjectHeartParameters.maxUpdateRadio);

	//Create LogicComponentWorldExistance
	pGameObjectHeart->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectHeart,
		tGameObjectHeartParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectHeart->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectHeart,tGameObjectHeartParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectHeart->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectHeart->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectHeart->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectHeartParameters.name,
		pGameObjectHeart,tGameObjectHeartParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectHeart->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectHeart, 
		tGameObjectHeartParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectHeart->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectHeart->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectHeart(pGameObjectHeart);

	return pGameObjectHeart;
}

GameObjectItem1UPPtr GameObjectFactory::createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectItem1UPPtr pGameObjectItem1UP;

	//Create GameObject
	pGameObjectItem1UP = GameObjectItem1UPPtr(new GameObjectItem1UP(tGameObjectItem1UPParameters.name));
	pGameObjectItem1UP->setMaxUpdateRadio(tGameObjectItem1UPParameters.maxUpdateRadio);

	//Create LogicComponentWorldExistance
	pGameObjectItem1UP->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectItem1UP,
		tGameObjectItem1UPParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectItem1UP->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectItem1UP->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectItem1UP->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectItem1UP->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectItem1UPParameters.name,
		pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectItem1UP->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectItem1UP, 
		tGameObjectItem1UPParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectItem1UP->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectItem1UP->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectItem1UP(pGameObjectItem1UP);
	return pGameObjectItem1UP;
}

GameObjectItemMaxHPPtr GameObjectFactory::createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectItemMaxHPPtr pGameObjectItemMaxHP;

	//Create GameObject
	pGameObjectItemMaxHP = GameObjectItemMaxHPPtr(new GameObjectItemMaxHP(tGameObjectItemMaxHPParameters.name));
	pGameObjectItemMaxHP->setMaxUpdateRadio(tGameObjectItemMaxHPParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectItemMaxHP->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectItemMaxHP,
		tGameObjectItemMaxHPParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectItemMaxHP->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectItemMaxHP->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectItemMaxHP->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectItemMaxHP->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectItemMaxHPParameters.name,
		pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectItemMaxHP->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectItemMaxHP, 
		tGameObjectItemMaxHPParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectItemMaxHP->getRenderComponentPositional()));

	//Create LogicComponent
	pGameObjectItemMaxHP->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectItemMaxHP,
		tGameObjectItemMaxHPParameters.tLogicComponentItemParameters));

	// Add a reference to this
	pGameObjectItemMaxHP->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectItemMaxHP(pGameObjectItemMaxHP);
	return pGameObjectItemMaxHP;
}

GameObjectLightPtr GameObjectFactory::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(tGameObjectLightParameters.name));
	pGameObjectLight->setMaxUpdateRadio(tGameObjectLightParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectLight->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectLight,
		tGameObjectLightParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectLight->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectLight,tGameObjectLightParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectLight->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectLight->getRenderComponentPositional()));

	//Create RenderComponentLight
	pGameObjectLight->setRenderComponentLight(mComponentFactory->createRenderComponentLight(
		tGameObjectLightParameters.name,pGameObjectLight,tGameObjectLightParameters.tRenderComponentLightParameters));

	// Add a reference to this
	pGameObjectLight->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectLight(pGameObjectLight);
	return pGameObjectLight;
}

GameObjectMagicClockPtr GameObjectFactory::createGameObjectMagicClock(TGameObjectMagicClockParameters tGameObjectMagicClockParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectMagicClockPtr pGameObjectMagicClock;

	//Create GameObject
	pGameObjectMagicClock = GameObjectMagicClockPtr(new GameObjectMagicClock(tGameObjectMagicClockParameters.name));
	pGameObjectMagicClock->setMaxUpdateRadio(tGameObjectMagicClockParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectMagicClock->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectMagicClock,
		tGameObjectMagicClockParameters.tLogicComponentParameters));

	//Add reference to this
	pGameObjectMagicClock->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectMagicClock(pGameObjectMagicClock);
	return pGameObjectMagicClock;
}

GameObjectNightGoblinPtr GameObjectFactory::createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectNightGoblinPtr pGameObjectNightGoblin;

	//Create GameObject
	pGameObjectNightGoblin = GameObjectNightGoblinPtr(new GameObjectNightGoblin(tGameObjectNightGoblinParameters.name));
	pGameObjectNightGoblin->setMaxUpdateRadio(tGameObjectNightGoblinParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectNightGoblin->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectNightGoblin,
		tGameObjectNightGoblinParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectNightGoblin->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectNightGoblin->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectNightGoblin->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectNightGoblin->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectNightGoblinParameters.dreamsName,
		pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectNightGoblin->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectNightGoblinParameters.nightmaresName,
		pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectNightGoblin->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectNightGoblin,
		tGameObjectNightGoblinParameters.tPhysicsComponentCharacterParameters,
		pGameObjectNightGoblin->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectNightGoblin->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectNightGoblin(pGameObjectNightGoblin);
	return pGameObjectNightGoblin;
}

GameObjectOnyPtr GameObjectFactory::createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters, 
	GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraMgr)
{
	GameObjectOnyPtr pGameObjectOny;

	//Create GameObject
	pGameObjectOny = GameObjectOnyPtr(new GameObjectOny(tGameObjectOnyParameters.name));
	pGameObjectOny->setMaxUpdateRadio(tGameObjectOnyParameters.maxUpdateRadio);

	//Create LogicComponentOny
	pGameObjectOny->setLogicComponentOny(
		mComponentFactory->createLogicComponentOny(
			pGameObjectOny,
			tGameObjectOnyParameters.tLogicComponentOnyParameters));

	//Create WeaponComponent
	pGameObjectOny->setWeaponComponent(
		mComponentFactory->createWeaponComponent(
			pGameObjectOny,
			tGameObjectOnyParameters.tWeaponComponentParameters));
	
	//Create RenderComponentPositional
	pGameObjectOny->setRenderComponentPositional(
		mComponentFactory->createRenderComponentPositional(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentPositionalParameters));

	//TODO ERASE THIS WHEN ONY IS PROPERLY SCALED
	pGameObjectOny->getRenderComponentPositional()->setScale(
		tGameObjectOnyParameters.tPhysicsComponentCharacterOnyParameters.scale_correction);

	//Create RenderComponentInitial
	pGameObjectOny->setRenderComponentInitial(
		mComponentFactory->createRenderComponentInitial(
			pGameObjectOny->getRenderComponentPositional()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->ONY_LAND_DREAMS;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID=Ogre::RENDER_QUEUE_MAIN;
	pGameObjectOny->setRenderComponentParticleSystemLandDreams(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectOny,
			tRenderComponentParticleSystemParameters,
			pGameObjectOny->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->ONY_LAND_NIGHTMARES;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID=Ogre::RENDER_QUEUE_MAIN;
	pGameObjectOny->setRenderComponentParticleSystemLandNightmares(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectOny,
		tRenderComponentParticleSystemParameters,
		pGameObjectOny->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectOny->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(
			tGameObjectOnyParameters.name,
			pGameObjectOny,
			tGameObjectOnyParameters.tRenderComponentEntityParameters));

	//Create RenderComponentQuadHalo
	pGameObjectOny->setRenderComponentQuadHalo(
		mComponentFactory->createRenderComponentQuadHalo(
			pGameObjectOny,
			tGameObjectOnyParameters.tRenderComponentQuadHaloParameters,
			pGameObjectOny->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectOny->setPhysicsComponentCharacterOny(
		mComponentFactory->createPhysicsComponentCharacterOny(
			pGameObjectOny,
			tGameObjectOnyParameters.tPhysicsComponentCharacterOnyParameters,
			pGameObjectOny->getRenderComponentPositional()));

	//TODO ERASE THIS WHEN PROPERLY DONE IN XSI
	pGameObjectOny->getPhysicsComponentCharacterOny()->setOffsetRenderPosition(
		tGameObjectOnyParameters.tPhysicsComponentCharacterOnyParameters.position_correction);

	pGameObjectOny->setAudioComponent(
		mComponentFactory->createAudioComponent(
			pGameObjectOny,
			tGameObjectOnyParameters.tAudioComponentParameters,
			gameWorldMgr->getParent()->getAudioSubsystem()));

	//Set Ony as camera target
	cameraMgr->setCameraTarget(pGameObjectOny->getPhysicsComponentCharacterOny());

	//Add reference to this
	pGameObjectOny->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectOny(pGameObjectOny);
	return pGameObjectOny;
}

GameObjectParticleSystemPtr GameObjectFactory::createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectParticleSystemPtr pGameObjectParticleSystem;	

	//Create GameObject
	pGameObjectParticleSystem = GameObjectParticleSystemPtr(new GameObjectParticleSystem(tGameObjectParticleSystemParameters.name));
	pGameObjectParticleSystem->setMaxUpdateRadio(tGameObjectParticleSystemParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectParticleSystem->setLogicComponent(
		mComponentFactory->createLogicComponent(
			pGameObjectParticleSystem,
			tGameObjectParticleSystemParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectParticleSystem->setRenderComponentPositional(
		mComponentFactory->createRenderComponentPositional(
			pGameObjectParticleSystem,
			tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectParticleSystem->setRenderComponentInitial(
		mComponentFactory->createRenderComponentInitial(
			pGameObjectParticleSystem->getRenderComponentPositional()));

	//Create RenderComponentParticleSystem
	pGameObjectParticleSystem->setRenderComponentParticleSystem(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectParticleSystem,
			tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters,
			pGameObjectParticleSystem->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectParticleSystem->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectParticleSystem(pGameObjectParticleSystem);
	return pGameObjectParticleSystem;
}

GameObjectPillowPtr GameObjectFactory::createGameObjectPillow(TGameObjectPillowParameters tGameObjectPillowParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPillowPtr pGameObjectPillow;

	//Create GameObject
	pGameObjectPillow = GameObjectPillowPtr(new GameObjectPillow(tGameObjectPillowParameters.name));	
	pGameObjectPillow->setMaxUpdateRadio(tGameObjectPillowParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectPillow->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectPillow,
		tGameObjectPillowParameters.tLogicComponentParameters));

	pGameObjectPillow->setAttackComponent(
		mComponentFactory->createAttackComponent(
		pGameObjectPillow,
		tGameObjectPillowParameters.attackComponentParameters
		));

	//Create RenderComponentPositional
	pGameObjectPillow->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectPillow,tGameObjectPillowParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectPillow->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectPillow->getRenderComponentPositional()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->PILLOW_ATTACK;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectPillow->setRenderComponentParticleSystemAttack(mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectPillow,tRenderComponentParticleSystemParameters,pGameObjectPillow->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectPillow->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectPillowParameters.name,
		pGameObjectPillow,tGameObjectPillowParameters.tRenderComponentEntityParameters));
	pGameObjectPillow->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	//UNCOMMENT WHEN THE FAKE COMPONENT ISN'T NEEDED ANYMORE
	//pGameObjectPillow->setPhysicsComponentSimpleCapsule(
	//	mComponentFactory->createPhysicsComponentSimpleCapsule(
	//	pGameObjectPillow, 
	//	tGameObjectPillowParameters.tPhysicsComponentSimpleCapsuleParameters, 
	//	pGameObjectPillow->getRenderComponentPositional()));
	PhysicsComponentSimpleCapsulePtr nullPtr=PhysicsComponentSimpleCapsulePtr();
	pGameObjectPillow->setPhysicsComponentSimpleCapsule(nullPtr);

	//Create FAKE PhysicsComponent
	TPhysicsComponentVolumeBoxParameters fakeVBParams;
	fakeVBParams.mass=0.0;
	fakeVBParams.lengthX=1.0;
	fakeVBParams.lengthY=1.0;
	fakeVBParams.lengthZ=1.0;
	pGameObjectPillow->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectPillow,
		fakeVBParams,
		pGameObjectPillow->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectPillow->setGameWorldManager(gameWorldMgr);

	//pGameObjectPillow->hide();
	//pGameObjectPillow->switchOff();

	//Add Object to GameWorldManager
	//addGameObjectPillow(pGameObjectPillow);	
	return pGameObjectPillow;
}

GameObjectPlanePtr GameObjectFactory::createGameObjectPlane(TGameObjectPlaneParameters tGameObjectPlaneParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPlanePtr pGameObjectPlane;

	//Create GameObject
	pGameObjectPlane = GameObjectPlanePtr(new GameObjectPlane(tGameObjectPlaneParameters.name));
	pGameObjectPlane->setMaxUpdateRadio(tGameObjectPlaneParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectPlane->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectPlane,
		tGameObjectPlaneParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectPlane->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectPlane,tGameObjectPlaneParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectPlane->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectPlane->getRenderComponentPositional()));

	//Create RenderComponentPlane
	pGameObjectPlane->setRenderComponentPlane(mComponentFactory->createRenderComponentPlane(
		pGameObjectPlane->getName(),pGameObjectPlane,tGameObjectPlaneParameters.tRenderComponentPlaneParameters));

	// Add a reference to this
	pGameObjectPlane->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectPlane(pGameObjectPlane);
	return pGameObjectPlane;
}

GameObjectPlataformPtr GameObjectFactory::createGameObjectPlataform(TGameObjectPlataformParameters tGameObjectPlataformParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPlataformPtr pGameObjectPlataform;

	//Create GameObject
	pGameObjectPlataform = GameObjectPlataformPtr(new GameObjectPlataform(tGameObjectPlataformParameters.name));
	pGameObjectPlataform->setMaxUpdateRadio(tGameObjectPlataformParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectPlataform->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectPlataform,
		tGameObjectPlataformParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectPlataform->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectPlataform->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectPlataform->getRenderComponentPositional()));

	if(pGameObjectPlataform->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectPlataform->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectPlataformParameters.dreamsName,
			pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectPlataform->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectPlataform->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectPlataformParameters.nightmaresName,
			pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityNightmaresParameters));
	}
	//Create PhysicsComponent
	pGameObjectPlataform->setPhysicsComponentComplexConvex(mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectPlataform,
		tGameObjectPlataformParameters.tPhysicsComponentComplexConvexParameters,
		pGameObjectPlataform->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectPlataform->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectPlataform(pGameObjectPlataform);
	return pGameObjectPlataform;
}

GameObjectPortalPtr GameObjectFactory::createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPortalPtr pGameObjectPortal;

	//Create GameObject
	pGameObjectPortal = GameObjectPortalPtr(new GameObjectPortal(tGameObjectPortalParameters.name));
	pGameObjectPortal->setMaxUpdateRadio(tGameObjectPortalParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectPortal->setLogicComponentUsable(
		mComponentFactory->createLogicComponentUsable(
		pGameObjectPortal,
		tGameObjectPortalParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectPortal->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectPortal->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectPortal->getRenderComponentPositional()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->PORTAL_CHANGE_WORLD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectPortal->setRenderComponentParticleSystemChangeWorld(mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectPortal,tRenderComponentParticleSystemParameters,pGameObjectPortal->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectPortal->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectPortalParameters.dreamsName,
		pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectPortal->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectPortalParameters.nightmaresName,
		pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityNightmaresParameters));

	//Create RenderComponentGlowDreams
	pGameObjectPortal->setRenderComponentGlowDreams(
		mComponentFactory->createRenderComponentGlow(
			pGameObjectPortal,
			tGameObjectPortalParameters.tRenderComponentGlowDreamsParameters,
			pGameObjectPortal->getRenderComponentPositional(),
			pGameObjectPortal->getRenderComponentEntityDreams()));

	//Create RenderComponentGlowNightmares
	pGameObjectPortal->setRenderComponentGlowNightmares(
		mComponentFactory->createRenderComponentGlow(
			pGameObjectPortal,
			tGameObjectPortalParameters.tRenderComponentGlowNightmaresParameters,
			pGameObjectPortal->getRenderComponentPositional(),
			pGameObjectPortal->getRenderComponentEntityNightmares()));
	
	//Create PhysicsComponent
	pGameObjectPortal->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectPortal, 
		tGameObjectPortalParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectPortal->getRenderComponentPositional()));

	pGameObjectPortal->setAudioComponent(
		mComponentFactory->createAudioComponent(
		pGameObjectPortal,
		tGameObjectPortalParameters.tAudioComponentParameters,
		gameWorldMgr->getParent()->getAudioSubsystem()));

	// Add a reference to this
	pGameObjectPortal->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectPortal(pGameObjectPortal);
	return pGameObjectPortal;
}

GameObjectProvisionalEntityPtr GameObjectFactory::createGameObjectProvisionalEntity(
	TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters,
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity;

	//Create GameObject
	pGameObjectProvisionalEntity = GameObjectProvisionalEntityPtr(new GameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters.name));
	pGameObjectProvisionalEntity->setMaxUpdateRadio(tGameObjectProvisionalEntityParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectProvisionalEntity->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectProvisionalEntity,
		tGameObjectProvisionalEntityParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectProvisionalEntity->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectProvisionalEntity->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectProvisionalEntity->getRenderComponentPositional()));

	if(pGameObjectProvisionalEntity->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectProvisionalEntity->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.dreamsName,
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectProvisionalEntity->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectProvisionalEntity->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.nightmaresName,
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectProvisionalEntity->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectProvisionalEntity, 
		tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectProvisionalEntity->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectProvisionalEntity->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectProvisionalEntity(pGameObjectProvisionalEntity);
	return pGameObjectProvisionalEntity;
}

GameObjectScaredPlantPtr GameObjectFactory::createGameObjectScaredPlant(TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectScaredPlantPtr pGameObjectScaredPlant;

	//Create GameObject
	pGameObjectScaredPlant = GameObjectScaredPlantPtr(new GameObjectScaredPlant(tGameObjectScaredPlantParameters.name));
	pGameObjectScaredPlant->setMaxUpdateRadio(tGameObjectScaredPlantParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectScaredPlant->setLogicComponent(
		mComponentFactory->createLogicComponentProp(
		pGameObjectScaredPlant,
		tGameObjectScaredPlantParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectScaredPlant->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectScaredPlant,tGameObjectScaredPlantParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectScaredPlant->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectScaredPlant->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectScaredPlant->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectScaredPlantParameters.name,
		pGameObjectScaredPlant,tGameObjectScaredPlantParameters.tRenderComponentEntityDreamsParameters));

	//Create PhysicsComponent
	pGameObjectScaredPlant->setPhysicsComponentSimpleBox(mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectScaredPlant,
		tGameObjectScaredPlantParameters.tPhysicsComponentSimpleBoxParameters,
		pGameObjectScaredPlant->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScaredPlant->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectScaredPlant(pGameObjectScaredPlant);
	return pGameObjectScaredPlant;
}

GameObjectScenePtr GameObjectFactory::createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters, 
	GameWorldManagerPtr gameWorldMgr)
{

	GameObjectScenePtr pGameObjectScene;

	//Create GameObject
	pGameObjectScene = GameObjectScenePtr(new GameObjectScene(tGameObjectSceneParameters.name));
	pGameObjectScene->setMaxUpdateRadio(tGameObjectSceneParameters.maxUpdateRadio);

	//Create RenderComponentViewport
	pGameObjectScene->setRenderComponentScene(mComponentFactory->createRenderComponentScene(
		pGameObjectScene,tGameObjectSceneParameters.tRenderComponentSceneParameters));

	// Add a reference to this
	pGameObjectScene->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectScene(pGameObjectScene);
	return pGameObjectScene;

}

GameObjectScepterPtr GameObjectFactory::createGameObjectScepter(TGameObjectScepterParameters tGameObjectScepterParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectScepterPtr pGameObjectScepter;

	//Create GameObject
	pGameObjectScepter = GameObjectScepterPtr(new GameObjectScepter(tGameObjectScepterParameters.name));
	pGameObjectScepter->setMaxUpdateRadio(tGameObjectScepterParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectScepter->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectScepter,
		tGameObjectScepterParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectScepter->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectScepter,tGameObjectScepterParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectScepter->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectScepter->getRenderComponentPositional()));

	//Create RenderComponentEntity 
	pGameObjectScepter->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectScepterParameters.name,
		pGameObjectScepter,tGameObjectScepterParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectScepter->setPhysicsComponentSimpleCapsule(
		mComponentFactory->createPhysicsComponentSimpleCapsule(
		pGameObjectScepter, 
		tGameObjectScepterParameters.tPhysicsComponentSimpleCapsuleParameters, 
		pGameObjectScepter->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScepter->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectScepter(pGameObjectScepter);
	return pGameObjectScepter;
}

GameObjectSkyBodyPtr GameObjectFactory::createGameObjectSkyBody(TGameObjectSkyBodyParameters params,
	GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraManager, Ogre::SceneManager* sceneManager)
{
	GameObjectSkyBodyPtr gameObject;

	//Create GameObject
	gameObject = GameObjectSkyBodyPtr(new GameObjectSkyBody(params.name));
	gameObject->setMaxUpdateRadio(params.maxUpdateRadio);

	gameObject->setUseEntityDreams(params.useEntityDreams);
	gameObject->setUseEntityNightmares(params.useEntityNightmares);

	//Create LogicComponent
	gameObject->setLogicComponent(
		mComponentFactory->createLogicComponent(
		gameObject,
		params.tLogicComponentParameters));

	//Create RenderComponentPositional
	gameObject->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		gameObject,params.tRenderComponentPositionalParameters));
	//gameObject->getRenderComponentPositional()->setScale(Vector3(10,10,10));

	//Create RenderComponentInitial
	gameObject->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		gameObject->getRenderComponentPositional()));

	if(gameObject->getLogicComponent()->existsInDreams() && gameObject->getLogicComponent()->existsInNightmares())
	{
		if (gameObject->isUsingEntityDreams())
		{
			//Create RenderComponentEntity Dreams
			gameObject->setRenderComponentEntityDreams(
				mComponentFactory->createRenderComponentEntity(params.dreamsName,
				gameObject,params.tRenderComponentEntityDreamsParameters));
			gameObject->setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr());
		}
		else
		{
			gameObject->setRenderComponentEntityDreams(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetDreams(mComponentFactory->createRenderComponentBillboardSet(
				params.dreamsName,
				gameObject,
				params.bbsDreamsParams));
		}
		gameObject->setLightDreams(mComponentFactory->createRenderComponentLight(
			params.dreamsName+"#light",
				gameObject,
				params.lightDreamsParams));

		if (gameObject->isUsingEntityNightmares())
		{
			gameObject->setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr());
			//Create RenderComponentEntity Nightmares
			gameObject->setRenderComponentEntityNightmares(
				mComponentFactory->createRenderComponentEntity(params.nightmaresName,
				gameObject,params.tRenderComponentEntityNightmaresParameters));
		}
		else
		{
			gameObject->setRenderComponentEntityNightmares(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetNightmares(mComponentFactory->createRenderComponentBillboardSet(
				params.nightmaresName,
				gameObject,
				params.bbsNightmaresParams));
		}

		gameObject->setLightNightmares(mComponentFactory->createRenderComponentLight(
			params.nightmaresName+"#light",
			gameObject,
			params.lightNightmaresParams));
	}
	else if(gameObject->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		if (gameObject->isUsingEntityDreams())
		{
			//Create RenderComponentEntity Dreams
			gameObject->setRenderComponentEntityDreams(
				mComponentFactory->createRenderComponentEntity(params.dreamsName,
				gameObject,params.tRenderComponentEntityDreamsParameters));

			gameObject->setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr());
		}
		else
		{
			gameObject->setRenderComponentEntityDreams(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetDreams(mComponentFactory->createRenderComponentBillboardSet(
				params.dreamsName,
				gameObject,
				params.bbsDreamsParams));
		}
		gameObject->setLightDreams(mComponentFactory->createRenderComponentLight(
			params.dreamsName,
			gameObject,
			params.lightDreamsParams));
	}
	else if(gameObject->getLogicComponent()->existsInNightmares())
	{
		if (gameObject->isUsingEntityNightmares())
		{
			gameObject->setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr());
			//Create RenderComponentEntity Nightmares
			gameObject->setRenderComponentEntityNightmares(
				mComponentFactory->createRenderComponentEntity(params.nightmaresName,
				gameObject,params.tRenderComponentEntityNightmaresParameters));
		}
		else
		{
			gameObject->setRenderComponentEntityNightmares(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetNightmares(mComponentFactory->createRenderComponentBillboardSet(
				params.nightmaresName,
				gameObject,
				params.bbsNightmaresParams));
		}

		gameObject->setLightNightmares(mComponentFactory->createRenderComponentLight(
			params.nightmaresName,
			gameObject,
			params.lightNightmaresParams));		
	}

	////////////////////////////////////////////////////////
	// Glow stuff

	if (gameObject->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentGlow Dreams
		gameObject->setRenderComponentGlowDreams(
			mComponentFactory->createRenderComponentGlow(
			gameObject,
			params.tRenderComponentGlowDreamsParameters,
			gameObject->getRenderComponentPositional(),
			gameObject->getRenderComponentEntityDreams()));
	}
	else
	{
		gameObject->setRenderComponentGlowDreams(RenderComponentGlowPtr());
	}

	if (gameObject->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentGlow Nightmares
		gameObject->setRenderComponentGlowNightmares(
			mComponentFactory->createRenderComponentGlow(
			gameObject,
			params.tRenderComponentGlowNightmaresParameters,
			gameObject->getRenderComponentPositional(),
			gameObject->getRenderComponentEntityNightmares()));
	}
	else
	{
		gameObject->setRenderComponentGlowNightmares(RenderComponentGlowPtr());
	}
	
	////////////////////////////////////////////////////////
	// Lens flare initialization
	gameObject->initLensFlare(cameraManager->getCamera(), sceneManager);

	//Add reference to this
	gameObject->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	return gameObject;
}

GameObjectSnakeCreeperPtr GameObjectFactory::createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSnakeCreeperPtr pGameObjectSnakeCreeper;

	//Create GameObject
	pGameObjectSnakeCreeper = GameObjectSnakeCreeperPtr(new GameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters.name));
	pGameObjectSnakeCreeper->setMaxUpdateRadio(tGameObjectSnakeCreeperParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectSnakeCreeper->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectSnakeCreeper,
		tGameObjectSnakeCreeperParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectSnakeCreeper->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectSnakeCreeper->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectSnakeCreeper->getRenderComponentPositional()));

	if(pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectSnakeCreeper->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectSnakeCreeperParameters.dreamsName,
			pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityDreamsParameters));
	}
	if(pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectSnakeCreeper->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectSnakeCreeperParameters.nightmaresName,
			pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectSnakeCreeper->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectSnakeCreeper, 
		tGameObjectSnakeCreeperParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectSnakeCreeper->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectSnakeCreeper->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectSnakeCreeper(pGameObjectSnakeCreeper);
	return pGameObjectSnakeCreeper;
}
GameObjectSoundPtr GameObjectFactory::createGameObjectSound(TGameObjectSoundParameters params, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSoundPtr sound = GameObjectSoundPtr(new GameObjectSound(params.name));
	sound->setMaxUpdateRadio(params.maxUpdateRadio);

	sound->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		sound,params.tRenderComponentPositionalParameters));

	sound->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		sound->getRenderComponentPositional()));

	AudioSubsystemPtr audioSS = gameWorldMgr->getParent()->getAudioSubsystem();

	sound->setAudioComponentDreams(mComponentFactory->createAudioComponent(sound,
		params.tAudioComponentDreamsParameters, audioSS));
	sound->setAudioComponentNightmares(mComponentFactory->createAudioComponent(sound,
		params.tAudioComponentNightmaresParameters, audioSS));

	sound->setSoundType(params.soundType);
	sound->setCurrentDreamsSoundId(params.currentDreamsSoundID);
	sound->setCurrentNightmaresSoundId(params.currentNightmaresSoundID);

	sound->setGameWorldManager(gameWorldMgr);

	return sound;
}

GameObjectStoryBookPtr GameObjectFactory::createGameObjectStoryBook(TGameObjectStoryBookParameters tGameObjectStoryBookParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectStoryBookPtr pGameObjectStoryBook;

	//Create GameObject
	pGameObjectStoryBook = GameObjectStoryBookPtr(new GameObjectStoryBook(tGameObjectStoryBookParameters.name));
	pGameObjectStoryBook->setMaxUpdateRadio(tGameObjectStoryBookParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectStoryBook->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectStoryBook,
		tGameObjectStoryBookParameters.tLogicComponentItemParameters));

	//Create RenderComponentPositional
	pGameObjectStoryBook->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectStoryBook,tGameObjectStoryBookParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectStoryBook->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectStoryBook->getRenderComponentPositional()));

	//Create RenderComponentEntity
	tGameObjectStoryBookParameters.tRenderComponentEntityParameters.prepareForNormalMapping=false;

	pGameObjectStoryBook->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectStoryBookParameters.name,
		pGameObjectStoryBook,tGameObjectStoryBookParameters.tRenderComponentEntityParameters));

	//pGameObjectStoryBook->getRenderComponentEntity()->prepareForNormalMapping();

	//Create PhysicsComponent
	pGameObjectStoryBook->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectStoryBook, 
		tGameObjectStoryBookParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectStoryBook->getRenderComponentPositional()));

	//Create LogicComponent
	pGameObjectStoryBook->setLogicComponentItem(
		mComponentFactory->createLogicComponentItem(
		pGameObjectStoryBook,
		tGameObjectStoryBookParameters.tLogicComponentItemParameters));

	//Add reference to this
	pGameObjectStoryBook->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectStoryBook(pGameObjectStoryBook);
	return pGameObjectStoryBook;
}

GameObjectTentetiesoPtr GameObjectFactory::createGameObjectTentetieso(TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTentetiesoPtr pGameObjectTentetieso;

	//Create GameObject
	pGameObjectTentetieso = GameObjectTentetiesoPtr(new GameObjectTentetieso(tGameObjectTentetiesoParameters.name));
	pGameObjectTentetieso->setMaxUpdateRadio(tGameObjectTentetiesoParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTentetieso->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectTentetieso,
		tGameObjectTentetiesoParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectTentetieso->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTentetieso->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTentetieso->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectTentetieso->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectTentetiesoParameters.dreamsName,
		pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectTentetieso->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTentetiesoParameters.nightmaresName,
		pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectTentetieso->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectTentetieso,
		tGameObjectTentetiesoParameters.tPhysicsComponentCharacterParameters,
		pGameObjectTentetieso->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTentetieso->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTentetieso(pGameObjectTentetieso);
	return pGameObjectTentetieso;
}

GameObjectTerrainConvexPtr GameObjectFactory::createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTerrainConvexPtr pGameObjectTerrainConvex;

	//Create GameObject
	pGameObjectTerrainConvex = GameObjectTerrainConvexPtr(new GameObjectTerrainConvex(tGameObjectTerrainConvexParameters.name));
	pGameObjectTerrainConvex->setMaxUpdateRadio(tGameObjectTerrainConvexParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTerrainConvex->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTerrainConvex,
		tGameObjectTerrainConvexParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTerrainConvex->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTerrainConvex->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTerrainConvex->getRenderComponentPositional()));

	if(pGameObjectTerrainConvex->getLogicComponent()->existsInDreams() && pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTerrainConvex->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.dreamsName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters));
		//Create RenderComponentEntityNightmares
		pGameObjectTerrainConvex->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.nightmaresName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters));
	}
	else if(pGameObjectTerrainConvex->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTerrainConvex->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.dreamsName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters));
	}
	else if(pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectTerrainConvex->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.nightmaresName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectTerrainConvex->setPhysicsComponentComplexConvex(mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectTerrainConvex,
		tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters,
		pGameObjectTerrainConvex->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTerrainConvex->setGameWorldManager(gameWorldMgr);
	//Add Object to GameWorldManager
	//addGameObjectTerrainConvex(pGameObjectTerrainConvex);
	return pGameObjectTerrainConvex;
}

GameObjectTerrainTrianglePtr GameObjectFactory::createGameObjectTerrainTriangle(
	TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle;

	//Create GameObject
	pGameObjectTerrainTriangle = GameObjectTerrainTrianglePtr(new GameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters.name));
	pGameObjectTerrainTriangle->setMaxUpdateRadio(tGameObjectTerrainTriangleParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTerrainTriangle->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTerrainTriangle,
		tGameObjectTerrainTriangleParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTerrainTriangle->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTerrainTriangle->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTerrainTriangle->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectTerrainTriangle->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectTerrainTriangleParameters.dreamsName,
		pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectTerrainTriangle->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTerrainTriangleParameters.nightmaresName,
		pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectTerrainTriangle->setPhysicsComponentComplexTriangle(mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectTerrainTriangle,
		tGameObjectTerrainTriangleParameters.tPhysicsComponentComplexTriangleParameters,
		pGameObjectTerrainTriangle->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTerrainTriangle->setGameWorldManager(gameWorldMgr);
	//Add Object to GameWorldManager
	//addGameObjectTerrainTriangle(pGameObjectTerrainTriangle);
	return pGameObjectTerrainTriangle;
}

GameObjectTreePtr GameObjectFactory::createGameObjectTree(TGameObjectTreeParameters tGameObjectTreeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTreePtr pGameObjectTree;

	//Create GameObject
	pGameObjectTree = GameObjectTreePtr(new GameObjectTree(tGameObjectTreeParameters.name));
	pGameObjectTree->setMaxUpdateRadio(tGameObjectTreeParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTree->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTree,
		tGameObjectTreeParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTree->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTree,tGameObjectTreeParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTree->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTree->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectTree->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectTreeParameters.name,
		pGameObjectTree,tGameObjectTreeParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectTree->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectTree, 
		tGameObjectTreeParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectTree->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTree->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTree(pGameObjectTree);
	return pGameObjectTree;
}

GameObjectTreeComplexPtr GameObjectFactory::createGameObjectTreeComplex(TGameObjectTreeComplexParameters tGameObjectTreeComplexParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTreeComplexPtr pGameObjectTreeComplex;

	//Create GameObject
	pGameObjectTreeComplex = GameObjectTreeComplexPtr(new GameObjectTreeComplex(tGameObjectTreeComplexParameters.name));
	pGameObjectTreeComplex->setMaxUpdateRadio(tGameObjectTreeComplexParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTreeComplex->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTreeComplex,
		tGameObjectTreeComplexParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTreeComplex->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTreeComplex,tGameObjectTreeComplexParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTreeComplex->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTreeComplex->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectTreeComplex->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectTreeComplexParameters.name,
		pGameObjectTreeComplex,tGameObjectTreeComplexParameters.tRenderComponentEntityParameters));

	//Create PhysicsComponent
	pGameObjectTreeComplex->setPhysicsComponentComplexConvex(
		mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectTreeComplex, 
		tGameObjectTreeComplexParameters.tPhysicsComponentComplexConvexParameters, 
		pGameObjectTreeComplex->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTreeComplex->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTreeComplex(pGameObjectTreeComplex);
	return pGameObjectTreeComplex;
}

GameObjectTowerPtr GameObjectFactory::createGameObjectTower(TGameObjectTowerParameters tGameObjectTowerParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTowerPtr pGameObjectTower;

	//Create GameObject
	pGameObjectTower = GameObjectTowerPtr(new GameObjectTower(tGameObjectTowerParameters.name));
	pGameObjectTower->setMaxUpdateRadio(tGameObjectTowerParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTower->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTower,
		tGameObjectTowerParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTower->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTower,tGameObjectTowerParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTower->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTower->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectTower->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectTowerParameters.dreamsName,
		pGameObjectTower,tGameObjectTowerParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectTower->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTowerParameters.nightmaresName,
		pGameObjectTower,tGameObjectTowerParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectTower->setPhysicsComponentComplexTriangle(
		mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectTower, 
		tGameObjectTowerParameters.tPhysicsComponentComplexTriangleParameters, 
		pGameObjectTower->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTower->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTower(pGameObjectTower);
	return pGameObjectTower;
}

GameObjectTriggerBoxPtr GameObjectFactory::createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTriggerBoxPtr pGameObjectTriggerBox;

	//Create GameObject
	pGameObjectTriggerBox = GameObjectTriggerBoxPtr(new GameObjectTriggerBox(tGameObjectTriggerBoxParameters.name));
	pGameObjectTriggerBox->setMaxUpdateRadio(tGameObjectTriggerBoxParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTriggerBox->setLogicComponent(
		mComponentFactory->createLogicComponentTrigger(
		pGameObjectTriggerBox,
		tGameObjectTriggerBoxParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTriggerBox->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTriggerBox,tGameObjectTriggerBoxParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTriggerBox->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTriggerBox->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectTriggerBox->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectTriggerBoxParameters.name,
		pGameObjectTriggerBox,tGameObjectTriggerBoxParameters.tRenderComponentEntityParameters));

	//Make RenderComponentEntity not visible
	pGameObjectTriggerBox->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectTriggerBox->setPhysicsComponentVolumeBox(mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectTriggerBox,
		tGameObjectTriggerBoxParameters.tPhysicsComponentVolumeBoxParameters,
		pGameObjectTriggerBox->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTriggerBox->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTriggerBox(pGameObjectTriggerBox);
	return pGameObjectTriggerBox;
}

GameObjectTriggerCapsulePtr GameObjectFactory::createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule;

	//Create GameObject
	pGameObjectTriggerCapsule = GameObjectTriggerCapsulePtr(new GameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters.name));
	pGameObjectTriggerCapsule->setMaxUpdateRadio(tGameObjectTriggerCapsuleParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTriggerCapsule->setLogicComponent(
		mComponentFactory->createLogicComponentTrigger(
		pGameObjectTriggerCapsule,
		tGameObjectTriggerCapsuleParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTriggerCapsule->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTriggerCapsule,tGameObjectTriggerCapsuleParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTriggerCapsule->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTriggerCapsule->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectTriggerCapsule->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectTriggerCapsuleParameters.name,
		pGameObjectTriggerCapsule,tGameObjectTriggerCapsuleParameters.tRenderComponentEntityParameters));

	//Make RenderComponentEntity not visible
	pGameObjectTriggerCapsule->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectTriggerCapsule->setPhysicsComponentVolumeCapsule(mComponentFactory->createPhysicsComponentVolumeCapsule(
		pGameObjectTriggerCapsule,
		tGameObjectTriggerCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters,
		pGameObjectTriggerCapsule->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTriggerCapsule->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTriggerCapsule(pGameObjectTriggerCapsule);
	return pGameObjectTriggerCapsule;
}

GameObjectTriggerCameraPtr GameObjectFactory::createGameObjectTriggerCamera(TGameObjectTriggerCameraParameters tGameObjectTriggerCameraParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTriggerCameraPtr pGameObjectTriggerCamera;

	//Create GameObject
	pGameObjectTriggerCamera = GameObjectTriggerCameraPtr(new GameObjectTriggerCamera(tGameObjectTriggerCameraParameters.name));
	pGameObjectTriggerCamera->setMaxUpdateRadio(tGameObjectTriggerCameraParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTriggerCamera->setLogicComponentTriggerCamera(
		mComponentFactory->createLogicComponentTriggerCamera(
		pGameObjectTriggerCamera,
		tGameObjectTriggerCameraParameters.tLogicComponentTriggerCameraParameters));

	//Create RenderComponentPositional
	pGameObjectTriggerCamera->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTriggerCamera,tGameObjectTriggerCameraParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTriggerCamera->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTriggerCamera->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectTriggerCamera->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectTriggerCameraParameters.name,
		pGameObjectTriggerCamera,tGameObjectTriggerCameraParameters.tRenderComponentEntityParameters));

	//Make RenderComponentEntity not visible
	pGameObjectTriggerCamera->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectTriggerCamera->setPhysicsComponentVolumeBox(mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectTriggerCamera,
		tGameObjectTriggerCameraParameters.tPhysicsComponentVolumeBoxParameters,
		pGameObjectTriggerCamera->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTriggerCamera->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTriggerCamera(pGameObjectTriggerCamera);
	return pGameObjectTriggerCamera;
}

GameObjectTripollitoPtr GameObjectFactory::createGameObjectTripollito(TGameObjectTripollitoParameters tGameObjectTripollitoParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTripollitoPtr pGameObjectTripollito;

	//Create GameObject
	pGameObjectTripollito = GameObjectTripollitoPtr(new GameObjectTripollito(tGameObjectTripollitoParameters.name));
	pGameObjectTripollito->setMaxUpdateRadio(tGameObjectTripollitoParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTripollito->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(pGameObjectTripollito,
		tGameObjectTripollitoParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectTripollito->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTripollito->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTripollito->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectTripollito->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectTripollitoParameters.dreamsName,
		pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentEntityDreamsParameters));

	//Create RenderComponentEntityNightmares
	pGameObjectTripollito->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTripollitoParameters.nightmaresName,
		pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentEntityNightmaresParameters));

	//Create PhysicsComponent
	pGameObjectTripollito->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectTripollito,
		tGameObjectTripollitoParameters.tPhysicsComponentCharacterParameters,
		pGameObjectTripollito->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTripollito->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectTripollito(pGameObjectTripollito);
	return pGameObjectTripollito;
}

GameObjectTripolloDreamsPtr GameObjectFactory::createGameObjectTripolloDreams(TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTripolloDreamsPtr pGameObjectTripolloDreams;

	//Create GameObject
	pGameObjectTripolloDreams = GameObjectTripolloDreamsPtr(new GameObjectTripolloDreams(tGameObjectTripolloDreamsParameters.name));
	pGameObjectTripolloDreams->setMaxUpdateRadio(tGameObjectTripolloDreamsParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectTripolloDreams->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(pGameObjectTripolloDreams,
		tGameObjectTripolloDreamsParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectTripolloDreams->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTripolloDreams,tGameObjectTripolloDreamsParameters.tRenderComponentPositionalParameters));

	//TODO ERASE THIS WHEN TRIPOLLO IS PROPERLY SCALED
	pGameObjectTripolloDreams->getRenderComponentPositional()->setScale(
		tGameObjectTripolloDreamsParameters.tPhysicsComponentCharacterParameters.scale_correction);

	//Create RenderComponentInitial
	pGameObjectTripolloDreams->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTripolloDreams->getRenderComponentPositional()));

	if(pGameObjectTripolloDreams->getLogicComponentEnemy()->existsInDreams() && pGameObjectTripolloDreams->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTripolloDreams->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloDreamsParameters.dreamsName,
			pGameObjectTripolloDreams,tGameObjectTripolloDreamsParameters.tRenderComponentEntityDreamsParameters));
		//Create RenderComponentEntityNightmares
		pGameObjectTripolloDreams->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloDreamsParameters.nightmaresName,
			pGameObjectTripolloDreams,tGameObjectTripolloDreamsParameters.tRenderComponentEntityNightmaresParameters));
	}
	else if(pGameObjectTripolloDreams->getLogicComponentEnemy()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTripolloDreams->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloDreamsParameters.dreamsName,
			pGameObjectTripolloDreams,tGameObjectTripolloDreamsParameters.tRenderComponentEntityDreamsParameters));
	}
	else if(pGameObjectTripolloDreams->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectTripolloDreams->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloDreamsParameters.nightmaresName,
			pGameObjectTripolloDreams,tGameObjectTripolloDreamsParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectTripolloDreams->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectTripolloDreams,
		tGameObjectTripolloDreamsParameters.tPhysicsComponentCharacterParameters,
		pGameObjectTripolloDreams->getRenderComponentPositional()));

	//TODO ERASE THIS WHEN PROPERLY DONE IN XSI
	pGameObjectTripolloDreams->getPhysicsComponentCharacter()->setOffsetRenderPosition(
		tGameObjectTripolloDreamsParameters.tPhysicsComponentCharacterParameters.position_correction);

	//Create TrajectoryComponent
	pGameObjectTripolloDreams->setTrajectoryComponent(mComponentFactory->createTrajectoryComponent(
		pGameObjectTripolloDreams,
		true));

	pGameObjectTripolloDreams->setAttackComponent(
		mComponentFactory->createAttackComponent(
		pGameObjectTripolloDreams,
		tGameObjectTripolloDreamsParameters.tAttackComponentParameters));

	// Create audio component
	pGameObjectTripolloDreams->setAudioComponent(
		mComponentFactory->createAudioComponent(
		pGameObjectTripolloDreams,
		tGameObjectTripolloDreamsParameters.tAudioComponentParameters
		,gameWorldMgr->getParent()->getAudioSubsystem()));

	// Add a reference to this
	pGameObjectTripolloDreams->setGameWorldManager(gameWorldMgr);


	//Add Object to GameWorldManager
	//addGameObjectTripolloDreams(pGameObjectTripolloDreams);
	return pGameObjectTripolloDreams;
}

GameObjectViewportPtr GameObjectFactory::createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectViewportPtr pGameObjectViewport;

	//Create GameObject
	pGameObjectViewport = GameObjectViewportPtr(new GameObjectViewport(tGameObjectViewportParameters.name));
	pGameObjectViewport->setMaxUpdateRadio(tGameObjectViewportParameters.maxUpdateRadio);

	//Create RenderComponentViewport
	pGameObjectViewport->setRenderComponentViewport(mComponentFactory->createRenderComponentViewport(
		pGameObjectViewport,tGameObjectViewportParameters.tRenderComponentViewportParameters));

	// Add a reference to this
	pGameObjectViewport->setGameWorldManager(gameWorldMgr);

	//Initialize compositor effects

	//pGameObjectViewport->setEffect("Posterize",true);

	//Add Object to GameWorldManager
	//addGameObjectViewport(pGameObjectViewport);
	return pGameObjectViewport;
}

GameObjectWoodBoxPtr GameObjectFactory::createGameObjectWoodBox(TGameObjectWoodBoxParameters tGameObjectWoodBoxParameters, 
											 GameWorldManagerPtr gameWorldMgr)
{
	GameObjectWoodBoxPtr pGameObjectWoodBox;

	//Create GameObject
	pGameObjectWoodBox = GameObjectWoodBoxPtr(new GameObjectWoodBox(tGameObjectWoodBoxParameters.name));
	pGameObjectWoodBox->setMaxUpdateRadio(tGameObjectWoodBoxParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectWoodBox->setLogicComponentBreakable(
		mComponentFactory->createLogicComponentBreakable(
			pGameObjectWoodBox,
			tGameObjectWoodBoxParameters.tLogicComponentBreakableParameters));

	//Create RenderComponentPositional
	pGameObjectWoodBox->setRenderComponentPositional(
		mComponentFactory->createRenderComponentPositional(
			pGameObjectWoodBox,
			tGameObjectWoodBoxParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectWoodBox->setRenderComponentInitial(
		mComponentFactory->createRenderComponentInitial(
			pGameObjectWoodBox->getRenderComponentPositional()));

	if(pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams() && pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares())
	{
		//Create RenderComponentEntityDreams
		pGameObjectWoodBox->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.dreamsName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityDreamsParameters));
		//Create RenderComponentEntityNightmares
		pGameObjectWoodBox->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.nightmaresName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityNightmaresParameters));
	}
	else if(pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectWoodBox->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.dreamsName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityDreamsParameters));
	}
	else if(pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectWoodBox->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.nightmaresName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityNightmaresParameters));
	}

	//Create PhysicsComponent
	pGameObjectWoodBox->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
			pGameObjectWoodBox, 
			tGameObjectWoodBoxParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectWoodBox->getRenderComponentPositional()));

	pGameObjectWoodBox->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectWoodBox, 
		tGameObjectWoodBoxParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectWoodBox->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectWoodBox->setGameWorldManager(gameWorldMgr);

	//Add Object to GameWorldManager
	//addGameObjectWoodBox(pGameObjectWoodBox);
	return pGameObjectWoodBox;
}

GameObjectWaterPtr GameObjectFactory::createGameObjectWater(TGameObjectWaterParameters tGameObjectWaterParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectWaterPtr pGameObjectWater;

	//Create GameObject
	pGameObjectWater = GameObjectWaterPtr(new GameObjectWater(tGameObjectWaterParameters.name));
	pGameObjectWater->setMaxUpdateRadio(tGameObjectWaterParameters.maxUpdateRadio);

	//Create LogicComponent
	pGameObjectWater->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectWater,
		tGameObjectWaterParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectWater->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectWater,tGameObjectWaterParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectWater->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectWater->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectWater->setPhysicsComponentVolumeConvex(mComponentFactory->createPhysicsComponentVolumeConvex(
		pGameObjectWater,
		tGameObjectWaterParameters.tPhysicsComponentVolumeConvexParameters,
		pGameObjectWater->getRenderComponentPositional()));

	if(pGameObjectWater->getLogicComponent()->existsInDreams() && pGameObjectWater->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentWaterDreams
		pGameObjectWater->setRenderComponentWaterDreams(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.dreamsName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterDreamsParameters));
		//Create RenderComponentWaterNightmares
		pGameObjectWater->setRenderComponentWaterNightmares(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.nightmaresName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterNightmaresParameters));
	}
	else if(pGameObjectWater->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentWaterDreams
		pGameObjectWater->setRenderComponentWaterDreams(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.dreamsName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterDreamsParameters));
	}
	else if(pGameObjectWater->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentWaterNightmares
		pGameObjectWater->setRenderComponentWaterNightmares(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.nightmaresName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterNightmaresParameters));
	}

	// Add a reference to this
	pGameObjectWater->setGameWorldManager(gameWorldMgr);
	//Add Object to GameWorldManager
	//addGameObjectWater(pGameObjectWater);
	return pGameObjectWater;
}