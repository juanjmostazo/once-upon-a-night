#include "GameObjectTriggerBox.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectTriggerBox::GameObjectTriggerBox(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TRIGGERBOX)
{

}

GameObjectTriggerBox::~GameObjectTriggerBox()
{

}

void GameObjectTriggerBox::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTriggerBox::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTriggerBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTriggerBox::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTriggerBox::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectTriggerBox::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTriggerBox::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectTriggerBox::getPhysicsComponentVolumeBox() const
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectTriggerBox::changeVisibility()
{
	if (mPhysicsComponentVolumeBox->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectTriggerBox::changeWorld(int world)
{
	if (!isEnabled()) return;

	mRenderComponentEntity->setVisible(false);

	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}
		return;
	}
	else
	{
		switch(world)
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
}

void GameObjectTriggerBox::reset()
{
	GameObject::reset();
}

bool GameObjectTriggerBox::hasPositionalComponent() const
{
	return true;
}

/// Set logic component
void GameObjectTriggerBox::setLogicComponent(LogicComponentTriggerPtr logicComponent)
{
	mLogicComponent=logicComponent;
}

/// return logic component
LogicComponentTriggerPtr GameObjectTriggerBox::getLogicComponent()
{
	return mLogicComponent;
}


RenderComponentPositionalPtr GameObjectTriggerBox::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

bool GameObjectTriggerBox::hasPhysicsComponent() const
{
	return true;
}
PhysicsComponentPtr GameObjectTriggerBox::getPhysicsComponent() const
{
	return getPhysicsComponentVolumeBox();
}


void GameObjectTriggerBox::processCollision(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processCollision(pGameObject);
	}
}

void GameObjectTriggerBox::processEnterTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processEnterTrigger(pGameObject);
	}
}

void GameObjectTriggerBox::processExitTrigger(GameObjectPtr pGameObject)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->processExitTrigger(pGameObject);
	}
}

void GameObjectTriggerBox::updateLogic(double elapsedSeconds)
{
	if (mLogicComponent.get())
	{
		mLogicComponent->update(elapsedSeconds);
	}
}
//-------------------------------------------------------------------------------------------

TGameObjectTriggerBoxParameters::TGameObjectTriggerBoxParameters() : TGameObjectParameters()
{

}

TGameObjectTriggerBoxParameters::~TGameObjectTriggerBoxParameters()
{

}