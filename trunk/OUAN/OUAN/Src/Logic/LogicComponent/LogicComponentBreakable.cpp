#include "OUAN_Precompiled.h"

#include "LogicComponentBreakable.h"
#include "../LogicSubsystem.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameObject/GameObjectWoodBox.h"

using namespace OUAN;

LogicComponentBreakable::LogicComponentBreakable(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_BREAKABLE)
,mElapsedTimeSinceBreakup(-1)
,mDisableTime(5)
{
	mIsBroken=false;
}

LogicComponentBreakable::~LogicComponentBreakable()
{

}

void LogicComponentBreakable::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW) == 0 && !mIsBroken)
	{	
		setIsBroken(true);
		if (mDisableTime>=0.0)
		{
			mElapsedTimeSinceBreakup=0;
		}

		Logger::getInstance()->log("BREAK");

		if (getParent()->getType().compare(GAME_OBJECT_TYPE_WOODBOX))
		{
			GameObjectWoodBoxPtr box = BOOST_PTR_CAST(GameObjectWoodBox, getParent());
			box->getRenderComponentParticleSystemDust()->start();
		}
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

	if (mDisableTime>=0.0)
	{
		if (mElapsedTimeSinceBreakup>mDisableTime)
		{
			getParent()->disable();
		}

		else
		{
			mElapsedTimeSinceBreakup+=elapsedTime;
		}
	}
}

double LogicComponentBreakable::getDisableTime() const
{
	return mDisableTime;
}
void LogicComponentBreakable::setDisableTime(double disableTime)
{
	mDisableTime=disableTime;
}

TLogicComponentBreakableParameters::TLogicComponentBreakableParameters() : TLogicComponentParameters()
{

}

TLogicComponentBreakableParameters::~TLogicComponentBreakableParameters()
{

}
