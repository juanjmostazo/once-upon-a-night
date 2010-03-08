#include "GameObjectItem1UP.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectItem1UP::GameObjectItem1UP(const std::string& name)
:GameObject(name)
{

}

GameObjectItem1UP::~GameObjectItem1UP()
{

}

RenderComponentEntityPtr GameObjectItem1UP::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectItem1UP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectItem1UP::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectItem1UP::getPhysicsComponentSimpleCapsule()
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectItem1UP::setLogicComponentWorldExistance(LogicComponentWorldExistancePtr pLogicComponentWorldExistance)
{
	mLogicComponentWorldExistance=pLogicComponentWorldExistance;
}

LogicComponentWorldExistancePtr GameObjectItem1UP::getLogicComponentWorldExistance()
{
	return mLogicComponentWorldExistance;
}

void GameObjectItem1UP::changeWorld(int world)
{
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:
			if(mLogicComponentWorldExistance->getExistsInDreams())
			{
				mRenderComponentEntity->setVisible(true);

				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentWorldExistance->getExistsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}
			break;
		default:
			break;
		}
	}

}

void GameObjectItem1UP::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
}

void GameObjectItem1UP::registerHandlers()
{
	GameObjectItem1UPPtr _this =shared_from_this();
	//Subscribe to world change event
	registerEventHandler<GameObjectItem1UP,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectItem1UP::processChangeWorld,
		mGameWorldManager->getEventManager());

}
void GameObjectItem1UP::unregisterHandlers()
{
	GameObjectItem1UPPtr _this =shared_from_this();
	//Subscribe to world change event
	registerEventHandler<GameObjectItem1UP,ChangeWorldEvent,EVENT_TYPE_CHANGEWORLD>(_this,&GameObjectItem1UP::processChangeWorld,
		mGameWorldManager->getEventManager());

}
//-------------------------------------------------------------------------------------------

TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{

}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{

}