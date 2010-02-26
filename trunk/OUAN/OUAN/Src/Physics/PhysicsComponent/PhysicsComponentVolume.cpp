#include "PhysicsComponentVolume.h"
using namespace OUAN;

PhysicsComponentVolume::PhysicsComponentVolume(const std::string& type)
:PhysicsComponent(COMPONENT_TYPE_PHYSICS_VOLUME)
{

}

PhysicsComponentVolume::~PhysicsComponentVolume()
{

}

NxOgre::Volume* PhysicsComponentVolume::getNxOgreVolume()
{
	return mNxOgreVolume;
}

void PhysicsComponentVolume::setNxOgreVolume(NxOgre::Volume* pNxOgreVolume)
{
	mNxOgreVolume=pNxOgreVolume;
}

TPhysicsComponentVolumeParameters::TPhysicsComponentVolumeParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentVolumeParameters::~TPhysicsComponentVolumeParameters()
{

}