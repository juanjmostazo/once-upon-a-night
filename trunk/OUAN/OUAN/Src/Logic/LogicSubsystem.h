#ifndef LOGICSUBSYSTEMH_H
#define LOGICSUBSYSTEMH_H
#include "../OUAN.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace OUAN
{
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
		void cleanUp();
		void update (double elapsedSeconds);
		void executeScript(const std::string& filename);

		// lua wrappers
		//-- lua from c++
		void loadFunction(const std::string& filename);
		void pushNumber(double number);
		void pushNumber(float number);
		void pushNumber(long number);
		void pushNumber(int number);
		void pushBoolean(bool booleanValue);
		void pushString(const std::string& string);
		void invokeFunction(int args, int results);
		double extractNumericResult(int index);

		//-- c++ from lua
		//void registerFunction(const std::string& functionName, FPLuaFunction function);
		int getArgsNum();
		int getInt(int index);
		long getLong(int index);
		double getDouble(int index);
		float getFloat(int index);
		bool getBool(int index);
		std::string getString(int index);


	};
}
#endif