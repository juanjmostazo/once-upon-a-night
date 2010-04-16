#include "PhysicsComponentCharacter.h"
using namespace OUAN;

PhysicsComponentCharacter::PhysicsComponentCharacter(const std::string& type)
:PhysicsComponent(type)
{
	mNextMovement = NxOgre::Vec3(0,0,0);
	mLastMovement = NxOgre::Vec3::ZERO;

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

	NxOgre::String name=NxOgre::String(this->getParent()->getName().c_str());
	
	//Ogre::LogManager::getSingleton().logMessage("Creating character " + getParent()->getName() + ". Initial yaw: " + Ogre::StringConverter::toString(Ogre::Real(getSceneNode()->getOrientation().getYaw().valueRadians())));

	setNxOgreController(
		Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->createCapsuleController(
			getNxOgreControllerDescription(), 
			getNxOgreSize(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreScene(), 
			Application::getInstance()->getPhysicsSubsystem()->getNxOgreRenderSystem()->
				createPointRenderable(getSceneNode()),			
			name,
			getMass(),
			getSceneNode()->getOrientation().getYaw().valueDegrees()));
}

void PhysicsComponentCharacter::destroy()
{
	PhysicsComponent::destroy();
	Application::getInstance()->getPhysicsSubsystem()->getNxOgreControllerManager()->destroyController(getNxOgreController());
}

void PhysicsComponentCharacter::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	if (mNextMovement!=Vector3::ZERO)
	{
		// Scale next movement using time and speed
		if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
		{
			mNextMovement=mNextMovement+mNextMovement * Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;
		}
		// Apply gravity
		mNextMovement+=Application::getInstance()->getPhysicsSubsystem()->mGravity * elapsedSeconds;
	}

	if (mJumping)
	{
		setJumpSpeed(mJumpSpeed + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * mJumpTime);
		mJumpTime += elapsedSeconds;
		mNextMovement.y += mJumpSpeed * elapsedSeconds - 0.5f * Application::getInstance()->getPhysicsSubsystem()->mGravity.y * elapsedSeconds * elapsedSeconds;
	} 
	else if (mFalling) 
	{
		setFallSpeed(mFallSpeed + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * mFallTime);
		mFallTime += elapsedSeconds;
		mNextMovement.y += mFallSpeed * elapsedSeconds - 0.5f * Application::getInstance()->getPhysicsSubsystem()->mGravity.y * elapsedSeconds * elapsedSeconds;
	}

	// Perform last frame sliding displacement
	if (mSliding && mNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle)
	{
		mNextMovement += mSlideDisplacement * Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * elapsedSeconds;
		resetSliding();
	}

	////////////////////////////////////////////////////////////////////////////
	// Applying global factor to displacement
	if(getParent()->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		mNextMovement *= Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale;
	}

	if (isInUse())
	{

		setCharactersDisplayYaw();


		getNxOgreController()->move(
			mNextMovement,
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
	
	//Set movement to zero for the next frame
	mNextMovement=Vector3::ZERO;
}

void PhysicsComponentCharacter::setCharactersDisplayYaw()
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
	/*
	if(characterYaw!=getNxOgreController()->getDisplayYaw())
	{
		Ogre::LogManager::getSingleton().logMessage("mNextMovement "+Ogre::StringConverter::toString(mNextMovement.x)+" "
																	+Ogre::StringConverter::toString(mNextMovement.z));
		Ogre::LogManager::getSingleton().logMessage("characterYaw "+Ogre::StringConverter::toString(Ogre::Real(characterYaw)));
	}
	*/
	getNxOgreController()->setDisplayYaw(characterYaw);
}

void PhysicsComponentCharacter::setQueryFlags(QueryFlags queryFlags)
{
	//unsigned int i;
	//for(i=0;i<getNxOgreBody()->getNxActor()->getShapes().size();i++)
	//{
	//	getNxOgreBody()->getNxActor()->getShapes()[i]->setFlag(queryFlags);
	//}
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

	if (pNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngle)
	{
		mSliding = true;
		mNormalAngle = pNormalAngle;

		mSlideDisplacement.x = pNormal.x;
		mSlideDisplacement.y = -pNormal.y * Application::getInstance()->getPhysicsSubsystem()->mSlidingFactor;
		mSlideDisplacement.z = pNormal.z;
		
		if (pNormalAngle > Application::getInstance()->getPhysicsSubsystem()->mMinSlidingAngleFall)
		{
			mSlideDisplacement.y *= Application::getInstance()->getPhysicsSubsystem()->mSlidingFactorFall;
		}
	}
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

TPhysicsComponentCharacterParameters::TPhysicsComponentCharacterParameters() : TPhysicsComponentParameters()
{

}

TPhysicsComponentCharacterParameters::~TPhysicsComponentCharacterParameters()
{

}