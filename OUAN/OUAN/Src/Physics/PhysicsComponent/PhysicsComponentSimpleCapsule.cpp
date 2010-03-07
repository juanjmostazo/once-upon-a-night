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
	
	setNxOgreBody(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->createBody(
			new NxOgre::Capsule(getNxOgreSize().x,
								getNxOgreSize().y),
			getSceneNode()->getPosition(),
			getSceneNode(),
			getNxOgreRigidBodyDescription()));
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