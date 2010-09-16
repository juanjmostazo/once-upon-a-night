#include "OUAN_Precompiled.h"

#include "GameObjectTreeComplex.h"
#include "../GameWorldManager.h"
#include "../../Graphics/RenderComponent/RenderComponentParticleSystem.h"

using namespace OUAN;

GameObjectTreeComplex::GameObjectTreeComplex(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TREE_COMPLEX)
{

}

GameObjectTreeComplex::~GameObjectTreeComplex()
{

}

void GameObjectTreeComplex::setType(int pType)
{
	mType = pType;
}

int GameObjectTreeComplex::getType() const
{
	return mType;
}

RenderComponentEntityPtr GameObjectTreeComplex::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTreeComplex::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectTreeComplex::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTreeComplex::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTreeComplex::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTreeComplex::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTreeComplex::setRenderComponentParticleSystemStars(RenderComponentParticleSystemPtr pRenderComponentParticleSystemStars)
{
	mRenderComponentParticleSystemStars = pRenderComponentParticleSystemStars;
}

RenderComponentParticleSystemPtr GameObjectTreeComplex::getRenderComponentParticleSystemStars() const
{
	return mRenderComponentParticleSystemStars;
}

void GameObjectTreeComplex::setPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	mPhysicsComponentComplexConvex=pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexConvexPtr GameObjectTreeComplex::getPhysicsComponentComplexConvex() const
{
	return mPhysicsComponentComplexConvex;
}

void GameObjectTreeComplex::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}
				mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_IDLE_UP);
				
				if (mType == 9)
				{
					mRenderComponentParticleSystemStars->stop();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_IDLE_DOWN);
				
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
				if (mPhysicsComponentComplexConvex.get() && !mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->create();
				}

				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_IDLE_UP);	

				if (mType == 9)
				{
					mRenderComponentParticleSystemStars->start();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentComplexConvex.get() && mPhysicsComponentComplexConvex->isInUse())
				{
					mPhysicsComponentComplexConvex->destroy();
				}
				std::string nodeName=getRenderComponentPositional()->getSceneNode()->getName();

				mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_IDLE_DOWN);

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

void GameObjectTreeComplex::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setVisible(true);

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_UP);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_DOWN);
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_DOWN);
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{	
			mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_UP);
		}
		break;
	default:
		break;
	}
}

void GameObjectTreeComplex::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;
	
	std::string currentAnimName=mRenderComponentEntity->getCurrentAnimationName();
	float currentAnimLen=mRenderComponentEntity->getCurrentAnimationLength();
	if(!mRenderComponentEntity->getCurrentAnimation()) return;

	switch(newWorld)
	{
	case DREAMS:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TreeComplex_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
			else if(currentAnimName.compare(TreeComplex_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TreeComplex_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
			else if(currentAnimName.compare(TreeComplex_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
		}
		break;
	case NIGHTMARES:
		if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TreeComplex_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
			else if(currentAnimName.compare(TreeComplex_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
		}
		else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
		{
			if(currentAnimName.compare(TreeComplex_ANIM_DOWN)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(1-perc));
			}
			else if(currentAnimName.compare(TreeComplex_ANIM_UP)==0)
			{
				mRenderComponentEntity->setAnimationPosition(currentAnimLen*(perc));
			}
		}
		break;
	default:
		break;
	}
}

void GameObjectTreeComplex::reset()
{
	GameObject::reset();

	mRenderComponentEntity->changeAnimation(TreeComplex_ANIM_IDLE_UP);
}

bool GameObjectTreeComplex::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTreeComplex::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTreeComplex::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTreeComplex::getPhysicsComponent() const
{
	return getPhysicsComponentComplexConvex();
}


/// Set logic component
void GameObjectTreeComplex::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectTreeComplex::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTreeComplex::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectTreeComplex::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTreeComplex::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTreeComplex::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	mRenderComponentEntity->update(elapsedSeconds);
}

bool GameObjectTreeComplex::hasRenderComponentEntity() const
{
	return true;
}

void GameObjectTreeComplex::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.09f;
}

void GameObjectTreeComplex::calculateChangeWorldDelay(double totalElapsedTime,double totalTime,int newWorld,double delay_factor,double intersection)
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

RenderComponentEntityPtr GameObjectTreeComplex::getEntityComponent() const
{
	return mRenderComponentEntity;
}
void GameObjectTreeComplex::setVisible(bool visible)
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
bool GameObjectTreeComplex::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectTreeComplex::getLogicComponentInstance() const
{
	return mLogicComponent;
}
TGameObjectTreeComplexParameters::TGameObjectTreeComplexParameters() : TGameObjectParameters()
{

}

TGameObjectTreeComplexParameters::~TGameObjectTreeComplexParameters()
{

}