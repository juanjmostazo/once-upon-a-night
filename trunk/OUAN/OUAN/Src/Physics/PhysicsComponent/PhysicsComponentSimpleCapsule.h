#ifndef PhysicsComponentSimpleCapsuleH_H
#define PhysicsComponentSimpleCapsuleH_H

#include "PhysicsComponentSimple.h"
namespace OUAN
{
	// Simple physics elements whose shape is a capsule
	// Example: Barrels, trees?, etc.
	class PhysicsComponentSimpleCapsule: public PhysicsComponentSimple
	{
	public:
		PhysicsComponentSimpleCapsule(const std::string& name="");
		~PhysicsComponentSimpleCapsule();
	};

	class TPhysicsComponentSimpleCapsuleParameters: public TPhysicsComponentSimpleParameters
	{
	public:
		TPhysicsComponentSimpleCapsuleParameters();
		~TPhysicsComponentSimpleCapsuleParameters();

		float radius;
		float height;
	};
}

#endif