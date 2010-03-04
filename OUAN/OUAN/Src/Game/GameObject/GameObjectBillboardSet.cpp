#include "GameObjectBillboardSet.h"

using namespace OUAN;

GameObjectBillboardSet::GameObjectBillboardSet(const std::string& name)
:GameObject(name)
{

}

GameObjectBillboardSet::~GameObjectBillboardSet()
{

}

RenderComponentBillboardSetPtr GameObjectBillboardSet::getRenderComponentBillboardSet() const
{
	return mRenderComponentBillboardSet;
}

void GameObjectBillboardSet::setRenderComponentBillboardSet(RenderComponentBillboardSetPtr pRenderComponentBillboardSet)
{
	mRenderComponentBillboardSet=pRenderComponentBillboardSet;
}
void GameObjectBillboardSet::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectBillboardSet::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

TGameObjectBillboardSetParameters::TGameObjectBillboardSetParameters() : TGameObjectParameters()
{

}

TGameObjectBillboardSetParameters::~TGameObjectBillboardSetParameters()
{

}