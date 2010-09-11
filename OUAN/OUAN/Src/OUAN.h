#ifndef __OUAN__H__
#define __OUAN__H__

#include "ConfigKeys.h"

#include "TinyXML/tinyxml.h"

#include "Logic/LogicDefs.h"

#include "Utils/Logger.h"

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
	//	Input module-related constants, type definitions and forwarded declarations
	//-------------------------------------
		CLASS_DECLARATIONS_NO_PARAMS(FullInputManager);

	//-------------------------------------
	//	Core module-related constants, type definitions and forwarded declarations
	//-------------------------------------
		const int AI_FPS=60;
		const int SKIP_TICKS=1000000/AI_FPS;
		const int MAX_FRAMESKIP=5;
		const int DEFAULT_KEY_BUFFER=200000; // = 200ms

		const int DEBUGMODE_NONE=0;
		const int DEBUGMODE_PERFORMANCE=1;
		const int DEBUGMODE_PHYSICS=2;
		const int DEBUGMODE_WIREFRAME=3;
		const int DEBUGMODE_POINTS=4;
		const int DEBUGMODE_VOLUMES=5;

		const std::string DEFAULT_WIN_NAME="OUAN";

		//forward declarations
		CLASS_DECLARATIONS_NO_PARAMS(GameStateManager);
		CLASS_DECLARATIONS_NO_PARAMS(GameState);
		CLASS_DECLARATIONS_NO_PARAMS(Application);

	//---------------
	// Game module-related constants, type definitions and forwarded declarations
	//---------------
		CLASS_DECLARATIONS_NO_PARAMS(GameWorldManager);
		CLASS_DECLARATIONS_NO_PARAMS(Component);

		const std::string GAMEWORLDMANAGER_CFG="../../Config/gameworldmanager-cfg.xml";

		const int DREAMS=0;
		const int NIGHTMARES=1;
		const int BOTH_WORLDS=2;

		const std::string SUFFIX_DREAMS="_d";
		const std::string SUFFIX_NIGHTMARES="_n";	
		const std::string SUFFIX_CHANGEWORLD="_cw";
		const std::string TRANSPARENT_TEXTURE="transparent.dds";

		class WorldNameConverter;

		const std::string LEVEL_NONE="None";
		const std::string LEVEL_TEST="TestLevel";
		const std::string LEVEL_SANDBOX="Sandbox";
		const std::string LEVEL_CLOCK="Clock";
		const std::string LEVEL_1="Level1";
		const std::string LEVEL_2="Level2";

		const std::string LEVEL_START_CHECKPOINT="LevelStart";

		//Render Components
		CLASS_DECLARATIONS(RenderComponent);
		CLASS_DECLARATIONS(RenderComponentBillboardSet);
		class TRenderComponentBillboardParameters;

		CLASS_DECLARATIONS(RenderComponentEntity);
		class TRenderComponentSubEntityParameters;
		class TRenderComponentEntityAnimParams;

		CLASS_DECLARATIONS(RenderComponentLight);
		CLASS_DECLARATIONS(RenderComponentParticleSystem);
		CLASS_DECLARATIONS(RenderComponentQuadHalo);
		CLASS_DECLARATIONS(RenderComponentGlow);
		CLASS_DECLARATIONS(RenderComponentFractalVolume);
		CLASS_DECLARATIONS(RenderComponentWater);
		CLASS_DECLARATIONS(RenderComponentPlane);
		CLASS_DECLARATIONS (RenderComponentScene);
		class TRenderComponentFogParameters;
		class TRenderComponentSkyDomeParameters;

		CLASS_DECLARATIONS (RenderComponentPositional);
		CLASS_DECLARATIONS (RenderComponentInitial);
		CLASS_DECLARATIONS(RenderComponentViewport);
		CLASS_DECLARATIONS(RenderComponentDecal);
		CLASS_DECLARATIONS(RenderComponentMessageBox);

		const std::string COMPONENT_TYPE_RENDER="RenderComponent";
		const std::string COMPONENT_TYPE_RENDER_BILLBOARD_SET="RenderComponentBillboardSet";
		const std::string COMPONENT_TYPE_RENDER_CAMERA="RenderComponentCamera";
		const std::string COMPONENT_TYPE_RENDER_ENTITY="RenderComponentEntity";
		const std::string COMPONENT_TYPE_RENDER_INITIAL="RenderComponentInitial";
		const std::string COMPONENT_TYPE_RENDER_LIGHT="RenderComponentLight";
		const std::string COMPONENT_TYPE_RENDER_PARTICLE_SYSTEM="RenderComponentParticleSystem";
		const std::string COMPONENT_TYPE_RENDER_POSITIONAL="RenderComponentPositional";
		const std::string COMPONENT_TYPE_RENDER_QUAD_HALO="RenderComponentQuadHalo";
		const std::string COMPONENT_TYPE_RENDER_GLOW="RenderComponentGlow";
		const std::string COMPONENT_TYPE_RENDER_FRACTAL_VOLUME="RenderComponentFractalVolume";
		const std::string COMPONENT_TYPE_RENDER_SCENE="RenderComponentScene";
		const std::string COMPONENT_TYPE_RENDER_VIEWPORT="RenderComponentViewport";
		const std::string COMPONENT_TYPE_RENDER_DECAL="RenderComponentDecal";
		const std::string COMPONENT_TYPE_RENDER_MESSAGEBOX="RenderComponentMessageBox";

		//RayCasting
		CLASS_DECLARATIONS_NO_PARAMS(RayCasting);

		enum QueryFlags
		{
			QUERYFLAGS_NONE = 0,
			QUERYFLAGS_STATIC = 1<<0,
			QUERYFLAGS_DYNAMIC = 1<<1,
			QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET = 1<<2,
			QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID = 1<<3,
			QUERYFLAGS_FLASHLIGHT_LIGHT = 1<<4,
			QUERYFLAGS_CAMERA_COLLISION=QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET| QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID
			//QUERYFLAGS... = 1<<3
		};

		//Physics components
		CLASS_DECLARATIONS(PhysicsComponent);
		CLASS_DECLARATIONS(PhysicsComponentCharacter);
		CLASS_DECLARATIONS(PhysicsComponentCharacterOny);
		
		CLASS_DECLARATIONS(PhysicsComponentComplex);
		CLASS_DECLARATIONS(PhysicsComponentComplexConvex);
		CLASS_DECLARATIONS(PhysicsComponentComplexTriangle);

		CLASS_DECLARATIONS(PhysicsComponentSimpleCapsule);
		CLASS_DECLARATIONS(PhysicsComponentSimpleBox);
		CLASS_DECLARATIONS(PhysicsComponentVolumeCapsule);
		CLASS_DECLARATIONS(PhysicsComponentVolumeBox);
		CLASS_DECLARATIONS(PhysicsComponentVolumeConvex);
		CLASS_DECLARATIONS(PhysicsComponentVolumeTriangle);
		CLASS_DECLARATIONS(PhysicsComponentWeapon);
		
		const std::string COMPONENT_TYPE_PHYSICS="PhysicsComponent";
		const std::string COMPONENT_TYPE_PHYSICS_CHARACTER="PhysicsComponentCharacter";
		const std::string COMPONENT_TYPE_PHYSICS_CHARACTER_ONY="PhysicsComponentCharacterOny";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX="PhysicsComponentComplex";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX_CONVEX="PhysicsComponentComplexConvex";
		const std::string COMPONENT_TYPE_PHYSICS_COMPLEX_TRIANGLE="PhysicsComponentComplexTriangle";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE="PhysicsComponentSimple";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE_BOX="PhysicsComponentSimpleBox";
		const std::string COMPONENT_TYPE_PHYSICS_SIMPLE_CAPSULE="PhysicsComponentSimpleCapsule";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME="PhysicsComponentVolume";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_BOX="PhysicsComponentVolumeBox";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_CAPSULE="PhysicsComponentVolumeCapsule";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_CONVEX="PhysicsComponentVolumeConvex";
		const std::string COMPONENT_TYPE_PHYSICS_VOLUME_TRIANGLE="PhysicsComponentVolumeTriangle";
		const std::string COMPONENT_TYPE_PHYSICS_PILLOW="PhysicsComponentWeapon";

		//Logic Components
		CLASS_DECLARATIONS(LogicComponent);
		CLASS_DECLARATIONS(LogicComponentOny);
		CLASS_DECLARATIONS(LogicComponentEnemy);
		CLASS_DECLARATIONS(LogicComponentItem);
		CLASS_DECLARATIONS(LogicComponentBreakable);
		CLASS_DECLARATIONS(LogicComponentUsable);
		CLASS_DECLARATIONS(LogicComponentProp);
		CLASS_DECLARATIONS(LogicComponentTrigger);
		CLASS_DECLARATIONS(LogicComponentCameraTrigger);
		
		CLASS_DECLARATIONS(WeaponComponent);
		CLASS_DECLARATIONS(AttackComponent);

		const int DEFAULT_MAX_WEAPON_POWER=10;
		typedef enum
		{
			WEAPON_MODE_INVALID=-1,
			WEAPON_MODE_0,
			WEAPON_MODE_1,
			WEAPON_MODE_2,
			//...
			WEAPON_MODE_SPECIAL
		} TWeaponMode;

		const std::string COMPONENT_TYPE_LOGIC="LogicComponent";
		const std::string COMPONENT_TYPE_LOGIC_ONY="LogicComponentOny";
		const std::string COMPONENT_TYPE_LOGIC_ENEMY="LogicComponentEnemy";
		const std::string COMPONENT_TYPE_LOGIC_ITEM="LogicComponentItem";
		const std::string COMPONENT_TYPE_LOGIC_BREAKABLE="LogicComponentBreakable";
		const std::string COMPONENT_TYPE_LOGIC_USABLE="LogicComponentUsable";
		const std::string COMPONENT_TYPE_LOGIC_TRIGGER="LogicComponentTrigger";
		const std::string COMPONENT_TYPE_LOGIC_PROP="LogicComponentProp";
		const std::string COMPONENT_TYPE_WEAPON="WeaponComponent";
		const std::string COMPONENT_TYPE_ATTACK="AttackComponent";
		const std::string COMPONENT_TYPE_LOGIC_TRIGGER_CAMERA="LogicComponentCameraTrigger";
		const std::string COMPONENT_TYPE_LOGIC_TRIGGER_ACTION="LogicComponentCameraAction";

		///////////////////////////////////////////////////////////////////

		//Game Object Specializations
		CLASS_DECLARATIONS(GameObject);


		typedef std::map<std::string,GameObjectPtr> TGameObjectContainer;
		typedef TGameObjectContainer::iterator TGameObjectContainerIterator;

		GAMEOBJECT_CONTAINER_DECL(Positional);
		GAMEOBJECT_CONTAINER_DECL(Movable);
		GAMEOBJECT_CONTAINER_DECL(NonMovable);
		GAMEOBJECT_CONTAINER_DECL(MovableEntity);
		GAMEOBJECT_CONTAINER_DECL(NonMovableEntity);
		GAMEOBJECT_CONTAINER_DECL(Entity);
		GAMEOBJECT_CONTAINER_DECL(Physics);
		GAMEOBJECT_CONTAINER_DECL(PhysicsCharacter);
		GAMEOBJECT_CONTAINER_DECL(PhysicsComplex);
		GAMEOBJECT_CONTAINER_DECL(PhysicsComplexConvex);
		GAMEOBJECT_CONTAINER_DECL(PhysicsComplexTriangle);
		GAMEOBJECT_CONTAINER_DECL(PhysicsSimple);
		GAMEOBJECT_CONTAINER_DECL(PhysicsSimpleBox);
		GAMEOBJECT_CONTAINER_DECL(PhysicsSimpleCapsule);
		GAMEOBJECT_CONTAINER_DECL(PhysicsVolume);
		GAMEOBJECT_CONTAINER_DECL(PhysicsVolumeBox);
		GAMEOBJECT_CONTAINER_DECL(PhysicsVolumeCapsule);
		GAMEOBJECT_CONTAINER_DECL(Logic);
		GAMEOBJECT_CONTAINER_DECL(Usable);
		GAMEOBJECT_CONTAINER_DECL(Sound);


		////////////////////////////////////////////////////////////////////

		const int HIT_RECOVERY_TIME=500;
		const int MIN_RANDOM_MOVEMENT_DELAY=500;
		const int MAX_RANDOM_MOVEMENT_DELAY=800;

		GAMEOBJECT_CLASS_DECL(Scene);
		GAMEOBJECT_CLASS_DECL(Viewport);
		GAMEOBJECT_CLASS_DECL(TerrainConvex);
		GAMEOBJECT_CLASS_DECL(TerrainTriangle);
		GAMEOBJECT_CLASS_DECL(Light);
		GAMEOBJECT_CLASS_DECL(BillboardSet);
		GAMEOBJECT_CLASS_DECL(ParticleSystem);
		GAMEOBJECT_CLASS_DECL(Ony);
		GAMEOBJECT_CLASS_DECL(Tripollo);
		GAMEOBJECT_CLASS_DECL(Portal);
		GAMEOBJECT_CLASS_DECL(Eye);
		GAMEOBJECT_CLASS_DECL(Item1UP);
		GAMEOBJECT_CLASS_DECL(ItemMaxHP);
		GAMEOBJECT_CLASS_DECL(TriggerBox);
		GAMEOBJECT_CLASS_DECL(TriggerCapsule);
		GAMEOBJECT_CLASS_DECL(CryKing);
		GAMEOBJECT_CLASS_DECL(Boss);
		GAMEOBJECT_CLASS_DECL(MagicClock);
		GAMEOBJECT_CLASS_DECL(Pillow);
		GAMEOBJECT_CLASS_DECL(FlashLight);	
		GAMEOBJECT_CLASS_DECL(Tentetieso);
		GAMEOBJECT_CLASS_DECL(Bee_Butterfly);
		GAMEOBJECT_CLASS_DECL(DiamondTree);
		GAMEOBJECT_CLASS_DECL(StoryBook);
		GAMEOBJECT_CLASS_DECL(Heart);
		GAMEOBJECT_CLASS_DECL(Diamond);
		GAMEOBJECT_CLASS_DECL(ScaredPlant);
		GAMEOBJECT_CLASS_DECL(TreeDreams);
		GAMEOBJECT_CLASS_DECL(TreeNightmares);
		GAMEOBJECT_CLASS_DECL(ClockPiece);
		GAMEOBJECT_CLASS_DECL(CarnivorousPlant);
		GAMEOBJECT_CLASS_DECL(SnakeCreeper);
		GAMEOBJECT_CLASS_DECL(WoodBox);
		GAMEOBJECT_CLASS_DECL(Water);
		GAMEOBJECT_CLASS_DECL(Plane);
		GAMEOBJECT_CLASS_DECL(Fog);
		GAMEOBJECT_CLASS_DECL(Tower);
		GAMEOBJECT_CLASS_DECL(TreeComplex);
		GAMEOBJECT_CLASS_DECL(CameraTrigger);
		GAMEOBJECT_CLASS_DECL(Signpost);
		GAMEOBJECT_CLASS_DECL(Nest);
		GAMEOBJECT_CLASS_DECL(Totem);
		GAMEOBJECT_CLASS_DECL(Switch);
		GAMEOBJECT_CLASS_DECL(LevelEntrance);
		GAMEOBJECT_CLASS_DECL(Bomb);
		GAMEOBJECT_CLASS_DECL(Traspasable);
		GAMEOBJECT_CLASS_DECL(Cloud);
		GAMEOBJECT_CLASS_DECL(Door);
		GAMEOBJECT_CLASS_DECL(NightGoblin);
		GAMEOBJECT_CLASS_DECL(Plataform);
		GAMEOBJECT_CLASS_DECL(ProvisionalEntity);
		GAMEOBJECT_CLASS_DECL(Scepter);
		GAMEOBJECT_CLASS_DECL(Tree);
		GAMEOBJECT_CLASS_DECL(SkyBody);

		GAMEOBJECT_CLASS_DECL(BreakableRock);
		GAMEOBJECT_CLASS_DECL(InvisibleWall);

		//Some object have types in mayus for Ogitor convenience
		const std::string GAME_OBJECT_TYPE="object";
		const std::string GAME_OBJECT_TYPE_SCENE="SceneManager";
		const std::string GAME_OBJECT_TYPE_TERRAIN="terrain";
		const std::string GAME_OBJECT_TYPE_TERRAINCONVEX="terrain-convex";
		const std::string GAME_OBJECT_TYPE_TERRAINTRIANGLE="terrain-triangle";
		const std::string GAME_OBJECT_TYPE_LIGHT="Light";
		const std::string GAME_OBJECT_TYPE_CAMERA="Camera";
		const std::string GAME_OBJECT_TYPE_BILLBOARDSET="BillboardSet";
		const std::string GAME_OBJECT_TYPE_PARTICLESYSTEM="Particle";
		const std::string GAME_OBJECT_TYPE_ONY="ony";
		const std::string GAME_OBJECT_TYPE_TRIPOLLO="tripollo";
		const std::string GAME_OBJECT_TYPE_PORTAL="changeworld";
		const std::string GAME_OBJECT_TYPE_EYE="eye";
		const std::string GAME_OBJECT_TYPE_ITEM_1UP="item1up";
		const std::string GAME_OBJECT_TYPE_ITEM_MAXHP="heartbag";
		const std::string GAME_OBJECT_TYPE_TRIGGER_BOX="volume-box";
		const std::string GAME_OBJECT_TYPE_TRIGGER_CAPSULE="volume-capsule";
		const std::string GAME_OBJECT_TYPE_VIEWPORT="Viewport1";
		const std::string GAME_OBJECT_TYPE_NIGHTGOBLIN="nightgoblin";
		const std::string GAME_OBJECT_TYPE_CRYKING="cryking";
		const std::string GAME_OBJECT_TYPE_BOSS="boss";
		const std::string GAME_OBJECT_TYPE_MAGICCLOCK="magicclock";
		const std::string GAME_OBJECT_TYPE_PILLOW="pillow";
		const std::string GAME_OBJECT_TYPE_FLASHLIGHT="flashlight";
		const std::string GAME_OBJECT_TYPE_TENTETIESO="tentetieso";
		const std::string GAME_OBJECT_TYPE_BEE_BUTTERFLY="bee%butterfly";
		const std::string GAME_OBJECT_TYPE_DIAMONDTREE="diamondtree";
		const std::string GAME_OBJECT_TYPE_STORYBOOK="storybook";
		const std::string GAME_OBJECT_TYPE_HEART="heart";
		const std::string GAME_OBJECT_TYPE_DIAMOND="diamond";
		const std::string GAME_OBJECT_TYPE_SCAREDPLANT="scaredplant";
		const std::string GAME_OBJECT_TYPE_CLOCKPIECE="clockpiece";
		const std::string GAME_OBJECT_TYPE_PROVISIONALENTITY="provisional-entity";
		const std::string GAME_OBJECT_TYPE_SOUND="sound";
		const std::string GAME_OBJECT_TYPE_SIGNPOST="signpost";
		const std::string GAME_OBJECT_TYPE_NEST="nest";

		const std::string GAME_OBJECT_TYPE_SNAKECREEPER="snakecreeper";
		const std::string GAME_OBJECT_TYPE_CARNIVOROUSPLANT="carnivorousplant";
		const std::string GAME_OBJECT_TYPE_SCEPTER="scepter";
		const std::string GAME_OBJECT_TYPE_TREE="tree";
		const std::string GAME_OBJECT_TYPE_TREE_COMPLEX="tree_complex";
		const std::string GAME_OBJECT_TYPE_TREE1="tree1";
		const std::string GAME_OBJECT_TYPE_TREE2="tree2";
		const std::string GAME_OBJECT_TYPE_TREE3="tree3";
		const std::string GAME_OBJECT_TYPE_TREE4="tree4";
		const std::string GAME_OBJECT_TYPE_TREE5="tree5";
		const std::string GAME_OBJECT_TYPE_TREE6="tree6";
		const std::string GAME_OBJECT_TYPE_TREE7="tree7";
		const std::string GAME_OBJECT_TYPE_TREE8="tree8";
		const std::string GAME_OBJECT_TYPE_TREE9="tree9";
		const std::string GAME_OBJECT_TYPE_TREE10="tree10";
		const std::string GAME_OBJECT_TYPE_TREE11="tree11";
		const std::string GAME_OBJECT_TYPE_TREE12="tree12";
		const std::string GAME_OBJECT_TYPE_DOOR="door";
		const std::string GAME_OBJECT_TYPE_PLATAFORM="plataform";
		const std::string GAME_OBJECT_TYPE_TRASPASABLE="bush";
		const std::string GAME_OBJECT_TYPE_TRASPASABLE1="bush1";
		const std::string GAME_OBJECT_TYPE_TRASPASABLE2="bush2";
		const std::string GAME_OBJECT_TYPE_TRASPASABLE3="bush3";
		const std::string GAME_OBJECT_TYPE_CLOUD="cloud";
		const std::string GAME_OBJECT_TYPE_WOODBOX="woodbox";
		const std::string GAME_OBJECT_TYPE_WATER="water";
		const std::string GAME_OBJECT_TYPE_PLANE="Plane";
		const std::string GAME_OBJECT_TYPE_SKYBODY="skybody";
		const std::string GAME_OBJECT_TYPE_TOWER="tower";
		const std::string GAME_OBJECT_TYPE_FOG="fog";
		const std::string GAME_OBJECT_TYPE_TRIGGER_CAMERA="trigger-camera";		

		const std::string GAME_OBJECT_TYPE_TOTEM="totem";
		const std::string GAME_OBJECT_TYPE_LEVEL_ENTRANCE="level-entrance";
		const std::string GAME_OBJECT_TYPE_SWITCH="switch";
		const std::string GAME_OBJECT_TYPE_BOMB="bomb";

		const std::string GAME_OBJECT_TYPE_BREAKABLE_ROCK="breakable-rock";
		const std::string GAME_OBJECT_TYPE_INVISIBLE_WALL="invisible-wall";


		const std::string PRESET_PATROL_TRAJECTORY_PREFIX="patrol_";

		enum EnemyType
		{
			ENEMY_TYPE_NORMAL,
			ENEMY_TYPE_FLYING,
			ENEMY_TYPE_STATUE
		};

		
		///////////////////////////////////////////////////////////////////

		//-------------------------------------
		//	Trajectory module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		class Trajectory;
		class TTrajectoryParameters;

		class TrajectoryNode;
		class TTrajectoryNodeParameters;

		class WalkabilityMap;
		class TWalkabilityMapParameters;
		class TWalkabilityMapNodeParameters;

		class Line3D;

		CLASS_DECLARATIONS_NO_PARAMS(TrajectoryManager);
		CLASS_DECLARATIONS(TrajectoryComponent);

		const std::string COMPONENT_TYPE_TRAJECTORY="TrajectoryComponent";
		const std::string DEFAULT_WALKABILITY_MAP_DREAMS="dreams";
		const std::string DEFAULT_WALKABILITY_MAP_NIGHTMARES="nightmares";

		#define TRAJECTORY_CFG "../../Config/trajectory-cfg.xml"
		#define OGITOR_CAMERA_TRAJECTORY_NODE "CameraTrajectory"

		//-------------------------------------
		//	Loader module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		class XMLGameObject;
		typedef std::map<std::string,XMLGameObject> XMLGameObjectContainer;
		typedef std::map<std::string,XMLGameObject>::iterator XMLGameObjectContainerIterator;

		class XMLSceneNode;
		typedef std::vector<XMLSceneNode> XMLSceneNodeContainer;

		class XMLTrajectory;
		typedef std::map<std::string,XMLTrajectory> XMLTrajectoryContainer;
		typedef std::map<std::string,XMLTrajectory>::iterator XMLTrajectoryContainerIterator;

		class XMLWalkabilityMap;
		typedef std::map<std::string,XMLWalkabilityMap> XMLWalkabilityMapContainer;
		typedef std::map<std::string,XMLWalkabilityMap>::iterator XMLWalkabilityMapContainerIterator;

		class XMLParser;
		
		CLASS_DECLARATIONS_NO_PARAMS(LevelLoader);

		const std::string DEFAULT_OGRE_RESOURCE_MANAGER_GROUP="General";

		//Exception messages
		const std::string SCENE_NODE_NOT_FOUND="Scene Parameters not found";
		const std::string VIEWPORT_NODE_NOT_FOUND="Viewport Parameters not found";
		const std::string DREAMS_NODE_NOT_FOUND="Dreams node does not exist or has wrong name in Ogitor";   
		const std::string NIGHTMARES_NODE_NOT_FOUND="Nightmares node does not exist or has wrong name in Ogitor";
		const std::string CUSTOM_PROPERTIES_NODE_NOT_FOUND="Custom Properties node does not exist or has wrong .ctp filename";
		const std::string DREAMS_SHOULD_NOT_EXIST="This object can't have dreams node";  
		const std::string NIGHTMARES_SHOULD_NOT_EXIST="This object can't have nightmares node";  

		const std::string GAME_OBJECT_PARAMETERS_PATH="../../Resources/Levels/GameObjects/";
		const std::string LEVELS_PATH="../../Resources/Levels/";
		const std::string FRACTAL_CLOUDS_CFG="../../Config/clouds_fractal-cfg.xml";
		const std::string BILLBOARD_CLOUDS_CFG="../../Config/clouds_billboard-cfg.xml";

		CLASS_DECLARATIONS_NO_PARAMS(Configuration);
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

		#define COMPOSITOR_CFG "../../Config/compositor-cfg.xml"

		#define BAR_CFG "../../Config/bar-cfg.xml"

		const int DEFAULT_OGRE_MIPMAPS_NUMBER=5;
		const std::string MAIN_CAMERA_NAME="Camera";
		// Default path constants
		const std::string DEFAULT_OGRE_RESOURCES_PATH="../../Config/resources.cfg";
		const std::string DEFAULT_OGRE_CONFIG_PATH  = "../../Config/ogre.cfg";
		const std::string DEFAULT_OGRE_LOG_PATH = "Ogre.log";
		//Fetch the plugins file conditionally, depending on whether we're on debug mode or not
		#ifdef OUAN_DEBUG
				const std::string DEFAULT_OGRE_PLUGINS_PATH="../../Config/plugins-dbg.cfg";
		#else
				const std::string DEFAULT_OGRE_PLUGINS_PATH="../../Config/plugins.cfg";
		#endif	
		typedef enum
		{
			AXIS_POS_X,
			AXIS_NEG_X,
			AXIS_POS_Y,
			AXIS_NEG_Y,
			AXIS_POS_Z,
			AXIS_NEG_Z
		}TCoordinateAxis;

		CLASS_DECLARATIONS_NO_PARAMS(RenderSubsystem);
		CLASS_DECLARATIONS_NO_PARAMS(ChangeWorldRenderer);
		

		///Camera Manager
		const std::string CAMERA_CFG="../../Config/camera-cfg.xml";
		const std::string CAMERA_CONTROLLER_THIRD_PERSON_FREE_CFG="../../Config/camera-thirdfree-cfg.xml";
		const std::string CAMERA_CONTROLLER_THIRD_PERSON_AUTO_CFG="../../Config/camera-thirdauto-cfg.xml";

		CLASS_DECLARATIONS_NO_PARAMS(CameraManager);

		CLASS_DECLARATIONS_NO_PARAMS(CameraParameters);
		CLASS_DECLARATIONS_NO_PARAMS(CameraTrigger);
		CLASS_DECLARATIONS_NO_PARAMS(CameraInput);

		class CameraController;
		class CameraControllerFirstPerson;
		class CameraControllerThirdPerson;

		CLASS_DECLARATIONS_NO_PARAMS(TransparentEntityManager);
		CLASS_DECLARATIONS_NO_PARAMS(TransparentEntity);

		/// Ogre root object
		typedef boost::shared_ptr<Ogre::Root> RootPtr;

		typedef enum 
		{
			CAMERA_NONE,
			CAMERA_FIRST_PERSON,
			CAMERA_THIRD_PERSON
		}TCameraControllerType;

		enum CameraState
		{
			CS_FREE,
			CS_TRACKING,
			CS_AUTO_ROTATION,
			CS_TRAJECTORY,
			CS_MOVE_TO_POSITION,
			CS_MOVE_TO_TARGET,
			CS_MOVE_TO_POSITION_LOOKING_AT_TARGET,
			CS_FIXED_FIRST_PERSON
		};

		enum CameraTriggerType
		{
			CTT_FREE,
			CTT_TRACKING,
			CTT_AUTO_ROTATION,
			CTT_AUTO_CENTER,
			CTT_TRAJECTORY
		};

		//-------------------------------------
		//	Physics module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		CLASS_DECLARATIONS_NO_PARAMS(PhysicsSubsystem);

		enum GameGroup
		{
			GROUP_NON_COLLIDABLE,
			GROUP_COLLIDABLE_NON_PUSHABLE,
			GROUP_COLLIDABLE_PUSHABLE,
		};

		#define GROUP_COLLIDABLE_MASK (1 << GROUP_COLLIDABLE_NON_PUSHABLE) | (1 << GROUP_COLLIDABLE_PUSHABLE)
		#define NXS_PATH "file:../../Resources/Graphics/NxModels"
		#define PHYSICS_CFG "../../Config/physics-cfg.xml"

		#define COLLISION_TYPE_TRIGGER_UNKNOWN 0
		#define COLLISION_TYPE_TRIGGER_ENTER 1
		#define COLLISION_TYPE_TRIGGER_PRESENCE 2
		#define COLLISION_TYPE_TRIGGER_EXIT 3

		#define PI 3.14159265
		#define PI_HALF 1.57079632
		#define TO_DEGREES 57.296 // 180/PI
		#define TO_RADIANS 0.0174532925 // PI/180

		//-------------------------------------
		//  Particle Systems
		//-------------------------------------

		#define PARTICLES_CFG "../../Config/particles-cfg.xml"

		//-------------------------------------
		//  Movements masks
		//-------------------------------------
		
		const int MOV_NOWHERE = 0;
		const int MOV_GO_FORWARD = 1;
		const int MOV_GO_BACK = 2;
		const int MOV_GO_LEFT = 4;
		const int MOV_GO_RIGHT = 8;
		const int MOV_JUMP = 16;
		const int MOV_WALK = 32;

		const int MOV_FORWARD_OR_BACK = MOV_GO_FORWARD | MOV_GO_BACK;
		const int MOV_LEFT_OR_RIGHT = MOV_GO_LEFT | MOV_GO_RIGHT;

		enum TWalkingSurface
		{
			WALKING_SURFACE_GRASS,
			WALKING_SURFACE_WATER
		};

		//-------------------------------------
		//  Logger stuff
		//-------------------------------------

		const std::string LOGGER_CFG = "../../Config/logger-cfg.xml";
	
		//-------------------------------------
		//  Other stuff
		//-------------------------------------
		
		// NOTE:
		// The mouse button keys are using negative values so they don't 
		// interfere with existing key codes
		// As a result, the array must be larger to hold buffers for them.
		// Also, they'll be indexed at the end of the array like this:
		// if (key<0) then array[KEY_BUFFER_SIZE + key]
		
		const int MOUSEBUTTONS_BUFFER_SIZE=8;
		const int KEY_BUFFER_SIZE =256 + MOUSEBUTTONS_BUFFER_SIZE;

		//Message boxes/texts display time
		const double DEFAULT_DISPLAY_LIFETIME=2.0;
}

#endif