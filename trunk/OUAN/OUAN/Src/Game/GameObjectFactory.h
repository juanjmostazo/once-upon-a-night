#ifndef GAMEOBJECTFACTORYH_H
#define GAMEOBJECTFACTORYH_H
#include "../OUAN.h"
namespace OUAN
{
	class ComponentFactory;
	typedef boost::shared_ptr<ComponentFactory> ComponentFactoryPtr;

	class GameObjectSound;
	typedef boost::shared_ptr<GameObjectSound> GameObjectSoundPtr;
	class TGameObjectSoundParameters;

	class GameObjectFactory
	{
	private:
		ComponentFactoryPtr mComponentFactory;
	public:
		GameObjectFactory();
		~GameObjectFactory();
		void init(ApplicationPtr app);
		/// Create a game object using the given 'parameters' object
		/// @param objectParams parameters to init the game object and its components
		GameObjectBee_ButterflyPtr createGameObjectBee_Butterfly(TGameObjectBee_ButterflyParameters tGameObjectBee_ButterflyParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectBillboardSetPtr createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTraspasablePtr createGameObjectTraspasable(TGameObjectTraspasableParameters tGameObjectTraspasableParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCarnivorousPlantPtr createGameObjectCarnivorousPlant(TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectClockPiecePtr createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCloudPtr createGameObjectCloud(TGameObjectCloudParameters tGameObjectCloudParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCryKingPtr createGameObjectCryKing(TGameObjectCryKingParameters tGameObjectCryKingParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDiamondPtr createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDiamondTreePtr createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDoorPtr createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectBossPtr createGameObjectBoss(TGameObjectBossParameters tGameObjectBossParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectEyePtr createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectFlashLightPtr createGameObjectFlashLight
			(TGameObjectFlashLightParameters tGameObjectFlashLightParameters, 
			GameWorldManagerPtr gameWorldMgr, RenderSubsystemPtr renderSubsystem);
		GameObjectHeartPtr createGameObjectHeart(TGameObjectHeartParameters tGameObjectHeartParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectItem1UPPtr createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectItemMaxHPPtr createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectLightPtr createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectMagicClockPtr createGameObjectMagicClock(TGameObjectMagicClockParameters tGameObjectMagicClockParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectNestPtr createGameObjectNest(TGameObjectNestParameters tGameObjectNestParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectNightGoblinPtr createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectOnyPtr createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters, 
			GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraMgr);
		GameObjectParticleSystemPtr createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectPillowPtr createGameObjectPillow(TGameObjectPillowParameters tGameObjectPillowParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectPlanePtr createGameObjectPlane(TGameObjectPlaneParameters tGameObjectPlaneParameters, 
			GameWorldManagerPtr gameWorldMgr);	
		GameObjectPlataformPtr createGameObjectPlataform(TGameObjectPlataformParameters tGameObjectPlataformParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectPortalPtr createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectProvisionalEntityPtr createGameObjectProvisionalEntity(TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectScaredPlantPtr createGameObjectScaredPlant(TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectScenePtr createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectScepterPtr createGameObjectScepter(TGameObjectScepterParameters tGameObjectScepterParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectSkyBodyPtr createGameObjectSkyBody(TGameObjectSkyBodyParameters params,
			GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraManager, Ogre::SceneManager* sceneManager );
		GameObjectSnakeCreeperPtr createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectSoundPtr createGameObjectSound(TGameObjectSoundParameters params, GameWorldManagerPtr gameWorldMgr);
		GameObjectStoryBookPtr createGameObjectStoryBook(TGameObjectStoryBookParameters tGameObjectStoryBookParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTentetiesoPtr createGameObjectTentetieso(TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTerrainConvexPtr createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters, 
			GameWorldManagerPtr gameWorldMgr);	
		GameObjectTerrainTrianglePtr createGameObjectTerrainTriangle(TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTreePtr createGameObjectTree(TGameObjectTreeParameters tGameObjectTreeParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTriggerBoxPtr createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTriggerCapsulePtr createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTripolloNightmaresPtr createGameObjectTripolloNightmares(TGameObjectTripolloNightmaresParameters tGameObjectTripolloNightmaresParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTripolloDreamsPtr createGameObjectTripolloDreams(TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectViewportPtr createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectWoodBoxPtr createGameObjectWoodBox(TGameObjectWoodBoxParameters tGameObjectWoodBoxParameters, 
			GameWorldManagerPtr gameWorldMgr);		
		GameObjectWaterPtr createGameObjectWater(TGameObjectWaterParameters tGameObjectWaterParameters, 
			GameWorldManagerPtr gameWorldMgr);		

		GameObjectTowerPtr createGameObjectTower(TGameObjectTowerParameters tGameObjectTowerParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTreeComplexPtr createGameObjectTreeComplex(TGameObjectTreeComplexParameters tGameObjectTreeComplexParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectFogPtr createGameObjectFog(TGameObjectFogParameters tGameObjectFogParameters, 
			GameWorldManagerPtr gameWorldMgr);		
		GameObjectCameraTriggerPtr createGameObjectCameraTrigger(TGameObjectCameraTriggerParameters tGameObjectCameraTriggerParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectSignPostPtr createGameObjectSignPost(TGameObjectSignPostParameters tGameObjectSignPostParameters, 
			GameWorldManagerPtr gameWorldMgr);

		GameObjectBombPtr createGameObjectBomb(TGameObjectBombParameters tGameObjecBombParameters, 
			GameWorldManagerPtr gameWorldMgr);	
		GameObjectTotemPtr createGameObjectTotem(TGameObjectTotemParameters tGameObjectTotemParameters, 
			GameWorldManagerPtr gameWorldMgr);	
		GameObjectSwitchPtr createGameObjectSwitch(TGameObjectSwitchParameters tGameObjectSwitchParameters, 
			GameWorldManagerPtr gameWorldMgr);	
		GameObjectLevelEntrancePtr createGameObjectLevelEntrance(TGameObjectLevelEntranceParameters tGameObjectLevelEntranceParameters, 
			GameWorldManagerPtr gameWorldMgr);	
	};
}
#endif