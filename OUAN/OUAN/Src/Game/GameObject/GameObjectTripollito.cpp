#include "GameObjectTripollito.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTripollito::GameObjectTripollito(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLITO)
{

}

GameObjectTripollito::~GameObjectTripollito()
{

}

void GameObjectTripollito::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTripollito::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTripollito::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTripollito::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTripollito::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripollito::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTripollito::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTripollito::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTripollito::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollito::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectTripollito::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

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

void GameObjectTripollito::reset()
{
	GameObject::reset();

	changeWorld(DREAMS);

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
	}
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
	}
}

void GameObjectTripollito::changeWorld(int world)
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

bool GameObjectTripollito::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTripollito::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectTripollitoParameters::TGameObjectTripollitoParameters() : TGameObjectParameters()
{

}

TGameObjectTripollitoParameters::~TGameObjectTripollitoParameters()
{

}