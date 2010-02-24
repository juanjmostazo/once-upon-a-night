#include "GameObjectItem1UP.h"

using namespace OUAN;

GameObjectItem1UP::GameObjectItem1UP(const std::string& name, const std::string& id)
:GameObject(name,id)
{

}

GameObjectItem1UP::~GameObjectItem1UP()
{

}

RenderComponentEntityPtr GameObjectItem1UP::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectItem1UP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectItem1UP::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectItem1UP::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}


TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{
}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{
}