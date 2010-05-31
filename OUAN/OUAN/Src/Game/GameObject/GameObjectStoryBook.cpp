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

void GameObjectStoryBook::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	//mRenderComponentEntity->setOriginalMaterials();
	mRenderComponentPositional->setScale(Vector3(1,1,1));

	switch(newWorld)
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

void GameObjectStoryBook::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	//if(mLogicComponentItem->existsInDreams()&& !mLogicComponentItem->existsInNightmares())
	//{
	//	mRenderComponentEntity->setChangeWorldMaterials();
	//	mRenderComponentEntity->randomizeChangeWorldMaterials();
	//}

	//if(mLogicComponentItem->existsInNightmares()&& !mLogicComponentItem->existsInNightmares())
	//{
	//	mRenderComponentEntity->setChangeWorldMaterials();
	//	mRenderComponentEntity->randomizeChangeWorldMaterials();
	//}

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponentItem->existsInDreams()&& !mLogicComponentItem->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(true);
			mRenderComponentPositional->setScale(Vector3(0,0,0));
		}
		break;
	case NIGHTMARES:
		if(!mLogicComponentItem->existsInDreams()&& mLogicComponentItem->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(true);
			mRenderComponentPositional->setScale(Vector3(0,0,0));
		}	
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
			if(mLogicComponentItem->existsInDreams()&& !mLogicComponentItem->existsInNightmares())
			{
				//mRenderComponentEntity->setChangeWorldFactor(1-perc);
				mRenderComponentPositional->setScale(Vector3(perc,perc,perc));
			}
			else if(!mLogicComponentItem->existsInDreams()&& mLogicComponentItem->existsInNightmares())
			{
				//mRenderComponentEntity->setChangeWorldFactor(perc);
				mRenderComponentPositional->setScale(Vector3(1-perc,1-perc,1-perc));
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentItem->existsInDreams()&& !mLogicComponentItem->existsInNightmares())
			{
				//mRenderComponentEntity->setChangeWorldFactor(perc);
				mRenderComponentPositional->setScale(Vector3(1-perc,1-perc,1-perc));
			}
			else if(!mLogicComponentItem->existsInDreams()&& mLogicComponentItem->existsInNightmares())
			{
				//mRenderComponentEntity->setChangeWorldFactor(1-perc);
				mRenderComponentPositional->setScale(Vector3(perc,perc,perc));
			}		
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

void GameObjectStoryBook::processCollision(GameObjectPtr pGameObject)
{
	if (isEnabled() && mLogicComponentItem.get() && !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject);
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

void GameObjectStoryBook::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->update(elapsedSeconds);
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


TGameObjectStoryBookParameters::TGameObjectStoryBookParameters() : TGameObjectParameters()
{

}

TGameObjectStoryBookParameters::~TGameObjectStoryBookParameters()
{

}