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

RenderComponentBillboardSetPtr GameObjectBillboardSet::getRenderComponentBillboardSet() const
{
	return mRenderComponentBillboardSet;
}

void GameObjectBillboardSet::setRenderComponentBillboardSet(RenderComponentBillboardSetPtr pRenderComponentBillboardSet)
{
	mRenderComponentBillboardSet=pRenderComponentBillboardSet;
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

	//mRenderComponentBillboardSet->setOriginalMaterials();

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(true);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(true);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(false);
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(true);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(false);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSet->getBillboardSet()->setVisible(true);
		}	
		break;
	default:break;
	}
}

void GameObjectBillboardSet::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	//mRenderComponentBillboardSet->setChangeWorldMaterials();

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

	//mRenderComponentBillboardSet->setChangeWorldFactor(perc);

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

