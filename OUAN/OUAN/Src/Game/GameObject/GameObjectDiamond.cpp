#include "OUAN_Precompiled.h"

#include "GameObjectDiamond.h"
#include "GameObjectDiamondTree.h"
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

void GameObjectDiamond::changeWorldFinished(int newWorld)
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

void GameObjectDiamond::changeWorldStarted(int newWorld)
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

void GameObjectDiamond::changeToWorld(int newWorld, double perc)
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

void GameObjectDiamond::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectDiamond::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

std::string& GameObjectDiamond::getParentDiamondTreeName()
{
	return mParentDiamondTreeName;
}
void GameObjectDiamond::setParentDiamondTreeName(const std::string& parentName)
{
	mParentDiamondTreeName=parentName;
}

GameObjectDiamondTreePtr GameObjectDiamond::getParentDiamondTree() const
{
	if (!mParentDiamondTree.get() && !mParentDiamondTreeName.empty())
	{
		return boost::dynamic_pointer_cast<GameObjectDiamondTree>(mGameWorldManager->getObject(mParentDiamondTreeName));
	}
	return GameObjectDiamondTreePtr();
}
void GameObjectDiamond::setParentDiamondTree(GameObjectDiamondTreePtr parent)
{
	mParentDiamondTree=parent;
}
TGameObjectDiamondParameters::TGameObjectDiamondParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondParameters::~TGameObjectDiamondParameters()
{

}