#include "OUAN_Precompiled.h"

#include "GameObjectDiamondTree.h"
#include "GameObjectDiamond.h"
#include "../GameWorldManager.h"
#include "../../Logic/LogicSubsystem.h"
#include "../../Audio/AudioComponent/AudioComponent.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

GameObjectDiamondTree::GameObjectDiamondTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMONDTREE)
{

}

GameObjectDiamondTree::~GameObjectDiamondTree()
{

}

void GameObjectDiamondTree::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

AudioComponentPtr GameObjectDiamondTree::getAudioComponent() const
{
	return mAudioComponent;
}

void GameObjectDiamondTree::setAudioComponent(AudioComponentPtr audioComponent)
{
	mAudioComponent=audioComponent;
}


RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectDiamondTree::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDiamondTree::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDiamondTree::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDiamondTree::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDiamondTree::setRenderComponentParticleSystemStars(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStars)
{
	mRenderComponentParticleSystemStars = pRenderComponentParticleSystemStars;
}

RenderComponentParticleSystemPtr GameObjectDiamondTree::getRenderComponentParticleSystemStars() const
{
	return mRenderComponentParticleSystemStars;
}

void GameObjectDiamondTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr physicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=physicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDiamondTree::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDiamondTree::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			setDreamsRender();
			if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentParticleSystemStars->start();
				mRenderComponentEntity->setVisible(true);

				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}

				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();
				
				//mRenderComponentEntityDreams->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_IDLE_UP:TREE_ANIM_IDLE_UP);
			}
			else if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentParticleSystemStars->stop();
				mRenderComponentEntity->setVisible(false);

				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				//mRenderComponentEntityNightmares->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_IDLE_DOWN:TREE_ANIM_IDLE_DOWN);
			}		
			break;
		case NIGHTMARES:
			setNightmaresRender();
			if(!mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentParticleSystemStars->start();
				mRenderComponentEntity->setVisible(true);

				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}

				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				//mRenderComponentEntityNightmares->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_IDLE_UP:TREE_ANIM_IDLE_UP);	
			}
			else if(mLogicComponent->existsInDreams() && !mLogicComponent->existsInNightmares())
			{
				mRenderComponentParticleSystemStars->stop();
				mRenderComponentEntity->setVisible(false);

				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				//mRenderComponentEntityDreams->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_IDLE_DOWN:TREE_ANIM_IDLE_DOWN);	
			}
			break;
		default:
			break;
	}
}

void GameObjectDiamondTree::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	Logger::getInstance()->log("[changeWorldStarted] CHANGING "+getName());

	mRenderComponentEntity->setVisible(true);
	setChangeWorldRender();

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

			//mRenderComponentEntityDreams->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_UP:TREE_ANIM_UP);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{

			std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

			//mRenderComponentEntity->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_DOWN:TREE_ANIM_DOWN);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

			//mRenderComponentEntity->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_DOWN:TREE_ANIM_DOWN);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{	
			std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();
			//mRenderComponentEntity->changeAnimation((nodeName.find("tree8")!=std::string::npos)?TREE8_ANIM_UP:TREE_ANIM_UP);
		}
		break;
	default:
		break;
	}
}

void GameObjectDiamondTree::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;
	
	//std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
	//double currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();
	//if(!mRenderComponentEntity->getCurrentAnimation()) return;

	//switch(newWorld)
	//{
	//case DREAMS:
	//	if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
	//	{
	//		if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
	//		}
	//		else if(currentAnimName.compare(TREE_ANIM_UP)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
	//		}
	//	}
	//	else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
	//	{
	//		if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
	//		}
	//		else if(currentAnimName.compare(TREE_ANIM_UP)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
	//		}
	//	}
	//	break;
	//case NIGHTMARES:
	//	if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
	//	{
	//		if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
	//		}
	//		else if(currentAnimName.compare(TREE_ANIM_UP)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
	//		}
	//	}
	//	else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
	//	{
	//		if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
	//		}
	//		else if(currentAnimName.compare(TREE_ANIM_UP)==0)
	//		{
	//			mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}
}

void GameObjectDiamondTree::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
}

void GameObjectDiamondTree::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

