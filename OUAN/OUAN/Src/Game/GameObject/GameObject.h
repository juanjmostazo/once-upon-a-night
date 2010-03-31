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
		/// GameObject attribute 
		bool mEnabled;

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

		static GameObjectPtr Null;

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

		virtual void updateLogic(double elapsedSeconds);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		virtual void changeWorld(int world);

		/// Process world change event
		/// @param evt pointer to the event data
		virtual void processChangeWorld(ChangeWorldEventPtr evt);

		/// Disable the object
		void disable();

		/// Check if the object is enabled
		bool isEnabled();

		/// If applicable, increase the object's health points
		/// @param amount number of HP to increase
		virtual void increaseHP(int amount=1);
		/// If applicable, decrease the object's health points
		/// @param amount number of HP to decrease
		virtual void decreaseHP(int amount=1);
		
		/// If applicable, increase the object's number of lives
		/// @param amount of lives to increase
		virtual void increaseLives(int amount=1);
		/// If applicable, decrease the object's number of lives
		/// @param amount of lives to decrease
		virtual void decreaseLives(int amount=1);

		/// Additional actions to take after losing one life
		virtual void loseLife();

		/// Additional actions to take after losing all lives
		virtual void die();

		virtual bool hasPositionalComponent() const;
		virtual RenderComponentPositionalPtr getPositionalComponent() const;

		//QUERY METHODS (Used by LUA scripts)

		/// Return number of lives (in practice, all enemies will have only 1 life, so it won't be used)
		int getNumLives() const;

		/// Return health points
		int getHealthPoints() const;

		/// Return base/maximum health points
		int getMaximumHealthPoints() const;

		/// Return sight distance
		int getLineOfSight() const;

		/// Compute distance from this object to the passed one
		double computeDistanceTo(GameObjectPtr other) const;
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