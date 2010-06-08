#include "OUAN_Precompiled.h"

#include "GameObjectTriggerCapsule.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTriggerCapsule::GameObjectTriggerCapsule(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIGGERCAPSULE)
{

}

GameObjectTriggerCapsule::~GameObjectTriggerCapsule()
{

}

void GameObjectTriggerCapsule::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTriggerCapsule::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTriggerCapsule::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTriggerCapsule::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTriggerCapsule::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectTriggerCapsule::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTriggerCapsule::setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule)
{
	mPhysicsComponentVolumeCapsule=pPhysicsComponentVolumeCapsule;
}

PhysicsComponentVolumeCapsulePtr GameObjectTriggerCapsule::getPhysicsComponentVolumeCapsule() const
{
	return mPhysicsComponentVolumeCapsule;
}

void GameObjectTriggerCapsule::changeVisibility()
{
	if (mPhysicsComponentVolumeCapsule->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectTriggerCapsule::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams())
			{
				if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->create();
				}
			}
			else
			{
				if (mPhysicsComponentVolumeCapsule.get() && mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->create();
				}
			}
			else
			{
				if (mPhysicsComponentVolumeCapsule.get() && mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->destroy();
				}
			}
			break;
		default:
			break;
	}
}

void GameObjectTriggerCapsule::changeWorldStarted(int newWorld)
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

void GameObjectTriggerCapsule::changeToWorld(int newWorld, double perc)
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

void GameObjectTriggerCapsule::reset()
{
	GameObject::reset();
}

bool GameObjectTriggerCapsule::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTriggerCapsule::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTriggerCapsule::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTriggerCapsule::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeCapsule();
}


/// Set logic component
void GameObjectTriggerCapsule::setLogicComponent(LogicComponentTriggerPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentTriggerPtr GameObjectTriggerCapsule::getLogicComponent()
{
	return mLogicComponent;
}

void GameObjectTriggerCapsule::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTriggerCapsule::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTriggerCapsule::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTriggerCapsule::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
//-------------------------------------------------------------------------------------------
TGameObjectTriggerCapsuleParameters::TGameObjectTriggerCapsuleParameters() : TGameObjectParameters()
{

}

TGameObjectTriggerCapsuleParameters::~TGameObjectTriggerCapsuleParameters()
{

}