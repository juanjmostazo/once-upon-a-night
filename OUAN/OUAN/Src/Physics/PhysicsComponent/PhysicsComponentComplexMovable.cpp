#include "PhysicsComponentComplexMovable.h"
using namespace OUAN;

PhysicsComponentComplexMovable::PhysicsComponentComplexMovable(const std::string& name)
:PhysicsComponentComplex(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentComplexMovable::~PhysicsComponentComplexMovable()
{
}

TPhysicsComponentComplexMovableParameters::TPhysicsComponentComplexMovableParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexMovableParameters::~TPhysicsComponentComplexMovableParameters()
{
}