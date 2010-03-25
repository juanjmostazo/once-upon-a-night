#include "GameObjectDiamond.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDiamond::GameObjectDiamond(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMOND)
{

}

GameObjectDiamond::~GameObjectDiamond()
{

}

RenderComponentEntityPtr GameObjectDiamond::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectDiamond::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectDiamond::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectDiamond::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectDiamond::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectDiamond::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

TGameObjectDiamondParameters::TGameObjectDiamondParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondParameters::~TGameObjectDiamondParameters()
{

}