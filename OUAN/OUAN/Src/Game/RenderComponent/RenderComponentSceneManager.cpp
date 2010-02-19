#include "RenderComponentSceneManager.h"
using namespace OUAN;

RenderComponentSceneManager::RenderComponentSceneManager(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponentSceneManager::~RenderComponentSceneManager()
{
	mSceneManager=NULL;
}
Ogre::SceneManager* RenderComponentSceneManager::getSceneManager() const
{
	return mSceneManager;
}
void RenderComponentSceneManager::setSceneManager(Ogre::SceneManager* sceneManager)
{
	mSceneManager=sceneManager;
}


