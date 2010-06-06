#include "RenderComponentGlow.h"

using namespace OUAN;

RenderComponentGlow::RenderComponentGlow(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_GLOW)
{

}

RenderComponentGlow::~RenderComponentGlow()
{

}

Ogre::SceneNode* RenderComponentGlow::getSceneNode() const
{
	return mSceneNode;
}

void RenderComponentGlow::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode = sceneNode;
}

Ogre::Entity* RenderComponentGlow::getEntity() const
{
	return mEntity;
}

void RenderComponentGlow::setEntity(Ogre::Entity* entity)
{
	mEntity = entity;
}

void RenderComponentGlow::setVisible(bool visible)
{
	mSceneNode->setVisible(visible);	
}

TRenderComponentGlowParameters::TRenderComponentGlowParameters() : TRenderComponentParameters()
{

}

TRenderComponentGlowParameters::~TRenderComponentGlowParameters()
{

}
