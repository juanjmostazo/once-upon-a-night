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

void GameObjectOny::setDreamsMode()
{

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