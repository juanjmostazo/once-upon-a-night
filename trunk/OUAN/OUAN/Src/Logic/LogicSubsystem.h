#ifndef LOGICSUBSYSTEMH_H
#define LOGICSUBSYSTEMH_H
#include "../OUAN.h"

extern "C" {
#include "lua.h"
}
namespace OUAN
{
	const std::string SCRIPTS_PATH ="../../Resources/Scripts";
	/// This class will manage the
	/// logic of the game, acting as an interface
	/// to LUA
	class LogicSubsystem
	{
	private:
		///Pointer to the application
		ApplicationPtr mApp;
		/// Pointer to LUA's virtual machine
		lua_State* mLuaEngine;
	public:
		LogicSubsystem();
		~LogicSubsystem();
		/// Initialise subsystem
		/// @param app	pointer to the application
		void init(ApplicationPtr app);
		/// Register game classes and functions with LUA
		/// through luabind
		void registerModules();
		/// Load LUA scripts for all the game objects whose logic component
		/// requires so
		void loadScripts();
		/// Free resources
		void cleanUp();
		/// Update logic for all game objects whose state is controlled by LUA
		/// @param double elapsedSeconds time since last call (unused)
		void update (double elapsedSeconds);
		/// Load the given LUA script
		/// @param filename name of the script to load
		void loadScript(const std::string& filename);
		/// Execute a LUA chunk
		/// @param scriptString chunk to execute
		void executeString(const std::string& scriptString);
		
		/// Invoke a LUA function from c++ code
		/// @param functionName name of the function to invoke
		/// @param game object state
		/// @param gameObject game object to update
		int invokeFunction(const std::string& functionName,int state, GameObjectPtr gameObject);
	};
}
#endif