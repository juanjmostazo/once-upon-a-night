#include "GameObjectWater.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectWater::GameObjectWater(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_WATER)
{

}

GameObjectWater::~GameObjectWater()
{

}

void GameObjectWater::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectWater::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectWater::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectWater::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectWater::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectWater::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectWater::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectWater::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectWater::setPhysicsComponentVolumeConvex(PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex)
{
	mPhysicsComponentVolumeConvex=pPhysicsComponentVolumeConvex;
	mPhysicsComponentVolumeConvex->create();
}

PhysicsComponentVolumeConvexPtr GameObjectWater::getPhysicsComponentVolumeConvex() const
{
	return mPhysicsComponentVolumeConvex;
}

void GameObjectWater::changeWorld(int world)
{
	if (!isEnabled()) return;

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

void GameObjectWater::reset()
{
	GameObject::reset();
}

bool GameObjectWater::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectWater::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectWater::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectWater::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeConvex();
}


/// Set logic component
void GameObjectWater::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectWater::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectWater::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectWater::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectWater::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectWater::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectWater::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectWater::getEntityComponent() const
{
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
TGameObjectWaterParameters::TGameObjectWaterParameters() : TGameObjectParameters()
{

}

TGameObjectWaterParameters::~TGameObjectWaterParameters()
{

}
