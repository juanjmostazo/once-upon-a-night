#include "GameObjectLight.h"

using namespace OUAN;

GameObjectLight::GameObjectLight(const std::string& name, const std::string& id)
:GameObject(LOADER_LIGHT_ID,id)
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
void GameObjectLight::setRenderComponentPositional(RenderComponentPositionalPtr pPositionalEntity)
{
	mRenderComponentPositional=pPositionalEntity;
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