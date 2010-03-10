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
TGameObjectTerrainTriangleParameters::TGameObjectTerrainTriangleParameters() : TGameObjectParameters()
{

}

TGameObjectTerrainTriangleParameters::~TGameObjectTerrainTriangleParameters()
{

}
