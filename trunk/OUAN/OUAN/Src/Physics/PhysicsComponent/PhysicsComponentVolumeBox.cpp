#include "PhysicsComponentVolumeBox.h"
using namespace OUAN;

PhysicsComponentVolumeBox::PhysicsComponentVolumeBox(const std::string& type)
:PhysicsComponentVolume(COMPONENT_TYPE_PHYSICS_VOLUME_BOX)
{

}

PhysicsComponentVolumeBox::~PhysicsComponentVolumeBox()
{

}

void PhysicsComponentVolumeBox::create()
{
	PhysicsComponentVolume::create();
	
	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			new NxOgre::Box(
				getNxOgreSize().x,
				getNxOgreSize().y,
				getNxOgreSize().z),
			NxOgre::Matrix44(	
				NxOgre::Vec3(getSceneNode()->getPosition()), 
				NxOgre::Quat(getSceneNode()->getOrientation())),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));	
}

void PhysicsComponentVolumeBox::destroy()
{
	PhysicsComponentVolume::destroy();
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