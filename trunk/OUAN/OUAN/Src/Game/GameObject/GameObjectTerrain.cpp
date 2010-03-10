#include "GameObjectTerrain.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrain::GameObjectTerrain(const std::string& name)
:GameObject(name)
{

}

GameObjectTerrain::~GameObjectTerrain()
{

}

RenderComponentEntityPtr GameObjectTerrain::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTerrain::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectTerrain::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectTerrain::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTerrain::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTerrain::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}
/*
void GameObjectTerrain::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectTerrain::getPhysicsComponentComplexConvex()
{
	return mPhysicsComponentComplexConvex;
}
*/
void GameObjectTerrain::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		mPhysicsComponentComplexTriangle->create();
		break;
	case NIGHTMARES:
		break;
	default:break;
	}
}
//-------------------------------------------------------------------------------------------

void GameObjectTerrain::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectTerrain::registerHandlers()
{
	GameObjectTerrainPtr _this =shared_from_this();

	registerEventHandler<GameObjectTerrain,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrain::processChangeWorld,
		mGameWorldManager->getEventManager());
}
void GameObjectTerrain::unregisterHandlers()
{
	GameObjectTerrainPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectTerrain,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrain::processChangeWorld,
		mGameWorldManager->getEventManager());
}

//-------------------------------------------------------------------------------------------
TGameObjectTerrainParameters::TGameObjectTerrainParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainParameters::~TGameObjectTerrainParameters()
{

}
