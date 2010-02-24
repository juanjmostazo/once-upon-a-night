#include "RenderComponentCamera.h"
using namespace OUAN;

RenderComponentCamera::RenderComponentCamera(const std::string& name)
:RenderComponent(COMPONENT_NAME_RENDER_CAMERA)
{
}
RenderComponentCamera::~RenderComponentCamera()
{
	//mCamera=NULL;
}

//Ogre::Camera* RenderComponentCamera::getCamera() const
//{
//	return mCamera;
//}
//void RenderComponentCamera::setCamera(Ogre::Camera* camera)
//{
//	mCamera=camera;
//}
TRenderComponentCameraParameters::TRenderComponentCameraParameters() : TRenderComponentParameters()
{
}
TRenderComponentCameraParameters::~TRenderComponentCameraParameters()
{
}
