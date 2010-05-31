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
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setVisible(true);
				mRenderComponentWaterNightmares->setVisible(false);
				if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setVisible(true);
				if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setVisible(false);
				if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setVisible(false);
				mRenderComponentWaterNightmares->setVisible(true);
				if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setVisible(false);
				if (mPhysicsComponentVolumeConvex.get() && mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setVisible(true);
				if (mPhysicsComponentVolumeConvex.get() && !mPhysicsComponentVolumeConvex->isInUse())
				{
					mPhysicsComponentVolumeConvex->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectWater::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentWaterDreams->randomizeChangeWorldMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentWaterNightmares->randomizeChangeWorldMaterials();
	}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentWaterDreams->setVisible(true);
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentWaterNightmares->setVisible(true);
		}	
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
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setChangeWorldFactor(perc);
				mRenderComponentWaterDreams->setChangeWorldFactor(1-perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setChangeWorldFactor(1-perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setChangeWorldFactor(perc);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setChangeWorldFactor(1-perc);
				mRenderComponentWaterDreams->setChangeWorldFactor(perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterDreams->setChangeWorldFactor(perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentWaterNightmares->setChangeWorldFactor(1-perc);
			}		
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
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentWaterDreams->update(elapsedTime);
	}
	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentWaterNightmares->update(elapsedTime);
	}
}

void GameObjectWater::postUpdate()
{
	GameObject::postUpdate();
	switch(mWorld)
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


//bool GameObjectWater::hasRenderComponentWater() const
//{
//	return true;
//}
//RenderComponentWaterPtr GameObjectWater::getWaterComponent() const
//{
//	if(mGameWorldManager->getWorld()==DREAMS)
//	{
//		return mRenderComponentWaterDreams->getRenderComponentWater()
//	}
//	else:mRenderComponentWaterNightmares;
//}
TGameObjectWaterParameters::TGameObjectWaterParameters() : TGameObjectParameters()
{

}

TGameObjectWaterParameters::~TGameObjectWaterParameters()
{

}
