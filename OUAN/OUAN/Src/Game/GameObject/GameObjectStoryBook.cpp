#include "GameObjectStoryBook.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectStoryBook::GameObjectStoryBook(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_STORYBOOK)
{

}

GameObjectStoryBook::~GameObjectStoryBook()
{

}

RenderComponentEntityPtr GameObjectStoryBook::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectStoryBook::setRenderComponentInitialFromPositional()
{
	mRenderComponentInitial->setPosition(mRenderComponentPositional->getPosition());
	mRenderComponentInitial->setOrientation(mRenderComponentPositional->getOrientation());
}

RenderComponentPositionalPtr GameObjectStoryBook::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectStoryBook::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectStoryBook::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectStoryBook::changeWorld(int world)
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

void GameObjectStoryBook::reset()
{

}

bool GameObjectStoryBook::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectStoryBook::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectStoryBookParameters::TGameObjectStoryBookParameters() : TGameObjectParameters()
{

}

TGameObjectStoryBookParameters::~TGameObjectStoryBookParameters()
{

}