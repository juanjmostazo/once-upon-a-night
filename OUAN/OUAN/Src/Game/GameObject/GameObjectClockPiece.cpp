#include "OUAN_Precompiled.h"

#include "GameObjectClockPiece.h"
#include "../GameWorldManager.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

GameObjectClockPiece::GameObjectClockPiece(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CLOCKPIECE)
{

}

GameObjectClockPiece::~GameObjectClockPiece()
{

}

void GameObjectClockPiece::makeAppear(Ogre::Vector3 position)
{
	mRenderComponentEntity->setVisible(true);
	if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->create();		

	mPhysicsComponentVolumeBox->getSceneNode()->setPosition(position);
	mRenderComponentPositional->setPosition(position);

	mRenderComponentGlow->setVisible(true);
	mLogicComponentItem->setState(STATE_ITEM_NOT_TAKEN);
}

RenderComponentEntityPtr GameObjectClockPiece::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

AudioComponentPtr GameObjectClockPiece::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectClockPiece::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


void GameObjectClockPiece::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectClockPiece::setRenderComponentGlow(RenderComponentGlowPtr pRenderComponentGlow)
{
	mRenderComponentGlow=pRenderComponentGlow;
}

RenderComponentGlowPtr GameObjectClockPiece::getRenderComponentGlow() const
{
	return mRenderComponentGlow;
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

void GameObjectClockPiece::setRenderComponentParticleSystemStarsCloud(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStarsCloud)
{
	mRenderComponentParticleSystemStarsCloud = pRenderComponentParticleSystemStarsCloud;
}

RenderComponentParticleSystemPtr GameObjectClockPiece::getRenderComponentParticleSystemStarsCloud() const
{
	return mRenderComponentParticleSystemStarsCloud;
}

void GameObjectClockPiece::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectClockPiece::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectClockPiece::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentItem->existsInDreams())
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setDreamsMaterials();
		mRenderComponentGlow->setVisible(true);
	}
	else
	{
		mRenderComponentEntity->setVisible(false);
		mRenderComponentGlow->setVisible(false);
	}
}

void GameObjectClockPiece::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponentItem->existsInNightmares())
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setNightmaresMaterials();
		mRenderComponentGlow->setVisible(true);
	}
	else
	{
		mRenderComponentEntity->setVisible(false);
		mRenderComponentGlow->setVisible(false);
	}
}

void GameObjectClockPiece::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectClockPiece::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectClockPiece::changeWorldFinished(int newWorld)
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

	if(mLogicComponentItem->existsInDreams() && mLogicComponentItem->existsInNightmares())
	{
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}
		return;
	}
	else
	{
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
}

void GameObjectClockPiece::changeToWorld(int newWorld, double perc)
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


void GameObjectClockPiece::reset()
{
	GameObject::reset();
	mLogicComponentItem->setState(STATE_ITEM_TAKEN);
	mRenderComponentEntity->setVisible(false);
	mRenderComponentGlow->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
		mPhysicsComponentVolumeBox->destroy();		
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

void GameObjectClockPiece::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
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

void GameObjectClockPiece::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	if (mLogicComponentItem->isStateChanged())
	{
		if (mLogicComponentItem->getState()==STATE_ITEM_TAKEN)
		{
			mRenderComponentEntity->setVisible(false);
			mRenderComponentGlow->setVisible(false);
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
				mPhysicsComponentVolumeBox->destroy();		
		}
		else if (mLogicComponentItem->getState()==STATE_ITEM_NOT_TAKEN)
		{
			mRenderComponentEntity->setVisible(true);
			mRenderComponentGlow->setVisible(true);
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				mPhysicsComponentVolumeBox->create();		
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

void GameObjectClockPiece::setVisible(bool visible)
{
	if (mLogicComponentItem->getState()!=STATE_ITEM_TAKEN)
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
}

bool GameObjectClockPiece::hasLogicComponent() const
{
	return true;
}

LogicComponentPtr GameObjectClockPiece::getLogicComponent() const
{
	return mLogicComponentItem;
}

void GameObjectClockPiece::startCollisionEffects()
{
	mRenderComponentParticleSystemStarsCloud->start();
}

TGameObjectClockPieceParameters::TGameObjectClockPieceParameters() : TGameObjectParameters()
{

}

TGameObjectClockPieceParameters::~TGameObjectClockPieceParameters()
{

}