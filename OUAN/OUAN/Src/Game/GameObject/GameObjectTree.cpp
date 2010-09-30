#include "OUAN_Precompiled.h"

#include "GameObjectTree.h"
#include "../GameWorldManager.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../../Utils/Utils.h"

using namespace OUAN;

GameObjectTree::GameObjectTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TREE)
{

}

GameObjectTree::~GameObjectTree()
{

}

void GameObjectTree::setType(int pType)
{
	mType = pType;
}

int GameObjectTree::getType() const
{
	return mType;
}

RenderComponentEntityPtr GameObjectTree::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTree::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectTree::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTree::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTree::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTree::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTree::setRenderComponentParticleSystemStars(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStars)
{
	mRenderComponentParticleSystemStars = pRenderComponentParticleSystemStars;
}

RenderComponentParticleSystemPtr GameObjectTree::getRenderComponentParticleSystemStars() const
{
	return mRenderComponentParticleSystemStars;
}

void GameObjectTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectTree::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectTree::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_UP);
				
				if (mType == 9)
				{
					mRenderComponentParticleSystemStars->stop();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_DOWN);
				
				if (mType == 9)
				{
					mRenderComponentParticleSystemStars->stop();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}

				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_UP);	

				if (mType == 9)
				{
					recalculateNextParticlesCountDown();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_DOWN);

				if (mType == 9)
				{
					mRenderComponentParticleSystemStars->stop();
				}
			}
			break;
		default:
			break;
	}
}

void GameObjectTree::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setVisible(true);

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TREE_ANIM_UP);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TREE_ANIM_DOWN);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TREE_ANIM_DOWN);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{	
			mRenderComponentEntity->changeAnimation(TREE_ANIM_UP);
		}
		break;
	default:
		break;
	}
}

void GameObjectTree::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;
	
	std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
	double currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();
	if(!mRenderComponentEntity->getCurrentAnimation()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
			else if(currentAnimName.compare(TREE_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
			else if(currentAnimName.compare(TREE_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
			else if(currentAnimName.compare(TREE_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TREE_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
			else if(currentAnimName.compare(TREE_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
		}
		break;
	default:
		break;
	}
}

void GameObjectTree::reset()
{
	GameObject::reset();

	mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_UP);
	recalculateNextParticlesCountDown();
}

void GameObjectTree::recalculateNextParticlesCountDown()
{
	mNextParticlesCountDown=Utils::Random::getInstance()->getRandomDouble(0,TREE_MAX_PARTICLES_ELAPSED_TIME);
}

bool GameObjectTree::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTree::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTree::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTree::getPhysicsComponent() const
{
	return getPhysicsComponentSimpleBox();
}


/// Set logic component
void GameObjectTree::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTree::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTree::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectTree::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTree::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTree::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	mRenderComponentEntity->update(elapsedSeconds);

	if(isEnabled() && ((mLogicComponent->existsInDreams() && mWorld==DREAMS) || (mLogicComponent->existsInNightmares() && mWorld==NIGHTMARES)))
	{
		if(mType == 9)
		{
			mNextParticlesCountDown-=elapsedSeconds;

			if(mNextParticlesCountDown<-TREE_PARTICLES_ACTIVE_TIME)
			{
				recalculateNextParticlesCountDown();
				mRenderComponentParticleSystemStars->stop();
			}
			else if(mNextParticlesCountDown<0 && !mRenderComponentParticleSystemStars->hasStarted())
			{
				mRenderComponentParticleSystemStars->start();
			}
		}
	}
}

bool GameObjectTree::hasRenderComponentEntity() const
{
	return true;
}

void GameObjectTree::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.09f;
}

void GameObjectTree::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

RenderComponentEntityPtr GameObjectTree::getEntityComponent() const
{
	return mRenderComponentEntity;
}
void GameObjectTree::setVisible(bool visible)
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
bool GameObjectTree::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTree::getLogicComponent() const
{
	return mLogicComponent;
}
TGameObjectTreeParameters::TGameObjectTreeParameters() : TGameObjectParameters()
{

}

TGameObjectTreeParameters::~TGameObjectTreeParameters()
{

}