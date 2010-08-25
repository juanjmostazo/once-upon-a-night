#include "OUAN_Precompiled.h"

#include "GameObjectFactory.h"

#include "GameWorldManager.h"

#include "GameObject/GameObject.h"
#include "GameObject/GameObjectBee_Butterfly.h"
#include "GameObject/GameObjectBillboardSet.h"
#include "GameObject/GameObjectTraspasable.h"
#include "GameObject/GameObjectCarnivorousPlant.h"
#include "GameObject/GameObjectClockPiece.h"
#include "GameObject/GameObjectCloud.h"
#include "GameObject/GameObjectCryKing.h"
#include "GameObject/GameObjectDiamond.h"
#include "GameObject/GameObjectDiamondTree.h"
#include "GameObject/GameObjectBreakableRock.h"
#include "GameObject/GameObjectInvisibleWall.h"
#include "GameObject/GameObjectDoor.h"
#include "GameObject/GameObjectBoss.h"
#include "GameObject/GameObjectEye.h"
#include "GameObject/GameObjectFlashLight.h"
#include "GameObject/GameObjectHeart.h"
#include "GameObject/GameObjectItem1UP.h"
#include "GameObject/GameObjectItemMaxHP.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectMagicClock.h"
#include "GameObject/GameObjectNest.h"
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
#include "GameObject/GameObjectSignpost.h"
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
#include "GameObject/GameObjectTripollo.h"
#include "GameObject/GameObjectViewport.h"
#include "GameObject/GameObjectWoodBox.h"
#include "GameObject/GameObjectWater.h"
#include "GameObject/GameObjectTreeComplex.h"
#include "GameObject/GameObjectTower.h"
#include "GameObject/GameObjectFog.h"
#include "GameObject/GameObjectCameraTrigger.h"
#include "GameObject/GameObjectSwitch.h"
#include "GameObject/GameObjectBomb.h"
#include "GameObject/GameObjectTotem.h"
#include "GameObject/GameObjectLevelEntrance.h"

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

#include "../Logic/LogicSubsystem.h"

#include "../Component/ComponentFactory.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"
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
	pGameObjectBee_Butterfly->setMaxUpdateRadium(tGameObjectBee_ButterflyParameters.mMaxUpdateRadium);
	pGameObjectBee_Butterfly->setParentNest(tGameObjectBee_ButterflyParameters.parentNest);
	pGameObjectBee_Butterfly->setSpawnProbability(tGameObjectBee_ButterflyParameters.spawnProbability);
	pGameObjectBee_Butterfly->setMaxRenderRadium(tGameObjectBee_ButterflyParameters.mMaxRenderRadium);

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
			pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityDreamsParameters,
			pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInDreams(),
			pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInNightmares()));

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
			pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityNightmaresParameters,
			pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInDreams(),
			pGameObjectBee_Butterfly->getLogicComponentEnemy()->existsInNightmares()));

		//Create PhysicsComponent Nightmares
		pGameObjectBee_Butterfly->setPhysicsComponentCharacterNightmares(
			mComponentFactory->createPhysicsComponentCharacter(
			pGameObjectBee_Butterfly, 
			tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterNightmaresParameters, 
			pGameObjectBee_Butterfly->getRenderComponentPositional()));
	}

	//Add reference to this
	pGameObjectBee_Butterfly->setGameWorldManager(gameWorldMgr);
	std::string scriptFile="";	
	pGameObjectBee_Butterfly->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

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
	pGameObjectBillboardSet->setMaxUpdateRadium(tGameObjectBillboardSetParameters.mMaxUpdateRadium);
	pGameObjectBillboardSet->setParentNest(tGameObjectBillboardSetParameters.parentNest);
	pGameObjectBillboardSet->setSpawnProbability(tGameObjectBillboardSetParameters.spawnProbability);
	pGameObjectBillboardSet->setMaxRenderRadium(tGameObjectBillboardSetParameters.mMaxRenderRadium);

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
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters,
			pGameObjectBillboardSet->getLogicComponent()->existsInDreams(),
			pGameObjectBillboardSet->getLogicComponent()->existsInNightmares()));
		//Create RenderComponentBillboardSetNightmares
		pGameObjectBillboardSet->setRenderComponentBillboardSetNightmares(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.nightmaresName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters,
			pGameObjectBillboardSet->getLogicComponent()->existsInDreams(),
			pGameObjectBillboardSet->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectBillboardSet->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentBillboardSetDreams
		pGameObjectBillboardSet->setRenderComponentBillboardSetDreams(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.dreamsName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetDreamsParameters,
			pGameObjectBillboardSet->getLogicComponent()->existsInDreams(),
			pGameObjectBillboardSet->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectBillboardSet->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentBillboardSetNightmares
		pGameObjectBillboardSet->setRenderComponentBillboardSetNightmares(
			mComponentFactory->createRenderComponentBillboardSet(tGameObjectBillboardSetParameters.nightmaresName,
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetNightmaresParameters,
			pGameObjectBillboardSet->getLogicComponent()->existsInDreams(),
			pGameObjectBillboardSet->getLogicComponent()->existsInNightmares()));
	}
	// Add a reference to this
	pGameObjectBillboardSet->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectBillboardSet->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	//Add Object to GameWorldManager
	//addGameObjectBillboardSet(pGameObjectBillboardSet);
	return pGameObjectBillboardSet;
}

GameObjectTraspasablePtr GameObjectFactory::createGameObjectTraspasable(TGameObjectTraspasableParameters tGameObjectTraspasableParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTraspasablePtr pGameObjectTraspasable;

	//Create GameObject
	pGameObjectTraspasable = GameObjectTraspasablePtr(new GameObjectTraspasable(tGameObjectTraspasableParameters.name));
	pGameObjectTraspasable->setMaxUpdateRadium(tGameObjectTraspasableParameters.mMaxUpdateRadium);
	pGameObjectTraspasable->setParentNest(tGameObjectTraspasableParameters.parentNest);
	pGameObjectTraspasable->setSpawnProbability(tGameObjectTraspasableParameters.spawnProbability);
	pGameObjectTraspasable->setMaxRenderRadium(tGameObjectTraspasableParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectTraspasable->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTraspasable,
		tGameObjectTraspasableParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTraspasable->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTraspasable,tGameObjectTraspasableParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTraspasable->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTraspasable->getRenderComponentPositional()));

	if(pGameObjectTraspasable->getLogicComponent()->existsInDreams() && pGameObjectTraspasable->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectTraspasable->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTraspasableParameters.dreamsName,
			pGameObjectTraspasable,tGameObjectTraspasableParameters.tRenderComponentEntityDreamsParameters,
			pGameObjectTraspasable->getLogicComponent()->existsInDreams(),
			pGameObjectTraspasable->getLogicComponent()->existsInNightmares()));

		//Create RenderComponentEntity Nightmares
		pGameObjectTraspasable->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTraspasableParameters.nightmaresName,
			pGameObjectTraspasable,tGameObjectTraspasableParameters.tRenderComponentEntityNightmaresParameters,
			pGameObjectTraspasable->getLogicComponent()->existsInDreams(),
			pGameObjectTraspasable->getLogicComponent()->existsInNightmares()));

	}
	else if(pGameObjectTraspasable->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectTraspasable->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTraspasableParameters.dreamsName,
			pGameObjectTraspasable,tGameObjectTraspasableParameters.tRenderComponentEntityDreamsParameters,
			pGameObjectTraspasable->getLogicComponent()->existsInDreams(),
			pGameObjectTraspasable->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectTraspasable->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectTraspasable->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTraspasableParameters.nightmaresName,
			pGameObjectTraspasable,tGameObjectTraspasableParameters.tRenderComponentEntityNightmaresParameters,
			pGameObjectTraspasable->getLogicComponent()->existsInDreams(),
			pGameObjectTraspasable->getLogicComponent()->existsInNightmares()));
	}

	//Add reference to this
	pGameObjectTraspasable->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTraspasable->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	//Add Object to GameWorldManager
	//addGameObjectTraspasable(pGameObjectTraspasable);
	return pGameObjectTraspasable;
}


GameObjectCarnivorousPlantPtr GameObjectFactory::createGameObjectCarnivorousPlant(
	TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant;

	//Create GameObject
	pGameObjectCarnivorousPlant = GameObjectCarnivorousPlantPtr(new GameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters.name));
	pGameObjectCarnivorousPlant->setMaxUpdateRadium(tGameObjectCarnivorousPlantParameters.mMaxUpdateRadium);
	pGameObjectCarnivorousPlant->setParentNest(
		tGameObjectCarnivorousPlantParameters.parentNest);
	pGameObjectCarnivorousPlant->setSpawnProbability(tGameObjectCarnivorousPlantParameters.spawnProbability);
	pGameObjectCarnivorousPlant->setMaxRenderRadium(tGameObjectCarnivorousPlantParameters.mMaxRenderRadium);

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
			pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityDreamsParameters,
			pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInDreams(),
			pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInNightmares()));
	}
	if(pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectCarnivorousPlant->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectCarnivorousPlantParameters.nightmaresName,
			pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityNightmaresParameters,
			pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInDreams(),
			pGameObjectCarnivorousPlant->getLogicComponentEnemy()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectCarnivorousPlant->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectCarnivorousPlant, 
		tGameObjectCarnivorousPlantParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectCarnivorousPlant->getRenderComponentPositional()));


	//Add reference to this
	pGameObjectCarnivorousPlant->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectCarnivorousPlant->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectCarnivorousPlant;
}

