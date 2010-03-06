#include "GameObjectPortal.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectPortal::GameObjectPortal(const std::string& name)
:GameObject(name)
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
void GameObjectPortal::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}

}
//-------------------------------------------------------------------------------------------
void GameObjectPortal::registerHandlers()
{
	GameObjectPortalPtr _this =shared_from_this();
}
void GameObjectPortal::unregisterHandlers()
{
	GameObjectPortalPtr _this =shared_from_this();
}
//-------------------------------------------------------------------------------------------

TGameObjectPortalParameters::TGameObjectPortalParameters() : TGameObjectParameters()
{

}

TGameObjectPortalParameters::~TGameObjectPortalParameters()
{

}