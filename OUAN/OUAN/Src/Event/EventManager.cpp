#include "EventManager.h"
using namespace OUAN;
EventManager::EventManager()
{
}
EventManager::~EventManager()
{

}
void EventManager::addEvent(EventPtr evt)
{
	mEventQueue.push(evt);
}
void EventManager::dispatchEvents()
{
	while(!mEventQueue.empty())
	{
		EventPtr evt = removeEvent();
		//for (HandlersIterator it=handlers.begin();it!=handlers.end();++it)
		//{
		//	(*it)->handleEvent(evt);
		//}
		
	}
}
EventPtr EventManager::peekEvent() const
{
	if (!mEventQueue.empty())
		return mEventQueue.top();
	else return EventPtr();
}
EventPtr EventManager::removeEvent()
{
	if (!mEventQueue.empty())
	{
		EventPtr result=mEventQueue.top();
		mEventQueue.pop();
		return result;
	}
	return EventPtr();
}