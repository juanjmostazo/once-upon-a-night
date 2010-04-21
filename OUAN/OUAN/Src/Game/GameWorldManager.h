#ifndef GAMEWORLDMANAGERH_H
#define GAMEWORLDMANAGERH_H
#include "../OUAN.h"
#include "../Event/Event.h"

namespace OUAN
{

	/// Manages the game scene:
	/// the landscape, all of its objects (creatures, props,...)
	class GameWorldManager: public boost::enable_shared_from_this<GameWorldManager>
	{
	public:
		GameWorldManager();
		~GameWorldManager();
		/// find gameObject by Id
		/// @param objectId identifier of the object to retrieve
		/// @return pointer to the object, if found
		GameObjectPtr getObject(const std::string& objectId);

		/// Return all game objects
		/// @return the game object container
		TGameObjectContainer getAllGameObjects();

		TGameObjectMovableContainer getGameObjectMovableContainer();
		TGameObjectMovableEntityContainer getGameObjectMovableEntityContainer();
		TGameObjectNonMovableContainer getGameObjectNonMovableContainer();
		TGameObjectNonMovableEntityContainer getGameObjectNonMovableEntityContainer();
		TGameObjectTerrainConvexContainer getGameObjectTerrainConvexContainer();
		TGameObjectTerrainTriangleContainer getGameObjectTerrainTriangleContainer();
		TGameObjectLightContainer getGameObjectLightContainer();
		TGameObjectParticleSystemContainer getGameObjectParticleSystemContainer();
		TGameObjectBillboardSetContainer getGameObjectBillboardSetContainer();
		TGameObjectOnyContainer getGameObjectOnyContainer();
		TGameObjectPositionalContainer getGameObjectPositionalContainer();
		TGameObjectSceneContainer getGameObjectSceneContainer();
		TGameObjectTripolloDreamsContainer getGameObjectTripolloDreamsContainer();
		TGameObjectTripollitoContainer getGameObjectTripollitoContainer();
		TGameObjectTentetiesoContainer getGameObjectTentetiesoContainer();
		TGameObjectEyeContainer getGameObjectEyeContainer();
		TGameObjectBee_ButterflyContainer getGameObjectBeeButterflyContainer();
		TGameObjectCarnivorousPlantContainer getGameObjectCarnivorousPlantContainer();
		TGameObjectSnakeCreeperContainer getGameObjectSnakeCreeperContainer();
		TGameObjectTriggerBoxContainer getGameObjectTriggerBoxContainer();
		TGameObjectTriggerCapsuleContainer getGameObjectTriggerCapsuleContainer();
		TGameObjectViewportContainer getGameObjectViewportContainer();

		TGameObjectPortalContainer getGameObjectPortalContainer();

		TGameObjectPhysicsContainer getGameObjectPhysicsContainer();
		TGameObjectPhysicsCharacterContainer getGameObjectPhysicsCharacterContainer();
		TGameObjectPhysicsComplexContainer getGameObjectPhysicsComplexContainer();
		TGameObjectPhysicsComplexConvexContainer getGameObjectPhysicsComplexConvexContainer();
		TGameObjectPhysicsComplexTriangleContainer getGameObjectPhysicsComplexTriangleContainer();
		TGameObjectPhysicsSimpleContainer getGameObjectPhysicsSimpleContainer();
		TGameObjectPhysicsSimpleBoxContainer getGameObjectPhysicsSimpleBoxContainer();
		TGameObjectPhysicsSimpleCapsuleContainer getGameObjectPhysicsSimpleCapsuleContainer();
		TGameObjectPhysicsVolumeContainer getGameObjectPhysicsVolumeContainer();
		TGameObjectPhysicsVolumeBoxContainer getGameObjectPhysicsVolumeBoxContainer();
		TGameObjectPhysicsVolumeCapsuleContainer getGameObjectPhysicsVolumeCapsuleContainer();

		TGameObjectLogicContainer getGameObjectLogicContainer();

		TGameObjectUsableContainer getGameObjectUsableContainer();

		/// Load level from the given file
		/// @param levelFileName name of the level file
		void loadLevel (const std::string& levelFileName);

