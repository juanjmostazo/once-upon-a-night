#ifndef PhysicsComponentSimpleCubeH_H
#define PhysicsComponentSimpleCubeH_H

#include "PhysicsComponentSimple.h"
namespace OUAN
{
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

		int radius;
		int height;
	};
}

#endif