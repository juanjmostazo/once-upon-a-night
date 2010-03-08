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

Vector3 RenderComponentPositional::getPosition() const
{
	return mSceneNode->getPosition();
}

Quaternion RenderComponentPositional::getOrientation() const
{
	return mSceneNode->getOrientation();
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

RenderSubsystemPtr RenderComponentPositional::getRenderSubsystem() const
{
	return mRenderSubsystem;
}

void RenderComponentPositional::setRenderSubsystem(RenderSubsystemPtr renderSubsystem)
{
	mRenderSubsystem=renderSubsystem;
}

void RenderComponentPositional::setAsCameraTarget()
{
	mRenderSubsystem->setCameraTarget(this);
}

TRenderComponentPositionalParameters::TRenderComponentPositionalParameters()
:TRenderComponentParameters()
{
}
TRenderComponentPositionalParameters::~TRenderComponentPositionalParameters()
{
}