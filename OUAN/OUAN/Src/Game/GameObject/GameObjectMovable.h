#ifndef GameObjectMovableH_H
#define GameObjectMovableH_H
#include "GameObject.h"
namespace OUAN
{
	class GameObjectMovable : public GameObject
	{
		//TODO: Add physics component
	public:
		//Constructor
		GameObjectMovable(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectMovable();

	};
}
#endif