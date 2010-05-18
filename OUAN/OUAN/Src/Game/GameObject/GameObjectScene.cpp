#include "GameObjectScene.h"
#include "../GameWorldManager.h"

using namespace OUAN;

GameObjectScene::GameObjectScene(const std::string& name)
:GameObject(name,GAME_OBJECT_TYPE_SCENE)
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

void GameObjectScene::changeWorldFinished(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}

	mRenderComponentScene->changeToWorld(world,1);
}

void GameObjectScene::changeWorldStarted(int world)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScene::changeToWorld(int world, double perc)
{
	if (!isEnabled()) return;

	switch(world)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

//-------------------------------------------------------------------------------------------
TGameObjectSceneParameters::TGameObjectSceneParameters() : TGameObjectParameters()
{

}

TGameObjectSceneParameters::~TGameObjectSceneParameters()
{

}