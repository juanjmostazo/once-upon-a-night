#include "GameObjectViewport.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectViewport::GameObjectViewport(const std::string& name)
:GameObject(name)
{

}

GameObjectViewport::~GameObjectViewport()
{

}

void GameObjectViewport::setRenderComponentViewport(RenderComponentViewportPtr pRenderComponentViewport)
{
	mRenderComponentViewport=pRenderComponentViewport;
}

RenderComponentViewportPtr GameObjectViewport::getRenderComponentViewport() const
{
	return mRenderComponentViewport;
}

void GameObjectViewport::changeWorld(int world)
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

void GameObjectViewport::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectViewport::registerHandlers()
{
	GameObjectViewportPtr _this =shared_from_this();

	registerEventHandler<GameObjectViewport,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectViewport::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectViewport::unregisterHandlers()
{
	GameObjectViewportPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectViewport,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectViewport::processChangeWorld,
		mGameWorldManager->getEventManager());
}
//-------------------------------------------------------------------------------------------

TGameObjectViewportParameters::TGameObjectViewportParameters() : TGameObjectParameters()
{

}

TGameObjectViewportParameters::~TGameObjectViewportParameters()
{

}