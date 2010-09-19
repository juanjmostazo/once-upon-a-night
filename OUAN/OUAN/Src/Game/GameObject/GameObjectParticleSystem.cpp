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
			Logger::getInstance()->log("Starting static GameObjectParticleSystem dreams: " + getName());
			mRenderComponentParticleSystem->start();
		}
		else
		{
			mRenderComponentParticleSystem->stop();
		}		
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			Logger::getInstance()->log("Starting static GameObjectParticleSystem nightmares: " + getName());
			mRenderComponentParticleSystem->start();
		}
		else
		{
			mRenderComponentParticleSystem->stop();
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


void GameObjectParticleSystem::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
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

void GameObjectParticleSystem::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentParticleSystem->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentParticleSystem->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
bool GameObjectParticleSystem::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectParticleSystem::getLogicComponent() const
{
	return mLogicComponent;
}
TGameObjectParticleSystemParameters::TGameObjectParticleSystemParameters() : TGameObjectParameters()
{

}

TGameObjectParticleSystemParameters::~TGameObjectParticleSystemParameters()
{

}