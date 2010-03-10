#include "GameObjectTerrainConvex.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainConvex::GameObjectTerrainConvex(const std::string& name)
:GameObject(name)
{

}

GameObjectTerrainConvex::~GameObjectTerrainConvex()
{

}

void GameObjectTerrainConvex::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntityDreams)
{
	mRenderComponentEntityDreams=pRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectTerrainConvex::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

void GameObjectTerrainConvex::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntityNightmares)
{
	mRenderComponentEntityNightmares=pRenderComponentEntityNightmares;
}

RenderComponentEntityPtr GameObjectTerrainConvex::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectTerrainConvex::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectTerrainConvex::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTerrainConvex::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectTerrainConvex::getPhysicsComponentComplexConvex()
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectTerrainConvex::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		mPhysicsComponentComplexConvex->create();
		break;
	case NIGHTMARES:
		break;
	default:break;
	}
}
//-------------------------------------------------------------------------------------------

void GameObjectTerrainConvex::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectTerrainConvex::registerHandlers()
{
	GameObjectTerrainConvexPtr _this =shared_from_this();

	registerEventHandler<GameObjectTerrainConvex,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrainConvex::processChangeWorld,
		mGameWorldManager->getEventManager());
}
void GameObjectTerrainConvex::unregisterHandlers()
{
	GameObjectTerrainConvexPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectTerrainConvex,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrainConvex::processChangeWorld,
		mGameWorldManager->getEventManager());
}

//-------------------------------------------------------------------------------------------
TGameObjectTerrainConvexParameters::TGameObjectTerrainConvexParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainConvexParameters::~TGameObjectTerrainConvexParameters()
{

}
