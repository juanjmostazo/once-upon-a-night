#include "OUAN_Precompiled.h"

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
void GameObjectItem1UP::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->destroy();
	mLogicComponentItem->setIsTaken(false);
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

void GameObjectItem1UP::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentItem->existsInDreams())
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setDreamsMaterials();
	}
	else
	{
		mRenderComponentEntity->setVisible(false);
	}
}

void GameObjectItem1UP::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentItem->existsInDreams())
	{
		mRenderComponentEntity->setVisible(false);
	}
	else
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setNightmaresMaterials();
	}
}

void GameObjectItem1UP::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectItem1UP::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			break;
		case NIGHTMARES:
			setNightmaresRender();
			break;
		default:
			break;
	}

	switch(newWorld)
	{
	case DREAMS:

		if(mLogicComponentItem->existsInDreams())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else
		{
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
			}
		}		
		break;
	case NIGHTMARES:

		if(mLogicComponentItem->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
			}
		}
		else
		{
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

void GameObjectItem1UP::changeWorldStarted(int newWorld)
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

void GameObjectItem1UP::changeToWorld(int newWorld, double perc)
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

void GameObjectItem1UP::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectItem1UP::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentItem->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponentItem->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentItem->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponentItem->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectItem1UP::enable()
{
	GameObject::enable();
	mRenderComponentEntity->setVisible(true);
	mPhysicsComponentVolumeBox->create();
}
void GameObjectItem1UP::reset()
{
	GameObject::reset();
	if (mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->setIsTaken(false);
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

void GameObjectItem1UP::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
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

	if (isEnabled())
	{
		if (isFirstUpdate())
		{
			mRenderComponentEntity->changeAnimation(ITEM1UP_ANIM_IDLE);
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}
bool GameObjectItem1UP::hasRenderComponentEntity() const
{
	return true;
}
void GameObjectItem1UP::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponentItem->existsInDreams())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponentItem->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
RenderComponentEntityPtr GameObjectItem1UP::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectItem1UP::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectItem1UP::getLogicComponentInstance() const
{
	return mLogicComponentItem;
}
TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{

}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{

}