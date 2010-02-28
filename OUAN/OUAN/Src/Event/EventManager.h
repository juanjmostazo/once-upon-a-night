#ifndef EVENTMANAGERH_H
#define EVENTMANAGERH_H
#include "../OUAN.h"
#include "Event.h"

#include <queue>
#include <vector>

namespace OUAN
{
	typedef std::priority_queue<EventPtr,std::vector<EventPtr>,EventComparator> TEventQueue;
	class EventManager
	{
	private:
		TEventQueue mEventQueue;
		//Handlers
	public:
		EventManager();
		virtual ~EventManager();
		void addEvent(EventPtr evt);
		void dispatchEvents();
		EventPtr peekEvent() const;
		EventPtr removeEvent();

		//
		//void registerHandler(EventHandler);
		//void unregisterHandler(EventHandler);
	};
}
#endif