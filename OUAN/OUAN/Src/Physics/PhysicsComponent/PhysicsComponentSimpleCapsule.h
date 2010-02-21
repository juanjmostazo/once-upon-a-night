#ifndef PhysicsComponentSimpleCapsuleH_H
#define PhysicsComponentSimpleCapsuleH_H

#include "PhysicsComponentSimple.h"
namespace OUAN
{
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

		int x;
		int y;
		int z;
	};
}

#endif