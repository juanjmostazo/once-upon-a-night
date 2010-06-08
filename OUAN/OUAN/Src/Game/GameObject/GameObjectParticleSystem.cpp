#include "OUAN_Precompiled.h"

#include "GameObjectParticleSystem.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectParticleSystem::GameObjectParticleSystem(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PARTICLESYSTEM)
{

}

GameObjectParticleSystem::~GameObjectParticleSystem()
{

}

RenderComponentParticleSystemPtr GameObjectParticleSystem::getRenderComponentParticleSystem() const
{
	return mRenderComponentParticleSystem;
}

void GameObjectParticleSystem::setRenderComponentParticleSystem(RenderComponentParticleSystemPtr pRenderComponentParticleSystem)
{
	mRenderComponentParticleSystem=pRenderComponentParticleSystem;
}

void GameObjectParticleSystem::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectParticleSystem::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectParticleSystem::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectParticleSystem::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectParticleSystem::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentParticleSystem->setVisible(true);
			mRenderComponentParticleSystem->start();
		}
		else
		{
			mRenderComponentParticleSystem->setVisible(false);

		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentParticleSystem->setVisible(true);
			mRenderComponentParticleSystem->start();
		}
		else
		{
			mRenderComponentParticleSystem->setVisible(false);
		}
		break;
	default:
		break;
	}
}

void GameObjectParticleSystem::changeWorldStarted(int newWorld)
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

void GameObjectParticleSystem::changeToWorld(int newWorld, double perc)
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

void GameObjectParticleSystem::reset()
{
	GameObject::reset();
}

bool GameObjectParticleSystem::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectParticleSystem::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectParticleSystem::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectParticleSystem::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectParticleSystem::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectParticleSystem::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectParticleSystem::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectParticleSystem::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectParticleSystemParameters::TGameObjectParticleSystemParameters() : TGameObjectParameters()
{

}

TGameObjectParticleSystemParameters::~TGameObjectParticleSystemParameters()
{

}