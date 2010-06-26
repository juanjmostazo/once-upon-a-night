#ifndef LOGICCOMPONENTTRIGGERH_H
#define LOGICCOMPONENTTRIGGERH_H

#include "LogicComponent.h"
namespace OUAN
{

	class LogicComponentTrigger: public LogicComponent
	{
	public:
		LogicComponentTrigger(const std::string& type="");
		~LogicComponentTrigger();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		void processEnterTrigger(GameObjectPtr pGameObject);
		void processExitTrigger(GameObjectPtr pGameObject);

		std::string getTriggerScript();
		void setTriggerScript(const std::string& triggerScript);

		std::string getDreamsEnterConditionFunction();
		void setDreamsEnterConditionFunction(const std::string& dreamsEnterConditionFunction);

		std::string getDreamsExitConditionFunction();
		void setDreamsExitConditionFunction(const std::string& dreamsExitConditionFunction);

		std::string getNightmaresEnterConditionFunction();
		void setNightmaresEnterConditionFunction(const std::string& nightmaresEnterConditionFunction);

		std::string getNightmaresExitConditionFunction();
		void setNightmaresExitConditionFunction(const std::string& nightmaresExitConditionFunction);

		std::string getDreamsEnterActionFunction();
		void setDreamsEnterActionFunction(const std::string& dreamsEnterActionFunction);

		std::string getDreamsExitActionFunction();
		void setDreamsExitActionFunction(const std::string& dreamsExitActionFunction);

		std::string getNightmaresEnterActionFunction();
		void setNightmaresEnterActionFunction(const std::string& nightmaresEnterActionFunction);

		std::string getNightmaresExitActionFunction();
		void setNightmaresExitActionFunction(const std::string& nightmaresExitActionFunction);		
	private:
		//TODO: Extend this to multiple possible actions depending on the object that enters if necessary
		// Since at the moment the only one that'll be of relevance will be Ony, we can do fine with just one

		//NOTE: The condition functions may be empty: in that case, the action function 
		// will be fired unconditionally
		
		//Name of the LUA function to check the enter condition
		std::string mDreamsEnterConditionFunction;
		//Name of the LUA function to execute the trigger enter actions
		std::string mDreamsEnterActionFunction;

		//Name of the LUA function to check the exit condition
		std::string mDreamsExitConditionFunction;
		//Name of the LUA function to execute the trigger exit actions
		std::string mDreamsExitActionFunction;	

		//Name of the LUA function to check the enter condition
		std::string mNightmaresEnterConditionFunction;
		//Name of the LUA function to execute the trigger enter actions
		std::string mNightmaresEnterActionFunction;

		//Name of the LUA function to check the exit condition
		std::string mNightmaresExitConditionFunction;
		//Name of the LUA function to execute the trigger exit actions
		std::string mNightmaresExitActionFunction;	

		//Name of the script filename where the trigger actions will be defined
		std::string mTriggerScript;

	};

	class TLogicComponentTriggerParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentTriggerParameters();
		~TLogicComponentTriggerParameters();

		
		std::string mDreamsEnterConditionFunction;
		std::string mDreamsEnterActionFunction;

		std::string mDreamsExitConditionFunction;
		std::string mDreamsExitActionFunction;	

		std::string mNightmaresEnterConditionFunction;
		std::string mNightmaresEnterActionFunction;

		std::string mNightmaresExitConditionFunction;
		std::string mNightmaresExitActionFunction;	

		std::string mTriggerScript;
	};
}

#endif