#include "GameObjectHeart.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectHeart::GameObjectHeart(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_HEART)
{

}

GameObjectHeart::~GameObjectHeart()
{

}

RenderComponentEntityPtr GameObjectHeart::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectHeart::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectHeart::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectHeart::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectHeart::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectHeart::changeWorld(int world)
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

TGameObjectHeartParameters::TGameObjectHeartParameters() : TGameObjectParameters()
{

}

TGameObjectHeartParameters::~TGameObjectHeartParameters()
{

}