GameObjectClockPiecePtr GameObjectFactory::createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectClockPiecePtr pGameObjectClockPiece;

	//Create GameObject
	pGameObjectClockPiece = GameObjectClockPiecePtr(new GameObjectClockPiece(tGameObjectClockPieceParameters.name));
	pGameObjectClockPiece->setMaxUpdateRadium(tGameObjectClockPieceParameters.mMaxUpdateRadium);
	pGameObjectClockPiece->setSpawnProbability(tGameObjectClockPieceParameters.spawnProbability);
	pGameObjectClockPiece->setParentNest(tGameObjectClockPieceParameters.parentNest);
	pGameObjectClockPiece->setMaxRenderRadium(tGameObjectClockPieceParameters.mMaxRenderRadium);

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
		pGameObjectClockPiece,tGameObjectClockPieceParameters.tRenderComponentEntityParameters,
		pGameObjectClockPiece->getLogicComponentItem()->existsInDreams(),
		pGameObjectClockPiece->getLogicComponentItem()->existsInNightmares()));

	//Create RenderComponentGlowDreams
	pGameObjectClockPiece->setRenderComponentGlow(
		mComponentFactory->createRenderComponentGlow(
			pGameObjectClockPiece,
			tGameObjectClockPieceParameters.tRenderComponentGlowParameters,
			pGameObjectClockPiece->getRenderComponentPositional(),
			pGameObjectClockPiece->getRenderComponentEntity()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->CLOCK_PIECE_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectClockPiece->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectClockPiece,
		tRenderComponentParticleSystemParameters,
		pGameObjectClockPiece->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectClockPiece->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectClockPiece, 
		tGameObjectClockPieceParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectClockPiece->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectClockPiece->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectClockPiece->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectClockPiece;
}

GameObjectCloudPtr GameObjectFactory::createGameObjectCloud(TGameObjectCloudParameters tGameObjectCloudParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCloudPtr pGameObjectCloud;
	
	//Create GameObject
	pGameObjectCloud = GameObjectCloudPtr(new GameObjectCloud(tGameObjectCloudParameters.name));
	pGameObjectCloud->setMaxUpdateRadium(tGameObjectCloudParameters.mMaxUpdateRadium);
	pGameObjectCloud->setParentNest(tGameObjectCloudParameters.parentNest);
	pGameObjectCloud->setSpawnProbability(tGameObjectCloudParameters.spawnProbability);
	pGameObjectCloud->setMaxRenderRadium(tGameObjectCloudParameters.mMaxRenderRadium);

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
	std::string scriptFile="";
	pGameObjectCloud->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

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
	pGameObjectCryKing->setMaxUpdateRadium(tGameObjectCryKingParameters.mMaxUpdateRadium);
	pGameObjectCryKing->setParentNest(tGameObjectCryKingParameters.parentNest);
	pGameObjectCryKing->setSpawnProbability(tGameObjectCryKingParameters.spawnProbability);
	pGameObjectCryKing->setMaxRenderRadium(tGameObjectCryKingParameters.mMaxRenderRadium);

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
			pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectCryKing->getLogicComponent()->existsInDreams(),
		pGameObjectCryKing->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectCryKing->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectCryKing->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectCryKingParameters.nightmaresName,
			pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectCryKing->getLogicComponent()->existsInDreams(),
		pGameObjectCryKing->getLogicComponent()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectCryKing->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectCryKing, 
		tGameObjectCryKingParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectCryKing->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectCryKing->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectCryKing->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectCryKing;
}

GameObjectDiamondPtr GameObjectFactory::createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters, 
	GameWorldManagerPtr gameWorldMgr, bool hasGravity)
{
	GameObjectDiamondPtr pGameObjectDiamond;

	//Create GameObject
	pGameObjectDiamond = GameObjectDiamondPtr(new GameObjectDiamond(tGameObjectDiamondParameters.name));
	pGameObjectDiamond->setMaxUpdateRadium(tGameObjectDiamondParameters.mMaxUpdateRadium);
	pGameObjectDiamond->setParentNest(tGameObjectDiamondParameters.parentNest);
	pGameObjectDiamond->setSpawnProbability(tGameObjectDiamondParameters.spawnProbability);
	pGameObjectDiamond->setMaxRenderRadium(tGameObjectDiamondParameters.mMaxRenderRadium);

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
		pGameObjectDiamond,tGameObjectDiamondParameters.tRenderComponentEntityParameters,
		pGameObjectDiamond->getLogicComponentItem()->existsInDreams(),
		pGameObjectDiamond->getLogicComponentItem()->existsInNightmares()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->DIAMOND_BRIGHTNESS;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectDiamond->setRenderComponentParticleSystemBrightness(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectDiamond,
		tRenderComponentParticleSystemParameters,
		pGameObjectDiamond->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->DIAMOND_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectDiamond->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectDiamond,
		tRenderComponentParticleSystemParameters,
		pGameObjectDiamond->getRenderComponentPositional()));

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

	if(!hasGravity)
	{
		pGameObjectDiamond->getPhysicsComponentSimpleBox()->destroy();
	}

	if (!tGameObjectDiamondParameters.tParentDiamondTree.empty())
	{
		pGameObjectDiamond->setParentDiamondTreeName(tGameObjectDiamondParameters.tParentDiamondTree);
	}	

	//Add reference to this
	pGameObjectDiamond->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectDiamond->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectDiamond;
}

GameObjectDiamondTreePtr GameObjectFactory::createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDiamondTreePtr pGameObjectDiamondTree;

	//Create GameObject
	pGameObjectDiamondTree = GameObjectDiamondTreePtr(new GameObjectDiamondTree(tGameObjectDiamondTreeParameters.name));
	pGameObjectDiamondTree->setMaxUpdateRadium(tGameObjectDiamondTreeParameters.mMaxUpdateRadium);
	pGameObjectDiamondTree->setParentNest(tGameObjectDiamondTreeParameters.parentNest);
	pGameObjectDiamondTree->setSpawnProbability(tGameObjectDiamondTreeParameters.spawnProbability);
	pGameObjectDiamondTree->setMaxRenderRadium(tGameObjectDiamondTreeParameters.mMaxRenderRadium);

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
			pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectDiamondTree->getLogicComponent()->existsInDreams(),
		pGameObjectDiamondTree->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectDiamondTree->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectDiamondTree->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectDiamondTreeParameters.nightmaresName,
			pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectDiamondTree->getLogicComponent()->existsInDreams(),
		pGameObjectDiamondTree->getLogicComponent()->existsInNightmares()));
	}
						
	//Create PhysicsComponent
	pGameObjectDiamondTree->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectDiamondTree, 
		tGameObjectDiamondTreeParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectDiamondTree->getRenderComponentPositional()));


	//Add reference to this
	pGameObjectDiamondTree->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectDiamondTree->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectDiamondTree;
}

GameObjectDoorPtr GameObjectFactory::createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectDoorPtr pGameObjectDoor;

	//Create GameObject
	pGameObjectDoor = GameObjectDoorPtr(new GameObjectDoor(tGameObjectDoorParameters.name));
	pGameObjectDoor->setMaxUpdateRadium(tGameObjectDoorParameters.mMaxUpdateRadium);
	pGameObjectDoor->setParentNest(tGameObjectDoorParameters.parentNest);
	pGameObjectDoor->setSpawnProbability(tGameObjectDoorParameters.spawnProbability);
	pGameObjectDoor->setMaxRenderRadium(tGameObjectDoorParameters.mMaxRenderRadium);

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
			pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectDoor->getLogicComponent()->existsInDreams(),
		pGameObjectDoor->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectDoor->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectDoor->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectDoorParameters.nightmaresName,
			pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectDoor->getLogicComponent()->existsInDreams(),
		pGameObjectDoor->getLogicComponent()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectDoor->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectDoor, 
		tGameObjectDoorParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectDoor->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDoor->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectDoor->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectDoor;
}

GameObjectBreakableRockPtr GameObjectFactory::createGameObjectBreakableRock(TGameObjectBreakableRockParameters tGameObjectBreakableRockParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBreakableRockPtr pGameObjectBreakableRock;

	//Create GameObject
	pGameObjectBreakableRock = GameObjectBreakableRockPtr(new GameObjectBreakableRock(tGameObjectBreakableRockParameters.name));
	pGameObjectBreakableRock->setMaxUpdateRadium(tGameObjectBreakableRockParameters.mMaxUpdateRadium);
	pGameObjectBreakableRock->setParentNest(tGameObjectBreakableRockParameters.parentNest);
	pGameObjectBreakableRock->setSpawnProbability(tGameObjectBreakableRockParameters.spawnProbability);
	pGameObjectBreakableRock->setMaxRenderRadium(tGameObjectBreakableRockParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectBreakableRock->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectBreakableRock,
		tGameObjectBreakableRockParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectBreakableRock->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBreakableRock,tGameObjectBreakableRockParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBreakableRock->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBreakableRock->getRenderComponentPositional()));

	if(pGameObjectBreakableRock->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectBreakableRock->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectBreakableRockParameters.dreamsName,
			pGameObjectBreakableRock,tGameObjectBreakableRockParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectBreakableRock->getLogicComponent()->existsInDreams(),
		pGameObjectBreakableRock->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectBreakableRock->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectBreakableRock->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectBreakableRockParameters.nightmaresName,
			pGameObjectBreakableRock,tGameObjectBreakableRockParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectBreakableRock->getLogicComponent()->existsInDreams(),
		pGameObjectBreakableRock->getLogicComponent()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectBreakableRock->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectBreakableRock, 
		tGameObjectBreakableRockParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectBreakableRock->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectBreakableRock->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectBreakableRock->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectBreakableRock;
}

GameObjectInvisibleWallPtr GameObjectFactory::createGameObjectInvisibleWall(TGameObjectInvisibleWallParameters tGameObjectInvisibleWallParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectInvisibleWallPtr pGameObjectInvisibleWall;

	//Create GameObject
	pGameObjectInvisibleWall = GameObjectInvisibleWallPtr(new GameObjectInvisibleWall(tGameObjectInvisibleWallParameters.name));
	pGameObjectInvisibleWall->setMaxUpdateRadium(tGameObjectInvisibleWallParameters.mMaxUpdateRadium);
	pGameObjectInvisibleWall->setParentNest(tGameObjectInvisibleWallParameters.parentNest);
	pGameObjectInvisibleWall->setSpawnProbability(tGameObjectInvisibleWallParameters.spawnProbability);
	pGameObjectInvisibleWall->setMaxRenderRadium(tGameObjectInvisibleWallParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectInvisibleWall->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectInvisibleWall,
		tGameObjectInvisibleWallParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectInvisibleWall->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectInvisibleWall,tGameObjectInvisibleWallParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectInvisibleWall->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectInvisibleWall->getRenderComponentPositional()));

	if(pGameObjectInvisibleWall->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectInvisibleWall->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectInvisibleWallParameters.dreamsName,
			pGameObjectInvisibleWall,tGameObjectInvisibleWallParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectInvisibleWall->getLogicComponent()->existsInDreams(),
		pGameObjectInvisibleWall->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectInvisibleWall->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectInvisibleWall->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectInvisibleWallParameters.nightmaresName,
			pGameObjectInvisibleWall,tGameObjectInvisibleWallParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectInvisibleWall->getLogicComponent()->existsInDreams(),
		pGameObjectInvisibleWall->getLogicComponent()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectInvisibleWall->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectInvisibleWall, 
		tGameObjectInvisibleWallParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectInvisibleWall->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectInvisibleWall->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectInvisibleWall->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectInvisibleWall;
}

GameObjectBossPtr GameObjectFactory::createGameObjectBoss(TGameObjectBossParameters tGameObjectBossParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBossPtr pGameObjectBoss;

	//Create GameObject
	pGameObjectBoss = GameObjectBossPtr(new GameObjectBoss(tGameObjectBossParameters.name));
	pGameObjectBoss->setMaxUpdateRadium(tGameObjectBossParameters.mMaxUpdateRadium);
	pGameObjectBoss->setParentNest(tGameObjectBossParameters.parentNest);
	pGameObjectBoss->setSpawnProbability(tGameObjectBossParameters.spawnProbability);
	pGameObjectBoss->setMaxRenderRadium(tGameObjectBossParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectBoss->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(
		pGameObjectBoss,
		tGameObjectBossParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectBoss->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBoss,tGameObjectBossParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBoss->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBoss->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectBoss->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectBossParameters.dreamsName,
		pGameObjectBoss,tGameObjectBossParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectBoss->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectBoss->getLogicComponentEnemy()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectBoss->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectBossParameters.nightmaresName,
		pGameObjectBoss,tGameObjectBossParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectBoss->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectBoss->getLogicComponentEnemy()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectBoss->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectBoss,
		tGameObjectBossParameters.tPhysicsComponentCharacterParameters,
		pGameObjectBoss->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectBoss->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectBoss->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectBoss;
}


GameObjectEyePtr GameObjectFactory::createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectEyePtr pGameObjectEye;

	//Create GameObject
	pGameObjectEye = GameObjectEyePtr(new GameObjectEye(tGameObjectEyeParameters.name));
	pGameObjectEye->setMaxUpdateRadium(tGameObjectEyeParameters.mMaxUpdateRadium);
	pGameObjectEye->setParentNest(tGameObjectEyeParameters.parentNest);
	pGameObjectEye->setSpawnProbability(tGameObjectEyeParameters.spawnProbability);
	pGameObjectEye->setMaxRenderRadium(tGameObjectEyeParameters.mMaxRenderRadium);

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
		pGameObjectEye,tGameObjectEyeParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectEye->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectEye->getLogicComponentEnemy()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectEye->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectEye,
		tGameObjectEyeParameters.tPhysicsComponentCharacterParameters,
		pGameObjectEye->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectEye->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectEye->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectEye;
}

GameObjectFogPtr GameObjectFactory::createGameObjectFog(TGameObjectFogParameters tGameObjectFogParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectFogPtr pGameObjectFog;

	//Create GameObject
	pGameObjectFog = GameObjectFogPtr(new GameObjectFog(tGameObjectFogParameters.name));
	pGameObjectFog->setMaxUpdateRadium(tGameObjectFogParameters.mMaxUpdateRadium);
	pGameObjectFog->setParentNest(tGameObjectFogParameters.parentNest);
	pGameObjectFog->setSpawnProbability(tGameObjectFogParameters.spawnProbability);
	pGameObjectFog->setMaxRenderRadium(tGameObjectFogParameters.mMaxRenderRadium);

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
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectFog->getLogicComponent()->existsInDreams(),
		pGameObjectFog->getLogicComponent()->existsInNightmares()));

		//Create RenderComponentEntity Nightmares
		pGameObjectFog->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.nightmaresName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectFog->getLogicComponent()->existsInDreams(),
		pGameObjectFog->getLogicComponent()->existsInNightmares()));

	}
	else if(pGameObjectFog->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		pGameObjectFog->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.dreamsName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectFog->getLogicComponent()->existsInDreams(),
		pGameObjectFog->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectFog->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectFog->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectFogParameters.nightmaresName,
			pGameObjectFog,tGameObjectFogParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectFog->getLogicComponent()->existsInDreams(),
		pGameObjectFog->getLogicComponent()->existsInNightmares()));
	}

	//Add reference to this
	pGameObjectFog->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectFog->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectFog;
}

