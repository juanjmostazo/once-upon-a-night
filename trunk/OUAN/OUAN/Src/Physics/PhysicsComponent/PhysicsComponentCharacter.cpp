#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacter.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Graphics/CameraManager/CameraManager.h"

using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(type)
{
	reset();
	mFlyingCharacter=false;
	mOffsetDisplayYaw=0;
	mOffsetRenderPosition=Vector3::ZERO;
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
	
	setWalking(false);
	setMoving(false);
	setOnSurface(false);
	setLastElapsedSeconds(0);
	mSliding=false;
	mSlidingCalculatedThisFrame=false;
}

void PhysicsComponentCharacter::update(double elapsedSeconds)
{
	if (isCyclicCharacter())
	{
		performCyclicMovement(elapsedSeconds);
	}
	else
	{
		performClassicMovement(elapsedSeconds);
	}

	setLastElapsedSeconds(elapsedSeconds);
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

	setOnSurface((collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? true : false);

	getSceneNode()->setPosition(
		getSceneNode()->getPosition().x,
		sceneNodeLastPositionY,
		getSceneNode()->getPosition().z);

	mCyclicDirection = (collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? 1 : mCyclicDirection;
	mCyclicDirection = (collisionFlags & NxOgre::Enums::ControllerFlag_Up) ? -1 : mCyclicDirection;

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

void PhysicsComponentCharacter::applySlideY(double elapsedSeconds)
{
	// If sliding is applied, nextMovement will be REPLACED by the slide movement so the character won't 
	// move normally. This means it wo't be able to jump or move around while sliding.

	if(mSliding && !mFlyingCharacter)
	{
		mNextMovement.y =  -Application::getInstance()->getPhysicsSubsystem()->mSlidingUnitsPerSecond*elapsedSeconds;
		if(mSlidingCalculatedThisFrame)
		{
			mNextMovement.x = mSlidingDirection.x*Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond*elapsedSeconds;
			mNextMovement.z = mSlidingDirection.z*Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond*elapsedSeconds;
		}
	}
	else
	{
		mSliding=false;
	}
}

void PhysicsComponentCharacter::calculateSliding(Ogre::Vector3 normal)
{
	double angle;

	angle = Application::getInstance()->getPhysicsSubsystem()->angleFromNormal(normal);

	mSliding = angle >= Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle;
	mSlidingCalculatedThisFrame = true;

	if(mSliding)
	{
		mSlidingDirection=normal;
	}
	else
	{
		mSlidingDirection=Vector3::ZERO;
	}
}

bool PhysicsComponentCharacter::isSliding() const
{
	return mSliding;
}

void PhysicsComponentCharacter::performClassicMovement(double elapsedSeconds)
{	
	Vector3 lastPosition;

	lastPosition=getNxOgreController()->getPosition().as<Ogre::Vector3>();

	//logStatus("PERFORMING CLASSIC MOVEMENT - BEGINNING", elapsedSeconds);
	applyOuternMovement(elapsedSeconds);

	//logStatus("Before scaleNextMovementXZ()", elapsedSeconds);
	scaleNextMovementXZ(elapsedSeconds);

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
			setWalking(false);
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
			applySlideY(elapsedSeconds);
			//logStatus("After applying fall", elapsedSeconds);
		}

		//logStatus("Before setMoving()", elapsedSeconds);
		setMoving((getNextMovement().x >= 0.1 && getNextMovement().z >= 0.1));

		//logStatus("Before setNewYaw()", elapsedSeconds);
		setNewYaw(elapsedSeconds);

		//logStatus("Before move()", elapsedSeconds);
		applyMove();

	}

	//logStatus("Before setLastMovement(), setNextMovement(), setOuternMovement()", elapsedSeconds);
	setLastMovement(getNxOgreController()->getPosition().as<Ogre::Vector3>()-lastPosition);
	setNextMovement(Ogre::Vector3::ZERO);
	setOuternMovement(Ogre::Vector3::ZERO);

	mSlidingCalculatedThisFrame=false;

	updateSceneNode();
	//logStatus("PERFORMING CLASSIC MOVEMENT - END", elapsedSeconds);
}

void PhysicsComponentCharacter::applyMove()
{
		//Logger::getInstance()->log("move "+getParent()->getName());
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		getNxOgreController()->move(
			NxOgre::Vec3(getNextMovement()),
			collisionFlags,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);

			setOnSurface((collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? true : false);
}

void PhysicsComponentCharacter::setLastSurfacePosition(Ogre::Vector3 lastSurfacePosition)
{
	mLastSurfacePosition=lastSurfacePosition;
}

Vector3 PhysicsComponentCharacter::getLastSurfacePosition() const
{
	return mLastSurfacePosition;
}

void PhysicsComponentCharacter::applyWalkXZ(double elapsedSeconds)
{
	mNextMovement.x *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeedFactor;
	mNextMovement.z *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeedFactor;
}

void PhysicsComponentCharacter::applyJumpY(double elapsedSeconds)
{
	double initialTime = mJumpingTime;
	double finalTime = mJumpingTime + elapsedSeconds;

	finalTime = finalTime <= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime 
		? finalTime 
		: Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;

	////////////

	initialTime -= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;
	finalTime -= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;

	////////////

	double basicValueInitial = (initialTime / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);
	basicValueInitial *= basicValueInitial;

	double initialValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
		((-1 * basicValueInitial) + 1);

	////////////

	double basicValueFinal = (finalTime / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);
	basicValueFinal *= basicValueFinal;

	double finalValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
		((-1 * basicValueFinal) + 1);

	////////////

	mNextMovement.y +=  finalValue - initialValue;
	mJumpingTime += elapsedSeconds;
}

void PhysicsComponentCharacter::applyFallY(double elapsedSeconds)
{
	double initialTime = mFallingTime;
	double finalTime = mFallingTime + elapsedSeconds;

	if(!mFlyingCharacter)
	{
		if (initialTime <= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime)
		{
			finalTime = finalTime <= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime 
			? finalTime 
			: Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;

			////////////

			// DO NOTHING HERE

			////////////

			double basicValueInitial = (initialTime / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);
			basicValueInitial *= basicValueInitial;

			double initialValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
				((-1 * basicValueInitial) + 1);

			////////////

			double basicValueFinal = (finalTime / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);
			basicValueFinal *= basicValueFinal;

			double finalValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
				((-1 * basicValueFinal) + 1);

			////////////

			mNextMovement.y +=  finalValue - initialValue;
		}
		else
		{
			mNextMovement.y +=  
				-3 * 
				elapsedSeconds * 
				Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight / 
				Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;
		}
		mFallingTime += elapsedSeconds;
	}
}
/*
void PhysicsComponentCharacter::applyJumpY(double elapsedSeconds)
{
	double initialTime = mJumpingTime;
	double finalTime = mJumpingTime + elapsedSeconds;

	finalTime = finalTime <= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime 
		? finalTime 
		: Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;

	double initialValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
		sin(initialTime * PI_HALF / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);

	double finalValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
		sin(finalTime * PI_HALF / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);

	mNextMovement.y +=  finalValue - initialValue;
	mJumpingTime += elapsedSeconds;
}

void PhysicsComponentCharacter::applyFallY(double elapsedSeconds)
{
	double initialTime = mFallingTime;
	double finalTime = mFallingTime + elapsedSeconds;

	if (initialTime <= Application::getInstance()->getPhysicsSubsystem()->mImpulseTime)
	{
		double initialValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
			cos(initialTime * PI_HALF / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);

		double finalValue = Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight *
			cos(finalTime * PI_HALF / Application::getInstance()->getPhysicsSubsystem()->mImpulseTime);

		mNextMovement.y +=  finalValue - initialValue;
	}
	else
	{
		mNextMovement.y -=  
			2 * 
			elapsedSeconds * 
			Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight / 
			Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;
	}

	mFallingTime += elapsedSeconds;
}
*/
/*
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
	mNextMovement.y -=  
		elapsedSeconds * 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseHeight / 
		Application::getInstance()->getPhysicsSubsystem()->mImpulseTime;	

	mFallingTime += elapsedSeconds;
}
*/
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
	return isInUse() && (getNextMovement() != Ogre::Vector3::ZERO);
}

void PhysicsComponentCharacter::stabilize(double elapsedSeconds)
{
	if(isInUse() && !mFlyingCharacter)
	{
		PhysicsSubsystemPtr physicsSS = Application::getInstance()->getPhysicsSubsystem();
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		getNxOgreController()->move(
			NxOgre::Vec3(0,-physicsSS->mStabilizeCharacterMoveY,0),
			collisionFlags,
			physicsSS->mMinDistance,
			collisionFlags);

		setOnSurface(true);
	}
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
	return !isJumping() && isOnSurface() && !isSliding();
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

		setLastSurfacePosition(getNxOgreController()->getPosition().as<Ogre::Vector3>());
	}
}

