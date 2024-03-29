#ifndef EVENTH_H
#define EVENTH_H

#include "../OUAN.h"
#include "EventDefs.h"

namespace OUAN
{
	/// Class to model every in-game event.
	class Event
	{
	private:
		/// Event priority, used to order the event queue:
		/// the lower the value, the higher the priority will be.
		int mPriority;
		/// Event type
		TEventType mEventType;
	public:
		///
		Event(int priority,TEventType eventType);
		virtual ~Event(){}

		/// Return the event priority
		/// @return event priority
		int getPriority() const;

		/// Return the event type
		/// @return Event type
		TEventType getEventType() const;
	};
	//------------------------------------
	/// Functor class used to compare two event pointers
	class EventComparator
	{
	public:
		/// Compare two events checking their priorities:
		/// The event with the lower value will have higher priority
		bool operator()(EventPtr& evt1, EventPtr& evt2);
	};

	//------------------------------------
	
	/// Event class representing a world change.
	/// At the moment, it serves as a sample of what an event would look like:
	/// A data container, holding only the essential information required
	/// so that an event handler can process it.
	class ChangeWorldEvent: public Event
	{
	public:
		ChangeWorldEvent(int mNewWorld);
		int getNewWorld() const;
		bool fast;
		double time;
		double change_world_elapsed_time;
		bool random_trees;

	private:
		int mNewWorld;
	};
	//------------------------------------

	/// Event class representing a collision between two GameObjects
	class CollisionEvent: public Event
	{
	public:
		CollisionEvent(GameObjectPtr pGameObject1, GameObjectPtr pGameObject2, Ogre::Vector3 pNormal);
		GameObjectPtr getGameObject1();
		GameObjectPtr getGameObject2();
		Ogre::Vector3 getNormal();

	private:
		GameObjectPtr mGameObject1;
		GameObjectPtr mGameObject2;
		Ogre::Vector3 mNormal;
	};

	//------------------------------------

	/// Event class representing a game Object enters a trigger zone
	class EnterTriggerEvent: public Event
	{
	public:
		EnterTriggerEvent(GameObjectPtr pTrigger, GameObjectPtr pGameObject);
		GameObjectPtr getTrigger();
		GameObjectPtr getGameObject();

	private:
		GameObjectPtr mTrigger;
		GameObjectPtr mGameObject;
	};

	//------------------------------------

	/// Event class representing a game Object exits a trigger zone
	class ExitTriggerEvent: public Event
	{
	public:
		ExitTriggerEvent(GameObjectPtr pTrigger, GameObjectPtr pGameObject);
		GameObjectPtr getTrigger();
		GameObjectPtr getGameObject();

	private:
		GameObjectPtr mTrigger;
		GameObjectPtr mGameObject;
	};

	//------------------------------------

	class ClearQueueEvent: public Event{
	public:
		ClearQueueEvent();
	};

	//------------------------------------

	class GameOverEvent: public Event
	{
	public:
		GameOverEvent(bool win);
		bool isWin() const;
	private:
		bool mWin;
	};
	
	//------------------------------------
	
	class OnyDiesEvent: public Event
	{
	public:
		OnyDiesEvent(int remainingLives,bool onyFellDown=false);
		int getRemainingLives() const;
		bool onyFellDown() const;
	private:
		int mRemainingLives;
		bool mOnyFellDown;
	};

	//------------------------------------

	class OnyFallsEvent: public Event
	{
	public:
		OnyFallsEvent();
	};

	//------------------------------------

	class WeaponModeChangedEvent: public Event
	{
		public: 
			WeaponModeChangedEvent(TWeaponMode newWeaponMode);
			TWeaponMode getNewWeaponMode() const;
		private:
			TWeaponMode mNewWeaponMode;
	};

	class AnimationEndedEvent: public Event
	{
	public: 
		AnimationEndedEvent(GameObjectPtr mActor, const std::string animationName);
		GameObjectPtr getActor() const;
		std::string getAnimationName() const;
	private:
		GameObjectPtr mActor;
		std::string mAnimationName;
	};

	class AnimationStartedEvent: public Event
	{
	public: 
		AnimationStartedEvent(GameObjectPtr actor, const std::string animationName);
		GameObjectPtr getActor() const;
		std::string getAnimationName() const;
	private:
		GameObjectPtr mActor;
		std::string mAnimationName;
	};

	class ActivatedItemEvent: public Event
	{
	public:
		ActivatedItemEvent(GameObjectPtr actor);
		GameObjectPtr getActor() const;
	private:
		GameObjectPtr mActor;
	};

	class OnyTakesHitEvent: public Event{
	public:
		OnyTakesHitEvent();
	//remaining info?
	};

	class AttackEndedEvent: public Event
	{
	public:
		AttackEndedEvent(const std::string& attackName, GameObjectPtr attackingObject);
		GameObjectPtr getAttackingObject() const;
		const std::string& getAttackName() const;
	private:
		std::string mAttackName;
		GameObjectPtr mAttackingObject;
	};

	class CameraTriggerEvent: public Event
	{
	public:
		CameraTriggerEvent();
		CameraTriggerPtr pCameraTrigger;
		std::string name;
		bool enter;
	};

	class ChangeLevelEvent: public Event
	{
	public:
		ChangeLevelEvent();
		std::string level;
	};

	class MsgBoxVisibilityChangedEvent: public Event
	{
	public:
		MsgBoxVisibilityChangedEvent(bool visible);
		bool mVisible;
	};

	class FirstSignpostHitEvent: public Event
	{
	public:
		FirstSignpostHitEvent();

	};

	class LevelEvent: public Event
	{
	public:
		LevelEvent();
		std::string level_event_name;
	};

	class StorybookPartPickedEvent: public Event
	{
	public:
		StorybookPartPickedEvent(int currentParts, int totalParts);
		int currentPickedParts;
		int totalPickedParts;
	};

}
#endif