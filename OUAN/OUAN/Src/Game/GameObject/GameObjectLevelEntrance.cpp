#include "OUAN_Precompiled.h"

#include "GameObjectLevelEntrance.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectLevelEntrance::GameObjectLevelEntrance(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_LEVEL_ENTRANCE)
{

}

GameObjectLevelEntrance::~GameObjectLevelEntrance()
{

}

void GameObjectLevelEntrance::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectLevelEntrance::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectLevelEntrance::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectLevelEntrance::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectLevelEntrance::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectLevelEntrance::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectLevelEntrance::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectLevelEntrance::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectLevelEntrance::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectLevelEntrance::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectLevelEntrance::changeWorldFinished(int newWorld)
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

void GameObjectLevelEntrance::changeWorldStarted(int newWorld)
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

void GameObjectLevelEntrance::changeToWorld(int newWorld, double perc)
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

void GameObjectLevelEntrance::reset()
{
	GameObject::reset();
}

bool GameObjectLevelEntrance::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectLevelEntrance::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectLevelEntrance::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectLevelEntrance::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectLevelEntrance::setDreamsRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
}

void GameObjectLevelEntrance::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();
}

void GameObjectLevelEntrance::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntityDreams->setChangeWorldFactor(factor);
	}

	if(mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntityNightmares->setChangeWorldFactor(factor);
	}
}

void GameObjectLevelEntrance::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

bool GameObjectLevelEntrance::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectLevelEntrance::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
bool GameObjectLevelEntrance::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectLevelEntrance::getLogicComponentInstance() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectLevelEntranceParameters::TGameObjectLevelEntranceParameters() : TGameObjectParameters()
{

}

TGameObjectLevelEntranceParameters::~TGameObjectLevelEntranceParameters()
{

}