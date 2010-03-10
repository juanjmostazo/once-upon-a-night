#include "GameObjectCamera.h"
#include "../GameWorldManager.h"

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

void GameObjectCamera::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}
//-------------------------------------------------------------------------------------------

TGameObjectCameraParameters::TGameObjectCameraParameters() : TGameObjectParameters()
{

}

TGameObjectCameraParameters::~TGameObjectCameraParameters()
{

}


