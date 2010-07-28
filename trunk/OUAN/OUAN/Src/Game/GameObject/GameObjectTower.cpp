#include "OUAN_Precompiled.h"

#include "GameObjectTower.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectTower::GameObjectTower(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TOWER)
{

}

GameObjectTower::~GameObjectTower()
{

}

void GameObjectTower::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTower::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTower::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTower::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTower::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTower::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTower::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTower::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTower::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTower::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTower::changeWorldFinished(int newWorld)
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

void GameObjectTower::changeWorldStarted(int newWorld)
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

void GameObjectTower::changeToWorld(int newWorld, double perc)
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

void GameObjectTower::reset()
{
	GameObject::reset();
}

bool GameObjectTower::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTower::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectTower::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTower::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTower::setDreamsRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
}

void GameObjectTower::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();
}

void GameObjectTower::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

bool GameObjectTower::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTower::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
bool GameObjectTower::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTower::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectTowerParameters::TGameObjectTowerParameters() : TGameObjectParameters()
{

}

TGameObjectTowerParameters::~TGameObjectTowerParameters()
{

}