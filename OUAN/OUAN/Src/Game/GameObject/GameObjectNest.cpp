#include "OUAN_Precompiled.h"

#include "GameObjectNest.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Utils/Utils.h"
#include <numeric>
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

double gameObjectSum(double d1, GameObjectPtr obj)
{
	return d1 + obj->getSpawnProbability();
}

GameObjectNest::GameObjectNest(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_NEST)
,mEggHatched(false)
,mChildrenTotalWeight(0.0)
{

}

GameObjectNest::~GameObjectNest()
{

}

void GameObjectNest::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectNest::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectNest::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectNest::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectNest::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectNest::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectNest::setRenderComponentParticleSystemBreak(RenderComponentParticleSystemPtr pRenderComponentParticleSystemBreak)
{
	mRenderComponentParticleSystemBreak = pRenderComponentParticleSystemBreak;
}

RenderComponentParticleSystemPtr GameObjectNest::getRenderComponentParticleSystemBreak() const
{
	return mRenderComponentParticleSystemBreak;
}

void GameObjectNest::setRenderComponentParticleSystemJump(RenderComponentParticleSystemPtr pRenderComponentParticleSystemJump)
{
	mRenderComponentParticleSystemJump = pRenderComponentParticleSystemJump;
}

RenderComponentParticleSystemPtr GameObjectNest::getRenderComponentParticleSystemJump() const
{
	return mRenderComponentParticleSystemJump;
}

void GameObjectNest::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr physicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=physicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectNest::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

AudioComponentPtr GameObjectNest::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectNest::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


void GameObjectNest::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->create();
		}
		break;
	case NIGHTMARES:		
		setNightmaresRender();
		if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->destroy();
		}
		break;
	default:
		break;
	}
}

void GameObjectNest::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		if (mLogicComponent->existsInDreams())
			mRenderComponentEntity->setVisible(true);
		break;
	case NIGHTMARES:
		if (mLogicComponent->existsInNightmares())
			mRenderComponentEntity->setVisible(true);
		break;
	default:
		break;
	}
}

void GameObjectNest::changeToWorld(int newWorld, double perc)
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

void GameObjectNest::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectNest::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
{
	double fraction=0.25f;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor;
		}
		else if(mLogicComponent->existsInNightmares())
		{
			mChangeWorldDelay=(fraction+intersection)*totalTime*delay_factor+(2*fraction-intersection)*totalTime;
		}
		break;
	default:
		break;
	}	
}

void GameObjectNest::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(NEST_STATE_IDLE));
	mEggHatched=false;
	mRenderComponentEntity->changeAnimation(NEST_ANIM_IDLE);
	mRenderComponentEntity->setVisible((mWorld==DREAMS && mLogicComponent->existsInDreams()) ||
		(mWorld==NIGHTMARES && mLogicComponent->existsInNightmares()));
}

bool GameObjectNest::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectNest::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectNest::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectNest::getPhysicsComponent() const
{
	return mPhysicsComponentSimpleBox;
}

/// Set logic component
void GameObjectNest::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectNest::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectNest::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectNest::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectNest::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectNest::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectNest::getEntityComponent() const
{
	return mRenderComponentEntity;
}

