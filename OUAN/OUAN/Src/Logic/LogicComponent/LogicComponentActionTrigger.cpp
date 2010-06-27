#include "OUAN_Precompiled.h"

#include "LogicComponentActionTrigger.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

LogicComponentActionTrigger::LogicComponentActionTrigger(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_TRIGGER_ACTION)
{
}

LogicComponentActionTrigger::~LogicComponentActionTrigger()
{

}

void LogicComponentActionTrigger::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		Logger::getInstance()->log("@@ Collision between " + getParent()->getName() + " and Ony");
	}
}

void LogicComponentActionTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	
}

void LogicComponentActionTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	
}

TLogicComponentActionTriggerParameters::TLogicComponentActionTriggerParameters() : TLogicComponentParameters()
{

}

TLogicComponentActionTriggerParameters::~TLogicComponentActionTriggerParameters()
{

}
