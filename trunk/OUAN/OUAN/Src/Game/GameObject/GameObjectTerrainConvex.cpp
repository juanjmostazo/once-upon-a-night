#include "GameObjectTerrainConvex.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainConvex::GameObjectTerrainConvex(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TERRAINCONVEX)
{

}

GameObjectTerrainConvex::~GameObjectTerrainConvex()
{

}

void GameObjectTerrainConvex::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainConvex::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainConvex::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainConvex::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainConvex::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTerrainConvex::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTerrainConvex::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTerrainConvex::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTerrainConvex::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectTerrainConvex::getPhysicsComponentComplexConvex() const
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectTerrainConvex::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldFactor(0);
				mRenderComponentEntityNightmares->setVisible(false);
				mRenderComponentEntityNightmares->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
				mRenderComponentEntityNightmares->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityDreams->setChangeWorldFactor(0);
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityDreams->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldFactor(0);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}	
			break;
		default:break;
	}
}

void GameObjectTerrainConvex::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->randomizeChangeWorldMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->randomizeChangeWorldMaterials();
	}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
		}	
		break;
	default:
		break;
	}
}

void GameObjectTerrainConvex::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setChangeWorldFactor(1-perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(perc);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setChangeWorldFactor(perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setChangeWorldFactor(1-perc);
			}		
			break;
		default:
			break;
	}
}

void GameObjectTerrainConvex::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->update(elapsedSeconds);
	}
	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->update(elapsedSeconds);
	}

	//mRenderComponentEntityDreams->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
	//mRenderComponentEntityNightmares->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
}

void GameObjectTerrainConvex::reset()
{
	GameObject::reset();
}

bool GameObjectTerrainConvex::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTerrainConvex::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTerrainConvex::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTerrainConvex::getPhysicsComponent() const
{
	return getPhysicsComponentComplexConvex();
}


/// Set logic component
void GameObjectTerrainConvex::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTerrainConvex::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTerrainConvex::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTerrainConvex::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTerrainConvex::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTerrainConvex::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectTerrainConvex::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTerrainConvex::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------
TGameObjectTerrainConvexParameters::TGameObjectTerrainConvexParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainConvexParameters::~TGameObjectTerrainConvexParameters()
{

}
