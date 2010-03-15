#ifndef __OUAN__H__
#define __OUAN__H__

#include <map>
#include <string>
#include <iostream>
#include <fstream> 
#include <sys/stat.h>
#include <Ogre.h>
#include <ois/OIS.h>

#include "ConfigKeys.h"

#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

#include "TinyXML/tinyxml.h"

#include "Event/EventDefs.h"

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}
#define _CRT_SECURE_NO_WARNINGS

namespace OUAN
{
	//-------------------------------------
	//	Basic Types
	//-------------------------------------
	typedef Ogre::String String;
	typedef Ogre::StringConverter StringConverter;
	typedef Ogre::Vector2 Vector2;
	typedef Ogre::Vector3 Vector3;
	typedef Ogre::Vector4 Vector4;
	typedef Ogre::Quaternion Quaternion;
	typedef Ogre::Real Real;
	typedef Ogre::ColourValue ColourValue;


	//-------------------------------------
	//	Core module-related constants, type definitions and forwarded declarations
	//-------------------------------------
		const int AI_FPS=60;
		const int SKIP_TICKS=1000000/AI_FPS;
		const int MAX_FRAMESKIP=5;
		const int DEFAULT_KEY_BUFFER=500000;

		const int DEBUGMODE_NONE=0;
		const int DEBUGMODE_PERFORMANCE=1;
		const int DEBUGMODE_PHYSICS=2;
		const int DEBUGMODE_WIREFRAME=3;
		const int DEBUGMODE_POINTS=4;

		const std::string DEFAULT_WIN_NAME="OUAN";

		//forward declarations
		class GameStateManager;
		class GameState;
		class GameRunningState;
		class MainMenuState;
		class Application;

		typedef boost::shared_ptr<GameStateManager> GameStateManagerPtr;
		typedef boost::shared_ptr<GameState> GameStatePtr;
		typedef boost::shared_ptr<Application> ApplicationPtr;

	//---------------
	// Game module-related constants, type definitions and forwarded declarations
	//---------------

		class GameWorldManager;
		class Component;

		const int DREAMS=0;
		const int NIGHTMARES=1;

		const std::string LEVEL_NONE="None";
		const std::string LEVEL_TEST="TestLevel";
		const std::string LEVEL_SANDBOX="Sandbox";
		const std::string LEVEL_CLOCK="Clock";
		const std::string LEVEL_1="Level1";
		const std::string LEVEL_2="Level2";

		//Render Components
		class RenderComponent;
		class TRenderComponentParameters;
		typedef boost::shared_ptr<RenderComponent> RenderComponentPtr;

		class RenderComponentBillboardSet;
		class TRenderComponentBillboardSetParameters;
		class TRenderComponentBillboardParameters;
		typedef boost::shared_ptr<RenderComponentBillboardSet> RenderComponentBillboardSetPtr;

		class RenderComponentCamera;
		class TRenderComponentCameraParameters;
		typedef boost::shared_ptr<RenderComponentCamera> RenderComponentCameraPtr;

		class RenderComponentEntity;
		class TRenderComponentEntityParameters;
		class TRenderComponentSubEntityParameters;
		typedef boost::shared_ptr<RenderComponentEntity> RenderComponentEntityPtr;

		class RenderComponentLight;
		class TRenderComponentLightParameters;
		typedef boost::shared_ptr<RenderComponentLight> RenderComponentLightPtr;

		class RenderComponentViewport;
		class TRenderComponentViewportParameters;
		typedef boost::shared_ptr<RenderComponentViewport> RenderComponentViewportPtr;

		class RenderComponentParticleSystem;
		class TRenderComponentParticleSystemParameters;
		typedef boost::shared_ptr<RenderComponentParticleSystem> RenderComponentParticleSystemPtr;

		class RenderComponentScene;
		class TRenderComponentSkyDomeParameters;
		class TRenderComponentSkyBoxParameters;
		class TRenderComponentSceneParameters;
		typedef boost::shared_ptr<RenderComponentScene> RenderComponentScenePtr;

		class RenderComponentPositional;
		class TRenderComponentPositionalParameters;
		typedef boost::shared_ptr<RenderComponentPositional> RenderComponentPositionalPtr;

