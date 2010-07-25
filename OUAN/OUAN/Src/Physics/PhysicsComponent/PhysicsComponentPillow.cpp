#include "OUAN_Precompiled.h"

#include "PhysicsComponentPillow.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Graphics/CameraManager/CameraManager.h"

using namespace OUAN;

PhysicsComponentPillow::PhysicsComponentPillow(const std::string& type)
:PhysicsComponentCharacter(type)
{
	reset();
}

PhysicsComponentPillow::~PhysicsComponentPillow()
{
	
}

void PhysicsComponentPillow::reset()
{
	PhysicsComponentCharacter::reset();
}

void PhysicsComponentPillow::update(double elapsedSeconds)
{
	PhysicsComponentCharacter::update(elapsedSeconds);
	//Logger::getInstance()->log("PILLOW MOVEMENT " + Ogre::StringConverter::toString(getNextMovement()));
}

void PhysicsComponentPillow::applyOuternMovement(double elapsedSeconds)
{
	setNextMovement(getOuternMovement()*mMovementFactor);
}


void PhysicsComponentPillow::setMovementFactor(double movementFactor)
{
	mMovementFactor=movementFactor;
}

double PhysicsComponentPillow::getMovementFactor()
{
	return mMovementFactor;
}

void PhysicsComponentPillow::applyFallY(double elapsedSeconds)
{

}

void PhysicsComponentPillow::applyMove()
{
	//Logger::getInstance()->log("PILLOW MOVEMENT " + Ogre::StringConverter::toString(getNextMovement()));
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		getNxOgreController()->move(
			NxOgre::Vec3(getNextMovement()),
			collisionFlags,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);
}

TPhysicsComponentPillowParameters::TPhysicsComponentPillowParameters() : TPhysicsComponentCharacterParameters()
{

}

TPhysicsComponentPillowParameters::~TPhysicsComponentPillowParameters()
{

}