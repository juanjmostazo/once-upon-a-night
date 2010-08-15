#include "OUAN_Precompiled.h"

#include "PhysicsComponentSimpleCapsule.h"
using namespace OUAN;

PhysicsComponentSimpleCapsule::PhysicsComponentSimpleCapsule(const std::string& type)
:PhysicsComponentSimple(type)
{

}

PhysicsComponentSimpleCapsule::~PhysicsComponentSimpleCapsule()
{

}

void PhysicsComponentSimpleCapsule::create()
{
	PhysicsComponentSimple::create();

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	
	NxOgre::Capsule* pCapsule = 
		new NxOgre::Capsule(getNxOgreSize().x,
							getNxOgreSize().y);

	pCapsule->setName(name);

	if (getMass() > 0)
	{
		setNxOgreKinematicBody(NULL);

		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();
		pDesc.mName = name;

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				pCapsule,
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		getNxOgreBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));
		//getNxOgreBody()->setQueryFlags((int)mQueryFlags);
	}
	else
	{
		pCapsule->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
		setStatic(true);
		setNxOgreBody(NULL);

		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
				pCapsule,
				getSceneNode()->getPosition(),
				getSceneNode()));

		getNxOgreKinematicBody()->setGlobalOrientationQuat(NxOgre::Quat(getSceneNode()->getOrientation()));
		//getNxOgreKinematicBody()->setQueryFlags((int)mQueryFlags);
	}

	setNxOgreVolume(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->createVolume(
			pCapsule,								
			NxOgre::Matrix44(	
				NxOgre::Vec3(getSceneNode()->getPosition()), 
				NxOgre::Quat(getSceneNode()->getOrientation())),
			Application::getInstance()->getPhysicsSubsystem().get(), 
			NxOgre::Enums::VolumeCollisionType_All));	
}

void PhysicsComponentSimpleCapsule::destroy()
{
	PhysicsComponentSimple::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene()->destroyVolume(getNxOgreVolume());
}

NxOgre::Volume* PhysicsComponentSimpleCapsule::getNxOgreVolume()
{
	return mNxOgreVolume;
}

void PhysicsComponentSimpleCapsule::setNxOgreVolume(NxOgre::Volume* pNxOgreVolume)
{
	mNxOgreVolume=pNxOgreVolume;
}

void PhysicsComponentSimpleCapsule::setPosition(NxOgre::Vec3 position)
{
	if (isInUse())
	{
		getNxOgreKinematicBody()->setGlobalPosition(position);
	}
}

void PhysicsComponentSimpleCapsule::setOrientation(NxOgre::Quat orientation)
{
	if (isInUse())
	{
		getNxOgreKinematicBody()->setGlobalOrientationQuat(orientation);
	}
}

NxOgre::Vec2 PhysicsComponentSimpleCapsule::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentSimpleCapsule::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
	mHeight=pNxOgreSize.y;
}

//void PhysicsComponentSimpleCapsule::setQueryFlags(QueryFlags queryFlags)
//{
//	mQueryFlags = queryFlags;
//}

TPhysicsComponentSimpleCapsuleParameters::TPhysicsComponentSimpleCapsuleParameters() : TPhysicsComponentSimpleParameters()
{

}

TPhysicsComponentSimpleCapsuleParameters::~TPhysicsComponentSimpleCapsuleParameters()
{

}