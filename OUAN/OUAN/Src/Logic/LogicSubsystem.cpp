#include "LogicSubsystem.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectTripollo.h"
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include <luabind/luabind.hpp>

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
	luaL_openlibs(mLuaEngine);
	luabind::open(mLuaEngine);

	loadScripts();
	registerModules();

}
void LogicSubsystem::registerModules()
{
	using namespace luabind;
	module(mLuaEngine) [
		class_<GameObject>("GameObject")
			.def( constructor<const std::string&,const std::string&>())
			.def("getName",&GameObject::getName),
		class_<GameObjectTripollo, GameObject > ("GameObjectTripollo")
			.def(constructor<const std::string&>())
			.def("getNumLives",&GameObjectTripollo::getNumLives)
	];
	//Do the same with the others.
}
void LogicSubsystem::loadScripts()
{
	TGameObjectTripolloContainer tripolloList= mApp->getGameWorldManager()->getGameObjectTripolloContainer();
	if (!tripolloList.empty() && !tripolloList.at(0)->getLogicComponent()->getScriptFilename().empty())
		loadScript(SCRIPTS_PATH+"/"+tripolloList.at(0)->getLogicComponent()->getScriptFilename());
	//repeat
}
void LogicSubsystem::cleanUp()
{
	//...
	lua_close(mLuaEngine);
}
void LogicSubsystem::update (double elapsedSeconds)
{
	if (mApp)
	{
		TGameObjectTripolloContainer tripolloList= mApp->getGameWorldManager()->getGameObjectTripolloContainer();
		if (!tripolloList.empty())
		{
			for (TGameObjectTripolloContainer::iterator it=tripolloList.begin();it!=tripolloList.end();++it)
			{
				GameObjectTripolloPtr tripollo=*it;
				tripollo->updateLogic(elapsedSeconds);
			}
		}
	}
}
void LogicSubsystem::loadScript(const std::string& filename)
{
	if (mLuaEngine)
	{
		luaL_dofile(mLuaEngine,filename.c_str());
	}
}
void LogicSubsystem::executeString(const std::string& scriptString)
{
	if (mLuaEngine)
	{
		luaL_dostring(mLuaEngine,scriptString.c_str());
	}
}
int LogicSubsystem::invokeFunction(const std::string& functionName,int state, GameObjectPtr gameObject)
{	
	int result=-1;
	if (mLuaEngine)
	{
		try{
			GameObjectTripollo* ptr=dynamic_cast<GameObjectTripollo*>(gameObject.get());
			if (ptr)
				result= luabind::call_function<int>(mLuaEngine,functionName.c_str(),ptr,state);
				//result=luabind::call_function<int>(mLuaEngine,"gimmeSumthin",45);
				
		}
		catch(const luabind::error& err)
		{
			std::string errString = "LUA Function call failed: ";
			errString.append(err.what()).append(" - ");
			errString.append(lua_tostring(err.state(),-1));
			Ogre::LogManager::getSingletonPtr()->logMessage(errString);
		}

	}
	return result;
}