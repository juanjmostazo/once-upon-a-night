#include "PhysicsComponentVolumeBox.h"
using namespace OUAN;

PhysicsComponentVolumeBox::PhysicsComponentVolumeBox(const std::string& type)
:PhysicsComponentVolume(type)
{

}

PhysicsComponentVolumeBox::~PhysicsComponentVolumeBox()
{

}

void PhysicsComponentVolumeBox::create()
{
	PhysicsComponentVolume::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());

	NxOgre::Box * pBox = new NxOgre::Box(
				getNxOgreSize().x,
				getNxOgreSize().y,
				getNxOgreSize().z);

	pBox->setName(name);
	
	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			pBox,								
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

void PhysicsComponentVolumeBox::setQueryFlags(QueryFlags queryFlags)
{
	//getNxOgreBody()->setQueryFlags((int)queryFlags);
}

TPhysicsComponentVolumeBoxParameters::TPhysicsComponentVolumeBoxParameters() : TPhysicsComponentVolumeParameters()
{

}

TPhysicsComponentVolumeBoxParameters::~TPhysicsComponentVolumeBoxParameters()
{

}