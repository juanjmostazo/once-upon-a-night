#include "PhysicsComponentComplexConvex.h"
using namespace OUAN;

PhysicsComponentComplexConvex::PhysicsComponentComplexConvex(const std::string& name)
:PhysicsComponentComplex(COMPONENT_NAME_PHYSICS_COMPLEX_MOVABLE)
{
}

PhysicsComponentComplexConvex::~PhysicsComponentComplexConvex()
{
}

TPhysicsComponentComplexConvexParameters::TPhysicsComponentComplexConvexParameters() : TPhysicsComponentComplexParameters()
{
}

TPhysicsComponentComplexConvexParameters::~TPhysicsComponentComplexConvexParameters()
{
}