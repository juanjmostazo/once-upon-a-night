#include "GameObjectEye.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectEye::GameObjectEye(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_EYE)
{

}

GameObjectEye::~GameObjectEye()
{

}

RenderComponentEntityPtr GameObjectEye::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectEye::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

void GameObjectEye::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectEye::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectEye::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectEye::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
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

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		getPhysicsComponentCharacter()->getNxOgreController()->move(
			Application::getInstance()->getPhysicsSubsystem()->mGravity * 
			Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
			GROUP_COLLIDABLE_MASK,
			Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
			collisionFlags);
	}
}

void GameObjectEye::reset()
{
	GameObject::reset();
}

void GameObjectEye::changeWorld(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
		mRenderComponentEntityNightmares->setVisible(false);
		break;
	case NIGHTMARES:
		if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}
		mRenderComponentEntityNightmares->setVisible(true);
		break;
	default:break;
	}
}
bool GameObjectEye::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectEye::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------

TGameObjectEyeParameters::TGameObjectEyeParameters() : TGameObjectParameters()
{

}

TGameObjectEyeParameters::~TGameObjectEyeParameters()
{

}