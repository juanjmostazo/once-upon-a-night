#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacterOny.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

PhysicsComponentCharacterOny::PhysicsComponentCharacterOny(const std::string& type)
:PhysicsComponentCharacter(type)
{
	reset();
}

PhysicsComponentCharacterOny::~PhysicsComponentCharacterOny()
{
	
}

void PhysicsComponentCharacterOny::reset()
{
	PhysicsComponentCharacter::reset();
}

void PhysicsComponentCharacterOny::update(double elapsedSeconds)
{
	PhysicsComponentCharacter::update(elapsedSeconds);
}

bool PhysicsComponentCharacterOny::isWorthUpdating()
{
	return isInUse();
}

bool PhysicsComponentCharacterOny::canJump()
{
	return 
		PhysicsComponentCharacter::canJump() ||
		Application::getInstance()->getGameWorldManager()->isGodMode();
}

TPhysicsComponentCharacterOnyParameters::TPhysicsComponentCharacterOnyParameters() : TPhysicsComponentCharacterParameters()
{

}

TPhysicsComponentCharacterOnyParameters::~TPhysicsComponentCharacterOnyParameters()
{

}