#include "EventManager.h"
#include <algorithm>

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
		if (mEventHandlers.count(evt->getEventType()))
		{
			for (TEventHandlerList::iterator it = mEventHandlers[evt->getEventType()].begin();it!=mEventHandlers[evt->getEventType()].end();++it)
			{
				(*it)->handleEvent(evt);				
			}
		}
	}
}

EventPtr EventManager::peekEvent() const
{
	if (!mEventQueue.empty())
	{
		return mEventQueue.top();
	}
	else
	{
		return EventPtr();
	}
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

void EventManager::registerHandler(EventHandlerPtr handler, TEventType evtType)
{
	if (mEventHandlers.count(evtType)==0)
	{
		mEventHandlers[evtType].clear();
	}

	mEventHandlers[evtType].push_back(handler);
}

void EventManager::unregisterHandler(EventHandlerPtr hdl,TEventType evtType)
{
	if (!mEventHandlers.empty() && mEventHandlers.count(evtType))
	{
		//look for handler in the list
		TEventHandlerList::iterator newEnd=remove_if(
			mEventHandlers[evtType].begin(),
			mEventHandlers[evtType].end(),
			EventHandlerComparisonFunctor(hdl));

		mEventHandlers[evtType].erase(newEnd,mEventHandlers[evtType].end());

		if (mEventHandlers[evtType].size()==0)
		{
			mEventHandlers.erase(evtType);
		}
	}
}

void EventManager::clear()
{
	while(!mEventQueue.empty())
	{
		mEventQueue.pop();
	}

	for (TEventHandlerMap::iterator it=mEventHandlers.begin();it!=mEventHandlers.end();++it)
	{
		(it->second).clear();
	}

	mEventHandlers.clear();
}