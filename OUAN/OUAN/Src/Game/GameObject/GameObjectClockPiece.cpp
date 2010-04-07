#include "GameObjectClockPiece.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectClockPiece::GameObjectClockPiece(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_CLOCKPIECE)
{

}

GameObjectClockPiece::~GameObjectClockPiece()
{

}

RenderComponentEntityPtr GameObjectClockPiece::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectClockPiece::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectClockPiece::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

void GameObjectClockPiece::setRenderComponentInitialFromPositional()
{
	mRenderComponentInitial->setPosition(mRenderComponentPositional->getPosition());
	mRenderComponentInitial->setOrientation(mRenderComponentPositional->getOrientation());
}

RenderComponentPositionalPtr GameObjectClockPiece::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectClockPiece::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectClockPiece::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}

void GameObjectClockPiece::changeWorld(int world)
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

void GameObjectClockPiece::reset()
{

}

bool GameObjectClockPiece::hasPositionalComponent() const
{
	return true;
}

RenderComponentPositionalPtr GameObjectClockPiece::getPositionalComponent() const
{
	return getRenderComponentPositional();
}

TGameObjectClockPieceParameters::TGameObjectClockPieceParameters() : TGameObjectParameters()
{

}

TGameObjectClockPieceParameters::~TGameObjectClockPieceParameters()
{

}