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

		NxOgre::Vec2 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);

	protected:
		NxOgre::Vec2 mNxOgreSize;
	};

	class TPhysicsComponentSimpleCapsuleParameters: public TPhysicsComponentSimpleParameters
	{
	public:
		TPhysicsComponentSimpleCapsuleParameters();
		~TPhysicsComponentSimpleCapsuleParameters();

		double radius;
		double height;
	};
}

#endif