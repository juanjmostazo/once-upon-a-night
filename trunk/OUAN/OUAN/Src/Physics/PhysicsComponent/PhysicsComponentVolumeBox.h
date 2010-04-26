#ifndef PhysicsComponentVolumeBoxH_H
#define PhysicsComponentVolumeBoxH_H

#include "PhysicsComponentVolume.h"
namespace OUAN
{
	// Physics volumes having the shape of a box
	class PhysicsComponentVolumeBox: public PhysicsComponentVolume
	{
	public:
		PhysicsComponentVolumeBox(const std::string& type="");
		~PhysicsComponentVolumeBox();

		virtual void create();
		virtual void destroy();

		NxOgre::Vec3 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec3 pNxOgreSize);

		void PhysicsComponentVolumeBox::setPosition(NxOgre::Vec3 position);
		void PhysicsComponentVolumeBox::setOrientation(NxOgre::Quat orientation);

		//void setQueryFlags(QueryFlags queryFlags);

	protected:
		NxOgre::Vec3 mNxOgreSize;

	};

	class TPhysicsComponentVolumeBoxParameters: public TPhysicsComponentVolumeParameters
	{
	public:
		TPhysicsComponentVolumeBoxParameters();
		~TPhysicsComponentVolumeBoxParameters();

		double lengthX;
		double lengthY;
		double lengthZ;
	};
}

#endif