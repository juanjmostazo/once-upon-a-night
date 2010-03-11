#include "RenderComponentCamera.h"
using namespace OUAN;

RenderComponentCamera::RenderComponentCamera(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_CAMERA)
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
void RenderComponentCamera::setCameraParameters(TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	//Set parameters as new initial parameters
	initialParameters=tRenderComponentCameraParameters;

	//Set Camera Parameters
	mCamera->setPolygonMode(tRenderComponentCameraParameters.polygonmode);
	mCamera->setPosition(tRenderComponentCameraParameters.position);
	mCamera->setOrientation(tRenderComponentCameraParameters.orientation);
	mCamera->setAutoAspectRatio(tRenderComponentCameraParameters.autoaspectratio);

	mCamera->setNearClipDistance(tRenderComponentCameraParameters.clipdistance.x);
	mCamera->setFarClipDistance(tRenderComponentCameraParameters.clipdistance.y);
	
	mCamera->setFOVy(Ogre::Angle(tRenderComponentCameraParameters.FOVy));

	////set autotracktarget
	//if(tRenderComponentCameraParameters.autotracktarget.compare("None")!=0)
	//{
	//	//TODO test this
	//	SceneNode *trackTarget;
	//	trackTarget=mSceneManager->getSceneNode(tRenderComponentCameraParameters.autotracktarget);
	//	mCamera->setAutoTracking(true,trackTarget);
	//}
}
void RenderComponentCamera::resetCameraParameters()
{
	setCameraParameters(this->initialParameters);
}
TRenderComponentCameraParameters::TRenderComponentCameraParameters() : TRenderComponentParameters()
{
}
TRenderComponentCameraParameters::~TRenderComponentCameraParameters()
{
}
