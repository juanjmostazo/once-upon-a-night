#include "GameObjectDiamond.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDiamond::GameObjectDiamond(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMOND)
{

}

GameObjectDiamond::~GameObjectDiamond()
{

}

RenderComponentEntityPtr GameObjectDiamond::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}
/// Set logic component
void GameObjectDiamond::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectDiamond::getLogicComponentItem()
{
	return mLogicComponentItem;
}

void GameObjectDiamond::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectDiamond::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDiamond::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDiamond::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDiamond::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDiamond::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectDiamond::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectDiamond::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

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

void GameObjectDiamond::changeWorldStarted(int world)
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

void GameObjectDiamond::changeToWorld(int world, double perc)
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

void GameObjectDiamond::reset()
{
	GameObject::reset();
	mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
}

bool GameObjectDiamond::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDiamond::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectDiamond::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectDiamond::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


void GameObjectDiamond::processCollision(GameObjectPtr pGameObject)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject);
	}
}

void GameObjectDiamond::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectDiamond::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectDiamond::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->update(elapsedSeconds);
	}
}
void GameObjectDiamond::update(double elapsedSeconds)
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
	if (isEnabled())
	{
		if (isFirstUpdate())
		{
			mRenderComponentEntity->changeAnimation("idle_Clip");
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}
bool GameObjectDiamond::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDiamond::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectDiamondParameters::TGameObjectDiamondParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondParameters::~TGameObjectDiamondParameters()
{

}