#include "GameObjectTripolloDreams.h"

#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Graphics/TrajectoryManager/Trajectory.h"
#include "../../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../../Graphics/TrajectoryManager/TrajectoryNode.h"

using namespace OUAN;



GameObjectTripolloDreams::GameObjectTripolloDreams(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{
	mRandomMovementDelay=-1;
}

GameObjectTripolloDreams::~GameObjectTripolloDreams()
{

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

PhysicsComponentCharacterPtr GameObjectTripolloDreams::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectTripolloDreams::update(double elapsedSeconds)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
	LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();
	//
	int currentState=mLogicComponent->getState();
	if (mPhysicsComponentCharacter.get())
	{
		NxOgre::Vec3 movement=mPhysicsComponentCharacter->getLastMovement();
		if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_IDLE))
		{
			movement=NxOgre::Vec3::ZERO;
			mPatrol=NULL;
			mNextPatrolPoint=-1;
		}
		else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_PATROL))
		{				

			if (mLogicComponent->isStateChanged())
			{
				/*
					If the state has just changed, then load the trajectory and set the displacement
					vector as (marker1-marker0)
				*/

				mRandomMovementDelay=Utils::Random::getInstance()->getRandomInteger(MIN_RANDOM_MOVEMENT_DELAY,MAX_RANDOM_MOVEMENT_DELAY);
				movement.x=Utils::Random::getInstance()->getRandomDouble(-1,1);
				movement.z=Utils::Random::getInstance()->getRandomDouble(-1,1);

			}
			else
			{
				if (mRandomMovementDelay>=0)
				{
					mRandomMovementDelay-=elapsedSeconds*1000;
				}
				else
				{
					mRandomMovementDelay=Utils::Random::getInstance()->getRandomInteger(MIN_RANDOM_MOVEMENT_DELAY,MAX_RANDOM_MOVEMENT_DELAY);
					movement.x=Utils::Random::getInstance()->getRandomDouble(-1,1);
					movement.z=Utils::Random::getInstance()->getRandomDouble(-1,1);
				}
			}
			
		}
		else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
		{
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
			*/
			movement=NxOgre::Vec3::ZERO;
			if (mGameWorldManager.get() && mGameWorldManager->getGameObjectOny().get())
			{
				Vector3 chaseDirection= mGameWorldManager->getGameObjectOny()->getRenderComponentPositional()->getPosition()-
					mRenderComponentPositional->getPosition();
				chaseDirection.normalise();
				movement.x=chaseDirection.x;
				movement.y=chaseDirection.y;
				movement.z=chaseDirection.z;
				movement=movement/5; //temporary hack: decrease the chase speed for the time being 
									// so Ony can escape from the tripollo's reach
			}
			mPatrol=NULL;
			mNextPatrolPoint=-1;
			
		}
		else
		{
			mPatrol=NULL;
			mNextPatrolPoint=-1;
		}
		if (mPhysicsComponentCharacter->isInUse())
		{
			bool rotate = movement!=NxOgre::Vec3::ZERO;
			mPhysicsComponentCharacter->setLastMovement(movement);
			mPhysicsComponentCharacter->setNextMovement(movement);
			mPhysicsComponentCharacter->update(elapsedSeconds);
			if (rotate)
				mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(
					mPhysicsComponentCharacter->getNxOgreController()->getDisplayYaw()+180
			);
		}
	}

	//if (mPhysicsComponentCharacter.get() && mPhysicsComponentCharacter->isInUse())
	//{

	
	//	//mPhysicsComponentCharacter->getNxOgreController()->move(
	//	//	getPhysicsComponentCharacter()->getNextMovement()+
	//	//	Application::getInstance()->getPhysicsSubsystem()->mGravity* 
	//	//	Application::getInstance()->getPhysicsSubsystem()->mDisplacementScale,
	//	//	GROUP_COLLIDABLE_MASK,
	//	//	Application::getInstance()->getPhysicsSubsystem()->mMinDistance,
	//	//	collisionFlags);
	//}
}

void GameObjectTripolloDreams::reset()
{
	GameObject::reset();

	if (!mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}

	mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
}

void GameObjectTripolloDreams::changeWorld(int world)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
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
		if (mPhysicsComponentCharacter.get() && !mPhysicsComponentCharacter->isInUse())
		{
			mPhysicsComponentCharacter->create();
		}
		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			
			if(mLogicComponent->existsInDreams())
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
			
			if(mLogicComponent->existsInNightmares())
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
	}
}
bool GameObjectTripolloDreams::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTripolloDreams::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloDreamsParameters::TGameObjectTripolloDreamsParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloDreamsParameters::~TGameObjectTripolloDreamsParameters()
{

}