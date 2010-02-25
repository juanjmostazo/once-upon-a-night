#include "GameObjectItemMaxHP.h"

using namespace OUAN;

GameObjectItemMaxHP::GameObjectItemMaxHP(const std::string& name)
:GameObject(name)
{

}

GameObjectItemMaxHP::~GameObjectItemMaxHP()
{

}

RenderComponentEntityPtr GameObjectItemMaxHP::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectItemMaxHP::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectItemMaxHP::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectItemMaxHP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectItemMaxHP::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectItemMaxHP::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}


TGameObjectItemMaxHPParameters::TGameObjectItemMaxHPParameters() : TGameObjectParameters()
{
}

TGameObjectItemMaxHPParameters::~TGameObjectItemMaxHPParameters()
{
}