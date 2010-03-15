#include "RenderComponentParticleSystem.h"
using namespace OUAN;

RenderComponentParticleSystem::RenderComponentParticleSystem(const std::string& type)
:RenderComponent(COMPONENT_TYPE_RENDER_PARTICLE_SYSTEM)
{

}

RenderComponentParticleSystem::~RenderComponentParticleSystem()
{
	mParticleSystem=NULL;
}

Ogre::ParticleSystem* RenderComponentParticleSystem::getParticleSystem() const
{
	return mParticleSystem;
}

void RenderComponentParticleSystem::setParticleSystem(Ogre::ParticleSystem* particleSystem)
{
	mParticleSystem=particleSystem;
}

void RenderComponentParticleSystem::setVisible(bool visible)
{
	mParticleSystem->setVisible(visible);
}

TRenderComponentParticleSystemParameters::TRenderComponentParticleSystemParameters() : TRenderComponentParameters()
{

}

TRenderComponentParticleSystemParameters::~TRenderComponentParticleSystemParameters()
{

}
