#ifndef __OUAN__H__
#define __OUAN__H__

#include <map>
#include <string>
#include <Ogre.h>
#include <ois/OIS.h>
#include <cegui/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "ConfigKeys.h"

#include <boost/shared_ptr.hpp>

#include "TinyXML/tinyxml.h"

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
		const int SKIP_TICKS=1000/AI_FPS;
		const int MAX_FRAMESKIP=5;

		const int DEBUGMODE_NONE=0;
		const int DEBUGMODE_PHYSICS=1;
		const int DEBUGMODE_WIREFRAME=2;
		const int DEBUGMODE_POINTS=4;

		const std::string DEFAULT_WIN_NAME="Demo Application";

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

		//Component specializations

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

			//Physics components
			class PhysicsComponentCharacter;
			class TPhysicsComponentCharacterParameters;
			typedef boost::shared_ptr<PhysicsComponentCharacter> PhysicsComponentCharacterPtr;

			class PhysicsComponentComplexMovable;
			class TPhysicsComponentComplexMovableParameters;
			typedef boost::shared_ptr<PhysicsComponentComplexMovable> PhysicsComponentComplexMovablePtr;

			class PhysicsComponentComplexNonMovable;
			class TPhysicsComponentComplexNonMovableParameters;
			typedef boost::shared_ptr<PhysicsComponentComplexNonMovable> PhysicsComponentComplexNonMovablePtr;

			class PhysicsComponentSimpleCapsule;
			class TPhysicsComponentSimpleCapsuleParameters;
			typedef boost::shared_ptr<PhysicsComponentSimpleCapsule> PhysicsComponentSimpleCapsulePtr;

			class PhysicsComponentSimpleCube;
			class TPhysicsComponentSimpleCubeParameters;
			typedef boost::shared_ptr<PhysicsComponentSimpleCube> PhysicsComponentSimpleCubePtr;

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

		typedef std::vector<GameObjectPtr> TGameObjectPhysicsCharacter;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsComplexMovable;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsComplexNonMovable;
		typedef std::vector<GameObjectPtr> TGameObjectPhysicsSimple;


		class GameObjectScene;
		class TGameObjectSceneParameters;
		typedef boost::shared_ptr<GameObjectScene> GameObjectScenePtr;
		typedef std::vector<GameObjectScenePtr> TGameObjectSceneContainer;
		const std::string GAME_OBJECT_NAME_SCENE="scene";

		class GameObjectTerrain;
		class TGameObjectTerrainParameters;
		typedef boost::shared_ptr<GameObjectTerrain> GameObjectTerrainPtr;
		typedef std::vector<GameObjectTerrainPtr> TGameObjectTerrainContainer;
		const std::string GAME_OBJECT_NAME_TERRAIN="terrain";

		class GameObjectLight;
		class TGameObjectLightParameters;
		typedef boost::shared_ptr<GameObjectLight> GameObjectLightPtr;
		typedef std::vector<GameObjectLightPtr> TGameObjectLightContainer;
		const std::string GAME_OBJECT_NAME_LIGHT="light";

		class GameObjectBillboardSet;
		class TGameObjectBillboardSetParameters;
		typedef boost::shared_ptr<GameObjectBillboardSet> GameObjectBillboardSetPtr;
		typedef std::vector<GameObjectBillboardSetPtr> TGameObjectBillboardSetContainer;
		const std::string GAME_OBJECT_NAME_BILLBOARDSET="billboard";

		class GameObjectParticleSystem;
		class TGameObjectParticleSystemParameters;
		typedef boost::shared_ptr<GameObjectParticleSystem> GameObjectParticleSystemPtr;
		typedef std::vector<GameObjectParticleSystemPtr> TGameObjectParticleSystemContainer;
		const std::string GAME_OBJECT_NAME_PARTICLESYSTEM="particle";

		class GameObjectOny;
		class TGameObjectOnyParameters;
		typedef boost::shared_ptr<GameObjectOny> GameObjectOnyPtr;
		typedef std::vector<GameObjectOnyPtr> TGameObjectOnyContainer;
		const std::string GAME_OBJECT_NAME_ONY="ony";

		class GameObjectTripollo;
		class TGameObjectTripolloParameters;
		typedef boost::shared_ptr<GameObjectTripollo> GameObjectTripolloPtr;
		typedef std::vector<GameObjectTripolloPtr> TGameObjectTripolloContainer;
		const std::string GAME_OBJECT_NAME_TRIPOLLO="tripollo";

		class GameObjectPortal;
		class TGameObjectPortalParameters;
		typedef boost::shared_ptr<GameObjectPortal> GameObjectPortalPtr;
		typedef std::vector<GameObjectPortalPtr> TGameObjectPortalContainer;
		const std::string GAME_OBJECT_NAME_PORTAL="portal";

		class GameObjectEye;
		class TGameObjectEyeParameters;
		typedef boost::shared_ptr<GameObjectEye> GameObjectEyePtr;
		typedef std::vector<GameObjectEyePtr> TGameObjectEyeContainer;
		const std::string GAME_OBJECT_NAME_EYE="eye";

		class GameObjectItem1UP;
		class TGameObjectItem1UPParameters;
		typedef boost::shared_ptr<GameObjectItem1UP> GameObjectItem1UPPtr;
		typedef std::vector<GameObjectItem1UPPtr> TGameObjecItem1UPContainer;
		const std::string GAME_OBJECT_NAME_ITEM_1UP="item-1up";

		class GameObjectItemMaxHP;
		class TGameObjectItemMaxHPParameters;
		typedef boost::shared_ptr<GameObjectItemMaxHP> GameObjectItemMaxHPPtr;
		typedef std::vector<GameObjectItemMaxHPPtr> TGameObjecItemMaxHPContainer;
		const std::string GAME_OBJECT_NAME_ITEM_MAXHP="item-maxhp";

		typedef boost::shared_ptr<GameWorldManager> GameWorldManagerPtr;
		typedef boost::shared_ptr<Component> ComponentPtr;
		
		typedef std::map<std::string,ComponentPtr> TComponentContainer;
		typedef TComponentContainer::iterator TComponentContainerIterator;

		const int GAMEOBJECT_ID_ZERO_PADDING=6;

		const std::string COMPONENT_NAME_PHYSICS="PhysicsComponent";
		const std::string COMPONENT_NAME_PHYSICS_CHARACTER="PhysicsComponentCharacter";
		const std::string COMPONENT_NAME_PHYSICS_COMPLEX="PhysicsComponentComplex";
		const std::string COMPONENT_NAME_PHYSICS_COMPLEX_MOVABLE="PhysicsComponentComplexMovable";
		const std::string COMPONENT_NAME_PHYSICS_COMPLEX_NON_MOVABLE="PhysicsComponentComplexNonMovable";
		const std::string COMPONENT_NAME_PHYSICS_SIMPLE="PhysicsComponentSimple";
		const std::string COMPONENT_NAME_PHYSICS_SIMPLE_CAPSULE="PhysicsComponentSimpleCapsule";
		const std::string COMPONENT_NAME_PHYSICS_SIMPLE_CUBE="PhysicsComponentSimpleCube";
		
		const std::string COMPONENT_NAME_RENDER="RenderComponent";
		const std::string COMPONENT_NAME_RENDER_BILLBOARD_SET="RenderComponentBillboardSet";
		const std::string COMPONENT_NAME_RENDER_CAMERA="RenderComponentCamera";
		const std::string COMPONENT_NAME_RENDER_ENTITY="RenderComponentEntity";
		const std::string COMPONENT_NAME_RENDER_LIGHT="RenderComponentLight";
		const std::string COMPONENT_NAME_RENDER_PARTICLE_SYSTEM="RenderComponentParticleSystem";
		const std::string COMPONENT_NAME_RENDER_POSITIONAL="RenderComponentPositional";
		const std::string COMPONENT_NAME_RENDER_SCENE="RenderComponentScene";
		const std::string COMPONENT_NAME_RENDER_VIEWPORT="RenderComponentViewport";

		//-------------------------------------
		//	Loader module-related constants, type definitions and forwarded declarations
		//-------------------------------------

		class Configuration;
		class LevelLoader;
		typedef boost::shared_ptr<Configuration> ConfigurationPtr;
		typedef boost::shared_ptr<LevelLoader> LevelLoaderPtr;

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

		const float DEFAULT_MOVE_SPEED = 1;
		const float DEFAULT_ROTATE_SPEED=0.3f;
		const float MOUSE_MOVE_ROTATION_INCREMENT=0.1f;

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
		class CameraControllerFirstPerson;

		typedef boost::shared_ptr<RenderSubsystem> RenderSubsystemPtr;

		//-------------------------------------
		//	GUI module-related constants, type definitions and forwarded declarations
		//-------------------------------------
		class GUISubsystem;
		typedef boost::shared_ptr<GUISubsystem> GUISubsystemPtr;
		/// Keyboard event types
		typedef enum{
			GUI_KEYDOWN,
			GUI_KEYUP,
		} TGUIKeyboardEvent;
		
		/// Mouse event types ([TODO - Incomplete: Mouse wheel events should be added as well]
		typedef enum{
			GUI_MOUSEDOWN,
			GUI_MOUSEUP,
			GUI_MOUSEMOVE,
		} TGUIMouseEvent;

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

		#define COLLIDABLE_MASK (1 << GROUP_COLLIDABLE_NON_PUSHABLE) | (1 << GROUP_COLLIDABLE_PUSHABLE)
		#define NXS_PATH "file:../../Resources/Graphics/NxModels"

}


#endif