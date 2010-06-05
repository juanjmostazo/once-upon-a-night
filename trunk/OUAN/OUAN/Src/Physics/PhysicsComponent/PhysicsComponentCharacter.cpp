#include "PhysicsComponentCharacter.h"
#include "../../RayCasting/RayCasting.h"

using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(type)
,mPointRenderable(NULL)
{
	reset();
}

PhysicsComponentCharacter::~PhysicsComponentCharacter()
{
	mPointRenderable=NULL;//NxOgre will handle the destruction of these objects.
}

void PhysicsComponentCharacter::reset()
{
	mNextMovement = NxOgre::Vec3::ZERO;
	mLastMovement = NxOgre::Vec3::ZERO;

	mJumping = false;
	mFalling = true;
	mFallingLimit = false;
	mSliding = false;
	mOnSurface = false;
	mIsWalking = false;
	
	mFallTime = 0;

	mJumpSpeed = 0;
	mFallSpeed = 0;
	mSlideDisplacement = NxOgre::Vec3(0,0,0);
	mNormalAngle = 0;

	mDash = 0;

	mLastYaw=0;
	mDashDirection=Ogre::Vector3::ZERO;
	mIsNotApplyingDash=true;

	//mOffsetRenderPosition=Ogre::Vector3::ZERO;

	mDashAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMinDashAccelerationFactor;
	mAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMinAccelerationFactor;

	mCyclicCharacter = false;
	mCyclicDirection = 1;
	mCyclicOffset = 0;
}

