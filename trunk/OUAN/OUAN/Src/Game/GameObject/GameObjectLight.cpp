#include "OUAN_Precompiled.h"

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

void GameObjectLight::changeWorldFinished(int newWorld)
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

void GameObjectLight::changeWorldStarted(int newWorld)
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

void GameObjectLight::changeToWorld(int newWorld, double perc)
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

void GameObjectLight::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
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

bool GameObjectLight::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectLight::getLogicComponent() const
{
	return mLogicComponent;
}
TGameObjectLightParameters::TGameObjectLightParameters() : TGameObjectParameters()
{

}

TGameObjectLightParameters::~TGameObjectLightParameters()
{

}