#include "PhysicsComponentMovable.h"
using namespace OUAN;

PhysicsComponentMovable::PhysicsComponentMovable(const std::string& name)
:PhysicsComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentMovable::~PhysicsComponentMovable()
{
}

TPhysicsComponentMovableParameters::TPhysicsComponentMovableParameters() : TPhysicsComponentParameters()
{
}

TPhysicsComponentMovableParameters::~TPhysicsComponentMovableParameters()
{
}