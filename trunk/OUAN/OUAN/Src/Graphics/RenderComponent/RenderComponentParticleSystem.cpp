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
	if (mParticleSystem)
		mParticleSystem->setVisible(visible);
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - setVisible(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::run()
{
	if (mParticleSystem)
	{
		stop();	
		start();
	}
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - run(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::runOnce()
{
	run();
	//stopWhenFinished();
}

void RenderComponentParticleSystem::start()
{
	if (mParticleSystem)
	{
		mParticleSystem->prepare();		
		mParticleSystem->start();
	}
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - start(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::stop()
{
	if (mParticleSystem)
		mParticleSystem->stop();	
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stop(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::stopWhenFinished()
{
	if (mParticleSystem)
		mParticleSystem->stopFade();
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stopWhenFinished(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::stopWithDelay(double seconds)
{
	if (mParticleSystem)
		mParticleSystem->stop(seconds);
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stopWithDelay(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::pause()
{
	if (mParticleSystem)
		mParticleSystem->pause();	
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - pause(): mParticleSystem is NULL ");
}

void RenderComponentParticleSystem::resume()
{
	if (mParticleSystem)
		mParticleSystem->resume();		
	else Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - resume(): mParticleSystem is NULL ");
}

TRenderComponentParticleSystemParameters::TRenderComponentParticleSystemParameters() : TRenderComponentParameters()
{

}

TRenderComponentParticleSystemParameters::~TRenderComponentParticleSystemParameters()
{

}
