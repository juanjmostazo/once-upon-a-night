#include "OUAN_Precompiled.h"

#include "GameObjectTripollo.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{

}

GameObjectTripollo::~GameObjectTripollo()
{

}
/// Set logic component
void GameObjectTripollo::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectTripollo::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectTripollo::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTripollo::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTripollo::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTripollo::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTripollo::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTripollo::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTripollo::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTripollo::setRenderComponentParticleSystemDie(RenderComponentParticleSystemPtr pRenderComponentParticleSystemDie)
{
	mRenderComponentParticleSystemDie = pRenderComponentParticleSystemDie;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemDie() const
{
	return mRenderComponentParticleSystemDie;
}

void GameObjectTripollo::setRenderComponentParticleSystemShock(RenderComponentParticleSystemPtr pRenderComponentParticleSystemShock)
{
	mRenderComponentParticleSystemShock = pRenderComponentParticleSystemShock;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemShock() const
{
	return mRenderComponentParticleSystemShock;
}

void GameObjectTripollo::setRenderComponentParticleSystemSurprise(RenderComponentParticleSystemPtr pRenderComponentParticleSystemSurprise)
{
	mRenderComponentParticleSystemSurprise = pRenderComponentParticleSystemSurprise;
}

RenderComponentParticleSystemPtr GameObjectTripollo::getRenderComponentParticleSystemSurprise() const
{
	return mRenderComponentParticleSystemSurprise;
}

void GameObjectTripollo::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollo::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

bool GameObjectTripollo::activateTrajectory(int newWorld)
{
	if(newWorld==DREAMS)
	{
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_DREAMS))
		{
			mTrajectoryComponent->activatePathfindingToPredefinedTrajectory(getName()+SUFFIX_DREAMS,newWorld,true);
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
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_NIGHTMARES))
		{
			mTrajectoryComponent->activatePathfindingToPredefinedTrajectory(getName()+SUFFIX_NIGHTMARES,newWorld,true);
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

void GameObjectTripollo::activateFlying(bool flying)
{
	mPhysicsComponentCharacter->setFlyingCharacter(flying);
	if(flying)
	{
		mTrajectoryComponent->setAs3DTrajectory();
	}
	else
	{
		mTrajectoryComponent->setAs2DTrajectory();
	}
}

void GameObjectTripollo::activateStatue(bool statue)
{
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	int currentState=mLogicComponentEnemy->getState();
	if(statue)
	{
		//Logger::getInstance()->log("STATUE ON "+Ogre::StringConverter::toString(logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE)));
		mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE));	
		mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
	}
	else
	{
		if(currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE))
		{
			mLogicComponentEnemy->setState(logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE));
			if(mRenderComponentEntityDreams.get())
			{
				mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
			}

			if(mRenderComponentEntityNightmares.get())
			{
				mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
			}

			mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
		}
	}
}


void GameObjectTripollo::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();


		int currentState=mLogicComponentEnemy->getState();


		if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE))
		{
			return;
		}

		if (mPhysicsComponentCharacter.get())
		{
			if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE))
			{
				if (mLogicComponentEnemy->isStateChanged())
				{
					if(mRenderComponentEntityDreams.get())
					{
						mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
					}

					if(mRenderComponentEntityNightmares.get())
					{
						mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
					}

					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
			{				
				if (mLogicComponentEnemy->isStateChanged())
				{
					if(activateTrajectory(mGameWorldManager->getWorld()))
					{
						//If the state has just changed, then load the trajectory and set the displacement
						//vector as (marker1-marker0)
						
						if(mRenderComponentEntityDreams.get())
						{
							mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_WALK);
						}

						if(mRenderComponentEntityNightmares.get())
						{
							mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_WALK);
						}
					}
					else
					{
						if(mRenderComponentEntityDreams.get())
						{
							mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
						}

						if(mRenderComponentEntityNightmares.get())
						{
							mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_IDLE_02);
						}
					}
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FIND))
			{
				//Logger::getInstance()->log("FIND");
				if (mLogicComponentEnemy->isStateChanged())
				{
					if(mRenderComponentEntityDreams.get())
					{
						mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_WALK);
					}

					if(mRenderComponentEntityNightmares.get())
					{
						mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_WALK);
					}

					mTrajectoryComponent->activatePathFinding(
						mGameWorldManager->getGameObjectOny()->getName(),
						mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_HIT))
			{
				if (mLogicComponentEnemy->isStateChanged())
				{
					mRenderComponentParticleSystemShock->start();
					mAudioComponent->playSound(TRIPOLLO_SOUND_HIT);

					if(mRenderComponentEntityDreams.get())
					{
						mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_HIT01);
					}

					if(mRenderComponentEntityNightmares.get())
					{
						mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_HIT01);
					}

					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_DEAD))
			{
				if (mLogicComponentEnemy->isStateChanged())
				{
					mAudioComponent->playSound(TRIPOLLO_SOUND_DIE);
					mRenderComponentParticleSystemDie->start();

					if(mRenderComponentEntityDreams.get())
					{
						mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_DIE);
					}

					if(mRenderComponentEntityNightmares.get())
					{
						mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_DIE);
					}

					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getWorld());
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
			{
				//Logger::getInstance()->log("CHASE");
				if (mLogicComponentEnemy->isStateChanged())
				{
					if(mRenderComponentEntityDreams.get())
					{
						mRenderComponentEntityDreams->changeAnimation(TRIPOLLO_ANIM_WALK);
					}

					if(mRenderComponentEntityNightmares.get())
					{
						mRenderComponentEntityNightmares->changeAnimation(TRIPOLLO_ANIM_WALK);
					}

					mTrajectoryComponent->activateChase(mGameWorldManager->getGameObjectOny()->getName());
				}
			}
			else
			{
				//DO NOTHING
			}

			if(!currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE))
			{
				if(mRenderComponentEntityDreams.get())
				{
					mRenderComponentEntityDreams->update(elapsedSeconds);
				}

				if(mRenderComponentEntityNightmares.get())
				{
					mRenderComponentEntityNightmares->update(elapsedSeconds);
				}
			}

			mTrajectoryComponent->update(elapsedSeconds);

			if (mPhysicsComponentCharacter->isInUse())
			{
				mPhysicsComponentCharacter->setOuternMovement(mTrajectoryComponent->getNextMovementAbsolute());
			}
		}
	}
	else
	{		
		if (mRenderComponentEntityDreams.get())
			mRenderComponentEntityDreams->setVisible(false);
		if (mRenderComponentEntityNightmares.get())
			mRenderComponentEntityNightmares->setVisible(false);
		if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->destroy();
		}
	}
}

