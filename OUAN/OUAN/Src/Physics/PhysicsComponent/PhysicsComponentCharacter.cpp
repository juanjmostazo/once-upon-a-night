#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacter.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Graphics/CameraManager/CameraManager.h"

using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(type)
{
	reset();
}

PhysicsComponentCharacter::~PhysicsComponentCharacter()
{

}

void PhysicsComponentCharacter::reset()
{
	resetJumpingVars();
	initFallingVars();
	resetMovementVars();
	resetCyclicVars();

	setOnSurface(false);
	setMoving(false);
	setWalking(false);
}

void PhysicsComponentCharacter::update(double elapsedSeconds)
{
	if (getParent()->isFirstUpdate())
	{
		//DO NOTHING
	}
	else if(!getParent()->isEnabled())
	{
		resetMovementVars();
	} 
	else if (isCyclicCharacter())
	{
		performCyclicMovement(elapsedSeconds);
	}
	else
	{
		performClassicMovement(elapsedSeconds);
	}
}

void PhysicsComponentCharacter::performCyclicMovement(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	setNextMovement(Ogre::Vector3(0, Application::getInstance()->getPhysicsSubsystem()->mCyclicSpeed * mCyclicDirection * elapsedSeconds, 0));

	scaleNextMovementXYZ(elapsedSeconds);

	double cyclicLastPositionY = getNxOgreController()->getPosition().y;
	double sceneNodeLastPositionY = getSceneNode()->getPosition().y;

	getNxOgreController()->move(
		NxOgre::Vec3(getNextMovement()),
		collisionFlags,
		Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
		collisionFlags);

	getSceneNode()->setPosition(
		getSceneNode()->getPosition().x,
		sceneNodeLastPositionY,
		getSceneNode()->getPosition().z);

	mCyclicDirection = (collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? 1 : mCyclicDirection;
	mCyclicDirection = (collisionFlags & NxOgre::Enums::ControllerFlag_Up) ? -1 : mCyclicDirection;

	setOnSurface((collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? true : false);

	mCyclicOffset += getNxOgreController()->getPosition().y - cyclicLastPositionY;

	if (mCyclicOffset >= Application::getInstance()->getPhysicsSubsystem()->mCyclicMaxOffset)
	{
		mCyclicDirection = -1;
	}
	else if (mCyclicOffset <= -Application::getInstance()->getPhysicsSubsystem()->mCyclicMaxOffset)
	{
		mCyclicDirection = 1;
	}

	setLastMovement(getNextMovement());
	setNextMovement(Ogre::Vector3::ZERO);
}

void PhysicsComponentCharacter::performClassicMovement(double elapsedSeconds)
{	
	//logStatus("PERFORMING CLASSIC MOVEMENT - BEGINNING", elapsedSeconds);
	setNextMovement(Application::getInstance()->getCameraManager()->rotateMovementVector(getOuternMovement(), elapsedSeconds));
	setNextMovement(getNextMovement() * Application::getInstance()->getPhysicsSubsystem()->mOuternMovementFactor);

	if (!isWorthUpdating())
	{
		//logStatus("isWorthUpdating() == FALSE", elapsedSeconds);
		resetMovementVars();
	} 
	else
	{
		//logStatus("isWorthUpdating() == TRUE", elapsedSeconds);

		if (isWalking())
		{
			//logStatus("Within isWalking(), beginning", elapsedSeconds);
			applyWalkXZ(elapsedSeconds);
			//logStatus("Within isWalking(), end", elapsedSeconds);
		}

		if (isJumping())
		{
			//logStatus("Before applying jump", elapsedSeconds);
			applyJumpY(elapsedSeconds);

			if (mJumpingTime >= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime)
			{
				resetJumpingVars();
				initFallingVars();
			}
			//logStatus("After applying jump", elapsedSeconds);
		}
		else
		{
			//logStatus("Before applying fall", elapsedSeconds);
			applyFallY(elapsedSeconds);
			//logStatus("After applying fall", elapsedSeconds);
		}

		//logStatus("Before setNewYaw()", elapsedSeconds);
		setNewYaw();

		//logStatus("Before scaleNextMovementXZ()", elapsedSeconds);
		scaleNextMovementXZ(elapsedSeconds);

		//logStatus("Before move()", elapsedSeconds);
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		getNxOgreController()->move(
			NxOgre::Vec3(getNextMovement()),
			collisionFlags,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);

		//logStatus("Before setOnSurface()", elapsedSeconds);
		setOnSurface((collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? true : false);

		//logStatus("Before setWalking(), setMoving()", elapsedSeconds);
		setWalking(false);
		setMoving((getNextMovement().x >= 0.1 && getNextMovement().z >= 0.1));
	}

	logStatus("Before setLastMovement(), setNextMovement(), setOuternMovement()", elapsedSeconds);
	setLastMovement(getNextMovement());
	setNextMovement(Ogre::Vector3::ZERO);
	setOuternMovement(Ogre::Vector3::ZERO);

	//logStatus("PERFORMING CLASSIC MOVEMENT - END", elapsedSeconds);
	updateSceneNode();
}

void PhysicsComponentCharacter::applyWalkXZ(double elapsedSeconds)
{
	mNextMovement.x *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeedFactor;
	mNextMovement.z *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeedFactor;
}

void PhysicsComponentCharacter::applyJumpY(double elapsedSeconds)
{
	mJumpingTime += elapsedSeconds;
	mNextMovement.y += 
		elapsedSeconds * 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight / 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;			
}

void PhysicsComponentCharacter::applyFallY(double elapsedSeconds)
{
	mFallingTime += elapsedSeconds;
	mNextMovement.y += 
		-1 * 
		elapsedSeconds * 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight / 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;	
}

void PhysicsComponentCharacter::scaleNextMovementXZ(double elapsedSeconds)
{
	mNextMovement.x *= Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;
	mNextMovement.z *= Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;

	setNextMovement(getNextMovement());
}

void PhysicsComponentCharacter::scaleNextMovementXYZ(double elapsedSeconds)
{
	setNextMovement(getNextMovement() * 
		Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds);
}

bool PhysicsComponentCharacter::isWorthUpdating()
{
	return isInUse() && getNextMovement() != Ogre::Vector3::ZERO;
}

void PhysicsComponentCharacter::walk()
{
	setWalking(true);
}

void PhysicsComponentCharacter::jump()
{
	if(canJump())
	{
		initJumpingVars();
		resetFallingVars();
	}
}

bool PhysicsComponentCharacter::canJump()
{
	return !isJumping() && isOnSurface();
}

void PhysicsComponentCharacter::resetJumpingVars()
{
	mJumping = false;
	mJumpingTime = 0;
}

void PhysicsComponentCharacter::resetFallingVars()
{
	mFalling = false;
	mFallingTime = 0;
}

void PhysicsComponentCharacter::resetCyclicVars()
{
	mCyclicCharacter = false;
	mCyclicDirection = 1;
	mCyclicOffset = 0;
}

void PhysicsComponentCharacter::resetMovementVars()
{
	setOuternMovement(Ogre::Vector3::ZERO);
	setNextMovement(Ogre::Vector3::ZERO);
	setLastMovement(Ogre::Vector3::ZERO);
}

void PhysicsComponentCharacter::initJumpingVars()
{
	resetJumpingVars();
	mJumping = true;
}

void PhysicsComponentCharacter::initFallingVars()
{
	resetFallingVars();
	mFalling = true;
}	

bool PhysicsComponentCharacter::isJumping() const
{
	return mJumping;
}

bool PhysicsComponentCharacter::isFalling() const
{
	return mFalling;
}

bool PhysicsComponentCharacter::isFallingLimit() const
{
	return isFalling() && 
		mFallingTime >= Application::getInstance()->getPhysicsSubsystem()->mFallingTimeLimit;
}

bool PhysicsComponentCharacter::isWalking() const
{
	return mWalking;
}

bool PhysicsComponentCharacter::isMoving() const
{
	return mMoving;
}

void PhysicsComponentCharacter::setOnSurface(bool pOnSurface)
{
	PhysicsComponent::setOnSurface(pOnSurface);

	if (pOnSurface)
	{
		resetJumpingVars();
		resetFallingVars();
	}
}

void PhysicsComponentCharacter::setMoving(bool pMoving)
{
	mMoving = pMoving;
}

void PhysicsComponentCharacter::setWalking(bool pWalking)
{
	mWalking = pWalking;
}

void PhysicsComponentCharacter::setNewYaw()
{
	double characterYaw = getNxOgreController()->getDisplayYaw();

	if(getNextMovement().z<0 && getNextMovement().x<0)
	{
		characterYaw = Ogre::Math::ATan(getNextMovement().x/getNextMovement().z).valueDegrees();
	}
	else if(getNextMovement().z<0 && getNextMovement().x>0)
	{
		characterYaw = Ogre::Math::ATan(getNextMovement().x/getNextMovement().z).valueDegrees();
	}
	else if(getNextMovement().z>0 && getNextMovement().x>0)
	{
		characterYaw = Ogre::Math::ATan(getNextMovement().x/getNextMovement().z).valueDegrees();
		characterYaw+=180;
	}
	else if(getNextMovement().z>0 && getNextMovement().x<0)
	{
		characterYaw = Ogre::Math::ATan(getNextMovement().x/getNextMovement().z).valueDegrees();
		characterYaw+=180;
	}
	else if(getNextMovement().z!=0)
	{
		if(getNextMovement().z<0)
		{
			characterYaw=0;
		}
		else if(getNextMovement().z>0)
		{
			characterYaw=180;
		}
	}
	else if(getNextMovement().x!=0)
	{
		if(getNextMovement().x<0)
		{
			characterYaw=90;
		}
		else if(getNextMovement().x>0)
		{
			characterYaw=270;
		}
	}

	if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0 && (getNextMovement().x!=0 || getNextMovement().z!=0))
	{
		characterYaw+=180;
	}

	if(characterYaw>=360)
	{
		characterYaw-=360;
	}
	else if(characterYaw<0)
	{
		characterYaw+=360;
	}

	getNxOgreController()->setDisplayYaw(characterYaw);
}

void PhysicsComponentCharacter::create()
{
	PhysicsComponent::create();
	
	setNxOgreController(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene(), 		
			NxOgre::String(getParent()->getName().c_str()),
			getMass(),
			getSceneNode()->getOrientation().getYaw().valueDegrees(),
			Ogre::Math::Cos(Application::getInstance()->getPhysicsSubsystem()->mSlopeLimit * TO_RADIANS),   
			Application::getInstance()->getPhysicsSubsystem()->mStepOffset,
			Application::getInstance()->getPhysicsSubsystem()->mSkinWidth));
}

void PhysicsComponentCharacter::destroy()
{
	PhysicsComponent::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->destroyController(getNxOgreController());
}

void PhysicsComponentCharacter::setOuternMovement(Ogre::Vector3 outernMovement)
{
	mOuternMovement = outernMovement;
}

Ogre::Vector3 PhysicsComponentCharacter::getOuternMovement()
{
	return mOuternMovement;
}

void PhysicsComponentCharacter::setNextMovement(Ogre::Vector3 nextMovement)
{
	mNextMovement = nextMovement;
}

Ogre::Vector3 PhysicsComponentCharacter::getNextMovement()
{
	return mNextMovement;
}

void PhysicsComponentCharacter::setLastMovement(Ogre::Vector3 lastMovement)
{
	mLastMovement = lastMovement;
}

Ogre::Vector3 PhysicsComponentCharacter::getLastMovement()
{
	return mLastMovement;
}

void PhysicsComponentCharacter::updateSceneNode()
{
	getSceneNode()->setPosition(
		getNxOgreController()->getPosition().as<Ogre::Vector3>() + 
		mOffsetRenderPosition);

	getSceneNode()->setOrientation(
		getNxOgreController()->getOrientation().as<Ogre::Quaternion>());
}

void PhysicsComponentCharacter::setOffsetRenderPosition(Vector3 offsetRenderPosition)
{
	mOffsetRenderPosition = offsetRenderPosition;
}

Vector3 PhysicsComponentCharacter::getOffsetRenderPosition() const
{
	return mOffsetRenderPosition;
}

void PhysicsComponentCharacter::setCyclicCharacter(bool pCyclicCharacter)
{
	mCyclicCharacter = pCyclicCharacter;
}

bool PhysicsComponentCharacter::isCyclicCharacter()
{
	return mCyclicCharacter;
}

void PhysicsComponentCharacter::setNxOgreController(NxOgre::Controller* pNxOgreController)
{
	mNxOgreController = pNxOgreController;
}

NxOgre::Controller* PhysicsComponentCharacter::getNxOgreController()
{
	return mNxOgreController;
}

void PhysicsComponentCharacter::setNxOgreSize(NxOgre::Vec2 pNxOgreSize)
{
	mNxOgreSize = pNxOgreSize;
}

NxOgre::Vec2 PhysicsComponentCharacter::getNxOgreSize()
{
	return mNxOgreSize;
}

void PhysicsComponentCharacter::setNxOgreControllerDescription(NxOgre::ControllerDescription pNxOgreControllerDescription)
{
	mNxOgreControllerDescription = pNxOgreControllerDescription;
}

NxOgre::ControllerDescription PhysicsComponentCharacter::getNxOgreControllerDescription()
{
	return mNxOgreControllerDescription;
}

Ogre::Vector3 PhysicsComponentCharacter::getPosition()
{
	return getNxOgreController()->getPosition().as<Ogre::Vector3>();
}

double PhysicsComponentCharacter::getYaw()
{
	return getNxOgreController()->getDisplayYaw();
}

void PhysicsComponentCharacter::logStatus(Ogre::String label, double elapsedSeconds)
{
	//TODO REMOVE THIS LINE WHEN THIS LOG IS REQUIRED
	//return;

	if (getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0) 
	{
		Logger::getInstance()->log("PPC: ## LOG STATUS INIT ## " + label + " ##");
		
		Logger::getInstance()->log("PPC: mInUse -> " + Ogre::StringConverter::toString(mInUse));
		Logger::getInstance()->log("PPC: mOnSurface -> " + Ogre::StringConverter::toString(mOnSurface));

		Logger::getInstance()->log("PPC: isWalking() -> " + Ogre::StringConverter::toString(isWalking()));
		Logger::getInstance()->log("PPC: isMoving() -> " + Ogre::StringConverter::toString(isMoving()));
		Logger::getInstance()->log("PPC: isJumping() -> " + Ogre::StringConverter::toString(isJumping()));
		Logger::getInstance()->log("PPC: isFalling() -> " + Ogre::StringConverter::toString(isFalling()));
		Logger::getInstance()->log("PPC: isFallingLimit() -> " + Ogre::StringConverter::toString(isFallingLimit()));

		Logger::getInstance()->log("PPC: mJumpingTime -> " + Ogre::StringConverter::toString(Ogre::Real(mJumpingTime)));
		Logger::getInstance()->log("PPC: mFallingTime -> " + Ogre::StringConverter::toString(Ogre::Real(mFallingTime)));

		Logger::getInstance()->log("PPC: mNxOgreControllerPosition -> " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().x)) + " " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)) + " " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().z)));
		Logger::getInstance()->log("PPC: mNxOgreControllerYaw -> " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getDisplayYaw())));
		
		Logger::getInstance()->log("PPC: mOuternMovement -> " + Ogre::StringConverter::toString(Ogre::Real(mOuternMovement.x)) + " " + Ogre::StringConverter::toString(Ogre::Real(mOuternMovement.y)) + " " + Ogre::StringConverter::toString(Ogre::Real(mOuternMovement.z)));
		Logger::getInstance()->log("PPC: mNextMovement -> " + Ogre::StringConverter::toString(Ogre::Real(mNextMovement.x)) + " " + Ogre::StringConverter::toString(Ogre::Real(mNextMovement.y)) + " " + Ogre::StringConverter::toString(Ogre::Real(mNextMovement.z)));

		Logger::getInstance()->log("PPC: mLastMovement -> " + Ogre::StringConverter::toString(Ogre::Real(mLastMovement.x)) + " " + Ogre::StringConverter::toString(Ogre::Real(mLastMovement.y)) + " " + Ogre::StringConverter::toString(Ogre::Real(mLastMovement.z)));

		Logger::getInstance()->log("PPC: elapsedSeconds -> " + Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)));
		
		Logger::getInstance()->log("PPC: ## LOG STATUS END ## " + label + " ##");
	}
}

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{

}