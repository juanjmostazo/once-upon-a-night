#include "RenderComponentCamera.h"
using namespace OUAN;

RenderComponentCamera::RenderComponentCamera(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponentCamera::~RenderComponentCamera()
{
	mCamera=NULL;
}

Ogre::Camera* RenderComponentCamera::getCamera() const
{
	return mCamera;
}
void RenderComponentCamera::setCamera(Ogre::Camera* camera)
{
	mCamera=camera;
}
