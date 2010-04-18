#include "Event.h"

using namespace OUAN;

bool EventComparator::operator() (EventPtr& evt1, EventPtr& evt2)
{
	if (!evt1.get()) return true;
	if (!evt2.get()) return false;
	// The more or less standard convention for a priority queue
	// assigns more priority to values with lower numbers.
	// However, the STL implementation does the opposite ¬_¬.
	// To stick with the more familiar convention, the comparison operator
	// used for this method is > instead of <, so that the queue ordering 
	// gets reversed.
	return evt1->getPriority()>evt2->getPriority();
}

//-------------------------

Event::Event(int priority, TEventType eventType)
:mEventType(eventType)
,mPriority(priority)
{

}

TEventType Event::getEventType() const
{
	return mEventType;
}

int Event::getPriority() const
{
	return mPriority;
}

//----------------------

ChangeWorldEvent::ChangeWorldEvent(int newWorld)
:Event(EVT_PRIORITY_CHANGEWORLD,EVENT_TYPE_CHANGEWORLD)
,mNewWorld(newWorld)
{

};

int ChangeWorldEvent::getNewWorld() const
{
	return mNewWorld;
}

//----------------------

CollisionEvent::CollisionEvent(GameObjectPtr pGameObject1, GameObjectPtr pGameObject2)
:Event(EVT_PRIORITY_COLLISION,EVENT_TYPE_COLLISION)
{
	mGameObject1=pGameObject1;
	mGameObject2=pGameObject2;
};

GameObjectPtr CollisionEvent::getGameObject1()
{
	return mGameObject1;
}

GameObjectPtr CollisionEvent::getGameObject2()
{
	return mGameObject2;
}

//----------------------

EnterTriggerEvent::EnterTriggerEvent(GameObjectPtr pTrigger, GameObjectPtr pGameObject)
:Event(EVT_PRIORITY_ENTER_TRIGGER,EVENT_TYPE_ENTER_TRIGGER)
{
	mTrigger=pTrigger;
	mGameObject=pGameObject;
};

GameObjectPtr EnterTriggerEvent::getGameObject()
{
	return mGameObject;
}

GameObjectPtr EnterTriggerEvent::getTrigger()
{
	return mTrigger;
}

//----------------------
//----------------------

ExitTriggerEvent::ExitTriggerEvent(GameObjectPtr pTrigger, GameObjectPtr pGameObject)
:Event(EVT_PRIORITY_EXIT_TRIGGER,EVENT_TYPE_EXIT_TRIGGER)
{
	mTrigger=pTrigger;
	mGameObject=pGameObject;
};

GameObjectPtr ExitTriggerEvent::getGameObject()
{
	return mGameObject;
}

GameObjectPtr ExitTriggerEvent::getTrigger()
{
	return mTrigger;
}

//----------------------

ClearQueueEvent::ClearQueueEvent()
:Event(EVT_PRIORITY_CLEARQUEUE,EVENT_TYPE_CLEARQUEUE)
{
}

//----------------------

GameOverEvent::GameOverEvent(bool win)
:Event(EVT_PRIORITY_GAMEOVER,EVENT_TYPE_GAMEOVER)
,mWin(win)
{
}

bool GameOverEvent::isWin() const
{
	return mWin;
}
//-----------------------

OnyDiesEvent::OnyDiesEvent(int remainingLives)
:Event(EVT_PRIORITY_ONY_DEATH,EVENT_TYPE_ONY_DEATH)
,mRemainingLives(remainingLives)
{

}

//-----------------------

OnyFallsEvent::OnyFallsEvent()
:Event(EVT_PRIORITY_ONY_FALLS,EVENT_TYPE_ONY_FALLS)
{

}

//-----------------------
WeaponModeChangedEvent::WeaponModeChangedEvent(TWeaponMode newWeaponMode)
:Event(EVT_PRIORITY_WEAPON_MODE_CHANGED,EVENT_TYPE_WEAPON_MODE_CHANGED)
{
	mNewWeaponMode=newWeaponMode;
}
TWeaponMode WeaponModeChangedEvent::getNewWeaponMode() const
{
	return mNewWeaponMode;
}
