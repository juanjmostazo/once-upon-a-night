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

void GameObjectCamera::setDreamsMode()
{

}

void GameObjectCamera::setNightmaresMode()
{

}

TGameObjectCameraParameters::TGameObjectCameraParameters() : TGameObjectParameters()
{

}

TGameObjectCameraParameters::~TGameObjectCameraParameters()
{

}