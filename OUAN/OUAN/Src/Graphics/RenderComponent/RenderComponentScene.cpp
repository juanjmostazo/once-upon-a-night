#include "RenderComponentScene.h"
using namespace OUAN;

RenderComponentScene::RenderComponentScene(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_SCENE)
{
}
RenderComponentScene::~RenderComponentScene()
{
	mSceneManager=NULL;
}
Ogre::SceneManager* RenderComponentScene::getSceneManager() const
{
	return mSceneManager;
}
void RenderComponentScene::setSceneManager(Ogre::SceneManager* sceneManager)
{
	mSceneManager=sceneManager;
}


TRenderComponentSceneParameters::TRenderComponentSceneParameters() : TRenderComponentParameters()
{
}
TRenderComponentSceneParameters::~TRenderComponentSceneParameters()
{
}

TRenderComponentSkyBoxParameters::TRenderComponentSkyBoxParameters() : TRenderComponentParameters()
{
}
TRenderComponentSkyBoxParameters::~TRenderComponentSkyBoxParameters()
{
}

TRenderComponentSkyDomeParameters::TRenderComponentSkyDomeParameters() : TRenderComponentParameters()
{
}
TRenderComponentSkyDomeParameters::~TRenderComponentSkyDomeParameters()
{
}