GameObjectFlashLightPtr GameObjectFactory::createGameObjectFlashLight(TGameObjectFlashLightParameters tGameObjectFlashLightParameters, 
	GameWorldManagerPtr gameWorldMgr, RenderSubsystemPtr renderSubsystem)
{
	GameObjectFlashLightPtr pGameObjectFlashLight;

	//Create GameObject
	pGameObjectFlashLight = GameObjectFlashLightPtr(new GameObjectFlashLight(tGameObjectFlashLightParameters.name,renderSubsystem));
	pGameObjectFlashLight->setMaxUpdateRadium(tGameObjectFlashLightParameters.mMaxUpdateRadium);
	pGameObjectFlashLight->setParentNest(tGameObjectFlashLightParameters.parentNest);
	pGameObjectFlashLight->setSpawnProbability(tGameObjectFlashLightParameters.spawnProbability);
	pGameObjectFlashLight->setMaxRenderRadium(tGameObjectFlashLightParameters.mMaxRenderRadium);

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

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->FLASH_LIGHT_ATTACK;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectFlashLight->setRenderComponentParticleSystemAttack(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectFlashLight,
			tRenderComponentParticleSystemParameters,
			pGameObjectFlashLight->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->FLASH_LIGHT_ATTACK_RED;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectFlashLight->setRenderComponentParticleSystemAttackRed(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectFlashLight,
			tRenderComponentParticleSystemParameters,
			pGameObjectFlashLight->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->FLASH_LIGHT_ATTACK_GREEN;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectFlashLight->setRenderComponentParticleSystemAttackGreen(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectFlashLight,
			tRenderComponentParticleSystemParameters,
			pGameObjectFlashLight->getRenderComponentPositional()));
	
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->FLASH_LIGHT_ATTACK_BLUE;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectFlashLight->setRenderComponentParticleSystemAttackBlue(
		mComponentFactory->createRenderComponentParticleSystem(
			pGameObjectFlashLight,
			tRenderComponentParticleSystemParameters,
			pGameObjectFlashLight->getRenderComponentPositional()));

	//Create RenderComponentInitial
	pGameObjectFlashLight->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectFlashLight->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectFlashLight->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectFlashLightParameters.name,
		pGameObjectFlashLight,tGameObjectFlashLightParameters.tRenderComponentEntityParameters,
		pGameObjectFlashLight->getLogicComponent()->existsInDreams(),
		pGameObjectFlashLight->getLogicComponent()->existsInNightmares()));
	pGameObjectFlashLight->getRenderComponentEntity()->setVisible(false);

	////Create PhysicsComponent
	pGameObjectFlashLight->setPhysicsComponentVolumeConvex(
		mComponentFactory->createPhysicsComponentVolumeConvex(
		pGameObjectFlashLight, 
		tGameObjectFlashLightParameters.tPhysicsComponentVolumeConvexParameters, 
		pGameObjectFlashLight->getRenderComponentPositional()));

	pGameObjectFlashLight->setPhysicsComponentWeapon(
		mComponentFactory->createPhysicsComponentWeapon(
		pGameObjectFlashLight,
		tGameObjectFlashLightParameters.tPhysicsComponentWeaponParameters,
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

	pGameObjectFlashLight->setConeEntity(
		mComponentFactory->createRenderComponentEntity(
		tGameObjectFlashLightParameters.name+"#lightCone",
		pGameObjectFlashLight,
		tGameObjectFlashLightParameters.tConeParams,
		pGameObjectFlashLight->getLogicComponent()->existsInDreams(),
		pGameObjectFlashLight->getLogicComponent()->existsInNightmares()));
	pGameObjectFlashLight->getConeEntity()->setVisible(false);

	TRenderComponentDecalParameters decalParams;
	decalParams.filterTextureName=FLASHLIGHT_DECAL_FILTER_TEX_NAME;
	decalParams.projectorName=FLASHLIGHT_DECAL_PROJECTOR_NAME;
	decalParams.projectorNode=pGameObjectFlashLight->getRenderComponentPositional()->getSceneNode();
	decalParams.projectorOffset=Ogre::Vector3::ZERO;
	decalParams.textureName=FLASHLIGHT_DECAL_TEX_NAME;
	decalParams.tintColour=pGameObjectFlashLight->getColour();

	pGameObjectFlashLight->setDecalComponent(
		mComponentFactory->createRenderComponentDecal(
		pGameObjectFlashLight,
		decalParams,renderSubsystem->getSceneManager()
		));

	//Add reference to this
	pGameObjectFlashLight->setGameWorldManager(gameWorldMgr);
	pGameObjectFlashLight->hide();
	pGameObjectFlashLight->switchOff();

	std::string scriptFile="";
	pGameObjectFlashLight->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectFlashLight;
}

GameObjectHeartPtr GameObjectFactory::createGameObjectHeart(TGameObjectHeartParameters tGameObjectHeartParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectHeartPtr pGameObjectHeart;

	//Create GameObject
	pGameObjectHeart = GameObjectHeartPtr(new GameObjectHeart(tGameObjectHeartParameters.name));
	pGameObjectHeart->setMaxUpdateRadium(tGameObjectHeartParameters.mMaxUpdateRadium);
	pGameObjectHeart->setParentNest(tGameObjectHeartParameters.parentNest);
	pGameObjectHeart->setSpawnProbability(tGameObjectHeartParameters.spawnProbability);
	pGameObjectHeart->setMaxRenderRadium(tGameObjectHeartParameters.mMaxRenderRadium);

	if (!tGameObjectHeartParameters.parentNest.empty())
	{
		gameWorldMgr->addNestLink(pGameObjectHeart->getName(),tGameObjectHeartParameters.parentNest);
	}

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
		pGameObjectHeart,tGameObjectHeartParameters.tRenderComponentEntityParameters,
		pGameObjectHeart->getLogicComponentItem()->existsInDreams(),
		pGameObjectHeart->getLogicComponentItem()->existsInNightmares()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->HEART_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectHeart->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectHeart,
		tRenderComponentParticleSystemParameters,
		pGameObjectHeart->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectHeart->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectHeart, 
		tGameObjectHeartParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectHeart->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectHeart->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectHeart->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectHeart;
}

GameObjectItem1UPPtr GameObjectFactory::createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectItem1UPPtr pGameObjectItem1UP;

	//Create GameObject
	pGameObjectItem1UP = GameObjectItem1UPPtr(new GameObjectItem1UP(tGameObjectItem1UPParameters.name));
	pGameObjectItem1UP->setMaxUpdateRadium(tGameObjectItem1UPParameters.mMaxUpdateRadium);
	pGameObjectItem1UP->setParentNest(tGameObjectItem1UPParameters
		.parentNest);
	pGameObjectItem1UP->setSpawnProbability(tGameObjectItem1UPParameters.spawnProbability);
	pGameObjectItem1UP->setMaxRenderRadium(tGameObjectItem1UPParameters.mMaxRenderRadium);


	if (!tGameObjectItem1UPParameters.parentNest.empty())
	{
		gameWorldMgr->addNestLink(pGameObjectItem1UP->getName(),tGameObjectItem1UPParameters.parentNest);
	}

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
		pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters,
		pGameObjectItem1UP->getLogicComponentItem()->existsInDreams(),
		pGameObjectItem1UP->getLogicComponentItem()->existsInNightmares()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->TOY_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectItem1UP->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectItem1UP,
		tRenderComponentParticleSystemParameters,
		pGameObjectItem1UP->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectItem1UP->setPhysicsComponentVolumeBox(
		mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectItem1UP, 
		tGameObjectItem1UPParameters.tPhysicsComponentVolumeBoxParameters, 
		pGameObjectItem1UP->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectItem1UP->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectItem1UP->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectItem1UP;
}

GameObjectItemMaxHPPtr GameObjectFactory::createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectItemMaxHPPtr pGameObjectItemMaxHP;

	//Create GameObject
	pGameObjectItemMaxHP = GameObjectItemMaxHPPtr(new GameObjectItemMaxHP(tGameObjectItemMaxHPParameters.name));
	pGameObjectItemMaxHP->setMaxUpdateRadium(tGameObjectItemMaxHPParameters.mMaxUpdateRadium);
	pGameObjectItemMaxHP->setParentNest(tGameObjectItemMaxHPParameters.parentNest);
	pGameObjectItemMaxHP->setSpawnProbability(tGameObjectItemMaxHPParameters.spawnProbability);
	pGameObjectItemMaxHP->setMaxRenderRadium(tGameObjectItemMaxHPParameters.mMaxRenderRadium);

	if (!tGameObjectItemMaxHPParameters.parentNest.empty())
	{
		gameWorldMgr->addNestLink(pGameObjectItemMaxHP->getName(),tGameObjectItemMaxHPParameters.parentNest);
	}

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
		pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters,
		pGameObjectItemMaxHP->getLogicComponentItem()->existsInDreams(),
		pGameObjectItemMaxHP->getLogicComponentItem()->existsInNightmares()));

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->BAG_HEARTS_FOUNTAIN;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectItemMaxHP->setRenderComponentParticleSystemHeartsFountain(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectItemMaxHP,
		tRenderComponentParticleSystemParameters,
		pGameObjectItemMaxHP->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->BAG_HEARTS_FOUNTAIN_DOUBLE;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectItemMaxHP->setRenderComponentParticleSystemHeartsFountainDouble(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectItemMaxHP,
		tRenderComponentParticleSystemParameters,
		pGameObjectItemMaxHP->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->BAG_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectItemMaxHP->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectItemMaxHP,
		tRenderComponentParticleSystemParameters,
		pGameObjectItemMaxHP->getRenderComponentPositional()));

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

	std::string scriptFile="";
	pGameObjectItemMaxHP->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectItemMaxHP;
}

GameObjectLightPtr GameObjectFactory::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(tGameObjectLightParameters.name));
	pGameObjectLight->setMaxUpdateRadium(tGameObjectLightParameters.mMaxUpdateRadium);
	pGameObjectLight->setParentNest(tGameObjectLightParameters.parentNest);
	pGameObjectLight->setSpawnProbability(tGameObjectLightParameters.spawnProbability);
	pGameObjectLight->setMaxRenderRadium(tGameObjectLightParameters.mMaxRenderRadium);

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

	std::string scriptFile="";
	pGameObjectLight->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectLight;
}

