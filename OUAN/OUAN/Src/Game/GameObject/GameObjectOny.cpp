#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Application.h"
#include "../../Graphics/RenderSubsystem.h"
#include "GameObjectViewport.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ONY)
{
	mDreamsWeapon="pillow#0";
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

void GameObjectOny::setRenderComponentParticleSystemLand(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLand)
{
	mRenderComponentParticleSystemLand = pRenderComponentParticleSystemLand;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemLand() const
{
	return mRenderComponentParticleSystemLand;
}

void GameObjectOny::setRenderComponentQuadHalo(RenderComponentQuadHaloPtr pRenderComponentQuadHalo)
{
	mRenderComponentQuadHalo = pRenderComponentQuadHalo;
}

RenderComponentQuadHaloPtr GameObjectOny::getRenderComponentQuadHalo() const
{
	return mRenderComponentQuadHalo;
}

void GameObjectOny::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

AudioComponentPtr GameObjectOny::getAudioComponent() const
{
	return mAudioComponent;
}
void GameObjectOny::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

PhysicsComponentCharacterPtr GameObjectOny::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

bool GameObjectOny::isMoving()
{
	return mPhysicsComponentCharacter->isMoving();
}

bool GameObjectOny::isJumping()
{
	return mPhysicsComponentCharacter->isJumping();
}

bool GameObjectOny::cancelAutoCameraMovement()
{
	if(mWeaponComponent->isActiveWeaponInUse() && getGameWorldManager()->getWorld()==NIGHTMARES)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameObjectOny::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isFirstUpdate())
	{
		mLogicComponentOny->setNewState(ONY_STATE_IDLE);
		mIdleTime=0;
	}

	if (mLogicComponentOny->getState()==ONY_STATE_IDLE)
	{
		mIdleTime+=elapsedSeconds;
	}

	mRenderComponentEntity->update(elapsedSeconds);

	if (mPhysicsComponentCharacter->getNxOgreController()->getPosition().y < 
		Application::getInstance()->getPhysicsSubsystem()->mMinAllowedY)
	{
		if (!mGameWorldManager->getGodMode())
		{
			OnyFallsEventPtr evt(new OnyFallsEvent());
			mGameWorldManager->addEvent(evt);
		}
		else
		{
			mPhysicsComponentCharacter->jump();
			int newState = mLogicComponentOny->getNewState();
			newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_JUMP);
			mLogicComponentOny->setNewState(newState);
		}
	}

	//QuadHalo god mode effect
	mRenderComponentQuadHalo->setVisible(Application::getInstance()->getGameWorldManager()->getGodMode());
	if (Application::getInstance()->getGameWorldManager()->getGodMode())
	{
		mRenderComponentQuadHalo->update(elapsedSeconds);
	}
}

void GameObjectOny::reset()
{
	GameObject::reset();

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

	mLogicComponentOny->initStateHistory();
	mLogicComponentOny->setState(ONY_STATE_IDLE);
	mLogicComponentOny->setNewState(ONY_STATE_IDLE);
	mLogicComponentOny->setHealthPoints(mLogicComponentOny->getInitialHealthPoints());
	mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE01);
	mRenderComponentQuadHalo->setVisible(false);
}

void GameObjectOny::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}

	mWeaponComponent->changeActiveWeapon((newWorld==DREAMS)?mDreamsWeapon:mNightmaresWeapon);
	mWeaponComponent->updateAttackType();
	mWeaponComponent->switchOff();
}

void GameObjectOny::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectOny::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
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

void GameObjectOny::processAnimationEnded(const std::string& animationName)
{
	if(mLogicComponentOny.get())
	{
		mLogicComponentOny->processAnimationEnded(animationName);
	}
}

bool GameObjectOny::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectOny::getEntityComponent() const
{
	return mRenderComponentEntity;
}

bool GameObjectOny::isDying() const
{
	return CHECK_BIT(mLogicComponentOny->getState(),ONY_STATE_BIT_FIELD_DIE);
}

void GameObjectOny::postUpdate()
{
	GameObject::postUpdate();

	int currentState=mLogicComponentOny->getState();
	int lastState=mLogicComponentOny->getOldState();

	if (currentState==ONY_STATE_IDLE)
	{
		if (mLogicComponentOny->isStateChanged())
		{
			mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE01);
			mIdleTime=0.0;

			if (CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP))
			{
				mRenderComponentParticleSystemLand->start();
			}
		}
		else
		{
			if (mIdleTime>=IDLE_SECONDS_TO_NAP)
			{
				if (mRenderComponentEntity->getCurrentAnimationName().compare(ONY_ANIM_IDLE02)!=0)
				{
					mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE02);
				}
			}
		}
	}		
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_DIE) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_DIE) && 
		mRenderComponentEntity->getCurrentAnimationName().compare(ONY_ANIM_DIE01)!=0)
	{
		mAudioComponent->playSound(ONY_SOUND_DIE);
		mRenderComponentEntity->changeAnimation(ONY_ANIM_DIE01);
	}

	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_HIT) && 
		!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_HIT) && 
		mRenderComponentEntity->getCurrentAnimationName().compare(ONY_ANIM_HIT01)!=0)
	{
		mAudioComponent->playSound(ONY_SOUND_HIT);
		mRenderComponentEntity->changeAnimation(ONY_ANIM_HIT01);
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP)
		&& !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP))
	{
		mRenderComponentEntity->changeAnimation(ONY_ANIM_JUMP);			
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_MOVEMENT) && mLogicComponentOny->isStateChanged())
	{
		if (!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_MOVEMENT)) //beginning movement
		{
			mRenderComponentEntity->changeAnimation(CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK)?ONY_ANIM_WALK:ONY_ANIM_RUN);
		}
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

	//Apply falling efect when reached fall speed limit
	setFallingEffect(mPhysicsComponentCharacter->isFallingLimit());
}

AudioComponentPtr GameObjectOny::getAudioComponentInstance() const
{
	return mAudioComponent;
}

bool GameObjectOny::hasAudioComponent() const
{
	return true;
}

void GameObjectOny::setFallingEffect(bool enabled)
{
	if ((mGameWorldManager->getWorld() == DREAMS && 
		 !Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_DREAMS) ||	
		(mGameWorldManager->getWorld() == NIGHTMARES && 
		 !Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR_ACTIVATED_ALWAYS_NIGHTMARES))
	{
		mGameWorldManager->getGameObjectViewport()->setEffect(
			Application::getInstance()->getRenderSubsystem()->RADIAL_BLUR, 
			enabled);
	}
}
//-------

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
