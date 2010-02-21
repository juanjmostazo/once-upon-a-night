#ifndef PhysicsComponentSimpleH_H
#define PhysicsComponentSimpleH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Simple physics elements which interact with other elements
	class PhysicsComponentSimple: public PhysicsComponent
	{
	public:
		PhysicsComponentSimple(const std::string& name="");
		~PhysicsComponentSimple();
	};

	class TPhysicsComponentSimpleParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentSimpleParameters();
		~TPhysicsComponentSimpleParameters();
	};
}

#endif