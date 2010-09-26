#include "OUAN_Precompiled.h"

#include "GameObjectBoss.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;

GameObjectBoss::GameObjectBoss(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BOSS)
{

}

GameObjectBoss::~GameObjectBoss()
{

}
/// Set logic component
void GameObjectBoss::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

AudioComponentPtr GameObjectBoss::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectBoss::setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent)
{
	mTrajectoryComponent=pTrajectoryComponent;
}

TrajectoryComponentPtr GameObjectBoss::getTrajectoryComponent()
{	
	return mTrajectoryComponent;
}

void GameObjectBoss::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


/// return logic component
LogicComponentEnemyPtr GameObjectBoss::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}

void GameObjectBoss::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBoss::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBoss::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBoss::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBoss::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectBoss::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectBoss::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectBoss::getPhysicsComponentCharacter() const
{ 
	return mPhysicsComponentCharacter;
}

bool GameObjectBoss::hasPatrolTrajectory()
{
	return mTrajectoryComponent->predefinedTrajectoryExists(getPatrolTrajectoryName(
		mGameWorldManager->getWorld()));
}

std::string GameObjectBoss::getPatrolTrajectoryName(int world)
{
	std::string trajectoryName = getName();
	trajectoryName.append(world==DREAMS?SUFFIX_DREAMS:SUFFIX_NIGHTMARES);
	return trajectoryName;
}

bool GameObjectBoss::activateTrajectory(int newWorld)
{
	std::string trajectoryName = getPatrolTrajectoryName(newWorld);
	if(mTrajectoryComponent->predefinedTrajectoryExists(trajectoryName))
	{
		mTrajectoryComponent->activatePathfindingToPredefinedTrajectory(trajectoryName,
			newWorld,true);
		return true;
	}
	else
	{
		mTrajectoryComponent->activateIdle(getName(),newWorld);
		return false;
	}
}

void GameObjectBoss::setCurrentWalkAnimation()
{
	int hp=mLogicComponentEnemy->getHealthPoints();
	if(hp==3)
	{
		mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_WALK);
		mTrajectoryComponent->setDefaultSpeed(BOSS_SPEED_WALK);
	}
	else if(hp==2)
	{
		mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_RUN);
		mTrajectoryComponent->setDefaultSpeed(BOSS_SPEED_RUN);
	}
	else if(hp==1)
	{
		mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_RUN_PISSED_OFF);
		mTrajectoryComponent->setDefaultSpeed(BOSS_SPEED_RUN_PISSED_OFF);
	}
}

void GameObjectBoss::updateHPEvents()
{
	int hp=mLogicComponentEnemy->getHealthPoints();
	if(hp==3)
	{
		mLogicComponentEnemy->setColourSensitivityMask(COLOUR_FLAG_BLUE);
	}
	else if(hp==2)
	{
		getGameWorldManager()->addExecutedLevelEvent(BOSS_HIT_1_DONE);
		mLogicComponentEnemy->setColourSensitivityMask(COLOUR_FLAG_GREEN);
	}
	else if(hp==1)
	{
		getGameWorldManager()->addExecutedLevelEvent(BOSS_HIT_2_DONE);
		mLogicComponentEnemy->setColourSensitivityMask(COLOUR_FLAG_RED);
	}
	else if(hp==0)
	{
		getGameWorldManager()->addExecutedLevelEvent(BOSS_HIT_3_DONE);
	}
}

void GameObjectBoss::setPhysicsComponentWeapon(PhysicsComponentWeaponPtr pPhysicsComponentWeapon)
{
	mPhysicsComponentWeapon=pPhysicsComponentWeapon;
}

PhysicsComponentWeaponPtr GameObjectBoss::getPhysicsComponentWeapon() const
{
	return mPhysicsComponentWeapon;
}

