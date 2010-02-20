#ifndef PhysicsComponentNonMovableH_H
#define PhysicsComponentNonMovableH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	//Examples: Terrains, platforms, walls...
	class PhysicsComponentNonMovable: public PhysicsComponent
	{
	public:
		PhysicsComponentNonMovable(const std::string& name="");
		~PhysicsComponentNonMovable();
	};

	class TPhysicsComponentNonMovableParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentNonMovableParameters();
		~TPhysicsComponentNonMovableParameters();
	};
}

#endif