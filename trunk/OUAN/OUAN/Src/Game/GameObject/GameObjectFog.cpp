#include "OUAN_Precompiled.h"

#include "GameObjectFog.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectFog::GameObjectFog(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_FOG)
{

}

GameObjectFog::~GameObjectFog()
{

}

void GameObjectFog::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectFog::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectFog::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectFog::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectFog::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectFog::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectFog::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectFog::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectFog::changeWorldFinished(int newWorld)
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
		default:
			break;
	}
}

void GameObjectFog::changeWorldStarted(int newWorld)
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

void GameObjectFog::changeToWorld(int newWorld, double perc)
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

void GameObjectFog::reset()
{
	GameObject::reset();
}

bool GameObjectFog::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectFog::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectFog::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectFog::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectFog::setDreamsRender()
{
	if (!isEnabled()) return;
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

void GameObjectFog::setNightmaresRender()
{
	if (!isEnabled()) return;
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

void GameObjectFog::setChangeWorldRender()
{
	if (!isEnabled()) return;
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

bool GameObjectFog::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectFog::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectFogParameters::TGameObjectFogParameters() : TGameObjectParameters()
{

}

TGameObjectFogParameters::~TGameObjectFogParameters()
{

}