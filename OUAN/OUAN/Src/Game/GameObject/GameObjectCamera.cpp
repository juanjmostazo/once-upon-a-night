#include "GameObjectCamera.h"

using namespace OUAN;

GameObjectCamera::GameObjectCamera(const std::string& name, const std::string& id)
:GameObject(name,id)
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