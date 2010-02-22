#include "GameObjectItem1UP.h"

using namespace OUAN;

GameObjectItem1UP::GameObjectItem1UP(const std::string& name, const std::string& id)
:GameObject(GAME_OBJECT_NAME_ITEM_1UP,id)
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

void GameObjectItem1UP::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
}

RenderComponentPositionalPtr GameObjectItem1UP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectItem1UP::setPhysicsComponentComplexNonMovable(PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable)
{
	mPhysicsComponentComplexNonMovable=pPhysicsComponentComplexNonMovable;
}

PhysicsComponentComplexNonMovablePtr GameObjectItem1UP::getPhysicsComponentComplexNonMovable()
{
	return mPhysicsComponentComplexNonMovable;
}


TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{
}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{
}