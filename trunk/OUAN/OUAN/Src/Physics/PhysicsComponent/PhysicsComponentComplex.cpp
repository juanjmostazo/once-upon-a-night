#include "PhysicsComponentComplex.h"
using namespace OUAN;

PhysicsComponentComplex::PhysicsComponentComplex(const std::string& name)
:PhysicsComponent(name.empty()?COMPONENT_NAME_OGRE:name)
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