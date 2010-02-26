#include "RenderComponentViewport.h"
using namespace OUAN;

RenderComponentViewport::RenderComponentViewport(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_VIEWPORT)
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