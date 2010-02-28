#ifndef EVENTH_H
#define EVENTH_H
#include "../OUAN.h"
namespace OUAN
{
	class Event
	{
	private:
		int mPriority;
		int mEventType; //Replace with enum
	public:
		Event(int priority,int eventType);
		int getPriority() const;
		int getEventType() const;
	};
	class EventComparator
	{
	public:
		bool operator()(EventPtr& evt1, EventPtr& evt2);
	};
}
#endif