#include "PhysicsComponentSimpleCapsule.h"
using namespace OUAN;

PhysicsComponentSimpleCapsule::PhysicsComponentSimpleCapsule(const std::string& name)
:PhysicsComponentSimple(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentSimpleCapsule::~PhysicsComponentSimpleCapsule()
{
}

TPhysicsComponentSimpleCapsuleParameters::TPhysicsComponentSimpleCapsuleParameters() : TPhysicsComponentSimpleParameters()
{
}

TPhysicsComponentSimpleCapsuleParameters::~TPhysicsComponentSimpleCapsuleParameters()
{
}