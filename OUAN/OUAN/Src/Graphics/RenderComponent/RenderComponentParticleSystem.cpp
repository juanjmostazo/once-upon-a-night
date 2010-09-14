#include "OUAN_Precompiled.h"

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

std::vector<ParticleUniverse::ParticleSystem*> RenderComponentParticleSystem::getParticleSystems() const
{
	return mParticleSystems;
}

void RenderComponentParticleSystem::setParticleSystems(std::vector<ParticleUniverse::ParticleSystem*> particleSystems)
{
	mParticleSystems=particleSystems;
}

void RenderComponentParticleSystem::setVisible(bool visible)
{
	for (unsigned int i=0; i<mParticleSystems.size(); i++)
	{
		if(mParticleSystems[i])
		{
			mParticleSystems[i]->setVisible(visible);
		}
	}
}

void RenderComponentParticleSystem::start()
{
	start(Ogre::Vector3::ZERO);
}

void RenderComponentParticleSystem::start(Ogre::Vector3 position)
{
	//TODO REMOVE THIS LINE WHEN POOL BUG IS FIXED
	stop();

	advancePoolPointer();

	if (mParticleSystems.size() > 0)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->getParentSceneNode()->setPosition(position);
			mParticleSystems[mPoolPointer]->prepare();		
			mParticleSystems[mPoolPointer]->start();
		} 
		else 
		{
			Logger::getInstance()->log("RCParticleSystem - start(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
		}
	}
	else 
	{
		Logger::getInstance()->log("RCParticleSystem - start(): mParticleSystems is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::stop()
{
	if (mParticleSystems.size() > 0)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->stop();
		} 
		else 
		{
			Logger::getInstance()->log("RCParticleSystem - stop(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
		}
	}
	else 
	{
		Logger::getInstance()->log("RCParticleSystem - stop(): mParticleSystem is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::pause()
{
	if (mParticleSystems.size() > 0)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->pause();
		} 
		else 
		{
			Logger::getInstance()->log("RCParticleSystem - pause(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
		}
	}
	else 
	{
		Logger::getInstance()->log("RCParticleSystem - pause(): mParticleSystem is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::resume()
{
	if (mParticleSystems.size() > 0)
	{
		if (mParticleSystems[mPoolPointer])
		{
			mParticleSystems[mPoolPointer]->resume();
		} 
		else 
		{
			Logger::getInstance()->log("RCParticleSystem - resume(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
		}
	}
	else 
	{
		Logger::getInstance()->log("RCParticleSystem - resume(): mParticleSystem is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::startAll()
{
	if (mParticleSystems.size() > 0)
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
				Logger::getInstance()->log("RCParticleSystem - startAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
			}
		}
	}
	else
	{
		Logger::getInstance()->log("RCParticleSystem - startAll(): mParticleSystems is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::stopAll()
{
	if (mParticleSystems.size() > 0)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->stop();
			} 
			else 
			{
				Logger::getInstance()->log("RCParticleSystem - stopAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
			}
		}
	}
	else
	{
		Logger::getInstance()->log("RCParticleSystem - stopAll(): mParticleSystems is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::pauseAll()
{
	if (mParticleSystems.size() > 0)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->pause();
			} 
			else 
			{
				Logger::getInstance()->log("RCParticleSystem - pauseAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
			}
		}
	}
	else
	{
		Logger::getInstance()->log("RCParticleSystem - pauseAll(): mParticleSystems is NULL from " + getParentName());
	}
}

void RenderComponentParticleSystem::resumeAll()
{
	if (mParticleSystems.size() > 0)
	{
		for (int i=0; i<mPoolSize; i++)
		{
			if (mParticleSystems[i])
			{
				mParticleSystems[i]->resume();
			} 
			else 
			{
				Logger::getInstance()->log("RCParticleSystem - resumeAll(): mParticleSystem " + Ogre::StringConverter::toString(Ogre::Real(mPoolPointer)) + " is NULL from " + getParentName());
			}
		}
	}
	else
	{
		Logger::getInstance()->log("RCParticleSystem - resumeAll(): mParticleSystems is NULL from " + getParentName());
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
