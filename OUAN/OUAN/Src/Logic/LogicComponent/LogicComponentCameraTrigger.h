#ifndef LogicComponentCameraTriggerH_H
#define LogicComponentCameraTriggerH_H

#include "LogicComponent.h"
namespace OUAN
{

	class LogicComponentCameraTrigger: public LogicComponent
	{
	public:
		LogicComponentCameraTrigger(const std::string& type="");
		~LogicComponentCameraTrigger();
		// CameraTrigger
		CameraTriggerPtr getCameraTrigger() const;
		void setCameraTrigger(CameraTriggerPtr pCameraTrigger);

		void processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal);
		void processEnterTrigger(GameObjectPtr pGameObject);
		void processExitTrigger(GameObjectPtr pGameObject);

	protected:

		CameraTriggerPtr mCameraTrigger;
	};
	
	class TLogicComponentCameraTriggerParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentCameraTriggerParameters();
		~TLogicComponentCameraTriggerParameters();

		///Camera Parameters
		CameraTriggerPtr pCameraTrigger;
		bool triggerOnlyOnce;

	};
}

#endif