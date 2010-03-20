#include "PhysicsComponentVolume.h"
using namespace OUAN;

PhysicsComponentVolume::PhysicsComponentVolume(const std::string& type)
:PhysicsComponent(type)
{

}

PhysicsComponentVolume::~PhysicsComponentVolume()
{
	
}

void PhysicsComponentVolume::create()
{
	PhysicsComponent::create();
}

void PhysicsComponentVolume::destroy()
{
	PhysicsComponent::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->destroyVolume(getNxOgreVolume());
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