#include "GameObjectClockPiece.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectClockPiece::GameObjectClockPiece(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CLOCKPIECE)
{

}

GameObjectClockPiece::~GameObjectClockPiece()
{

}

RenderComponentEntityPtr GameObjectClockPiece::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectClockPiece::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectClockPiece::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectClockPiece::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectClockPiece::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectClockPiece::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectClockPiece::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectClockPiece::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectClockPiece::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	//mRenderComponentEntity->setOriginalMaterials();
	mRenderComponentPositional->setScale(Vector3(1,1,1));

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
}

void GameObjectClockPiece::changeWorldStarted(int newWorld)
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

void GameObjectClockPiece::changeToWorld(int newWorld, double perc)
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


void GameObjectClockPiece::reset()
{
	GameObject::reset();
	mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
}

bool GameObjectClockPiece::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectClockPiece::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectClockPiece::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectClockPiece::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


/// Set logic component
void GameObjectClockPiece::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectClockPiece::getLogicComponentItem()
{
	return mLogicComponentItem;
}

void GameObjectClockPiece::processCollision(GameObjectPtr pGameObject)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject);
	}
}

void GameObjectClockPiece::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectClockPiece::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectClockPiece::updateLogic(double elapsedSeconds)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->update(elapsedSeconds);
	}
}

void GameObjectClockPiece::update(double elapsedSeconds)
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
bool GameObjectClockPiece::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectClockPiece::getEntityComponent() const
{
	return mRenderComponentEntity;
}
TGameObjectClockPieceParameters::TGameObjectClockPieceParameters() : TGameObjectParameters()
{

}

TGameObjectClockPieceParameters::~TGameObjectClockPieceParameters()
{

}