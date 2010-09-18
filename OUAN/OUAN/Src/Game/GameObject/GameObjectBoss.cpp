#include "OUAN_Precompiled.h"

#include "GameObjectBoss.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

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

void GameObjectBoss::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
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
}

void GameObjectBoss::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			break;
		case NIGHTMARES:
			break;
		default:break;
	}
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