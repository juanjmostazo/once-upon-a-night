#ifndef PhysicsComponentVolumeH_H
#define PhysicsComponentVolumeH_H

#include "PhysicsComponent.h"
namespace OUAN
{
	// Physics volumes
	class PhysicsComponentVolume: public PhysicsComponent
	{
	public:
		PhysicsComponentVolume(const std::string& name="");
		~PhysicsComponentVolume();

		NxOgre::Volume* getNxOgreVolume();
		void setNxOgreVolume(NxOgre::Volume* pNxOgreVolume);

	protected:
		NxOgre::Volume* mNxOgreVolume;
	};

	class TPhysicsComponentVolumeParameters: public TPhysicsComponentParameters
	{
	public:
		TPhysicsComponentVolumeParameters();
		~TPhysicsComponentVolumeParameters();
	};
}

#endif