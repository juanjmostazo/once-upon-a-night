#include "PhysicsComponentComplex.h"
using namespace OUAN;

PhysicsComponentComplex::PhysicsComponentComplex(const std::string& name)
:PhysicsComponent(COMPONENT_NAME_PHYSICS_COMPLEX)
{
}

PhysicsComponentComplex::~PhysicsComponentComplex()
{
}

TPhysicsComponentComplexParameters::TPhysicsComponentComplexParameters() : TPhysicsComponentParameters()
{
}

TPhysicsComponentComplexParameters::~TPhysicsComponentComplexParameters()
{
}