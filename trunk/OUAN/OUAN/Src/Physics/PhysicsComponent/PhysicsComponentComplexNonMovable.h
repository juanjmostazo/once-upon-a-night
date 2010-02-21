#ifndef PhysicsComponentComplexNonMovableH_H
#define PhysicsComponentComplexNonMovableH_H

#include "PhysicsComponentComplex.h"
namespace OUAN
{
	class PhysicsComponentComplexNonMovable: public PhysicsComponentComplex
	{
	public:
		PhysicsComponentComplexNonMovable(const std::string& name="");
		~PhysicsComponentComplexNonMovable();
	};

	class TPhysicsComponentComplexNonMovableParameters: public TPhysicsComponentComplexParameters
	{
	public:
		TPhysicsComponentComplexNonMovableParameters();
		~TPhysicsComponentComplexNonMovableParameters();

		int radius;
		int height;
	};
}

#endif