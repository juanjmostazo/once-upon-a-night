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

void GameObjectScene::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentScene->setChangeWorldMaterials(newWorld);

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScene::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

	mRenderComponentScene->randomizeChangeWorldMaterials();

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScene::changeToWorld(int newWorld, double perc)
{
	if (!isEnabled()) return;

	mRenderComponentScene->changeToWorld(newWorld,perc);

	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameObjectScene::update(double elapsedSeconds)
{
	GameObject::update(elapsedSeconds);
	mRenderComponentScene->update(elapsedSeconds);
}

//-------------------------------------------------------------------------------------------
TGameObjectSceneParameters::TGameObjectSceneParameters() : TGameObjectParameters()
{

}

TGameObjectSceneParameters::~TGameObjectSceneParameters()
{

}