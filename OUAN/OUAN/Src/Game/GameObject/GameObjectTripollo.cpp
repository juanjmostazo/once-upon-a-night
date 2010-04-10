#include "GameObjectTripollo.h"

#include "GameObjectOny.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Utils/Utils.h"
#include "../../Logic/LogicSubsystem.h"

using namespace OUAN;



GameObjectTripollo::GameObjectTripollo(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIPOLLO)
{
	mRandomMovementDelay=-1;
}

GameObjectTripollo::~GameObjectTripollo()
{

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

void GameObjectTripollo::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectTripollo::getPhysicsComponentCharacter()
{
	return mPhysicsComponentCharacter;
}

void GameObjectTripollo::update(double elapsedSeconds)
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
				movement.x=Utils::Random::getInstance()->getRandomDouble(-3,3);
				movement.z=Utils::Random::getInstance()->getRandomDouble(-3,3);
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
					movement.x=Utils::Random::getInstance()->getRandomDouble(-3,3);
					movement.z=Utils::Random::getInstance()->getRandomDouble(-3,3);
				}
				
				/*
					If the object is currently at one marker, compute the displacement vector as
					(marker_n+1 - marker_n) (if it is the last one, marker_n+1 will be marker_0)
					There might be some kind of flag to select a patrol behaviour, but at the moment
					I'm just considering circular patrols
						- Traverse the patrol markers and then traverse them again in reverse order:
							0..1..2..3..2..1..0..1 (etc)
						- Traverse the patrol makers and from the last one move to the first one:
							0..1..2..3..0..1..2..3 (etc)
				*/
			}
			
		}
		else if (currentState==logicSS->getGlobalInt(TRIPOLLO_STATE_CHASE))
		{
			/*
				Set the displacementVector as ony.position-this.position
				until there is a walkability map, beware of collisions and chasms
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
				movement=movement/5;
			}
			
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

void GameObjectTripollo::reset()
{
	GameObject::reset();

	if (!mPhysicsComponentCharacter->isInUse())
	{
		mPhysicsComponentCharacter->create();
	}

	mPhysicsComponentCharacter->getNxOgreController()->setPosition(mRenderComponentInitial->getPosition());
	mPhysicsComponentCharacter->getNxOgreController()->setDisplayYaw(mRenderComponentInitial->getOrientation().getYaw().valueRadians());
}

void GameObjectTripollo::changeWorld(int world)
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
bool GameObjectTripollo::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTripollo::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------
TGameObjectTripolloParameters::TGameObjectTripolloParameters() : TGameObjectParameters()
{

}

TGameObjectTripolloParameters::~TGameObjectTripolloParameters()
{

}