#include "GameObjectBillboardSet.h"
#include "../GameWorldManager.h"

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

void GameObjectBillboardSet::changeWorld(int world)
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
void GameObjectBillboardSet::registerHandlers()
{
	GameObjectBillboardSetPtr _this =shared_from_this();
	//registerEventHandler<GameObjectBillboardSet,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectBillboardSet::processChangeWorld,
	//	mGameWorldManager->getEventManager());

}
void GameObjectBillboardSet::unregisterHandlers()
{
	GameObjectBillboardSetPtr _this =shared_from_this();
	//unregisterEventHandler<GameObjectOny,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectOny::processChangeWorld,
	//	mGameWorldManager->getEventManager());

}
//-------------------------------------------------------------------------------------------

TGameObjectBillboardSetParameters::TGameObjectBillboardSetParameters() : TGameObjectParameters()
{

}

TGameObjectBillboardSetParameters::~TGameObjectBillboardSetParameters()
{

}

