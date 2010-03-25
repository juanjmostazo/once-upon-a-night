#include "GameObjectStoryBook.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectStoryBook::GameObjectStoryBook(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_STORYBOOK)
{

}

GameObjectStoryBook::~GameObjectStoryBook()
{

}

RenderComponentEntityPtr GameObjectStoryBook::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

void GameObjectStoryBook::setRenderComponentPositional(RenderComponentPositionalPtr pRenderComponentPositional)
{
	mRenderComponentPositional=pRenderComponentPositional;
}

RenderComponentPositionalPtr GameObjectStoryBook::getRenderComponentPositional() const
{
	return mRenderComponentPositional;
}

void GameObjectStoryBook::setPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	mPhysicsComponentVolumeBox=pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeBoxPtr GameObjectStoryBook::getPhysicsComponentVolumeBox()
{
	return mPhysicsComponentVolumeBox;
}


TGameObjectStoryBookParameters::TGameObjectStoryBookParameters() : TGameObjectParameters()
{

}

TGameObjectStoryBookParameters::~TGameObjectStoryBookParameters()
{

}