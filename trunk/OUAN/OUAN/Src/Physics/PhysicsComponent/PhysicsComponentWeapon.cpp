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
	mAttackCollisions.clear();
}

void PhysicsComponentWeapon::setNxOgreMaxSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreMaxSize=pNxOgreSize;
}

NxOgre::Vec2 PhysicsComponentWeapon::getNxOgreMaxSize()
{
	return mNxOgreMaxSize;
}

void PhysicsComponentWeapon::startAttack()
{
	mAttackCollisions.clear();
	if(isInUse())
	{
		destroy();
	}
	setNxOgreSize(NxOgre::Vec2(0.01,0.01));
	create();
}

void PhysicsComponentWeapon::endAttack()
{
	if(isInUse())
	{
		destroy();
	}
}

void PhysicsComponentWeapon::addCollision(std::string gameObjectName)
{
	mAttackCollisions.insert(gameObjectName);
}

bool PhysicsComponentWeapon::attackHasCollision(std::string gameObjectName)
{
	return mAttackCollisions.count(gameObjectName)>0;
}

void PhysicsComponentWeapon::update(double elapsedSeconds)
{
	if(getNxOgreSize().x<getNxOgreMaxSize().x || getNxOgreSize().y<getNxOgreMaxSize().y )
	{
		destroy();
		setNxOgreSize(NxOgre::Vec2(getNxOgreSize().x+mInflateSpeed*elapsedSeconds,getNxOgreSize().y+mInflateSpeed*elapsedSeconds));
		create();
	}

	PhysicsComponentCharacter::update(elapsedSeconds);
	//Logger::getInstance()->log("PILLOW MOVEMENT " + Ogre::StringConverter::toString(getNextMovement()));
}

void PhysicsComponentWeapon::applyOuternMovement(double elapsedSeconds)
{
	setNextMovement(getOuternMovement()*mMovementFactor);
}

void PhysicsComponentWeapon::setOuternMovement(Ogre::Vector3 outernMovement)
{
	if(outernMovement!=Vector3::ZERO)
	{
		mOuternMovement = outernMovement;
	}
}

void PhysicsComponentWeapon::setMovementFactor(double movementFactor)
{
	mMovementFactor=movementFactor;
}

double PhysicsComponentWeapon::getMovementFactor()
{
	return mMovementFactor;
}

void PhysicsComponentWeapon::setInflateSpeed(double inflateSpeed)
{
	mInflateSpeed=inflateSpeed;
}

double PhysicsComponentWeapon::getInflateSpeed()
{
	return mInflateSpeed;
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