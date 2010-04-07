#include "GameObjectTree.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectTree::GameObjectTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_TREE)
{

}

GameObjectTree::~GameObjectTree()
{

}

RenderComponentEntityPtr GameObjectTree::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectTree::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectTree::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectTree::setRenderComponentInitial(RenderComponentInitialPtr pRenderComponentInitial)
{
	mRenderComponentInitial=pRenderComponentInitial;
}

RenderComponentPositionalPtr GameObjectTree::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

RenderComponentInitialPtr GameObjectTree::getRenderComponentInitial() const
{
	return mRenderComponentInitial;
}

void GameObjectTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectTree::getPhysicsComponentSimpleBox()
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectTree::changeWorld(int world)
{
	if(mLogicComponent->existsInDreams() && mLogicComponent->existsInNightmares())
	{
		if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
		{
			mPhysicsComponentSimpleBox->create();
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
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}		
			break;
		case NIGHTMARES:
			if(mLogicComponent->existsInNightmares())
			{
				mRenderComponentEntity->setVisible(true);
				if (mPhysicsComponentSimpleBox.get() && !mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->create();
				}
			}
			else
			{
				mRenderComponentEntity->setVisible(false);
				if (mPhysicsComponentSimpleBox.get() && mPhysicsComponentSimpleBox->isInUse())
				{
					mPhysicsComponentSimpleBox->destroy();
				}
			}
			break;
		default:
			break;
		}
	}
}

void GameObjectTree::reset()
{
	GameObject::reset();
}

bool GameObjectTree::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectTree::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectTreeParameters::TGameObjectTreeParameters() : TGameObjectParameters()
{

}

TGameObjectTreeParameters::~TGameObjectTreeParameters()
{

}