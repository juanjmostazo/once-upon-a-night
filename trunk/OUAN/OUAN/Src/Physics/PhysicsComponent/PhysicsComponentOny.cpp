#include "PhysicsComponentOny.h"
using namespace OUAN;

PhysicsComponentOny::PhysicsComponentOny(const std::string& name)
:PhysicsComponentMovableEntity(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentOny::~PhysicsComponentOny()
{
}

TPhysicsComponentOnyParameters::TPhysicsComponentOnyParameters() : TPhysicsComponentMovableEntityParameters()
{
}

TPhysicsComponentOnyParameters::~TPhysicsComponentOnyParameters()
{
}