#ifndef RenderComponentParticleSystemH_H
#define RenderComponentParticleSystemH_H

#include "RenderComponent.h"
#include "ParticleUniverseSystemManager.h"

namespace OUAN
{
	class RenderComponentParticleSystem: public RenderComponent
	{
	private:
		std::vector<ParticleUniverse::ParticleSystem*> mParticleSystems;
		int mPoolPointer;
		int mPoolSize;
		bool mStarted;

		void advancePoolPointer();

	public:
		RenderComponentParticleSystem(const std::string& type="", int poolSize=1);
		~RenderComponentParticleSystem();

		std::vector<ParticleUniverse::ParticleSystem*> getParticleSystems() const;
		void setParticleSystems(std::vector<ParticleUniverse::ParticleSystem*>);

		void setVisible(bool visible);

		void start();
		void start(Ogre::Vector3 position);
		void stop();
		void pause();
		void resume();
		bool hasStarted();

		void startAll();
		void stopAll();
		void pauseAll();
		void resumeAll();
	};

	class TRenderComponentParticleSystemParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentParticleSystemParameters();
		~TRenderComponentParticleSystemParameters();

		String templateName;
		bool attached;
		int poolSize;

		Ogre::uint8 queueID;
	};
}

#endif