GameObjectMagicClockPtr GameObjectFactory::createGameObjectMagicClock(TGameObjectMagicClockParameters tGameObjectMagicClockParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectMagicClockPtr pGameObjectMagicClock;

	//Create GameObject
	pGameObjectMagicClock = GameObjectMagicClockPtr(new GameObjectMagicClock(tGameObjectMagicClockParameters.name));
	pGameObjectMagicClock->setMaxUpdateRadium(tGameObjectMagicClockParameters.mMaxUpdateRadium);
	pGameObjectMagicClock->setParentNest(tGameObjectMagicClockParameters.parentNest);
	pGameObjectMagicClock->setSpawnProbability(tGameObjectMagicClockParameters.spawnProbability);
	pGameObjectMagicClock->setMaxRenderRadium(tGameObjectMagicClockParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectMagicClock->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectMagicClock,
		tGameObjectMagicClockParameters.tLogicComponentParameters));

	//Add reference to this
	pGameObjectMagicClock->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectMagicClock->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectMagicClock;
}
GameObjectNestPtr GameObjectFactory::createGameObjectNest(TGameObjectNestParameters 
														  params, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectNestPtr pGameObjectNest;

	//Create GameObject
	pGameObjectNest= GameObjectNestPtr(new GameObjectNest(params.name));
	pGameObjectNest->setMaxUpdateRadium(params.mMaxUpdateRadium);
	pGameObjectNest->setParentNest(params.parentNest);
	pGameObjectNest->setSpawnProbability(params.spawnProbability);
	pGameObjectNest->setMaxRenderRadium(params.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectNest->setLogicComponent(
		mComponentFactory->createLogicComponentProp(
		pGameObjectNest,
		params.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectNest->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectNest,params.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectNest->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectNest->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectNest->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(params.dreamsName,
		pGameObjectNest,params.tRenderComponentEntityParameters,
		pGameObjectNest->getLogicComponent()->existsInDreams(),
		pGameObjectNest->getLogicComponent()->existsInNightmares()));
	//Create PhysicsComponent
	pGameObjectNest->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectNest,
		params.tPhysicsComponentCharacterParameters,
		pGameObjectNest->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectNest->setGameWorldManager(gameWorldMgr);
	
	std::string scriptFile="";
	pGameObjectNest->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectNest;
}

GameObjectNightGoblinPtr GameObjectFactory::createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectNightGoblinPtr pGameObjectNightGoblin;

	//Create GameObject
	pGameObjectNightGoblin = GameObjectNightGoblinPtr(new GameObjectNightGoblin(tGameObjectNightGoblinParameters.name));
	pGameObjectNightGoblin->setMaxUpdateRadium(tGameObjectNightGoblinParameters.mMaxUpdateRadium);
	pGameObjectNightGoblin->setParentNest(tGameObjectNightGoblinParameters.parentNest);
	pGameObjectNightGoblin->setSpawnProbability(tGameObjectNightGoblinParameters.spawnProbability);
	pGameObjectNightGoblin->setMaxRenderRadium(tGameObjectNightGoblinParameters.mMaxRenderRadium);

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
		pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectNightGoblin->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectNightGoblin->getLogicComponentEnemy()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectNightGoblin->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectNightGoblinParameters.nightmaresName,
		pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectNightGoblin->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectNightGoblin->getLogicComponentEnemy()->existsInNightmares()));

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
	pGameObjectOny->setMaxUpdateRadium(tGameObjectOnyParameters.mMaxUpdateRadium);
	pGameObjectOny->setParentNest(tGameObjectOnyParameters.parentNest);
	pGameObjectOny->setSpawnProbability(tGameObjectOnyParameters.spawnProbability);
	pGameObjectOny->setMaxRenderRadium(tGameObjectOnyParameters.mMaxRenderRadium);

	pGameObjectOny->setRunParticlesMin(tGameObjectOnyParameters.mRunParticlesMin);
	pGameObjectOny->setRunParticlesMax(tGameObjectOnyParameters.mRunParticlesMax);
	pGameObjectOny->setRunParticlesElapsed(-1.0);
	pGameObjectOny->setRunParticlesNextInterval(-1.0);

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

	//Trajectory component for cutscenes
	pGameObjectOny->setTrajectoryComponent(mComponentFactory->createTrajectoryComponent(
		pGameObjectOny,
		tGameObjectOnyParameters.tTrajectoryComponentParameters));

	//Create RenderComponenetParticleSystem

	//NOTE: Refactored out for readability
	createOnyParticleSystems(pGameObjectOny);
	
	//Create RenderComponentEntity
	pGameObjectOny->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(
			tGameObjectOnyParameters.name,
			pGameObjectOny,
			tGameObjectOnyParameters.tRenderComponentEntityParameters,
		pGameObjectOny->getLogicComponentOny()->existsInDreams(),
		pGameObjectOny->getLogicComponentOny()->existsInNightmares()));

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

	//Add reference to this
	pGameObjectOny->setGameWorldManager(gameWorldMgr);
	
	std::string scriptFile="";
	pGameObjectOny->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return pGameObjectOny;
}
void GameObjectFactory::createOnyParticleSystems(GameObjectOnyPtr onyPtr)
{
	ParticleTemplates* templates = ParticleTemplates::getInstance();
	std::string templateNames[]={templates->ONY_LAND_DREAMS,
		templates->ONY_LAND_NIGHTMARES,
		templates->ONY_LAND_WAVE,
		templates->ONY_LAND_WATER_WAVE,
		templates->ONY_LAND_WATER_DROPS,
		templates->ONY_RUN_GRASS,
		templates->ONY_RUN_SAND,
		templates->ONY_RUN_SURPRISE,
		templates->ONY_RUN_WATER
	};
	
	/*
		Range through the enums. 
		The last part of the for-statement just invokes a code-replacement macro that increments i;
	*/
	for (GameObjectOny::OnyParticleSystemID i = GameObjectOny::ONY_PS_MIN_ID; 
		i<=GameObjectOny::ONY_PS_MAX_ID;
		INC_ENUM(GameObjectOny::OnyParticleSystemID,i))
	{
		createOnyParticleSystem(onyPtr, i,
			templateNames[i],true,
			templates->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE,
			Ogre::RENDER_QUEUE_MAIN);
	}

}
void GameObjectFactory::createOnyParticleSystem(GameObjectOnyPtr onyPtr, 
	GameObjectOny::OnyParticleSystemID id,const std::string& templateName,
	bool attached, int poolsize,Ogre::uint8 queueID)
{
	TRenderComponentParticleSystemParameters psParams;

	psParams.templateName = templateName;
	psParams.attached = attached;
	psParams.poolSize = poolsize;
	psParams.queueID=queueID;
	onyPtr->addParticleSystem(id,mComponentFactory->createRenderComponentParticleSystem(
		onyPtr,
		psParams,
		onyPtr->getRenderComponentPositional()));
}

GameObjectParticleSystemPtr GameObjectFactory::createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectParticleSystemPtr pGameObjectParticleSystem;	

	//Create GameObject
	pGameObjectParticleSystem = GameObjectParticleSystemPtr(new GameObjectParticleSystem(tGameObjectParticleSystemParameters.name));
	pGameObjectParticleSystem->setMaxUpdateRadium(tGameObjectParticleSystemParameters.mMaxUpdateRadium);
	pGameObjectParticleSystem->setParentNest(tGameObjectParticleSystemParameters.parentNest);
	pGameObjectParticleSystem->setSpawnProbability(tGameObjectParticleSystemParameters.spawnProbability);
	pGameObjectParticleSystem->setMaxRenderRadium(tGameObjectParticleSystemParameters.mMaxRenderRadium);

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
	pGameObjectPillow->setMaxUpdateRadium(tGameObjectPillowParameters.mMaxUpdateRadium);
	pGameObjectPillow->setParentNest(tGameObjectPillowParameters.parentNest);
	pGameObjectPillow->setSpawnProbability(tGameObjectPillowParameters.spawnProbability);
	pGameObjectPillow->setMaxRenderRadium(tGameObjectPillowParameters.mMaxRenderRadium);

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
		pGameObjectPillow,tGameObjectPillowParameters.tRenderComponentEntityParameters,
		pGameObjectPillow->getLogicComponent()->existsInDreams(),
		pGameObjectPillow->getLogicComponent()->existsInNightmares()));
	pGameObjectPillow->getRenderComponentEntity()->setVisible(false);

	pGameObjectPillow->setPhysicsComponentWeapon(
		mComponentFactory->createPhysicsComponentWeapon(
		pGameObjectPillow,
		tGameObjectPillowParameters.tPhysicsComponentWeaponParameters,
		pGameObjectPillow->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectPillow->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectPillow->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}	
	return pGameObjectPillow;
}

GameObjectPlanePtr GameObjectFactory::createGameObjectPlane(TGameObjectPlaneParameters tGameObjectPlaneParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPlanePtr pGameObjectPlane;

	//Create GameObject
	pGameObjectPlane = GameObjectPlanePtr(new GameObjectPlane(tGameObjectPlaneParameters.name));
	pGameObjectPlane->setMaxUpdateRadium(tGameObjectPlaneParameters.mMaxUpdateRadium);
	pGameObjectPlane->setParentNest(tGameObjectPlaneParameters.parentNest);
	pGameObjectPlane->setSpawnProbability(tGameObjectPlaneParameters.spawnProbability);
	pGameObjectPlane->setMaxRenderRadium(tGameObjectPlaneParameters.mMaxRenderRadium);

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

	std::string scriptFile="";
	pGameObjectPlane->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectPlane;
}

GameObjectPlataformPtr GameObjectFactory::createGameObjectPlataform(TGameObjectPlataformParameters tGameObjectPlataformParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPlataformPtr pGameObjectPlataform;

	//Create GameObject
	pGameObjectPlataform = GameObjectPlataformPtr(new GameObjectPlataform(tGameObjectPlataformParameters.name));
	pGameObjectPlataform->setMaxUpdateRadium(tGameObjectPlataformParameters.mMaxUpdateRadium);
	pGameObjectPlataform->setParentNest(tGameObjectPlataformParameters.parentNest);
	pGameObjectPlataform->setSpawnProbability(tGameObjectPlataformParameters.spawnProbability);
	pGameObjectPlataform->setMaxRenderRadium(tGameObjectPlataformParameters.mMaxRenderRadium);

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
			pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectPlataform->getLogicComponent()->existsInDreams(),
		pGameObjectPlataform->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectPlataform->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectPlataform->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectPlataformParameters.nightmaresName,
			pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectPlataform->getLogicComponent()->existsInDreams(),
		pGameObjectPlataform->getLogicComponent()->existsInNightmares()));
	}
	//Create PhysicsComponent
	pGameObjectPlataform->setPhysicsComponentComplexConvex(mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectPlataform,
		tGameObjectPlataformParameters.tPhysicsComponentComplexConvexParameters,
		pGameObjectPlataform->getRenderComponentPositional()));

	//Create TrajectoryComponent
	pGameObjectPlataform->setTrajectoryComponent(mComponentFactory->createTrajectoryComponent(
		pGameObjectPlataform,
		tGameObjectPlataformParameters.tTrajectoryComponentParameters));
	pGameObjectPlataform->activateTrajectory();

	//Add reference to this
	pGameObjectPlataform->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectPlataform->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectPlataform;
}

