#include "PhysicsComponentVolumeCapsule.h"
using namespace OUAN;

PhysicsComponentVolumeCapsule::PhysicsComponentVolumeCapsule(const std::string& type)
:PhysicsComponentVolume(type)
{

}

PhysicsComponentVolumeCapsule::~PhysicsComponentVolumeCapsule()
{

}

void PhysicsComponentVolumeCapsule::create()
{
	PhysicsComponentVolume::create();

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			new NxOgre::Capsule(
				getNxOgreSize().x,
				getNxOgreSize().y),
			NxOgre::Matrix44(	
				NxOgre::Vec3(getSceneNode()->getPosition()), 
				NxOgre::Quat(getSceneNode()->getOrientation())),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));	
}

void PhysicsComponentVolumeCapsule::destroy()
{
	PhysicsComponentVolume::destroy();
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