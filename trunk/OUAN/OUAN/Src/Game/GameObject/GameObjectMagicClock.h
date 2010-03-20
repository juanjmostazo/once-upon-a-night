#ifndef GameObjectMagicClockH_H
#define GameObjectMagicClockH_H

#include "GameObject.h"

namespace OUAN
{
	/// Class to hold GameObjectMagicClock information
	class GameObjectMagicClock : public GameObject, public boost::enable_shared_from_this<GameObjectMagicClock>
	{
	private:

		//TODO: think what happens when world changes with the rendercomponent
	public:
		//Constructor
		GameObjectMagicClock(const std::string& name);
		//Destructor
		~GameObjectMagicClock();

	};

	class TGameObjectMagicClockParameters: public TGameObjectParameters
	{
	public:
		TGameObjectMagicClockParameters();
		~TGameObjectMagicClockParameters();
	};
}
#endif