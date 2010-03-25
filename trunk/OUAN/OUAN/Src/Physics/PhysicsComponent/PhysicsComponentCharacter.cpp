#include "PhysicsComponentCharacter.h"
using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(type)
{
	mMovementFlags = MOV_NOWHERE;

	mJumping = false;
	mFalling = true;
	mSliding = false;
	mOnSurface = false;

	mJumpTime = 0;
	mFallTime = 0;

	mJumpSpeed = 0;
	mFallSpeed = 0;
	mSlideDisplacement = NxOgre::Vec3(0,0,0);
	mNormalAngle = 0;
}

PhysicsComponentCharacter::~PhysicsComponentCharacter()
{

}

void PhysicsComponentCharacter::create()
{
	PhysicsComponent::create();
	
	setNxOgreController(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->
				createPointRenderable(getSceneNode())));

	//TODO SET SCENE NODE ORIENTATION SOMEHOW
}

void PhysicsComponentCharacter::destroy()
{
	PhysicsComponent::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->destroyController(getNxOgreController());
}

void PhysicsComponentCharacter::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	// Initial displacement vector: gravity
	NxOgre::Vec3 mDisplacement(Application::getInstance()->getPhysicsSubsystem()->mGravity * elapsedSeconds);

	// Movement forces
	if (mMovementFlags > 0)
	{
		// Advance stuff
		if ((mMovementFlags & MOV_FORWARD_OR_BACK) > 0)
		{	
			double way = ((mMovementFlags & MOV_GO_FORWARD) > 0) ? 1.0f : -1.0f;
			mDisplacement += Ogre::Vector3::UNIT_Z * Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * way * elapsedSeconds;
		}

		// Turn stuff
		if ((mMovementFlags & MOV_LEFT_OR_RIGHT) > 0)
		{
			double offsetYaw = ((mMovementFlags & MOV_GO_LEFT) > 0) ? 
				Application::getInstance()->getPhysicsSubsystem()->mTurnDegreesPerSecond : 
			-Application::getInstance()->getPhysicsSubsystem()->mTurnDegreesPerSecond;
			offsetYaw *= elapsedSeconds;

			getNxOgreController()->setDisplayYaw(getNxOgreController()->getDisplayYaw() + offsetYaw);
		}

		// Jump stuff
		if ((mMovementFlags & MOV_JUMP) > 0 && !mJumping && mOnSurface)
		{
			Ogre::LogManager::getSingleton().logMessage("Jump!"); 
			initJump();
		} 

		// Calculates the current displacement from position and angle
		mDisplacement = Ogre::Quaternion(
			Ogre::Degree(getNxOgreController()->getDisplayYaw()), 
			Ogre::Vector3::UNIT_Y) * 
			mDisplacement.as<Ogre::Vector3>();
	}

	if (mJumping)
	{
		setJumpSpeed(mJumpSpeed + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * mJumpTime);
		mJumpTime += elapsedSeconds;
		mDisplacement.y += mJumpSpeed * elapsedSeconds - 0.5f * Application::getInstance()->getPhysicsSubsystem()->mGravity.y * elapsedSeconds * elapsedSeconds;
	} 
	else if (mFalling) 
	{
		setFallSpeed(mFallSpeed + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * mFallTime);
		mFallTime += elapsedSeconds;
		mDisplacement.y += mFallSpeed * elapsedSeconds - 0.5f * Application::getInstance()->getPhysicsSubsystem()->mGravity.y * elapsedSeconds * elapsedSeconds;
	}

	// Perform last frame sliding displacement
	if (mSliding && mNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle)
	{
		mDisplacement += mSlideDisplacement * Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;
		resetSliding();
	}

	////////////////////////////////////////////////////////////////////////////
	// Applying global factor to displacement
	mDisplacement *= Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale;

	if (isInUse())
	{
		getNxOgreController()->move(
			mDisplacement,
			GROUP_COLLIDABLE_MASK,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);

		//Ogre::LogManager::getSingleton().logMessage("* * Moving!");
	}

	if(collisionFlags & NxOgre::Enums::ControllerFlag_Down)
	{
		setOnSurface(true);
	}
	else
	{
		setOnSurface(false);
	}

	if (getNxOgreController()->getPosition().y < Application::getInstance()->getPhysicsSubsystem()->mMinAllowedY){
		Application::getInstance()->getGameWorldManager()->setGameOver(true);
		Application::getInstance()->getGameWorldManager()->setGameBeaten(false);
	}
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

void PhysicsComponentCharacter::resetSliding()
{
	mSlideDisplacement = NxOgre::Vec3(0,0,0);
	mNormalAngle = 0;
	mSliding = false;
}

void PhysicsComponentCharacter::setSlidingValues(NxOgre::Vec3 pNormal, double pNormalAngle)
{
	//Ogre::LogManager::getSingleton().logMessage("* * Setting sliding!");

	mSlideDisplacement.x = pNormal.x;
	mSlideDisplacement.y = -pNormal.y * Application::getInstance()->getPhysicsSubsystem()->mSlidingFactor;
	mSlideDisplacement.z = pNormal.z;

	mNormalAngle = pNormalAngle;

	mSliding = true;
}

void PhysicsComponentCharacter::initJump()
{
	mJumping = true;
	mJumpTime = 0;
	mJumpSpeed = Application::getInstance()->getPhysicsSubsystem()->mInitialJumpSpeed;
}

void PhysicsComponentCharacter::initFall()
{
	mFalling = true;
	mFallTime = 0;
	mFallSpeed = 0;
}

void PhysicsComponentCharacter::setJumpSpeed(double pJumpSpeed)
{
	mJumpSpeed = pJumpSpeed < Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond ?
		pJumpSpeed : Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond;
}

void PhysicsComponentCharacter::setFallSpeed(double pFallSpeed)
{
	mFallSpeed = pFallSpeed < Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond ?
		pFallSpeed : Application::getInstance()->getPhysicsSubsystem()->mMovementLimitUnitsPerSecond;
}

void PhysicsComponentCharacter::setOnSurface(bool pOnSurface)
{
	mOnSurface=pOnSurface;

	if (pOnSurface)
	{
		mJumping = false;
		initFall();
	}
}

void PhysicsComponentCharacter::setMovementFlags(int pMovementFlags)
{
	mMovementFlags=pMovementFlags;
}

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{

}