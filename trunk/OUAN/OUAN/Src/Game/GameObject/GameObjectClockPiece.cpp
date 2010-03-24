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

RenderComponentPositionalPtr GameObjectClockPiece::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectClockPiece::setPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	mPhysicsComponentSimpleCapsule=pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCapsulePtr GameObjectClockPiece::getPhysicsComponentSimpleCapsule()
{
	return mPhysicsComponentSimpleCapsule;
}


TGameObjectClockPieceParameters::TGameObjectClockPieceParameters() : TGameObjectParameters()
{

}

TGameObjectClockPieceParameters::~TGameObjectClockPieceParameters()
{

}