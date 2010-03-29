#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ONY)
{
	mHitRecoveryTime=HIT_RECOVERY_TIME;
}

GameObjectOny::~GameObjectOny()
{

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
	if (mHitRecoveryTime>=0)
		mHitRecoveryTime-=elapsedSeconds*1000000;
	GameObject::update(elapsedSeconds);

	//TODO THIS SHOULD BE DONE IN A GENERAL WAY IN THE PHYSICSSUBSYSTEM::UPDATE
	mPhysicsComponentCharacter->update(elapsedSeconds);
}

void GameObjectOny::changeWorld(int world)
{
	if (!isEnabled()) return;

	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
}
void GameObjectOny::decreaseHP(int amount)
{
	if (mHitRecoveryTime<=0)
	{
		GameObject::decreaseHP();
		mHitRecoveryTime=HIT_RECOVERY_TIME;
	}
}

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
