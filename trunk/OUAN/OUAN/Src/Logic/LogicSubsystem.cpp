#include "OUAN_Precompiled.h"

#include "LogicSubsystem.h"
#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectBee_Butterfly.h"
#include "../Game/GameObject/GameObjectCarnivorousPlant.h"
#include "../Game/GameObject/GameObjectSnakeCreeper.h"
#include "../Game/GameObject/GameObjectDiamondTree.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectTentetieso.h"
#include "../Game/GameObject/GameObjectTripollito.h"
#include "../Game/GameObject/GameObjectTripolloDreams.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectSignpost.h"
#include "../Game/GameObject/GameObjectNest.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Core/GameRunningState.h"
#include "LogicComponent/LogicComponent.h"
#include "LogicComponent/LogicComponentOny.h"
#include "LogicComponent/LogicComponentItem.h"
#include "LogicComponent/LogicComponentEnemy.h"
#include "LogicComponent/LogicComponentUsable.h"
#include "LogicComponent/LogicComponentProp.h"

#include "../Utils/Utils.h"

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
	mCutsceneFinished=false;
	mTimer=boost::shared_ptr<Utils::LUATimer>(new Utils::LUATimer());
	//loadScripts();
}

void LogicSubsystem::registerModules()
{
	using namespace luabind;

	module(mLuaEngine) [
		def("log", (void (*) (const std::string&)) &Utils::scriptLog),
		def("getDistance",&GameWorldManager::getDistance),
		def("getPlayerDistance",&GameWorldManager::getPlayerDistance),
		def("getWorld",&GameWorldManager::getMyInstanceWorld),
		def("victory",&GameWorldManager::victory),
		def("setCheckPoint",&GameWorldManager::setCheckPointLUA),
		def("getCheckPointNumber",&GameWorldManager::getCheckPointNumberLUA),
		def("playMusic",&GameRunningState::playMusic),
		def("playSoundFromGameObject",&GameRunningState::playSoundFromGameObject),
		def("setCameraTrajectory",&CameraManager::setTrajectoryCamera),
		def("isCameraTrajectoryFinished",&CameraManager::isCameraTrajectoryEnded),
		def("setAnyTrackingCamera",&CameraManager::setAnyTrackingCamera),
		def("getAny",&GameWorldManager::getOny),
		class_<Utils::LUATimer>("Timer")
			.def(constructor<>())
			.def("reset",&Utils::LUATimer::reset)
			.def("getTime",&Utils::LUATimer::getTime),
		class_<LogicComponent>("LogicComponent")
		.def(constructor<const std::string&>())
			.def("getName",&LogicComponent::getParentName)
			.def("say",&LogicComponent::printMessage),
		class_<LogicComponentEnemy, LogicComponent > ("LogicComponentEnemy")
			.def(constructor<const std::string&>())
			.def("getNumLives",&LogicComponentEnemy::getNumLives)
			.def("getLineOfSight",&LogicComponentEnemy::getLineOfSight)
			.def("getHP",&LogicComponentEnemy::getHealthPoints)
			.def("getMaxHP",&LogicComponentEnemy::getInitialHealthPoints)
			.def("hasBeenHit",&LogicComponentEnemy::hasBeenHit)
			.def("hasDied",&LogicComponentEnemy::hasDied),
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
			.def("isActivated",&LogicComponentUsable::isActivated),
		class_<LogicComponentProp,LogicComponent>("LogicComponentProp")
			.def(constructor<const std::string&>())
			.def("getApproachDistance",&LogicComponentProp::getApproachDistance)
			.def("getDelay",&LogicComponentProp::getDelay)
			.def("getTimeSpent",&LogicComponentProp::getTimeSpent)
			.def("hasTakenHit", &LogicComponentProp::hasTakenHit)
			.def("isReloadSet", &LogicComponentProp::isReload)
	];
}

