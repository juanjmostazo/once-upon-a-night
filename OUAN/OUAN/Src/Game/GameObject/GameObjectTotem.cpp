#include "OUAN_Precompiled.h"

#include "GameObjectTotem.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectTotem::GameObjectTotem(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TOTEM)
{

}

GameObjectTotem::~GameObjectTotem()
{

}

void GameObjectTotem::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTotem::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTotem::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTotem::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTotem::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTotem::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTotem::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectTotem::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectTotem::changeWorldFinished(int newWorld)
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
		default:break;
	}
}

void GameObjectTotem::changeWorldStarted(int newWorld)
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

void GameObjectTotem::changeToWorld(int newWorld, double perc)
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

void GameObjectTotem::reset()
{
	GameObject::reset();
}

bool GameObjectTotem::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTotem::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectTotem::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTotem::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectTotem::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setChangeWorldFactor(factor);

}

bool GameObjectTotem::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTotem::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectTotem::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTotem::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectTotemParameters::TGameObjectTotemParameters() : TGameObjectParameters()
{

}

TGameObjectTotemParameters::~TGameObjectTotemParameters()
{

}