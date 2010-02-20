#ifndef GameObjectMovableH_H
#define GameObjectMovableH_H
#include "GameObjectPositional.h"
namespace OUAN
{
	class GameObjectMovable : public GameObjectPositional
	{
		//TODO: Add physics component

	public:
		//Constructor
		GameObjectMovable(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectMovable();
	};

	class TGameObjectMovableParameters : public TGameObjectPositionalParameters
	{
	public:
		TGameObjectMovableParameters();
		~TGameObjectMovableParameters();
	};

}
#endif