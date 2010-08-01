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

void GameObjectDiamond::setDreamsRender()
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

void GameObjectDiamond::setNightmaresRender()
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

void GameObjectDiamond::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectDiamond::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectDiamond::changeWorldFinished(int newWorld)
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
			break;
		case NIGHTMARES:
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
			break;
		case NIGHTMARES:	
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
	//mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
	mLogicComponentItem->setIsTaken(false);
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


void GameObjectDiamond::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
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

void GameObjectDiamond::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (mLogicComponentItem->isStateChanged())
	{
		if (mLogicComponentItem->getState()==STATE_ITEM_TAKEN)
		{
			disable();
			mLogicComponentItem->setStateChanged(false);
		}
	}	
	if (isEnabled())
	{
		if (isFirstUpdate())
		{
			mRenderComponentEntity->changeAnimation(DIAMOND_ANIM_IDLE);
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
		if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			if (mPhysicsComponentSimpleBox->isOnSurface())
			{
				mPhysicsComponentSimpleBox->destroy();
				//mPhysicsComponentVolumeBox->create();
				NxOgre::Vec3 position;
				position.x=mRenderComponentPositional->getPosition().x;
				position.y=mRenderComponentPositional->getPosition().y;
				position.z=mRenderComponentPositional->getPosition().z;
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
					mPhysicsComponentVolumeBox->create();
				mPhysicsComponentVolumeBox->setPosition(position);
			}

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
		return BOOST_PTR_CAST(GameObjectDiamondTree,mGameWorldManager->getObject(mParentDiamondTreeName));
	}
	return GameObjectDiamondTreePtr();
}
void GameObjectDiamond::setParentDiamondTree(GameObjectDiamondTreePtr parent)
{
	mParentDiamondTree=parent;
}

/// Set physics component
void GameObjectDiamond::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

/// Get physics component
PhysicsComponentSimpleBoxPtr GameObjectDiamond::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

/// Tell if this game object is bound to a diamond tree.
bool GameObjectDiamond::isBoundToTree() const
{
	return !mParentDiamondTreeName.empty();
}

void GameObjectDiamond::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->destroy();
	if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		mPhysicsComponentSimpleBox->destroy();
	mLogicComponentItem->setIsTaken(false);
}
void GameObjectDiamond::enable()
{
	GameObject::enable();
	mRenderComponentEntity->setVisible(true);
	mPhysicsComponentVolumeBox->create();
}
void GameObjectDiamond::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
	if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	mPhysicsComponentSimpleBox->update(elapsedSeconds);
}

void GameObjectDiamond::setVisible(bool visible)
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
bool GameObjectDiamond::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectDiamond::getLogicComponentInstance() const
{
	return mLogicComponentItem;
}
TGameObjectDiamondParameters::TGameObjectDiamondParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondParameters::~TGameObjectDiamondParameters()
{

}