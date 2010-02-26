#include "PhysicsComponentVolumeCapsule.h"
using namespace OUAN;

PhysicsComponentVolumeCapsule::PhysicsComponentVolumeCapsule(const std::string& type)
:PhysicsComponentVolume(COMPONENT_TYPE_PHYSICS_VOLUME_CAPSULE)
{

}

PhysicsComponentVolumeCapsule::~PhysicsComponentVolumeCapsule()
{

}

NxOgre::Vec2 PhysicsComponentVolumeCapsule::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentVolumeCapsule::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
}

TPhysicsComponentVolumeCapsuleParameters::TPhysicsComponentVolumeCapsuleParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeCapsuleParameters::~TPhysicsComponentVolumeCapsuleParameters()
{

}