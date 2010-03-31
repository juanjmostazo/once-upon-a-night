#include "GameObjectScepter.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectScepter::GameObjectScepter(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SCEPTER)
{

}

GameObjectScepter::~GameObjectScepter()
{

}

RenderComponentEntityPtr GameObjectScepter::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectScepter::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectScepter::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectScepter::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectScepter::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectScepter::getPhysicsComponentSimpleCapsule()
{
	return mPhysicsComponentSimpleCapsule;
}

void GameObjectScepter::changeWorld(int world)
{
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
		{
			mPhysicsComponentSimpleCapsule->create();
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
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleCapsule.get() && !mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleCapsule.get() && mPhysicsComponentSimpleCapsule->isInUse())
				{
					mPhysicsComponentSimpleCapsule->destroy();
				}
			}
			break;
		default:
			break;
		}
	}
}
bool GameObjectScepter::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectScepter::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
TGameObjectScepterParameters::TGameObjectScepterParameters() : TGameObjectParameters()
{

}

TGameObjectScepterParameters::~TGameObjectScepterParameters()
{

}