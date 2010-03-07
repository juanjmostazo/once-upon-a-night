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
	
	if (getNxOgreRigidBodyDescription().mMass > 0)
	{
		setNxOgreBody(
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
				new NxOgre::Capsule(getNxOgreSize().x,
									getNxOgreSize().y),
				getSceneNode()->getPosition(),
				getSceneNode(),
				getNxOgreRigidBodyDescription()));
	}
	else
	{
		setNxOgreBody(NULL);	
		setStatic(true);
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