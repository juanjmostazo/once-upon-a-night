#include "GameObjectTerrain.h"

using namespace OUAN;

GameObjectTerrain::GameObjectTerrain(const std::string& name, const std::string& id)
:GameObject(LOADER_TERRAIN_ID,id)
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

TGameObjectTerrainParameters::TGameObjectTerrainParameters() : TGameObjectParameters()
{
}

TGameObjectTerrainParameters::~TGameObjectTerrainParameters()
{
}