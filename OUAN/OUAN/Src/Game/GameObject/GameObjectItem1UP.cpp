#include "GameObjectItem1UP.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectItem1UP::GameObjectItem1UP(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ITEM_1UP)
{

}

GameObjectItem1UP::~GameObjectItem1UP()
{

}

/// Set logic component
void GameObjectItem1UP::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectItem1UP::getLogicComponentItem()
{
	return mLogicComponentItem;
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

void GameObjectItem1UP::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectItem1UP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectItem1UP::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectItem1UP::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectItem1UP::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectItem1UP::changeWorld(int world)
{
	if (!isEnabled()) return;

	if(mLogicComponentItem->existsInDreams() && mLogicComponentItem->existsInNightmares())
	{
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}

		mRenderComponentEntity->setVisible(true);
		return;
	}
	else
	{
		switch(world)
		{
		case DREAMS:

			if(mLogicComponentItem->existsInDreams())
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

			if(mLogicComponentItem->existsInNightmares())
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

void GameObjectItem1UP::reset()
{
	GameObject::reset();
	if (mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
		disable();
	}
	
}

bool GameObjectItem1UP::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectItem1UP::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectItem1UP::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectItem1UP::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}

void GameObjectItem1UP::processCollision(GameObjectPtr pGameObject)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject);
	}
}

void GameObjectItem1UP::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectItem1UP::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectItem1UP::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->update(elapsedSeconds);
	}
}

void GameObjectItem1UP::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if (mLogicComponentItem->isStateChanged())
	{
		if (mLogicComponentItem->getState()==STATE_ITEM_TAKEN)
		{
			mRenderComponentEntity->setVisible(false);
			mPhysicsComponentVolumeBox->destroy();
			mLogicComponentItem->setStateChanged(false);
		}
	}
}
bool GameObjectItem1UP::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectItem1UP::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{

}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{

}