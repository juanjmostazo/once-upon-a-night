#include "PhysicsComponentCharacter.h"
using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& name)
:PhysicsComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

PhysicsComponentCharacter::~PhysicsComponentCharacter()
{
}

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{
}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{
}