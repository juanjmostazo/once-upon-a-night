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

void GameObjectPortal::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
}

RenderComponentPositionalPtr GameObjectPortal::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectPortal::setPhysicsComponentComplexNonMovable(PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable)
{
	mPhysicsComponentComplexNonMovable=pPhysicsComponentComplexNonMovable;
}

PhysicsComponentComplexNonMovablePtr GameObjectPortal::getPhysicsComponentComplexNonMovable()
{
	return mPhysicsComponentComplexNonMovable;
}


TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{
}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{
}