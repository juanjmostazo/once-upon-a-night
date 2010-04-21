#include "GameObjectItemMaxHP.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectItemMaxHP::GameObjectItemMaxHP(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ITEM_MAXHP)
{

}

GameObjectItemMaxHP::~GameObjectItemMaxHP()
{

}


/// Set logic component
void GameObjectItemMaxHP::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectItemMaxHP::getLogicComponentItem()
{
	return mLogicComponentItem;
}

RenderComponentEntityPtr GameObjectItemMaxHP::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectItemMaxHP::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectItemMaxHP::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectItemMaxHP::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectItemMaxHP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectItemMaxHP::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectItemMaxHP::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectItemMaxHP::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectItemMaxHP::changeWorld(int world)
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

void GameObjectItemMaxHP::reset()
{
	GameObject::reset();
	mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
}

bool GameObjectItemMaxHP::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectItemMaxHP::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectItemMaxHP::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectItemMaxHP::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}

void GameObjectItemMaxHP::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processCollision(pGameObject);
	}
}

void GameObjectItemMaxHP::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectItemMaxHP::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectItemMaxHP::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->update(elapsedSeconds);
	}
}

void GameObjectItemMaxHP::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (mLogicComponentItem->isStateChanged())
	{
		if (mLogicComponentItem->getState()==STATE_ITEM_TAKEN)
		{
			mRenderComponentEntity->setVisible(false);
			mPhysicsComponentVolumeBox->destroy();
		}
	}
}

TGameObjectItemMaxHPParameters::TGameObjectItemMaxHPParameters() : TGameObjectParameters()
{

}

TGameObjectItemMaxHPParameters::~TGameObjectItemMaxHPParameters()
{

}