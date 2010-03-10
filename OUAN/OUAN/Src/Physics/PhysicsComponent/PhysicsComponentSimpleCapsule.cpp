#include "PhysicsComponentSimpleCapsule.h"
using namespace OUAN;

PhysicsComponentSimpleCapsule::PhysicsComponentSimpleCapsule(const std::string& type)
:PhysicsComponentSimple(COMPONENT_TYPE_PHYSICS_SIMPLE_CAPSULE)
{

}

PhysicsComponentSimpleCapsule::~PhysicsComponentSimpleCapsule()
{

}

void PhysicsComponentSimpleCapsule::create()
{
	PhysicsComponentSimple::create();
	
	if (getMass() > 0)
	{
		NxOgre::RigidBodyDescription pDesc = NxOgre::RigidBodyDescription();
		pDesc.mMass = getMass();

		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				new NxOgre::Capsule(getNxOgreSize().x,
									getNxOgreSize().y),
				getSceneNode()->getPosition(),
				getSceneNode(),
				pDesc));

		setNxOgreKinematicBody(NULL);
	}
	else
	{
		setNxOgreKinematicBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createKinematicBody(
				new NxOgre::Capsule(getNxOgreSize().x,
								getNxOgreSize().y),
				getSceneNode()->getPosition(),
				getSceneNode()));

		setStatic(true);
		setNxOgreBody(NULL);
	}
}

void PhysicsComponentSimpleCapsule::destroy()
{
	PhysicsComponentSimple::destroy();
}

NxOgre::Vec2 PhysicsComponentSimpleCapsule::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentSimpleCapsule::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize=pNxOgreSize;
}

TPhysicsComponentSimpleCapsuleParameters::TPhysicsComponentSimpleCapsuleParameters() : TPhysicsComponentSimpleParameters()
{

}

TPhysicsComponentSimpleCapsuleParameters::~TPhysicsComponentSimpleCapsuleParameters()
{

}