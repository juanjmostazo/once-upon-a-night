#include "OUAN_Precompiled.h"

#include "GameObjectActionTrigger.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Logic/LogicComponent/LogicComponentActionTrigger.h"

using namespace OUAN;

GameObjectActionTrigger::GameObjectActionTrigger(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIGGER_ACTION)
{

}

GameObjectActionTrigger::~GameObjectActionTrigger()
{

}

void GameObjectActionTrigger::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectActionTrigger::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectActionTrigger::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectActionTrigger::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectActionTrigger::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectActionTrigger::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectActionTrigger::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectActionTrigger::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectActionTrigger::changeVisibility()
{
	if (mPhysicsComponentVolumeBox->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectActionTrigger::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:

		if(mLogicComponent->existsInDreams())
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

		if(mLogicComponent->existsInNightmares())
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

void GameObjectActionTrigger::changeWorldStarted(int newWorld)
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

void GameObjectActionTrigger::changeToWorld(int newWorld, double perc)
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

void GameObjectActionTrigger::reset()
{
	GameObject::reset();
}

bool GameObjectActionTrigger::hasPositionalComponent() const
{
	return true;
}

/// Set logic component
void GameObjectActionTrigger::setLogicComponentActionTrigger(LogicComponentActionTriggerPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentActionTriggerPtr GameObjectActionTrigger::getLogicComponentActionTrigger()
{
	return mLogicComponent;
}


RenderComponentPositionalPtr GameObjectActionTrigger::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectActionTrigger::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectActionTrigger::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


void GameObjectActionTrigger::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectActionTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectActionTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectActionTrigger::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
//-------------------------------------------------------------------------------------------

TGameObjectActionTriggerParameters::TGameObjectActionTriggerParameters() : TGameObjectParameters()
{

}

TGameObjectActionTriggerParameters::~TGameObjectActionTriggerParameters()
{

}