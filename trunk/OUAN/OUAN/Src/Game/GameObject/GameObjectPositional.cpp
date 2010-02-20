#include "GameObjectPositional.h"

using namespace OUAN;

GameObjectPositional::GameObjectPositional(const std::string& name, const std::string& id)
:GameObject(name,id)
{

}

GameObjectPositional::~GameObjectPositional()
{

}



RenderComponentSceneNodePtr GameObjectPositional::getRenderComponentSceneNode() const
{
	return mRenderComponentSceneNode;
}

void GameObjectPositional::setRenderComponentSceneNode(RenderComponentSceneNodePtr pRenderComponentSceneNode)
{
	mRenderComponentSceneNode=pRenderComponentSceneNode;
}

TGameObjectPositionalParameters::TGameObjectPositionalParameters() : TGameObjectParameters()
{
}
TGameObjectPositionalParameters::~TGameObjectPositionalParameters()
{
}