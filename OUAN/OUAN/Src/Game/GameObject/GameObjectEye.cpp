#include "GameObjectEye.h"

using namespace OUAN;

GameObjectEye::GameObjectEye(const std::string& name)
:GameObject(name)
{

}

GameObjectEye::~GameObjectEye()
{

}

RenderComponentEntityPtr GameObjectEye::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectEye::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectEye::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectEye::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectEye::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectEye::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectEye::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	getPhysicsComponentCharacter()->getNxOgreController()->move(
		Application::getInstance()->getPhysicsSubsystem()->mGravity * 
			Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
		GROUP_COLLIDABLE_MASK,
		Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
		collisionFlags);
}

void GameObjectEye::setDreamsMode()
{
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
}

void GameObjectEye::setNightmaresMode()
{

}

TGameObjectEyeParameters::TGameObjectEyeParameters() : TGameObjectParameters()
{

}

TGameObjectEyeParameters::~TGameObjectEyeParameters()
{

}