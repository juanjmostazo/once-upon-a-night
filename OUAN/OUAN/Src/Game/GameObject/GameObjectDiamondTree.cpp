#include "GameObjectDiamondTree.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDiamondTree::GameObjectDiamondTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMONDTREE)
{

}

GameObjectDiamondTree::~GameObjectDiamondTree()
{

}

void GameObjectDiamondTree::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDiamondTree::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
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

void GameObjectDiamondTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDiamondTree::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDiamondTree::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
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

void GameObjectDiamondTree::changeWorldStarted(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectDiamondTree::changeToWorld(int world, double perc)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectDiamondTree::reset()
{
	GameObject::reset();
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
	return getPhysicsComponentSimpleBox();
}


/// Set logic component
void GameObjectDiamondTree::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectDiamondTree::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectDiamondTree::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
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

void GameObjectDiamondTree::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectDiamondTree::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectDiamondTree::getEntityComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectDiamondTreeParameters::TGameObjectDiamondTreeParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondTreeParameters::~TGameObjectDiamondTreeParameters()
{

}