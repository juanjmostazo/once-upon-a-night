#include "LogicComponentBreakable.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"

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
	if( pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 && !mIsBroken)
	{	
		setIsBroken(true);
		getParent()->disable();
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

void LogicComponentBreakable::update(double elapsedTime)
{
	if (isStateChanged() && mIsBroken)
	{
		setStateChanged(false);
	}
}

TLogicComponentBreakableParameters::TLogicComponentBreakableParameters() : TLogicComponentParameters()
{

}

TLogicComponentBreakableParameters::~TLogicComponentBreakableParameters()
{

}
