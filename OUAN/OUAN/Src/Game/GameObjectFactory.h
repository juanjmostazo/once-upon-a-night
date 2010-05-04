#ifndef GAMEOBJECTFACTORYH_H
#define GAMEOBJECTFACTORYH_H
#include "../OUAN.h"
namespace OUAN
{
	class ComponentFactory;
	typedef boost::shared_ptr<ComponentFactory> ComponentFactoryPtr;
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
		GameObjectBushPtr createGameObjectBush(TGameObjectBushParameters tGameObjectBushParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCameraPtr createGameObjectCamera(TGameObjectCameraParameters tGameObjectCameraParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCarnivorousPlantPtr createGameObjectCarnivorousPlant(TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectClockPiecePtr createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectCryKingPtr createGameObjectCryKing(TGameObjectCryKingParameters tGameObjectCryKingParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDiamondPtr createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDiamondTreePtr createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDoorPtr createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectDragonPtr createGameObjectDragon(TGameObjectDragonParameters tGameObjectDragonParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectEyePtr createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectFlashLightPtr createGameObjectFlashLight(TGameObjectFlashLightParameters tGameObjectFlashLightParameters, 
			GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraMgr, RayCastingPtr raycasting);
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
		GameObjectNightGoblinPtr createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectOnyPtr createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters, 
			GameWorldManagerPtr gameWorldMgr, CameraManagerPtr cameraMgr);
		GameObjectParticleSystemPtr createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectPillowPtr createGameObjectPillow(TGameObjectPillowParameters tGameObjectPillowParameters, 
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
		GameObjectSnakeCreeperPtr createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters, 
			GameWorldManagerPtr gameWorldMgr);
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
		GameObjectTripollitoPtr createGameObjectTripollito(TGameObjectTripollitoParameters tGameObjectTripollitoParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectTripolloDreamsPtr createGameObjectTripolloDreams(TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectViewportPtr createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters, 
			GameWorldManagerPtr gameWorldMgr);
		GameObjectWoodBoxPtr createGameObjectWoodBox(TGameObjectWoodBoxParameters tGameObjectWoodBoxParameters, 
			GameWorldManagerPtr gameWorldMgr);		
	};
}
#endif