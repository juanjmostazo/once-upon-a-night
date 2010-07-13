#ifndef EVENTPROCESSORH_H
#define EVENTPROCESSORH_H

#include "../OUAN.h"
#include "../Event/Event.h"

namespace OUAN
{
	/// Process game events in two stages: first, it
	/// resolves local-scope events, dispatching them to
	/// the interested game objects; secondly, 
	class EventProcessor: public boost::enable_shared_from_this<EventProcessor>
	{
	public:
		EventProcessor();
		/// Initialise processor
		/// @param worldManager	the world manager
		void init(GameWorldManagerPtr worldManager);
		/// Free resources if necessary
		void cleanUp();		
		
		/// Process world change event
		/// @param evt pointer to the event
		void processChangeWorld(ChangeWorldEventPtr evt);

		/// Process collision event
		/// @param evt pointer to the event
		void processCollision(CollisionEventPtr evt);

		/// Process enter trigger event
		/// @param evt pointer to the event
		void processEnterTrigger(EnterTriggerEventPtr evt);

		/// Process exit trigger event
		/// @param evt pointer to the event
		void processExitTrigger(ExitTriggerEventPtr evt);

		/// Process game over event
		/// @param evt pointer to the event
		void processGameOver(GameOverEventPtr evt);

		/// Process clear queue event (likely to be removed)
		void processClearQueue(ClearQueueEventPtr evt);

		/// Process ony's death event
		void processOnyDies(OnyDiesEventPtr evt);

		/// Process 'ony falls down a chasm' event
		void processOnyFalls(OnyFallsEventPtr evt);

		/// Process weapon mode (i.e, the flashlight colour or the 
		/// pillow special funtion) change event
		void processWeaponModeChanged(WeaponModeChangedEventPtr evt);

		/// Process the 'animation has ended' event
		void processAnimationEnded(AnimationEndedEventPtr evt);

		/// Process the 'animation has started' event
		void processAnimationStarted(AnimationStartedEventPtr evt);

		/// Process the 'activated item' event
		void processActivatedItem(ActivatedItemEventPtr evt);

		/// Process the 'ony takes hit' event
		void processOnyTakesHit(OnyTakesHitEventPtr evt);

		/// Process the 'ony takes hit' event
		void processAttackEnded(AttackEndedEventPtr evt);

		/// Process the 'change camera parameters' event
		void processCameraTrigger(CameraTriggerEventPtr evt);

		/// Process the 'change level' event
		void processChangeLevel(ChangeLevelEventPtr evt);

	private:
		/// Register all event handling methods
		void registerHandlers();
		/// Detach all event handling methods
		void unregisterHandlers();	

		/// Generic method to register an event handler.
		/// @param instance		the instance that'll invoke the method
		/// @param callback		the member function that will be called by instance when handling the event
		/// @param evtManager	event manager pointer
		template<class T, class EventT,TEventType eventType>
		void registerEventHandler(boost::shared_ptr<T> instance,void (T::*callback)(boost::shared_ptr<EventT>),EventManagerPtr evtManager)
		{
			EventHandlerPtr eh = EventHandlerPtr(new EventHandler<T,EventT>(instance,callback));
			evtManager->registerHandler(eh,eventType);
		}

		/// Generic method to unregister an event handler. It is completely analogous to the register method
		/// @param instance		the instance that'll invoke the method
		/// @param callback		the member function that 'instance' will invoke
		/// @param evtManager	pointer to the event manager
		template<class T, class EventT,TEventType eventType>
		void unregisterEventHandler(boost::shared_ptr<T> instance,void (T::*callback)(boost::shared_ptr<EventT>),EventManagerPtr evtManager)
		{
			EventHandlerPtr eh = EventHandlerPtr(new EventHandler<T,EventT>(instance,callback));
			evtManager->unregisterHandler(eh,eventType);
		}

		/// Pointer to the world Manager: it provides 
		/// indirect access to the game world's objects
		GameWorldManagerPtr mWorldManager;	
	};
}
#endif