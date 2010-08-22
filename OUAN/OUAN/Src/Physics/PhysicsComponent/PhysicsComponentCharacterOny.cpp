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