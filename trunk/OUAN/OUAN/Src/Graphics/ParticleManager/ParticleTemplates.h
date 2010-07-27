#ifndef PARTICLETEMPLATESH_H
#define PARTICLETEMPLATESH_H

#include "../../OUAN.h"

namespace OUAN
{
	class ParticleTemplates
	{
	public:
		//Constructor
		ParticleTemplates();

		//Destructor
		~ParticleTemplates();

		/// Singleton getter
		static ParticleTemplates* getInstance();

		/// Load params from config file
		virtual bool loadConfig();

		/// Particle name values
		std::string PORTAL_CHANGE_WORLD;

		std::string ONY_LAND_DREAMS;
		std::string ONY_LAND_NIGHTMARES;
		std::string ONY_LAND_WAVE;
		std::string ONY_RUN_GRASS;
		std::string ONY_RUN_SAND;
		std::string ONY_RUN_WATER;
		std::string ONY_RUN_SURPRISE;

		std::string PILLOW_ATTACK;
		std::string FLASH_LIGHT_ATTACK;

		/// General particle system params
		int DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;

	protected:
		/// Singleton instance
		static ParticleTemplates* instance;
	};
}

#endif