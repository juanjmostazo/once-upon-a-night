#ifndef GameObjectNonMovableH_H
#define GameObjectNonMovableH_H
#include "GameObjectPositional.h"
namespace OUAN
{
	class GameObjectNonMovable : public GameObjectPositional
	{
		//TODO: Add physics component
	public:
		//Constructor
		GameObjectNonMovable(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectNonMovable();

	};

	class TGameObjectNonMovableParameters : public TGameObjectPositionalParameters
	{
	public:
		TGameObjectNonMovableParameters();
		~TGameObjectNonMovableParameters();

	};
}
#endif