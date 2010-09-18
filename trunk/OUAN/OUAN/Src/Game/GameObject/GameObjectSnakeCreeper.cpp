#include "OUAN_Precompiled.h"

#include "GameObjectSnakeCreeper.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectSnakeCreeper::GameObjectSnakeCreeper(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SNAKECREEPER)
{

}

GameObjectSnakeCreeper::~GameObjectSnakeCreeper()
{

}
/// Set logic component
void GameObjectSnakeCreeper::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectSnakeCreeper::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectSnakeCreeper::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectSnakeCreeper::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSnakeCreeper::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSnakeCreeper::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSnakeCreeper::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectSnakeCreeper::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSnakeCreeper::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectSnakeCreeper::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectSnakeCreeper::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectSnakeCreeper::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectSnakeCreeper::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectSnakeCreeper::changeWorldFinished(int newWorld)
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

void GameObjectSnakeCreeper::changeWorldStarted(int newWorld)
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

void GameObjectSnakeCreeper::changeToWorld(int newWorld, double perc)
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

void GameObjectSnakeCreeper::reset()
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

bool GameObjectSnakeCreeper::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSnakeCreeper::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectSnakeCreeper::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectSnakeCreeper::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}

void GameObjectSnakeCreeper::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject, pNormal);
	}
}

void GameObjectSnakeCreeper::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectSnakeCreeper::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

bool GameObjectSnakeCreeper::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectSnakeCreeper::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
bool GameObjectSnakeCreeper::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectSnakeCreeper::getLogicComponent() const
{
	return mLogicComponentEnemy;
}
//-------------------------------------------------------------------------------------------
TGameObjectSnakeCreeperParameters::TGameObjectSnakeCreeperParameters() : TGameObjectParameters()
{

}

TGameObjectSnakeCreeperParameters::~TGameObjectSnakeCreeperParameters()
{

}