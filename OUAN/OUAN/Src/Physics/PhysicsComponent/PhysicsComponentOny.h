#ifndef PhysicsComponentOnyH_H
#define PhysicsComponentOnyH_H

#include "PhysicsComponentMovableEntity.h"
namespace OUAN
{
	class PhysicsComponentOny: public PhysicsComponentMovableEntity
	{
	public:
		PhysicsComponentOny(const std::string& name="");
		~PhysicsComponentOny();
	};

	class TPhysicsComponentOnyParameters: public TPhysicsComponentMovableEntityParameters
	{
	public:
		TPhysicsComponentOnyParameters();
		~TPhysicsComponentOnyParameters();
	};
}

#endif