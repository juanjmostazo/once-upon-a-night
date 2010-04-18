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

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	
	NxOgre::Capsule* pCapsule = 
		new NxOgre::Capsule(getNxOgreSize().x,
							getNxOgreSize().y);

	pCapsule->setName(name);

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			pCapsule,
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

//void PhysicsComponentVolumeCapsule::setQueryFlags(QueryFlags queryFlags)
//{
//	//getNxOgreBody()->setQueryFlags((int)queryFlags);
//}

TPhysicsComponentVolumeCapsuleParameters::TPhysicsComponentVolumeCapsuleParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeCapsuleParameters::~TPhysicsComponentVolumeCapsuleParameters()
{

}