		class RenderComponentViewport;
		class TRenderComponentViewportParameters;
		typedef boost::shared_ptr<RenderComponentViewport> RenderComponentViewportPtr;

		const std::string COMPONENT_TYPE_RENDER="RenderComponent";
		const std::string COMPONENT_TYPE_RENDER_BILLBOARD_SET="RenderComponentBillboardSet";
		const std::string COMPONENT_TYPE_RENDER_CAMERA="RenderComponentCamera";
		const std::string COMPONENT_TYPE_RENDER_ENTITY="RenderComponentEntity";
		const std::string COMPONENT_TYPE_RENDER_LIGHT="RenderComponentLight";
		const std::string COMPONENT_TYPE_RENDER_PARTICLE_SYSTEM="RenderComponentParticleSystem";
		const std::string COMPONENT_TYPE_RENDER_POSITIONAL="RenderComponentPositional";
		const std::string COMPONENT_TYPE_RENDER_SCENE="RenderComponentScene";
		const std::string COMPONENT_TYPE_RENDER_VIEWPORT="RenderComponentViewport";

		//Physics components
		class PhysicsComponentCharacter;
		class TPhysicsComponentCharacterParameters;
		typedef boost::shared_ptr<PhysicsComponentCharacter> PhysicsComponentCharacterPtr;

		class PhysicsComponentComplex;
		class TPhysicsComponentComplexParameters;
		typedef boost::shared_ptr<PhysicsComponentComplex> PhysicsComponentComplexPtr;

		class PhysicsComponentComplexConvex;
		class TPhysicsComponentComplexConvexParameters;
		typedef boost::shared_ptr<PhysicsComponentComplexConvex> PhysicsComponentComplexConvexPtr;

		class PhysicsComponentComplexTriangle;
		class TPhysicsComponentComplexTriangleParameters;
		typedef boost::shared_ptr<PhysicsComponentComplexTriangle> PhysicsComponentComplexTrianglePtr;

		class PhysicsComponentSimpleCapsule;
		class TPhysicsComponentSimpleCapsuleParameters;
		typedef boost::shared_ptr<PhysicsComponentSimpleCapsule> PhysicsComponentSimpleCapsulePtr;

		class PhysicsComponentSimpleBox;
		class TPhysicsComponentSimpleBoxParameters;
		typedef boost::shared_ptr<PhysicsComponentSimpleBox> PhysicsComponentSimpleBoxPtr;

		class PhysicsComponentVolumeCapsule;
		class TPhysicsComponentVolumeCapsuleParameters;
		typedef boost::shared_ptr<PhysicsComponentVolumeCapsule> PhysicsComponentVolumeCapsulePtr;

		class PhysicsComponentVolumeBox;
		class TPhysicsComponentVolumeBoxParameters;
		typedef boost::shared_ptr<PhysicsComponentVolumeBox> PhysicsComponentVolumeBoxPtr;

		const std::string COMPONENT_TYPE_PHYSICS="PhysicsComponent";
		const std::string COMPONENT_TYPE_PHYSICS_CHARACTER="PhysicsComponentCharacter";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX="PhysicsComponentComplex";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX_MOVABLE="PhysicsComponentComplexConvex";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX_NON_MOVABLE="PhysicsComponentComplexTriangle";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE="PhysicsComponentSimple";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE_CAPSULE="PhysicsComponentSimpleCapsule";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE_BOX="PhysicsComponentSimpleBox";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME="PhysicsComponentVolume";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_CAPSULE="PhysicsComponentVolumeCapsule";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_BOX="PhysicsComponentVolumeBox";

		//Logic Components
		class LogicComponent;
		class TLogicComponentParameters;
		typedef boost::shared_ptr<LogicComponent> LogicComponentPtr;

		class LogicComponentEvent;
		class TLogicComponentEventParameters;
		typedef boost::shared_ptr<LogicComponentEvent> LogicComponentEventPtr;

		class LogicComponentWorldExistance;
		class TLogicComponentWorldExistanceParameters;
		typedef boost::shared_ptr<LogicComponentWorldExistance> LogicComponentWorldExistancePtr;

		const std::string COMPONENT_TYPE_LOGIC="LogicComponent";
		const std::string COMPONENT_TYPE_LOGIC_EVENT="LogicComponentEvent";
		const std::string COMPONENT_TYPE_LOGIC_WORLD_EXISTANCE="LogicComponentWorldExistance";

