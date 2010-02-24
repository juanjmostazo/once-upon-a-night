#include "GameObjectPortal.h"

using namespace OUAN;

GameObjectPortal::GameObjectPortal(const std::string& name, const std::string& id)
:GameObject(name,id)
{

}

GameObjectPortal::~GameObjectPortal()
{

}

RenderComponentEntityPtr GameObjectPortal::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectPortal::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectPortal::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectPortal::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectPortal::setPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mPhysicsComponentComplexTriangle=pPhysicsComponentComplexTriangle;
}

PhysicsComponentComplexTrianglePtr GameObjectPortal::getPhysicsComponentComplexTriangle()
{
	return mPhysicsComponentComplexTriangle;
}


TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{
}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{
}