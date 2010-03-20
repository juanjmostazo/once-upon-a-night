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