GameObjectPortalPtr GameObjectFactory::createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectPortalPtr pGameObjectPortal;

	//Create GameObject
	pGameObjectPortal = GameObjectPortalPtr(new GameObjectPortal(tGameObjectPortalParameters.name));
	pGameObjectPortal->setMaxUpdateRadium(tGameObjectPortalParameters.mMaxUpdateRadium);
	pGameObjectPortal->setParentNest(tGameObjectPortalParameters.parentNest);
	pGameObjectPortal->setSpawnProbability(tGameObjectPortalParameters.spawnProbability);
	pGameObjectPortal->setMaxRenderRadium(tGameObjectPortalParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectPortal->setLogicComponentProp(
		mComponentFactory->createLogicComponentProp(
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

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->PORTAL_CHANGE_WORLD_IDLE;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectPortal->setRenderComponentParticleSystemChangeWorldIdle(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectPortal,
		tRenderComponentParticleSystemParameters,
		pGameObjectPortal->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->PORTAL_CHANGE_WORLD_CHANGING;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectPortal->setRenderComponentParticleSystemChangeWorldChanging(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectPortal,
		tRenderComponentParticleSystemParameters,
		pGameObjectPortal->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectPortal->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectPortalParameters.dreamsName,
		pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectPortal->getLogicComponentProp()->existsInDreams(),
		pGameObjectPortal->getLogicComponentProp()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectPortal->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectPortalParameters.nightmaresName,
		pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectPortal->getLogicComponentProp()->existsInDreams(),
		pGameObjectPortal->getLogicComponentProp()->existsInNightmares()));

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

	std::string scriptFile="";
	pGameObjectPortal->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectPortal;
}

GameObjectProvisionalEntityPtr GameObjectFactory::createGameObjectProvisionalEntity(
	TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters,
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity;

	//Create GameObject
	pGameObjectProvisionalEntity = GameObjectProvisionalEntityPtr(new GameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters.name));
	pGameObjectProvisionalEntity->setMaxUpdateRadium(tGameObjectProvisionalEntityParameters.mMaxUpdateRadium);
	pGameObjectProvisionalEntity->setParentNest(tGameObjectProvisionalEntityParameters.parentNest);
	pGameObjectProvisionalEntity->setSpawnProbability(tGameObjectProvisionalEntityParameters.spawnProbability);
	pGameObjectProvisionalEntity->setMaxRenderRadium(tGameObjectProvisionalEntityParameters.mMaxRenderRadium);

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
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectProvisionalEntity->getLogicComponent()->existsInDreams(),
		pGameObjectProvisionalEntity->getLogicComponent()->existsInNightmares()));
	}
	if(pGameObjectProvisionalEntity->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectProvisionalEntity->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.nightmaresName,
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectProvisionalEntity->getLogicComponent()->existsInDreams(),
		pGameObjectProvisionalEntity->getLogicComponent()->existsInNightmares()));
	}

	// Add a reference to this
	pGameObjectProvisionalEntity->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectProvisionalEntity->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectProvisionalEntity;
}

GameObjectScaredPlantPtr GameObjectFactory::createGameObjectScaredPlant(TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectScaredPlantPtr pGameObjectScaredPlant;

	//Create GameObject
	pGameObjectScaredPlant = GameObjectScaredPlantPtr(new GameObjectScaredPlant(tGameObjectScaredPlantParameters.name));
	pGameObjectScaredPlant->setMaxUpdateRadium(tGameObjectScaredPlantParameters.mMaxUpdateRadium);
	pGameObjectScaredPlant->setParentNest(tGameObjectScaredPlantParameters.parentNest);
	pGameObjectScaredPlant->setSpawnProbability(tGameObjectScaredPlantParameters.spawnProbability);
	pGameObjectScaredPlant->setMaxRenderRadium(tGameObjectScaredPlantParameters.mMaxRenderRadium);

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
		pGameObjectScaredPlant,tGameObjectScaredPlantParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectScaredPlant->getLogicComponent()->existsInDreams(),
		pGameObjectScaredPlant->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectScaredPlant->setPhysicsComponentSimpleBox(mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectScaredPlant,
		tGameObjectScaredPlantParameters.tPhysicsComponentSimpleBoxParameters,
		pGameObjectScaredPlant->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScaredPlant->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectScaredPlant->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectScaredPlant;
}

GameObjectScenePtr GameObjectFactory::createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters, 
	GameWorldManagerPtr gameWorldMgr)
{

	GameObjectScenePtr pGameObjectScene;

	//Create GameObject
	pGameObjectScene = GameObjectScenePtr(new GameObjectScene(tGameObjectSceneParameters.name));
	pGameObjectScene->setMaxUpdateRadium(tGameObjectSceneParameters.mMaxUpdateRadium);
	pGameObjectScene->setParentNest(tGameObjectSceneParameters.parentNest);
	pGameObjectScene->setSpawnProbability(tGameObjectSceneParameters.spawnProbability);
	pGameObjectScene->setMaxRenderRadium(tGameObjectSceneParameters.mMaxRenderRadium);

	//Create RenderComponentViewport
	pGameObjectScene->setRenderComponentScene(mComponentFactory->createRenderComponentScene(
		pGameObjectScene,tGameObjectSceneParameters.tRenderComponentSceneParameters));

	// Add a reference to this
	pGameObjectScene->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectScene->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectScene;

}

GameObjectScepterPtr GameObjectFactory::createGameObjectScepter(TGameObjectScepterParameters tGameObjectScepterParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectScepterPtr pGameObjectScepter;

	//Create GameObject
	pGameObjectScepter = GameObjectScepterPtr(new GameObjectScepter(tGameObjectScepterParameters.name));
	pGameObjectScepter->setMaxUpdateRadium(tGameObjectScepterParameters.mMaxUpdateRadium);
	pGameObjectScepter->setParentNest(tGameObjectScepterParameters.parentNest);
	pGameObjectScepter->setSpawnProbability(tGameObjectScepterParameters.spawnProbability);
	pGameObjectScepter->setMaxRenderRadium(tGameObjectScepterParameters.mMaxRenderRadium);

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
		pGameObjectScepter,tGameObjectScepterParameters.tRenderComponentEntityParameters,
		pGameObjectScepter->getLogicComponent()->existsInDreams(),
		pGameObjectScepter->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectScepter->setPhysicsComponentSimpleCapsule(
		mComponentFactory->createPhysicsComponentSimpleCapsule(
		pGameObjectScepter, 
		tGameObjectScepterParameters.tPhysicsComponentSimpleCapsuleParameters, 
		pGameObjectScepter->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScepter->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectScepter->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectScepter;
}

GameObjectSkyBodyPtr GameObjectFactory::createGameObjectSkyBody(TGameObjectSkyBodyParameters params,
	GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraManager, Ogre::SceneManager* sceneManager)
{
	GameObjectSkyBodyPtr gameObject;

	//Create GameObject
	gameObject = GameObjectSkyBodyPtr(new GameObjectSkyBody(params.name));
	gameObject->setMaxUpdateRadium(params.mMaxUpdateRadium);
	gameObject->setParentNest(params.parentNest);
	gameObject->setSpawnProbability(params.spawnProbability);
	gameObject->setMaxRenderRadium(params.mMaxRenderRadium);

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
				gameObject,params.tRenderComponentEntityDreamsParameters,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
			gameObject->setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr());
		}
		else
		{
			gameObject->setRenderComponentEntityDreams(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetDreams(mComponentFactory->createRenderComponentBillboardSet(
				params.dreamsName,
				gameObject,
				params.bbsDreamsParams,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}
		//gameObject->setLightDreams(mComponentFactory->createRenderComponentLight(
		//	params.dreamsName+"#light",
		//		gameObject,
		//		params.lightDreamsParams));

		if (gameObject->isUsingEntityNightmares())
		{
			gameObject->setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr());
			//Create RenderComponentEntity Nightmares
			gameObject->setRenderComponentEntityNightmares(
				mComponentFactory->createRenderComponentEntity(params.nightmaresName,
				gameObject,params.tRenderComponentEntityNightmaresParameters,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}
		else
		{
			gameObject->setRenderComponentEntityNightmares(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetNightmares(mComponentFactory->createRenderComponentBillboardSet(
				params.nightmaresName,
				gameObject,
				params.bbsNightmaresParams,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}

		//gameObject->setLightNightmares(mComponentFactory->createRenderComponentLight(
		//	params.nightmaresName+"#light",
		//	gameObject,
		//	params.lightNightmaresParams));
	}
	else if(gameObject->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntity Dreams
		if (gameObject->isUsingEntityDreams())
		{
			//Create RenderComponentEntity Dreams
			gameObject->setRenderComponentEntityDreams(
				mComponentFactory->createRenderComponentEntity(params.dreamsName,
				gameObject,params.tRenderComponentEntityDreamsParameters,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));

			gameObject->setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr());
		}
		else
		{
			gameObject->setRenderComponentEntityDreams(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetDreams(mComponentFactory->createRenderComponentBillboardSet(
				params.dreamsName,
				gameObject,
				params.bbsDreamsParams,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}
		//gameObject->setLightDreams(mComponentFactory->createRenderComponentLight(
		//	params.dreamsName,
		//	gameObject,
		//	params.lightDreamsParams));
	}
	else if(gameObject->getLogicComponent()->existsInNightmares())
	{
		if (gameObject->isUsingEntityNightmares())
		{
			gameObject->setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr());
			//Create RenderComponentEntity Nightmares
			gameObject->setRenderComponentEntityNightmares(
				mComponentFactory->createRenderComponentEntity(params.nightmaresName,
				gameObject,params.tRenderComponentEntityNightmaresParameters,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}
		else
		{
			gameObject->setRenderComponentEntityNightmares(RenderComponentEntityPtr());				
			gameObject->setRenderComponentBillboardSetNightmares(mComponentFactory->createRenderComponentBillboardSet(
				params.nightmaresName,
				gameObject,
				params.bbsNightmaresParams,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));
		}

		//gameObject->setLightNightmares(mComponentFactory->createRenderComponentLight(
		//	params.nightmaresName,
		//	gameObject,
		//	params.lightNightmaresParams));	
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
	gameObject->initLensFlare(sceneManager,params.lensFlareScale);

	//Add reference to this
	gameObject->setGameWorldManager(gameWorldMgr);
	
	std::string scriptFile="";
	gameObject->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	//Add Object to GameWorldManager
	return gameObject;
}

GameObjectSnakeCreeperPtr GameObjectFactory::createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSnakeCreeperPtr pGameObjectSnakeCreeper;

	//Create GameObject
	pGameObjectSnakeCreeper = GameObjectSnakeCreeperPtr(new GameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters.name));
	pGameObjectSnakeCreeper->setMaxUpdateRadium(tGameObjectSnakeCreeperParameters.mMaxUpdateRadium);
	pGameObjectSnakeCreeper->setParentNest(tGameObjectSnakeCreeperParameters.parentNest);
	pGameObjectSnakeCreeper->setSpawnProbability(tGameObjectSnakeCreeperParameters.spawnProbability);
	pGameObjectSnakeCreeper->setMaxRenderRadium(tGameObjectSnakeCreeperParameters.mMaxRenderRadium);

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
			pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInNightmares()));
	}
	if(pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntity Nightmares
		pGameObjectSnakeCreeper->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectSnakeCreeperParameters.nightmaresName,
			pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectSnakeCreeper->getLogicComponentEnemy()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectSnakeCreeper->setPhysicsComponentCharacter(
		mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectSnakeCreeper, 
		tGameObjectSnakeCreeperParameters.tPhysicsComponentCharacterParameters, 
		pGameObjectSnakeCreeper->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectSnakeCreeper->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectSnakeCreeper->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectSnakeCreeper;
}
GameObjectSoundPtr GameObjectFactory::createGameObjectSound(TGameObjectSoundParameters params, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSoundPtr sound = GameObjectSoundPtr(new GameObjectSound(params.name));
	sound->setMaxUpdateRadium(params.mMaxUpdateRadium);
	sound->setParentNest(params.parentNest);
	sound->setSpawnProbability(params.spawnProbability);
	sound->setMaxRenderRadium(params.mMaxRenderRadium);

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
	std::string scriptFile="";
	sound->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return sound;
}

GameObjectStoryBookPtr GameObjectFactory::createGameObjectStoryBook(TGameObjectStoryBookParameters tGameObjectStoryBookParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectStoryBookPtr pGameObjectStoryBook;

	//Create GameObject
	pGameObjectStoryBook = GameObjectStoryBookPtr(new GameObjectStoryBook(tGameObjectStoryBookParameters.name));
	pGameObjectStoryBook->setMaxUpdateRadium(tGameObjectStoryBookParameters.mMaxUpdateRadium);
	pGameObjectStoryBook->setParentNest(tGameObjectStoryBookParameters.parentNest);
	pGameObjectStoryBook->setSpawnProbability(tGameObjectStoryBookParameters.spawnProbability);
	pGameObjectStoryBook->setMaxRenderRadium(tGameObjectStoryBookParameters.mMaxRenderRadium);

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
		pGameObjectStoryBook,tGameObjectStoryBookParameters.tRenderComponentEntityParameters,
		pGameObjectStoryBook->getLogicComponentItem()->existsInDreams(),
		pGameObjectStoryBook->getLogicComponentItem()->existsInNightmares()));

	//pGameObjectStoryBook->getRenderComponentEntity()->prepareForNormalMapping();

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->STORY_BOOK_HALO;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectStoryBook->setRenderComponentParticleSystemHalo(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectStoryBook,
		tRenderComponentParticleSystemParameters,
		pGameObjectStoryBook->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->STORY_BOOK_STARS_CLOUD;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectStoryBook->setRenderComponentParticleSystemStarsCloud(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectStoryBook,
		tRenderComponentParticleSystemParameters,
		pGameObjectStoryBook->getRenderComponentPositional()));

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

	std::string scriptFile="";
	pGameObjectStoryBook->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectStoryBook;
}

GameObjectTentetiesoPtr GameObjectFactory::createGameObjectTentetieso(TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTentetiesoPtr pGameObjectTentetieso;

	//Create GameObject
	pGameObjectTentetieso = GameObjectTentetiesoPtr(new GameObjectTentetieso(tGameObjectTentetiesoParameters.name));
	pGameObjectTentetieso->setMaxUpdateRadium(tGameObjectTentetiesoParameters.mMaxUpdateRadium);
	pGameObjectTentetieso->setParentNest(tGameObjectTentetiesoParameters.parentNest);
	pGameObjectTentetieso->setSpawnProbability(tGameObjectTentetiesoParameters.spawnProbability);
	pGameObjectTentetieso->setMaxRenderRadium(tGameObjectTentetiesoParameters.mMaxRenderRadium);

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
		pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTentetieso->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTentetieso->getLogicComponentEnemy()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectTentetieso->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTentetiesoParameters.nightmaresName,
		pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTentetieso->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTentetieso->getLogicComponentEnemy()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTentetieso->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectTentetieso,
		tGameObjectTentetiesoParameters.tPhysicsComponentCharacterParameters,
		pGameObjectTentetieso->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTentetieso->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTentetieso->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTentetieso;
}

GameObjectTerrainConvexPtr GameObjectFactory::createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTerrainConvexPtr pGameObjectTerrainConvex;

	//Create GameObject
	pGameObjectTerrainConvex = GameObjectTerrainConvexPtr(new GameObjectTerrainConvex(tGameObjectTerrainConvexParameters.name));
	pGameObjectTerrainConvex->setMaxUpdateRadium(tGameObjectTerrainConvexParameters.mMaxUpdateRadium);
	pGameObjectTerrainConvex->setParentNest(tGameObjectTerrainConvexParameters.parentNest);
	pGameObjectTerrainConvex->setSpawnProbability(tGameObjectTerrainConvexParameters.spawnProbability);
	pGameObjectTerrainConvex->setMaxRenderRadium(tGameObjectTerrainConvexParameters.mMaxRenderRadium);

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
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTerrainConvex->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares()));
		//Create RenderComponentEntityNightmares
		pGameObjectTerrainConvex->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.nightmaresName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTerrainConvex->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectTerrainConvex->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTerrainConvex->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.dreamsName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTerrainConvex->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectTerrainConvex->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.nightmaresName,
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTerrainConvex->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares()));
	}

	//Create PhysicsComponent
	pGameObjectTerrainConvex->setPhysicsComponentComplexConvex(mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectTerrainConvex,
		tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters,
		pGameObjectTerrainConvex->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTerrainConvex->setGameWorldManager(gameWorldMgr);
	std::string scriptFile="";
	pGameObjectTerrainConvex->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTerrainConvex;
}

