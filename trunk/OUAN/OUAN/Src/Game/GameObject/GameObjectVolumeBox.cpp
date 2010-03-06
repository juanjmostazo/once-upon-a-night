#include "GameObjectVolumeBox.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectVolumeBox::GameObjectVolumeBox(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeBox::~GameObjectVolumeBox()
{

}

void GameObjectVolumeBox::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeBox::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeBox::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeBox::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectVolumeBox::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectVolumeBox::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}
		break;
	case NIGHTMARES:
		break;
	default:break;
	}
}

void GameObjectVolumeBox::registerHandlers()
{
	GameObjectVolumeBoxPtr _this =shared_from_this();
	registerEventHandler<GameObjectVolumeBox,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectVolumeBox::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectVolumeBox::unregisterHandlers()
{
	GameObjectVolumeBoxPtr _this =shared_from_this();
	unregisterEventHandler<GameObjectVolumeBox,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectVolumeBox::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectVolumeBox::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}
//-------------------------------------------------------------------------------------------
TGameObjectVolumeBoxParameters::TGameObjectVolumeBoxParameters() : TGameObjectParameters()
{

}

TGameObjectVolumeBoxParameters::~TGameObjectVolumeBoxParameters()
{

}