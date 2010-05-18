#include "GameObjectLight.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectLight::GameObjectLight(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_LIGHT)
{

}

GameObjectLight::~GameObjectLight()
{

}

RenderComponentLightPtr GameObjectLight::getRenderComponentLight() const
{
	return mRenderComponentLight;
}

void GameObjectLight::setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight)
{
	mRenderComponentLight=pRenderComponentLight;
}

void GameObjectLight::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectLight::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectLight::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectLight::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectLight::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectLight::changeWorldStarted(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectLight::changeToWorld(int world, double perc)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectLight::reset()
{
	GameObject::reset();
}

bool GameObjectLight::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectLight::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectLight::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectLight::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectLight::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectLight::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectLight::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectLight::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectLightParameters::TGameObjectLightParameters() : TGameObjectParameters()
{

}

TGameObjectLightParameters::~TGameObjectLightParameters()
{

}