		///////////////////////////////////////////////////////////////////

		//Game Object Specializations
		class GameObject;
		class TGameObjectParameters;
		typedef boost::shared_ptr<GameObject> GameObjectPtr;

		typedef std::map<std::string,GameObjectPtr> TGameObjectContainer;
		typedef TGameObjectContainer::iterator TGameObjectContainerIterator;

		typedef std::vector<GameObjectPtr> TGameObjectPositionalContainer;
		typedef std::vector<GameObjectPtr> TGameObjectMovableContainer;
		typedef std::vector<GameObjectPtr> TGameObjectNonMovableContainer;
		typedef std::vector<GameObjectPtr> TGameObjectMovableEntityContainer;
		typedef std::vector<GameObjectPtr> TGameObjectNonMovableEntityContainer;
		typedef std::vector<GameObjectPtr> TGameObjectEntityContainer;
		
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsCharacterContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsComplexContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsComplexConvexContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsComplexTriangleContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsSimpleContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsSimpleBoxContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsSimpleCapsuleContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsVolumeContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsVolumeBoxContainer;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsVolumeCapsuleContainer;

		////////////////////////////////////////////////////////////////////

		class GameObjectScene;
		class TGameObjectSceneParameters;
		typedef boost::shared_ptr<GameObjectScene> GameObjectScenePtr;

		class GameObjectViewport;
		class TGameObjectViewportParameters;
		typedef boost::shared_ptr<GameObjectViewport> GameObjectViewportPtr;

		class GameObjectProvisionalEntity;
		class TGameObjectProvisionalEntityParameters;
		typedef boost::shared_ptr<GameObjectProvisionalEntity> GameObjectProvisionalEntityPtr;

		class GameObjectTerrainTriangle;
		class TGameObjectTerrainTriangleParameters;
		typedef boost::shared_ptr<GameObjectTerrainTriangle> GameObjectTerrainTrianglePtr;

		class GameObjectTerrainConvex;
		class TGameObjectTerrainConvexParameters;
		typedef boost::shared_ptr<GameObjectTerrainConvex> GameObjectTerrainConvexPtr;

		class GameObjectLight;
		class TGameObjectLightParameters;
		typedef boost::shared_ptr<GameObjectLight> GameObjectLightPtr;

		class GameObjectCamera;
		class TGameObjectCameraParameters;
		typedef boost::shared_ptr<GameObjectCamera> GameObjectCameraPtr;

		class GameObjectBillboardSet;
		class TGameObjectBillboardSetParameters;
		typedef boost::shared_ptr<GameObjectBillboardSet> GameObjectBillboardSetPtr;

		class GameObjectParticleSystem;
		class TGameObjectParticleSystemParameters;
		typedef boost::shared_ptr<GameObjectParticleSystem> GameObjectParticleSystemPtr;

		class GameObjectOny;
		class TGameObjectOnyParameters;
		typedef boost::shared_ptr<GameObjectOny> GameObjectOnyPtr;

		class GameObjectTripollo;
		class TGameObjectTripolloParameters;
		typedef boost::shared_ptr<GameObjectTripollo> GameObjectTripolloPtr;

		class GameObjectPortal;
		class TGameObjectPortalParameters;
		typedef boost::shared_ptr<GameObjectPortal> GameObjectPortalPtr;

		class GameObjectEye;
		class TGameObjectEyeParameters;
		typedef boost::shared_ptr<GameObjectEye> GameObjectEyePtr;

		class GameObjectItem1UP;
		class TGameObjectItem1UPParameters;
		typedef boost::shared_ptr<GameObjectItem1UP> GameObjectItem1UPPtr;

		class GameObjectItemMaxHP;
		class TGameObjectItemMaxHPParameters;
		typedef boost::shared_ptr<GameObjectItemMaxHP> GameObjectItemMaxHPPtr;

		class GameObjectVolumeBox;
		class TGameObjectVolumeBoxParameters;
		typedef boost::shared_ptr<GameObjectVolumeBox> GameObjectVolumeBoxPtr;

		class GameObjectVolumeCapsule;
		class TGameObjectVolumeCapsuleParameters;
		typedef boost::shared_ptr<GameObjectVolumeCapsule> GameObjectVolumeCapsulePtr;

