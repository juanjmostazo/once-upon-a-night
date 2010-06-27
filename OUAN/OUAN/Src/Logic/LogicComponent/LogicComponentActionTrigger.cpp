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

}

void LogicComponentActionTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		/*
		ActionTriggerEventPtr evt;
		evt.reset( new ActionTriggerEvent());

		evt->pActionTrigger=mActionTrigger;
		evt->name=getParent()->getName();
		evt->enter=true;

		getParent()->getGameWorldManager()->addEvent(evt);
		*/
	}
}

void LogicComponentActionTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		/*
		ActionTriggerEventPtr evt;
		evt.reset( new ActionTriggerEvent());

		evt->pActionTrigger=mActionTrigger;
		evt->name=getParent()->getName();
		evt->enter=false;

		getParent()->getGameWorldManager()->addEvent(evt);
		*/
	}
}

TLogicComponentActionTriggerParameters::TLogicComponentActionTriggerParameters() : TLogicComponentParameters()
{

}

TLogicComponentActionTriggerParameters::~TLogicComponentActionTriggerParameters()
{

}
