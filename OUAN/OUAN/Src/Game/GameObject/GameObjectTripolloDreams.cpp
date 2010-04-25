#include "GameObjectTripolloDreams.h"
#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/TrajectoryManager/TrajectoryComponent.h"

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

void GameObjectTripolloDreams::activateTrajectory(int world)
{
	if(world==DREAMS)
	{
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_TRAJECTORY_DREAMS))
		{
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_TRAJECTORY_DREAMS,world);
		}
		else
		{
			mTrajectoryComponent->activateIdle(getName(),world);
		}
	}
	else if(world==NIGHTMARES)
	{
		if(mTrajectoryComponent->predefinedTrajectoryExists(getName()+SUFFIX_TRAJECTORY_NIGHTMARES))
		{
			mTrajectoryComponent->activatePredefinedTrajectory(getName()+SUFFIX_TRAJECTORY_NIGHTMARES,world);
		}
		else
		{
			mTrajectoryComponent->activateIdle(getName(),world);
		}
	}
}

void GameObjectTripolloDreams::update(double elapsedSeconds)
{
	if (isEnabled())
	{
		GameObject::update(elapsedSeconds);

		unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		//debug code, erase when it works
		//if(getName().compare("tripollo#12")!=0)
		//	return;

		RenderComponentEntityPtr entityToUpdate = (mGameWorldManager->getCurrentWorld()==DREAMS)
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
					mTrajectoryComponent->activateIdle(getName(),mGameWorldManager->getCurrentWorld());
				}

			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
			{				
				if (mLogicComponentEnemy->isStateChanged())
				{
					activateTrajectory(mGameWorldManager->getCurrentWorld());
					/*
						If the state has just changed, then load the trajectory and set the displacement
						vector as (marker1-marker0)
					*/
					if (entityToUpdate.get())
						entityToUpdate->changeAnimation(TRIPOLLO_ANIM_WALK);
				}
			}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_FIND))
			{
				//Ogre::LogManager::getSingleton().logMessage("FIND");
				if (entityToUpdate.get() && mLogicComponentEnemy->isStateChanged())
				{
					entityToUpdate->changeAnimation(TRIPOLLO_ANIM_WALK);

					mTrajectoryComponent->activatePathFinding(
						mGameWorldManager->getGameObjectOny()->getName(),
						mGameWorldManager->getCurrentWorld());
				}

				/*
				
					TODO: Instead of getting a direct vector to Ony, such as we're doing at the moment,
					compute a trajectory of nodes via an A* implementation.

					For the sake of efficiency, here are two suggestions that I recall from the pathfinding classes:
						- It may be useful to keep a structure containing precalculated paths between pairs of nodes. By doing this, 
						only one invocation would be needed at the beginning, as the path might be retrieved in practically constant time.
						- If the first option isn't chosen, don't invoke the A* on every tick. There should be some kind of constraint, such as:
							- not to recompute the trajectory unless the distance between A*'s last destination node and Ony's current position
							  exceeds a given value
							- wait for a given amount of time before callin A* again

							<---- 
							If its not fast enough we could use dynamic programming and keep the list.
							The trajectory will be computed every certain time (see Trajectory::recalculateTime) 
							recalculateTime has a random component so every object calculates at different periods
				*/
			}
			//else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_DEAD))
			//{
			//	std::string msg="Enemy ";
			//	msg.append(getName()).append(" died");
			//	Ogre::LogManager::getSingletonPtr()->logMessage(msg);
			//	disable();
			//}
			else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
			{
				//Ogre::LogManager::getSingleton().logMessage("CHASE");
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

				//Ogre::LogManager::getSingleton().logMessage("[Movement] "+getName()+" "+Ogre::StringConverter::toString(movement));
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
	//TODO ERASE THIS WHEN PROPERLY DONE IN XSI
	mRenderComponentPositional->setPosition(mRenderComponentPositional->getPosition()+Vector3(0,-9.7,0));
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

void GameObjectTripolloDreams::changeWorld(int world)
{
	if (!isEnabled()) return;

	if(mLogicComponentEnemy->existsInDreams() && mLogicComponentEnemy->existsInNightmares())
	{
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
			}
		activateTrajectory(world);
	}
	else
	{
		switch(world)
		{
			case DREAMS:
				
				if(mLogicComponentEnemy->existsInDreams())
				{
					mRenderComponentEntityDreams->setVisible(true);
					if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
					{
						mPhysicsComponentCharacter->create();
					}
				}
				else
				{
					mRenderComponentEntityNightmares->setVisible(false);
					if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
					{
						mPhysicsComponentCharacter->destroy();
					}
				}		
				break;
			case NIGHTMARES:
				
				if(mLogicComponentEnemy->existsInNightmares())
				{
					mRenderComponentEntityNightmares->setVisible(true);
					if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
					{
						mPhysicsComponentCharacter->create();
					}
				}
				else
				{
					mRenderComponentEntityDreams->setVisible(false);
					if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
					{
						mPhysicsComponentCharacter->destroy();
					}
				}
				break;
			default:
				break;
		}
		activateTrajectory(world);
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
	if (mLogicComponentEnemy.get())
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
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloDreamsParameters::TGameObjectTripolloDreamsParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloDreamsParameters::~TGameObjectTripolloDreamsParameters()
{

}