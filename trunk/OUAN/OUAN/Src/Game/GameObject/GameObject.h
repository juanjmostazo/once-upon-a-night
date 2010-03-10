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

		///World Existance Information
		TLogicComponentWorldExistanceParameters tLogicComponentWorldExistanceParameters;

	};
}
#endif