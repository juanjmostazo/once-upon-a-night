#ifndef PhysicsComponentComplexConvexH_H
#define PhysicsComponentComplexConvexH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	// Complex elements which can be moved, shape will be Convex
	// Examples: Diamods, weapons, etc.
	class PhysicsComponentComplexConvex: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexConvex(const std::string& name="");
		~PhysicsComponentComplexConvex();
	};

	class TPhysicsComponentComplexConvexParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexConvexParameters();
		~TPhysicsComponentComplexConvexParameters();
	};
}

#endif