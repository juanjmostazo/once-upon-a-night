#ifndef PhysicsComponentComplexH_H
#define PhysicsComponentComplexH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Complex physics elements, geometry is specified in a nxs file
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

		// Name of the physics nxs file related to the given object mesh
		std::string nxsFile;
	};
}

#endif