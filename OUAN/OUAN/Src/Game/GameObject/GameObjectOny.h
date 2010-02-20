#ifndef GameObjectOnyH_H
#define GameObjectOnyeH_H
#include "GameObjectMovableEntity.h"
namespace OUAN
{
	class GameObjectOny : public GameObjectMovableEntity
	{

	public:
		//Constructor
		GameObjectOny(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectOny();
	};

	class TGameObjectOnyParameters: public TGameObjectMovableEntityParameters
	{
	public:
		TGameObjectOnyParameters();
		~TGameObjectOnyParameters();

	};

}
#endif