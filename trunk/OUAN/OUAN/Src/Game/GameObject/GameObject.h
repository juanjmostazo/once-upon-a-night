#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H

#include "../../OUAN.h"
#include "../../Event/EventManager.h"
#include "../../Event/EventHandler.h"
#include "../../Logic/LogicComponent/LogicComponentWorldExistance.h"

namespace OUAN
{
	class GameObject{
	private:
		/// GameObject identifier (i.e, "pc_ony")
		std::string mName;
	protected:
		///Game world manager
		GameWorldManagerPtr mGameWorldManager;

		/// World Existance informacion
		LogicComponentWorldExistancePtr mLogicComponentWorldExistance;
	public:
		//Constructor
		GameObject(const std::string& name);
		//Destructor
		~GameObject();

		GameWorldManagerPtr getGameWorldManager();
		void setGameWorldManager(GameWorldManagerPtr gameWorldManager);

		/// Return entity name (i.e, its "type" identifier)
		/// @return name of the entity
		const std::string& getName() const;

		/// Set WorldExistence component
		void setLogicComponentWorldExistance(LogicComponentWorldExistancePtr pLogicComponentWorldExistance);

		/// Get WorldExistence component
		LogicComponentWorldExistancePtr getLogicComponentWorldExistance();


		/// Update object
		virtual void update(double elapsedSeconds);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		virtual void changeWorld(int world);

		/// Generic method to register an event handler. The way to use it on the subclasses will be something like this
		/// Suppose we want GameObjectOny to process ChangeWorldEvents invoking its member function "void doChangeWorld (ChangeWorldEventPtr evt)".
		/// We'll have to call registerEventHandler like this:
		///
		/// GameObjectOny::registerHandlers()
		/// {
		///		boost::shared_ptr<GameObjectOny> _this= shared_from_this(); // get reference to 'this' pointer
		///		registerEventHandler<GameObjectOny,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectOny::processChangeWorld,mgr);
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
		void unregisterEventHandler(boost::shared_ptr<T> instance,void (T::*callback)(boost::shared_ptr<EventT>),EventManagerPtr evtManager)
		{
			EventHandlerPtr eh = EventHandlerPtr(new EventHandler<T,EventT>(instance,callback));
			evtManager->unregisterHandler(eh,eventType);
		}
		
		/// Attach all event handlers for this object.
		// This method will have to be redefined by all GameObject subclasses to register all the event handlers
		virtual void registerHandlers();

		/// Detach all event handlers
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

		///World Existance Information
		TLogicComponentWorldExistanceParameters tLogicComponentWorldExistanceParameters;

	};
}
#endif