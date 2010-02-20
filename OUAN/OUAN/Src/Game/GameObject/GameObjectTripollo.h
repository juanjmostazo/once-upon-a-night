#ifndef GameObjectTripolloH_H
#define GameObjectTripolloeH_H
#include "GameObjectMovableEntity.h"
namespace OUAN
{
	class GameObjectTripollo : public GameObjectMovableEntity
	{

	public:
		//Constructor
		GameObjectTripollo(const std::string& name, const std::string& id);
		//Destructor
		~GameObjectTripollo();
	};

	class TGameObjectTripolloParameters: public TGameObjectMovableEntityParameters
	{
	public:
		TGameObjectTripolloParameters();
		~TGameObjectTripolloParameters();

	};

}
#endif