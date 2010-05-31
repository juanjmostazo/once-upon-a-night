#include "GameObjectBee_Butterfly.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectBee_Butterfly::GameObjectBee_Butterfly(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BEE_BUTTERFLY)
{

}

GameObjectBee_Butterfly::~GameObjectBee_Butterfly()
{

}
/// Set logic component
void GameObjectBee_Butterfly::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectBee_Butterfly::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}

void GameObjectBee_Butterfly::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBee_Butterfly::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBee_Butterfly::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBee_Butterfly::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBee_Butterfly::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

void GameObjectBee_Butterfly::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectBee_Butterfly::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectBee_Butterfly::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectBee_Butterfly::setPhysicsComponentCharacterDreams(PhysicsComponentCharacterPtr pPhysicsComponentCharacterDreams)
{
	mPhysicsComponentCharacterDreams=pPhysicsComponentCharacterDreams;
}

PhysicsComponentCharacterPtr GameObjectBee_Butterfly::getPhysicsComponentCharacterDreams() const
{
	return mPhysicsComponentCharacterDreams;
}

void GameObjectBee_Butterfly::setPhysicsComponentCharacterNightmares(PhysicsComponentCharacterPtr pPhysicsComponentCharacterNightmares)
{
	mPhysicsComponentCharacterNightmares=pPhysicsComponentCharacterNightmares;
}

PhysicsComponentCharacterPtr GameObjectBee_Butterfly::getPhysicsComponentCharacterNightmares() const
{
	return mPhysicsComponentCharacterNightmares;
}

void GameObjectBee_Butterfly::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectBee_Butterfly::reset()
{
	GameObject::reset();

	mPhysicsComponentCharacterDreams->reset();
	mPhysicsComponentCharacterNightmares->reset();
}

bool GameObjectBee_Butterfly::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBee_Butterfly::getPositionalComponent() const
{
	return getRenderComponentPositional();
}


void GameObjectBee_Butterfly::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

bool GameObjectBee_Butterfly::hasPhysicsComponent() const
{
	return false;
}
PhysicsComponentPtr GameObjectBee_Butterfly::getPhysicsComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)
		?getPhysicsComponentCharacterDreams()
		:getPhysicsComponentCharacterNightmares();
}


void GameObjectBee_Butterfly::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectBee_Butterfly::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectBee_Butterfly::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}

void GameObjectBee_Butterfly::changeWorldFinished(int newWorld)
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

void GameObjectBee_Butterfly::changeWorldStarted(int newWorld)
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

void GameObjectBee_Butterfly::changeToWorld(int newWorld, double perc)
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

bool GameObjectBee_Butterfly::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectBee_Butterfly::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectBee_ButterflyParameters::TGameObjectBee_ButterflyParameters() : TGameObjectParameters()
{

}

TGameObjectBee_ButterflyParameters::~TGameObjectBee_ButterflyParameters()
{

}