		class GameObjectNightGoblin;
		class TGameObjectNightGoblinParameters;
		typedef boost::shared_ptr<GameObjectNightGoblin> GameObjectNightGoblinPtr;

		class GameObjectCryKing;
		class TGameObjectCryKingParameters;
		typedef boost::shared_ptr<GameObjectCryKing> GameObjectCryKingPtr;

		class GameObjectDragon;
		class TGameObjectDragonParameters;
		typedef boost::shared_ptr<GameObjectDragon> GameObjectDragonPtr;

		class GameObjectMagicClock;
		class TGameObjectMagicClockParameters;
		typedef boost::shared_ptr<GameObjectMagicClock> GameObjectMagicClockPtr;

		class GameObjectPillow;
		class TGameObjectPillowParameters;
		typedef boost::shared_ptr<GameObjectPillow> GameObjectPillowPtr;

		class GameObjectFlashlight;
		class TGameObjectFlashlightParameters;
		typedef boost::shared_ptr<GameObjectFlashlight> GameObjectFlashlightPtr;

		class GameObjectTententieso;
		class TGameObjectTententiesoParameters;
		typedef boost::shared_ptr<GameObjectTententieso> GameObjectTententiesoPtr;

		class GameObjectBee_Butterfly;
		class TGameObjectBee_ButterflyParameters;
		typedef boost::shared_ptr<GameObjectBee_Butterfly> GameObjectBee_ButterflyPtr;

		class GameObjectSnakeCreeper_CarnivorousPlant;
		class TGameObjectSnakeCreeper_CarnivorousPlantParameters;
		typedef boost::shared_ptr<GameObjectSnakeCreeper_CarnivorousPlant> GameObjectSnakeCreeper_CarnivorousPlantPtr;

		class GameObjectDiamondTree;
		class TGameObjectDiamondTreeParameters;
		typedef boost::shared_ptr<GameObjectDiamondTree> GameObjectDiamondTreePtr;

		class GameObjectStorybook;
		class TGameObjectStorybookParameters;
		typedef boost::shared_ptr<GameObjectStorybook> GameObjectStorybookPtr;

		class GameObjectHeart;
		class TGameObjectHeartParameters;
		typedef boost::shared_ptr<GameObjectHeart> GameObjectHeartPtr;

		class GameObjectDiamond;
		class TGameObjectDiamondParameters;
		typedef boost::shared_ptr<GameObjectDiamond> GameObjectDiamondPtr;

		class GameObjectScaredPlant;
		class TGameObjectScaredPlantParameters;
		typedef boost::shared_ptr<GameObjectScaredPlant> GameObjectScaredPlantPtr;

		class GameObjectTree;
		class TGameObjectTreeParameters;
		typedef boost::shared_ptr<GameObjectTree> GameObjectTreePtr;

		class GameObjectClockPiece;
		class TGameObjectClockPieceParameters;
		typedef boost::shared_ptr<GameObjectClockPiece> GameObjectClockPiecePtr;

