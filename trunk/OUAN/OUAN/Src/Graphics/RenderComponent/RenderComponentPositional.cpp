#include "RenderComponentPositional.h"
using namespace OUAN;

RenderComponentPositional::RenderComponentPositional(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_POSITIONAL)
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