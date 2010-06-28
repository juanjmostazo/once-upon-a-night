#ifndef LogicComponentActionTriggerH_H
#define LogicComponentActionTriggerH_H

#include "LogicComponent.h"

namespace OUAN
{

	class LogicComponentActionTrigger: public LogicComponent
	{
	public:
		LogicComponentActionTrigger(const std::string& type="");
		~LogicComponentActionTrigger();

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		void processEnterTrigger(GameObjectPtr pGameObject);
		void processExitTrigger(GameObjectPtr pGameObject);

	protected:

		std::string triggerPlatformBigName;
		std::string portalPlatformBigName;
		double portalPlatformBigMaxDistance;

		void processActionPlatformBig();
	};

	class TLogicComponentActionTriggerParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentActionTriggerParameters();
		~TLogicComponentActionTriggerParameters();
	};
}

#endif