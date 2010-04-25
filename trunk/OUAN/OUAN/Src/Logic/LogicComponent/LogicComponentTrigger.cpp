#include "LogicComponentTrigger.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"

using namespace OUAN;

LogicComponentTrigger::LogicComponentTrigger(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_TRIGGER)
{
}

LogicComponentTrigger::~LogicComponentTrigger()
{

}

void LogicComponentTrigger::processCollision(GameObjectPtr pGameObject)
{
}
void LogicComponentTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	bool hasEnterActionDefined = !mTriggerScript.empty() && (!mDreamsEnterActionFunction.empty() || !mNightmaresEnterActionFunction.empty());
	if (hasEnterActionDefined && pGameObject.get() && pGameObject->getType()==GAME_OBJECT_TYPE_ONY)
	{
		LogicSubsystemPtr logicSS= Application::getInstance()->getLogicSubsystem();
		logicSS->loadScript(SCRIPTS_PATH+"/"+mTriggerScript);		
		int world=getParent()->getGameWorldManager()->getCurrentWorld();
		GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(pGameObject);	
		
		if (world==DREAMS)
		{			
			bool conditionFulfilled = mDreamsEnterConditionFunction.empty() || 
				logicSS->invokeConditionFunction(mDreamsEnterConditionFunction,ony->getLogicComponentOny().get());
			if (!mDreamsEnterActionFunction.empty() && conditionFulfilled)	
			{
					logicSS->invokeActionFunction(mDreamsEnterActionFunction,ony->getLogicComponentOny().get());
			}
		}
		else //NIGHTMARES
		{
			bool conditionFulfilled = mNightmaresEnterConditionFunction.empty() || 
				logicSS->invokeConditionFunction(mNightmaresEnterConditionFunction,ony->getLogicComponentOny().get());
			if (!mNightmaresEnterActionFunction.empty() && conditionFulfilled)	
			{
					logicSS->invokeActionFunction(mNightmaresEnterActionFunction,ony->getLogicComponentOny().get());
			}		
		}
	}
}
void LogicComponentTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	bool hasExitActionDefined = !mTriggerScript.empty() && (!mDreamsExitActionFunction.empty() || !mNightmaresExitActionFunction.empty());
	if (hasExitActionDefined && pGameObject.get() && pGameObject->getType()==GAME_OBJECT_TYPE_ONY)
	{
		LogicSubsystemPtr logicSS= Application::getInstance()->getLogicSubsystem();
		logicSS->loadScript(SCRIPTS_PATH+"/"+mTriggerScript);

		int world=getParent()->getGameWorldManager()->getCurrentWorld();
		GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(pGameObject);	
		if (DREAMS)
		{			
			bool conditionFulfilled = mDreamsExitConditionFunction.empty() || 
				logicSS->invokeConditionFunction(mDreamsExitConditionFunction,ony->getLogicComponentOny().get());
			if (!mDreamsExitActionFunction.empty() && conditionFulfilled)	
			{
				logicSS->invokeActionFunction(mDreamsExitActionFunction,ony->getLogicComponentOny().get());
			}
		}
		else //NIGHTMARES
		{
			bool conditionFulfilled = mNightmaresExitConditionFunction.empty() || 
				logicSS->invokeConditionFunction(mNightmaresExitConditionFunction,ony->getLogicComponentOny().get());
			if (!mNightmaresExitActionFunction.empty() && conditionFulfilled)	
			{
				logicSS->invokeActionFunction(mNightmaresExitActionFunction,ony->getLogicComponentOny().get());			
			}		
		}
	}
}

std::string LogicComponentTrigger::getDreamsEnterConditionFunction()
{
	return mDreamsEnterConditionFunction;
}
void LogicComponentTrigger::setDreamsEnterConditionFunction(const std::string& dreamsEnterConditionFunction)
{
	mDreamsEnterConditionFunction=dreamsEnterConditionFunction;
}

std::string LogicComponentTrigger::getDreamsExitConditionFunction()
{
	return mDreamsExitConditionFunction;
}
void LogicComponentTrigger::setDreamsExitConditionFunction(const std::string& dreamsExitConditionFunction)
{
	mDreamsExitConditionFunction=dreamsExitConditionFunction;
}

std::string LogicComponentTrigger::getDreamsEnterActionFunction()
{
	return mDreamsEnterActionFunction;
}
void LogicComponentTrigger::setDreamsEnterActionFunction(const std::string& dreamsEnterActionFunction)
{
	mDreamsEnterActionFunction=dreamsEnterActionFunction;
}

std::string LogicComponentTrigger::getDreamsExitActionFunction()
{
	return mDreamsExitActionFunction;
}
void LogicComponentTrigger::setDreamsExitActionFunction(const std::string& dreamsExitActionFunction)
{
	mDreamsExitActionFunction=dreamsExitActionFunction;
}


//---
std::string LogicComponentTrigger::getNightmaresEnterConditionFunction()
{
	return mNightmaresEnterConditionFunction;
}
void LogicComponentTrigger::setNightmaresEnterConditionFunction(const std::string& nightmaresEnterConditionFunction)
{
	mNightmaresEnterConditionFunction=nightmaresEnterConditionFunction;
}

std::string LogicComponentTrigger::getNightmaresExitConditionFunction()
{
	return mNightmaresExitConditionFunction;
}
void LogicComponentTrigger::setNightmaresExitConditionFunction(const std::string& nightmaresExitConditionFunction)
{
	mNightmaresExitConditionFunction=nightmaresExitConditionFunction;
}

std::string LogicComponentTrigger::getNightmaresEnterActionFunction()
{
	return mNightmaresEnterActionFunction;
}
void LogicComponentTrigger::setNightmaresEnterActionFunction(const std::string& nightmaresEnterActionFunction)
{
	mNightmaresEnterActionFunction=nightmaresEnterActionFunction;
}

std::string LogicComponentTrigger::getNightmaresExitActionFunction()
{
	return mNightmaresExitActionFunction;
}
void LogicComponentTrigger::setNightmaresExitActionFunction(const std::string& nightmaresExitActionFunction)
{
	mNightmaresExitActionFunction=nightmaresExitActionFunction;
}

std::string LogicComponentTrigger::getTriggerScript()
{
	return mTriggerScript;
}
void LogicComponentTrigger::setTriggerScript(const std::string& triggerScript)
{
	mTriggerScript=triggerScript;
}
//---
TLogicComponentTriggerParameters::TLogicComponentTriggerParameters() : TLogicComponentParameters()
{
}

TLogicComponentTriggerParameters::~TLogicComponentTriggerParameters()
{
}