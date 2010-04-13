#include "GameObjectDoor.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDoor::GameObjectDoor(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DOOR)
{

}

GameObjectDoor::~GameObjectDoor()
{

}

void GameObjectDoor::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDoor::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDoor::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDoor::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectDoor::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectDoor::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectDoor::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectDoor::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectDoor::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDoor::getPhysicsComponentSimpleBox()
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDoor::changeWorld(int world)
{
	switch(world)
	{
		case DREAMS:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else if(mLogicComponent->existsInDreams()&& !mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityDreams->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}
			else if(!mLogicComponent->existsInDreams()&& mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntityNightmares->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}		
			break;
		default:
			break;
	}
}

void GameObjectDoor::reset()
{
	GameObject::reset();

	changeWorld(DREAMS);
}

bool GameObjectDoor::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectDoor::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------

TGameObjectDoorParameters::TGameObjectDoorParameters() : TGameObjectParameters()
{

}

TGameObjectDoorParameters::~TGameObjectDoorParameters()
{

}