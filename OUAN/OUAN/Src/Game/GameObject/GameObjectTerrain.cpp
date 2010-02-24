#include "GameObjectTerrain.h"

using namespace OUAN;

GameObjectTerrain::GameObjectTerrain(const std::string& name, const std::string& id)
:GameObject(name,id)
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


TGameObjectTerrainParameters::TGameObjectTerrainParameters() : TGameObjectParameters()
{
}

TGameObjectTerrainParameters::~TGameObjectTerrainParameters()
{
}