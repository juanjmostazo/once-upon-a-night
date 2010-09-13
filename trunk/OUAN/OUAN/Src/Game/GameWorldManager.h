#ifndef GAMEWORLDMANAGERH_H
#define GAMEWORLDMANAGERH_H
#include "../OUAN.h"
#include "../Event/Event.h"
#include "LevelEvents.h"
namespace OUAN
{
	//forward declarations
	class GameObjectSound;
	typedef boost::shared_ptr<GameObjectSound> GameObjectSoundPtr;

	typedef std::map<std::string, std::string> TNestLinkMap;

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
		TGameObjectTripolloContainer * getGameObjectTripolloContainer();
		TGameObjectTentetiesoContainer * getGameObjectTentetiesoContainer();
		TGameObjectEyeContainer * getGameObjectEyeContainer();
		TGameObjectBee_ButterflyContainer * getGameObjectBeeButterflyContainer();
		TGameObjectCarnivorousPlantContainer * getGameObjectCarnivorousPlantContainer();
		TGameObjectScaredPlantContainer * getGameObjectScaredPlantContainer();
		TGameObjectSnakeCreeperContainer * getGameObjectSnakeCreeperContainer();
		TGameObjectTriggerBoxContainer * getGameObjectTriggerBoxContainer();
		TGameObjectTriggerCapsuleContainer * getGameObjectTriggerCapsuleContainer();
		TGameObjectViewportContainer * getGameObjectViewportContainer();
		TGameObjectSignpostContainer* getGameObjectSignpostContainer();
		TGameObjectNestContainer* getGameObjectNestContainer();


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
		std::string getLevelname();

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
		static LogicComponent* getCryKing();
		static LogicComponent* getBomb();

		static void victory();

		static void setCheckPointLUA(std::string checkpoint,int checkpointNumber);
		static int getCheckPointNumberLUA();

		static GameObject* getGameObject(const std::string& objectName);
		// END lua scripts

		static bool isChangingWorldLUA();
		bool isChangingWorld();

		void setCheckPointPosition(Vector3 checkpoint);
		Vector3 getCheckPointPosition() const;
		void setCheckPointOrientation(Quaternion checkpoint);
		Quaternion getCheckPointOrientation() const;
		void setCheckPointNumber(int checkpointNumber);
		int getCheckPointNumber() const;
		void setCheckPointWorld(int world);
		int getCheckPointWorld() const;


		void useWeapon();
		void stopUsingWeapon();

		void useObject();

		void setGodMode(bool activated);
		bool isGodMode();

		void setChangeWorldTimes();
		double getChangeWorldElapsedTime() const;
		double getChangeWorldTotalTime() const;

		static void restartBombPositionLUA();
		void restartBombPosition();

		static void initBombPuzzleLUA();
		void initBombPuzzle();


