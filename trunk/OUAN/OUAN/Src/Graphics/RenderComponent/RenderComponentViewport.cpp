#include "RenderComponentViewport.h"
using namespace OUAN;

RenderComponentViewport::RenderComponentViewport(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}

RenderComponentViewport::~RenderComponentViewport()
{
	mViewport=NULL;
}

Ogre::Viewport* RenderComponentViewport::getViewport() const
{
	return mViewport;
}
void RenderComponentViewport::setViewport(Ogre::Viewport* viewport)
{
	mViewport=viewport;
}
TRenderComponentViewportParameters::TRenderComponentViewportParameters() : TRenderComponentParameters()
{
}
TRenderComponentViewportParameters::~TRenderComponentViewportParameters()
{
}