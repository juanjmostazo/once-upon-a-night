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
void GameObjectViewport::registerHandlers()
{
	GameObjectViewportPtr _this =shared_from_this();
}
void GameObjectViewport::unregisterHandlers()
{
	GameObjectViewportPtr _this =shared_from_this();
}
//-------------------------------------------------------------------------------------------
TGameObjectViewportParameters::TGameObjectViewportParameters() : TGameObjectParameters()
{

}

TGameObjectViewportParameters::~TGameObjectViewportParameters()
{

}