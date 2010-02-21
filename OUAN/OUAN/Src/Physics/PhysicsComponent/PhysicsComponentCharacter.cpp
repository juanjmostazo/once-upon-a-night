#include "PhysicsComponentCharacter.h"
using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& name)
:PhysicsComponent(COMPONENT_NAME_PHYSICS_CHARACTER)
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