#include "RenderComponentLight.h"
using namespace OUAN;

RenderComponentLight::RenderComponentLight(const std::string& name)
:RenderComponent(COMPONENT_NAME_RENDER_LIGHT)
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
