#include "OUAN_Precompiled.h"

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

void GameObjectScene::setDreamsRender()
{
	mRenderComponentScene->setDreamsMaterials();
}

void GameObjectScene::setNightmaresRender()
{
	mRenderComponentScene->setNightmaresMaterials();
}

void GameObjectScene::setChangeWorldRender()
{
	mRenderComponentScene->setChangeWorldMaterials();
}

void GameObjectScene::changeWorldFinished(int newWorld)
{
	if (!isEnabled()) return;

	switch(newWorld)
	{
	case DREAMS:
		setDreamsRender();
		break;
	case NIGHTMARES:
		setNightmaresRender();
		break;
	default:break;
	}
}

void GameObjectScene::changeWorldStarted(int newWorld)
{
	if (!isEnabled()) return;

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