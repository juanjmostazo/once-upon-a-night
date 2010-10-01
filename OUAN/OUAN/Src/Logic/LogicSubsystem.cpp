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
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectSignpost.h"
#include "../Game/GameObject/GameObjectNest.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Core/GameRunningState.h"
#include "../Core/CutsceneState.h"
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
	
	mScriptFiles.clear();
	addScriptFile(SCRIPT_COMMON_FUNCTIONS);
	//loadScripts();
}

void LogicSubsystem::registerModules()
{
	using namespace luabind;

	module(mLuaEngine) [
		def("log", (void (*) (const std::string&)) &Utils::scriptLog),
		def("world",&Application::world),
		def("getDistance",&GameWorldManager::getDistance),
		def("getPlayerDistance",&GameWorldManager::getPlayerDistance),
		def("getWorld",&GameWorldManager::getMyInstanceWorld),
		def("victory",&GameWorldManager::victory),
		def("skip",&CutsceneState::isSkippingCutscene),
		def("changeWorld",&CutsceneState::changeWorld),
		def("setMyReturningToGameTransition",&CutsceneState::setMyReturningToGameTransitionLUA),
		def("hasFinishedChangingWorld",&CutsceneState::hasFinishedChangingWorld),
		def("changeLevel",&GameRunningState::changeLevel),
		def("setCheckPoint",&GameWorldManager::setCheckPointLUA),
		def("getCheckPointNumber",&GameWorldManager::getCheckPointNumberLUA),
		def("isChangingWorld",&GameWorldManager::isChangingWorldLUA),
		def("playMusic",&GameRunningState::playMusic),
		def("playSoundFromGameObject",&GameRunningState::playSoundFromGameObject),
		def("launchCutScene",&GameRunningState::launchCutScene),
		def("setCameraTrajectory",&CameraManager::setCameraTrajectoryLUA),
		def("setCameraFree",&CameraManager::setCameraFreeLUA),
		def("setCameraTracking",&CameraManager::setCameraTrackingLUA),
		def("setDefaultThirdPersonCamera",&CameraManager::setDefaultThirdPersonCameraLUA),
		def("setCameraFixedFirstPerson",&CameraManager::setCameraFixedFirstPersonLUA),
		def("isCameraTrajectoryFinished",&CameraManager::isCameraTrajectoryEnded),
		def("setAnyTrackingCamera",&CameraManager::setAnyTrackingCamera),
		def("getAny",&GameWorldManager::getOny),
		def("getCryKing",&GameWorldManager::getCryKing),
		def("getBomb",&GameWorldManager::getBomb),
		def("getObject",&GameWorldManager::getGameObject),
		def("addExecutedLevelEvent",&GameWorldManager::addExecutedLevelEventLUA),
		def("hasExecutedLevelEvent",&GameWorldManager::hasExecutedLevelEventLUA),
		def("restartBombPosition",&GameWorldManager::restartBombPositionLUA),
		def("initBombPuzzle",&GameWorldManager::initBombPuzzleLUA),
		class_<GameObject>("GameObject")
			.def("setCurrentWorldVisible", &GameObject::setCurrentWorldVisibility)
			.def("enabled",&GameObject::isEnabled),
		class_<GameObjectPortal, GameObject>("GameObjectPortal")
			.def("setCurrentWorldVisible", &GameObjectPortal::setCurrentWorldVisibility),
		class_<GameObjectTripollo, GameObject>("GameObjectTripollo"),
		class_<Utils::LUATimer>("Timer")
			.def(constructor<>())
			.def("reset",&Utils::LUATimer::reset)
			.def("getTime",&Utils::LUATimer::getTime),
		class_<LogicComponent>("LogicComponent")
		.def(constructor<const std::string&>())
			.def("getName",&LogicComponent::getParentName)
			.def("say",&LogicComponent::printMessage)
			.def("getTimeSpent",&LogicComponent::getTimeSpent)
			.def("setTimeSpent",&LogicComponent::setTimeSpent)
			.def("changeAnimation",&LogicComponent::changeAnimation)
			.def("animLooping",&LogicComponent::isLoopingAnimation)
			.def("animFinished",&LogicComponent::hasFinishedAnimation),
		class_<LogicComponentEnemy, LogicComponent > ("LogicComponentEnemy")
			.def(constructor<const std::string&>())
			.def("getWorld",&LogicComponentEnemy::getWorld)
			.def("getNumLives",&LogicComponentEnemy::getNumLives)
			.def("getLineOfSight",&LogicComponentEnemy::getLineOfSight)
			.def("getHP",&LogicComponentEnemy::getHealthPoints)
			.def("getMaxHP",&LogicComponentEnemy::getInitialHealthPoints)
			.def("getEnemyType",&LogicComponentEnemy::getEnemyTypeLUA)
			.def("hasBeenHit",&LogicComponentEnemy::hasBeenHit)
			.def("hasHitOny",&LogicComponentEnemy::hasHitOny)
			.def("hasDied",&LogicComponentEnemy::hasDied)
			.def("getNeighboursInRange",&LogicComponentEnemy::getNeighboursInRange)
			.def("callWasHeard",&LogicComponentEnemy::callWasHeard)
			.def("hasHeardCall",&LogicComponentEnemy::hasHeardCall)			
			.def("getPreviousState",&LogicComponentEnemy::getPreviousState)
			.def("isAlertFinished",&LogicComponentEnemy::isAlertFinished)
			.def("isSurpriseFinished",&LogicComponentEnemy::isSurpriseFinished)
			.def("isFalseAlarmFinished",&LogicComponentEnemy::isFalseAlarmFinished)
			.def("isCallToArmsFinished",&LogicComponentEnemy::isCallToArmsFinished)
			.def("isIdle1Finished",&LogicComponentEnemy::isIdle1Finished)
			.def("isAttackFinished",&LogicComponentEnemy::isAttackFinished)
			.def("isFlashLightHitFinished",&LogicComponentEnemy::isFlashLightHitFinished)
			.def("isPillowHitFinished",&LogicComponentEnemy::isPillowHitFinished)
			.def("getMeleeRange",&LogicComponentEnemy::getMeleeRange)
			.def("isTiredFinished",&LogicComponentEnemy::isTiredFinished)
			.def("isStatueEnabled",&LogicComponentEnemy::isStatueEnabled)
			.def("isFlyingEnabled",&LogicComponentEnemy::isFlyingEnabled)
			.def("isFlying",&LogicComponentEnemy::isFlying)
			.def("hasPatrolTrajectory",&LogicComponentEnemy::hasPatrolTrajectory),
		class_<LogicComponentOny, LogicComponent > ("LogicComponentOny")
			.def(constructor<const std::string&>())
			.def("getNumLives",&LogicComponentOny::getNumLives)
			.def("getHP",&LogicComponentOny::getHealthPoints)
			.def("getMaxHP",&LogicComponentOny::getInitialHealthPoints)
			.def("beginTrajectory",&LogicComponentOny::activateTrajectory)
			.def("endTrajectory", &LogicComponentOny::deactivateTrajectory)
			.def("isTrajectoryFinished",&LogicComponentOny::isTrajectoryFinished)
			.def("changeMessage",(void(LogicComponentOny::*)(const std::string&, double))&LogicComponentOny::changeMessage)
			.def("changeMessage",(void(LogicComponentOny::*)(const std::string&))&LogicComponentOny::changeMessage)
			.def("showMessage",&LogicComponentOny::showMessage)
			.def("hideMessage",&LogicComponentOny::hideMessage)
			.def("isMessageVisible",&LogicComponentOny::isMessageVisible)
			,
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
			.def("hasTakenHit", &LogicComponentProp::hasTakenHit)
			.def("isRecovered", &LogicComponentProp::isRecovered)
			.def("isReloadSet", &LogicComponentProp::isReload)
	];
}
void LogicSubsystem::addScriptFile(const std::string& scriptFile)
{
	mScriptFiles.insert(scriptFile);
}
void LogicSubsystem::addScriptFiles(std::set<std::string> scriptFiles)
{
	//This isn't the most efficient way to insert a vector, but
	// we need to check
	mScriptFiles.insert(scriptFiles.begin(),scriptFiles.end());
}
void LogicSubsystem::loadScripts()
{
	//loadScript(SCRIPTS_PATH+"/"+SCRIPT_COMMON_FUNCTIONS);
	if (!mScriptFiles.empty())
	{
		for (std::set<std::string>::const_iterator it=mScriptFiles.begin();
			it!=mScriptFiles.end();++it)
			loadScript(SCRIPTS_PATH+"/"+*it);
	}
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
				//it->second->updateLogic(elapsedSeconds);
				if (it->second->isWorthUpdatingLogicComponents())
				{
					it->second->updateLogic(it->second->getElapsedTimeSinceLastLogicUpdate()+elapsedSeconds);
					it->second->setElapsedTimeSinceLastLogicUpdate(0);
				}
				else
				{
					it->second->setElapsedTimeSinceLastLogicUpdate(it->second->getElapsedTimeSinceLastLogicUpdate()+elapsedSeconds);
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
double LogicSubsystem::getGlobalReal(const std::string& globalName)
{
	return luabind::object_cast<double>(luabind::globals(mLuaEngine)[globalName]);
}

void LogicSubsystem::invokeCutsceneFunction(const std::string& functionName)
{
	mCoroutine=lua_newthread(mLuaEngine);
	mCutsceneFinished=false;
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
	if (mCoroutine && !mCutsceneFinished)
	{
		mTimer->addTime(elapsedSeconds);
		int retVal=luabind::resume<int>(mCoroutine,mTimer.get());
		if (retVal==1)
			mCutsceneFinished=true;
	}
}
void LogicSubsystem::terminateCutsceneFunction(const std::string& functionName)
{
	int i= lua_gettop(mLuaEngine);
	Logger::getInstance()->log("LUA::Terminate called!");
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