void GameObjectDiamondTree::reset()
{
	GameObject::reset();

	mLogicComponent->setState(mGameWorldManager->getParent()->getLogicSubsystem()->getGlobalInt(DT_STATE_IDLE));

	mLogicComponent->setReload(true);

	if (mLogicComponent->existsInNightmares())
	{
		mRenderComponentEntity->changeAnimation(DT_ANIM_IDLE);		
		mRenderComponentEntity->setVisible(mWorld==NIGHTMARES);
	}
	else if (mLogicComponent->existsInDreams())
	{
		mRenderComponentEntity->changeAnimation(DT_ANIM_IDLE);
		mRenderComponentEntity->setVisible(mWorld==DREAMS);
	}
}

bool GameObjectDiamondTree::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDiamondTree::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectDiamondTree::hasPhysicsComponent() const
{
	return true;
}

PhysicsComponentPtr GameObjectDiamondTree::getPhysicsComponent() const
{
	return mPhysicsComponentSimpleBox;
}

/// Set logic component
void GameObjectDiamondTree::setLogicComponent(LogicComponentPropPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPropPtr GameObjectDiamondTree::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectDiamondTree::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectDiamondTree::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectDiamondTree::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectDiamondTree::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDiamondTree::getEntityComponent() const
{
	return mRenderComponentEntity;
}
void GameObjectDiamondTree::processAnimationEnded(const std::string& animationName)
{

}
void GameObjectDiamondTree::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);

	if (isEnabled())
	{	
		if (isFirstUpdate() && mLogicComponent->existsInDreams())
		{
			mRenderComponentParticleSystemStars->start();
		}

		LogicSubsystemPtr logicSS = mGameWorldManager->getParent()->getLogicSubsystem();

		int currentState=mLogicComponent->getState();
		
		if (currentState==logicSS->getGlobalInt(DT_STATE_IDLE))
		{
			if (mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
			{
				mLogicComponent->setHasTakenHit(false);
				mLogicComponent->setReload(true);
				mRenderComponentEntity->changeAnimation(DT_ANIM_IDLE);
			}
		}
		else if (currentState==logicSS->getGlobalInt(DT_STATE_HIT) && mRenderComponentEntity.get())
		{		
			if(mLogicComponent->isStateChanged())
			{
				mRenderComponentEntity->changeAnimation(DT_ANIM_HIT);			

				if(mLogicComponent->isReload())
				{
					mLogicComponent->setTimeSpent(0);
					mLogicComponent->setReload(false);
				}

				mTotalHitTime=0;

				mAudioComponent->playSound(DT_SOUND_TREE);
				mLogicComponent->setRecovered(false);
				//play sound and particles

				mRenderComponentEntity->setAnimationPosition(0);
			}
			else
			{
				mTotalHitTime+=elapsedSeconds;
				std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
				double currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();

				if(mTotalHitTime>DT_ANIMATION_TIME)
				{
					mRenderComponentEntity->setAnimationPosition(1);
					mLogicComponent->setRecovered(true);
				}
				else
				{
					mRenderComponentEntity->setAnimationPosition(mTotalHitTime/DT_ANIMATION_TIME);
				}
			}
		}
		else if (currentState==logicSS->getGlobalInt(DT_STATE_MAY_HIT) && mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
		{					
			mRenderComponentEntity->changeAnimation(DT_ANIM_IDLE);
			mLogicComponent->setHasTakenHit(false);
			mAudioComponent->playSound(DT_SOUND_DIAMOND);
			mGameWorldManager->increaseOnyDiamonds(1);
			mRenderComponentParticleSystemStars->start();
		}
		else if (currentState==logicSS->getGlobalInt(DT_STATE_DEPLETED) &&
			mRenderComponentEntity.get() && mLogicComponent->isStateChanged())
		{
			mRenderComponentParticleSystemStars->stop();

			//TODO: Replace with depletion animation when it is done
			//TODO: Add particles
			mRenderComponentEntity->changeAnimation(DT_ANIM_IDLE);
			mLogicComponent->setHasTakenHit(false);
		}
		//Last, update the entity
		if (mRenderComponentEntity.get())
		{
			mRenderComponentEntity->update(elapsedSeconds);
		}
	}
}

void GameObjectDiamondTree::updatePhysicsComponents(double elapsedSeconds)
{
	GameObject::updatePhysicsComponents(elapsedSeconds);
	//mPhysicsComponentVolumeBox->update(elapsedSeconds);
}

void GameObjectDiamondTree::setVisible(bool visible)
{	switch(mWorld)
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
bool GameObjectDiamondTree::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectDiamondTree::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectDiamondTreeParameters::TGameObjectDiamondTreeParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondTreeParameters::~TGameObjectDiamondTreeParameters()
{

}