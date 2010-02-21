#ifndef PhysicsComponentComplexMovableH_H
#define PhysicsComponentComplexMovableH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
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

		int radius;
		int height;
	};
}

#endif