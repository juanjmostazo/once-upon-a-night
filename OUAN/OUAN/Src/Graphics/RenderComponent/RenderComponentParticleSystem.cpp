#include "RenderComponentParticleSystem.h"
using namespace OUAN;

RenderComponentParticleSystem::RenderComponentParticleSystem(const std::string& type, int poolSize)
:RenderComponent(COMPONENT_TYPE_RENDER_PARTICLE_SYSTEM)
{
	mPoolSize = poolSize;
	mPoolPointer = 0;
}

RenderComponentParticleSystem::~RenderComponentParticleSystem()
{
	for (int i=0; i<mPoolSize; i++)
	{
		mParticleSystems[i]=NULL;
	}
}

void RenderComponentParticleSystem::advancePoolPointer()
{
	mPoolPointer++;
	mPoolPointer = mPoolPointer % mPoolSize;
}

ParticleUniverse::ParticleSystem** RenderComponentParticleSystem::getParticleSystems() const
{
	return mParticleSystems;
}

void RenderComponentParticleSystem::setParticleSystems(ParticleUniverse::ParticleSystem** particleSystems)
{
	mParticleSystems=particleSystems;
}

void RenderComponentParticleSystem::setVisible(bool visible)
{
	if (mParticleSystems)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			mParticleSystems[i]->setVisible(visible);
		}
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - setVisible(): mParticleSystems is NULL");
	}
}

void RenderComponentParticleSystem::start()
{
	start(Ogre::Vector3::ZERO);
}

void RenderComponentParticleSystem::start(Ogre::Vector3 position)
{
	advancePoolPointer();

	if (mParticleSystems)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->getParentSceneNode()->setPosition(position);
			mParticleSystems[mPoolPointer]->prepare();		
			mParticleSystems[mPoolPointer]->start();
		} 
		else 
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - start(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
		}
	}
	else 
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - start(): mParticleSystems is NULL ");
	}
}

void RenderComponentParticleSystem::stop()
{
	if (mParticleSystems)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->stop();
		} 
		else 
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stop(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
		}
	}
	else 
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stop(): mParticleSystem is NULL ");
	}
}

void RenderComponentParticleSystem::pause()
{
	if (mParticleSystems)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->pause();
		} 
		else 
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - pause(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
		}
	}
	else 
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - pause(): mParticleSystem is NULL ");
	}
}

void RenderComponentParticleSystem::resume()
{
	if (mParticleSystems)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->resume();
		} 
		else 
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - resume(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
		}
	}
	else 
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - resume(): mParticleSystem is NULL ");
	}
}

void RenderComponentParticleSystem::startAll()
{
	if (mParticleSystems)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->prepare();
				mParticleSystems[i]->start();
			} 
			else 
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - startAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
			}
		}
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - startAll(): mParticleSystems is NULL");
	}
}

void RenderComponentParticleSystem::stopAll()
{
	if (mParticleSystems)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->stop();
			} 
			else 
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stopAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
			}
		}
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - stopAll(): mParticleSystems is NULL");
	}
}

void RenderComponentParticleSystem::pauseAll()
{
	if (mParticleSystems)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->pause();
			} 
			else 
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - pauseAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
			}
		}
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - pauseAll(): mParticleSystems is NULL");
	}
}

void RenderComponentParticleSystem::resumeAll()
{
	if (mParticleSystems)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->resume();
			} 
			else 
			{
				Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - resumeAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL ");
			}
		}
	}
	else
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("RCParticleSystem - resumeAll(): mParticleSystems is NULL");
	}
}

TRenderComponentParticleSystemParameters::TRenderComponentParticleSystemParameters() : TRenderComponentParameters()
{
	attached = true;
	poolSize = 1;
}

TRenderComponentParticleSystemParameters::~TRenderComponentParticleSystemParameters()
{

}