GameObjectTerrainTrianglePtr GameObjectFactory::createGameObjectTerrainTriangle(
	TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters, GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle;

	//Create GameObject
	pGameObjectTerrainTriangle = GameObjectTerrainTrianglePtr(new GameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters.name));
	pGameObjectTerrainTriangle->setMaxUpdateRadium(tGameObjectTerrainTriangleParameters.mMaxUpdateRadium);
	pGameObjectTerrainTriangle->setParentNest(tGameObjectTerrainTriangleParameters.parentNest);
	pGameObjectTerrainTriangle->setSpawnProbability(tGameObjectTerrainTriangleParameters.spawnProbability);
	pGameObjectTerrainTriangle->setMaxRenderRadium(tGameObjectTerrainTriangleParameters.mMaxRenderRadium);

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
		pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTerrainTriangle->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainTriangle->getLogicComponent()->existsInNightmares()));
	
	//Create RenderComponentEntityNightmares
	pGameObjectTerrainTriangle->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTerrainTriangleParameters.nightmaresName,
		pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTerrainTriangle->getLogicComponent()->existsInDreams(),
		pGameObjectTerrainTriangle->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTerrainTriangle->setPhysicsComponentComplexTriangle(mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectTerrainTriangle,
		tGameObjectTerrainTriangleParameters.tPhysicsComponentComplexTriangleParameters,
		pGameObjectTerrainTriangle->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTerrainTriangle->setGameWorldManager(gameWorldMgr);
	std::string scriptFile="";
	pGameObjectTerrainTriangle->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTerrainTriangle;
}

GameObjectTreePtr GameObjectFactory::createGameObjectTree(TGameObjectTreeParameters tGameObjectTreeParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTreePtr pGameObjectTree;

	//Create GameObject
	pGameObjectTree = GameObjectTreePtr(new GameObjectTree(tGameObjectTreeParameters.name));
	pGameObjectTree->setMaxUpdateRadium(tGameObjectTreeParameters.mMaxUpdateRadium);
	pGameObjectTree->setParentNest(tGameObjectTreeParameters.parentNest);
	pGameObjectTree->setSpawnProbability(tGameObjectTreeParameters.spawnProbability);
	pGameObjectTree->setMaxRenderRadium(tGameObjectTreeParameters.mMaxRenderRadium);

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
		pGameObjectTree,tGameObjectTreeParameters.tRenderComponentEntityParameters,
		pGameObjectTree->getLogicComponent()->existsInDreams(),
		pGameObjectTree->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTree->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectTree, 
		tGameObjectTreeParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectTree->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTree->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTree->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTree;
}

GameObjectTreeComplexPtr GameObjectFactory::createGameObjectTreeComplex(TGameObjectTreeComplexParameters tGameObjectTreeComplexParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTreeComplexPtr pGameObjectTreeComplex;

	//Create GameObject
	pGameObjectTreeComplex = GameObjectTreeComplexPtr(new GameObjectTreeComplex(tGameObjectTreeComplexParameters.name));
	pGameObjectTreeComplex->setMaxUpdateRadium(tGameObjectTreeComplexParameters.mMaxUpdateRadium);
	pGameObjectTreeComplex->setParentNest(tGameObjectTreeComplexParameters.parentNest);
	pGameObjectTreeComplex->setSpawnProbability(tGameObjectTreeComplexParameters.spawnProbability);
	pGameObjectTreeComplex->setMaxRenderRadium(tGameObjectTreeComplexParameters.mMaxRenderRadium);

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
		pGameObjectTreeComplex,tGameObjectTreeComplexParameters.tRenderComponentEntityParameters,
		pGameObjectTreeComplex->getLogicComponent()->existsInDreams(),
		pGameObjectTreeComplex->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTreeComplex->setPhysicsComponentComplexConvex(
		mComponentFactory->createPhysicsComponentComplexConvex(
		pGameObjectTreeComplex, 
		tGameObjectTreeComplexParameters.tPhysicsComponentComplexConvexParameters, 
		pGameObjectTreeComplex->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTreeComplex->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTreeComplex->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTreeComplex;
}

GameObjectTowerPtr GameObjectFactory::createGameObjectTower(TGameObjectTowerParameters tGameObjectTowerParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTowerPtr pGameObjectTower;

	//Create GameObject
	pGameObjectTower = GameObjectTowerPtr(new GameObjectTower(tGameObjectTowerParameters.name));
	pGameObjectTower->setMaxUpdateRadium(tGameObjectTowerParameters.mMaxUpdateRadium);
	pGameObjectTower->setParentNest(tGameObjectTowerParameters.parentNest);
	pGameObjectTower->setSpawnProbability(tGameObjectTowerParameters.spawnProbability);
	pGameObjectTower->setMaxRenderRadium(tGameObjectTowerParameters.mMaxRenderRadium);

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
		pGameObjectTower,tGameObjectTowerParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTower->getLogicComponent()->existsInDreams(),
		pGameObjectTower->getLogicComponent()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectTower->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTowerParameters.nightmaresName,
		pGameObjectTower,tGameObjectTowerParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTower->getLogicComponent()->existsInDreams(),
		pGameObjectTower->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTower->setPhysicsComponentComplexTriangle(
		mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectTower, 
		tGameObjectTowerParameters.tPhysicsComponentComplexTriangleParameters, 
		pGameObjectTower->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTower->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTower->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTower;
}

GameObjectTriggerBoxPtr GameObjectFactory::createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTriggerBoxPtr pGameObjectTriggerBox;

	//Create GameObject
	pGameObjectTriggerBox = GameObjectTriggerBoxPtr(new GameObjectTriggerBox(tGameObjectTriggerBoxParameters.name));
	pGameObjectTriggerBox->setMaxUpdateRadium(tGameObjectTriggerBoxParameters.mMaxUpdateRadium);
	pGameObjectTriggerBox->setParentNest(tGameObjectTriggerBoxParameters.parentNest);
	pGameObjectTriggerBox->setSpawnProbability(tGameObjectTriggerBoxParameters.spawnProbability);
	pGameObjectTriggerBox->setMaxRenderRadium(tGameObjectTriggerBoxParameters.mMaxRenderRadium);

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
		pGameObjectTriggerBox,tGameObjectTriggerBoxParameters.tRenderComponentEntityParameters,
		pGameObjectTriggerBox->getLogicComponent()->existsInDreams(),
		pGameObjectTriggerBox->getLogicComponent()->existsInNightmares()));

	//Make RenderComponentEntity not visible
	pGameObjectTriggerBox->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectTriggerBox->setPhysicsComponentVolumeBox(mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectTriggerBox,
		tGameObjectTriggerBoxParameters.tPhysicsComponentVolumeBoxParameters,
		pGameObjectTriggerBox->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTriggerBox->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTriggerBox->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTriggerBox;
}

GameObjectTriggerCapsulePtr GameObjectFactory::createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule;

	//Create GameObject
	pGameObjectTriggerCapsule = GameObjectTriggerCapsulePtr(new GameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters.name));
	pGameObjectTriggerCapsule->setMaxUpdateRadium(tGameObjectTriggerCapsuleParameters.mMaxUpdateRadium);
	pGameObjectTriggerCapsule->setParentNest(tGameObjectTriggerCapsuleParameters.parentNest);
	pGameObjectTriggerCapsule->setSpawnProbability(tGameObjectTriggerCapsuleParameters.spawnProbability);
	pGameObjectTriggerCapsule->setMaxRenderRadium(tGameObjectTriggerCapsuleParameters.mMaxRenderRadium);

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
		pGameObjectTriggerCapsule,tGameObjectTriggerCapsuleParameters.tRenderComponentEntityParameters,
		pGameObjectTriggerCapsule->getLogicComponent()->existsInDreams(),
		pGameObjectTriggerCapsule->getLogicComponent()->existsInNightmares()));

	//Make RenderComponentEntity not visible
	pGameObjectTriggerCapsule->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectTriggerCapsule->setPhysicsComponentVolumeCapsule(mComponentFactory->createPhysicsComponentVolumeCapsule(
		pGameObjectTriggerCapsule,
		tGameObjectTriggerCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters,
		pGameObjectTriggerCapsule->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectTriggerCapsule->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTriggerCapsule->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTriggerCapsule;
}

GameObjectCameraTriggerPtr GameObjectFactory::createGameObjectCameraTrigger(TGameObjectCameraTriggerParameters tGameObjectCameraTriggerParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectCameraTriggerPtr pGameObjectCameraTrigger;

	//Create GameObject
	pGameObjectCameraTrigger = GameObjectCameraTriggerPtr(new GameObjectCameraTrigger(tGameObjectCameraTriggerParameters.name));
	pGameObjectCameraTrigger->setMaxUpdateRadium(tGameObjectCameraTriggerParameters.mMaxUpdateRadium);
	pGameObjectCameraTrigger->setParentNest(tGameObjectCameraTriggerParameters.parentNest);
	pGameObjectCameraTrigger->setSpawnProbability(tGameObjectCameraTriggerParameters.spawnProbability);
	pGameObjectCameraTrigger->setMaxRenderRadium(tGameObjectCameraTriggerParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectCameraTrigger->setLogicComponentCameraTrigger(
		mComponentFactory->createLogicComponentCameraTrigger(
		pGameObjectCameraTrigger,
		tGameObjectCameraTriggerParameters.tLogicComponentCameraTriggerParameters));

	//Create RenderComponentPositional
	pGameObjectCameraTrigger->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectCameraTrigger,tGameObjectCameraTriggerParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectCameraTrigger->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectCameraTrigger->getRenderComponentPositional()));

	//Create RenderComponentEntity
	pGameObjectCameraTrigger->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(tGameObjectCameraTriggerParameters.name,
		pGameObjectCameraTrigger,tGameObjectCameraTriggerParameters.tRenderComponentEntityParameters,
		pGameObjectCameraTrigger->getLogicComponentCameraTrigger()->existsInDreams(),
		pGameObjectCameraTrigger->getLogicComponentCameraTrigger()->existsInNightmares()));

	//Make RenderComponentEntity not visible
	pGameObjectCameraTrigger->getRenderComponentEntity()->setVisible(false);

	//Create PhysicsComponent
	pGameObjectCameraTrigger->setPhysicsComponentVolumeBox(mComponentFactory->createPhysicsComponentVolumeBox(
		pGameObjectCameraTrigger,
		tGameObjectCameraTriggerParameters.tPhysicsComponentVolumeBoxParameters,
		pGameObjectCameraTrigger->getRenderComponentPositional()));

	// Add a reference to this
	pGameObjectCameraTrigger->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectCameraTrigger->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectCameraTrigger;
}

