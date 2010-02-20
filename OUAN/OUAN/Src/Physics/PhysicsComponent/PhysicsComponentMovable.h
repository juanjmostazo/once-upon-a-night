#ifndef PhysicsComponentMovableH_H
#define PhysicsComponentMovableH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Examples: boxes, barrels... elements which interacts with the entities
	class PhysicsComponentMovable: public PhysicsComponent
	{
	public:
		PhysicsComponentMovable(const std::string& name="");
		~PhysicsComponentMovable();
	};

	class TPhysicsComponentMovableParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentMovableParameters();
		~TPhysicsComponentMovableParameters();

		float mass;
	};
}

#endif