		typedef std::vector<GameObjectScenePtr> TGameObjectSceneContainer;
		typedef std::vector<GameObjectViewportPtr> TGameObjectViewportContainer;
		typedef std::vector<GameObjectTerrainConvexPtr> TGameObjectTerrainConvexContainer;
		typedef std::vector<GameObjectTerrainTrianglePtr> TGameObjectTerrainTriangleContainer;
		typedef std::vector<GameObjectLightPtr> TGameObjectLightContainer;
		typedef std::vector<GameObjectCameraPtr> TGameObjectCameraContainer;
		typedef std::vector<GameObjectBillboardSetPtr> TGameObjectBillboardSetContainer;
		typedef std::vector<GameObjectParticleSystemPtr> TGameObjectParticleSystemContainer;
		typedef std::vector<GameObjectOnyPtr> TGameObjectOnyContainer;
		typedef std::vector<GameObjectTripolloPtr> TGameObjectTripolloContainer;
		typedef std::vector<GameObjectPortalPtr> TGameObjectPortalContainer;
		typedef std::vector<GameObjectEyePtr> TGameObjectEyeContainer;
		typedef std::vector<GameObjectItem1UPPtr> TGameObjectItem1UPContainer;
		typedef std::vector<GameObjectItemMaxHPPtr> TGameObjectItemMaxHPContainer;
		typedef std::vector<GameObjectVolumeBoxPtr> TGameObjectVolumeBoxContainer;
		typedef std::vector<GameObjectVolumeCapsulePtr> TGameObjectVolumeCapsuleContainer;
		typedef std::vector<GameObjectNightGoblinPtr> TGameObjectNightGoblinContainer;
		typedef std::vector<GameObjectCryKingPtr> TGameObjectCryKingContainer;
		typedef std::vector<GameObjectDragonPtr> TGameObjectDragonContainer;
		typedef std::vector<GameObjectMagicClockPtr> TGameObjectMagicClockContainer;
		typedef std::vector<GameObjectPillowPtr> TGameObjectPillowContainer;
		typedef std::vector<GameObjectFlashlightPtr> TGameObjectFlashlightContainer;
		typedef std::vector<GameObjectTententiesoPtr> TGameObjectTententiesoContainer;
		typedef std::vector<GameObjectBee_ButterflyPtr> TGameObjectBee_ButterflyContainer;
		typedef std::vector<GameObjectSnakeCreeper_CarnivorousPlantPtr> TGameObjectSnakeCreeper_CarnivorousPlantContainer;
		typedef std::vector<GameObjectDiamondTreePtr> TGameObjectDiamondTreeContainer;
		typedef std::vector<GameObjectStorybookPtr> TGameObjectStorybookContainer;
		typedef std::vector<GameObjectHeartPtr> TGameObjectHeartContainer;
		typedef std::vector<GameObjectDiamondPtr> TGameObjectDiamondContainer;
		typedef std::vector<GameObjectScaredPlantPtr> TGameObjectScaredPlantContainer;
		typedef std::vector<GameObjectTreePtr> TGameObjectTreeContainer;
		typedef std::vector<GameObjectTreePtr> TGameObjectClockPieceContainer;

		//Some object have types in mayus for Ogitor convenience
		const std::string GAME_OBJECT_TYPE="object";
		const std::string GAME_OBJECT_TYPE_SCENE="SceneManager";
		const std::string GAME_OBJECT_TYPE_TERRAIN="terrain";
		const std::string GAME_OBJECT_TYPE_LIGHT="Light";
		const std::string GAME_OBJECT_TYPE_CAMERA="Camera";
		const std::string GAME_OBJECT_TYPE_BILLBOARDSET="BillboardSet";
		const std::string GAME_OBJECT_TYPE_PARTICLESYSTEM="Particle";
		const std::string GAME_OBJECT_TYPE_ONY="ony";
		const std::string GAME_OBJECT_TYPE_TRIPOLLO="tripollo";
		const std::string GAME_OBJECT_TYPE_PORTAL="changeworld";
		const std::string GAME_OBJECT_TYPE_EYE="eye";
		const std::string GAME_OBJECT_TYPE_ITEM_1UP="item_1up";
		const std::string GAME_OBJECT_TYPE_ITEM_MAXHP="heartbag";
		const std::string GAME_OBJECT_TYPE_VOLUMEBOX="volume-box";
		const std::string GAME_OBJECT_TYPE_VOLUMECAPSULE="volume-capsule";
		const std::string GAME_OBJECT_TYPE_VIEWPORT="Viewport1";
		const std::string GAME_OBJECT_TYPE_NIGHTGOBLIN="night_goblin";
		const std::string GAME_OBJECT_TYPE_CRYKING="cry_king";
		const std::string GAME_OBJECT_TYPE_DRAGON="dragon";
		const std::string GAME_OBJECT_TYPE_MAGIC_CLOCK="magic_clock";
		const std::string GAME_OBJECT_TYPE_PILLOW="pillow";
		const std::string GAME_OBJECT_TYPE_FLASHLIGHT="flashlight";
		const std::string GAME_OBJECT_TYPE_TENTENTIESO="tentetieso";
		const std::string GAME_OBJECT_TYPE_BEE_BUTTERFLY="bee%butterfly";
		const std::string GAME_OBJECT_TYPE_SNAKE_CREEPER_CARNIVOROUS_PLANT="snake_creeper%carnivorous_plant";
		const std::string GAME_OBJECT_TYPE_DIAMOND_TREE="diamond_tree";
		const std::string GAME_OBJECT_TYPE_STORYBOOK="storybook";
		const std::string GAME_OBJECT_TYPE_HEART="heart";
		const std::string GAME_OBJECT_TYPE_DIAMOND="diamond";
		const std::string GAME_OBJECT_TYPE_SCARED_PLANT="scared_plant";
		const std::string GAME_OBJECT_TYPE_TREE="tree";
		const std::string GAME_OBJECT_TYPE_CLOCK_PIECE="clock_piece";
		///////////////////////////////////////////////////////////////////

