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

void GameObjectLight::registerHandlers()
{
	GameObjectLightPtr _this =shared_from_this();
}

void GameObjectLight::unregisterHandlers()
{
	GameObjectLightPtr _this =shared_from_this();
}

//-------------------------------------------------------------------------------------------

TGameObjectLightParameters::TGameObjectLightParameters() : TGameObjectParameters()
{

}

TGameObjectLightParameters::~TGameObjectLightParameters()
{

}