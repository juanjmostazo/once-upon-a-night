#ifndef RenderComponentParticleSystemH_H
#define RenderComponentParticleSystemH_H

#include "RenderComponent.h"
#include "ParticleUniverseSystemManager.h"

namespace OUAN
{
	class RenderComponentParticleSystem: public RenderComponent
	{
	private:
		ParticleUniverse::ParticleSystem * mParticleSystem;

	public:

		RenderComponentParticleSystem(const std::string& type="");
		~RenderComponentParticleSystem();

		ParticleUniverse::ParticleSystem * getParticleSystem() const;
		void setParticleSystem(ParticleUniverse::ParticleSystem *);

		void setVisible(bool visible);
		void start();
		void stop();
		void pause();
		void resume();
	};

	class TRenderComponentParticleSystemParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentParticleSystemParameters();
		~TRenderComponentParticleSystemParameters();

		String templateName;
	};

}

#endif