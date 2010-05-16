#include "RenderComponentPlane.h"
using namespace OUAN;

RenderComponentPlane::RenderComponentPlane(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_BILLBOARD_SET)
{
}
RenderComponentPlane::~RenderComponentPlane()
{
	mPlane=NULL;
}

Ogre::Entity* RenderComponentPlane::getPlane() const
{
	return mPlane;
}
void RenderComponentPlane::setPlane(Ogre::Entity* Plane)
{
	mPlane=Plane;
}

TRenderComponentPlaneParameters::TRenderComponentPlaneParameters() : TRenderComponentParameters()
{
}
TRenderComponentPlaneParameters::~TRenderComponentPlaneParameters()
{
}
