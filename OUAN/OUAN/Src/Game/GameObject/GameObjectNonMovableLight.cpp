#include "GameObjectNonMovableLight.h"

using namespace OUAN;

GameObjectNonMovableLight::GameObjectNonMovableLight(const std::string& name, const std::string& id)
:GameObjectNonMovable(name,id)
{

}

GameObjectNonMovableLight::~GameObjectNonMovableLight()
{

}

RenderComponentLightPtr GameObjectNonMovableLight::getRenderComponentLight() const
{
	return mRenderComponentLight;
}

void GameObjectNonMovableLight::setRenderComponentLight(RenderComponentLightPtr pRenderComponentLight)
{
	mRenderComponentLight=pRenderComponentLight;
}

TGameObjectNonMovableLightParameters::TGameObjectNonMovableLightParameters() : TGameObjectNonMovableParameters()
{
}
TGameObjectNonMovableLightParameters::~TGameObjectNonMovableLightParameters()
{
}