void PhysicsComponentCharacter::create()
{
	PhysicsComponent::create();

	if (!mPointRenderable)
	{
		mPointRenderable= Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->
			createPointRenderable(getSceneNode());
	}

	setNxOgreController(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene(), 
			mPointRenderable,			
			NxOgre::String(this->getParent()->getName().c_str()),
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

void PhysicsComponentCharacter::update(double elapsedSeconds)
{
	if(!getParent()->isEnabled())
	{
		mNextMovement=NxOgre::Vec3::ZERO;
	} 
	else if (isCyclicCharacter())
	{
		performCyclicMovement(elapsedSeconds);
	}
	else
	{
		performCharacterMovement(elapsedSeconds);
	}
}

void PhysicsComponentCharacter::performCyclicMovement(double elapsedSeconds)
{
	if (getParent()->isFirstUpdate())
	{
		return;
	}

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	mNextMovement = NxOgre::Vec3(0, Application::getInstance()->getPhysicsSubsystem()->mCyclicSpeed * mCyclicDirection, 0);
	mNextMovement *= Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;

	double cyclicLastPositionY = getNxOgreController()->getPosition().y;
	double sceneNodeLastPositionY = getSceneNode()->getPosition().y;

	getNxOgreController()->move(
		mNextMovement,
		collisionFlags,
		Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
		collisionFlags);

	//correctSceneNodePosition();

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

	//if (getParent()->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0)
	//{
	//	Logger::getInstance()->log("####################################");
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC NEW OFFSET: " + Ogre::StringConverter::toString(Ogre::Real(mCyclicOffset)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC NEW DIRECTION: " + Ogre::StringConverter::toString(Ogre::Real(mCyclicDirection)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC NEXT MOVEMENT: " + Ogre::StringConverter::toString(Ogre::Real(mNextMovement.y)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC LAST POSY: " + Ogre::StringConverter::toString(Ogre::Real(cyclicLastPositionY)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC NEW POSY: " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC SPEED: " + Ogre::StringConverter::toString(Ogre::Real(Application::getInstance()->getPhysicsSubsystem()->mCyclicSpeed)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC MUPS: " + Ogre::StringConverter::toString(Ogre::Real(Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond)));
	//	Logger::getInstance()->log("DIAMONDTREE CYCLIC ES: " + Ogre::StringConverter::toString(Ogre::Real(elapsedSeconds)));
	//}

	setLastMovement(mNextMovement);
	mNextMovement=NxOgre::Vec3::ZERO;
	mIsWalking=false;
}

void PhysicsComponentCharacter::performCharacterMovement(double elapsedSeconds)
{
	if(	mNextMovement==NxOgre::Vec3::ZERO && 
		mOnSurface && 
		!mJumping && 
		!mSliding && 
		!getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		setLastMovement(NxOgre::Vec3::ZERO);
		correctSceneNodePosition();

		//Logger::getInstance()->log(getParent()->getName() + " Not updated, position" + Ogre::StringConverter::toString(getSceneNode()->getPosition().y));
		return;
	}

	//Logger::getInstance()->log(getParent()->getName() + " updated, position " + Ogre::StringConverter::toString(getSceneNode()->getPosition().y));

	if (isInUse())
	{
		if(mIsWalking)
		{
			Vector3 mWalkDirection;
			mWalkDirection=Vector3(mNextMovement.x,0,mNextMovement.z);
			mWalkDirection.normalise();

			mNextMovement.x *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeed;
			mNextMovement.z *= Application::getInstance()->getPhysicsSubsystem()->mWalkSpeed;
		}

		// Scale next movement using time and speed
		if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			mNextMovement *= 
				Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * 
				elapsedSeconds;
		}

		if (mJumping)
		{
			mNextMovement.y += mJumpSpeed * elapsedSeconds;
		} 

		applyGravity(elapsedSeconds);

		// Perform last frame sliding displacement
		if (mSliding && mNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle)
		{
			mNextMovement = 
				mSlideDisplacement * 
				Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * 
				elapsedSeconds;

			resetSliding();
		}

		////////////////////////////////////////////////////////////////////////////
		// Applying global factor to displacement and calculate dash
		if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			calculateAngleDifference();

			if(mOnSurface)
			{
				calculateAcceleration(elapsedSeconds);
			}

			mNextMovement.x *= mAccelerationFactor;
			mNextMovement.z *= mAccelerationFactor;

			//Logger::getInstance()->log("Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale "+Ogre::StringConverter::toString(Ogre::Real(Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale)));
		}

		setCharactersDisplayYaw();

		if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			applyDash(elapsedSeconds);
			mNextMovement *= Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale;
		}

		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

		getNxOgreController()->move(
			mNextMovement,
			collisionFlags,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);

		correctSceneNodePosition();

		setOnSurface((collisionFlags & NxOgre::Enums::ControllerFlag_Down) ? true : false);

		//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		//{
		//	Logger::getInstance()->log("* * mNextMovement! "+Ogre::StringConverter::toString(Vector3(mNextMovement.x,mNextMovement.y,mNextMovement.z)));
		//	Logger::getInstance()->log("* * mOnSurface! "+Ogre::StringConverter::toString(mOnSurface));
		//}

		setLastMovement(mNextMovement);
		mNextMovement=NxOgre::Vec3::ZERO;
		mIsWalking=false;
	}
}

void PhysicsComponentCharacter::correctSceneNodePosition()
{
	getSceneNode()->setPosition(
		Vector3(getNxOgreController()->getPosition().x,
				getNxOgreController()->getPosition().y,
				getNxOgreController()->getPosition().z)
		+ mOffsetRenderPosition);
}

void PhysicsComponentCharacter::applyGravity(double elapsedSeconds)
{
	setFallSpeed(mFallSpeed + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * mFallTime);
	mFallTime += elapsedSeconds;
	mNextMovement.y += mFallSpeed * elapsedSeconds;

	//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	//{
	//	Logger::getInstance()->log("* * mNextMovementY! "+Ogre::StringConverter::toString(Ogre::Real(mNextMovement.y)));
	//	Logger::getInstance()->log("* * mFallTime! "+Ogre::StringConverter::toString(Ogre::Real(mFallTime)));
	//	Logger::getInstance()->log("* * mFallSpeed! "+Ogre::StringConverter::toString(Ogre::Real(mFallSpeed)));
	//}
}

bool PhysicsComponentCharacter::isMoving() const
{
	return (Ogre::Math::Abs(mNextMovement.x)>0.1 || Ogre::Math::Abs(mNextMovement.z)>0.1);
}	

void PhysicsComponentCharacter::walk()
{
	mIsWalking=true;
}

void PhysicsComponentCharacter::calculateAngleDifference()
{
	double mCurrentYaw;
	if(isMoving())
	{
		mCurrentYaw=getYawFromMovement(mNextMovement);
		mAngleDifference=Ogre::Math::Abs(mCurrentYaw-mLastYaw);
		mLastYaw=mCurrentYaw;
	}
}

void PhysicsComponentCharacter::calculateAcceleration(double elapsedSeconds)
{
	Vector3 mXZMovement;
	Vector3 mLastXZMovement;

	if(isMoving() && mIsNotApplyingDash && !mIsWalking)
	{
		if(mAngleDifference<Application::getInstance()->getPhysicsSubsystem()->mMaxSameDirectionAngle)
		{
			mXZMovement=Vector3(mNextMovement.x,0,mNextMovement.z);
			mLastXZMovement=Vector3(mLastMovement.x,0,mLastMovement.z);

			if(	mXZMovement.length()>=mLastXZMovement.length())
			{
				mAccelerationFactor+=mXZMovement.length()*elapsedSeconds*Application::getInstance()->getPhysicsSubsystem()->mAccelerationIncrement;

				if(mAccelerationFactor>Application::getInstance()->getPhysicsSubsystem()->mMaxAccelerationFactor)
				{
					mAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMaxAccelerationFactor;
				}
			}
			else
			{
				mAccelerationFactor-=(mLastXZMovement-mXZMovement).length()*elapsedSeconds*Application::getInstance()->getPhysicsSubsystem()->mAccelerationIncrement;
			}
		}
	}
	else
	{
		mAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMinAccelerationFactor;
	}
}

Vector3 PhysicsComponentCharacter::getDashMovement(double elapsedSeconds)
{
	double dashPower;
	Vector3 dashMovement;

	dashMovement = Vector3::ZERO;
	dashPower = 0;

	if(mDash > 0)
	{
		dashPower=elapsedSeconds*mDashAccelerationFactor*Application::getInstance()->getPhysicsSubsystem()->mDashFactor;
		mDashAccelerationFactor-=elapsedSeconds*Application::getInstance()->getPhysicsSubsystem()->mDashAccelerationIncrement;
		
		if(mDashAccelerationFactor<Application::getInstance()->getPhysicsSubsystem()->mMinDashAccelerationFactor)
		{
			mDashAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMinDashAccelerationFactor;
		}

		mDash-=dashPower;
		dashMovement = mDashDirection * dashPower;
	}

	if(mDash < 0.1)
	{
		mDashAccelerationFactor = Application::getInstance()->getPhysicsSubsystem()->mMinDashAccelerationFactor;
		mDash = 0;
		mIsNotApplyingDash = true;
	}
	else
	{
		mIsNotApplyingDash = false;
	}

	//Logger::getInstance()->log("dashMovement "+Ogre::StringConverter::toString(dashMovement));
	//Logger::getInstance()->log("mNextMovement "+Ogre::StringConverter::toString(Vector3(mNextMovement.x,mNextMovement.y,mNextMovement.z)));

	return dashMovement;
}

void PhysicsComponentCharacter::applyDash(double elapsedSeconds)
{
	if(isMoving())
	{
		if(mAngleDifference<Application::getInstance()->getPhysicsSubsystem()->mMaxSameDirectionAngle && mIsNotApplyingDash)
		{
			//same direction
			mDashAccelerationFactor+=elapsedSeconds*Application::getInstance()->getPhysicsSubsystem()->mDashAccelerationIncrement;

			if(mDashAccelerationFactor>Application::getInstance()->getPhysicsSubsystem()->mMaxDashAccelerationFactor*mAccelerationFactor)
			{
				mDashAccelerationFactor=Application::getInstance()->getPhysicsSubsystem()->mMaxDashAccelerationFactor*mAccelerationFactor;
			}

			mDash+=elapsedSeconds*Application::getInstance()->getPhysicsSubsystem()->mDashFactor;

			if(mDash > Application::getInstance()->getPhysicsSubsystem()->mDashMax)
			{
				mDash = Application::getInstance()->getPhysicsSubsystem()->mDashMax;
			}

			mDashDirection=Vector3(mNextMovement.x,0,mNextMovement.z);
			mDashDirection.normalise();

		}
		else
		{
			//different direction
			mNextMovement+=getDashMovement(elapsedSeconds);
		}
	}
	else
	{
		//different direction
		mNextMovement+=getDashMovement(elapsedSeconds);
	}

	//Logger::getInstance()->log("mDash "+Ogre::StringConverter::toString(Ogre::Real(mDash)));
	//Logger::getInstance()->log("mIsNotApplyingDash "+Ogre::StringConverter::toString(mIsNotApplyingDash));
}

void PhysicsComponentCharacter::jump()
{
	if(!mJumping && !mSliding && mOnSurface)
	{
		//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		//{
		//    Logger::getInstance()->log("* * INIT JUMP NORMAL");
		//}
		
		initJump();
	}
	else if(getParent()->getGameWorldManager()->getGodMode())
	{
		//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		//{
		//    Logger::getInstance()->log("* * INIT JUMP GOD MODE");
		//}

		initJump();
	}
}

double PhysicsComponentCharacter::getYawFromMovement(NxOgre::Vec3 movement)
{
	double characterYaw=getNxOgreController()->getDisplayYaw();

	if(mNextMovement.z<0 && mNextMovement.x<0)
	{
		characterYaw = Ogre::Math::ATan(mNextMovement.x/mNextMovement.z).valueDegrees();
	}
	else if(mNextMovement.z<0 && mNextMovement.x>0)
	{
		characterYaw = Ogre::Math::ATan(mNextMovement.x/mNextMovement.z).valueDegrees();
	}
	else if(mNextMovement.z>0 && mNextMovement.x>0)
	{
		characterYaw = Ogre::Math::ATan(mNextMovement.x/mNextMovement.z).valueDegrees();
		characterYaw+=180;
	}
	else if(mNextMovement.z>0 && mNextMovement.x<0)
	{
		characterYaw = Ogre::Math::ATan(mNextMovement.x/mNextMovement.z).valueDegrees();
		characterYaw+=180;
	}
	else if(mNextMovement.z!=0)
	{
		if(mNextMovement.z<0)
		{
			characterYaw=0;
		}
		else if(mNextMovement.z>0)
		{
			characterYaw=180;
		}
	}
	else if(mNextMovement.x!=0)
	{
		if(mNextMovement.x<0)
		{
			characterYaw=90;
		}
		else if(mNextMovement.x>0)
		{
			characterYaw=270;
		}
	}

	if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0 && (mNextMovement.x!=0 || mNextMovement.z!=0))
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

	return characterYaw;
}

void PhysicsComponentCharacter::setCharactersDisplayYaw()
{
	double characterYaw;
	characterYaw=getYawFromMovement(mNextMovement);
	getNxOgreController()->setDisplayYaw(characterYaw);
}

//void PhysicsComponentCharacter::setQueryFlags(QueryFlags queryFlags)
//{
//	unsigned int i;
//	for(i=0;i<getNxOgreBody()->getNxActor()->getShapes().size();i++)
//	{
//		getNxOgreBody()->getNxActor()->getShapes()[i]->setFlag(queryFlags);
//	}
//}

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

void PhysicsComponentCharacter::resetSliding()
{
	mSlideDisplacement = NxOgre::Vec3(0,0,0);
	mNormalAngle = 0;
	mSliding = false;
}

void PhysicsComponentCharacter::setSlidingValues(NxOgre::Vec3 pNormal, double pNormalAngle)
{
	//Logger::getInstance()->log("* * Setting sliding!");
	if(!getParent()->getGameWorldManager()->getGodMode())
	{
		if (pNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle && 
			pNormalAngle < Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngleFall)
		{
			mSliding = true;
			mNormalAngle = pNormalAngle;

			//TODO ADJUST THIS VALUES
			//mSlideDisplacement.x = pNormal.x;
			//mSlideDisplacement.y = -pNormal.y * Application::getInstance()->getPhysicsSubsystem()->mSlidingFactor;
			//mSlideDisplacement.z = pNormal.z;

			//TEST THIS
			mSlideDisplacement.x = pNormal.x * Application::getInstance()->getPhysicsSubsystem()->mSlidingFactor;
			mSlideDisplacement.y = 0;
			mSlideDisplacement.z = pNormal.z * Application::getInstance()->getPhysicsSubsystem()->mSlidingFactor;
		}

		if(mSlideDisplacement.y > 0)
		{
			mSlideDisplacement.y = 0;
		}
	}
}

void PhysicsComponentCharacter::initJump()
{
	mJumping = true;
	mJumpSpeed = Application::getInstance()->getPhysicsSubsystem()->mInitialJumpSpeed;

	//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	//{
	//	Logger::getInstance()->log("* * INIT FALL JUMP");
	//}

	initFall();
}

void PhysicsComponentCharacter::initFall()
{
	mFalling = true;
	mFallTime = 0;
	mFallSpeed = 0;
}

void PhysicsComponentCharacter::setJumpSpeed(double pJumpSpeed)
{
	mJumpSpeed = pJumpSpeed;

	if(mJumpSpeed>Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond)
	{
		mJumpSpeed=Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond;
	}
}

void PhysicsComponentCharacter::setFallSpeed(double pFallSpeed)
{
	mFallSpeed = pFallSpeed;
	
	if(mFallSpeed <= -Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecondInverseScaled)
	{
		mFallingLimit = true;
		mFallSpeed = -Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecondInverseScaled;
	}
	else
	{
		mFallingLimit = false;
	}
}

void PhysicsComponentCharacter::setOnSurface(bool pOnSurface)
{
	//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	//{
	//	Logger::getInstance()->log("* * PositionY! " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)));
	//	Logger::getInstance()->log("* * minSurfaceY! " + Ogre::StringConverter::toString(Ogre::Real(Application::getInstance()->getPhysicsSubsystem()->mSurfaceMinY)));
	//}

	//HACK TO AVOID GOD MODE FALLING BUG (PROVISIONAL)
	if (mNextMovement.y < 0)
	{
		Vector3 rayCastResult;
		Ogre::uint32 collisionType;
		bool pCollision = false;

		Vector3 position = getNxOgreController()->getPosition().as<Vector3>();
		position.y += 1;

		Vector3 direction(0,-1,-0);

		pCollision = Application::getInstance()->getRayCasting()->
			raycastPhysicsClosestGeometry(
				position,
				direction,
				rayCastResult,
				collisionType,
				100);

		if (!pCollision)
		{
			getNxOgreController()->setPosition(
			NxOgre::Vec3(	getNxOgreController()->getPosition().x,
							getNxOgreController()->getPosition().y - 0.1,
							getNxOgreController()->getPosition().z));

			correctSceneNodePosition();

			//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
			//{
			//	Logger::getInstance()->log("* * GOD MODE HACK :: NO COLLISION");
			//	Logger::getInstance()->log("* * New PositionY! " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)));
			//}

			return;
		}
		//else
		//{
			//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
			//{
			//	Logger::getInstance()->log("* * GOD MODE HACK :: COLLISION");
			//	Logger::getInstance()->log("* * RayCastPositionY! " + Ogre::StringConverter::toString(Ogre::Real(rayCastResult.y)));
			//	Logger::getInstance()->log("* * New PositionY! " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)));
			//}
		//}
	}

	mOnSurface=pOnSurface;

	if (pOnSurface)
	{
		mJumping = false;
		
		//if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		//{
		//	Logger::getInstance()->log("* * PositionY! " + Ogre::StringConverter::toString(Ogre::Real(getNxOgreController()->getPosition().y)));
		//	Logger::getInstance()->log("* * INIT FALL SET ON SURFACE");
		//}

		initFall();
	}
}

void PhysicsComponentCharacter::setNextMovement(NxOgre::Vec3 nextMovement)
{
	mNextMovement=nextMovement;
}

NxOgre::Vec3 PhysicsComponentCharacter::getNextMovement()
{
	return mNextMovement;
}

void PhysicsComponentCharacter::setLastMovement(NxOgre::Vec3 lastMovement)
{
	mLastMovement=lastMovement;
}

NxOgre::Vec3 PhysicsComponentCharacter::getLastMovement()
{
	return mLastMovement;
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
	return mFallingLimit;
}

bool PhysicsComponentCharacter::isSliding() const
{
	return mSliding;
}

bool PhysicsComponentCharacter::isOnSurface() const
{
	return mOnSurface;
}

void PhysicsComponentCharacter::setOffsetRenderPosition(Vector3 offsetRenderPosition)
{
	mOffsetRenderPosition=offsetRenderPosition;
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

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{

}