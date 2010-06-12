#include "OUAN_Precompiled.h"

#include "GameObjectTerrainTriangle.h"
#include "../GameWorldManager.h"
#include "GameObjectOny.h"
#include "../../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainTriangle::GameObjectTerrainTriangle(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TERRAINTRIANGLE)
{

}

GameObjectTerrainTriangle::~GameObjectTerrainTriangle()
{

}

void GameObjectTerrainTriangle::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainTriangle::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainTriangle::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainTriangle::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTerrainTriangle::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTerrainTriangle::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTerrainTriangle::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
	mPhysicsComponentComplexTriangle->create();
}

PhysicsComponentComplexTrianglePtr GameObjectTerrainTriangle::getPhysicsComponentComplexTriangle() const
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTerrainTriangle::changeWorldFinished(int newWorld)
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

	//Logger::getInstance()->log("changeWorldFinished"+getName()+" ");
}

void GameObjectTerrainTriangle::changeWorldStarted(int newWorld)
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

	//Logger::getInstance()->log("changeWorldStarted"+getName()+" ");
}

void GameObjectTerrainTriangle::changeToWorld(int newWorld, double perc)
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

void GameObjectTerrainTriangle::setDreamsRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(true);
	mRenderComponentEntityDreams->setDreamsMaterials();
	mRenderComponentEntityNightmares->setVisible(false);
}

void GameObjectTerrainTriangle::setNightmaresRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setVisible(false);
	mRenderComponentEntityNightmares->setVisible(true);
	mRenderComponentEntityNightmares->setNightmaresMaterials();
}

void GameObjectTerrainTriangle::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntityDreams->setChangeWorldMaterials();
	mRenderComponentEntityNightmares->setChangeWorldMaterials();
}

void GameObjectTerrainTriangle::reset()
{
	GameObject::reset();
}

bool GameObjectTerrainTriangle::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTerrainTriangle::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTerrainTriangle::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTerrainTriangle::getPhysicsComponent() const
{
	return getPhysicsComponentComplexTriangle();
}


/// Set logic component
void GameObjectTerrainTriangle::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTerrainTriangle::getLogicComponent()
{
	return mLogicComponent;
}


void GameObjectTerrainTriangle::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTerrainTriangle::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTerrainTriangle::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTerrainTriangle::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectTerrainTriangle::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectTerrainTriangle::getEntityComponent() const
{
	return (mWorld==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}

void GameObjectTerrainTriangle::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	mRenderComponentEntityDreams->update(elapsedSeconds);
	mRenderComponentEntityNightmares->update(elapsedSeconds);

	//mRenderComponentEntityDreams->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
	//mRenderComponentEntityNightmares->setChangeWorldMaterialsPointOfInterest(mGameWorldManager->getGameObjectOny()->getPositionalComponent()->getPosition());
}

TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{
}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
