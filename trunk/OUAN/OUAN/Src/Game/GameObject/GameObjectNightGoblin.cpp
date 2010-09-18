#include "OUAN_Precompiled.h"

#include "GameObjectNightGoblin.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectNightGoblin::GameObjectNightGoblin(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CRYKING)
{

}

GameObjectNightGoblin::~GameObjectNightGoblin()
{

}
/// Set logic component
void GameObjectNightGoblin::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectNightGoblin::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectNightGoblin::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectNightGoblin::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectNightGoblin::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectNightGoblin::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectNightGoblin::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectNightGoblin::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectNightGoblin::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectNightGoblin::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectNightGoblin::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectNightGoblin::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectNightGoblin::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
}

void GameObjectNightGoblin::reset()
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

void GameObjectNightGoblin::changeWorldFinished(int newWorld)
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

void GameObjectNightGoblin::changeWorldStarted(int newWorld)
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

void GameObjectNightGoblin::changeToWorld(int newWorld, double perc)
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

bool GameObjectNightGoblin::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectNightGoblin::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectNightGoblin::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectNightGoblin::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}

void GameObjectNightGoblin::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
	}
}

void GameObjectNightGoblin::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectNightGoblin::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

bool GameObjectNightGoblin::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectNightGoblin::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
bool GameObjectNightGoblin::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectNightGoblin::getLogicComponent() const
{
	return mLogicComponentEnemy;
}
//-------------------------------------------------------------------------------------------
TGameObjectNightGoblinParameters::TGameObjectNightGoblinParameters() : TGameObjectParameters()
{

}

TGameObjectNightGoblinParameters::~TGameObjectNightGoblinParameters()
{

}