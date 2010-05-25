#include "GameObjectTree.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectTree::GameObjectTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TREE)
{

}

GameObjectTree::~GameObjectTree()
{

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
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_DOWN);
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
				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_DOWN);
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
				mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_UP);
			}
			break;
		default:
			break;
	}
}

void GameObjectTree::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		mRenderComponentEntity->changeAnimation(TREE_ANIM_UP);
		break;
	case NIGHTMARES:
		mRenderComponentEntity->changeAnimation(TREE_ANIM_DOWN);
		break;
	default:
		break;
	}
}

void GameObjectTree::changeToWorld(int newWorld, double perc)
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

void GameObjectTree::reset()
{
	GameObject::reset();
	mRenderComponentEntity->changeAnimation(TREE_ANIM_IDLE_UP);
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

void GameObjectTree::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
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

void GameObjectTree::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
void GameObjectTree::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	mRenderComponentEntity->update(elapsedSeconds);
}

bool GameObjectTree::hasRenderComponentEntity() const
{
	return true;
}

void GameObjectTree::calculateChangeWorldTotalTime(double changeWorldTotalTime)
{
	mChangeWorldTotalTime=changeWorldTotalTime*0.25f;
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

TGameObjectTreeParameters::TGameObjectTreeParameters() : TGameObjectParameters()
{

}

TGameObjectTreeParameters::~TGameObjectTreeParameters()
{

}