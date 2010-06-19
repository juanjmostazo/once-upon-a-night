#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacterOny.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

PhysicsComponentCharacterOny::PhysicsComponentCharacterOny(const std::string& type)
:PhysicsComponentCharacter(type)
{
	mPointRenderable=NULL;
	reset();
}

PhysicsComponentCharacterOny::~PhysicsComponentCharacterOny()
{
	mPointRenderable=NULL;//NxOgre will handle the destruction of these objects.
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