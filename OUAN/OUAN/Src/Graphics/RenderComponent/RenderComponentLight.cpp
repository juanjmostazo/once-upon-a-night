#include "RenderComponentLight.h"
using namespace OUAN;

RenderComponentLight::RenderComponentLight(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_LIGHT)
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
