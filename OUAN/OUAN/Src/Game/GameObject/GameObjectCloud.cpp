#include "GameObjectCloud.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectCloud::GameObjectCloud(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CLOUD)
{

}

GameObjectCloud::~GameObjectCloud()
{

}

void GameObjectCloud::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectCloud::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectCloud::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectCloud::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectCloud::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectCloud::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectCloud::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectCloud::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectCloud::changeWorld(int world)
{
	switch(world)
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

void GameObjectCloud::reset()
{
	GameObject::reset();
}

bool GameObjectCloud::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectCloud::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectCloud::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectCloud::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectCloud::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

bool GameObjectCloud::hasRenderComponentEntity() const
{
	return true;
}

RenderComponentEntityPtr GameObjectCloud::getEntityComponent() const
{
	return (mGameWorldManager->getCurrentWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectCloudParameters::TGameObjectCloudParameters() : TGameObjectParameters()
{

}

TGameObjectCloudParameters::~TGameObjectCloudParameters()
{

}