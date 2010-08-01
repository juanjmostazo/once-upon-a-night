#include "OUAN_Precompiled.h"

#include "GameObjectStoryBook.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectStoryBook::GameObjectStoryBook(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_STORYBOOK)
{

}

GameObjectStoryBook::~GameObjectStoryBook()
{

}

/// Set logic component
void GameObjectStoryBook::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectStoryBook::getLogicComponentItem()
{
	return mLogicComponentItem;
}

RenderComponentEntityPtr GameObjectStoryBook::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectStoryBook::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectStoryBook::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectStoryBook::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectStoryBook::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectStoryBook::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectStoryBook::setDreamsRender()
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

void GameObjectStoryBook::setNightmaresRender()
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

void GameObjectStoryBook::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectStoryBook::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectStoryBook::changeWorldFinished(int newWorld)
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

void GameObjectStoryBook::changeWorldStarted(int newWorld)
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

void GameObjectStoryBook::changeToWorld(int newWorld, double perc)
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

void GameObjectStoryBook::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectStoryBook::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectStoryBook::reset()
{
	GameObject::reset();
	mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
}

bool GameObjectStoryBook::hasPositionalComponent() const
{
	return true;
}

void GameObjectStoryBook::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get() && !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
	}
}

void GameObjectStoryBook::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectStoryBook::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectStoryBook::update(double elapsedSeconds)
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
			mRenderComponentEntity->changeAnimation("turn");
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}

bool GameObjectStoryBook::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectStoryBook::getEntityComponent() const
{
	return mRenderComponentEntity;
}
RenderComponentPositionalPtr GameObjectStoryBook::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectStoryBook::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectStoryBook::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}
void GameObjectStoryBook::setVisible(bool visible)
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
bool GameObjectStoryBook::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectStoryBook::getLogicComponentInstance() const
{
	return mLogicComponentItem;
}
TGameObjectStoryBookParameters::TGameObjectStoryBookParameters() : TGameObjectParameters()
{

}

TGameObjectStoryBookParameters::~TGameObjectStoryBookParameters()
{

}