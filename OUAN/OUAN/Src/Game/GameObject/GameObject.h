#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H

#include "../../OUAN.h"
#include "../../Event/EventHandler.h"

namespace OUAN
{
	class GameObject{
	private:
		/// GameObject identifier (i.e, "pc_ony")
		std::string mName;
	public:
		//Constructor
		GameObject(const std::string& name);
		//Destructor
		~GameObject();

		/// Return entity name (i.e, its "type" identifier)
		/// @return name of the entity
		const std::string& getName() const;

		/// Update object
		virtual void update(double elapsedSeconds);

		// Sets the GameObject to Dreams
		virtual void setDreamsMode();
		// Sets the GameObject to Nightmares
		virtual void setNightmaresMode();

		/// Generic method to register an event handler. The way to use it on the subclasses will be something like this
		/// Suppose we want GameObjectOny to process ChangeWorldEvents invoking its member function "void doChangeWorld (ChangeWorldEventPtr evt)".
		/// We'll have to call registerEventHandler like this:
		///
		/// GameObjectOny::registerHandlers()
		/// {
		///		boost::shared_ptr<GameObjectOny> _this= shared_from_this(); // get reference to 'this' pointer
		///		registerEventHandler<GameObjectOny,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectOny::doChangeWorld,mgr);
		///		//...remaining events...
		/// }
		/// 
		/// @param instance		the instance that'll invoke the method
		/// @param callback		the member function that will be called by instance when handling the event
		/// @param evtManager	event manager pointer
		template<class T, class EventT,TEventType eventType>
		void registerEventHandler(boost::shared_ptr<T> instance,void (T::*callback)(boost::shared_ptr<EventT>),EventManagerPtr evtManager)
		{
			EventHandlerPtr eh = EventHandlerPtr(new EventHandler<T,EventT>(instance,callback));
			evtManager->registerHandler(eh,eventType);
		}


		/// Generic method to unregister an event handler. The way to use it on the subclasses will be exactly as mentioned in registerEventHandler
		/// but calling this method instead.
		template<class T, class EventT,TEventType eventType>
		void unregisterEventHandler(boost::shared_ptr<T> instance,void (T::*callback)(boost::shared_ptr<EventT>),EventManager& evtManager)
		{
			EventHandlerPtr eh = EventHandlerPtr(new EventHandler<T,EventT>(instance,callback));
			evtManager->unregisterHandler(eh,eventType);
		}
		
		/// Initialise all event handlers.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		virtual void registerHandlers();

		/// Uninitialise all event handlers
		virtual void unregisterHandlers();

	};

	class TGameObjectParameters
	{
	public:
		TGameObjectParameters();
		~TGameObjectParameters();

		std::string name;
		std::string dreamsName;
		std::string nightmaresName;
	};
}
#endif