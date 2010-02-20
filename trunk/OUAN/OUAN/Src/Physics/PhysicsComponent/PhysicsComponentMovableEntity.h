#ifndef PhysicsComponentMovableEntityH_H
#define PhysicsComponentMovableEntityH_H

#include "PhysicsComponentMovable.h"
namespace OUAN
{
	class PhysicsComponentMovableEntity: public PhysicsComponentMovable
	{
	public:
		PhysicsComponentMovableEntity(const std::string& name="");
		~PhysicsComponentMovableEntity();
	};

	class TPhysicsComponentMovableEntityParameters: public TPhysicsComponentMovableParameters
	{
	public:
		TPhysicsComponentMovableEntityParameters();
		~TPhysicsComponentMovableEntityParameters();
	};
}

#endif