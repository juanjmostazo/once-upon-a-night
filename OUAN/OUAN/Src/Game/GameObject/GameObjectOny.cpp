#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ONY)
{
	mHitRecoveryTime=-1;
}

GameObjectOny::~GameObjectOny()
{

}

void GameObjectOny::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectOny::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectOny::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectOny::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
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
	{
		mHitRecoveryTime-=elapsedSeconds*1000;
	}

	GameObject::update(elapsedSeconds);

	mPhysicsComponentCharacter->update(elapsedSeconds);

	if (mPhysicsComponentCharacter->getNxOgreController()->getPosition().y < 
		Application::getInstance()->getPhysicsSubsystem()->mMinAllowedY)
	{
		OnyFallsEventPtr evt(new OnyFallsEvent());
		mGameWorldManager->addEvent(evt);
	}
}

void GameObjectOny::reset()
{
	GameObject::reset();

	if (!mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}

	mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
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

void GameObjectOny::setMaxHP()
{
	getLogicComponent()->setHealthPoints(getLogicComponent()->getInitialHealthPoints());
}

void GameObjectOny::increaseWeaponPower(int powerUnits)
{
	//TODO: WEAPONS NEEDED
}

void GameObjectOny::decreaseWeaponPower(int powerUnits)
{
	//TODO: WEAPONS NEEDED
}

void GameObjectOny::die()
{
	GameOverEventPtr evt=GameOverEventPtr(new GameOverEvent(false));
	mGameWorldManager->addEvent(evt);
}

void GameObjectOny::loseLife()
{
	GameObject::loseLife();
	OnyDiesEventPtr evt=OnyDiesEventPtr(new OnyDiesEvent(getLogicComponent()->getNumLives()));
	mGameWorldManager->addEvent(evt);
}

bool GameObjectOny::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectOny::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

//-------

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
