#include "RenderComponentPositional.h"
#include "../CameraManager/CameraManager.h"
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

Vector3 RenderComponentPositional::getPosition() const
{
	return mSceneNode->getPosition();
}

Quaternion RenderComponentPositional::getOrientation() const
{
	return mSceneNode->getOrientation();
}

void RenderComponentPositional::setPosition(Vector3 position)
{
	mSceneNode->setPosition(position);
}

Vector3 RenderComponentPositional::getScale() const
{
	return mSceneNode->getScale();
}

void RenderComponentPositional::setScale(Vector3 scale)
{
	mSceneNode->setScale(scale);
}

void RenderComponentPositional::setOrientation(Quaternion orientation)
{
	mSceneNode->setOrientation(orientation);
}

double RenderComponentPositional::getYaw() const
{
	return mSceneNode->getOrientation().getYaw().valueDegrees();
}

double RenderComponentPositional::getPitch() const
{
	return mSceneNode->getOrientation().getPitch().valueDegrees();
}

double RenderComponentPositional::getRoll() const
{
	return mSceneNode->getOrientation().getRoll().valueDegrees();
}

CameraManagerPtr RenderComponentPositional::getCameraManager() const
{
	return mCameraManager;
}

void RenderComponentPositional::setCameraManager(CameraManagerPtr pCameraManager)
{
	mCameraManager=pCameraManager;
}

double RenderComponentPositional::computeDistanceTo(RenderComponentPositionalPtr other)
{
	if (other.get())
		return getPosition().distance(other->getPosition());
	else return -1;
}

TRenderComponentPositionalParameters::TRenderComponentPositionalParameters()
:TRenderComponentParameters()
{
}
TRenderComponentPositionalParameters::~TRenderComponentPositionalParameters()
{
}