GameObjectTripolloPtr GameObjectFactory::createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTripolloPtr pGameObjectTripollo;

	//Create GameObject
	pGameObjectTripollo = GameObjectTripolloPtr(new GameObjectTripollo(tGameObjectTripolloParameters.name));
	pGameObjectTripollo->setMaxUpdateRadium(tGameObjectTripolloParameters.mMaxUpdateRadium);
	pGameObjectTripollo->setParentNest(tGameObjectTripolloParameters.parentNest);
	pGameObjectTripollo->setSpawnProbability(tGameObjectTripolloParameters.spawnProbability);
	pGameObjectTripollo->setMaxRenderRadium(tGameObjectTripolloParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectTripollo->setLogicComponentEnemy(
		mComponentFactory->createLogicComponentEnemy(pGameObjectTripollo,
		tGameObjectTripolloParameters.tLogicComponentEnemyParameters));

	//Create RenderComponentPositional
	pGameObjectTripollo->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentPositionalParameters));

	//TODO ERASE THIS WHEN TRIPOLLO IS PROPERLY SCALED
	pGameObjectTripollo->getRenderComponentPositional()->setScale(
		tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters.scale_correction);

	//Create RenderComponentInitial
	pGameObjectTripollo->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTripollo->getRenderComponentPositional()));

	if(pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams() && pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTripollo->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloParameters.dreamsName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares()));
		//Create RenderComponentEntityNightmares
		pGameObjectTripollo->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloParameters.nightmaresName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares()));
	}
	else if(pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectTripollo->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloParameters.dreamsName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares()));
	}
	else if(pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectTripollo->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectTripolloParameters.nightmaresName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTripollo->getLogicComponentEnemy()->existsInDreams(),
		pGameObjectTripollo->getLogicComponentEnemy()->existsInNightmares()));
	}

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->TRIPOLLO_DIE;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectTripollo->setRenderComponentParticleSystemDie(mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectTripollo,tRenderComponentParticleSystemParameters,pGameObjectTripollo->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->TRIPOLLO_SHOCK;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectTripollo->setRenderComponentParticleSystemShock(mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectTripollo,tRenderComponentParticleSystemParameters,pGameObjectTripollo->getRenderComponentPositional()));

	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->TRIPOLLO_SURPRISE;
	tRenderComponentParticleSystemParameters.attached = false;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectTripollo->setRenderComponentParticleSystemSurprise(mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectTripollo,tRenderComponentParticleSystemParameters,pGameObjectTripollo->getRenderComponentPositional()));

	//Create PhysicsComponent
	pGameObjectTripollo->setPhysicsComponentCharacter(mComponentFactory->createPhysicsComponentCharacter(
		pGameObjectTripollo,
		tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters,
		pGameObjectTripollo->getRenderComponentPositional()));

	//TODO ERASE THIS WHEN PROPERLY DONE IN XSI
	pGameObjectTripollo->getPhysicsComponentCharacter()->setOffsetRenderPosition(
		tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters.position_correction);

	//Create TrajectoryComponent
	pGameObjectTripollo->setTrajectoryComponent(mComponentFactory->createTrajectoryComponent(
		pGameObjectTripollo,
		tGameObjectTripolloParameters.tTrajectoryComponentParameters));

	pGameObjectTripollo->setAttackComponent(
		mComponentFactory->createAttackComponent(
		pGameObjectTripollo,
		tGameObjectTripolloParameters.tAttackComponentParameters));

	// Create audio component
	pGameObjectTripollo->setAudioComponent(
		mComponentFactory->createAudioComponent(
		pGameObjectTripollo,
		tGameObjectTripolloParameters.tAudioComponentParameters
		,gameWorldMgr->getParent()->getAudioSubsystem()));

	// Add a reference to this
	pGameObjectTripollo->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTripollo->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTripollo;
}

GameObjectViewportPtr GameObjectFactory::createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectViewportPtr pGameObjectViewport;

	//Create GameObject
	pGameObjectViewport = GameObjectViewportPtr(new GameObjectViewport(tGameObjectViewportParameters.name));
	pGameObjectViewport->setMaxUpdateRadium(tGameObjectViewportParameters.mMaxUpdateRadium);
	pGameObjectViewport->setParentNest(tGameObjectViewportParameters.parentNest);
	pGameObjectViewport->setSpawnProbability(tGameObjectViewportParameters.spawnProbability);
	pGameObjectViewport->setMaxRenderRadium(tGameObjectViewportParameters.mMaxRenderRadium);

	//Create RenderComponentViewport
	pGameObjectViewport->setRenderComponentViewport(mComponentFactory->createRenderComponentViewport(
		pGameObjectViewport,tGameObjectViewportParameters.tRenderComponentViewportParameters));

	// Add a reference to this
	pGameObjectViewport->setGameWorldManager(gameWorldMgr);

	//Initialize compositor effects
	std::string scriptFile="";
	pGameObjectViewport->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectViewport;
}

GameObjectWoodBoxPtr GameObjectFactory::createGameObjectWoodBox(TGameObjectWoodBoxParameters tGameObjectWoodBoxParameters, 
											 GameWorldManagerPtr gameWorldMgr)
{
	GameObjectWoodBoxPtr pGameObjectWoodBox;

	//Create GameObject
	pGameObjectWoodBox = GameObjectWoodBoxPtr(new GameObjectWoodBox(tGameObjectWoodBoxParameters.name));
	pGameObjectWoodBox->setMaxUpdateRadium(tGameObjectWoodBoxParameters.mMaxUpdateRadium);
	pGameObjectWoodBox->setParentNest(tGameObjectWoodBoxParameters.parentNest);
	pGameObjectWoodBox->setSpawnProbability(tGameObjectWoodBoxParameters.spawnProbability);
	pGameObjectWoodBox->setMaxRenderRadium(tGameObjectWoodBoxParameters.mMaxRenderRadium);

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
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams(),
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares()));
		//Create RenderComponentEntityNightmares
		pGameObjectWoodBox->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.nightmaresName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams(),
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares()));
		std::string addName=tGameObjectWoodBoxParameters.name+"additional";
		pGameObjectWoodBox->setRenderComponentEntityAdditional(
			mComponentFactory->createRenderComponentEntity(addName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentAdditionalParameters,
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams(),
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares()));
	}
	else if(pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams())
	{
		//Create RenderComponentEntityDreams
		pGameObjectWoodBox->setRenderComponentEntityDreams(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.dreamsName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams(),
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares()));
	}
	else if(pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares())
	{
		//Create RenderComponentEntityNightmares
		pGameObjectWoodBox->setRenderComponentEntityNightmares(
			mComponentFactory->createRenderComponentEntity(tGameObjectWoodBoxParameters.nightmaresName,
			pGameObjectWoodBox,tGameObjectWoodBoxParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInDreams(),
		pGameObjectWoodBox->getLogicComponentBreakable()->existsInNightmares()));
	}

	//Create RenderComponenetParticleSystem
	TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters;
	tRenderComponentParticleSystemParameters.templateName = ParticleTemplates::getInstance()->BOX_DUST;
	tRenderComponentParticleSystemParameters.attached = true;
	tRenderComponentParticleSystemParameters.poolSize = ParticleTemplates::getInstance()->DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;
	tRenderComponentParticleSystemParameters.queueID = Ogre::RENDER_QUEUE_MAIN;
	pGameObjectWoodBox->setRenderComponentParticleSystemDust(
		mComponentFactory->createRenderComponentParticleSystem(
		pGameObjectWoodBox,
		tRenderComponentParticleSystemParameters,
		pGameObjectWoodBox->getRenderComponentPositional()));

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

	std::string scriptFile="";
	pGameObjectWoodBox->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectWoodBox;
}