void LogicSubsystem::loadScripts()
{
	loadScript(SCRIPTS_PATH+"/"+SCRIPT_COMMON_FUNCTIONS);

	GameWorldManagerPtr worldMgr=mApp->getGameWorldManager();
	std::string currentFilename;
	TGameObjectTripolloDreamsContainer * tripolloList= worldMgr->getGameObjectTripolloDreamsContainer();
	if (!tripolloList->empty() && !(currentFilename=tripolloList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectEyeContainer  * eyeList=worldMgr->getGameObjectEyeContainer();
	if(!eyeList->empty() && !(currentFilename=eyeList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTentetiesoContainer  * tentetiesoList=worldMgr->getGameObjectTentetiesoContainer();
	if(!tentetiesoList->empty() && !(currentFilename=tentetiesoList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectTripollitoContainer  * tripollitoList=worldMgr->getGameObjectTripollitoContainer();
	if(!tripollitoList->empty() && !(currentFilename=tripollitoList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectBee_ButterflyContainer  * bbList=worldMgr->getGameObjectBeeButterflyContainer();
	if(!bbList->empty() && !(currentFilename=bbList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectCarnivorousPlantContainer  * cpList=worldMgr->getGameObjectCarnivorousPlantContainer();
	if(!cpList->empty() && !(currentFilename=cpList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectSnakeCreeperContainer  * scList=worldMgr->getGameObjectSnakeCreeperContainer();
	if(!scList->empty() && !(currentFilename=scList->at(0)->getLogicComponentEnemy()->getScriptFilename()).empty())
		loadScript(SCRIPTS_PATH+"/"+currentFilename);
	TGameObjectPortalContainer  * ptList=worldMgr->getGameObjectPortalContainer();
	if (!ptList->empty())
	{
		GameObjectPortalPtr portal= boost::dynamic_pointer_cast<GameObjectPortal>(ptList->at(0));
		if (portal && portal.get() && !portal->getLogicComponentUsable()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+portal->getLogicComponentUsable()->getScriptFilename());
		}
	}
	TGameObjectScaredPlantContainer * spList=worldMgr->getGameObjectScaredPlantContainer();
	if (!spList->empty())
	{
		GameObjectScaredPlantPtr scplant= boost::dynamic_pointer_cast<GameObjectScaredPlant>(spList->at(0));
		if (scplant && scplant.get() && !scplant->getLogicComponent()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+scplant->getLogicComponent()->getScriptFilename());
		}
	}
	TGameObjectDiamondTreeContainer* dtList = worldMgr->getGameObjectDiamondTreeContainer();
	if (!dtList->empty())
	{
		GameObjectDiamondTreePtr dtree = boost::dynamic_pointer_cast<GameObjectDiamondTree>(dtList->at(0));
		if (dtree.get() && !dtree->getLogicComponent()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+dtree->getLogicComponent()->getScriptFilename());
		}
	}
	TGameObjectSignPostContainer* signList = worldMgr->getGameObjectSignPostContainer();
	if (!signList->empty())
	{
		GameObjectSignPostPtr sign= boost::dynamic_pointer_cast<GameObjectSignpost>(signList->at(0));
		if (sign.get() && !sign->getLogicComponent()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+sign->getLogicComponent()->getScriptFilename());
		}
	}
	TGameObjectNestContainer* nestList = worldMgr->getGameObjectNestContainer();
	if (!nestList ->empty())
	{
		GameObjectNestPtr nest= boost::dynamic_pointer_cast<GameObjectNest>(nestList ->at(0));
		if (nest.get() && !nest->getLogicComponent()->getScriptFilename().empty())
		{
			loadScript(SCRIPTS_PATH+"/"+nest->getLogicComponent()->getScriptFilename());
		}
	}
	//TODO: CHANGE THIS!!!
	//GameObjectDragonPtr dragon = boost::dynamic_pointer_cast<GameObjectDragon> (worldMgr->getObject("dragon#0"));
	//if (dragon.get() && !(currentFilename=dragon->getLogicComponentEnemy()->getScriptFilename()).empty())
	//	loadScript(SCRIPTS_PATH+"/"+currentFilename);
}

void LogicSubsystem::cleanUp()
{
	lua_close(mLuaEngine);
}

void LogicSubsystem::update (double elapsedSeconds)
{
	if (mApp)
	{
		TGameObjectContainer * container = mApp->getGameWorldManager()->getAllGameObjects();
		
		if (!container->empty())
		{
			for (TGameObjectContainer::iterator it=container->begin();it!=container->end();++it)
			{
				if (it->second->isWorthUpdatingLogicComponents())
				{
					it->second->updateLogic(elapsedSeconds);
				}
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
			Logger::getInstance()->log(errString);
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
			else if (LogicComponentProp* propPtr=dynamic_cast<LogicComponentProp*>(pLogicComponent) )
				result=luabind::call_function<int>(mLuaEngine,functionName.c_str(),propPtr,state);
		}
		catch(const luabind::error& err)
		{
			std::string errString = "LUA Function call failed: ";
			errString.append(err.what()).append(" - ");
			errString.append(lua_tostring(err.state(),-1));
			Logger::getInstance()->log(errString);
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
			Logger::getInstance()->log(errString);
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
			Logger::getInstance()->log(errString);
		}
	}
}

int LogicSubsystem::getGlobalInt (const std::string& globalName)
{
	return luabind::object_cast<int>(luabind::globals(mLuaEngine)[globalName]);
}

void LogicSubsystem::invokeCutsceneFunction(const std::string& functionName)
{
	mCoroutine=lua_newthread(mLuaEngine);
	int retVal=0;
	try{
		retVal=luabind::resume_function<int>(mCoroutine, functionName.c_str(),mTimer.get());
	}
	catch(const luabind::error& err)
	{
		std::string errString = "LUA Coroutine function call failed: ";
		errString.append(err.what()).append(" - ");
		errString.append(lua_tostring(err.state(),-1));
		Logger::getInstance()->log(errString);
	}
	if (retVal==1)
		mCutsceneFinished=true;
}
void LogicSubsystem::updateCutsceneFunction(const std::string& functionName, double elapsedSeconds)
{
	if (mCoroutine)
	{
		mTimer->addTime(elapsedSeconds);
		int retVal=luabind::resume<int>(mCoroutine,mTimer.get());
		if (retVal==1)
			mCutsceneFinished=true;
	}
}
void LogicSubsystem::terminateCutsceneFunction(const std::string& functionName)
{
	lua_pop(mLuaEngine,1);
	mCoroutine=NULL;
}
bool LogicSubsystem::isCutsceneFinished(const std::string& functionName)
{
	return mCutsceneFinished;
}
void LogicSubsystem::initCutsceneScript(const std::string& scriptFilename)
{
	loadScript(SCRIPTS_PATH+"/"+scriptFilename);
}
void LogicSubsystem::skipCutscene(const std::string& functionName)
{

}
void LogicSubsystem::resetCutsceneFinished()
{
	mCutsceneFinished=false;
}