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

ParticleUniverse::ParticleSystem* RenderComponentParticleSystem::getParticleSystem() const
{
	return mParticleSystem;
}

void RenderComponentParticleSystem::setParticleSystem(ParticleUniverse::ParticleSystem* particleSystem)
{
	mParticleSystem=particleSystem;
}

void RenderComponentParticleSystem::setVisible(bool visible)
{
	mParticleSystem->setVisible(visible);	
}

void RenderComponentParticleSystem::start()
{
	mParticleSystem->stop();		
	mParticleSystem->prepare();		
	mParticleSystem->start();		
}

void RenderComponentParticleSystem::stop()
{
	mParticleSystem->stop();		
}

void RenderComponentParticleSystem::pause()
{
	mParticleSystem->pause();		
}

void RenderComponentParticleSystem::resume()
{
	mParticleSystem->resume();		
}

TRenderComponentParticleSystemParameters::TRenderComponentParticleSystemParameters() : TRenderComponentParameters()
{

}

TRenderComponentParticleSystemParameters::~TRenderComponentParticleSystemParameters()
{

}
