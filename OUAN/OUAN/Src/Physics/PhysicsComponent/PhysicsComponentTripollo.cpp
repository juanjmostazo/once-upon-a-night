#include "PhysicsComponentTripollo.h"
using namespace OUAN;

PhysicsComponentTripollo::PhysicsComponentTripollo(const std::string& name)
:PhysicsComponentMovableEntity(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentTripollo::~PhysicsComponentTripollo()
{
}

TPhysicsComponentTripolloParameters::TPhysicsComponentTripolloParameters() : TPhysicsComponentMovableEntityParameters()
{
}

TPhysicsComponentTripolloParameters::~TPhysicsComponentTripolloParameters()
{
}