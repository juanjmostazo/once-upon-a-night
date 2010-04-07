#include "GameObjectCarnivorousPlant.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectCarnivorousPlant::GameObjectCarnivorousPlant(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CARNIVOROUSPLANT)
{

}

GameObjectCarnivorousPlant::~GameObjectCarnivorousPlant()
{

}

void GameObjectCarnivorousPlant::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectCarnivorousPlant::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectCarnivorousPlant::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectCarnivorousPlant::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectCarnivorousPlant::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectCarnivorousPlant::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectCarnivorousPlant::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectCarnivorousPlant::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectCarnivorousPlant::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectCarnivorousPlant::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectCarnivorousPlant::update(double elapsedSeconds)
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

void GameObjectCarnivorousPlant::reset()
{
	GameObject::reset();
}

void GameObjectCarnivorousPlant::changeWorld(int world)
{
	if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}
	switch(world)
	{
	case DREAMS:
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityNightmares->setVisible(false);
		break;
	case NIGHTMARES:
		mRenderComponentEntityDreams->setVisible(false);
		mRenderComponentEntityNightmares->setVisible(true);
		break;
	default:break;
	}
}
bool GameObjectCarnivorousPlant::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectCarnivorousPlant::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectCarnivorousPlantParameters::TGameObjectCarnivorousPlantParameters() : TGameObjectParameters()
{

}

TGameObjectCarnivorousPlantParameters::~TGameObjectCarnivorousPlantParameters()
{

}