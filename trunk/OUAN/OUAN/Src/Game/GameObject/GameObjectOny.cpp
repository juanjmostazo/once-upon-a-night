#include "GameObjectOny.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name)
{
	mMovementFlags = MOV_NOWHERE;
	mJumping = false;
	mJumpTime = 0;
	mJumpSpeed = 0;
}

GameObjectOny::~GameObjectOny()
{

}

int GameObjectOny::getMovementFlags() const
{
	return mMovementFlags;
}

void GameObjectOny::setMovementFlags(int pMovementFlags)
{
	mMovementFlags=pMovementFlags;
}

bool GameObjectOny::isJumping() const
{
	return mJumping;
}

void GameObjectOny::setJumping(bool pJumping)
{
	mJumping=pJumping;
}

double GameObjectOny::getJumpTime() const
{
	return mJumpTime;
}

void GameObjectOny::setJumpTime(double pJumpTime)
{
	mJumpTime=pJumpTime;
}

double GameObjectOny::getJumpSpeed() const
{
	return mJumpSpeed;
}

void GameObjectOny::setJumpSpeed(double pJumpSpeed)
{
	mJumpSpeed=pJumpSpeed;
}

void GameObjectOny::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectOny::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectOny::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectOny::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectOny::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectOny::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectOny::update(double elapsedSeconds)
{
	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTime = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Advancing " + elapsedTime + " seconds");

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
	int movementFlags = getMovementFlags();

	// Initial displacement vector: gravity
	NxOgre::Vec3 mDisplacement(Application::getInstance()->getPhysicsSubsystem()->mGravity * elapsedSeconds);

	// Movement forces
	if (movementFlags > 0)
	{
		// Advance stuff
		if ((movementFlags & MOV_FORWARD_OR_BACK) > 0)
		{	
			double way = ((movementFlags & MOV_GO_FORWARD) > 0) ? 1.0f : -1.0f;
			mDisplacement += Ogre::Vector3::UNIT_Z * Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond * way * elapsedSeconds;
		}

		// Turn stuff
		if ((movementFlags & MOV_LEFT_OR_RIGHT) > 0)
		{
			double offsetYaw = ((movementFlags & MOV_GO_LEFT) > 0) ? 
				Application::getInstance()->getPhysicsSubsystem()->mTurnDegreesPerSecond : 
				-Application::getInstance()->getPhysicsSubsystem()->mTurnDegreesPerSecond;
			offsetYaw *= elapsedSeconds;

			getPhysicsComponentCharacter()->getNxOgreController()->setDisplayYaw(
				getPhysicsComponentCharacter()->getNxOgreController()->getDisplayYaw() + offsetYaw);
		}

		// Jump stuff
		if ((movementFlags & MOV_JUMP) > 0 && !isJumping())
		{
			Ogre::LogManager::getSingleton().logMessage("Jump!"); 
			setJumping(true);
			setJumpTime(0);
			setJumpSpeed(Application::getInstance()->getPhysicsSubsystem()->mInitialJumpSpeed);
		}

		// Calculates the current displacement from position and angle
		mDisplacement = Ogre::Quaternion(
			Ogre::Degree(getPhysicsComponentCharacter()->getNxOgreController()->getDisplayYaw()), 
			Ogre::Vector3::UNIT_Y) * 
			mDisplacement.as<Ogre::Vector3>();
	}

	// If it's jumping, calculate height and apply vertical displacement
	if (isJumping())
	{
		setJumpSpeed(getJumpSpeed() + Application::getInstance()->getPhysicsSubsystem()->mGravity.y * getJumpTime());
		setJumpTime(getJumpTime() + elapsedSeconds);
		mDisplacement.y += getJumpSpeed() * elapsedSeconds - 0.5f * Application::getInstance()->getPhysicsSubsystem()->mGravity.y * elapsedSeconds * elapsedSeconds;
	}

	////////////////////////////////////////////////////////////////////////////

	// Applying global factor to displacement
	mDisplacement *= Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale;

	getPhysicsComponentCharacter()->getNxOgreController()->move(
		mDisplacement,
		GROUP_COLLIDABLE_MASK,
		Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
		collisionFlags);

	if(collisionFlags & NxOgre::Enums::ControllerFlag_Down)
	{
		setJumping(false);
	}
}

void GameObjectOny::setDreamsMode()
{
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
}

void GameObjectOny::setNightmaresMode()
{

}

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}