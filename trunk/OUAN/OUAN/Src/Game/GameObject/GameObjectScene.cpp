#include "GameObjectScene.h"

using namespace OUAN;

GameObjectScene::GameObjectScene(const std::string& name)
:GameObject(name)
{

}

GameObjectScene::~GameObjectScene()
{

}

RenderComponentScenePtr GameObjectScene::getRenderComponentScene() const
{
	return mRenderComponentScene;
}

void GameObjectScene::setRenderComponentScene(RenderComponentScenePtr pRenderComponentScene)
{
	mRenderComponentScene=pRenderComponentScene;
}

TGameObjectSceneParameters::TGameObjectSceneParameters() : TGameObjectParameters()
{

}

TGameObjectSceneParameters::~TGameObjectSceneParameters()
{

}