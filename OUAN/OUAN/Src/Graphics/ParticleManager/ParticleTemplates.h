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
		std::string PORTAL_CHANGE_WORLD_IDLE;
		std::string PORTAL_CHANGE_WORLD_CHANGING;

		std::string ONY_LAND_DREAMS;
		std::string ONY_LAND_NIGHTMARES;
		std::string ONY_LAND_WAVE;
		std::string ONY_LAND_WATER_WAVE;
		std::string ONY_LAND_WATER_DROPS;
		std::string ONY_RUN_GRASS;
		std::string ONY_RUN_SAND;
		std::string ONY_RUN_WATER;
		std::string ONY_RUN_SURPRISE;

		std::string PILLOW_ATTACK;

		std::string FLASH_LIGHT_ATTACK;
		std::string FLASH_LIGHT_ATTACK_RED;
		std::string FLASH_LIGHT_ATTACK_GREEN;
		std::string FLASH_LIGHT_ATTACK_BLUE;

		std::string DIAMOND_BRIGHTNESS;
		std::string DIAMOND_STARS_CLOUD;

		std::string HEART_STARS_CLOUD;

		std::string BAG_HEARTS_FOUNTAIN;
		std::string BAG_HEARTS_FOUNTAIN_DOUBLE;
		std::string BAG_STARS_CLOUD;

		std::string STORY_BOOK_HALO;
		std::string STORY_BOOK_STARS_CLOUD;

		std::string TOY_STARS_CLOUD;

		std::string CLOCK_PIECE_STARS_CLOUD;

		std::string BOX_DUST;

		std::string TRIPOLLO_DIE;

		/// General particle system params
		int DEFAULT_PARTICLE_SYSTEM_POOL_SIZE;

	protected:
		/// Singleton instance
		static ParticleTemplates* instance;
	};
}

#endif