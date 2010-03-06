#include "GameObjectVolumeCapsule.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectVolumeCapsule::GameObjectVolumeCapsule(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeCapsule::~GameObjectVolumeCapsule()
{

}

void GameObjectVolumeCapsule::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeCapsule::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeCapsule::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeCapsule::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeCapsule::setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule)
{
	mPhysicsComponentVolumeCapsule=pPhysicsComponentVolumeCapsule;
}

PhysicsComponentVolumeCapsulePtr GameObjectVolumeCapsule::getPhysicsComponentVolumeCapsule()
{
	return mPhysicsComponentVolumeCapsule;
}

void GameObjectVolumeCapsule::changeWorld(int world)
{
	switch(world)
	{
	case DREAMS:
		if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
		{
			mPhysicsComponentVolumeCapsule->create();
		}
		break;
	case NIGHTMARES:
		break;
	default:break;
	}
}

void GameObjectVolumeCapsule::registerHandlers()
{
	GameObjectVolumeCapsulePtr _this =shared_from_this();
	registerEventHandler<GameObjectVolumeCapsule,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectVolumeCapsule::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectVolumeCapsule::unregisterHandlers()
{
	GameObjectVolumeCapsulePtr _this =shared_from_this();
	unregisterEventHandler<GameObjectVolumeCapsule,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectVolumeCapsule::processChangeWorld,
		mGameWorldManager->getEventManager());
}

void GameObjectVolumeCapsule::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

//-------------------------------------------------------------------------------------------
TGameObjectVolumeCapsuleParameters::TGameObjectVolumeCapsuleParameters() : TGameObjectParameters()
{

}

TGameObjectVolumeCapsuleParameters::~TGameObjectVolumeCapsuleParameters()
{

}