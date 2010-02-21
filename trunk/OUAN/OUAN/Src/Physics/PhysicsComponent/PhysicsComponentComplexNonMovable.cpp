#include "PhysicsComponentComplexNonMovable.h"
using namespace OUAN;

PhysicsComponentComplexNonMovable::PhysicsComponentComplexNonMovable(const std::string& name)
:PhysicsComponentComplex(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentComplexNonMovable::~PhysicsComponentComplexNonMovable()
{
}

TPhysicsComponentComplexNonMovableParameters::TPhysicsComponentComplexNonMovableParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexNonMovableParameters::~TPhysicsComponentComplexNonMovableParameters()
{
}