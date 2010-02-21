#include "PhysicsComponentSimpleCapsule.h"
using namespace OUAN;

PhysicsComponentSimpleCapsule::PhysicsComponentSimpleCapsule(const std::string& name)
:PhysicsComponentSimple(COMPONENT_NAME_PHYSICS_SIMPLE_CAPSULE)
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