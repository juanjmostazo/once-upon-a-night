#include "OUAN_Precompiled.h"

#include "GameObjectBreakableRock.h"
#include "GameObjectInvisibleWall.h"
#include "../GameWorldManager.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

GameObjectBreakableRock::GameObjectBreakableRock(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_BREAKABLE_ROCK)
{

}

GameObjectBreakableRock::~GameObjectBreakableRock()
{

}

void GameObjectBreakableRock::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

AudioComponentPtr GameObjectBreakableRock::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectBreakableRock::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}

void GameObjectBreakableRock::setRenderComponentEntityBroken(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityBroken=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectBreakableRock::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectBreakableRock::getRenderComponentEntityBroken() const
{
	return mRenderComponentEntityBroken;
}

void GameObjectBreakableRock::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectBreakableRock::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectBreakableRock::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectBreakableRock::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectBreakableRock::setRenderComponentParticleSystemBreak(RenderComponentParticleSystemPtr pRenderComponentParticleSystemBreak)
{
	mRenderComponentParticleSystemBreak = pRenderComponentParticleSystemBreak;
}

RenderComponentParticleSystemPtr GameObjectBreakableRock::getRenderComponentParticleSystemBreak() const
{
	return mRenderComponentParticleSystemBreak;
}

void GameObjectBreakableRock::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectBreakableRock::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectBreakableRock::breakRock()
{
	if(!mBroken)
	{
		if(getName().compare("breakable-rock#rock_big")==0)
		{
			getGameWorldManager()->addExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK);
		}
		mBroken=true;
		mRenderComponentEntity->setVisible(false);
		mRenderComponentEntityBroken->setVisible(true);
		mRenderComponentPositional->setPosition(mRenderComponentPositional->getPosition()+BROKEN_DISPLACEMENT);
		if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}
		mAudioComponent->playSound("explosion");
		getRenderComponentParticleSystemBreak()->start(); 

	}
}

void GameObjectBreakableRock::changeWorldFinished(int newWorld)
{
	if (!isEnabled() || mBroken) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				getEntityComponent()->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				getEntityComponent()->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				getEntityComponent()->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				getEntityComponent()->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}		
			break;
		default:
			break;
	}
}

void GameObjectBreakableRock::setVisible(bool visible)
{

	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			getEntityComponent()->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			getEntityComponent()->setVisible(visible);
		}
		break;
	default:
		break;
	}


}

void GameObjectBreakableRock::changeWorldStarted(int newWorld)
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

void GameObjectBreakableRock::changeToWorld(int newWorld, double perc)
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

void GameObjectBreakableRock::reset()
{
	GameObject::reset();
	if(getName().compare("breakable-rock#rock_big")!=0 || !getGameWorldManager()->hasExecutedLevelEvent(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK))
	{
		mBroken=false;
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntityBroken->setVisible(false);
	}

}

bool GameObjectBreakableRock::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectBreakableRock::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectBreakableRock::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectBreakableRock::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}

/// Set logic component
void GameObjectBreakableRock::setLogicComponentProp(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectBreakableRock::getLogicComponentProp()
{
	return mLogicComponent;
}

void GameObjectBreakableRock::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectBreakableRock::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectBreakableRock::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectBreakableRock::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectBreakableRock::getEntityComponent() const
{
	return (mBroken)?mRenderComponentEntityBroken:mRenderComponentEntity;
}
bool GameObjectBreakableRock::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectBreakableRock::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectBreakableRockParameters::TGameObjectBreakableRockParameters() : TGameObjectParameters()
{

}

TGameObjectBreakableRockParameters::~TGameObjectBreakableRockParameters()
{

}