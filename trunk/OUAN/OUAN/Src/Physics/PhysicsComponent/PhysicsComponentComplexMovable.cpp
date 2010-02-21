#include "PhysicsComponentComplexMovable.h"
using namespace OUAN;

PhysicsComponentComplexMovable::PhysicsComponentComplexMovable(const std::string& name)
:PhysicsComponentComplex(COMPONENT_NAME_PHYSICS_COMPLEX_MOVABLE)
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