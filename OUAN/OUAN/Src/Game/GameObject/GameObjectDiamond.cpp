#include "GameObjectDiamond.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDiamond::GameObjectDiamond(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMOND)
{

}

GameObjectDiamond::~GameObjectDiamond()
{

}

RenderComponentEntityPtr GameObjectDiamond::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectDiamond::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectDiamond::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDiamond::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDiamond::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDiamond::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDiamond::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectDiamond::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectDiamond::changeWorld(int world)
{
	if (!isEnabled()) return;

	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentVolumeBox.get() && !mPhysicsComponentVolumeBox->isInUse())
		{
			mPhysicsComponentVolumeBox->create();
		}

		mRenderComponentEntity->setVisible(true);
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

void GameObjectDiamond::reset()
{
	GameObject::reset();
}

bool GameObjectDiamond::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDiamond::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectDiamondParameters::TGameObjectDiamondParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondParameters::~TGameObjectDiamondParameters()
{

}