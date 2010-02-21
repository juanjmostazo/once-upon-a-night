#include "GameObjectNonMovableTerrain.h"

using namespace OUAN;

GameObjectNonMovableTerrain::GameObjectNonMovableTerrain(const std::string& name, const std::string& id)
:GameObjectNonMovableEntity(name,id)
{

}

GameObjectNonMovableTerrain::~GameObjectNonMovableTerrain()
{

}

RenderComponentEntityPtr GameObjectNonMovableTerrain::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectNonMovableTerrain::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

PhysicsComponentTerrainPtr GameObjectNonMovableTerrain::getPhysicsComponentTerrain() const
{
	return mPhysicsComponentTerrain;
}

void GameObjectNonMovableTerrain::setPhysicsComponentTerrain(PhysicsComponentTerrainPtr pPhysicsComponentTerrain)
{
	mPhysicsComponentTerrain=pPhysicsComponentTerrain;
}

TGameObjectNonMovableTerrainParameters::TGameObjectNonMovableTerrainParameters() : TGameObjectNonMovableEntityParameters()
{
}

TGameObjectNonMovableTerrainParameters::~TGameObjectNonMovableTerrainParameters()
{
}