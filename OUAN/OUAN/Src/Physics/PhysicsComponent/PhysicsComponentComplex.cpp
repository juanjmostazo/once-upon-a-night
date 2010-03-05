#include "PhysicsComponentComplex.h"
using namespace OUAN;

PhysicsComponentComplex::PhysicsComponentComplex(const std::string& type)
:PhysicsComponent(COMPONENT_TYPE_PHYSICS_COMPLEX)
{

}

PhysicsComponentComplex::~PhysicsComponentComplex()
{

}

void PhysicsComponentComplex::create()
{
	PhysicsComponent::create();
}

void PhysicsComponentComplex::destroy()
{	
	PhysicsComponent::destroy();
}

TPhysicsComponentComplexParameters::TPhysicsComponentComplexParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentComplexParameters::~TPhysicsComponentComplexParameters()
{

}