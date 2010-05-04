#include "GameObjectTentetieso.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTentetieso::GameObjectTentetieso(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TENTETIESO)
{

}

GameObjectTentetieso::~GameObjectTentetieso()
{

}

void GameObjectTentetieso::setLogicComponentEnemy(LogicComponentEnemyPtr logicComponentEnemy)
{
	mLogicComponentEnemy=logicComponentEnemy;
}

LogicComponentEnemyPtr GameObjectTentetieso::getLogicComponentEnemy()
{
	return mLogicComponentEnemy;
}

void GameObjectTentetieso::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTentetieso::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTentetieso::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTentetieso::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTentetieso::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTentetieso::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTentetieso::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTentetieso::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTentetieso::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectTentetieso::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectTentetieso::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	RenderComponentEntityPtr entityToUpdate = (mGameWorldManager->getCurrentWorld()==DREAMS)
		?mRenderComponentEntityDreams
		:mRenderComponentEntityNightmares;

	if (isFirstUpdate())
	{
		entityToUpdate->changeAnimation("attack01_Clip");
	}

	entityToUpdate->update(elapsedSeconds/2);
}

void GameObjectTentetieso::reset()
{
	GameObject::reset();

	changeWorld(DREAMS);

}

void GameObjectTentetieso::changeWorld(int world)
{
	if (!isEnabled()) return;

	if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->create();
	}

	switch(world)
	{
		case DREAMS:
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
			mRenderComponentEntityDreams->changeAnimation("attack01_Clip");
			break;
		case NIGHTMARES:
			mRenderComponentEntityDreams->setVisible(false);			
			mRenderComponentEntityNightmares->setVisible(true);
			mRenderComponentEntityNightmares->changeAnimation("attack01_Clip");
			break;
		default:break;
	}
}

bool GameObjectTentetieso::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTentetieso::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTentetieso::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTentetieso::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}


void GameObjectTentetieso::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processCollision(pGameObject);
	}
}

void GameObjectTentetieso::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processEnterTrigger(pGameObject);
	}
}

void GameObjectTentetieso::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->processExitTrigger(pGameObject);
	}
}

void GameObjectTentetieso::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentEnemy.get())
	{
		mLogicComponentEnemy->update(elapsedSeconds);
	}
}
bool GameObjectTentetieso::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTentetieso::getEntityComponent() const
{
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectTentetiesoParameters::TGameObjectTentetiesoParameters() : TGameObjectParameters()
{

}

TGameObjectTentetiesoParameters::~TGameObjectTentetiesoParameters()
{

}