void GameObjectTripollo::postUpdate()
{
	GameObject::postUpdate();
}

AttackComponentPtr GameObjectTripollo::getAttackComponent() const
{
	return mAttackComponent;
}

void GameObjectTripollo::setAttackComponent(AttackComponentPtr attackComponent)
{
	mAttackComponent=attackComponent;
}

std::string GameObjectTripollo::getDefaultAttack()
{
	return TRIPOLLO_ATTACK_PECK;
}

void GameObjectTripollo::reset()
{
	GameObject::reset();

	LogicSubsystemPtr logicSS = getGameWorldManager()->getParent()->getLogicSubsystem();

	if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->reset();
		mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueDegrees());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);

	}		
	else
	{
		mPhysicsComponentCharacter->getSceneNode()->setPosition(mRenderComponentInitial->getPosition());
		mPhysicsComponentCharacter->getSceneNode()->setOrientation(mRenderComponentInitial->getOrientation());
		mLogicComponentEnemy->setHasDied(false);
		mLogicComponentEnemy->setHasBeenHit(false);

	}

	switch(mWorld)
	{
		case DREAMS:
			activateStatue(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			activateStatue(false);
			break;
		default:break;
	}

}

void GameObjectTripollo::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectTripollo::setNightmaresRender()
{
	if (!isEnabled()) return;

	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectTripollo::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponentEnemy->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponentEnemy->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectTripollo::setChangeWorldRender()
{
	if (!isEnabled()) return;
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			if(mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
			}	
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(false);
			}
			if(mLogicComponentEnemy->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}	
			break;
		default:break;
	}
}

void GameObjectTripollo::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			activateStatue(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			setNightmaresRender();
			activateStatue(false);
			break;
		default:break;
	}

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{

			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->destroy();
				}
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
				if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
				{
					mPhysicsComponentCharacter->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectTripollo::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			activateStatue(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			activateStatue(false);
			break;
		default:break;
	}

}

void GameObjectTripollo::changeToWorld(int newWorld, double perc)
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


void GameObjectTripollo::setTrajectoryComponent(TrajectoryComponentPtr pTrajectoryComponent)
{
	mTrajectoryComponent=pTrajectoryComponent;
}

TrajectoryComponentPtr GameObjectTripollo::getTrajectoryComponent()
{
	return mTrajectoryComponent;
}

bool GameObjectTripollo::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTripollo::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTripollo::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTripollo::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectTripollo::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
	}

	if(mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse() && pGameObject->getType().compare(GAME_OBJECT_TYPE_WATER)!=0)
	{
		mPhysicsComponentCharacter->calculateSliding(pNormal);
	}
}

void GameObjectTripollo::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectTripollo::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

bool GameObjectTripollo::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTripollo::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//
void GameObjectTripollo::processAnimationEnded(const std::string& animationName)
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

bool GameObjectTripollo::hasBeenHit() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasBeenHit();
	return false;
}

bool GameObjectTripollo::hasDied() const
{
	if (mLogicComponentEnemy.get())
		return mLogicComponentEnemy->hasDied();
	return false;
}

AudioComponentPtr GameObjectTripollo::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectTripollo::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

AudioComponentPtr GameObjectTripollo::getAudioComponentInstance() const
{
	return mAudioComponent;
}

bool GameObjectTripollo::hasAudioComponent() const
{
	return true;
}
void GameObjectTripollo::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponentEnemy->existsInDreams())
		{
			mRenderComponentEntityDreams->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentEnemy->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
bool GameObjectTripollo::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTripollo::getLogicComponentInstance() const
{
	return mLogicComponentEnemy;
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{

}