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
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		mRenderComponentEntity->setVisible(true);
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}
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
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:

			if(mLogicComponentWorldExistance->getExistsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
			}
			break;
		default:
			break;
		}
	}
}
//-------------------------------------------------------------------------------------------

void GameObjectVolumeBox::processChangeWorld(ChangeWorldEventPtr evt)
{
	changeWorld(evt->getNewWorld());
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
//-------------------------------------------------------------------------------------------

TGameObjectVolumeBoxParameters::TGameObjectVolumeBoxParameters() : TGameObjectParameters()
{

}

TGameObjectVolumeBoxParameters::~TGameObjectVolumeBoxParameters()
{

}