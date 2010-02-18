#ifndef __OUAN__H__
#define __OUAN__H__

#include <map>
#include <string>
#include <Ogre.h>
#include <ois/OIS.h>
#include <cegui/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#include "ConfigKeys.h"
#include "Logger/Logger.h"

#include <boost/shared_ptr.hpp>

#include "TinyXML/tinyxml.h"

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

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
		const int AI_FPS=40;
		const int SKIP_TICKS=1000/AI_FPS;
		const int MAX_FRAMESKIP=5;

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
		class GameObject;
		class GameWorldManager;
		class Component;

		typedef boost::shared_ptr<GameObject> GameObjectPtr;
		typedef boost::shared_ptr<GameWorldManager> GameWorldManagerPtr;
		typedef boost::shared_ptr<Component> ComponentPtr;
		
		typedef std::map<std::string,ComponentPtr> TComponentContainer;
		typedef TComponentContainer::iterator TComponentContainerIterator;

		typedef std::map<std::string,GameObjectPtr> TGameObjectContainer;
		typedef TGameObjectContainer::iterator TGameObjectContainerIterator;

		const int GAMEOBJECT_ID_ZERO_PADDING=6;

		const std::string COMPONENT_NAME_OGRE="ogreComponent";
		const std::string COMPONENT_NAME_PHYSICS="physicsComponent";
		
		//Component specializations
		class OgreComponent;
		typedef boost::shared_ptr<OgreComponent> OgreComponentPtr;

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
		#define NXS_PATH "file:../../../Resources/Graphics/NxModels"


	//GameObject Creation Parameters Structs

	//TODO: Add Physix and other Subsystems parameters to the structs

	struct TSubEntityRenderParameters
	{
		String material;
		bool visible;
	};

	struct TEntityRenderParameters
	{
		String meshfile;
		bool castshadows;
		std::vector<TSubEntityRenderParameters> tSubEntityRenderParameters;
	};

	struct TLightRenderParameters
	{
		Ogre::Light::LightTypes lighttype;
		ColourValue diffuse;
		ColourValue specular;
		Vector3 direction;
		bool castshadows;
		Vector3 lightrange;
		Vector4 attenuation;
		Real power;
	};

	struct TSceneNodeRenderParameters
	{
		String parentSceneNodeName;
		Vector3 position;
		Quaternion orientation;
		Vector3 scale;
		String autotracktarget;
	};

	struct TCameraRenderParameters
	{
		Vector3 position;
		Quaternion orientation;
		String autotracktarget;
		bool autoaspectratio;
		Vector2 clipdistance;
		Real FOVy;
		Ogre::PolygonMode polygonmode;
		int viewmode;
	};

	struct TParticleSystemRenderParameters
	{
		String particle;
		bool castshadows;
	};

	struct TBillboardRenderParameters
	{
		ColourValue colour;
		Vector2 dimensions;
		Vector3 position;
		Real rotation;
		int texcoordindex;
		Vector4 texrect;
	};

	struct TBillboardSetRenderParameters
	{
		String material;
		Ogre::BillboardOrigin billboardorigin;
		Ogre::BillboardRotationType billboardrotation;
		Ogre::BillboardType billboardtype;
		Real defaultheight;
		Real defaultwidth;
		bool pointrendering;
		Real renderdistance;
		bool sorting;
		std::vector<TBillboardRenderParameters> tBillboardRenderParameters;
	};

	struct TViewportRenderParameters
	{
		ColourValue colour;
		int compositorcount;
		int index;
		bool overlays;
		bool shadows;
		bool skies;
	};

	struct TSkyBoxRenderParameters
	{
		bool active;
		String material;
		Real distance;
	};

	struct TSkyDomeRenderParameters
	{
		bool active;
		String material;
	};

	struct TSceneManagerRenderParameters
	{
		ColourValue ambient;
		TSkyBoxRenderParameters tSkyBoxRenderParameters;
		TSkyDomeRenderParameters tSkyDomeRenderParameters;
	};

	struct TParticleSystemParameters
	{
		String name;
		TParticleSystemRenderParameters tParticleSystemRenderParameters;
	};

	struct TSceneNodeParameters
	{
		String name;
		TSceneNodeRenderParameters tSceneNodeRenderParameters;
	};

	struct TEntityParameters
	{
		String name;
		TEntityRenderParameters tEntityRenderParameters;
	};

	struct TLightParameters
	{
		String name;
		TLightRenderParameters tLightRenderParameters;
	};

	struct TCameraParameters
	{
		String name;
		TCameraRenderParameters tCameraRenderParameters;
	};

	struct TBillboardSetParameters
	{
		String name;
		TBillboardSetRenderParameters tBillboardSetRenderParameters;
	};

	struct TSceneManagerParameters
	{
		String name;
		TSceneManagerRenderParameters tSceneManagerRenderParameters;
	};

	struct TViewportParameters
	{
		String name;
		TViewportRenderParameters tViewPortRenderParameters;
	};
}


#endif