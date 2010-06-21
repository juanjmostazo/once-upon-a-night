#include "OUAN_Precompiled.h"

#include "GameObjectTriggerCamera.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"
#include "../../Logic/LogicComponent/LogicComponentTriggerCamera.h"

using namespace OUAN;

GameObjectTriggerCamera::GameObjectTriggerCamera(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIGGER_CAMERA)
{

}

GameObjectTriggerCamera::~GameObjectTriggerCamera()
{

}

void GameObjectTriggerCamera::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTriggerCamera::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTriggerCamera::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTriggerCamera::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTriggerCamera::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectTriggerCamera::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTriggerCamera::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectTriggerCamera::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectTriggerCamera::changeVisibility()
{
	if (mPhysicsComponentVolumeBox->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectTriggerCamera::changeWorldFinished(int newWorld)
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

void GameObjectTriggerCamera::changeWorldStarted(int newWorld)
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

void GameObjectTriggerCamera::changeToWorld(int newWorld, double perc)
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

void GameObjectTriggerCamera::reset()
{
	GameObject::reset();
}

bool GameObjectTriggerCamera::hasPositionalComponent() const
{
	return true;
}

/// Set logic component
void GameObjectTriggerCamera::setLogicComponentTriggerCamera(LogicComponentTriggerCameraPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentTriggerCameraPtr GameObjectTriggerCamera::getLogicComponentTriggerCamera()
{
	return mLogicComponent;
}


RenderComponentPositionalPtr GameObjectTriggerCamera::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTriggerCamera::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTriggerCamera::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


void GameObjectTriggerCamera::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTriggerCamera::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTriggerCamera::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTriggerCamera::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
//-------------------------------------------------------------------------------------------

TGameObjectTriggerCameraParameters::TGameObjectTriggerCameraParameters() : TGameObjectParameters()
{

}

TGameObjectTriggerCameraParameters::~TGameObjectTriggerCameraParameters()
{

}