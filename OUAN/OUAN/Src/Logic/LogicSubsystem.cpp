#include "LogicSubsystem.h"
using namespace OUAN;
LogicSubsystem::LogicSubsystem()
{

}
LogicSubsystem::~LogicSubsystem()
{

}
void LogicSubsystem::init(ApplicationPtr app)
{
	mApp=app;
	mLuaEngine = lua_open();
	lua_baselibopen(mLuaEngine);

}
void LogicSubsystem::cleanUp()
{
	lua_close(mLuaEngine);

}
void LogicSubsystem::update (double elapsedSeconds)
{

}
void LogicSubsystem::executeScript(const std::string& filename)
{
	if (mLuaEngine)
	{
		lua_dofile(mLuaEngine,filename.c_str());
	}
}


// lua wrappers
//-- lua from c++
void LogicSubsystem::loadFunction(const std::string& filename)	
{
	if (mLuaEngine)
		lua_getglobal(mLuaEngine,filename.c_str());	
}
void LogicSubsystem::pushNumber(double number)
{
	if (mLuaEngine)
		lua_pushnumber(mLuaEngine,number);

}
void LogicSubsystem::pushNumber(float number)
{
	if (mLuaEngine)
		lua_pushnumber(mLuaEngine,number);
}
void LogicSubsystem::pushNumber(long number)
{
	if (mLuaEngine)
		lua_pushnumber(mLuaEngine,number);
}
void LogicSubsystem::pushNumber(int number)
{
	if (mLuaEngine)
		lua_pushnumber(mLuaEngine,number);
}
void LogicSubsystem::pushBoolean(bool booleanValue)
{
	if(mLuaEngine)
		lua_pushboolean(mLuaEngine,booleanValue?1:0);
}
void LogicSubsystem::pushString(const std::string& string)
{
	if (mLuaEngine)
		lua_pushstring(mLuaEngine,string.c_str());
}

void LogicSubsystem::invokeFunction(int args, int results)
{	
	if (mLuaEngine)
		lua_call(mLuaEngine,args,results);
}
double LogicSubsystem::extractNumericResult(int index)
{
	double luaResult=-1;
	if (mLuaEngine)
	{
		if (index>0)
			index*=-1;
		luaResult=(double)lua_tonumber(mLuaEngine,index);
		lua_pop(mLuaEngine,1);
	}
	return luaResult;
}

//-- c++ from lua
//void registerFunction(const std::string& functionName, FPLuaFunction function);
int LogicSubsystem::getArgsNum()
{
	int argsNum=-1;
	argsNum=lua_gettop(mLuaEngine);
	return argsNum;
}
int LogicSubsystem::getInt(int index)
{
	return static_cast<int>(lua_tonumber(mLuaEngine,index));

}
long LogicSubsystem::getLong(int index)
{
	return static_cast<long>(lua_tonumber(mLuaEngine,index));
}
double LogicSubsystem::getDouble(int index)
{
	return static_cast<double>(lua_tonumber(mLuaEngine,index));
}
float LogicSubsystem::getFloat(int index)
{
	return static_cast<float>(lua_tonumber(mLuaEngine,index));
}
bool LogicSubsystem::getBool(int index)
{
	return (lua_toboolean(mLuaEngine,index))?true:false;
}
std::string LogicSubsystem::getString(int index)
{
	std::string result=lua_tostring(mLuaEngine,index);
	return result;
}
