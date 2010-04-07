#include "GameObjectItem1UP.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectItem1UP::GameObjectItem1UP(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_ITEM_1UP)
{

}

GameObjectItem1UP::~GameObjectItem1UP()
{

}

RenderComponentEntityPtr GameObjectItem1UP::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectItem1UP::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectItem1UP::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectItem1UP::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectItem1UP::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectItem1UP::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectItem1UP::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectItem1UP::changeWorld(int world)
{
	if (!isEnabled()) return;

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
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeBox.get() && mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
				{
					mPhysicsComponentVolumeBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
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

void GameObjectItem1UP::reset()
{
	GameObject::reset();
}

bool GameObjectItem1UP::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectItem1UP::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectItem1UPParameters::TGameObjectItem1UPParameters() : TGameObjectParameters()
{

}

TGameObjectItem1UPParameters::~TGameObjectItem1UPParameters()
{

}