void GameObjectNest::processAnimationEnded(const std::string& animationName)
{
	if (animationName.compare(NEST_ANIM_HATCH)==0)
	{
		spawnChild();
		mEggHatched=true;
		mAudioComponent->playSound(NEST_SOUND_BREAK);
		mRenderComponentParticleSystemBreak->start();
		//disable();
	}
}
void GameObjectNest::disable()
{
	GameObject::disable();
	mRenderComponentEntity->setVisible(false);

	if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
	{
		mPhysicsComponentSimpleBox->destroy();
	}

}
void GameObjectNest::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled() && mWorld==DREAMS)
	{	
		if (isFirstUpdate())
		{
			for (std::vector<GameObjectPtr>::iterator it=mChildren.begin();it!=mChildren.end();++it)
			{
				(*it)->disable();
			}
		}
		else
		{
			LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

			int currentState=mLogicComponent->getState();

			if (currentState==logicSS->getGlobalInt(NEST_STATE_IDLE))
			{
				if (mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
				{
					mLogicComponent->setStateChanged(false);
					mRenderComponentEntity->changeAnimation(NEST_ANIM_IDLE);					
					for (std::vector<GameObjectPtr>::iterator it=mChildren.begin();it!=mChildren.end();++it)
					{
						GameObjectPtr obj=*it;
						if (!obj->isEnabled())
						{
							obj->reset();
							obj->disable();
						}
					}
				}
			}
			else if (currentState==logicSS->getGlobalInt(NEST_STATE_SHAKING) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{	
				mRenderComponentEntity->changeAnimation(NEST_ANIM_SHAKE);	
				mAudioComponent->playSound(NEST_SOUND_TOC_TOC);
				mRenderComponentParticleSystemJump->start();
			}
			else if (currentState==logicSS->getGlobalInt(NEST_STATE_HATCHING) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{	
				mRenderComponentEntity->changeAnimation(NEST_ANIM_HATCH);	
				//mRenderComponentParticleSystemBreak->start();
			}
			if (mRenderComponentEntity.get() && !mEggHatched)
			{
				mRenderComponentEntity->update(elapsedSeconds);
			}
		}
	}
}
void GameObjectNest::setDreamsRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setDreamsMaterials();
	}
	else
	{
		mRenderComponentEntity->setVisible(false);
	}
}

void GameObjectNest::setNightmaresRender()
{
	if (!isEnabled()) return;
	if(mLogicComponent->existsInDreams())
	{
		mRenderComponentEntity->setVisible(false);
	}
	else
	{
		mRenderComponentEntity->setVisible(true);
		mRenderComponentEntity->setNightmaresMaterials();
	}
}

void GameObjectNest::setChangeWorldFactor(double factor)
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setChangeWorldFactor(factor);
}

void GameObjectNest::setChangeWorldRender()
{
	if (!isEnabled()) return;
	mRenderComponentEntity->setVisible(true);
	mRenderComponentEntity->setChangeWorldMaterials();
}

std::vector<GameObjectPtr>* GameObjectNest::getChildren()
{
	return &mChildren;
}
void GameObjectNest::setChildren(const std::vector<GameObjectPtr>& children)
{
	mChildren=children;
	mChildrenTotalWeight = std::accumulate(children.begin(),children.end(),0.0,gameObjectSum);
}
void GameObjectNest::addChild(GameObjectPtr child)
{
	mChildren.push_back(child);
	mChildrenTotalWeight+=child->getSpawnProbability();
}
void GameObjectNest::spawnChild()
{
	//decide which child to enable
	double dice=Utils::Random::getInstance()->getRandomDouble();
	std::vector<GameObjectPtr>::iterator it;
	for (it=mChildren.begin();it!=mChildren.end();++it)
	{
		if (dice<(*it)->getSpawnProbability())
		{
			(*it)->reset();
			(*it)->enable();

			if((*it)->getType().compare(GAME_OBJECT_TYPE_BOSS)==0)
			{
				mAudioComponent->playSound(NEST_SOUND_BOSS);
			}
			break;
		}
		else 
		{
			dice-=(*it)->getSpawnProbability();
		}
	}
	if (it==mChildren.end())
	{
		mAudioComponent->playSound(NEST_SOUND_NOTHING);
		//displayText("Better luck next time");
	}
}
void GameObjectNest::setVisible(bool visible)
{
	switch(mWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->setVisible(visible);
		}
		break;
	default:
		break;
	}
}
bool GameObjectNest::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectNest::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectNestParameters::TGameObjectNestParameters() : TGameObjectParameters()
{

}

TGameObjectNestParameters::~TGameObjectNestParameters()
{

}