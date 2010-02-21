#ifndef PhysicsComponentComplexH_H
#define PhysicsComponentComplexH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Examples: boxes, barrels... elements which interacts with the entities
	class PhysicsComponentComplex: public PhysicsComponent
	{
	public:
		PhysicsComponentComplex(const std::string& name="");
		~PhysicsComponentComplex();
	};

	class TPhysicsComponentComplexParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentComplexParameters();
		~TPhysicsComponentComplexParameters();

		std::string nxsFile;
	};
}

#endif