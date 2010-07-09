#include "OUAN_Precompiled.h"

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
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_DREAMS))
		{
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_DREAMS,newWorld);
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
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_NIGHTMARES,newWorld);
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

		int currentState=mLogicComponentEnemy->getState();

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

			if(mRenderComponentEntityDreams.get())
			{
				mRenderComponentEntityDreams->update(elapsedSeconds);
			}

			if(mRenderComponentEntityNightmares.get())
			{
				mRenderComponentEntityNightmares->update(elapsedSeconds);
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

void GameObjectTripolloDreams::setDreamsRender()
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

void GameObjectTripolloDreams::setNightmaresRender()
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

void GameObjectTripolloDreams::setChangeWorldRender()
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


void GameObjectTripolloDreams::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			break;
		case NIGHTMARES:
			setNightmaresRender();
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
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
			{
			}
			else if(mLogicComponentEnemy->existsInDreams()&& !mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
			}
			else if(!mLogicComponentEnemy->existsInDreams()&& mLogicComponentEnemy->existsInNightmares())
			{
				activateTrajectory(newWorld);
			}	
			break;
		default:break;
	}
}

void GameObjectTripolloDreams::changeWorldStarted(int newWorld)
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

void GameObjectTripolloDreams::changeToWorld(int newWorld, double perc)
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


void GameObjectTripolloDreams::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
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
void GameObjectTripolloDreams::setVisible(bool visible)
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
//-------------------------------------------------------------------------------------------
TGameObjectTripolloDreamsParameters::TGameObjectTripolloDreamsParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloDreamsParameters::~TGameObjectTripolloDreamsParameters()
{

}