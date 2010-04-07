#include "GameObjectNightGoblin.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectNightGoblin::GameObjectNightGoblin(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CRYKING)
{

}

GameObjectNightGoblin::~GameObjectNightGoblin()
{

}

void GameObjectNightGoblin::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectNightGoblin::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectNightGoblin::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectNightGoblin::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectNightGoblin::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectNightGoblin::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectNightGoblin::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectNightGoblin::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectNightGoblin::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectNightGoblin::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectNightGoblin::update(double elapsedSeconds)
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

void GameObjectNightGoblin::reset()
{
	GameObject::reset();
}

void GameObjectNightGoblin::changeWorld(int world)
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
bool GameObjectNightGoblin::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectNightGoblin::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectNightGoblinParameters::TGameObjectNightGoblinParameters() : TGameObjectParameters()
{

}

TGameObjectNightGoblinParameters::~TGameObjectNightGoblinParameters()
{

}