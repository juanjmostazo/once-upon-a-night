#include "GameObjectVolumeCapsule.h"

using namespace OUAN;

GameObjectVolumeCapsule::GameObjectVolumeCapsule(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeCapsule::~GameObjectVolumeCapsule()
{

}

void GameObjectVolumeCapsule::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeCapsule::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeCapsule::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeCapsule::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeCapsule::setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule)
{
	mPhysicsComponentVolumeCapsule=pPhysicsComponentVolumeCapsule;
}

PhysicsComponentVolumeCapsulePtr GameObjectVolumeCapsule::getPhysicsComponentVolumeCapsule()
{
	return mPhysicsComponentVolumeCapsule;
}

TGameObjectVolumeCapsuleParameters::TGameObjectVolumeCapsuleParameters() : TGameObjectParameters()
{
}

TGameObjectVolumeCapsuleParameters::~TGameObjectVolumeCapsuleParameters()
{
}