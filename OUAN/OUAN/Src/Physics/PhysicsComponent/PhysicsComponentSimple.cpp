#include "PhysicsComponentSimple.h"
using namespace OUAN;

PhysicsComponentSimple::PhysicsComponentSimple(const std::string& name)
:PhysicsComponent(COMPONENT_NAME_PHYSICS_SIMPLE)
{
}

PhysicsComponentSimple::~PhysicsComponentSimple()
{
}

TPhysicsComponentSimpleParameters::TPhysicsComponentSimpleParameters() : TPhysicsComponentParameters()
{
}

TPhysicsComponentSimpleParameters::~TPhysicsComponentSimpleParameters()
{
}