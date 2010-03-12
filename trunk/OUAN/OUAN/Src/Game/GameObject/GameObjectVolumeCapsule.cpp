#include "GameObjectVolumeCapsule.h"
#include "../GameWorldManager.h"
#include "../../Event/Event.h"

using namespace OUAN;

GameObjectVolumeCapsule::GameObjectVolumeCapsule(const std::string& name)
:GameObject(name)
{

}

GameObjectVolumeCapsule::~GameObjectVolumeCapsule()
{

}

void GameObjectVolumeCapsule::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectVolumeCapsule::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectVolumeCapsule::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}


RenderComponentEntityPtr GameObjectVolumeCapsule::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectVolumeCapsule::setPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule)
{
	mPhysicsComponentVolumeCapsule=pPhysicsComponentVolumeCapsule;
}

PhysicsComponentVolumeCapsulePtr GameObjectVolumeCapsule::getPhysicsComponentVolumeCapsule()
{
	return mPhysicsComponentVolumeCapsule;
}

void GameObjectVolumeCapsule::changeWorld(int world)
{
	if(mLogicComponentWorldExistance->getExistsInDreams() && mLogicComponentWorldExistance->getExistsInNightmares())
	{
		mRenderComponentEntity->setVisible(false);
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
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeCapsule.get() && mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponentWorldExistance->getExistsInNightmares())
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentVolumeCapsule.get() && !mPhysicsComponentVolumeCapsule->isInUse())
				{
					mPhysicsComponentVolumeCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
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
TGameObjectVolumeCapsuleParameters::TGameObjectVolumeCapsuleParameters() : TGameObjectParameters()
{

}

TGameObjectVolumeCapsuleParameters::~TGameObjectVolumeCapsuleParameters()
{

}