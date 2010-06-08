#include "OUAN_Precompiled.h"

#include "PhysicsComponentComplex.h"
using namespace OUAN;

PhysicsComponentComplex::PhysicsComponentComplex(const std::string& type)
:PhysicsComponent(type)
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