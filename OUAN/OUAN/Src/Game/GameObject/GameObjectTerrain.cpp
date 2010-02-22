#include "GameObjectTerrain.h"

using namespace OUAN;

GameObjectTerrain::GameObjectTerrain(const std::string& name, const std::string& id)
:GameObject(GAME_OBJECT_NAME_TERRAIN,id)
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

void GameObjectTerrain::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
}

RenderComponentPositionalPtr GameObjectTerrain::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectTerrain::setPhysicsComponentComplexNonMovable(PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable)
{
	mPhysicsComponentComplexNonMovable=pPhysicsComponentComplexNonMovable;
}

PhysicsComponentComplexNonMovablePtr GameObjectTerrain::getPhysicsComponentComplexNonMovable()
{
	return mPhysicsComponentComplexNonMovable;
}


TGameObjectTerrainParameters::TGameObjectTerrainParameters() : TGameObjectParameters()
{
}

TGameObjectTerrainParameters::~TGameObjectTerrainParameters()
{
}