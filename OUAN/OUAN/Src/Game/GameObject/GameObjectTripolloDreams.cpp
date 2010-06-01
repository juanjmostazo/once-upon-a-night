#include "GameObjectTripolloDreams.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectTripolloDreams::GameObjectTripolloDreams(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{

}

GameObjectTripolloDreams::~GameObjectTripolloDreams()
{

}
/// Set logic component
void GameObjectTripolloDreams::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectTripolloDreams::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectTripolloDreams::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTripolloDreams::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTripolloDreams::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTripolloDreams::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTripolloDreams::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripolloDreams::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTripolloDreams::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTripolloDreams::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTripolloDreams::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripolloDreams::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

bool GameObjectTripolloDreams::activateTrajectory(int newWorld)
{
	if(newWorld==DREAMS)
	{
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_TRAJECTORY_DREAMS))
		{
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_TRAJECTORY_DREAMS,newWorld);
			return true;
		}
		else
		{
			mTrajectoryComponent->activateIdle(getName(),newWorld);
			return false;
		}
	}
	else if(newWorld==NIGHTMARES)
	{
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_TRAJECTORY_NIGHTMARES))
		{
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_TRAJECTORY_NIGHTMARES,newWorld);
			return true;
		}
		else
		{
			mTrajectoryComponent->activateIdle(getName(),newWorld);
			return false;
		}
	}
	return false;
}

void GameObjectTripolloDreams::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		//debug code, erase when it works
		//if(getName().compare("tripollo#12")!=0)
		//	return;

		RenderComponentEntityPtr entityToUpdate = (mWorld==DREAMS)
			?mRenderComponentEntityDreams
			:mRenderComponentEntityNightmares;

		int currentState=mLogicComponentEnemy->getState();

		if (mPhysicsComponentCharacter.get())
		{
			if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE))
			{

				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}

			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
			{				
				if (mLogicComponentEnemy->isStateChanged())
				{
					if(activateTrajectory(mGameWorldManager->getWorld()))
					{
						/*
							If the state has just changed, then load the trajectory and set the displacement
							vector as (marker1-marker0)
						*/
						if (entityToUpdate.get())
							entityToUpdate->changeAnimation(TRIPOLLO_ANIM_WALK);
					}
					else
					{
						if (entityToUpdate.get())
							entityToUpdate->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
					}
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FIND))
			{
				//Logger::getInstance()->log("FIND");
				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_WALK);

					mTrajectoryComponent->activatePathFinding(
						mGameWorldManager->getGameObjectOny()->getName(),
						mGameWorldManager->getWorld());
				}

			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_HIT))
			{
				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					mAudioComponent->playSound(TRIPOLLO_SOUND_HIT);
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_HIT01);
					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_DEAD))
			{
				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					mAudioComponent->playSound(TRIPOLLO_SOUND_DIE);
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_DIE);
					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
			{
				//Logger::getInstance()->log("CHASE");
				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_WALK);

					mTrajectoryComponent->activateChase(
						mGameWorldManager->getGameObjectOny()->getName());
				}
			}
			else
			{
				
			}

			if (entityToUpdate.get())
			{
				entityToUpdate->update(elapsedSeconds);
			}

			mTrajectoryComponent->update(elapsedSeconds);

			if (mPhysicsComponentCharacter->isInUse())
			{
				//mRenderComponentPositional->setPosition(mTrajectory->getCurrentPosition());

				//Logger::getInstance()->log("[Movement] "+getName()+" "+Ogre::StringConverter::toString(movement));
				mPhysicsComponentCharacter->setNextMovement(mTrajectoryComponent->getNextMovement());
			}
		}
	}
	else
	{		
		mRenderComponentEntityDreams->setVisible(false);
		mRenderComponentEntityNightmares->setVisible(false);
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
	}
}

void GameObjectTripolloDreams::postUpdate()
{
	GameObject::postUpdate();
}

AttackComponentPtr GameObjectTripolloDreams::getAttackComponent() const
{
	return mAttackComponent;
}
void GameObjectTripolloDreams::setAttackComponent(AttackComponentPtr attackComponent)
{
	mAttackComponent=attackComponent;
}
std::string GameObjectTripolloDreams::getDefaultAttack()
{
	return TRIPOLLO_ATTACK_PECK;
}
void GameObjectTripolloDreams::reset()
{
	GameObject::reset();

	LogicSubsystemPtr logicSS = getGameWorldManager()->getParent()->getLogicSubsystem();

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);

		mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE));
	}		
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);
		mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE));
	}
}

void GameObjectTripolloDreams::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityNightmares->setVisible(false);
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				activateTrajectory(newWorld);
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
				activateTrajectory(newWorld);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityNightmares->setVisible(true);
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				activateTrajectory(newWorld);
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				activateTrajectory(newWorld);
			}	
			break;
		default:break;
	}
}

void GameObjectTripolloDreams::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->randomizeChangeWorldMaterials();
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->randomizeChangeWorldMaterials();
	}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
		}	
		break;
	default:
		break;
	}	
}

void GameObjectTripolloDreams::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
			}		
			break;
		default:
			break;
	}
}


void GameObjectTripolloDreams::setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent)
{
	mTrajectoryComponent=pTrajectoryComponent;
}

TrajectoryComponentPtr GameObjectTripolloDreams::getTrajectoryComponent()
{
	return mTrajectoryComponent;
}

bool GameObjectTripolloDreams::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTripolloDreams::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTripolloDreams::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTripolloDreams::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectTripolloDreams::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

void GameObjectTripolloDreams::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectTripolloDreams::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectTripolloDreams::updateLogic(double elapsedSeconds)
{
	if (isEnabled() && mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}
bool GameObjectTripolloDreams::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTripolloDreams::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//
void GameObjectTripolloDreams::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(TRIPOLLO_ANIM_HIT01)==0)
	{
		mLogicComponentEnemy->setHasBeenHit(false);
	}
	if (animationName.compare(TRIPOLLO_ANIM_DIE)==0)
	{
		disableDisplayMsg();
		std::string msg="Enemy ";
		msg.append(getName()).append(" died");
		Logger::getInstance()->log(msg);
		disable();		
	}
}

bool GameObjectTripolloDreams::hasBeenHit() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasBeenHit();
	return false;
}
bool GameObjectTripolloDreams::hasDied() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasDied();
	return false;
}

AudioComponentPtr GameObjectTripolloDreams::getAudioComponent() const
{
	return mAudioComponent;
}
void GameObjectTripolloDreams::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

AudioComponentPtr GameObjectTripolloDreams::getAudioComponentInstance() const
{
	return mAudioComponent;
}
bool GameObjectTripolloDreams::hasAudioComponent() const
{
	return true;
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloDreamsParameters::TGameObjectTripolloDreamsParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloDreamsParameters::~TGameObjectTripolloDreamsParameters()
{

}