#include "OUAN_Precompiled.h"

#include "GameObjectCameraTrigger.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Logic/LogicComponent/LogicComponentCameraTrigger.h"

using namespace OUAN;

GameObjectCameraTrigger::GameObjectCameraTrigger(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIGGER_CAMERA)
{

}

GameObjectCameraTrigger::~GameObjectCameraTrigger()
{

}

void GameObjectCameraTrigger::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectCameraTrigger::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectCameraTrigger::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectCameraTrigger::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectCameraTrigger::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectCameraTrigger::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectCameraTrigger::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectCameraTrigger::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectCameraTrigger::changeVisibility()
{
	if (mPhysicsComponentVolumeBox->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectCameraTrigger::changeWorldFinished(int newWorld)
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

void GameObjectCameraTrigger::changeWorldStarted(int newWorld)
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

void GameObjectCameraTrigger::changeToWorld(int newWorld, double perc)
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

void GameObjectCameraTrigger::reset()
{
	GameObject::reset();
}

bool GameObjectCameraTrigger::hasPositionalComponent() const
{
	return true;
}

/// Set logic component
void GameObjectCameraTrigger::setLogicComponentCameraTrigger(LogicComponentCameraTriggerPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentCameraTriggerPtr GameObjectCameraTrigger::getLogicComponentCameraTrigger()
{
	return mLogicComponent;
}


RenderComponentPositionalPtr GameObjectCameraTrigger::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectCameraTrigger::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectCameraTrigger::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


void GameObjectCameraTrigger::processCollision(GameObjectPtr pGameObject, Ogre::Vector3 pNormal)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject, pNormal);
	}
}

void GameObjectCameraTrigger::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectCameraTrigger::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

bool GameObjectCameraTrigger::hasLogicComponent() const
{
	return true;
}
LogicComponentPtr GameObjectCameraTrigger::getLogicComponent() const
{
	return mLogicComponent;
}
//-------------------------------------------------------------------------------------------

TGameObjectCameraTriggerParameters::TGameObjectCameraTriggerParameters() : TGameObjectParameters()
{

}

TGameObjectCameraTriggerParameters::~TGameObjectCameraTriggerParameters()
{

}