GameObjectWaterPtr GameObjectFactory::createGameObjectWater(TGameObjectWaterParameters tGameObjectWaterParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectWaterPtr pGameObjectWater;

	//Create GameObject
	pGameObjectWater = GameObjectWaterPtr(new GameObjectWater(tGameObjectWaterParameters.name));
	pGameObjectWater->setMaxUpdateRadium(tGameObjectWaterParameters.mMaxUpdateRadium);
	pGameObjectWater->setParentNest(tGameObjectWaterParameters.parentNest);
	pGameObjectWater->setSpawnProbability(tGameObjectWaterParameters.spawnProbability);
	pGameObjectWater->setMaxRenderRadium(tGameObjectWaterParameters.mMaxRenderRadium);

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
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterDreamsParameters,
		pGameObjectWater->getLogicComponent()->existsInDreams(),
		pGameObjectWater->getLogicComponent()->existsInNightmares()));
		//Create RenderComponentWaterNightmares
		pGameObjectWater->setRenderComponentWaterNightmares(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.nightmaresName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterNightmaresParameters,
		pGameObjectWater->getLogicComponent()->existsInDreams(),
		pGameObjectWater->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectWater->getLogicComponent()->existsInDreams())
	{
		//Create RenderComponentWaterDreams
		pGameObjectWater->setRenderComponentWaterDreams(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.dreamsName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterDreamsParameters,
		pGameObjectWater->getLogicComponent()->existsInDreams(),
		pGameObjectWater->getLogicComponent()->existsInNightmares()));
	}
	else if(pGameObjectWater->getLogicComponent()->existsInNightmares())
	{
		//Create RenderComponentWaterNightmares
		pGameObjectWater->setRenderComponentWaterNightmares(
			mComponentFactory->createRenderComponentWater(tGameObjectWaterParameters.nightmaresName,
			pGameObjectWater,tGameObjectWaterParameters.tRenderComponentWaterNightmaresParameters,
		pGameObjectWater->getLogicComponent()->existsInDreams(),
		pGameObjectWater->getLogicComponent()->existsInNightmares()));
	}

	// Add a reference to this
	pGameObjectWater->setGameWorldManager(gameWorldMgr);
	std::string scriptFile="";
	pGameObjectWater->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectWater;
}
GameObjectSignpostPtr GameObjectFactory::createGameObjectSignPost(TGameObjectSignpostParameters TGameObjectSignpostParameters, 
									   GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSignpostPtr gameObject;

	//Create GameObject
	gameObject= GameObjectSignpostPtr(new GameObjectSignpost(TGameObjectSignpostParameters.name));
	gameObject->setMaxUpdateRadium(TGameObjectSignpostParameters.mMaxUpdateRadium);
	gameObject->setParentNest(TGameObjectSignpostParameters.parentNest);
	gameObject->setSpawnProbability(TGameObjectSignpostParameters.spawnProbability);
	gameObject->setMaxRenderRadium(TGameObjectSignpostParameters.mMaxRenderRadium);

	//Create LogicComponent
	gameObject->setLogicComponent(
		mComponentFactory->createLogicComponentProp(
		gameObject,
		TGameObjectSignpostParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	gameObject->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		gameObject,TGameObjectSignpostParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	gameObject->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		gameObject->getRenderComponentPositional()));

	//Create RenderComponentEntity
	gameObject->setRenderComponentEntity(
		mComponentFactory->createRenderComponentEntity(TGameObjectSignpostParameters.name,
		gameObject,TGameObjectSignpostParameters.tRenderComponentEntityParameters,
		gameObject->getLogicComponent()->existsInDreams(),
		gameObject->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	gameObject->setPhysicsComponentSimpleBox(mComponentFactory->createPhysicsComponentSimpleBox(
		gameObject,
		TGameObjectSignpostParameters.tPhysicsComponentSimpleBoxParameters,
		gameObject->getRenderComponentPositional()));


	//gameObject->setSignpostMessage(TGameObjectSignpostParameters.signpostMessage);
	gameObject->setRenderComponentMessageBox(
		mComponentFactory->createRenderComponentMessageBox(
		gameObject,
		TGameObjectSignpostParameters.tMsgBoxParams
		));

	//Add reference to this
	gameObject->setGameWorldManager(gameWorldMgr);
	std::string scriptFile="";
	gameObject->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}

	return gameObject;

}

GameObjectLevelEntrancePtr GameObjectFactory::createGameObjectLevelEntrance(TGameObjectLevelEntranceParameters tGameObjectLevelEntranceParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectLevelEntrancePtr pGameObjectLevelEntrance;

	//Create GameObject
	pGameObjectLevelEntrance = GameObjectLevelEntrancePtr(new GameObjectLevelEntrance(tGameObjectLevelEntranceParameters.name));
	pGameObjectLevelEntrance->setMaxUpdateRadium(tGameObjectLevelEntranceParameters.mMaxUpdateRadium);
	pGameObjectLevelEntrance->setParentNest(tGameObjectLevelEntranceParameters.parentNest);
	pGameObjectLevelEntrance->setSpawnProbability(tGameObjectLevelEntranceParameters.spawnProbability);
	pGameObjectLevelEntrance->setMaxRenderRadium(tGameObjectLevelEntranceParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectLevelEntrance->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectLevelEntrance,
		tGameObjectLevelEntranceParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectLevelEntrance->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectLevelEntrance,tGameObjectLevelEntranceParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectLevelEntrance->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectLevelEntrance->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectLevelEntrance->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectLevelEntranceParameters.dreamsName,
		pGameObjectLevelEntrance,tGameObjectLevelEntranceParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectLevelEntrance->getLogicComponent()->existsInDreams(),
		pGameObjectLevelEntrance->getLogicComponent()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectLevelEntrance->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectLevelEntranceParameters.nightmaresName,
		pGameObjectLevelEntrance,tGameObjectLevelEntranceParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectLevelEntrance->getLogicComponent()->existsInDreams(),
		pGameObjectLevelEntrance->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectLevelEntrance->setPhysicsComponentComplexTriangle(
		mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectLevelEntrance, 
		tGameObjectLevelEntranceParameters.tPhysicsComponentComplexTriangleParameters, 
		pGameObjectLevelEntrance->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectLevelEntrance->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectLevelEntrance->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectLevelEntrance;
}

GameObjectSwitchPtr GameObjectFactory::createGameObjectSwitch(TGameObjectSwitchParameters tGameObjectSwitchParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectSwitchPtr pGameObjectSwitch;

	//Create GameObject
	pGameObjectSwitch = GameObjectSwitchPtr(new GameObjectSwitch(tGameObjectSwitchParameters.name));
	pGameObjectSwitch->setMaxUpdateRadium(tGameObjectSwitchParameters.mMaxUpdateRadium);
	pGameObjectSwitch->setParentNest(tGameObjectSwitchParameters.parentNest);
	pGameObjectSwitch->setSpawnProbability(tGameObjectSwitchParameters.spawnProbability);
	pGameObjectSwitch->setMaxRenderRadium(tGameObjectSwitchParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectSwitch->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectSwitch,
		tGameObjectSwitchParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectSwitch->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectSwitch,tGameObjectSwitchParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectSwitch->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectSwitch->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectSwitch->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectSwitchParameters.dreamsName,
		pGameObjectSwitch,tGameObjectSwitchParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectSwitch->getLogicComponent()->existsInDreams(),
		pGameObjectSwitch->getLogicComponent()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectSwitch->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectSwitchParameters.nightmaresName,
		pGameObjectSwitch,tGameObjectSwitchParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectSwitch->getLogicComponent()->existsInDreams(),
		pGameObjectSwitch->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponentSimpleBox
	pGameObjectSwitch->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectSwitch, 
		tGameObjectSwitchParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectSwitch->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectSwitch->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectSwitch->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectSwitch;
}

GameObjectTotemPtr GameObjectFactory::createGameObjectTotem(TGameObjectTotemParameters tGameObjectTotemParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectTotemPtr pGameObjectTotem;

	//Create GameObject
	pGameObjectTotem = GameObjectTotemPtr(new GameObjectTotem(tGameObjectTotemParameters.name));
	pGameObjectTotem->setMaxUpdateRadium(tGameObjectTotemParameters.mMaxUpdateRadium);
	pGameObjectTotem->setParentNest(tGameObjectTotemParameters.parentNest);
	pGameObjectTotem->setSpawnProbability(tGameObjectTotemParameters.spawnProbability);
	pGameObjectTotem->setMaxRenderRadium(tGameObjectTotemParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectTotem->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectTotem,
		tGameObjectTotemParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectTotem->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectTotem,tGameObjectTotemParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectTotem->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectTotem->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectTotem->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectTotemParameters.dreamsName,
		pGameObjectTotem,tGameObjectTotemParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectTotem->getLogicComponent()->existsInDreams(),
		pGameObjectTotem->getLogicComponent()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectTotem->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectTotemParameters.nightmaresName,
		pGameObjectTotem,tGameObjectTotemParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectTotem->getLogicComponent()->existsInDreams(),
		pGameObjectTotem->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponent
	pGameObjectTotem->setPhysicsComponentComplexTriangle(
		mComponentFactory->createPhysicsComponentComplexTriangle(
		pGameObjectTotem, 
		tGameObjectTotemParameters.tPhysicsComponentComplexTriangleParameters, 
		pGameObjectTotem->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTotem->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectTotem->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectTotem;
}

GameObjectBombPtr GameObjectFactory::createGameObjectBomb(TGameObjectBombParameters tGameObjectBombParameters, 
	GameWorldManagerPtr gameWorldMgr)
{
	GameObjectBombPtr pGameObjectBomb;

	//Create GameObject
	pGameObjectBomb = GameObjectBombPtr(new GameObjectBomb(tGameObjectBombParameters.name));
	pGameObjectBomb->setMaxUpdateRadium(tGameObjectBombParameters.mMaxUpdateRadium);
	pGameObjectBomb->setParentNest(tGameObjectBombParameters.parentNest);
	pGameObjectBomb->setSpawnProbability(tGameObjectBombParameters.spawnProbability);
	pGameObjectBomb->setMaxRenderRadium(tGameObjectBombParameters.mMaxRenderRadium);

	//Create LogicComponent
	pGameObjectBomb->setLogicComponent(
		mComponentFactory->createLogicComponent(
		pGameObjectBomb,
		tGameObjectBombParameters.tLogicComponentParameters));

	//Create RenderComponentPositional
	pGameObjectBomb->setRenderComponentPositional(mComponentFactory->createRenderComponentPositional(
		pGameObjectBomb,tGameObjectBombParameters.tRenderComponentPositionalParameters));

	//Create RenderComponentInitial
	pGameObjectBomb->setRenderComponentInitial(mComponentFactory->createRenderComponentInitial(
		pGameObjectBomb->getRenderComponentPositional()));

	//Create RenderComponentEntityDreams
	pGameObjectBomb->setRenderComponentEntityDreams(
		mComponentFactory->createRenderComponentEntity(tGameObjectBombParameters.dreamsName,
		pGameObjectBomb,tGameObjectBombParameters.tRenderComponentEntityDreamsParameters,
		pGameObjectBomb->getLogicComponent()->existsInDreams(),
		pGameObjectBomb->getLogicComponent()->existsInNightmares()));

	//Create RenderComponentEntityNightmares
	pGameObjectBomb->setRenderComponentEntityNightmares(
		mComponentFactory->createRenderComponentEntity(tGameObjectBombParameters.nightmaresName,
		pGameObjectBomb,tGameObjectBombParameters.tRenderComponentEntityNightmaresParameters,
		pGameObjectBomb->getLogicComponent()->existsInDreams(),
		pGameObjectBomb->getLogicComponent()->existsInNightmares()));

	//Create PhysicsComponentSimpleBox
	pGameObjectBomb->setPhysicsComponentSimpleBox(
		mComponentFactory->createPhysicsComponentSimpleBox(
		pGameObjectBomb, 
		tGameObjectBombParameters.tPhysicsComponentSimpleBoxParameters, 
		pGameObjectBomb->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectBomb->setGameWorldManager(gameWorldMgr);

	std::string scriptFile="";
	pGameObjectBomb->getLogicScriptFile(scriptFile);
	if (!scriptFile.empty())
	{
		gameWorldMgr->getParent()->getLogicSubsystem()->addScriptFile(scriptFile);
	}
	return pGameObjectBomb;
}