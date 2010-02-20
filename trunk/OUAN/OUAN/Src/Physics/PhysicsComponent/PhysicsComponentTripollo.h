#ifndef PhysicsComponentTripolloH_H
#define PhysicsComponentTripolloH_H

#include "PhysicsComponentMovableEntity.h"
namespace OUAN
{
	class PhysicsComponentTripollo: public PhysicsComponentMovableEntity
	{
	public:
		PhysicsComponentTripollo(const std::string& name="");
		~PhysicsComponentTripollo();
	};

	class TPhysicsComponentTripolloParameters: public TPhysicsComponentMovableEntityParameters
	{
	public:
		TPhysicsComponentTripolloParameters();
		~TPhysicsComponentTripolloParameters();
	};
}

#endif