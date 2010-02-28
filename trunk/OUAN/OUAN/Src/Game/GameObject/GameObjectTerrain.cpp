#include "GameObjectTerrain.h"

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
/*
void GameObjectTerrain::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectTerrain::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}
*/
void GameObjectTerrain::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectTerrain::getPhysicsComponentComplexConvex()
{
	return mPhysicsComponentComplexConvex;
}

TGameObjectTerrainParameters::TGameObjectTerrainParameters() : TGameObjectParameters()
{
}

TGameObjectTerrainParameters::~TGameObjectTerrainParameters()
{
}