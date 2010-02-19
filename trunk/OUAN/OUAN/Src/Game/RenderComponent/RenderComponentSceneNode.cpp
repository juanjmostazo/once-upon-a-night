#include "RenderComponentSceneNode.h"
using namespace OUAN;

RenderComponentSceneNode::RenderComponentSceneNode(const std::string& name)
:RenderComponent(name.empty()?COMPONENT_NAME_OGRE:name)
{
}
RenderComponentSceneNode::~RenderComponentSceneNode()
{
	mSceneNode=NULL;
}
Ogre::SceneNode* RenderComponentSceneNode::getSceneNode() const
{
	return mSceneNode;
}
void RenderComponentSceneNode::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode=sceneNode;
}
