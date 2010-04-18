#ifndef GameObjectMagicClockH_H
#define GameObjectMagicClockH_H

#include "GameObject.h"
#include "../../Logic/LogicComponent/LogicComponent.h"
namespace OUAN
{
	/// Class to hold GameObjectMagicClock information
	class GameObjectMagicClock : public GameObject, public boost::enable_shared_from_this<GameObjectMagicClock>
	{
	private:
		/// Logic component: it'll represent the 'brains' of the game object
		/// containing information on its current state, its life and health(if applicable),
		/// or the world(s) the object belongs to
		LogicComponentPtr mLogicComponent;
		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectMagicClock(const std::string& name);
		//Destructor
		~GameObjectMagicClock();
		/// Set logic component
		void setLogicComponent(LogicComponentPtr logicComponent);

		/// return logic component
		LogicComponentPtr getLogicComponent();

		/// Process collision event
		/// @param gameObject which has collision with
		void processCollision(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processEnterTrigger(GameObjectPtr pGameObject);

		/// Process collision event
		/// @param gameObject which has collision with
		void processExitTrigger(GameObjectPtr pGameObject);

		// update logic component
		void updateLogic(double elapsedSeconds);

	};

	class TGameObjectMagicClockParameters: public TGameObjectParameters
	{
	public:
		TGameObjectMagicClockParameters();
		~TGameObjectMagicClockParameters();

		///Logic parameters
		TLogicComponentParameters tLogicComponentParameters;
	};
}
#endif