		// Event manager-related constants, typedefs and forwarded declarations
		class Event;
		typedef boost::shared_ptr<Event> EventPtr;

		class BaseEventHandler;
		typedef boost::shared_ptr<BaseEventHandler> EventHandlerPtr;

		class EventManager;
		typedef boost::shared_ptr<EventManager> EventManagerPtr;

		class EventProcessor;
		typedef boost::shared_ptr<EventProcessor> EventProcessorPtr;

		class ChangeWorldEvent;
		typedef boost::shared_ptr<ChangeWorldEvent> ChangeWorldEventPtr;

		///////////////////////////////////////////////////////////////////

		typedef boost::shared_ptr<GameWorldManager> GameWorldManagerPtr;
		typedef boost::shared_ptr<Component> ComponentPtr;
		
		typedef std::map<std::string,ComponentPtr> TComponentContainer;
		typedef TComponentContainer::iterator TComponentContainerIterator;

		const int GAMEOBJECT_ID_ZERO_PADDING=6;

		///////////////////////////////////////////////////////////////////

		//-------------------------------------
		//	Trajectory module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		class Trajectory;
		class TTrajectoryParameters;

		class TrajectoryNode;
		class TTrajectoryNodeParameters;

		class TrajectoryManager;
		typedef boost::shared_ptr<TrajectoryManager> TrajectoryManagerPtr;

		//-------------------------------------
		//	Loader module-related constants, type definitions and forwarded declarations
		//-------------------------------------
		class XMLGameObject;
		typedef std::map<std::string,XMLGameObject>::iterator XMLGameObjectContainerIterator;

		class XMLTrajectory;
		typedef std::map<std::string,XMLTrajectory>::iterator XMLTrajectoryContainerIterator;

		class XMLParser;
		class Configuration;
		class LevelLoader;

		const std::string DEFAULT_OGRE_RESOURCE_MANAGER_GROUP="General";

		//Exception messages
		const std::string SCENE_NODE_NOT_FOUND="Scene Parameters not found";
		const std::string VIEWPORT_NODE_NOT_FOUND="Viewport Parameters not found";
		const std::string DREAMS_NODE_NOT_FOUND="Dreams node does not exist or has wrong name in Ogitor";   
		const std::string NIGHTMARES_NODE_NOT_FOUND="Nightmares node does not exist or has wrong name in Ogitor";
		const std::string CUSTOM_PROPERTIES_NODE_NOT_FOUND="Custom Properties node does not exist or has wrong .ctp filename";
		const std::string DREAMS_SHOULD_NOT_EXIST="This object can't have dreams node";  
		const std::string NIGHTMARES_SHOULD_NOT_EXIST="This object can't have nightmares node";  

		typedef boost::shared_ptr<Configuration> ConfigurationPtr;
		typedef boost::shared_ptr<LevelLoader> LevelLoaderPtr;

		const std::string GAME_OBJECT_PARAMETERS_PATH="../../Resources/Levels/GameObjects/";
		const std::string LEVELS_PATH="../../Resources/Levels/";

		///	Type definition for the data structure that'll hold the options:
		/// an STL map of pairs of strings, representing the key and value, respectively
		typedef std::map<std::string, std::string> TConfigMap;

		///Alias for a Config map iterator
		typedef TConfigMap::iterator TConfigMapIterator;
		///Alias for a Config map constant iterator
		typedef TConfigMap::const_iterator TConfigMapConstIterator;

