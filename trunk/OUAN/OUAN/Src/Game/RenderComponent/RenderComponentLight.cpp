#include "RenderComponentLight.h"
using namespace OUAN;

RenderComponentLight::RenderComponentLight(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponentLight::~RenderComponentLight()
{
	mLight=NULL;
}

Ogre::Light* RenderComponentLight::getLight() const
{
	return mLight;
}
void RenderComponentLight::setLight(Ogre::Light* light)
{
	mLight=light;
}

TRenderComponentLightParameters::TRenderComponentLightParameters() : TRenderComponentParameters()
{
}
TRenderComponentLightParameters::~TRenderComponentLightParameters()
{
}
