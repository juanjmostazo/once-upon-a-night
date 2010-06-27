#ifndef GAMEWORLDMANAGERH_H
#define GAMEWORLDMANAGERH_H
#include "../OUAN.h"
#include "../Event/Event.h"
namespace OUAN
{
	//forward declarations
	class GameObjectSound;
	typedef boost::shared_ptr<GameObjectSound> GameObjectSoundPtr;

	typedef std::map<std::string, std::string> TDiamondTreeLinkMap;

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
		TGameObjectContainer * getAllGameObjects();

		TGameObjectMovableContainer * getGameObjectMovableContainer();
		TGameObjectMovableEntityContainer * getGameObjectMovableEntityContainer();
		TGameObjectNonMovableContainer * getGameObjectNonMovableContainer();
		TGameObjectNonMovableEntityContainer * getGameObjectNonMovableEntityContainer();
		TGameObjectTerrainConvexContainer * getGameObjectTerrainConvexContainer();
		TGameObjectTerrainTriangleContainer * getGameObjectTerrainTriangleContainer();
		TGameObjectLightContainer * getGameObjectLightContainer();
		TGameObjectParticleSystemContainer * getGameObjectParticleSystemContainer();
		TGameObjectBillboardSetContainer * getGameObjectBillboardSetContainer();
		TGameObjectDiamondContainer * getGameObjectDiamondContainer();
		TGameObjectDiamondTreeContainer * getGameObjectDiamondTreeContainer();
		TGameObjectOnyContainer * getGameObjectOnyContainer();
		TGameObjectPositionalContainer * getGameObjectPositionalContainer();
		TGameObjectSceneContainer * getGameObjectSceneContainer();
		TGameObjectTripolloDreamsContainer * getGameObjectTripolloDreamsContainer();
		TGameObjectTripollitoContainer * getGameObjectTripollitoContainer();
		TGameObjectTentetiesoContainer * getGameObjectTentetiesoContainer();
		TGameObjectEyeContainer * getGameObjectEyeContainer();
		TGameObjectBee_ButterflyContainer * getGameObjectBeeButterflyContainer();
		TGameObjectCarnivorousPlantContainer * getGameObjectCarnivorousPlantContainer();
		TGameObjectScaredPlantContainer * getGameObjectScaredPlantContainer();
		TGameObjectSnakeCreeperContainer * getGameObjectSnakeCreeperContainer();
		TGameObjectTriggerBoxContainer * getGameObjectTriggerBoxContainer();
		TGameObjectTriggerCapsuleContainer * getGameObjectTriggerCapsuleContainer();
		TGameObjectViewportContainer * getGameObjectViewportContainer();
		TGameObjectSignPostContainer* getGameObjectSignPostContainer();

		TGameObjectPortalContainer * getGameObjectPortalContainer();

		TGameObjectPhysicsContainer * getGameObjectPhysicsContainer();
		TGameObjectPhysicsCharacterContainer * getGameObjectPhysicsCharacterContainer();
		TGameObjectPhysicsComplexContainer * getGameObjectPhysicsComplexContainer();
		TGameObjectPhysicsComplexConvexContainer * getGameObjectPhysicsComplexConvexContainer();
		TGameObjectPhysicsComplexTriangleContainer * getGameObjectPhysicsComplexTriangleContainer();
		TGameObjectPhysicsSimpleContainer * getGameObjectPhysicsSimpleContainer();
		TGameObjectPhysicsSimpleBoxContainer * getGameObjectPhysicsSimpleBoxContainer();
		TGameObjectPhysicsSimpleCapsuleContainer * getGameObjectPhysicsSimpleCapsuleContainer();
		TGameObjectPhysicsVolumeContainer * getGameObjectPhysicsVolumeContainer();
		TGameObjectPhysicsVolumeBoxContainer * getGameObjectPhysicsVolumeBoxContainer();
		TGameObjectPhysicsVolumeCapsuleContainer * getGameObjectPhysicsVolumeCapsuleContainer();

		TGameObjectLogicContainer * getGameObjectLogicContainer();

		TGameObjectUsableContainer * getGameObjectUsableContainer();

		TGameObjectSoundContainer* getGameObjectSoundContainer();
		TGameObjectContainer* getAmbientSoundContainer();



		///// Load level from the given file
		///// @param levelFileName name of the level file
		//void loadLevel (const std::string& levelFileName);

		/// Unload data from current level
		/// (i.e, clear all object lists, destroy landscape
		/// and so on)
		void unloadLevel();

		/// init object
		/// @param pointer to the application object
		void init(ApplicationPtr app);

		void initGame();
		void setLevelname(const std::string& filename);

		bool loadConfig();

		/// Free resources
		void cleanUp();

		/// Reset game objects
		void resetAll();

		//Trajectory Creator
		void createTrajectory(TTrajectoryParameters tTrajectoryParameters);

		//Scene Node Creator
		void createSceneNode(std::string name,TRenderComponentPositionalParameters tRenderComponentPositionalParameters);