void PhysicsComponentCharacter::setLastElapsedSeconds(double pLastElapsedSeconds)
{
	mLastElapsedSeconds = pLastElapsedSeconds;
}

void PhysicsComponentCharacter::setMoving(bool pMoving)
{
	mMoving = pMoving;
}

void PhysicsComponentCharacter::setWalking(bool pWalking)
{
	mWalking = pWalking;
}

double PhysicsComponentCharacter::calculateMovementDisplayYaw()
{
	double characterYaw = getDisplayYaw();

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

	characterYaw+=mOffsetDisplayYaw;

	if(characterYaw>=360)
	{
		characterYaw-=360;
	}
	else if(characterYaw<0)
	{
		characterYaw+=360;
	}
	return characterYaw;
}

void PhysicsComponentCharacter::setNewYaw(double elapsedSeconds)
{
	double characterYaw = calculateMovementDisplayYaw();

	double turnUnitsSecond=Application::getInstance()->getPhysicsSubsystem()->mTurnUnitsPerSecond;

	double angleDifference=calculateAngleDifference(getDisplayYaw(),characterYaw);
	if(Ogre::Math::Abs(angleDifference)>turnUnitsSecond*elapsedSeconds)
	{
		if(angleDifference<0)
		{
			setDisplayYaw(getDisplayYaw()-turnUnitsSecond*elapsedSeconds);
		}
		else if(angleDifference>0)
		{
			setDisplayYaw(getDisplayYaw()+turnUnitsSecond*elapsedSeconds);
		}
	}
	else
	{
		setDisplayYaw(characterYaw);
	}

	setRotationMovementFactor(angleDifference);

}

