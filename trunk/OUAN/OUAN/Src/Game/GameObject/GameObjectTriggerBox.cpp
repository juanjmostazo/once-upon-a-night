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

RenderComponentPositionalPtr GameObjectTriggerBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
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

PhysicsComponentVolumeBoxPtr GameObjectTriggerBox::getPhysicsComponentVolumeBox()
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
bool GameObjectTriggerBox::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectTriggerBox::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------

TGameObjectTriggerBoxParameters::TGameObjectTriggerBoxParameters() : TGameObjectParameters()
{

}

TGameObjectTriggerBoxParameters::~TGameObjectTriggerBoxParameters()
{

}