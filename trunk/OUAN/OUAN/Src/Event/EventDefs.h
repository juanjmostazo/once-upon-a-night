#ifndef EVENTPRIORITIESH_H
#define EVENTPRIORITIESH_H
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

	class OnyTakesHitEvent;
	typedef boost::shared_ptr<OnyTakesHitEvent> OnyTakesHitEventPtr;

	class WeaponModeChangedEvent;
	typedef boost::shared_ptr<WeaponModeChangedEvent> WeaponModeChangedEventPtr;

	class AnimationEndedEvent;
	typedef boost::shared_ptr<AnimationEndedEvent> AnimationEndedEventPtr;

	class AnimationStartedEvent;
	typedef boost::shared_ptr<AnimationStartedEvent> AnimationStartedEventPtr;

	class ActivatedItemEvent;
	typedef boost::shared_ptr<ActivatedItemEvent> ActivatedItemEventPtr;

	class AttackEndedEvent;
	typedef boost::shared_ptr<AttackEndedEvent> AttackEndedEventPtr;

	class CameraTriggerEvent;
	typedef boost::shared_ptr<CameraTriggerEvent> CameraTriggerEventPtr;

	class ChangeLevelEvent;
	typedef boost::shared_ptr<ChangeLevelEvent> ChangeLevelEventPtr;

	class LevelEvent;
	typedef boost::shared_ptr<LevelEvent> LevelEventPtr;

	CLASS_DECLARATIONS_NO_PARAMS(MsgBoxVisibilityChangedEvent);
	CLASS_DECLARATIONS_NO_PARAMS(FirstSignpostHitEvent);
	CLASS_DECLARATIONS_NO_PARAMS(StorybookPartPickedEvent);

	// Event types
	typedef enum{
		EVENT_TYPE_GAMEOVER,	
		EVENT_TYPE_ONY_DEATH,
		EVENT_TYPE_ONY_FALLS,
		EVENT_TYPE_CHANGEWORLD,
		EVENT_TYPE_CLEARQUEUE,
		EVENT_TYPE_ANIMATION_STARTED,
		EVENT_TYPE_ANIMATION_ENDED,
		EVENT_TYPE_ACTIVATED_ITEM,
		EVENT_TYPE_CHARACTERS_COLLISION,
		EVENT_TYPE_CHARACTER_IN_TRIGGER,
		EVENT_TYPE_CHARACTER_SHAPE_FRONT_COLLISION,
		EVENT_TYPE_COLLISION,
		EVENT_TYPE_ENTER_TRIGGER,
		EVENT_TYPE_EXIT_TRIGGER,
		EVENT_TYPE_ONY_TAKES_HIT,
		EVENT_TYPE_WEAPON_MODE_CHANGED,
		EVENT_TYPE_CAMERA_TRIGGER_PARAMETERS,
		EVENT_TYPE_ATTACK_ENDED,
		EVENT_TYPE_CHANGE_LEVEL,
		EVENT_TYPE_LEVEL,
		EVENT_TYPE_MSGBOX_VISIBILITY_CHANGED,
		EVENT_TYPE_FIRST_SIGNPOST_HIT,
		EVENT_TYPE_STORYBOOK_PART_PICKED
	} TEventType;


	// Priority values for all event types: 0 is highest
	const int EVT_PRIORITY_GAMEOVER=0;
	const int EVT_PRIORITY_ONY_DEATH=1;	//Ony loses 1 life
	const int EVT_PRIORITY_ONY_FALLS=1;
	const int EVT_PRIORITY_STORYBOOK_PART_PICKED=2;
	const int EVT_PRIORITY_CHANGEWORLD=2;
	const int EVT_PRIORITY_CLEARQUEUE=2;
	const int EVT_PRIORITY_ANIMATION_STARTED=3;
	const int EVT_PRIORITY_ANIMATION_ENDED=3;
	const int EVT_PRIORITY_WEAPON_MODE_CHANGED=3;	
	const int EVT_PRIORITY_ATTACK_ENDED=3;
	const int EVT_PRIORITY_EXIT_TRIGGER=3;
	const int EVT_PRIORITY_ENTER_TRIGGER=4;
	const int EVT_PRIORITY_ACTIVATED_ITEM=4;
	const int EVT_PRIORITY_ONY_TAKES_HIT=4;
	const int EVT_PRIORITY_COLLISION=5;
	const int EVT_PRIORITY_CAMERA_TRIGGER=5;
	const int EVT_PRIORITY_CHANGE_LEVEL=5;
	const int EVT_PRIORITY_LEVEL=5;
	const int EVT_PRIORITY_MSGBOX_VISIBILITY_CHANGED=6;
	const int EVT_PRIORITY_FIRST_SIGNPOST_HIT=6;

	//...
}

#endif