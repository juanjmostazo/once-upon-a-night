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

}

void PhysicsComponentSimpleCapsule::destroy()
{

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