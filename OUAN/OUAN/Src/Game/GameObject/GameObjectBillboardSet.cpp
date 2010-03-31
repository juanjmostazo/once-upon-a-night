#include "GameObjectBillboardSet.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectBillboardSet::GameObjectBillboardSet(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BILLBOARDSET)
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

void GameObjectBillboardSet::changeWorld(int world)
{
	if (!isEnabled()) return;
	
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
bool GameObjectBillboardSet::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectBillboardSet::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectBillboardSetParameters::TGameObjectBillboardSetParameters() : TGameObjectParameters()
{

}

TGameObjectBillboardSetParameters::~TGameObjectBillboardSetParameters()
{

}

