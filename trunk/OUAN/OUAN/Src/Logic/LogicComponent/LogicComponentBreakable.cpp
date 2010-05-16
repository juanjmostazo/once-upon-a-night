#include "LogicComponentBreakable.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"

using namespace OUAN;

LogicComponentBreakable::LogicComponentBreakable(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_BREAKABLE)
{
	mIsBroken=false;
}

LogicComponentBreakable::~LogicComponentBreakable()
{

}

void LogicComponentBreakable::processCollision(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0 && !mIsBroken)
	{
		//setIsBroken(true);
		//getParent()->disable();
	}
}

bool LogicComponentBreakable::getIsBroken() const
{
	return mIsBroken;
}

void LogicComponentBreakable::setIsBroken(bool isBroken)
{
	if(isBroken)
	{
		setState(STATE_BREAKABLE_BROKEN);
	}
	else
	{
		setState(STATE_BREAKABLE_NOT_BROKEN);
	}

	mIsBroken=isBroken;
}

TLogicComponentBreakableParameters::TLogicComponentBreakableParameters() : TLogicComponentParameters()
{

}

TLogicComponentBreakableParameters::~TLogicComponentBreakableParameters()
{

}
