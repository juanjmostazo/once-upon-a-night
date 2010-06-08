#include "OUAN_Precompiled.h"

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

void RenderComponentLight::setVisible(bool visible)
{
	mLight->setVisible(visible);
}

void RenderComponentLight::setDiffuseColor(ColourValue colour)
{
	mLight->setDiffuseColour(colour);
}

void RenderComponentLight::setSpecularColor(ColourValue colour)
{
	mLight->setSpecularColour(colour);
}

void RenderComponentLight::setDirection(Vector3 direction)
{
	mLight->setDirection(direction);
}

TRenderComponentLightParameters::TRenderComponentLightParameters() : TRenderComponentParameters()
{

}

TRenderComponentLightParameters::~TRenderComponentLightParameters()
{

}
