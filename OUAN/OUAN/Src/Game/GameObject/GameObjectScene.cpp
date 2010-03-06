#include "GameObjectScene.h"
#include "../GameWorldManager.h"

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

void GameObjectScene::changeWorld(int world)
{
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
void GameObjectScene::registerHandlers()
{
	GameObjectScenePtr _this =shared_from_this();
}
void GameObjectScene::unregisterHandlers()
{
	GameObjectScenePtr _this =shared_from_this();
}
//-------------------------------------------------------------------------------------------

TGameObjectSceneParameters::TGameObjectSceneParameters() : TGameObjectParameters()
{

}

TGameObjectSceneParameters::~TGameObjectSceneParameters()
{

}