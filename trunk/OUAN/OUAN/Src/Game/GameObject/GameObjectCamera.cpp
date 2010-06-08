#include "OUAN_Precompiled.h"

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

void GameObjectCamera::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectCamera::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectCamera::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	switch(newWorld)
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


