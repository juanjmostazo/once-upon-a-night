#include "GameObjectDragon.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectDragon::GameObjectDragon(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DRAGON)
{

}

GameObjectDragon::~GameObjectDragon()
{

}

void GameObjectDragon::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDragon::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDragon::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDragon::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDragon::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDragon::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDragon::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDragon::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectDragon::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectDragon::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectDragon::update(double elapsedSeconds)
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

void GameObjectDragon::reset()
{
	GameObject::reset();

	changeWorld(DREAMS);

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
	}
}

void GameObjectDragon::changeWorld(int world)
{
	if (!isEnabled()) return;

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

int GameObjectDragon::getTimeStunned() const
{
	//TODO: Define somewhere a stunned counter for the dragon and update
	// it accordingly; then, use that value here
	return 0;
}
bool GameObjectDragon::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectDragon::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectDragonParameters::TGameObjectDragonParameters() : TGameObjectParameters()
{

}

TGameObjectDragonParameters::~TGameObjectDragonParameters()
{

}