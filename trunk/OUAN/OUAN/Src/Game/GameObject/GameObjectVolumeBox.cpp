#include "GameObjectVolumeBox.h"

using namespace OUAN;

GameObjectVolumeBox::GameObjectVolumeBox(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeBox::~GameObjectVolumeBox()
{

}

void GameObjectVolumeBox::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeBox::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeBox::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeBox::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectVolumeBox::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

TGameObjectVolumeBoxParameters::TGameObjectVolumeBoxParameters() : TGameObjectParameters()
{
}

TGameObjectVolumeBoxParameters::~TGameObjectVolumeBoxParameters()
{
}