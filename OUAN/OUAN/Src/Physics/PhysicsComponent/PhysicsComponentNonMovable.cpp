#include "PhysicsComponentNonMovable.h"
using namespace OUAN;

PhysicsComponentNonMovable::PhysicsComponentNonMovable(const std::string& name)
:PhysicsComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentNonMovable::~PhysicsComponentNonMovable()
{
}

TPhysicsComponentNonMovableParameters::TPhysicsComponentNonMovableParameters() : TPhysicsComponentParameters()
{
}

TPhysicsComponentNonMovableParameters::~TPhysicsComponentNonMovableParameters()
{
}