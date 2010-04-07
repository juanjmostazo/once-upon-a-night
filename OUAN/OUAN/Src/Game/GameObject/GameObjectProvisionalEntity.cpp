#include "GameObjectProvisionalEntity.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectProvisionalEntity::GameObjectProvisionalEntity(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_PROVISIONALENTITY)
{

}

GameObjectProvisionalEntity::~GameObjectProvisionalEntity()
{

}

void GameObjectProvisionalEntity::setRenderComponentEntityDreams(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityDreams=pRenderComponentEntity;
}

void GameObjectProvisionalEntity::setRenderComponentEntityNightmares(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntityNightmares=pRenderComponentEntity;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityDreams() const
{
	return mRenderComponentEntityDreams;
}

RenderComponentEntityPtr GameObjectProvisionalEntity::getRenderComponentEntityNightmares() const
{
	return mRenderComponentEntityNightmares;
}

void GameObjectProvisionalEntity::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectProvisionalEntity::setRenderComponentInitialFromPositional()
{
	mRenderComponentInitial->setPosition(mRenderComponentPositional->getPosition());
	mRenderComponentInitial->setOrientation(mRenderComponentPositional->getOrientation());
}

RenderComponentPositionalPtr GameObjectProvisionalEntity::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectProvisionalEntity::setPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	mPhysicsComponentSimpleBox=pPhysicsComponentSimpleBox;
}

PhysicsComponentSimpleBoxPtr GameObjectProvisionalEntity::getPhysicsComponentSimpleBox()
{
	return mPhysicsComponentSimpleBox;
}

void GameObjectProvisionalEntity::changeWorld(int world)
{
	if (!isEnabled()) return;

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

void GameObjectProvisionalEntity::reset()
{

}

bool GameObjectProvisionalEntity::hasPositionalComponent() const
{
	return true;
}
RenderComponentPositionalPtr GameObjectProvisionalEntity::getPositionalComponent() const
{
	return getRenderComponentPositional();
}
//-------------------------------------------------------------------------------------------

TGameObjectProvisionalEntityParameters::TGameObjectProvisionalEntityParameters() : TGameObjectParameters()
{

}

TGameObjectProvisionalEntityParameters::~TGameObjectProvisionalEntityParameters()
{

}