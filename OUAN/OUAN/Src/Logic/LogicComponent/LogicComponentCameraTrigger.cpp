#include "OUAN_Precompiled.h"

#include "LogicComponentCameraTrigger.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Graphics/CameraManager/CameraTrigger.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

LogicComponentCameraTrigger::LogicComponentCameraTrigger(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_TRIGGER_CAMERA)
{
}

LogicComponentCameraTrigger::~LogicComponentCameraTrigger()
{

}

void LogicComponentCameraTrigger::processCollision(GameObjectPtr pGameObject)
{

}

void LogicComponentCameraTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		CameraTriggerEventPtr evt;
		evt.reset( new CameraTriggerEvent());

		evt->pCameraTrigger=mCameraTrigger;

		getParent()->getGameWorldManager()->addEvent(evt);
	}
}

void LogicComponentCameraTrigger::processExitTrigger(GameObjectPtr pGameObject)
{

}

CameraTriggerPtr LogicComponentCameraTrigger::getCameraTrigger() const
{
	return mCameraTrigger;
}

void LogicComponentCameraTrigger::setCameraTrigger(CameraTriggerPtr pCameraTrigger)
{
	mCameraTrigger=pCameraTrigger;
}

TLogicComponentCameraTriggerParameters::TLogicComponentCameraTriggerParameters() : TLogicComponentParameters()
{

}

TLogicComponentCameraTriggerParameters::~TLogicComponentCameraTriggerParameters()
{

}
