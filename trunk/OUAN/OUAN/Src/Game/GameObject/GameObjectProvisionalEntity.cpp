#include "GameObjectProvisionalEntity.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectProvisionalEntity::GameObjectProvisionalEntity(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PROVISIONALENTITY)
{

}

GameObjectProvisionalEntity::~GameObjectProvisionalEntity()
{

}

void GameObjectProvisionalEntity::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectProvisionalEntity::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectProvisionalEntity::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectProvisionalEntity::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectProvisionalEntity::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectProvisionalEntity::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectProvisionalEntity::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectProvisionalEntity::getPhysicsComponentSimpleBox() const
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectProvisionalEntity::changeWorldFinished(int world)
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

void GameObjectProvisionalEntity::changeWorldStarted(int world)
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

void GameObjectProvisionalEntity::changeToWorld(int world, double perc)
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

void GameObjectProvisionalEntity::reset()
{
	GameObject::reset();
}

bool GameObjectProvisionalEntity::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectProvisionalEntity::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

/// Set logic component
void GameObjectProvisionalEntity::setLogicComponent(LogicComponentPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentPtr GameObjectProvisionalEntity::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectProvisionalEntity::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectProvisionalEntity::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectProvisionalEntity::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectProvisionalEntity::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
bool GameObjectProvisionalEntity::hasRenderComponentEntity() const
{
	return true;
}
RenderComponentEntityPtr GameObjectProvisionalEntity::getEntityComponent() const
{
	return (mGameWorldManager->getWorld()==DREAMS)?mRenderComponentEntityDreams:mRenderComponentEntityNightmares;
}
//-------------------------------------------------------------------------------------------

TGameObjectProvisionalEntityParameters::TGameObjectProvisionalEntityParameters() : TGameObjectParameters()
{

}

TGameObjectProvisionalEntityParameters::~TGameObjectProvisionalEntityParameters()
{

}