void PhysicsComponentCharacter::setRotationMovementFactor(double angleDifference)
{
	angleDifference=Ogre::Math::Abs(angleDifference);

	if(!isJumping())
	{
		if(angleDifference>90)
		{
			setNextMovement(Vector3(0,getNextMovement().y,0));
		}
		else
		{
			double factor;
			factor=(1-(angleDifference/90)*(angleDifference/90));
			setNextMovement(Vector3(getNextMovement().x*factor,getNextMovement().y,getNextMovement().z*factor));
		}
	}
}

double PhysicsComponentCharacter::calculateAngleDifference(double angle1, double angle2)
{
    double difference = angle2 - angle1;
    while (difference < -180) difference += 360;
    while (difference > 180) difference -= 360;
    return difference;
}

void PhysicsComponentCharacter::create()
{
	PhysicsComponent::create();
	PhysicsSubsystemPtr physicsSS=Application::getInstance()->getPhysicsSubsystem();

	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS CREATE - Creating tripollo 1");
	}

	NxOgre::ControllerDescription pNxOgreControllerDescription;
	pNxOgreControllerDescription.mCallback=physicsSS.get();
	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS Callback address "+StringConverter::toString((int)physicsSS.get()));
	}
	pNxOgreControllerDescription.mPosition.set(NxOgre::Vec3(getSceneNode()->getPosition()-mOffsetRenderPosition+SAFE_SURFACE_DISTANCE));
	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS Position "+StringConverter::toString(getSceneNode()->getPosition()-mOffsetRenderPosition+SAFE_SURFACE_DISTANCE));
	}

	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS Size "+StringConverter::toString(getNxOgreSize().x)+", "+StringConverter::toString(getNxOgreSize().y));
	}

	setNxOgreControllerDescription(pNxOgreControllerDescription);

	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS "+StringConverter::toString((int)physicsSS->getNxOgreScene()));
	}

	setNxOgreController(
		physicsSS->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			physicsSS->getNxOgreScene(), 		
			NxOgre::String(getParent()->getName().c_str()),
			getMass(),
			getSceneNode()->getOrientation().getYaw().valueDegrees(),
			Ogre::Math::Cos(physicsSS->mSlopeLimit * TO_RADIANS),   
			physicsSS->mStepOffset,
			physicsSS->mSkinWidth));
	
	if (!mParent->getName().compare("tripollo#01"))
	{
		Logger::getInstance()->log("PHYSICS CREATE END- Creating tripollo 1");
	}

	if(Application::getInstance()->getGameWorldManager()->isInitialized())
	{
		stabilize(physicsSS->mStabilizeSeconds);
	}
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

void PhysicsComponentCharacter::applyOuternMovement(double elapsedSeconds)
{
	setNextMovement(getOuternMovement());
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

void PhysicsComponentCharacter::setOffsetDisplayYaw(double offsetDisplayYaw)
{
	mOffsetDisplayYaw = offsetDisplayYaw;
}

double PhysicsComponentCharacter::getOffsetDisplayYaw() const
{
	return mOffsetDisplayYaw;
}

void PhysicsComponentCharacter::setFlyingCharacter(bool pFlyingCharacter)
{
	mFlyingCharacter = pFlyingCharacter;
}

bool PhysicsComponentCharacter::isFlyingCharacter()
{
	return mFlyingCharacter;
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

void PhysicsComponentCharacter::setPosition(Ogre::Vector3 position)
{
	getNxOgreController()->setPosition(NxOgre::Vec3(position));
	updateSceneNode();
}

Ogre::Vector3 PhysicsComponentCharacter::getPosition()
{
	return getNxOgreController()->getPosition().as<Ogre::Vector3>();
}

double PhysicsComponentCharacter::getYaw()
{
	return getNxOgreController()->getDisplayYaw();
}

void PhysicsComponentCharacter::setDisplayYaw(double displayYaw)
{	
	getNxOgreController()->setDisplayYaw(displayYaw);
	updateSceneNode();
}

double PhysicsComponentCharacter::getDisplayYaw()
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

		Logger::getInstance()->log("PPC: mSceneNodePosition -> " + Ogre::StringConverter::toString(getSceneNode()->getPosition()));
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