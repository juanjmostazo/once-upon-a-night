#include "OUAN_Precompiled.h"

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

void GameObjectTerrainConvex::setDreamsRender()
{

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(true);
		mRenderComponentEntityDreams->setDreamsMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(false);
	}	
}

void GameObjectTerrainConvex::setNightmaresRender()
{
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setVisible(false);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setVisible(true);
		mRenderComponentEntityNightmares->setNightmaresMaterials();
	}	
}

void GameObjectTerrainConvex::setChangeWorldRender()
{
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityDreams->setChangeWorldMaterials();
			}
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
			}	
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntityDreams->setVisible(false);
			}
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				mRenderComponentEntityNightmares->setChangeWorldMaterials();
			}	
			break;
		default:break;
	}
}

void GameObjectTerrainConvex::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			break;
		case NIGHTMARES:
			setNightmaresRender();
			break;
		default:break;
	}

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
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

void GameObjectTerrainConvex::changeToWorld(int newWorld, double perc)
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
