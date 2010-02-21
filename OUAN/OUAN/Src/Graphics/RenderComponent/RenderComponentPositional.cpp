#include "RenderComponentPositional.h"
using namespace OUAN;

RenderComponentPositional::RenderComponentPositional(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponentPositional::~RenderComponentPositional()
{
	mSceneNode=NULL;
}
Ogre::SceneNode* RenderComponentPositional::getSceneNode() const
{
	return mSceneNode;
}
void RenderComponentPositional::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode=sceneNode;
}

TRenderComponentPositionalParameters::TRenderComponentPositionalParameters()
:TRenderComponentParameters()
{
}
TRenderComponentPositionalParameters::~TRenderComponentPositionalParameters()
{
}