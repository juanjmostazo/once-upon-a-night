#include "OUAN_Precompiled.h"

#include "RenderComponentFractalVolume.h"

using namespace OUAN;

RenderComponentFractalVolume::RenderComponentFractalVolume(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_FRACTAL_VOLUME)
{

}

RenderComponentFractalVolume::~RenderComponentFractalVolume()
{

}

VolumeRenderable* RenderComponentFractalVolume::getFractalVolume() const
{
	return mFractalVolume;
}

void RenderComponentFractalVolume::setFractalVolume(VolumeRenderable* FractalVolume)
{
	mFractalVolume = FractalVolume;
}

Ogre::SceneNode* RenderComponentFractalVolume::getSceneNode() const
{
	return mSceneNode;
}

void RenderComponentFractalVolume::setSceneNode(Ogre::SceneNode* sceneNode)
{
	mSceneNode = sceneNode;
}

Ogre::Vector3 RenderComponentFractalVolume::getRotationDegrees() const
{
	return mRotationDegrees;
}

void RenderComponentFractalVolume::setRotationDegrees(Ogre::Vector3 rotationDegrees)
{
	mRotationDegrees = rotationDegrees;
}

void RenderComponentFractalVolume::setVisible(bool visible)
{
	mSceneNode->setVisible(visible);	
}

void RenderComponentFractalVolume::update(double elapsedSeconds)
{
	mSceneNode->pitch(Ogre::Degree(mRotationDegrees.x * elapsedSeconds));
	mSceneNode->yaw(Ogre::Degree(mRotationDegrees.y * elapsedSeconds));
	mSceneNode->roll(Ogre::Degree(mRotationDegrees.z * elapsedSeconds));
}

TRenderComponentFractalVolumeParameters::TRenderComponentFractalVolumeParameters() : TRenderComponentParameters()
{

}

TRenderComponentFractalVolumeParameters::~TRenderComponentFractalVolumeParameters()
{

}
