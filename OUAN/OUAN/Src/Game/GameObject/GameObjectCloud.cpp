#include "OUAN_Precompiled.h"

#include "GameObjectCloud.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectCloud::GameObjectCloud(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CLOUD)
{
	mRenderComponentFractalVolumeSetDreams.clear();
	mRenderComponentFractalVolumeSetDreams.resize(CLOUD_FRACTAL_VOLUME_SET_SIZE);

	mRenderComponentFractalVolumeSetNightmares.clear();
	mRenderComponentFractalVolumeSetNightmares.resize(CLOUD_FRACTAL_VOLUME_SET_SIZE);
}

GameObjectCloud::~GameObjectCloud()
{

}

void GameObjectCloud::setRenderComponentFractalVolumeDreams(RenderComponentFractalVolumePtr pRenderComponentFractalVolume, int pUnit)
{
	mRenderComponentFractalVolumeSetDreams[pUnit]=pRenderComponentFractalVolume;
}

void GameObjectCloud::setRenderComponentFractalVolumeNightmares(RenderComponentFractalVolumePtr pRenderComponentFractalVolume, int pUnit)
{
	mRenderComponentFractalVolumeSetNightmares[pUnit]=pRenderComponentFractalVolume;
}

std::vector<RenderComponentFractalVolumePtr> GameObjectCloud::getRenderComponentFractalVolumeSetDreams()
{
	return mRenderComponentFractalVolumeSetDreams;
}

std::vector<RenderComponentFractalVolumePtr> GameObjectCloud::getRenderComponentFractalVolumeSetNightmares()
{
	return mRenderComponentFractalVolumeSetNightmares;
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

void GameObjectCloud::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetDreams[i]->setVisible(true);
		}
	}
	if(mLogicComponent->existsInNightmares())
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetNightmares[i]->setVisible(false);
		}
	}
}

void GameObjectCloud::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetDreams[i]->setVisible(false);
		}
	}
	if(mLogicComponent->existsInNightmares())
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetNightmares[i]->setVisible(true);
		}
	}
}

void GameObjectCloud::setChangeWorldRender()
{
	if (!isEnabled()) return;
}

void GameObjectCloud::changeWorldFinished(int newWorld)
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
		default:
			break;
	}
}

void GameObjectCloud::changeWorldStarted(int newWorld)
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

void GameObjectCloud::changeToWorld(int newWorld, double perc)
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

	if (getGameWorldManager()->getWorld() == DREAMS)
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetDreams[i]->update(elapsedSeconds);
		}
	} 
	else if (getGameWorldManager()->getWorld() == NIGHTMARES)
	{
		for (int i=0; i<CLOUD_FRACTAL_VOLUME_SET_SIZE; i++)
		{
			mRenderComponentFractalVolumeSetNightmares[i]->update(elapsedSeconds);
		}
	}
}

//-------------------------------------------------------------------------------------------

TGameObjectCloudParameters::TGameObjectCloudParameters() : TGameObjectParameters()
{

}

TGameObjectCloudParameters::~TGameObjectCloudParameters()
{

}