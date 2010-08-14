#include "OUAN_Precompiled.h"

#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Application.h"
#include "../../Graphics/RenderSubsystem.h"
#include "GameObjectViewport.h"
#include "GameObjectPillow.h"
#include "GameObjectFlashLight.h"
#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectOny::GameObjectOny(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ONY)
{
	mDreamsWeapon="pillow#0";
	mNightmaresWeapon="flashlight#1";
	mIdleTime=-1;
	mCurrentWeaponMode=WEAPON_MODE_0;
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

void GameObjectOny::setRenderComponentParticleSystemLandDreams(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLandDreams)
{
	mRenderComponentParticleSystemLandDreams = pRenderComponentParticleSystemLandDreams;
}

void GameObjectOny::setRenderComponentParticleSystemLandNightmares(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLandNightmares)
{
	mRenderComponentParticleSystemLandNightmares = pRenderComponentParticleSystemLandNightmares;
}

void GameObjectOny::setRenderComponentParticleSystemLandWave(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLandWave)
{
	mRenderComponentParticleSystemLandWave = pRenderComponentParticleSystemLandWave;
}

void GameObjectOny::setRenderComponentParticleSystemLandWaterWave(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLandWaterWave)
{
	mRenderComponentParticleSystemLandWaterWave = pRenderComponentParticleSystemLandWaterWave;
}

void GameObjectOny::setRenderComponentParticleSystemLandWaterDrops(RenderComponentParticleSystemPtr pRenderComponentParticleSystemLandWaterDrops)
{
	mRenderComponentParticleSystemLandWaterDrops = pRenderComponentParticleSystemLandWaterDrops;
}

void GameObjectOny::setRenderComponentParticleSystemRunGrass(RenderComponentParticleSystemPtr pRenderComponentParticleSystemRunGrass)
{
	mRenderComponentParticleSystemRunGrass = pRenderComponentParticleSystemRunGrass;
}

void GameObjectOny::setRenderComponentParticleSystemRunSand(RenderComponentParticleSystemPtr pRenderComponentParticleSystemRunSand)
{
	mRenderComponentParticleSystemRunSand = pRenderComponentParticleSystemRunSand;
}

void GameObjectOny::setRenderComponentParticleSystemRunWater(RenderComponentParticleSystemPtr pRenderComponentParticleSystemRunWater)
{
	mRenderComponentParticleSystemRunWater = pRenderComponentParticleSystemRunWater;
}

void GameObjectOny::setRenderComponentParticleSystemRunSurprise(RenderComponentParticleSystemPtr pRenderComponentParticleSystemRunSurprise)
{
	mRenderComponentParticleSystemRunSurprise = pRenderComponentParticleSystemRunSurprise;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemLandDreams() const
{
	return mRenderComponentParticleSystemLandDreams;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemLandNightmares() const
{
	return mRenderComponentParticleSystemLandNightmares;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemLandWave() const
{
	return mRenderComponentParticleSystemLandWave;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemRunGrass() const
{
	return mRenderComponentParticleSystemRunGrass;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemRunSand() const
{
	return mRenderComponentParticleSystemRunSand;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemRunWater() const
{
	return mRenderComponentParticleSystemRunWater;
}

RenderComponentParticleSystemPtr GameObjectOny::getRenderComponentParticleSystemRunSurprise() const
{
	return mRenderComponentParticleSystemRunSurprise;
}

void GameObjectOny::setRenderComponentQuadHalo(RenderComponentQuadHaloPtr pRenderComponentQuadHalo)
{
	mRenderComponentQuadHalo = pRenderComponentQuadHalo;
}

RenderComponentQuadHaloPtr GameObjectOny::getRenderComponentQuadHalo() const
{
	return mRenderComponentQuadHalo;
}

void GameObjectOny::setPhysicsComponentCharacterOny(PhysicsComponentCharacterOnyPtr pPhysicsComponentCharacterOny)
{
	mPhysicsComponentCharacterOny=pPhysicsComponentCharacterOny;
}

AudioComponentPtr GameObjectOny::getAudioComponent() const
{
	return mAudioComponent;
}
void GameObjectOny::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

PhysicsComponentCharacterOnyPtr GameObjectOny::getPhysicsComponentCharacterOny() const
{
	return mPhysicsComponentCharacterOny;
}

bool GameObjectOny::isMoving()
{
	return mPhysicsComponentCharacterOny->isMoving();
}

bool GameObjectOny::isJumping()
{
	return mPhysicsComponentCharacterOny->isJumping();
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

	//double animationTime=elapsedSeconds;
	//TODO: Move the scale factor to a configurable parameter
	mRenderComponentEntity->update(elapsedSeconds);

	if (mRenderComponentEntity->isTintBeingApplied())
	{
		double invulnerabilityTime = POST_HIT_INVULNERABILITY-mLogicComponentOny->getHitRecoveryTime();
		mRenderComponentEntity->setTintFactor(0.5*(1+Ogre::Math::Sin(invulnerabilityTime*10)));
	}

	if (mPhysicsComponentCharacterOny->getNxOgreController()->getPosition().y < 
		Application::getInstance()->getPhysicsSubsystem()->mMinAllowedY)
	{
		if (!mGameWorldManager->isGodMode())
		{
			OnyFallsEventPtr evt(new OnyFallsEvent());
			mGameWorldManager->addEvent(evt);
		}
		//else
		//{
		//	mPhysicsComponentCharacterOny->jump();
		//	int newState = mLogicComponentOny->getNewState();
		//	newState=SET_BIT(newState,ONY_STATE_BIT_FIELD_JUMP);
		//	mLogicComponentOny->setNewState(newState);
		//}
	}

	//QuadHalo god mode effect
	mRenderComponentQuadHalo->setVisible(Application::getInstance()->getGameWorldManager()->isGodMode());
	if (Application::getInstance()->getGameWorldManager()->isGodMode())
	{
		mRenderComponentQuadHalo->update(elapsedSeconds);
	}

	if (mRunParticlesElapsed>=0.0)
	{
		mRunParticlesElapsed+=elapsedSeconds;
		if (mRunParticlesElapsed>mRunParticlesNextInterval)
		{
			mRenderComponentParticleSystemRunSand->start();
			mRunParticlesElapsed=0.0;
			mRunParticlesNextInterval=Utils::Random::getInstance()->getRandomDouble(mRunParticlesMin,mRunParticlesMax);
		}
	}
}

void GameObjectOny::reset()
{
	GameObject::reset();

	mPhysicsComponentCharacterOny->reset();
	mPhysicsComponentCharacterOny->getNxOgreController()->setPosition(mGameWorldManager->getCheckPointPosition());
	//add 180 since it's the back
	mPhysicsComponentCharacterOny->getNxOgreController()->setDisplayYaw(mGameWorldManager->getCheckPointOrientation().getYaw().valueDegrees()+180);
	mRenderComponentPositional->setPosition(mGameWorldManager->getCheckPointPosition());
	mRenderComponentPositional->setOrientation(Ogre::Quaternion::IDENTITY);
	mRenderComponentPositional->getSceneNode()->yaw(
		Ogre::Radian(
		mPhysicsComponentCharacterOny->getNxOgreController()->getOrientation().as<Ogre::Quaternion>().getYaw().valueRadians())
		);

	mLogicComponentOny->initStateHistory();
	mLogicComponentOny->setState(ONY_STATE_IDLE);
	mLogicComponentOny->setNewState(ONY_STATE_IDLE);
	mLogicComponentOny->setHealthPoints(mLogicComponentOny->getInitialHealthPoints());
	mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE01,AnimationBlender::BT_SWITCH,1);
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
	{
		mWeaponComponent->increaseWeaponPower(powerUnits);
	}
}

void GameObjectOny::decreaseWeaponPower(int powerUnits)
{
	if (mWeaponComponent.get())
	{
		mWeaponComponent->decreaseWeaponPower(powerUnits);
	}
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
	return getPhysicsComponentCharacterOny();
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
	mCurrentWeaponMode = weaponMode;

	if (mWeaponComponent.get() && mWeaponComponent->getActiveWeapon().get())
	{
		std::string attackType = mWeaponComponent->getActiveWeapon()->translateWeaponMode(weaponMode);
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

void GameObjectOny::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentOny.get())
	{
		mLogicComponentOny->processCollision(pGameObject, pNormal);
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

bool GameObjectOny::isHit() const
{
	return CHECK_BIT(mLogicComponentOny->getState(),ONY_STATE_BIT_FIELD_HIT);
}

void GameObjectOny::postUpdate()
{
	GameObject::postUpdate();

	int currentState=mLogicComponentOny->getState();
	int lastState=mLogicComponentOny->getOldState();

	//TO REALLOCATE BETTER
	if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_MOVEMENT) && CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_IDLE)){
		mRenderComponentParticleSystemRunSand->start();
	}

	if (currentState==ONY_STATE_IDLE || currentState==(1<<ONY_STATE_BIT_FIELD_INVULNERABLE))
	{
		if (mLogicComponentOny->isStateChanged())
		{
			mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE01,AnimationBlender::BT_WHILEANIMATING,
				0.5,TRUE,1.0);
			mIdleTime=0.0;

			if (CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP))
			{
				if (mGameWorldManager->getWorld() == DREAMS)
				{
					mRenderComponentParticleSystemLandDreams->start();
					mRenderComponentParticleSystemLandWave->start();
				}
				else if (mGameWorldManager->getWorld() == NIGHTMARES)
				{
					mRenderComponentParticleSystemLandNightmares->start();
					mRenderComponentParticleSystemLandWave->start();
				}
			}
		}
		else
		{
			if (mIdleTime>=IDLE_SECONDS_TO_NAP)
			{
				if (mRenderComponentEntity->getCurrentAnimationName2().compare(ONY_ANIM_IDLE02)!=0)
				{
					mRenderComponentEntity->changeAnimation(ONY_ANIM_IDLE02,
						AnimationBlender::BT_WHILEANIMATING,0.5,false);
				}
			}
		}
	}		
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_DIE) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_DIE) && 
		mRenderComponentEntity->getCurrentAnimationName2().compare(ONY_ANIM_DIE01)!=0)
	{
		mAudioComponent->playSound(ONY_SOUND_DIE);
		mRenderComponentEntity->changeAnimation(ONY_ANIM_DIE01,AnimationBlender::BT_WHILEANIMATING,
			0.5,false);
	}

	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_HIT) && 
		!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_HIT) && 
		mRenderComponentEntity->getCurrentAnimationName2().compare(ONY_ANIM_HIT01)!=0)
	{
		mAudioComponent->playSound(ONY_SOUND_HIT);
		mRenderComponentEntity->changeAnimation(ONY_ANIM_HIT01,AnimationBlender::BT_WHILEANIMATING,
			0.5,false);
	}
	else if (CHECK_BIT(currentState, ONY_STATE_BIT_FIELD_ATTACK) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_ATTACK))
	{
		if (mWorld == DREAMS)
		{
			mRenderComponentEntity->changeAnimation(ONY_ANIM_STAB_PILLOW,AnimationBlender::BT_WHILEANIMATING,0.5,false,0.8);

			GameObjectPillowPtr pillow = BOOST_PTR_CAST(GameObjectPillow,
				mWeaponComponent->getActiveWeapon());

			if (pillow.get())
			{
				pillow->startAttackParticles();
			}
		} 
		else if (mWorld == NIGHTMARES) 
		{
			//get Camera Direction and change animation accordingly:
			mRenderComponentEntity->changeAnimation(ONY_ANIM_SHOOT_CENTER,AnimationBlender::BT_WHILEANIMATING,0.5,false);

			GameObjectFlashLightPtr flashLight = BOOST_PTR_CAST(GameObjectFlashLight,
				mWeaponComponent->getActiveWeapon());
		}
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP)
		&& !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP))
	{
		mRenderComponentEntity->changeAnimation(ONY_ANIM_JUMP,AnimationBlender::BT_WHILEANIMATING,
			0.5,false);			
	}
	else if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_MOVEMENT) && mLogicComponentOny->isStateChanged())
	{
		if (!CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_MOVEMENT)) //beginning movement
		{
			if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK))
				mRenderComponentEntity->changeAnimation(ONY_ANIM_WALK,AnimationBlender::BT_WHILEANIMATING,
				0.5,true,1.5);
			else
				mRenderComponentEntity->changeAnimation(ONY_ANIM_RUN,AnimationBlender::BT_WHILEANIMATING,
				0.5,true);
		}
		else //Walk/run toggle
		{
			bool toWalk=CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_WALK);
			bool toRun=CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_WALK) && !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK);
			bool fromJump = !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_JUMP) && CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_JUMP);

			if (toWalk || toRun || fromJump)
			{
				if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK))
					mRenderComponentEntity->changeAnimation(ONY_ANIM_WALK,
					AnimationBlender::BT_WHILEANIMATING,
					0.5,true,1.5);
				else
					mRenderComponentEntity->changeAnimation(ONY_ANIM_RUN,AnimationBlender::BT_WHILEANIMATING,
					0.5,true);
			}
		}		
	}
	if (CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_INVULNERABLE) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_INVULNERABLE))
	{
		mRenderComponentEntity->applyTint(Ogre::ColourValue::Red);
	}
	else if (!CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_INVULNERABLE) && CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_INVULNERABLE))
	{		
		mRenderComponentEntity->removeTint();
	}
	if (!CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_FALL)
		&& CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_FALL))
	{
		if (mGameWorldManager->getWorld() == DREAMS)
		{
			mRenderComponentParticleSystemLandDreams->start();
			mRenderComponentParticleSystemLandWave->start();
		}
		else if (mGameWorldManager->getWorld() == NIGHTMARES)
		{
			mRenderComponentParticleSystemLandNightmares->start();
			mRenderComponentParticleSystemLandWave->start();
		}
	}
	bool wasRunning = CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_MOVEMENT) && !CHECK_BIT(lastState,ONY_STATE_BIT_FIELD_WALK);
	bool hasStoppedRunning = !CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_MOVEMENT) || CHECK_BIT(currentState,ONY_STATE_BIT_FIELD_WALK);
	if (wasRunning && hasStoppedRunning)
	{
		mRunParticlesElapsed=-1.0;
		mRunParticlesNextInterval=-1.0;
	}

	bool hasBegunRunning = !wasRunning && !hasStoppedRunning;		
	if (hasBegunRunning)
	{
		mRunParticlesElapsed=0.0;
		mRunParticlesNextInterval = Utils::Random::getInstance()->getRandomDouble(mRunParticlesMin,mRunParticlesMax);
		mRenderComponentParticleSystemRunSand->start();
	}

	//Apply radial blur effect when reached fall speed limit
	mGameWorldManager->getGameObjectViewport()->
		setRadialBlurEffectIfPossible(
			mGameWorldManager->getWorld(),
			mPhysicsComponentCharacterOny->isFallingLimit());
}