		/// Unload data from current level
		/// (i.e, clear all object lists, destroy landscape
		/// and so on)
		void unloadLevel();

		/// init object
		/// @param pointer to the application object
		void init(ApplicationPtr app);

		/// Free resources
		void cleanUp();

		/// Reset game objects
		void resetAll();

		/// Create a game object using the given 'parameters' object
		/// @param objectParams parameters to init the game object and its components
		void createGameObjectBee_Butterfly(TGameObjectBee_ButterflyParameters tGameObjectBee_ButterflyParameters);
		void createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters);
		void createGameObjectBush(TGameObjectBushParameters tGameObjectBushParameters);
		void createGameObjectCamera(TGameObjectCameraParameters tGameObjectCameraParameters);
		void createGameObjectCarnivorousPlant(TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters);
		void createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters);
		void createGameObjectCryKing(TGameObjectCryKingParameters tGameObjectCryKingParameters);
		void createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters);
		void createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters);
		void createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters);
		void createGameObjectDragon(TGameObjectDragonParameters tGameObjectDragonParameters);
		void createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters);
		void createGameObjectFlashLight(TGameObjectFlashLightParameters tGameObjectFlashLightParameters);
		void createGameObjectHeart(TGameObjectHeartParameters tGameObjectHeartParameters);
		void createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters);
		void createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters);
		void createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters);
		void createGameObjectMagicClock(TGameObjectMagicClockParameters tGameObjectMagicClockParameters);
		void createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters);
		void createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters);
		void createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters);
		void createGameObjectPillow(TGameObjectPillowParameters tGameObjectPillowParameters);
		void createGameObjectPlataform(TGameObjectPlataformParameters tGameObjectPlataformParameters);
		void createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters);
		void createGameObjectProvisionalEntity(TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters);
		void createGameObjectScaredPlant(TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters);
		void createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters);
		void createGameObjectScepter(TGameObjectScepterParameters tGameObjectScepterParameters);
		void createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters);
		void createGameObjectStoryBook(TGameObjectStoryBookParameters tGameObjectStoryBookParameters);
		void createGameObjectTentetieso(TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters);
		void createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters);	
		void createGameObjectTerrainTriangle(TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters);
		void createGameObjectTree(TGameObjectTreeParameters tGameObjectTreeParameters);
		void createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters);
		void createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters);
		void createGameObjectTripollito(TGameObjectTripollitoParameters tGameObjectTripollitoParameters);
		void createGameObjectTripolloDreams(TGameObjectTripolloDreamsParameters tGameObjectTripolloDreamsParameters);
		void createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters);

		//Trajectory Creator
		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);

		//Walkability Map Creator
		void createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters);

		/// Update world state
		/// @param elapsedTime time since last update
		void update(double elapsedSeconds);

		/// Tell if the game over flag is set to true
		/// @return value of the "game over" flag
		bool isGameOver() const;

		/// Set the value of the game over flag
		/// @param gameOver	value to set
		void setGameOver(bool gameOver);

		/// Tell if the game beaten flag is set to true
		/// @return value of the "game beaten" flag
		bool isGameBeaten() const;

		/// Set the value of the game beaten flag
		/// @param gameBeaten value to set
		void setGameBeaten(bool gameBeaten);

		/// Sets the world to Nightmares if it was Dreams or Dreams if it was Nightmares
		void changeWorld();

		/// Pass current level
		void win();
		/// Lose game
		void lose();

		/// Reset the world after ony's death
		void onyDied();

		/// Change world to the one specified by the passed parameter
		/// @param currentworld world to change to
		void setWorld (int newWorld);

		/// returns NIGHTMARES or DREAMS depending on current world state
		int getCurrentWorld() const;

		/// gets current Loaded Level
		std::string getCurrentLevel() const;

		/// Adds event to the event manager's queue
		void addEvent(EventPtr event);
		/// Dispatch all events in the manager's queue
		void dispatchEvents();

		/// Return event manager
		/// @return event manager pointer
		EventManagerPtr getEventManager();

		/// Return GameObjectOny
		GameObjectOnyPtr getGameObjectOny();

		/// Return GameObjectFlashLight
		GameObjectFlashLightPtr getGameObjectFlashLight();

		/// Return the application pointer
		ApplicationPtr getParent();

		void clearEvents();

		// METHODS USED BY THE LUA SCRIPTS

		/// Compute distance between two game objects
		/// @param obj1	first object
		/// @param obj2 second object
		/// @return distance between the two game objects
		static double getDistance(const std::string& obj1, const std::string& obj2);
		
		/// Compute distance between a game object and the player
		/// @param obj object for which the distance to Ony will be computed
		/// @return distance between Ony and the object with its name equal to the passed one
		static double getPlayerDistance(const std::string& obj);

		/// Return the current world
		static int getWorld();

		void useWeapon();
		void stopUsingWeapon();

		void useObject();

	private:

		/// Add the game object pointer to the objects List
		/// @param gameObject pointer to the object to add to the main list
		void addGameObject(GameObjectPtr gameObject);
		void addGameObjectBee_Butterfly(GameObjectBee_ButterflyPtr gameObjectBee_Butterfly);
		void addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet);
		void addGameObjectBush(GameObjectBushPtr gameObjectBush);
		void addGameObjectCamera(GameObjectCameraPtr pGameObjectCamera);
		void addGameObjectCarnivorousPlant(GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant);
		void addGameObjectClockPiece(GameObjectClockPiecePtr pGameObjectClockPiece);
		void addGameObjectCryKing(GameObjectCryKingPtr pGameObjectCryKing);
		void addGameObjectDiamond(GameObjectDiamondPtr pGameObjectDiamond);
		void addGameObjectDiamondTree(GameObjectDiamondTreePtr pGameObjectDiamondTree);
		void addGameObjectDoor(GameObjectDoorPtr pGameObjectDoor);
		void addGameObjectDragon(GameObjectDragonPtr pGameObjectDragon);
		void addGameObjectEye(GameObjectEyePtr pGameObjectEye);
		void addGameObjectFlashLight(GameObjectFlashLightPtr pGameObjectFlashLight);
		void addGameObjectHeart(GameObjectHeartPtr pGameObjectHeart);
		void addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP);
		void addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP);
		void addGameObjectLight(GameObjectLightPtr pGameObjectLight);
		void addGameObjectMagicClock(GameObjectMagicClockPtr pGameObjectMagicClock);
		void addGameObjectNightGoblin(GameObjectNightGoblinPtr pGameObjectNightGoblin);
		void addGameObjectOny(GameObjectOnyPtr pGameObjectOny);
		void addGameObjectParticleSystem(GameObjectParticleSystemPtr pGameObjectParticleSystem);
		void addGameObjectPillow(GameObjectPillowPtr pGameObjectPillow);
		void addGameObjectPlataform(GameObjectPlataformPtr pGameObjectPlataform);
		void addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal);
		void addGameObjectProvisionalEntity(GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity);
		void addGameObjectScaredPlant(GameObjectScaredPlantPtr pGameObjectScaredPlant);
		void addGameObjectScene(GameObjectScenePtr pGameObjectScene);
		void addGameObjectScepter(GameObjectScepterPtr pGameObjectScepter);
		void addGameObjectSnakeCreeper(GameObjectSnakeCreeperPtr pGameObjectSnakeCreeper);
		void addGameObjectStoryBook(GameObjectStoryBookPtr pGameObjectStoryBook);
		void addGameObjectTentetieso(GameObjectTentetiesoPtr pGameObjectTentetieso);
		void addGameObjectTerrainConvex(GameObjectTerrainConvexPtr pGameObjectTerrainConvex);
		void addGameObjectTerrainTriangle(GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle);
		void addGameObjectTree(GameObjectTreePtr pGameObjectTree);
		void addGameObjectTriggerBox(GameObjectTriggerBoxPtr pGameObjectTriggerBox);
		void addGameObjectTriggerCapsule(GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule);
		void addGameObjectTripollito(GameObjectTripollitoPtr pGameObjectTripollito);
		void addGameObjectTripolloDreams(GameObjectTripolloDreamsPtr pGameObjectTripolloDreams);
		void addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport);


		/// Generate a unique id string with the following format:
		/// "baseString"_"00value"
		/// @param baseString	reference string to make the id
		/// @param padding		number of spaces for the value.
		///						if the number is too small, it'll be padded
		///						with 'padding' zeroes
		/// @param value		the value to append to the string
		/// @return id string
		std::string makeIdString(const std::string& baseString,const int& padding, const unsigned long& value);

		/// Pointer to the main application object
		ApplicationPtr mApp;
		


		/// Game objects currently existing in the world
		TGameObjectContainer mGameObjects;

		/// Game object containers to access specific game object types
		TGameObjectMovableContainer mGameObjectMovableContainer;
		TGameObjectMovableEntityContainer mGameObjectMovableEntityContainer;
		TGameObjectNonMovableContainer mGameObjectNonMovableContainer;
		TGameObjectNonMovableEntityContainer mGameObjectNonMovableEntityContainer;
		TGameObjectLightContainer mGameObjectLightContainer;
		TGameObjectParticleSystemContainer mGameObjectParticleSystemContainer;
		TGameObjectBillboardSetContainer mGameObjectBillboardSetContainer;
		TGameObjectTerrainTriangleContainer mGameObjectTerrainTriangleContainer;
		TGameObjectTerrainConvexContainer mGameObjectTerrainConvexContainer;
		TGameObjectOnyContainer mGameObjectOnyContainer;
		TGameObjectFlashLightContainer mGameObjectFlashLightContainer;
		TGameObjectPositionalContainer mGameObjectPositionalContainer;
		TGameObjectSceneContainer mGameObjectSceneContainer;
		TGameObjectTripolloDreamsContainer mGameObjectTripolloDreamsContainer;
		TGameObjectTripollitoContainer mGameObjectTripollitoContainer;
		TGameObjectTentetiesoContainer mGameObjectTentetiesoContainer;
		TGameObjectEyeContainer mGameObjectEyeContainer;
		TGameObjectTriggerBoxContainer mGameObjectTriggerBoxContainer;
		TGameObjectTriggerCapsuleContainer mGameObjectTriggerCapsuleContainer;
		TGameObjectBee_ButterflyContainer mGameObjectBeeButterflyContainer;
		TGameObjectCarnivorousPlantContainer mGameObjectCarnivorousPlantContainer;
		TGameObjectSnakeCreeperContainer mGameObjectSnakeCreeperContainer;

		TGameObjectPortalContainer mGameObjectPortalContainer;

		TGameObjectPhysicsContainer mGameObjectPhysicsContainer;
		TGameObjectPhysicsCharacterContainer mGameObjectPhysicsCharacterContainer;
		TGameObjectPhysicsComplexContainer mGameObjectPhysicsComplexContainer;
		TGameObjectPhysicsComplexConvexContainer mGameObjectPhysicsComplexConvexContainer;
		TGameObjectPhysicsComplexTriangleContainer mGameObjectPhysicsComplexTriangleContainer;
		TGameObjectPhysicsSimpleContainer mGameObjectPhysicsSimpleContainer;
		TGameObjectPhysicsSimpleBoxContainer mGameObjectPhysicsSimpleBoxContainer;
		TGameObjectPhysicsSimpleCapsuleContainer mGameObjectPhysicsSimpleCapsuleContainer;
		TGameObjectPhysicsVolumeContainer mGameObjectPhysicsVolumeContainer;
		TGameObjectPhysicsVolumeBoxContainer mGameObjectPhysicsVolumeBoxContainer;
		TGameObjectPhysicsVolumeCapsuleContainer mGameObjectPhysicsVolumeCapsuleContainer;

		TGameObjectLogicContainer mGameObjectLogicContainer;

		TGameObjectUsableContainer mGameObjectUsableContainer;

		TGameObjectViewportContainer mGameObjectViewportContainer;

		void clearContainers();

		bool mGameOver;
		// Besides being over, the game has been beaten
		bool mGameBeaten;

		// Current level
		std::string level;

		// Current world (DREAMS or NIGHTMARES)
		int world;

		EventManagerPtr mEventManager;
		EventProcessorPtr mEventProcessor;
		GameWorldManagerPtr mThis;

		static GameWorldManager* mInst;
	};
}
#endif