		//Walkability Map Creator
		void createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters);

		/// Update world state
		/// @param elapsedTime time since last update
		void update(double elapsedSeconds);

		/// Perform some additional tasks after the logic update (i.e, change the state)
		void postUpdate();

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

		/// Facade method to prevent input handling when ony's playing his 'dying' animation
		bool isOnyDying() const;
		bool isOnyHit() const;

		/// 
		void toggleTreeVisibility();
		
		/// Change world to the one specified by the passed parameter
		/// @param currentworld world to change to
		void setWorld (int newWorld);

		/// returns NIGHTMARES or DREAMS depending on current world state
		int getWorld();
		static int getMyInstanceWorld();

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
		Ogre::Vector3 getGameObjectOnyPosition();

		/// Return GameObjectViewport
		GameObjectViewportPtr getGameObjectViewport();

		/// Return GameObjectFlashLight
		GameObjectFlashLightPtr getGameObjectFlashLight();
		GameObjectPillowPtr getGameObjectPillow();

		/// Return the application pointer
		ApplicationPtr getParent();

		/// 
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

		double getClosestChangeWorldDistance(Vector3 objectPosition);

		static LogicComponentOny* getOny();

		static void victory();

		// END lua scripts

		void useWeapon();
		void stopUsingWeapon();

		void useObject();

		void setGodMode(bool activated);
		bool isGodMode();

		void setChangeWorldTimes();
		double getChangeWorldElapsedTime() const;
		double getChangeWorldTotalTime() const;

		/// Add the game object pointer to the objects List
		/// @param gameObject pointer to the object to add to the main list
		void addGameObject(GameObjectPtr gameObject);
		void addGameObjectBee_Butterfly(GameObjectBee_ButterflyPtr gameObjectBee_Butterfly);
		void addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet);
		void addGameObjectBush(GameObjectBushPtr gameObjectBush);
		void addGameObjectCarnivorousPlant(GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant);
		void addGameObjectClockPiece(GameObjectClockPiecePtr pGameObjectClockPiece);
		void addGameObjectCloud(GameObjectCloudPtr gameObjectCloud);
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
		void addGameObjectPlane(GameObjectPlanePtr pGameObjectPlane);
		void addGameObjectPlataform(GameObjectPlataformPtr pGameObjectPlataform);
		void addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal);
		void addGameObjectProvisionalEntity(GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity);
		void addGameObjectScaredPlant(GameObjectScaredPlantPtr pGameObjectScaredPlant);
		void addGameObjectScene(GameObjectScenePtr pGameObjectScene);
		void addGameObjectScepter(GameObjectScepterPtr pGameObjectScepter);
		void addGameObjectSignPost(GameObjectSignPostPtr pGameObjectSignPost);
		void addGameObjectSkyBody(GameObjectSkyBodyPtr pGameObjectSkyBody);
		void addGameObjectSnakeCreeper(GameObjectSnakeCreeperPtr pGameObjectSnakeCreeper);
		void addGameObjectSound(GameObjectSoundPtr pGameObjectSound);
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
		void addGameObjectWoodBox(GameObjectWoodBoxPtr pGameObjectWoodBox);
		void addGameObjectWater(GameObjectWaterPtr pGameObjectWater);
		void addGameObjectTreeComplex(GameObjectTreeComplexPtr pGameObjectTreeComplex);
		void addGameObjectFog(GameObjectFogPtr pGameObjectFog);
		void addGameObjectTower(GameObjectTowerPtr pGameObjectTower);
		void addGameObjectCameraTrigger(GameObjectCameraTriggerPtr pGameObjectCameraTrigger);
		void addGameObjectActionTrigger(GameObjectActionTriggerPtr pGameObjectActionTrigger);

		void activateChangeWorld();
		void activateChangeWorldFast();

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();

		void playSoundFromGameObject(const std::string& objectName, const std::string& soundID);

		double CHANGE_WORLD_RADIUM;
		double DEFAULT_TRAJECTORY_SPEED;

		// Add a diamond tree-diamond link.
		// Since the order the game objects are processed in can't be resolved, 
		// we need to keep track of the names, so the objects can be attached when 
		// the whole level has been loaded.
		void addDiamondTreeLink(const std::string& diamond, const std::string& diamondTree);
		// Append child diamonds to a diamond tree, and link the parent to its children)
		void resolveDiamondTreeLinks();

	private:		
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
		TGameObjectScaredPlantContainer mGameObjectScaredPlantContainer;
		TGameObjectDiamondTreeContainer mGameObjectDiamondTreeContainer;
		TGameObjectDiamondContainer mGameObjectDiamondContainer;
		TGameObjectSignPostContainer mGameObjectSignPostContainer;

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

		TGameObjectFlashLightContainer mGameObjectFlashLightContainer;
		GameObjectPillowPtr mGameObjectPillow;

		TGameObjectLogicContainer mGameObjectLogicContainer;
		TGameObjectUsableContainer mGameObjectUsableContainer;

		TGameObjectViewportContainer mGameObjectViewportContainer;

		TGameObjectSoundContainer mGameObjectSoundContainer;
		TGameObjectContainer mAmbientSoundContainer;


		std::string mDefaultAmbientSoundIDDreams; //Sound id
		std::string mDefaultAmbientSound;//Game object name
		std::string mDefaultAmbientSoundIDNightmares;

		void clearContainers();

		bool mGameOver;

		// Besides being over, the game has been beaten
		bool mGameBeaten;

		bool mGodMode;

		// Current level
		std::string level;

		//Changeworld functions and variables
		void changeToWorld(int newWorld, double perc);
		void changeWorldFinished(int newWorld);
		void changeWorldStarted(int newWorld);


		double mChangeWorldTotalTime;
		double mChangeWorldElapsedTime;
		bool mRandomChangeWorld;
		bool mIsChangingWorld;
		int mWorld;

		EventManagerPtr mEventManager;
		EventProcessorPtr mEventProcessor;
		GameWorldManagerPtr mThis;

		static GameWorldManager* mInst;

		//Keys contain the game object diamonds bound to a tree; 
		//Values, the trees.
		std::map<std::string, std::string> mDiamondTreeLinks;
	};
}
#endif