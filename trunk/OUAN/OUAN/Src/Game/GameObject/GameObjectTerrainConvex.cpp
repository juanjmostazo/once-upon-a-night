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

PhysicsComponentComplexConvexPtr GameObjectTerrainConvex::getPhysicsComponentComplexConvex()
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectTerrainConvex::changeWorld(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
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
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
			}	
			break;
		default:break;
	}
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

//-------------------------------------------------------------------------------------------
TGameObjectTerrainConvexParameters::TGameObjectTerrainConvexParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainConvexParameters::~TGameObjectTerrainConvexParameters()
{

}
