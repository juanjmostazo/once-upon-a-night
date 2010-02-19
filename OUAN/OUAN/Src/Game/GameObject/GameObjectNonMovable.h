#ifndef GameObjectNonMovableH_H
#define GameObjectNonMovableH_H
#include "GameObject.h"
namespace OUAN
{
	class GameObjectNonMovable : public GameObject
	{
		//TODO: Add physics component
	public:
		//Constructor
		GameObjectNonMovable(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectNonMovable();

	};
}
#endif