#include "GameObjectVolumeBox.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectVolumeBox::GameObjectVolumeBox(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeBox::~GameObjectVolumeBox()
{

}

void GameObjectVolumeBox::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeBox::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeBox::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeBox::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeBox::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectVolumeBox::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectVolumeBox::changeVisibility()
{
	if (mPhysicsComponentVolumeBox->isInUse())
	{
		mRenderComponentEntity->setVisible(!mRenderComponentEntity->getEntity()->isVisible());
	}
}

void GameObjectVolumeBox::changeWorld(int world)
{
	mRenderComponentEntity->setVisible(false);

	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
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
			
			if(mLogicComponentWorldExistance->getExistsInDreams())
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

			if(mLogicComponentWorldExistance->getExistsInNightmares())
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
//-------------------------------------------------------------------------------------------

TGameObjectVolumeBoxParameters::TGameObjectVolumeBoxParameters() : TGameObjectParameters()
{

}

TGameObjectVolumeBoxParameters::~TGameObjectVolumeBoxParameters()
{

}