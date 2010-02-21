#include "RenderComponentParticleSystem.h"
using namespace OUAN;

RenderComponentParticleSystem::RenderComponentParticleSystem(const std::string& name)
:RenderComponent(COMPONENT_NAME_RENDER_PARTICLE_SYSTEM)
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

TRenderComponentParticleSystemParameters::TRenderComponentParticleSystemParameters() : TRenderComponentParameters()
{
}
TRenderComponentParticleSystemParameters::~TRenderComponentParticleSystemParameters()
{
}
