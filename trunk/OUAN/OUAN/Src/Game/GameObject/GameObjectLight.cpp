#include "GameObjectLight.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectLight::GameObjectLight(const std::string& name)
:GameObject(name)
{

}

GameObjectLight::~GameObjectLight()
{

}

RenderComponentLightPtr GameObjectLight::getRenderComponentLight() const
{
	return mRenderComponentLight;
}

void GameObjectLight::setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight)
{
	mRenderComponentLight=pRenderComponentLight;
}
void GameObjectLight::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectLight::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectLight::changeWorld(int world)
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
void GameObjectLight::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectLight::registerHandlers()
{
	GameObjectLightPtr _this =shared_from_this();

	registerEventHandler<GameObjectLight,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectLight::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectLight::unregisterHandlers()
{
	GameObjectLightPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectLight,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectLight::processChangeWorld,
		mGameWorldManager->getEventManager());
}

//-------------------------------------------------------------------------------------------

TGameObjectLightParameters::TGameObjectLightParameters() : TGameObjectParameters()
{

}

TGameObjectLightParameters::~TGameObjectLightParameters()
{

}