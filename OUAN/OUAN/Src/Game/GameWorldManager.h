#ifndef GAMEWORLDMANAGERH_H
#define GAMEWORLDMANAGERH_H
#include "../OUAN.h"

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
		TGameObjectTripolloContainer getGameObjectTripolloContainer();
		TGameObjectTripollitoContainer getGameObjectTripollitoContainer();
		TGameObjectTentetiesoContainer getGameObjectTentetiesoContainer();
		TGameObjectEyeContainer getGameObjectEyeContainer();
		TGameObjectTriggerBoxContainer getGameObjectTriggerBoxContainer();
		TGameObjectTriggerCapsuleContainer getGameObjectTriggerCapsuleContainer();
		TGameObjectViewportContainer getGameObjectViewportContainer();

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
		void createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters);
		void createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters);

		//trajectory Creator
		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);

		/// Update world state
		/// @param elapsedTime time since last update
		void update(double elapsedSeconds);

		/// Return an id value and increment it
		/// @return id value
		inline unsigned long nextId() {return mNextIdNum++;}

		/// Return the last id value used
		/// @return last id value used
		inline unsigned long lastId() {return mNextIdNum;}

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

		// Take items
		void takeItemMaxHP(GameObjectItemMaxHPPtr gameObjectMaxHP,GameObjectOnyPtr ony);
		void takeItem1UP(GameObjectItem1UPPtr gameObjectItem1UP,GameObjectOnyPtr ony);
		void takeItemHeart(GameObjectHeartPtr gameObjectHeart,GameObjectOnyPtr ony);
		void takeItemDiamond(GameObjectDiamondPtr gameObjectDiamond,GameObjectOnyPtr ony);
		void takeItemClockPiece(GameObjectClockPiecePtr gameObjectClockPiece);
		void takeItemStoryBook(GameObjectStoryBookPtr gameObjectStoryBook);

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

		/// Return the application pointer
		ApplicationPtr getParent();

		void clearEvents();

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
		void addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo);
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
		
		///number used to generate a unique identifier
		///for every game object that is created
		static unsigned long mNextIdNum;

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
		TGameObjectPositionalContainer mGameObjectPositionalContainer;
		TGameObjectSceneContainer mGameObjectSceneContainer;
		TGameObjectTripolloContainer mGameObjectTripolloContainer;
		TGameObjectTripollitoContainer mGameObjectTripollitoContainer;
		TGameObjectTentetiesoContainer mGameObjectTentetiesoContainer;
		TGameObjectEyeContainer mGameObjectEyeContainer;
		TGameObjectTriggerBoxContainer mGameObjectTriggerBoxContainer;
		TGameObjectTriggerCapsuleContainer mGameObjectTriggerCapsuleContainer;

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

		TGameObjectViewportContainer mGameObjectViewportContainer;

		void clearContainers();

		// Lists of objects to be created/deleted as a result of an
		// update frame. 
		// Addition/Deletion will be effective just before the next
		// update cycle
		TGameObjectContainer mGameObjectsToAdd;
		TGameObjectContainer mGameObjectsToDelete;

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
	};
}
#endif