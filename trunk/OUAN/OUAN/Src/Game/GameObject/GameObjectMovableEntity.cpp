#include "GameObjectMovableEntity.h"

using namespace OUAN;

GameObjectMovableEntity::GameObjectMovableEntity(const std::string& name, const std::string& id)
:GameObjectMovable(name,id)
{

}

GameObjectMovableEntity::~GameObjectMovableEntity()
{

}

RenderComponentEntityPtr GameObjectMovableEntity::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectMovableEntity::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentSceneNodePtr GameObjectMovableEntity::getRenderComponentSceneNode() const
{
	return mRenderComponentSceneNode;
}

void GameObjectMovableEntity::setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode)
{
	mRenderComponentSceneNode=pRenderComponentSceneNode;
}