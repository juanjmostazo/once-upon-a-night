#include "OUAN_Precompiled.h"

#include "GameObjectPlane.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPlane::GameObjectPlane(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PLANE)
{

}

GameObjectPlane::~GameObjectPlane()
{

}

RenderComponentPlanePtr GameObjectPlane::getRenderComponentPlane() const
{
	return mRenderComponentPlane;
}

void GameObjectPlane::setRenderComponentPlane(RenderComponentPlanePtr pRenderComponentPlane)
{
	mRenderComponentPlane=pRenderComponentPlane;
}

void GameObjectPlane::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectPlane::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectPlane::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectPlane::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectPlane::changeWorldFinished(int newWorld)
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

void GameObjectPlane::changeWorldStarted(int newWorld)
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

void GameObjectPlane::changeToWorld(int newWorld, double perc)
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

void GameObjectPlane::reset()
{
	GameObject::reset();
}

bool GameObjectPlane::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectPlane::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectPlane::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectPlane::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectPlane::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectPlane::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectPlane::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectPlane::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}

TGameObjectPlaneParameters::TGameObjectPlaneParameters() : TGameObjectParameters()
{

}

TGameObjectPlaneParameters::~TGameObjectPlaneParameters()
{

}

