#include "GameObjectCarnivorousPlant.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectCarnivorousPlant::GameObjectCarnivorousPlant(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CARNIVOROUSPLANT)
{

}

GameObjectCarnivorousPlant::~GameObjectCarnivorousPlant()
{

}
/// Set logic component
void GameObjectCarnivorousPlant::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

/// return logic component
LogicComponentEnemyPtr GameObjectCarnivorousPlant::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}
void GameObjectCarnivorousPlant::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectCarnivorousPlant::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectCarnivorousPlant::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectCarnivorousPlant::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectCarnivorousPlant::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectCarnivorousPlant::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectCarnivorousPlant::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectCarnivorousPlant::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectCarnivorousPlant::setPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	mPhysicsComponentCharacter=pPhysicsComponentCharacter;
}

PhysicsComponentCharacterPtr GameObjectCarnivorousPlant::getPhysicsComponentCharacter() const
{
	return mPhysicsComponentCharacter;
}

void GameObjectCarnivorousPlant::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
}

void GameObjectCarnivorousPlant::reset()
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

void GameObjectCarnivorousPlant::changeWorld(int world)
{
	if (!isEnabled()) return;

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
		default:break;
	}
}

bool GameObjectCarnivorousPlant::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectCarnivorousPlant::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectCarnivorousPlant::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectCarnivorousPlant::getPhysicsComponent() const
{
	return getPhysicsComponentCharacter();
}


void GameObjectCarnivorousPlant::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

void GameObjectCarnivorousPlant::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectCarnivorousPlant::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectCarnivorousPlant::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}
bool GameObjectCarnivorousPlant::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectCarnivorousPlant::getEntityComponent() const
{
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectCarnivorousPlantParameters::TGameObjectCarnivorousPlantParameters() : TGameObjectParameters()
{

}

TGameObjectCarnivorousPlantParameters::~TGameObjectCarnivorousPlantParameters()
{

}