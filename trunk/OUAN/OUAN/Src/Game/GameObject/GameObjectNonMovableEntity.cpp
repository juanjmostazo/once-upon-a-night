#include "GameObjectNonMovableEntity.h"

using namespace OUAN;

GameObjectNonMovableEntity::GameObjectNonMovableEntity(const std::string& name, const std::string& id)
:GameObjectNonMovable(name,id)
{

}

GameObjectNonMovableEntity::~GameObjectNonMovableEntity()
{

}

RenderComponentEntityPtr GameObjectNonMovableEntity::getRenderComponentEntity() const
{
	return mRenderComponentEntity;
}

void GameObjectNonMovableEntity::setRenderComponentEntity(RenderComponentEntityPtr pRenderComponentEntity)
{
	mRenderComponentEntity=pRenderComponentEntity;
}

RenderComponentSceneNodePtr GameObjectNonMovableEntity::getRenderComponentSceneNode() const
{
	return mRenderComponentSceneNode;
}

void GameObjectNonMovableEntity::setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode)
{
	mRenderComponentSceneNode=pRenderComponentSceneNode;
}