#ifndef EVENTMANAGERH_H
#define EVENTMANAGERH_H

#include "../OUAN.h"
#include "Event.h"
#include "EventHandler.h"

#include <queue>
#include <vector>
#include <list>

namespace OUAN
{
	typedef std::priority_queue<EventPtr,std::vector<EventPtr>,EventComparator> TEventQueue;
	typedef std::list<EventHandlerPtr> TEventHandlerList;
	typedef std::map<TEventType,TEventHandlerList> TEventHandlerMap;

	/// Managers the in-game events using a priority queue that'll be used by all the game objects and/or subsystems
	/// to post an event. Then the queue will be processed and all events will be dispatched to the registered handlers
	class EventManager
	{
	private:
		/// Priority queue to hold the events posted by the game objects or subsystems.
		TEventQueue mEventQueue;
		/// Map containing the registered event handlers. For each type of event there is a list linked to it
		/// so the events may be quickly dispatched only to the instances interested on them.
		/// For instance, say we have two event types: CAUSE_DAMAGE and RECEIVE_DAMAGE
		/// A particular game object wants to call its member function "onCauseDamage" any time he hits something
		/// Then, the map entry for CAUSE_DAMAGE will contain at least one event handler object linking the instance
		/// that will react to the event and the callback method (the function onCauseDamage).		
		TEventHandlerMap mEventHandlers;

	public:
		EventManager();
		virtual ~EventManager();
		/// Delete all items from the event queue and
		/// event handlers map
		void clear();
		/// Add an event to the queue
		/// @param evt event to enqueue
		void addEvent(EventPtr evt);
		/// Process all events
		void dispatchEvents();
		/// Get the highest-priority event on the queue
		/// @return highest-priority event on the queue
		EventPtr peekEvent() const;
		/// Remove the highest-priority event from the queue, and
		/// return it.
		/// @return removed event
		EventPtr removeEvent();

		/// Add a new event handler for the given event type
		/// @param handler	functor object containing the instance that will handle the event 
		///					and the callback method it'll invoke
		/// @param evtType  type of the event that will be handled
		void registerHandler(EventHandlerPtr handler,TEventType evtType);


		/// Delete an event handler for the given event type
		/// @param handler  functor object to remove
		/// @param evtType  type of the event
		void unregisterHandler(EventHandlerPtr handler,TEventType evtType);
	};
}
#endif