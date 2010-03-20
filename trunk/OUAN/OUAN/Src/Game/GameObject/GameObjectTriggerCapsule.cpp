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

RenderComponentPositionalPtr GameObjectTriggerCapsule::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
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

PhysicsComponentVolumeCapsulePtr GameObjectTriggerCapsule::getPhysicsComponentVolumeCapsule()
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

void GameObjectTriggerCapsule::changeWorld(int world)
{
	mRenderComponentEntity->setVisible(false);

	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
		{
			mPhysicsComponentVolumeCapsule->create();
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
			if(mLogicComponentWorldExistance->getExistsInNightmares())
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
}
//-------------------------------------------------------------------------------------------
TGameObjectTriggerCapsuleParameters::TGameObjectTriggerCapsuleParameters() : TGameObjectParameters()
{

}

TGameObjectTriggerCapsuleParameters::~TGameObjectTriggerCapsuleParameters()
{

}