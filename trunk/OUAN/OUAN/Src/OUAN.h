#ifndef __OUAN__H__
#define __OUAN__H__

#include <map>
#include <string>
#include <Ogre.h>
#include <ois/OIS.h>
#include <cegui/CEGUI.h>
#include <OgreCEGUIRenderer.h>

//#include "Application.h"
//#include "Core/GameStateManager.h"
//#include "Core/GameState.h"
#include "ConfigKeys.h"
#include "Logger/Logger.h"

#include <boost/shared_ptr.hpp>

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

namespace OUAN
{

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
		typedef boost::shared_ptr<Configuration> ConfigurationPtr;

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

		class MainMenuState;		
}


#endif