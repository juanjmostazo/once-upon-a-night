#include "RenderComponentScene.h"
using namespace OUAN;

RenderComponentScene::RenderComponentScene(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
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