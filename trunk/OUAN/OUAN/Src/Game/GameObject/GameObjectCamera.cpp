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

void GameObjectCamera::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectCamera::registerHandlers()
{
	GameObjectCameraPtr _this =shared_from_this();

	registerEventHandler<GameObjectCamera,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectCamera::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectCamera::unregisterHandlers()
{
	GameObjectCameraPtr _this =shared_from_this();

	unregisterEventHandler<GameObjectCamera,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectCamera::processChangeWorld,
		mGameWorldManager->getEventManager());
}
//-------------------------------------------------------------------------------------------

TGameObjectCameraParameters::TGameObjectCameraParameters() : TGameObjectParameters()
{

}

TGameObjectCameraParameters::~TGameObjectCameraParameters()
{

}


