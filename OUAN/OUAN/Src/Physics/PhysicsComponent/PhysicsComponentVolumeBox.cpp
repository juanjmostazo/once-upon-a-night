#include "PhysicsComponentVolumeBox.h"
using namespace OUAN;

PhysicsComponentVolumeBox::PhysicsComponentVolumeBox(const std::string& name)
:PhysicsComponentVolume(COMPONENT_NAME_PHYSICS_VOLUME_BOX)
{

}

PhysicsComponentVolumeBox::~PhysicsComponentVolumeBox()
{

}

NxOgre::Vec3 PhysicsComponentVolumeBox::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentVolumeBox::setNxOgreSize(NxOgre::Vec3 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
}

TPhysicsComponentVolumeBoxParameters::TPhysicsComponentVolumeBoxParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeBoxParameters::~TPhysicsComponentVolumeBoxParameters()
{

}