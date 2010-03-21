#ifndef GAMEOBJECTH_H
#define GAMEOBJECTH_H

#include "../../OUAN.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
#include "../../Event/EventManager.h"
#include "../../Event/EventHandler.h"

namespace OUAN
{
	class GameObject{
	private:
		/// GameObject identifier (i.e, "tripollo#14")
		std::string mName;
		/// GameObject identifier (i.e. GameObjectTripollo)
		std::string mType;
	protected:
		///Game world manager
		GameWorldManagerPtr mGameWorldManager;

		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
	public:
		//Constructor
		GameObject(const std::string& name,const std::string& type);
		//Destructor
		~GameObject();

		GameWorldManagerPtr getGameWorldManager();
		void setGameWorldManager(GameWorldManagerPtr gameWorldManager);

		/// Manages Game Object destruction
		/// Each game object must take care about their specific components)
		virtual void destroy();

		/// Return Game Object name (i.e, its identifier)
		/// @return name of the Game Object
		const std::string& getName() const;

		/// Return Game Object type
		/// @return type of the Game Object
		const std::string& getType() const;

		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Update object
		virtual void update(double elapsedSeconds);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		virtual void changeWorld(int world);

		/// Process world change event
		/// @param evt pointer to the event data
		virtual void processChangeWorld(ChangeWorldEventPtr evt);
	};

	class TGameObjectParameters
	{
	public:
		TGameObjectParameters();
		~TGameObjectParameters();

		std::string name;
		std::string dreamsName;
		std::string nightmaresName;

		TLogicComponentParameters logicComponentParameters;
	};
}
#endif