void GameObjectBoss::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

	int currentState=mLogicComponentEnemy->getState();
	int world = getGameWorldManager()->getWorld();

	std::string onyName=getGameWorldManager()->getGameObjectOny()->getName();

	if(isEnabled())
	{
		if (mLogicComponentEnemy->isStateChanged())
		{
			if(currentState==logicSS->getGlobalInt(BOSS_STATE_PATROL))
			{
				setCurrentWalkAnimation();
				activateTrajectory(mGameWorldManager->getWorld());
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_CHASE))
			{
				setCurrentWalkAnimation();
				mTrajectoryComponent->activateChase(onyName);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_ALERT))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_ALERT);
				mLogicComponentEnemy->setAlertFinished(false);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_TIRED))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_TIRED);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setTiredFinished(false);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_ATTACK))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_ATTACK);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setAttackFinished(false);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_SP_ATTACK))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_SP_ATTACK);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setAttackFinished(false);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_FLASHLIGHT_HIT))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_FLASHLIGHT_HIT);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setFlashLightHitFinished(false);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_STUNNED))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_STUNNED);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->setHasBeenHit(false);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_LEAVING_NIGHTMARES))
			{
				//THIS IS NOT USED
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_LEAVE);
				mTrajectoryComponent->activateIdle(getName(),world);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_PILLOW_HIT))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_PILLOW_HIT);
				mLogicComponentEnemy->setPillowHitFinished(false);
				mLogicComponentEnemy->setHasBeenHit(false);
				mTrajectoryComponent->activateIdle(getName(),world);
				mLogicComponentEnemy->decreaseHP();
				updateHPEvents();
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_WARCRY))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_WARCRY);
				mLogicComponentEnemy->setCallToArmsFinished(false);
				mTrajectoryComponent->activateIdle(getName(),world);
			}
			else if(currentState==logicSS->getGlobalInt(BOSS_STATE_DIE))
			{
				mRenderComponentEntity->changeAnimation(BOSS_ANIMATION_DIE);
				mTrajectoryComponent->activateIdle(getName(),world);
			}
		}

		mTrajectoryComponent->update(elapsedSeconds);

		if (mPhysicsComponentCharacter->isInUse())
		{
			Ogre::Vector3 movement = mTrajectoryComponent->getNextMovementAbsolute();				
			mPhysicsComponentCharacter->setOuternMovement(movement);
		}
		//if (mPhysicsComponentWeapon->isInUse())
		//{
		//	Ogre::Vector3 pos;
		//	if (entity.get() && entity->getEntity()->hasSkeleton()
		//		&& entity->getEntity()->getSkeleton()->hasBone(HEAD_BONE_NAME))
		//	{
		//		Ogre::Entity* ent = entity->getEntity();
		//		Ogre::Node* bone = ent->getSkeleton()->getBone(HEAD_BONE_NAME);
		//		pos=Utils::getNodeWorldPosition(ent,bone);			
		//	}
		//	else
		//	{
		//		mRenderComponentPositional->getPosition();			
		//	}
		//	mPhysicsComponentWeapon->setPosition(pos);			
		//	mPhysicsComponentWeapon->setDisplayYaw(mPhysicsComponentCharacter->getDisplayYaw());
		//	mPhysicsComponentWeapon->update(elapsedSeconds);
		//}

		mRenderComponentEntity->update(elapsedSeconds);
	}
	else
	{
		if (mRenderComponentEntity.get())
			mRenderComponentEntity->setVisible(false);
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
	}
}

void GameObjectBoss::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(BOSS_ANIMATION_ALERT)==0)
	{
		mLogicComponentEnemy->setAlertFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_TIRED)==0)
	{
		mLogicComponentEnemy->setTiredFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_ATTACK)==0)
	{
		mLogicComponentEnemy->setAttackFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_SP_ATTACK)==0)
	{
		mLogicComponentEnemy->setAttackFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_FLASHLIGHT_HIT)==0)
	{
		mLogicComponentEnemy->setFlashLightHitFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_PILLOW_HIT)==0)
	{
		mLogicComponentEnemy->setPillowHitFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_WARCRY)==0)
	{
		mLogicComponentEnemy->setCallToArmsFinished(true);
	}
	else if(animationName.compare(BOSS_ANIMATION_DIE)==0)
	{
		disable();
	}
}

bool GameObjectBoss::hasBeenHit() const
{
	if (mLogicComponentEnemy.get())	
		return mLogicComponentEnemy->hasBeenHit();
	return false;
}

bool GameObjectBoss::hasDied() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasDied();
	return false;
}

bool GameObjectBoss::isWorthUpdatingPhysicsComponents()
{
	return true;
}

bool GameObjectBoss::isWorthUpdatingLogicComponents()
{
	return true;

}

void GameObjectBoss::reset()
{
	GameObject::reset();

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueDegrees());
	}
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
	}

	mTrajectoryComponent->setAs2DTrajectory();

	mLogicComponentEnemy->setHasDied(false);
	mLogicComponentEnemy->setHasBeenHit(false);
	mLogicComponentEnemy->setAttackFinished(false);
	mLogicComponentEnemy->setInitialHealthPoints(3);
	updateHPEvents();

	mLogicComponentEnemy->setAlertFinished(true);
	mLogicComponentEnemy->setTiredFinished(true);
	mLogicComponentEnemy->setFlashLightHitFinished(true);
	mLogicComponentEnemy->setPillowHitFinished(true);
	mLogicComponentEnemy->setCallToArmsFinished(true);

	setCurrentWalkAnimation();
	activateTrajectory(mGameWorldManager->getWorld());

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	mLogicComponentEnemy->setState(logicSS->getGlobalInt(BOSS_STATE_PATROL));

}

void GameObjectBoss::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentEnemy->getState();

	switch(newWorld)
	{
		case DREAMS:
			break;
		case NIGHTMARES:
			break;
		default:break;
	}

	if(currentState==logicSS->getGlobalInt(BOSS_STATE_PATROL))
	{
		activateTrajectory(mGameWorldManager->getWorld());
	}

	mLogicComponentEnemy->setHasBeenHit(false);
}

void GameObjectBoss::changeWorldStarted(int newWorld)
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

void GameObjectBoss::changeToWorld(int newWorld, double perc)
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

int GameObjectBoss::getTimeStunned() const
{
	//TODO: Define somewhere a stunned counter for the boss and update
	// it accordingly; then, use that value here
	return 0;
}

bool GameObjectBoss::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBoss::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectBoss::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectBoss::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectBoss::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
	}
}

void GameObjectBoss::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectBoss::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}
bool GameObjectBoss::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectBoss::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectBoss::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectBoss::getLogicComponent() const
{
	return mLogicComponentEnemy;
}
//-------------------------------------------------------------------------------------------
TGameObjectBossParameters::TGameObjectBossParameters() : TGameObjectParameters()
{

}

TGameObjectBossParameters::~TGameObjectBossParameters()
{

}