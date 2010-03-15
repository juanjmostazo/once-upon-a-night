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

		RenderComponentParticleSystem(const std::string& type="");
		~RenderComponentParticleSystem();

		Ogre::ParticleSystem * getParticleSystem() const;
		void setParticleSystem(Ogre::ParticleSystem *);

		void setVisible(bool visible);
	};

	class TRenderComponentParticleSystemParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentParticleSystemParameters();
		~TRenderComponentParticleSystemParameters();

		String particle;
		bool castshadows;
		bool visible;
	};

}

#endif