#ifndef PhysicsComponentComplexMovableH_H
#define PhysicsComponentComplexMovableH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	// Complex elements which can be moved, shape will be Convex
	// Examples: Diamods, weapons, etc.
	class PhysicsComponentComplexMovable: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexMovable(const std::string& name="");
		~PhysicsComponentComplexMovable();
	};

	class TPhysicsComponentComplexMovableParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexMovableParameters();
		~TPhysicsComponentComplexMovableParameters();
	};
}

#endif