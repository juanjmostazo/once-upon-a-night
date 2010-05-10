#include "RenderComponentQuadHalo.h"

using namespace OUAN;

RenderComponentQuadHalo::RenderComponentQuadHalo(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_QUAD_HALO)
{

}

RenderComponentQuadHalo::~RenderComponentQuadHalo()
{
	
}

ThingRenderable* RenderComponentQuadHalo::getQuadHalo() const
{
	return mQuadHalo;
}

void RenderComponentQuadHalo::setQuadHalo(ThingRenderable* quadHalo)
{
	mQuadHalo = quadHalo;
}

Ogre::SceneNode* RenderComponentQuadHalo::getSceneNode() const
{
	return mSceneNode;
}

void RenderComponentQuadHalo::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode = sceneNode;
}

double RenderComponentQuadHalo::getSpeedScale() const
{
	return mSpeedScale;
}

void RenderComponentQuadHalo::setSpeedScale(double speedScale)
{
	mSpeedScale = speedScale;
}

void RenderComponentQuadHalo::setVisible(bool visible)
{
	mSceneNode->setVisible(visible);	
}

void RenderComponentQuadHalo::update(double elapsedSeconds)
{
	mQuadHalo->addTime((float)(elapsedSeconds * mSpeedScale));
}

TRenderComponentQuadHaloParameters::TRenderComponentQuadHaloParameters() : TRenderComponentParameters()
{

}

TRenderComponentQuadHaloParameters::~TRenderComponentQuadHaloParameters()
{

}
