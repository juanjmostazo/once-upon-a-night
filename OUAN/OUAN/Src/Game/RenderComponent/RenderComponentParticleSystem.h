#ifndef RenderComponentParticleSystemH_H
#define RenderComponentParticleSystemH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentParticleSystem: public RenderComponent
	{
	private:
		Ogre::ParticleSystem * mParticleSystem;
	public:

		RenderComponentParticleSystem(const std::string& name="");
		~RenderComponentParticleSystem();

		Ogre::ParticleSystem * getParticleSystem() const;
		void setParticleSystem(Ogre::ParticleSystem *);


	};
}

#endif