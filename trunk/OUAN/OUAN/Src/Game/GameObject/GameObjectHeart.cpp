#include "OUAN_Precompiled.h"

#include "GameObjectHeart.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectHeart::GameObjectHeart(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_HEART)
{
	
}

GameObjectHeart::~GameObjectHeart()
{

}
void GameObjectHeart::reset()
{
	GameObject::reset();
	//mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
	mLogicComponentItem->setIsTaken(false);
}
void GameObjectHeart::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->destroy();	
	mLogicComponentItem->setIsTaken(false);
}

RenderComponentEntityPtr GameObjectHeart::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectHeart::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectHeart::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectHeart::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectHeart::setRenderComponentParticleSystemStarsCloud(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStarsCloud)
{
	mRenderComponentParticleSystemStarsCloud = pRenderComponentParticleSystemStarsCloud;
}

RenderComponentParticleSystemPtr GameObjectHeart::getRenderComponentParticleSystemStarsCloud() const
{
	return mRenderComponentParticleSystemStarsCloud;
}

void GameObjectHeart::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectHeart::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectHeart::setDreamsRender()
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

void GameObjectHeart::setNightmaresRender()
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
void GameObjectHeart::enable()
{
	mRenderComponentEntity->setVisible(true);
	if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->create();
}

void GameObjectHeart::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectHeart::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectHeart::changeWorldFinished(int newWorld)
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

void GameObjectHeart::changeWorldStarted(int newWorld)
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

void GameObjectHeart::changeToWorld(int newWorld, double perc)
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

void GameObjectHeart::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectHeart::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

/// Set logic component
void GameObjectHeart::setLogicComponentItem(LogicComponentItemPtr logicComponentItem)
{
	mLogicComponentItem=logicComponentItem;
}

/// return logic component
LogicComponentItemPtr GameObjectHeart::getLogicComponentItem()
{
	return mLogicComponentItem;
}


bool GameObjectHeart::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectHeart::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectHeart::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectHeart::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}

void GameObjectHeart::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
	}
}

void GameObjectHeart::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processEnterTrigger(pGameObject);
	}
}

void GameObjectHeart::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponentItem.get())
	{
		mLogicComponentItem->processExitTrigger(pGameObject);
	}
}

void GameObjectHeart::update(double elapsedSeconds)
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
			mRenderComponentEntity->changeAnimation("idle01");
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}
bool GameObjectHeart::hasRenderComponentEntity() const
{
	return true;
}
void GameObjectHeart::setVisible(bool visible)
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
RenderComponentEntityPtr GameObjectHeart::getEntityComponent() const
{
	return mRenderComponentEntity;
}
bool GameObjectHeart::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectHeart::getLogicComponentInstance() const
{
	return mLogicComponentItem;
}
TGameObjectHeartParameters::TGameObjectHeartParameters() : TGameObjectParameters()
{

}

TGameObjectHeartParameters::~TGameObjectHeartParameters()
{

}