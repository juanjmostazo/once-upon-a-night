#ifndef EVENTPRIORITIESH_H
#define EVENTPRIORITIESH_H
#include <boost/shared_ptr.hpp>

namespace OUAN
{
	// Event manager-related constants, typedefs and forwarded declarations
	class Event;
	typedef boost::shared_ptr<Event> EventPtr;

	class BaseEventHandler;
	typedef boost::shared_ptr<BaseEventHandler> EventHandlerPtr;

	class EventManager;
	typedef boost::shared_ptr<EventManager> EventManagerPtr;

	class EventProcessor;
	typedef boost::shared_ptr<EventProcessor> EventProcessorPtr;

	class ChangeWorldEvent;
	typedef boost::shared_ptr<ChangeWorldEvent> ChangeWorldEventPtr;

	class CollisionEvent;
	typedef boost::shared_ptr<CollisionEvent> CollisionEventPtr;

	class EnterTriggerEvent;
	typedef boost::shared_ptr<EnterTriggerEvent> EnterTriggerEventPtr;

	class ExitTriggerEvent;
	typedef boost::shared_ptr<ExitTriggerEvent> ExitTriggerEventPtr;

	class ClearQueueEvent;
	typedef boost::shared_ptr<ClearQueueEvent> ClearQueueEventPtr;

	class GameOverEvent;
	typedef boost::shared_ptr<GameOverEvent> GameOverEventPtr;

	class OnyDiesEvent;
	typedef boost::shared_ptr<OnyDiesEvent> OnyDiesEventPtr;

	class OnyFallsEvent;
	typedef boost::shared_ptr<OnyFallsEvent> OnyFallsEventPtr;

	class WeaponModeChangedEvent;
	typedef boost::shared_ptr<WeaponModeChangedEvent> WeaponModeChangedEventPtr;

	class AnimationEndedEvent;
	typedef boost::shared_ptr<AnimationEndedEvent> AnimationEndedEventPtr;

	// Event types
	typedef enum{
		EVENT_TYPE_GAMEOVER,	
		EVENT_TYPE_ONY_DEATH,
		EVENT_TYPE_ONY_FALLS,
		EVENT_TYPE_CHANGEWORLD,
		EVENT_TYPE_CLEARQUEUE,
		EVENT_TYPE_ANIMATION_ENDED,
		EVENT_TYPE_CHARACTERS_COLLISION,
		EVENT_TYPE_CHARACTER_IN_TRIGGER,
		EVENT_TYPE_CHARACTER_SHAPE_FRONT_COLLISION,
		EVENT_TYPE_COLLISION,
		EVENT_TYPE_ENTER_TRIGGER,
		EVENT_TYPE_EXIT_TRIGGER,
		EVENT_TYPE_WEAPON_MODE_CHANGED
	} TEventType;


	// Priority values for all event types: 0 is highest
	const int EVT_PRIORITY_GAMEOVER=0;
	const int EVT_PRIORITY_ONY_DEATH=1;	//Ony loses 1 live
	const int EVT_PRIORITY_ONY_FALLS=1;
	const int EVT_PRIORITY_CHANGEWORLD=2;
	const int EVT_PRIORITY_CLEARQUEUE=2;
	const int EVT_PRIORITY_ANIMATION_ENDED=3;
	const int EVT_PRIORITY_WEAPON_MODE_CHANGED=3;
	const int EVT_PRIORITY_EXIT_TRIGGER=3;
	const int EVT_PRIORITY_ENTER_TRIGGER=4;
	const int EVT_PRIORITY_COLLISION=5;
	//...
}

#endif