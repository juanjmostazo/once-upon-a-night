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

void GameObjectTotem::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectTotem::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTotem::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTotem::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
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

void GameObjectTotem::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTotem::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
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

void GameObjectTotem::setDreamsRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
}

void GameObjectTotem::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();
}

void GameObjectTotem::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

bool GameObjectTotem::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTotem::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
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