#ifndef PhysicsComponentSimpleBoxH_H
#define PhysicsComponentSimpleBoxH_H

#include "PhysicsComponentSimple.h"
namespace OUAN
{
	// Simple physics elements whose shape is a cube
	// Example: Boxes, etc.
	class PhysicsComponentSimpleBox: public PhysicsComponentSimple
	{
	public:
		PhysicsComponentSimpleBox(const std::string& type="");
		~PhysicsComponentSimpleBox();

		NxOgre::Vec3 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec3 pNxOgreSize);

	protected:
		NxOgre::Vec3 mNxOgreSize;
	};

	class TPhysicsComponentSimpleBoxParameters: public TPhysicsComponentSimpleParameters
	{
	public:
		TPhysicsComponentSimpleBoxParameters();
		~TPhysicsComponentSimpleBoxParameters();
		
		double lengthX;
		double lengthY;
		double lengthZ;
	};
}

#endif