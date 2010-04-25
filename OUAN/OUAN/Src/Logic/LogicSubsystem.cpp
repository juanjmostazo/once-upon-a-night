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
#include "../Game/GameObject/GameObjectTripolloDreams.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "LogicComponent/LogicComponent.h"
#include "LogicComponent/LogicComponentOny.h"
#include "LogicComponent/LogicComponentItem.h"
#include "LogicComponent/LogicComponentEnemy.h"
#include "LogicComponent/LogicComponentUsable.h"

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
		def("victory",&GameWorldManager::victory),
		class_<LogicComponent>("LogicComponent")
		.def(constructor<const std::string&>())
			.def("getName",&LogicComponent::getParentName),
		class_<LogicComponentEnemy, LogicComponent > ("LogicComponentEnemy")
			.def(constructor<const std::string&>())
			.def("getNumLives",&LogicComponentEnemy::getNumLives)
			.def("getLineOfSight",&LogicComponentEnemy::getLineOfSight)
			.def("getHP",&LogicComponentEnemy::getHealthPoints)
			.def("getMaxHP",&LogicComponentEnemy::getInitialHealthPoints),
		class_<LogicComponentOny, LogicComponent > ("LogicComponentOny")
			.def(constructor<const std::string&>())
			.def("getNumLives",&LogicComponentOny::getNumLives)
			.def("getHP",&LogicComponentOny::getHealthPoints)
			.def("getMaxHP",&LogicComponentOny::getInitialHealthPoints),
		class_<LogicComponentItem, LogicComponent > ("LogicComponentItem")
			.def(constructor<const std::string&>()),
		class_<LogicComponentUsable,LogicComponent>("LogicComponentUsable")
			.def(constructor<const std::string&>())
			.def("getApproachDistance",&LogicComponentUsable::getApproachDistance)
			.def("getActivateDistance",&LogicComponentUsable::getActivateDistance)
			.def("isActivated",&LogicComponentUsable::isActivated)
	];

	//NOW WORKS WITH LOGICCOMPONENTS INSTEAD OF GAMEOBJECTS
	//module(mLuaEngine) [
	//	def("log", (void (*) (const std::string&)) &Utils::scriptLog),
	//	def("getDistance",&GameWorldManager::getDistance),
	//	def("getPlayerDistance",&GameWorldManager::getPlayerDistance),
	//	def("getCurrentWorld",&GameWorldManager::getWorld),
	//	class_<GameObject>("GameObject")
	//	.def(constructor<const std::string&, const std::string&>())
	//		.def("getName",&GameObject::getName)
	//		.def("getNumLives",&GameObject::getNumLives)
	//		.def("getLineOfSight",&GameObject::getLineOfSight)
	//		.def("getHP",&GameObject::getHealthPoints)
	//		.def("getMaxHP",&GameObject::getMaximumHealthPoints),
	//	class_<GameObjectTripolloDreams, GameObject > ("GameObjectTripolloDreams")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectEye, GameObject >("GameObjectEye")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectBee_Butterfly,GameObject>("GameObjectBeeButterfly")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectTentetieso,GameObject>("GameObjectTentetieso")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectTripollito,GameObject>("GameObjectTripollito")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectCarnivorousPlant,GameObject>("GameObjectCarnivorousPlant")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectSnakeCreeper,GameObject>("GameObjectSnakeCreeper")
	//		.def(constructor<const std::string&>()),
	//	class_<GameObjectDragon,GameObject>("GameObjectDragon")
	//		.def(constructor<const std::string&>())
	//		.def("getTimeStunned",&GameObjectDragon::getTimeStunned)
	//	];
	//Do the same with the others.
}
void LogicSubsystem::loadScripts()
{
	loadScript(SCRIPTS_PATH+"/"+SCRIPT_COMMON_FUNCTIONS);

	GameWorldManagerPtr worldMgr=mApp->getGameWorldManager();
	std::string currentFilename;
	TGameObjectTripolloDreamsContainer tripolloList= worldMgr->getGameObjectTripolloDreamsContainer();
	if (!tripolloList.empty() && !(currentFilename=tripolloList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectEyeContainer eyeList=worldMgr->getGameObjectEyeContainer();
	if(!eyeList.empty() && !(currentFilename=eyeList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTentetiesoContainer tentetiesoList=worldMgr->getGameObjectTentetiesoContainer();
	if(!tentetiesoList.empty() && !(currentFilename=tentetiesoList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTripollitoContainer tripollitoList=worldMgr->getGameObjectTripollitoContainer();
	if(!tripollitoList.empty() && !(currentFilename=tripollitoList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectBee_ButterflyContainer bbList=worldMgr->getGameObjectBeeButterflyContainer();
	if(!bbList.empty() && !(currentFilename=bbList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectCarnivorousPlantContainer cpList=worldMgr->getGameObjectCarnivorousPlantContainer();
	if(!cpList.empty() && !(currentFilename=cpList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectSnakeCreeperContainer scList=worldMgr->getGameObjectSnakeCreeperContainer();
	if(!scList.empty() && !(currentFilename=scList.at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectPortalContainer ptList=worldMgr->getGameObjectPortalContainer();
	if (!ptList.empty())
	{
		GameObjectPortalPtr portal= boost::dynamic_pointer_cast<GameObjectPortal>(ptList.at(0));
		if (portal && portal.get() && !portal->getLogicComponentUsable()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+portal->getLogicComponentUsable()->getScriptFilename());
		}
	}
	//TODO: CHANGE THIS!!!
	GameObjectDragonPtr dragon = boost::dynamic_pointer_cast<GameObjectDragon> (worldMgr->getObject("dragon#0"));
	if (dragon.get() && !(currentFilename=dragon->getLogicComponentEnemy()->getScriptFilename()).empty())
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
		TGameObjectContainer container = mApp->getGameWorldManager()->getAllGameObjects();
		
		if (!container.empty())
		{
			for (TGameObjectContainer::iterator it=container.begin();it!=container.end();++it)
			{
				it->second->updateLogic(elapsedSeconds);
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
int LogicSubsystem::invokeStateFunction(const std::string& functionName,int state, LogicComponent * pLogicComponent)
{	
	int result=-1;
	if (mLuaEngine)
	{
		try{
			LogicComponentEnemy* enemyPtr=dynamic_cast<LogicComponentEnemy*>(pLogicComponent);
			if (enemyPtr)
				result= luabind::call_function<int>(mLuaEngine,functionName.c_str(),enemyPtr,state);
			else if(LogicComponentUsable* usablePtr=dynamic_cast<LogicComponentUsable*>(pLogicComponent))
				result=luabind::call_function<int>(mLuaEngine,functionName.c_str(),usablePtr,state);				
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

bool LogicSubsystem::invokeConditionFunction(const std::string& functionName, LogicComponent* logicComponent)
{
	bool result=false;
	if (mLuaEngine)
	{
		try{
			LogicComponentOny* onyPtr=dynamic_cast<LogicComponentOny*>(logicComponent);
			if (onyPtr)
				result= luabind::call_function<bool>(mLuaEngine,functionName.c_str(),onyPtr);
			//remaining cases to be added as needed
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

void LogicSubsystem::invokeActionFunction(const std::string& functionName, LogicComponent* logicComponent)
{
	if (mLuaEngine)
	{
		try{
			LogicComponentOny* onyPtr=dynamic_cast<LogicComponentOny*>(logicComponent);
			if (onyPtr)
				luabind::call_function<void>(mLuaEngine,functionName.c_str(),onyPtr);
			//remaining cases to be added as needed
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
int LogicSubsystem::getGlobalInt (const std::string& globalName)
{
	return luabind::object_cast<int>(luabind::globals(mLuaEngine)[globalName]);
}