AudioComponentPtr GameObjectOny::getAudioComponentInstance() const
{
	return mAudioComponent;
}

bool GameObjectOny::hasAudioComponent() const
{
	return true;
}

double GameObjectOny::getMovingSpeed()
{
	return Application::getInstance()->getPhysicsSubsystem()->mMovementUnitsPerSecond;
}

int GameObjectOny::getLogicNewState() const
{
	return mLogicComponentOny->getNewState();
}
void GameObjectOny::setLogicNewState(int newState)
{
	mLogicComponentOny->setNewState(newState);
}
int GameObjectOny::getLogicCurrentState() const
{
	return mLogicComponentOny->getState();
}
bool GameObjectOny::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectOny::getLogicComponentInstance() const
{
	return mLogicComponentOny;
}
double GameObjectOny::getRunParticlesElapsed() const
{
	return mRunParticlesElapsed;
}
void GameObjectOny::setRunParticlesElapsed(double runParticlesElapsed)
{
	mRunParticlesElapsed=runParticlesElapsed;
}
double GameObjectOny::getRunParticlesNextInterval() const
{
	return mRunParticlesNextInterval;
}
void GameObjectOny::setRunParticlesNextInterval(double runParticlesNextInterval)
{
	mRunParticlesNextInterval=runParticlesNextInterval;
}

//Random interval Bounds
double GameObjectOny::getRunParticlesMin() const
{
	return mRunParticlesMin;
}
void GameObjectOny::setRunParticlesMin(double runParticlesMin)
{
	mRunParticlesMin=runParticlesMin;
}
double GameObjectOny::getRunParticlesMax() const
{
	return mRunParticlesMax;
}
void GameObjectOny::setRunParticlesMax(double runParticlesMax)
{
	mRunParticlesMax=runParticlesMax;
}
void GameObjectOny::addDiamonds(int amount)
{
	mLogicComponentOny->increaseCollectableItemAmount(GAME_OBJECT_TYPE_DIAMOND,amount);
}
//-------

TGameObjectOnyParameters::TGameObjectOnyParameters() : TGameObjectParameters()
{

}

TGameObjectOnyParameters::~TGameObjectOnyParameters()
{

}
