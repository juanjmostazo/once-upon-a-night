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
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(true);
				mRenderComponentBillboardSetNightmares->setVisible(false);
				mRenderComponentBillboardSetDreams->setOriginalMaterials();
				mRenderComponentBillboardSetNightmares->setOriginalMaterials();
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(true);
				mRenderComponentBillboardSetDreams->setOriginalMaterials();
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setVisible(false);
				mRenderComponentBillboardSetNightmares->setOriginalMaterials();
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(false);
				mRenderComponentBillboardSetNightmares->setVisible(true);
				mRenderComponentBillboardSetDreams->setOriginalMaterials();
				mRenderComponentBillboardSetNightmares->setOriginalMaterials();
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setVisible(false);
				mRenderComponentBillboardSetDreams->setOriginalMaterials();
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setVisible(true);
				mRenderComponentBillboardSetNightmares->setOriginalMaterials();
			}	
			break;
		default:break;
	}
}

void GameObjectBillboardSet::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentBillboardSetDreams->setChangeWorldMaterials();
		mRenderComponentBillboardSetDreams->randomizeChangeWorldMaterials();
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentBillboardSetNightmares->setChangeWorldMaterials();
		mRenderComponentBillboardSetNightmares->randomizeChangeWorldMaterials();
	}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSetDreams->setVisible(true);
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentBillboardSetNightmares->setVisible(true);
		}	
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
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setChangeWorldFactor(perc);
				mRenderComponentBillboardSetDreams->setChangeWorldFactor(1-perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setChangeWorldFactor(1-perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setChangeWorldFactor(perc);
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setChangeWorldFactor(1-perc);
				mRenderComponentBillboardSetDreams->setChangeWorldFactor(perc);
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetDreams->setChangeWorldFactor(perc);
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentBillboardSetNightmares->setChangeWorldFactor(1-perc);
			}		
			break;
		default:
			break;
	}
}

void GameObjectBillboardSet::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectBillboardSet::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
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

