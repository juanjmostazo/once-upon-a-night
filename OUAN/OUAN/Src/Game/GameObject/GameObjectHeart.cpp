#include "GameObjectHeart.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectHeart::GameObjectHeart(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_HEART)
{

}

GameObjectHeart::~GameObjectHeart()
{

}

RenderComponentEntityPtr GameObjectHeart::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectHeart::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectHeart::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectHeart::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

TGameObjectHeartParameters::TGameObjectHeartParameters() : TGameObjectParameters()
{

}

TGameObjectHeartParameters::~TGameObjectHeartParameters()
{

}