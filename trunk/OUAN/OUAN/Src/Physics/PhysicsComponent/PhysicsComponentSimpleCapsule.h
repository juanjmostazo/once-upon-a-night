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
		PhysicsComponentSimpleCapsule(const std::string& type="");
		~PhysicsComponentSimpleCapsule();

		virtual void create();
		virtual void destroy();

		NxOgre::Vec2 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);

		//void setQueryFlags(QueryFlags queryFlags);
		void setPosition(NxOgre::Vec3 position);
		void setOrientation(NxOgre::Quat orientation);


	protected:
		NxOgre::Vec2 mNxOgreSize;
		QueryFlags mQueryFlags;

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