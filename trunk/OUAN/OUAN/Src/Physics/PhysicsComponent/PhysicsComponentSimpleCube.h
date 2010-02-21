#ifndef PhysicsComponentSimpleCubeH_H
#define PhysicsComponentSimpleCubeH_H

#include "PhysicsComponentSimple.h"
namespace OUAN
{
	// Simple physics elements whose shape is a cube
	// Example: Boxes, etc.
	class PhysicsComponentSimpleCube: public PhysicsComponentSimple
	{
	public:
		PhysicsComponentSimpleCube(const std::string& name="");
		~PhysicsComponentSimpleCube();
	};

	class TPhysicsComponentSimpleCubeParameters: public TPhysicsComponentSimpleParameters
	{
	public:
		TPhysicsComponentSimpleCubeParameters();
		~TPhysicsComponentSimpleCubeParameters();
		
		float lengthX;
		float lengthY;
		float lengthZ;
	};
}

#endif