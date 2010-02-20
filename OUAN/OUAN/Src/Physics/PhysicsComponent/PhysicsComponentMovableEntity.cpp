#include "PhysicsComponentMovableEntity.h"
using namespace OUAN;

PhysicsComponentMovableEntity::PhysicsComponentMovableEntity(const std::string& name)
:PhysicsComponentMovable(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentMovableEntity::~PhysicsComponentMovableEntity()
{
}

TPhysicsComponentMovableEntityParameters::TPhysicsComponentMovableEntityParameters() : TPhysicsComponentMovableParameters()
{
}

TPhysicsComponentMovableEntityParameters::~TPhysicsComponentMovableEntityParameters()
{
}