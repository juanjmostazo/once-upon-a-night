#include "LogicComponentItem.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"


using namespace OUAN;

LogicComponentItem::LogicComponentItem(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_ITEM)
{

	mIsTaken=false;
}

LogicComponentItem::~LogicComponentItem()
{
}

void LogicComponentItem::processCollision(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		setIsTaken(true);
		getParent()->disable();
	}
}

bool LogicComponentItem::getIsTaken() const
{
	return mIsTaken;
}

void LogicComponentItem::setIsTaken(bool isTaken)
{
	if(isTaken)
	{
		setState(STATE_ITEM_TAKEN);
	}
	else
	{
		setState(STATE_ITEM_NOT_TAKEN);
	}
	mIsTaken=isTaken;
}

TLogicComponentItemParameters::TLogicComponentItemParameters() : TLogicComponentParameters()
{
}

TLogicComponentItemParameters::~TLogicComponentItemParameters()
{
}
