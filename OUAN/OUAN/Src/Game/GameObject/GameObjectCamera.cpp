#include "GameObjectCamera.h"

using namespace OUAN;

GameObjectCamera::GameObjectCamera(const std::string& name)
:GameObject(name)
{

}

GameObjectCamera::~GameObjectCamera()
{

}

RenderComponentCameraPtr GameObjectCamera::getRenderComponentCamera() const
{
	return mRenderComponentCamera;
}

void GameObjectCamera::setRenderComponentCamera(RenderComponentCameraPtr pRenderComponentCamera)
{
	mRenderComponentCamera=pRenderComponentCamera;
}

TGameObjectCameraParameters::TGameObjectCameraParameters() : TGameObjectParameters()
{
}
TGameObjectCameraParameters::~TGameObjectCameraParameters()
{
}