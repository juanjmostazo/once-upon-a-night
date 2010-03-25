#include "GameObjectDiamondTree.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectDiamondTree::GameObjectDiamondTree(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_DIAMONDTREE)
{

}

GameObjectDiamondTree::~GameObjectDiamondTree()
{

}

void GameObjectDiamondTree::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectDiamondTree::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectDiamondTree::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectDiamondTree::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectDiamondTree::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectDiamondTree::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectDiamondTree::getPhysicsComponentSimpleBox()
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectDiamondTree::changeWorld(int world)
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
//-------------------------------------------------------------------------------------------

TGameObjectDiamondTreeParameters::TGameObjectDiamondTreeParameters() : TGameObjectParameters()
{

}

TGameObjectDiamondTreeParameters::~TGameObjectDiamondTreeParameters()
{

}