#include "PhysicsComponent.h"
using namespace OUAN;

PhysicsComponent::PhysicsComponent(const std::string& name)
:Component(COMPONENT_NAME_PHYSICS)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::update(long elapsedTime)
{
}

TPhysicsComponentParameters::TPhysicsComponentParameters() : TComponentParameters()
{
}

TPhysicsComponentParameters::~TPhysicsComponentParameters()
{
}