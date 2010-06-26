#ifndef LOGICSUBSYSTEMH_H
#define LOGICSUBSYSTEMH_H
#include "../OUAN.h"

namespace OUAN
{
	const std::string SCRIPTS_PATH ="../../Resources/Scripts";
	const std::string SCRIPT_COMMON_FUNCTIONS="common.lua";
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
		
		std::map<std::string,lua_State*> mCoroutines;
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
		
		/// Invoke a LUA function from c++ code to retrieve a state
		/// @param functionName name of the function to invoke
		/// @param state game object state
		/// @param pLogicComponent logic component to update
		int invokeStateFunction(const std::string& functionName,int state, LogicComponent * pLogicComponent);
		
		/// Invoke a LUA function from c++ code to check a condition about a game object's logic component
		/// @param functionName name of the function to invoke
		/// @param gameObject game object to update
		/// @return true if the condition is true, false otherwise
		bool invokeConditionFunction(const std::string& functionName, LogicComponent* logicComponent);
		/// Invoke a LUA function from c++ code to perform an action
		/// @param functionName name of the function to invoke
		void invokeActionFunction(const std::string& functionName, LogicComponent* logicComponent);

		void initCutsceneScript(const std::string& scriptFilename);
		void invokeCutsceneFunction(const std::string& functionName);
		void updateCutsceneFunction(const std::string& functionName);

		/// Retrieve the value of a global variable in LUA
		int getGlobalInt (const std::string& globalName);
	};
}
#endif