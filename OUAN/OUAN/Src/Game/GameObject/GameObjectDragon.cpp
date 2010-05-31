#include "GameObjectDragon.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectDragon::GameObjectDragon(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DRAGON)
{

}

GameObjectDragon::~GameObjectDragon()
{

}
/// Set logic component
void GameObjectDragon::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectDragon::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}

void GameObjectDragon::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDragon::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDragon::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDragon::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDragon::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDragon::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDragon::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDragon::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectDragon::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectDragon::getPhysicsComponentCharacter() const
{ 
	return mPhysicsComponentCharacter;
}

void GameObjectDragon::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
}

void GameObjectDragon::reset()
{
	GameObject::reset();

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

void GameObjectDragon::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			break;
		case NIGHTMARES:
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
			break;
		default:break;
	}
}

void GameObjectDragon::changeWorldStarted(int newWorld)
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

void GameObjectDragon::changeToWorld(int newWorld, double perc)
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

int GameObjectDragon::getTimeStunned() const
{
	//TODO: Define somewhere a stunned counter for the dragon and update
	// it accordingly; then, use that value here
	return 0;
}

bool GameObjectDragon::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDragon::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectDragon::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectDragon::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectDragon::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

void GameObjectDragon::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectDragon::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectDragon::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}
bool GameObjectDragon::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDragon::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectDragonParameters::TGameObjectDragonParameters() : TGameObjectParameters()
{

}

TGameObjectDragonParameters::~TGameObjectDragonParameters()
{

}