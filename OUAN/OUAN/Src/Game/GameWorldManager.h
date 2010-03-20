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

		void createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters);
		void createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters);
		void createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters);
		void createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters);
		void createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters);
		void createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters);
		void createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters);
		void createGameObjectTerrainTriangle(TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters);
		void createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters);		
		void createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters);
		void createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters);
		void createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters);
		void createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters);
		void createGameObjectCamera(TGameObjectCameraParameters tGameObjectCameraParameters);
		void createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters);
		void createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters);
		void createGameObjectProvisionalEntity(TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters);

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

	private:

		/// Add the game object pointer to the objects List
		/// @param gameObject pointer to the object to add to the main list
		void addGameObject(GameObjectPtr gameObject);
		void addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport);
		void addGameObjectScene(GameObjectScenePtr pGameObjectScene);
		void addGameObjectOny(GameObjectOnyPtr pGameObjectOny);
		void addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo);
		void addGameObjectTerrainConvex(GameObjectTerrainConvexPtr pGameObjectTerrainConvex);
		void addGameObjectTerrainTriangle(GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle);
		void addGameObjectLight(GameObjectLightPtr pGameObjectLight);
		void addGameObjectParticleSystem(GameObjectParticleSystemPtr pGameObjectParticleSystem);
		void addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet);
		void addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP);
		void addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP);
		void addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal);
		void addGameObjectEye(GameObjectEyePtr pGameObjectEye);
		void addGameObjectCamera(GameObjectCameraPtr pGameObjectCamera);
		void addGameObjectTriggerBox(GameObjectTriggerBoxPtr pGameObjectTriggerBox);
		void addGameObjectTriggerCapsule(GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule);
		void addGameObjectProvisionalEntity(GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity);


		//void addGameObjectMovableEntity(GameObjectMovableEntityPtr gameObjectMovableEntity);
		//[TODO]: Do the same with the toAdd/toDelete lists?

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