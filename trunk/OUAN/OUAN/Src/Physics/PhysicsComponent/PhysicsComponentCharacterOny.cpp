#include "OUAN_Precompiled.h"

#include "PhysicsComponentCharacterOny.h"
#include "../../Game/GameObject/GameObjectOny.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Graphics/CameraManager/CameraManager.h"

using namespace OUAN;

PhysicsComponentCharacterOny::PhysicsComponentCharacterOny(const std::string& type)
:PhysicsComponentCharacter(type)
{
	reset();
}

PhysicsComponentCharacterOny::~PhysicsComponentCharacterOny()
{
	
}

void PhysicsComponentCharacterOny::reset()
{
	PhysicsComponentCharacter::reset();
	mApplyGravityNextFrame=true;
}

void PhysicsComponentCharacterOny::update(double elapsedSeconds)
{
	PhysicsComponentCharacter::update(elapsedSeconds);
	GameObjectOnyPtr ony = BOOST_PTR_CAST(GameObjectOny,mParent);

	if (ony.get())		
	{
		//Use a facade method to prevent a dependency
		//between the logic and physics component
		int onyState = ony->getLogicCurrentState();
		int newState = 0;	
		if (isFalling())
		{
			if (!CHECK_BIT(onyState,ONY_STATE_BIT_FIELD_FALL))
			{
				newState = SET_BIT(onyState,ONY_STATE_BIT_FIELD_FALL);
				ony->setLogicNewState(newState);
			}
		}
		else
		{
			if (CHECK_BIT(onyState,ONY_STATE_BIT_FIELD_FALL))
			{
				newState = CLEAR_BIT(onyState,ONY_STATE_BIT_FIELD_FALL);
				ony->setLogicNewState(newState);
			}
		}
	}
	mApplyGravityNextFrame=true;
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

void PhysicsComponentCharacterOny::applyFallY(double elapsedSeconds)
{
	double initialTime = mFallingTime;
	double finalTime = mFallingTime + elapsedSeconds;

	if(!mFlyingCharacter && mApplyGravityNextFrame)
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

void PhysicsComponentCharacterOny::disactivateGravityNextFrame()
{
	mApplyGravityNextFrame=false;
}

void PhysicsComponentCharacterOny::applyOuternMovement(double elapsedSeconds)
{
	Application* app=Application::getInstance();
	if (app->isPlayingCutscene())
	{
		setNextMovement(getOuternMovement());
	}
	else
		setNextMovement(app->getCameraManager()->rotateMovementVector(getOuternMovement(), elapsedSeconds));
}

TPhysicsComponentCharacterOnyParameters::TPhysicsComponentCharacterOnyParameters() : TPhysicsComponentCharacterParameters()
{

}

TPhysicsComponentCharacterOnyParameters::~TPhysicsComponentCharacterOnyParameters()
{

}