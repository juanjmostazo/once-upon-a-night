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

CharactersCollisionEvent::CharactersCollisionEvent(GameObjectPtr pCharacter1, GameObjectPtr pCharacter2)
:Event(EVT_PRIORITY_CHARACTERS_COLLISION,EVENT_TYPE_CHARACTERS_COLLISION)
{
	mCharacter1=pCharacter1;
	mCharacter2=pCharacter2;
};

GameObjectPtr CharactersCollisionEvent::getCharacter1()
{
	return mCharacter1;
}

GameObjectPtr CharactersCollisionEvent::getCharacter2()
{
	return mCharacter2;
}

//----------------------

CharacterInTriggerEvent::CharacterInTriggerEvent(GameObjectPtr pCharacter, GameObjectPtr pTrigger, int pCollisionType)
:Event(EVT_PRIORITY_CHARACTER_IN_TRIGGER,EVENT_TYPE_CHARACTER_IN_TRIGGER)
{
	mCharacter=pCharacter;
	mTrigger=pTrigger;
	mCollisionType=pCollisionType;
};

GameObjectPtr CharacterInTriggerEvent::getCharacter()
{
	return mCharacter;
}

GameObjectPtr CharacterInTriggerEvent::getTrigger()
{
	return mTrigger;
}

int CharacterInTriggerEvent::getCollisionType()
{
	return mCollisionType;
}
//----------------------
//----------------------

CharacterShapeFrontCollisionEvent::CharacterShapeFrontCollisionEvent(GameObjectPtr pCharacter, GameObjectPtr pShape)
:Event(EVT_PRIORITY_CHARACTER_SHAPE_FRONT_COLLISION,EVENT_TYPE_CHARACTER_SHAPE_FRONT_COLLISION)
{
	mCharacter=pCharacter;
	mShape=pShape;
};

GameObjectPtr CharacterShapeFrontCollisionEvent::getCharacter()
{
	return mCharacter;
}

GameObjectPtr CharacterShapeFrontCollisionEvent::getShape()
{
	return mShape;
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