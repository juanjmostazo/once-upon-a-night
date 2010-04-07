#include "GameObjectScaredPlant.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectScaredPlant::GameObjectScaredPlant(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SCAREDPLANT)
{

}

GameObjectScaredPlant::~GameObjectScaredPlant()
{

}

RenderComponentEntityPtr GameObjectScaredPlant::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectScaredPlant::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

void GameObjectScaredPlant::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectScaredPlant::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectScaredPlant::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectScaredPlant::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectScaredPlant::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectScaredPlant::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectScaredPlant::update(double elapsedSeconds)
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

void GameObjectScaredPlant::reset()
{
	GameObject::reset();

	if (!mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}

	mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
}

void GameObjectScaredPlant::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
		mRenderComponentEntityDreams->setVisible(false);
		break;
	case NIGHTMARES:
		if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}
		mRenderComponentEntityDreams->setVisible(true);
		break;
	default:break;
	}
}
bool GameObjectScaredPlant::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectScaredPlant::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------

TGameObjectScaredPlantParameters::TGameObjectScaredPlantParameters() : TGameObjectParameters()
{

}

TGameObjectScaredPlantParameters::~TGameObjectScaredPlantParameters()
{

}