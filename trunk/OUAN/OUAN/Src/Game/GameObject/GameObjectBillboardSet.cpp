#include "OUAN_Precompiled.h"

#include "GameObjectBillboardSet.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectBillboardSet::GameObjectBillboardSet(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BILLBOARDSET)
{

}

GameObjectBillboardSet::~GameObjectBillboardSet()
{

}

RenderComponentBillboardSetPtr GameObjectBillboardSet::getRenderComponentBillboardSetDreams() const
{
	return mRenderComponentBillboardSetDreams;
}

void GameObjectBillboardSet::setRenderComponentBillboardSetDreams(RenderComponentBillboardSetPtr pRenderComponentBillboardSet)
{
	mRenderComponentBillboardSetDreams=pRenderComponentBillboardSet;
}

RenderComponentBillboardSetPtr GameObjectBillboardSet::getRenderComponentBillboardSetNightmares() const
{
	return mRenderComponentBillboardSetNightmares;
}

void GameObjectBillboardSet::setRenderComponentBillboardSetNightmares(RenderComponentBillboardSetPtr pRenderComponentBillboardSet)
{
	mRenderComponentBillboardSetNightmares=pRenderComponentBillboardSet;
}

void GameObjectBillboardSet::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBillboardSet::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBillboardSet::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBillboardSet::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBillboardSet::changeWorldFinished(int newWorld)
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
}

void GameObjectBillboardSet::setDreamsRender()
{

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentBillboardSetDreams->setVisible(true);
		mRenderComponentBillboardSetDreams->setDreamsMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentBillboardSetNightmares->setVisible(false);
	}	
}

void GameObjectBillboardSet::setNightmaresRender()
{
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentBillboardSetDreams->setVisible(false);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentBillboardSetNightmares->setVisible(true);
		mRenderComponentBillboardSetNightmares->setNightmaresMaterials();
	}	
}

void GameObjectBillboardSet::setChangeWorldRender()
{
	switch(mWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(true);
				mRenderComponentBillboardSetDreams->setChangeWorldMaterials();
				mRenderComponentBillboardSetNightmares->setVisible(false);
			}
			else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setVisible(true);
				mRenderComponentBillboardSetNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(true);
				mRenderComponentBillboardSetDreams->setChangeWorldMaterials();
			}
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setVisible(true);
				mRenderComponentBillboardSetNightmares->setChangeWorldMaterials();
				mRenderComponentBillboardSetDreams->setVisible(false);
			}
			else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setVisible(true);
				mRenderComponentBillboardSetNightmares->setChangeWorldMaterials();
			}
			else if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(true);
				mRenderComponentBillboardSetDreams->setChangeWorldMaterials();
			}
			break;
		default:break;
	}
}

void GameObjectBillboardSet::changeWorldStarted(int newWorld)
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

void GameObjectBillboardSet::changeToWorld(int newWorld, double perc)
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

void GameObjectBillboardSet::reset()
{
	GameObject::reset();
}

bool GameObjectBillboardSet::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBillboardSet::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectBillboardSet::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectBillboardSet::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectBillboardSet::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectBillboardSet::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectBillboardSet::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectBillboardSet::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectBillboardSetParameters::TGameObjectBillboardSetParameters() : TGameObjectParameters()
{

}

TGameObjectBillboardSetParameters::~TGameObjectBillboardSetParameters()
{

}

