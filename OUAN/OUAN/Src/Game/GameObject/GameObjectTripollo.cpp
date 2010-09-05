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


void GameObjectTripollo::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{
		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();


		int currentState=mLogicComponentEnemy->getState();


		if (mPhysicsComponentCharacter.get())
		{
			int world = mGameWorldManager->getWorld();

			RenderComponentEntityPtr entity;
			if (world == DREAMS && mRenderComponentEntityDreams.get())
				entity = mRenderComponentEntityDreams;
			else if (world ==NIGHTMARES && mLogicComponentEnemy->existsInNightmares() &&
					mRenderComponentEntityNightmares.get())
				entity = mRenderComponentEntityNightmares;

			if (entity.get())
			{
				std::string onyName = mGameWorldManager->getGameObjectOny()->getName();

				if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE) && 
					mLogicComponentEnemy->isStateChanged())
				{
					entity->changeAnimation(TRIPOLLO_ANIM_STATUE);
					mTrajectoryComponent->activateIdle(getName(),world);
				}
				//Check for state changes and update things appropriately
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_IDLE);
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState == logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE1))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_IDLE1);
						//Idle 1 can only come from idle, so there is no trajectory change
					}
				}
				else if (currentState == logicSS->getGlobalInt(TRIPOLLO_STATE_SURPRISE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_SURPRISE);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setSurpriseFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
				{				
					if (mLogicComponentEnemy->isStateChanged())
					{
						if(activateTrajectory(mGameWorldManager->getWorld()))
						{
							entity->changeAnimation(TRIPOLLO_ANIM_WALK);
						}
						else
						{
							entity->changeAnimation(TRIPOLLO_ANIM_IDLE);
						}
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FIND))
				{
					//Logger::getInstance()->log("FIND");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_WALK_FAST);
						mTrajectoryComponent->activatePathFinding(onyName,world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FALSE_ALARM))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_FALSE_ALARM);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setFalseAlarmFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_ALERT))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_ALERT);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setAlertFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
				{			
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_RUN);
						mTrajectoryComponent->activateChase(onyName);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_TIRED))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_TIRED);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setTiredFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_ATTACK))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(Utils::Random::getInstance()->getRandomDouble()>0.5
							?TRIPOLLO_ANIM_ATTACK_00
							:TRIPOLLO_ANIM_ATTACK_01);
						mTrajectoryComponent->activateChase(onyName);
						mLogicComponentEnemy->setAttackFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FLEE))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_RUN);
						mTrajectoryComponent->activateFlee(onyName);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_HIT))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						mRenderComponentParticleSystemShock->start();
						mAudioComponent->playSound(TRIPOLLO_SOUND_HIT);

						entity->changeAnimation(Utils::Random::getInstance()->getRandomDouble()>0.5
							?TRIPOLLO_ANIM_HIT01
							:TRIPOLLO_ANIM_HIT02);

						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CALL_TO_ARMS))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_CALL_TO_ARMS);
						double range = logicSS->getGlobalReal("MELEE_RANGE");
						bool callHeard = callNeighboursInRange(range);
						mLogicComponentEnemy->setCallWasHeard(callHeard);
						mTrajectoryComponent->activateIdle(getName(),world);
						mLogicComponentEnemy->setCallToArmsFinished(false);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_TREMBLING))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_AFRAID);					
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CALL_TO_CHASE))
				{
					//Logger::getInstance()->log("CHASE");
					if (mLogicComponentEnemy->isStateChanged())
					{
						entity->changeAnimation(TRIPOLLO_ANIM_RUN);
						mTrajectoryComponent->activateChase(onyName);
					}
				}
				else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_DEAD))
				{
					if (mLogicComponentEnemy->isStateChanged())
					{
						mAudioComponent->playSound(TRIPOLLO_SOUND_DIE);
						mRenderComponentParticleSystemDie->start();

						entity->changeAnimation(TRIPOLLO_ANIM_DIE);
						mTrajectoryComponent->activateIdle(getName(),world);
					}
				}
				else
				{
					//DO NOTHING
				}

				if(currentState!=logicSS->getGlobalInt(TRIPOLLO_STATE_STATUE))
				{
					entity->update(elapsedSeconds);
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
			//activateStatue(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			//activateStatue(false);
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
			mLogicComponentEnemy->setStatueEnabled(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			setNightmaresRender();
			if (mLogicComponentEnemy->isStatueEnabled())
				mLogicComponentEnemy->setStatueEnabled(false);
			else mLogicComponentEnemy->setState(Application::getInstance()->getLogicSubsystem()->getGlobalInt(TRIPOLLO_STATE_IDLE));
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
			mLogicComponentEnemy->setStatueEnabled(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			//activateStatue(mLogicComponentEnemy->getEnemyType()==ENEMY_TYPE_STATUE);
			break;
		case NIGHTMARES:
			//activateStatue(false);
			mLogicComponentEnemy->setStatueEnabled(false);
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
	if (animationName.compare(TRIPOLLO_ANIM_HIT01)==0 || 
		animationName.compare(TRIPOLLO_ANIM_HIT02)==0)
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
	if (animationName.compare(TRIPOLLO_ANIM_ALERT)==0)
	{
		mLogicComponentEnemy->setAlertFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_ATTACK_00)==0 || 
		animationName.compare(TRIPOLLO_ANIM_ATTACK_01)==0)
	{
		mLogicComponentEnemy->setAttackFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_CALL_TO_ARMS)==0)
	{
		mLogicComponentEnemy->setCallToArmsFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_SURPRISE)==0)
	{
		mLogicComponentEnemy->setSurpriseFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_FALSE_ALARM)==0)
	{
		mLogicComponentEnemy->setFalseAlarmFinished(true);
	}
	if (animationName.compare(TRIPOLLO_ANIM_TIRED)==0)
	{
		mLogicComponentEnemy->setTiredFinished(true);
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

double GameObjectTripollo::getMeleeRange() const
{
	if (mAttackComponent.get())
	{
		return mAttackComponent->getSelectedAttack()->attackRange;
	}
	return 0;
}

int GameObjectTripollo::countNeighboursInRange(double range, bool call) const
{
	std::string name= getName();
	TGameObjectTripolloContainer* tripollos= mGameWorldManager->getGameObjectTripolloContainer();
	if (!tripollos->empty())
	{
		int neighbours=0;
		double currentDistance=0;
		GameObjectTripolloPtr tripollo;
		for (TGameObjectTripolloContainer::iterator it=tripollos->begin();it!=tripollos->end();++it)
		{
			tripollo = *it;
			currentDistance= computeDistanceTo(tripollo);
			if (tripollo->isEnabled() && currentDistance<range && 
				tripollo->getName().compare(name)!=0)
			{
				if (call) 
					tripollo->getLogicComponentEnemy()->setHasHeardCall(true);
				neighbours++;
			}
		}
		return neighbours;
	}
	return 0;
}
bool GameObjectTripollo::isStatueEnabled() const
{
	return mLogicComponentEnemy->isStatueEnabled();
}

//-------------------------------------------------------------------------------------------
TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{

}