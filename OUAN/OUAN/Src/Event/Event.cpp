#include "Event.h"
using namespace OUAN;
bool EventComparator::operator() (EventPtr& evt1, EventPtr& evt2)
{
	if (!evt1.get()) return true;
	if (!evt2.get()) return false;
	return evt1->getPriority()<evt2->getPriority();
}

Event::Event(int priority, int eventType)
:mEventType(eventType)
,mPriority(priority)
{
}
int Event::getEventType() const
{
	return mEventType;
}
int Event::getPriority() const
{
	return mPriority;
}