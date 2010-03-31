#ifndef EVENTH_H
#define EVENTH_H

#include "../OUAN.h"

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

	private:
		int mNewWorld;
	};

	/// Event class representing a collision between two GameObjects
	/// which both contain a PhysicsComponentCharacter
	class CharactersCollisionEvent: public Event
	{
	public:
		CharactersCollisionEvent(GameObjectPtr pCharacter1, GameObjectPtr pCharacter2);
		GameObjectPtr getCharacter1();
		GameObjectPtr getCharacter2();

	private:
		GameObjectPtr mCharacter1;
		GameObjectPtr mCharacter2;
	};

	/// Event class representing a collision between two GameObjects
	/// which contain a PhysicsComponentCharacter and a PhysicsVolumeXXX
	class CharacterInTriggerEvent: public Event
	{
	public:
		CharacterInTriggerEvent(GameObjectPtr pCharacter, GameObjectPtr pTrigger, int pCollisionType);
		GameObjectPtr getCharacter();
		GameObjectPtr getTrigger();
		int getCollisionType();

	private:
		GameObjectPtr mCharacter;
		GameObjectPtr mTrigger;
		int mCollisionType;
	};

	/// Event class representing a collision between a Character and a Shape
	/// Character (Ony, enemies); Shape (terrain, columns, walls, trees...)
	class CharacterShapeFrontCollisionEvent: public Event
	{
	public:
		CharacterShapeFrontCollisionEvent(GameObjectPtr pCharacter, GameObjectPtr pShape);
		GameObjectPtr getCharacter();
		GameObjectPtr getShape();

	private:
		GameObjectPtr mCharacter;
		GameObjectPtr mShape;
	};

	class ClearQueueEvent: public Event{
	public:
		ClearQueueEvent();
	};

	class GameOverEvent: public Event
	{
	public:
		GameOverEvent(bool win);
		bool isWin() const;
	private:
		bool mWin;
	};
	
	class OnyDiesEvent: public Event
	{
	public:
		OnyDiesEvent(int remainingLives);
		int getRemainingLives() const;
	private:
		int mRemainingLives;
	};

}
#endif