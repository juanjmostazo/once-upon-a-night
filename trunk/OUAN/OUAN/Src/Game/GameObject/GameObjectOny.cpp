#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ONY)
{
	mDreamsWeapon="pillow#1";
	mNightmaresWeapon="flashlight#1";
	mIdleTime=-1;
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

PhysicsComponentCharacterPtr GameObjectOny::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectOny::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isFirstUpdate())
	{
		mLogicComponentOny->setState(ONY_STATE_IDLE);
		mIdleTime=0;
	}	
	int currentState=mLogicComponentOny->getState();
	int lastState=mLogicComponentOny->getOldState();
	
	if (currentState==ONY_STATE_IDLE)
	{
		if (mLogicComponentOny->isStateChanged())
		{
			mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE01);
			mIdleTime=0.0;
		}
		else
		{
			mIdleTime+=elapsedSeconds;
			if (mIdleTime>=IDLE_SECONDS_TO_NAP)
			{
				if (mRenderComponentEntity->getCurrentAnimationName().compare(ONY_ANIM_IDLE02)!=0)
					mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE02);
			}
		}
		//TODO: other cases
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP))
	{
		if (mLogicComponentOny->isStateChanged() && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP))
			mRenderComponentEntity->changeAnimation(ONY_ANIM_JUMP);			
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_MOVEMENT))
	{
		if (mLogicComponentOny->isStateChanged())			
		{
			if (!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_MOVEMENT)) //beginning movement
				mRenderComponentEntity->changeAnimation(CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK)?ONY_ANIM_WALK:ONY_ANIM_RUN);
			else //Walk/run toggle
			{
				bool toWalk=CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_WALK);
				bool toRun=CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_WALK) && !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK);
				bool fromJump = !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP) && CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP);
				if (toWalk || toRun || fromJump)
				{
					mRenderComponentEntity->changeAnimation(CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK)?ONY_ANIM_WALK:ONY_ANIM_RUN);
				}
			}
		}
	}

	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_HIT) && 
		!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_HIT) && 
		mRenderComponentEntity->getCurrentAnimationName().compare(ONY_ANIM_HIT01)!=0)
	{
		mRenderComponentEntity->changeAnimation(ONY_ANIM_HIT01);
	}

	mRenderComponentEntity->update(elapsedSeconds);
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

	changeWorld(DREAMS);

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
	}
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
	}
}

void GameObjectOny::changeWorld(int world)
{
	if (isEnabled())
	{
		if(mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}

		mWeaponComponent->changeActiveWeapon((world==DREAMS)?mDreamsWeapon:mNightmaresWeapon);
		mWeaponComponent->updateAttackType();
		mWeaponComponent->switchOff();
	}
}
void GameObjectOny::setLogicComponentOny(LogicComponentOnyPtr pLogicComponentOny)
{
	mLogicComponentOny=pLogicComponentOny;
}

LogicComponentOnyPtr GameObjectOny::getLogicComponentOny()
{
	return mLogicComponentOny;
}
void GameObjectOny::increaseWeaponPower(int powerUnits)
{
	if (mWeaponComponent.get())
		mWeaponComponent->increaseWeaponPower(powerUnits);
}

void GameObjectOny::decreaseWeaponPower(int powerUnits)
{
	if (mWeaponComponent.get())
		mWeaponComponent->decreaseWeaponPower(powerUnits);
}

bool GameObjectOny::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectOny::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectOny::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectOny::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}

void GameObjectOny::setWeaponComponent(WeaponComponentPtr weaponComponent)
{
	mWeaponComponent=weaponComponent;
}

WeaponComponentPtr GameObjectOny::getWeaponComponent() const
{
	return mWeaponComponent;
}

void GameObjectOny::setAttack(TWeaponMode weaponMode)
{
	if (mWeaponComponent.get() && mWeaponComponent->getActiveWeapon().get())
	{
		std::string attackType= mWeaponComponent->getActiveWeapon()->translateWeaponMode(weaponMode);
		mWeaponComponent->setAttackType(attackType);
	}
}

void GameObjectOny::setInitialWeaponComponent(int world)
{
	mWeaponComponent->changeActiveWeapon(world==DREAMS?mDreamsWeapon:mNightmaresWeapon);
}

void GameObjectOny::beginAttack()
{
	mWeaponComponent->switchOn();
}
void GameObjectOny::switchOff()
{
	mWeaponComponent->switchOff();
}

void GameObjectOny::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentOny.get())
	{
		mLogicComponentOny->processCollision(pGameObject);
	}
}

void GameObjectOny::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentOny.get())
	{
		mLogicComponentOny->processEnterTrigger(pGameObject);
	}
}

void GameObjectOny::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentOny.get())
	{
		mLogicComponentOny->processExitTrigger(pGameObject);
	}
}

void GameObjectOny::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentOny.get())
	{
		mLogicComponentOny->update(elapsedSeconds);
	}
}

void GameObjectOny::processAnimationEnded(const std::string animationName)
{
	if(mLogicComponentOny.get())
		mLogicComponentOny->processAnimationEnded(animationName);
}

//-------

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
