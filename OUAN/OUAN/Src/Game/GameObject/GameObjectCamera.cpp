#include "GameObjectCamera.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectCamera::GameObjectCamera(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CAMERA)
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
	if (!isEnabled()) return;

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


