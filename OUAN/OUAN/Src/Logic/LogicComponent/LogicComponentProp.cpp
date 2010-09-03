#include "OUAN_Precompiled.h"

#include "LogicComponentProp.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Game/GameObject/GameObjectDiamondTree.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../Game/GameObject/GameObjectFlashLight.h"
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

void LogicComponentProp::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{

	Logger::getInstance()->log(" LogicComponentProp::processCollision "+getParent()->getName()+" "+pGameObject->getName());

	GameWorldManagerPtr worldMgr = mParent->getGameWorldManager();
	ApplicationPtr app = worldMgr->getParent();

 	bool isParentDiamondTree = mParent->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	bool isWeaponCollision=pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0 
		|| pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0;
	LogicSubsystemPtr logicSS = app->getLogicSubsystem();

	if(isParentDiamondTree && isWeaponCollision && (getState()==logicSS->getGlobalInt(DT_STATE_IDLE) || getState()==logicSS->getGlobalInt(DT_STATE_MAY_HIT)))
	{		
		if (mHitRecoveryTime<0)
		{
			getParent()->displayText("THUD!");
			//TODO: LAUNCH PARTICLES!!
			mHasTakenHit=true;			
			mHitRecoveryTime=1;
		}		
	}
	bool isParentSignpost = mParent->getType().compare(GAME_OBJECT_TYPE_SIGNPOST)==0;
	if (isParentSignpost && isWeaponCollision)
	{
		if(mHitRecoveryTime<0)
		{
			mHasTakenHit=true;
			mHitRecoveryTime=1;

			if (worldMgr->isFirstSignpostHit())
			{
				FirstSignpostHitEventPtr evt = FirstSignpostHitEventPtr(new FirstSignpostHitEvent());
				worldMgr->addEvent(evt);
			}
		}
	}
	bool isParentPortal = mParent->getType().compare(GAME_OBJECT_TYPE_PORTAL)==0;
	if (isParentPortal && isWeaponCollision)
	{
		if(mHitRecoveryTime<0)
		{
			mHasTakenHit=true;
			mHitRecoveryTime=0;
		}
	}
	bool isParentBomb = mParent->getType().compare(GAME_OBJECT_TYPE_BOMB)==0;
	if (isParentBomb && pGameObject->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)==0)
	{
		GameObjectFlashLightPtr flashlight= 
			BOOST_PTR_CAST(GameObjectFlashLight,pGameObject);
	Logger::getInstance()->log("FLASHLIGHT HIT");

		getParent()->setVisible(false);
	}

	bool isParentCryKing = mParent->getType().compare(GAME_OBJECT_TYPE_CRYKING)==0;
	if (isParentCryKing && pGameObject->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0)
	{
		getParent()->getGameWorldManager()->restartBombPosition();
	}
}
//void processActivate(ActivateEventPtr evt);
//void processAnimationEnded(AnimationEndedEventPtr evt);
//...

void LogicComponentProp::update(double elapsedTime)
{
	LogicComponent::update(elapsedTime);
	if (mTimeSpent>=0.0 && mTimeSpent<mDelay)
		mTimeSpent+=elapsedTime;
	if(mHitRecoveryTime>=0)
		mHitRecoveryTime-=elapsedTime;
	
	mHasTakenHit=false;
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