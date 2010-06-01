#include "LogicComponentProp.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectDiamondTree.h"
#include "../../Game/GameObject/GameObjectOny.h"

using namespace OUAN;

LogicComponentProp::LogicComponentProp(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_PROP)
,mTimeSpent(0)
,mHasTakenHit(false)
,mHitRecoveryTime(-1)
{

}

LogicComponentProp::~LogicComponentProp()
{

}

void LogicComponentProp::processCollision(GameObjectPtr pGameObject)
{
	
/* 	bool isParentDiamondTree = mParent->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	bool isWeaponCollision=pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 
		|| pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0;
	LogicSubsystemPtr logicSS = mParent->getGameWorldManager()->getParent()->getLogicSubsystem();

	if(isParentDiamondTree && isWeaponCollision && getState()==logicSS->getGlobalInt(DT_STATE_IDLE))
	{		
		if (mHitRecoveryTime<0)
		{
			getParent()->displayText("THUD!");
			mHasTakenHit=true;			
			mHitRecoveryTime=1;
		}		
	}*/	
	if (pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		GameObjectOnyPtr ony = boost::dynamic_pointer_cast<GameObjectOny>(pGameObject);
		if (ony.get() && CHECK_BIT(ony->getLogicComponentOny()->getState(),ONY_STATE_BIT_FIELD_ATTACK)
			&& mParent->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0)
		{
			if (mHitRecoveryTime<0)
			{
				getParent()->displayText("THUD!");
				mHasTakenHit=true;			
				mHitRecoveryTime=1;
			}			
		}
	}
}
//void processActivate(ActivateEventPtr evt);
//void processAnimationEnded(AnimationEndedEventPtr evt);
//...

void LogicComponentProp::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
	if (mTimeSpent<mDelay)
		mTimeSpent+=elapsedTime;
	if(mHitRecoveryTime>=0)
		mHitRecoveryTime-=elapsedTime;
}

double LogicComponentProp::getApproachDistance() const
{
	return mApproachDistance;
}
void LogicComponentProp::setApproachDistance(double approachDistance)
{
	mApproachDistance=approachDistance;
}
double LogicComponentProp::getTimeSpent() const
{
	return mTimeSpent;
}
void LogicComponentProp::setTimeSpent(double timeSpent)
{
	mTimeSpent=timeSpent;
}
double LogicComponentProp::getDelay() const
{
	return mDelay;
}
void LogicComponentProp::setDelay(double delay)
{
	mDelay=delay;
}
bool LogicComponentProp::hasTakenHit() const
{
	return mHasTakenHit;
}
void LogicComponentProp::setHasTakenHit(bool hasTakenHit)
{
	mHasTakenHit=hasTakenHit;
}
bool LogicComponentProp::isReload() const
{
	return mReload;
}
void LogicComponentProp::setReload(bool reload)
{
	mReload=reload;
}
TLogicComponentPropParameters::TLogicComponentPropParameters()
{
}
TLogicComponentPropParameters::~TLogicComponentPropParameters()
{

}