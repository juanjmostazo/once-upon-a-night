#include "OUAN_Precompiled.h"

#include "PhysicsComponentWeapon.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Graphics/CameraManager/CameraManager.h"

using namespace OUAN;

PhysicsComponentWeapon::PhysicsComponentWeapon(const std::string& type)
:PhysicsComponentCharacter(type)
{
	reset();
}

PhysicsComponentWeapon::~PhysicsComponentWeapon()
{
	
}

void PhysicsComponentWeapon::reset()
{
	PhysicsComponentCharacter::reset();
}

void PhysicsComponentWeapon::update(double elapsedSeconds)
{
	PhysicsComponentCharacter::update(elapsedSeconds);
	//Logger::getInstance()->log("PILLOW MOVEMENT " + Ogre::StringConverter::toString(getNextMovement()));
}

void PhysicsComponentWeapon::applyOuternMovement(double elapsedSeconds)
{
	setNextMovement(getOuternMovement()*mMovementFactor);
}


void PhysicsComponentWeapon::setMovementFactor(double movementFactor)
{
	mMovementFactor=movementFactor;
}

double PhysicsComponentWeapon::getMovementFactor()
{
	return mMovementFactor;
}

void PhysicsComponentWeapon::applyFallY(double elapsedSeconds)
{

}

void PhysicsComponentWeapon::applyMove()
{
	//Logger::getInstance()->log("PILLOW MOVEMENT " + Ogre::StringConverter::toString(getNextMovement()));
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		getNxOgreController()->move(
			NxOgre::Vec3(getNextMovement()),
			collisionFlags,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);
}

void PhysicsComponentWeapon::updateSceneNode()
{
	//getSceneNode()->setPosition(
	//	getNxOgreController()->getPosition().as<Ogre::Vector3>() + 
	//	mOffsetRenderPosition);

	//getSceneNode()->setOrientation(
	//	getNxOgreController()->getOrientation().as<Ogre::Quaternion>());
}

TPhysicsComponentWeaponParameters::TPhysicsComponentWeaponParameters() : TPhysicsComponentCharacterParameters()
{

}

TPhysicsComponentWeaponParameters::~TPhysicsComponentWeaponParameters()
{

}