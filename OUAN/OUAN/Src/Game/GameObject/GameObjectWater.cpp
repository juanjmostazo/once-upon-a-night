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

void GameObjectWater::setRenderComponentWaterDreams(RenderComponentWaterPtr pRenderComponentWaterDreams)
{
	mRenderComponentWaterDreams=pRenderComponentWaterDreams;
}

RenderComponentWaterPtr GameObjectWater::getRenderComponentWaterDreams() const
{
	return mRenderComponentWaterDreams;
}

void GameObjectWater::setRenderComponentWaterNightmares(RenderComponentWaterPtr pRenderComponentWaterNightmares)
{
	mRenderComponentWaterNightmares=pRenderComponentWaterNightmares;
}

RenderComponentWaterPtr GameObjectWater::getRenderComponentWaterNightmares() const
{
	return mRenderComponentWaterNightmares;
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

void GameObjectWater::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentWaterDreams->setVisible(true);
			}
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setVisible(false);
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentWaterDreams->setVisible(false);
			}
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setVisible(true);
			}
			break;
		default:break;
	}
}

void GameObjectWater::changeWorldStarted(int newWorld)
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

void GameObjectWater::changeToWorld(int newWorld, double perc)
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

void GameObjectWater::update(double elapsedTime)
{
	GameObject::update(elapsedTime);
	switch(mGameWorldManager->getWorld())
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentWaterDreams->update(elapsedTime);
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->update(elapsedTime);
			}
			break;
		default:break;
	}
}

void GameObjectWater::postUpdate()
{
	GameObject::postUpdate();
	switch(mGameWorldManager->getWorld())
	{
		case DREAMS:	
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentWaterDreams->postUpdate();
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->postUpdate();
			}
			break;
		default:break;
	}
}


//bool GameObjectWater::hasRenderComponentEntity() const
//{
//	return true;
//}
//RenderComponentEntityPtr GameObjectWater::getEntityComponent() const
//{
//	if(mGameWorldManager->getWorld()==DREAMS)
//	{
//		return mRenderComponentWaterDreams->getRenderComponentEntity()
//	}
//	else:mRenderComponentWaterNightmares;
//}
TGameObjectWaterParameters::TGameObjectWaterParameters() : TGameObjectParameters()
{

}

TGameObjectWaterParameters::~TGameObjectWaterParameters()
{

}
