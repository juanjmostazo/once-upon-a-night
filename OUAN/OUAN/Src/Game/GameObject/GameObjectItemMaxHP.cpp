#include "GameObjectItemMaxHP.h"

using namespace OUAN;

GameObjectItemMaxHP::GameObjectItemMaxHP(const std::string& name, const std::string& id)
:GameObject(name,id)
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

void GameObjectItemMaxHP::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
}

RenderComponentPositionalPtr GameObjectItemMaxHP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectItemMaxHP::setPhysicsComponentComplexNonMovable(PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable)
{
	mPhysicsComponentComplexNonMovable=pPhysicsComponentComplexNonMovable;
}

PhysicsComponentComplexNonMovablePtr GameObjectItemMaxHP::getPhysicsComponentComplexNonMovable()
{
	return mPhysicsComponentComplexNonMovable;
}


TGameObjectItemMaxHPParameters::TGameObjectItemMaxHPParameters() : TGameObjectParameters()
{
}

TGameObjectItemMaxHPParameters::~TGameObjectItemMaxHPParameters()
{
}