		//-------------------------------------
		//	Graphics module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		const int DEFAULT_OGRE_MIPMAPS_NUMBER=5;
		const std::string MAIN_CAMERA_NAME="Camera";
		const std::string RUNNING_CAMERA_NAME="Camera";
		// Default path constants
		const std::string DEFAULT_OGRE_RESOURCES_PATH="../../Config/resources.cfg";
		const std::string DEFAULT_OGRE_CONFIG_PATH  = "../../Config/ogre.cfg";
		const std::string DEFAULT_OGRE_LOG_PATH = "ogre.log";
		//Fetch the plugins file conditionally, depending on whether we're on debug mode or not
		#ifdef OUAN_DEBUG
				const std::string DEFAULT_OGRE_PLUGINS_PATH="../../Config/plugins-dbg.cfg";
		#else
				const std::string DEFAULT_OGRE_PLUGINS_PATH="../../Config/plugins.cfg";
		#endif	

		const double DEFAULT_MOVE_SPEED = 1;
		const double DEFAULT_ROTATE_SPEED=0.3f;
		const double MOUSE_MOVE_ROTATION_INCREMENT=0.1f;

		typedef enum
		{
			AXIS_POS_X,
			AXIS_NEG_X,
			AXIS_POS_Y,
			AXIS_NEG_Y,
			AXIS_POS_Z,
			AXIS_NEG_Z
		}TCoordinateAxis;

		class RenderSubsystem;
		

		typedef boost::shared_ptr<RenderSubsystem> RenderSubsystemPtr;

		///Camera Manager
		class CameraManager;
		class CameraController;
		class CameraControllerFirstPerson;
		class CameraControllerThirdPerson;
		class CameraControllerFixedFirstPerson;
		class CameraControllerFixedThirdPerson;
		class CameraControllerTrajectory;

		typedef std::map<std::string,TRenderComponentCameraParameters> TCameraParamsContainer;
		typedef TCameraParamsContainer::iterator TCameraParamsContainerIterator;

		/// Ogre root object
		typedef boost::shared_ptr<Ogre::Root> RootPtr;

		typedef enum 
		{
			CAMERA_NONE,
			CAMERA_FIXED_FIRST_PERSON,
			CAMERA_FIXED_THIRD_PERSON,
			CAMERA_FIRST_PERSON,
			CAMERA_THIRD_PERSON,
			CAMERA_TRAJECTORY
		}TCameraControllerType;

		//-------------------------------------
		//	Physics module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		class PhysicsSubsystem;
		typedef boost::shared_ptr<PhysicsSubsystem> PhysicsSubsystemPtr;

		enum GameGroup
		{
			GROUP_NON_COLLIDABLE,
			GROUP_COLLIDABLE_NON_PUSHABLE,
			GROUP_COLLIDABLE_PUSHABLE,
		};

		#define GROUP_COLLIDABLE_MASK (1 << GROUP_COLLIDABLE_NON_PUSHABLE) | (1 << GROUP_COLLIDABLE_PUSHABLE)
		#define NXS_PATH "file:../../Resources/Graphics/NxModels"

		//-------------------------------------
		//  Movements masks
		//-------------------------------------

		bool isPressedMenu();			// Go to main menu
		bool isPressedPause();			// Go to pause menu

		bool isPressedJump();			// Jump
		bool isPressedDoAction();		// Perform an action
		bool isPressedUseWeapon();		// Use the pillow (dream) or shoot (nightmare)
		bool isPressedWeaponAction();	// Change holder hand (dream) or recharge (nightmare)

		//bool isPressedGoForward();		// Go forward
		bool isPressedGoBack();			// Go back
		bool isPressedGoLeft();			// Go to left
		bool isPressedGoRight();		// Go to right

		bool isPressedWalk();			// Walk mode
		bool isPressedAutoPoint();		// Automatic pointer
		bool isPressedRotateLeft();		// Rotate color to left
		bool isPressedRotateRight();	// Rotate color to right

		const int MOV_NOWHERE = 0;
		const int MOV_GO_FORWARD = 1;
		const int MOV_GO_BACK = 2;
		const int MOV_GO_LEFT = 4;
		const int MOV_GO_RIGHT = 8;
		const int MOV_JUMP = 16;
		const int MOV_WALK = 32;

		const int MOV_FORWARD_OR_BACK = MOV_GO_FORWARD | MOV_GO_BACK;
		const int MOV_LEFT_OR_RIGHT = MOV_GO_LEFT | MOV_GO_RIGHT;
}

#endif