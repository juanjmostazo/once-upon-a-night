#include "PhysicsComponentSimple.h"
using namespace OUAN;

PhysicsComponentSimple::PhysicsComponentSimple(const std::string& name)
:PhysicsComponent(name.empty()?COMPONENT_NAME_OGRE:name)
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