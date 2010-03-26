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
		ApplicationPtr mApp;
		lua_State* mLuaEngine;
	public:
		LogicSubsystem();
		~LogicSubsystem();
		void init(ApplicationPtr app);
		void registerModules();
		void loadScripts();
		void cleanUp();
		void update (double elapsedSeconds);
		void loadScript(const std::string& filename);
		void executeString(const std::string& scriptString);

		int invokeFunction(const std::string& functionName,int state, GameObjectPtr gameObject);

		//-- c++ from lua
		//void registerFunction(const std::string& functionName, FPLuaFunction function);

	};
}
#endif