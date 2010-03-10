#include "GameObjectTerrainTriangle.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTerrainTriangle::GameObjectTerrainTriangle(const std::string& name)
:GameObject(name)
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

RenderComponentPositionalPtr GameObjectTerrainTriangle::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTerrainTriangle::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTerrainTriangle::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}

void GameObjectTerrainTriangle::changeWorld(int world)
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

void GameObjectTerrainTriangle::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectTerrainTriangle::registerHandlers()
{
	GameObjectTerrainTrianglePtr _this =shared_from_this();

	registerEventHandler<GameObjectTerrainTriangle,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrainTriangle::processChangeWorld,
		mGameWorldManager->getEventManager());
}
void GameObjectTerrainTriangle::unregisterHandlers()
{
	GameObjectTerrainTrianglePtr _this =shared_from_this();

	unregisterEventHandler<GameObjectTerrainTriangle,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectTerrainTriangle::processChangeWorld,
		mGameWorldManager->getEventManager());
}

//-------------------------------------------------------------------------------------------
TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
