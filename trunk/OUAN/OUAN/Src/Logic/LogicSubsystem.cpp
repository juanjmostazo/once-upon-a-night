#include "LogicSubsystem.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectBee_Butterfly.h"
#include "../Game/GameObject/GameObjectCarnivorousPlant.h"
#include "../Game/GameObject/GameObjectSnakeCreeper.h"
#include "../Game/GameObject/GameObjectDragon.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectTentetieso.h"
#include "../Game/GameObject/GameObjectTripollito.h"
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Utils/Utils.h"


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

	registerModules();
	//loadScripts();
}
void LogicSubsystem::registerModules()
{
	using namespace luabind;
	module(mLuaEngine) [
		def("log", (void (*) (const std::string&)) &Utils::scriptLog),
		def("getDistance",&GameWorldManager::getDistance),
		def("getPlayerDistance",&GameWorldManager::getPlayerDistance),
		def("getCurrentWorld",&GameWorldManager::getWorld),
		class_<GameObject>("GameObject")
		.def(constructor<const std::string&, const std::string&>())
			.def("getName",&GameObject::getName)
			.def("getNumLives",&GameObject::getNumLives)
			.def("getLineOfSight",&GameObject::getLineOfSight)
			.def("getHP",&GameObject::getHealthPoints)
			.def("getMaxHP",&GameObject::getMaximumHealthPoints),
		class_<GameObjectTripollo, GameObject > ("GameObjectTripollo")
			.def(constructor<const std::string&>()),
		class_<GameObjectEye, GameObject >("GameObjectEye")
			.def(constructor<const std::string&>()),
		class_<GameObjectBee_Butterfly,GameObject>("GameObjectBeeButterfly")
			.def(constructor<const std::string&>()),
		class_<GameObjectTentetieso,GameObject>("GameObjectTentetieso")
			.def(constructor<const std::string&>()),
		class_<GameObjectTripollito,GameObject>("GameObjectTripollito")
			.def(constructor<const std::string&>()),
		class_<GameObjectCarnivorousPlant,GameObject>("GameObjectCarnivorousPlant")
			.def(constructor<const std::string&>()),
		class_<GameObjectSnakeCreeper,GameObject>("GameObjectSnakeCreeper")
			.def(constructor<const std::string&>()),
		class_<GameObjectDragon,GameObject>("GameObjectDragon")
			.def(constructor<const std::string&>())
			.def("getTimeStunned",&GameObjectDragon::getTimeStunned)
	];
	//Do the same with the others.
}
void LogicSubsystem::loadScripts()
{
	GameWorldManagerPtr worldMgr=mApp->getGameWorldManager();
	std::string currentFilename;
	TGameObjectTripolloContainer tripolloList= worldMgr->getGameObjectTripolloContainer();
	if (!tripolloList.empty() && !(currentFilename=tripolloList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectEyeContainer eyeList=worldMgr->getGameObjectEyeContainer();
	if(!eyeList.empty() && !(currentFilename=eyeList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTentetiesoContainer tentetiesoList=worldMgr->getGameObjectTentetiesoContainer();
	if(!tentetiesoList.empty() && !(currentFilename=tentetiesoList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTripollitoContainer tripollitoList=worldMgr->getGameObjectTripollitoContainer();
	if(!tripollitoList.empty() && !(currentFilename=tripollitoList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectBee_ButterflyContainer bbList=worldMgr->getGameObjectBeeButterflyContainer();
	if(!bbList.empty() && !(currentFilename=bbList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectCarnivorousPlantContainer cpList=worldMgr->getGameObjectCarnivorousPlantContainer();
	if(!cpList.empty() && !(currentFilename=cpList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectSnakeCreeperContainer scList=worldMgr->getGameObjectSnakeCreeperContainer();
	if(!scList.empty() && !(currentFilename=scList.at(0)->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	//TODO: CHANGE THIS!!!
	GameObjectDragonPtr dragon = boost::dynamic_pointer_cast<GameObjectDragon> (worldMgr->getObject("dragon#0"));
	if (dragon.get() && !(currentFilename=dragon->getLogicComponent()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
}
void LogicSubsystem::cleanUp()
{
	lua_close(mLuaEngine);
}
void LogicSubsystem::update (double elapsedSeconds)
{
	if (mApp)
	{
		TGameObjectLogicContainer logicContainer = mApp->getGameWorldManager()->getGameObjectLogicContainer();
		
		if (!logicContainer.empty())
		{
			for (TGameObjectLogicContainer::iterator it=logicContainer.begin();it!=logicContainer.end();++it)
			{
				(*it)->updateLogic(elapsedSeconds);
			}
		}
	}
}
void LogicSubsystem::loadScript(const std::string& filename)
{
	if (mLuaEngine)
	{
		try
		{
			luaL_dofile(mLuaEngine,filename.c_str());
		}
		catch(const luabind::error& err)
		{
			std::string errString = "LUA Function call failed: ";
			errString.append(err.what()).append(" - ");
			errString.append(lua_tostring(err.state(),-1));
			Ogre::LogManager::getSingletonPtr()->logMessage(errString);
		}
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
int LogicSubsystem::getGlobalInt (const std::string& globalName)
{
	return luabind::object_cast<int>(luabind::globals(mLuaEngine)[globalName]);
}