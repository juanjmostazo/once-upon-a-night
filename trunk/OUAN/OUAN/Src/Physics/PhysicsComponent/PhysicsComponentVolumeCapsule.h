#ifndef PhysicsComponentVolumeCapsuleH_H
#define PhysicsComponentVolumeCapsuleH_H

#include "PhysicsComponentVolume.h"
namespace OUAN
{
	// Physics volumes having the shape of a capsule
	class PhysicsComponentVolumeCapsule: public PhysicsComponentVolume
	{
	public:
		PhysicsComponentVolumeCapsule(const std::string& type="");
		~PhysicsComponentVolumeCapsule();

		virtual void create();
		virtual void destroy();

		NxOgre::Vec2 getNxOgreSize();
		void setNxOgreSize(NxOgre::Vec2 pNxOgreSize);

		//void setQueryFlags(QueryFlags queryFlags);

	protected:
		NxOgre::Vec2 mNxOgreSize;
	};

	class TPhysicsComponentVolumeCapsuleParameters: public TPhysicsComponentVolumeParameters
	{
	public:
		TPhysicsComponentVolumeCapsuleParameters();
		~TPhysicsComponentVolumeCapsuleParameters();

		double radius;
		double height;
	};
}

#endif