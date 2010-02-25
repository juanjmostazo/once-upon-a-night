#include "GameObjectLight.h"

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

TGameObjectLightParameters::TGameObjectLightParameters() : TGameObjectParameters()
{
}
TGameObjectLightParameters::~TGameObjectLightParameters()
{
}