		/// Add the game object pointer to the objects List
		/// @param gameObject pointer to the object to add to the main list
		void addGameObject(GameObjectPtr gameObject);
		void addGameObjectBee_Butterfly(GameObjectBee_ButterflyPtr gameObjectBee_Butterfly);
		void addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet);
		void addGameObjectTraspasable(GameObjectTraspasablePtr gameObjectTraspasable);
		void addGameObjectCarnivorousPlant(GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant);
		void addGameObjectClockPiece(GameObjectClockPiecePtr pGameObjectClockPiece);
		void addGameObjectCloud(GameObjectCloudPtr gameObjectCloud);
		void addGameObjectCryKing(GameObjectCryKingPtr pGameObjectCryKing);
		void addGameObjectDiamond(GameObjectDiamondPtr pGameObjectDiamond);
		void addGameObjectDiamondTree(GameObjectDiamondTreePtr pGameObjectDiamondTree);
		void addGameObjectDoor(GameObjectDoorPtr pGameObjectDoor);
		void addGameObjectBoss(GameObjectBossPtr pGameObjectBoss);
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
		void addGameObjectSignPost(GameObjectSignpostPtr pGameObjectSignPost);
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
		void addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo);
		void addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport);
		void addGameObjectWoodBox(GameObjectWoodBoxPtr pGameObjectWoodBox);
		void addGameObjectWater(GameObjectWaterPtr pGameObjectWater);
		void addGameObjectTreeComplex(GameObjectTreeComplexPtr pGameObjectTreeComplex);
		void addGameObjectFog(GameObjectFogPtr pGameObjectFog);
		void addGameObjectTower(GameObjectTowerPtr pGameObjectTower);
		void addGameObjectCameraTrigger(GameObjectCameraTriggerPtr pGameObjectCameraTrigger);

		void addGameObjectNest(GameObjectNestPtr pGameObjectNest);
		void addGameObjectSwitch(GameObjectSwitchPtr pGameObjectSwitch);
		void addGameObjectTotem(GameObjectTotemPtr pGameObjectTotem);
		void addGameObjectBomb(GameObjectBombPtr pGameObjectBomb);
		void addGameObjectLevelEntrance(GameObjectLevelEntrancePtr pGameObjectLevelEntrance);

		void addGameObjectInvisibleWall(GameObjectInvisibleWallPtr pGameObjectInvisibleWall);
		void addGameObjectBreakableRock(GameObjectBreakableRockPtr pGameObjectBreakableRock);

		void activateChangeWorld();
		void activateChangeWorldFast();

		void setDreamsRender();
		void setNightmaresRender();
		void setChangeWorldRender();
		void setChangeWorldFactor(double factor);

		void playSoundFromGameObject(const std::string& objectName, const std::string& soundID);

		double CHANGE_WORLD_RADIUM;
		double DEFAULT_TRAJECTORY_SPEED;
		double DEFAULT_MAX_UPDATE_RADIO_UPPER_LIMIT;
		double DEFAULT_MAX_UPDATE_RADIO;
		double DEFAULT_MAX_RENDER_RADIO;
		double CHANGE_FLASHLIGHT_COLOUR_SPEED;

		// Add an item nest link.
		// Since the order the game objects are processed in can't be resolved, 
		// we need to keep track of the names, 
		// so the objects can be attached later
		void addNestLink(const std::string& object, const std::string& nest);
		void resolveNestLinks();

		void loadFlashlightDecalMaterials();

		bool isFirstMsgBox() const;
		void setFirstMsgBox(bool firstMsgBox);

		bool isFirstSignpostHit() const;
		void setFirstSignpostHit(bool firstSignpostHit);

		void increaseOnyDiamonds(int amount=1);

		EventProcessorPtr getEventProcessor(); 

		static void addExecutedLevelEventLUA(std::string cutscene);
		void addExecutedLevelEvent(std::string cutscene);
		static bool hasExecutedLevelEventLUA(std::string cutscene);
		bool hasExecutedLevelEvent(std::string cutscene);
		void checkpointLevelEvents();

		void rescaleViewport(double left, double top, double width, double height);

	private:		
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
		TGameObjectTripolloContainer mGameObjectTripolloContainer;
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
		TGameObjectSignpostContainer mGameObjectSignPostContainer;
		TGameObjectNestContainer mGameObjectNestContainer;

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

		Vector3 mCheckPointPosition;
		Quaternion mCheckPointOrientation;
		int mCheckPointNumber;
		int mCheckPointWorld;

		EventManagerPtr mEventManager;
		EventProcessorPtr mEventProcessor;
		GameWorldManagerPtr mThis;

		static GameWorldManager* mInst;

		//Keys contain the game objects bound to a nest; 
		//Values, the nests.
		std::map<std::string, std::string> mNestLinks;

		bool mFirstMsgBox;
		bool mFirstSignpostHit;

		//Control over executed cutscenes
			//Current checkpoint events
		std::set<std::string> mExecutedLevelEvents;
			//Events saved from last checkpoint
		std::set<std::string> mExecutedLevelEventsPermanent;
	};
}
#endif