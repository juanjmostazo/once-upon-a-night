#include "OUAN_Precompiled.h"

#include "GameObjectItemMaxHP.h"
#include "../GameWorldManager.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"

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

AudioComponentPtr GameObjectItemMaxHP::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectItemMaxHP::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
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

void GameObjectItemMaxHP::setRenderComponentParticleSystemHeartsFountain(RenderComponentParticleSystemPtr pRenderComponentParticleSystemHeartsFountain)
{
	mRenderComponentParticleSystemHeartsFountain = pRenderComponentParticleSystemHeartsFountain;
}

void GameObjectItemMaxHP::setRenderComponentParticleSystemHeartsFountainDouble(RenderComponentParticleSystemPtr pRenderComponentParticleSystemHeartsFountainDouble)
{
	mRenderComponentParticleSystemHeartsFountainDouble = pRenderComponentParticleSystemHeartsFountainDouble;
}

void GameObjectItemMaxHP::setRenderComponentParticleSystemStarsCloud(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStarsCloud)
{
	mRenderComponentParticleSystemStarsCloud = pRenderComponentParticleSystemStarsCloud;
}

RenderComponentParticleSystemPtr GameObjectItemMaxHP::getRenderComponentParticleSystemHeartsFountain() const
{
	return mRenderComponentParticleSystemHeartsFountain;
}

RenderComponentParticleSystemPtr GameObjectItemMaxHP::getRenderComponentParticleSystemHeartsFountainDouble() const
{
	return mRenderComponentParticleSystemHeartsFountainDouble;
}

RenderComponentParticleSystemPtr GameObjectItemMaxHP::getRenderComponentParticleSystemStarsCloud() const
{
	return mRenderComponentParticleSystemStarsCloud;
}

void GameObjectItemMaxHP::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectItemMaxHP::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectItemMaxHP::setDreamsRender()
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

void GameObjectItemMaxHP::setNightmaresRender()
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

void GameObjectItemMaxHP::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectItemMaxHP::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

void GameObjectItemMaxHP::changeWorldFinished(int newWorld)
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
				mRenderComponentParticleSystemHeartsFountain->start();
			}
		}
		else
		{
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
				mRenderComponentParticleSystemHeartsFountain->stop();
			}
		}		
		break;
	case NIGHTMARES:

		if(mLogicComponentItem->existsInNightmares())
		{
			if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->create();
				mRenderComponentParticleSystemHeartsFountain->start();
			}
		}
		else
		{
			if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
			{
				mPhysicsComponentVolumeBox->destroy();
				mRenderComponentParticleSystemHeartsFountain->stop();
			}
		}
		break;
	default:
		break;
	}
}

void GameObjectItemMaxHP::changeWorldStarted(int newWorld)
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

void GameObjectItemMaxHP::changeToWorld(int newWorld, double perc)
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

void GameObjectItemMaxHP::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectItemMaxHP::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectItemMaxHP::reset()
{
	GameObject::reset();
	mLogicComponentItem->setIsTaken(false);
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

void GameObjectItemMaxHP::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (isEnabled() && mLogicComponentItem.get()&& !mLogicComponentItem->getIsTaken())
	{
		mLogicComponentItem->processCollision(pGameObject, pNormal);
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

void GameObjectItemMaxHP::update(double elapsedSeconds)
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
			mRenderComponentEntity->changeAnimation(MAXHP_ANIM_IDLE);
		}
		else
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}
bool GameObjectItemMaxHP::hasRenderComponentEntity() const
{
	return true;
}
void GameObjectItemMaxHP::setVisible(bool visible)
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

RenderComponentEntityPtr GameObjectItemMaxHP::getEntityComponent() const
{
	return mRenderComponentEntity;
}

bool GameObjectItemMaxHP::hasLogicComponent() const
{
	return true;
}

LogicComponentPtr GameObjectItemMaxHP::getLogicComponentInstance() const
{
	return mLogicComponentItem;
}

void GameObjectItemMaxHP::startCollisionEffects()
{
	mRenderComponentParticleSystemHeartsFountain->stop();

	mRenderComponentParticleSystemStarsCloud->start();
	mRenderComponentParticleSystemHeartsFountainDouble->start();

	mAudioComponent->playSound("maxHP");
}
void GameObjectItemMaxHP::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);
	if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
	{
		mPhysicsComponentVolumeBox->destroy();
	}
	mLogicComponentItem->setIsTaken(false);
	mRenderComponentParticleSystemHeartsFountain->stop();
}
void GameObjectItemMaxHP::enable()
{
	GameObject::enable();
	mRenderComponentEntity->setVisible(true);
	mPhysicsComponentVolumeBox->create();
	mRenderComponentParticleSystemHeartsFountain->start();

}

TGameObjectItemMaxHPParameters::TGameObjectItemMaxHPParameters() : TGameObjectParameters()
{

}

TGameObjectItemMaxHPParameters::~TGameObjectItemMaxHPParameters()
{

}