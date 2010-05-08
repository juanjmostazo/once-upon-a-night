#include "RenderComponentViewport.h"
#include "../RenderSubsystem.h"
using namespace OUAN;

RenderComponentViewport::RenderComponentViewport(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_VIEWPORT)
{
}

RenderComponentViewport::~RenderComponentViewport()
{
	mViewport=NULL;
}

Ogre::Viewport* RenderComponentViewport::getViewport() const
{
	return mViewport;
}

void RenderComponentViewport::initEffects()
{
	Ogre::CompositorManager::getSingleton().addCompositor(mViewport,mRenderSubsystem->BLOOM);
	Ogre::CompositorManager::getSingleton().addCompositor(mViewport,mRenderSubsystem->HDR);

	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, mRenderSubsystem->BLOOM, false);
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, mRenderSubsystem->HDR, true);

}

void RenderComponentViewport::setViewport(Ogre::Viewport* viewport)
{
	mViewport=viewport;
}

void RenderComponentViewport::setEffect(std::string effectName, bool activated)
{
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(mViewport, effectName, activated);
}

void RenderComponentViewport::setRenderSubsystem(RenderSubsystemPtr pRenderSubsystem)
{
	mRenderSubsystem=pRenderSubsystem;
}

RenderSubsystemPtr RenderComponentViewport::getRenderSubsystem() const
{
	return mRenderSubsystem;
}

TRenderComponentViewportParameters::TRenderComponentViewportParameters() : TRenderComponentParameters()
{
}
TRenderComponentViewportParameters::~TRenderComponentViewportParameters()
{
}