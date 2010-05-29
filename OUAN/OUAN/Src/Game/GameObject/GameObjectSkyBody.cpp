#include "GameObjectSkyBody.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectSkyBody::GameObjectSkyBody(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SKYBODY)
{

}

GameObjectSkyBody::~GameObjectSkyBody()
{

}

void GameObjectSkyBody::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectSkyBody::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectSkyBody::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectSkyBody::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectSkyBody::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectSkyBody::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectSkyBody::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectSkyBody::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectSkyBody::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
			mRenderComponentEntityNightmares->setVisible(false);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(true);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(false);
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
			mRenderComponentEntityNightmares->setVisible(true);
		}
		else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityDreams->setVisible(false);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntityNightmares->setVisible(true);
		}	
		break;
	default:break;
	}
}

void GameObjectSkyBody::changeWorldStarted(int newWorld)
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

void GameObjectSkyBody::changeToWorld(int newWorld, double perc)
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

void GameObjectSkyBody::reset()
{
	GameObject::reset();
}

bool GameObjectSkyBody::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectSkyBody::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectSkyBody::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectSkyBody::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectSkyBody::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectSkyBody::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectSkyBody::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectSkyBody::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

bool GameObjectSkyBody::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectSkyBody::getEntityComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectSkyBodyParameters::TGameObjectSkyBodyParameters() : TGameObjectParameters()
{

}

TGameObjectSkyBodyParameters::~TGameObjectSkyBodyParameters()
{

}