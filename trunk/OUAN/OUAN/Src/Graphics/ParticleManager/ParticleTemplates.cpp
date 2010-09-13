#include "OUAN_Precompiled.h"

#include "ParticleTemplates.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;

ParticleTemplates::ParticleTemplates()
{
	
}

ParticleTemplates::~ParticleTemplates()
{

}

ParticleTemplates* ParticleTemplates::instance = NULL;

ParticleTemplates* ParticleTemplates::getInstance()
{
	if (instance == NULL)
	{
		instance = new ParticleTemplates();
	}

	return instance;
}

bool ParticleTemplates::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(PARTICLES_CFG))
	{
		config.getOption("PORTAL_CHANGE_WORLD_IDLE", PORTAL_CHANGE_WORLD_IDLE); 
		config.getOption("PORTAL_CHANGE_WORLD_CHANGING", PORTAL_CHANGE_WORLD_CHANGING); 
		config.getOption("PORTAL_CHANGE_WORLD_SKY", PORTAL_CHANGE_WORLD_SKY); 

		config.getOption("ONY_LAND_DREAMS", ONY_LAND_DREAMS); 
		config.getOption("ONY_LAND_NIGHTMARES", ONY_LAND_NIGHTMARES); 
		config.getOption("ONY_LAND_WAVE", ONY_LAND_WAVE); 
		config.getOption("ONY_LAND_WATER_WAVE", ONY_LAND_WATER_WAVE);
		config.getOption("ONY_LAND_WATER_DROPS", ONY_LAND_WATER_DROPS); 
		config.getOption("ONY_RUN_GRASS", ONY_RUN_GRASS); 
		config.getOption("ONY_RUN_SAND", ONY_RUN_SAND); 
		config.getOption("ONY_RUN_WATER", ONY_RUN_WATER); 
		config.getOption("ONY_RUN_SURPRISE", ONY_RUN_SURPRISE); 

		config.getOption("PILLOW_ATTACK", PILLOW_ATTACK); 

		config.getOption("FLASH_LIGHT_ATTACK", FLASH_LIGHT_ATTACK); 
		config.getOption("FLASH_LIGHT_ATTACK_RED", FLASH_LIGHT_ATTACK_RED); 
		config.getOption("FLASH_LIGHT_ATTACK_GREEN", FLASH_LIGHT_ATTACK_GREEN); 
		config.getOption("FLASH_LIGHT_ATTACK_BLUE", FLASH_LIGHT_ATTACK_BLUE); 

		config.getOption("DIAMOND_BRIGHTNESS", DIAMOND_BRIGHTNESS); 		
		config.getOption("DIAMOND_STARS_CLOUD", DIAMOND_STARS_CLOUD); 

		config.getOption("HEART_STARS_CLOUD", HEART_STARS_CLOUD); 

		config.getOption("BAG_HEARTS_FOUNTAIN", BAG_HEARTS_FOUNTAIN); 
		config.getOption("BAG_HEARTS_FOUNTAIN_DOUBLE", BAG_HEARTS_FOUNTAIN_DOUBLE); 
		config.getOption("BAG_STARS_CLOUD", BAG_STARS_CLOUD); 

		config.getOption("STORY_BOOK_HALO", STORY_BOOK_HALO); 
		config.getOption("STORY_BOOK_STARS_CLOUD", STORY_BOOK_STARS_CLOUD); 

		config.getOption("TOY_STARS_CLOUD", TOY_STARS_CLOUD); 

		config.getOption("CLOCK_PIECE_STARS_CLOUD", CLOCK_PIECE_STARS_CLOUD); 

		config.getOption("BOX_DUST", BOX_DUST); 
		config.getOption("BOMB_EXPLOSION", BOMB_EXPLOSION); 

		config.getOption("TRIPOLLO_DIE_DREAMS", TRIPOLLO_DIE_DREAMS); 
		config.getOption("TRIPOLLO_DIE_NIGHTMARES", TRIPOLLO_DIE_NIGHTMARES);
		config.getOption("TRIPOLLO_SHOCK", TRIPOLLO_SHOCK); 
		config.getOption("TRIPOLLO_SURPRISE", TRIPOLLO_SURPRISE); 

		config.getOption("NEST_BREAK", NEST_BREAK); 
		config.getOption("NEST_JUMP", NEST_JUMP); 

		config.getOption("DEFAULT_PARTICLE_SYSTEM_POOL_SIZE", value); 
		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE = atoi(value.c_str());

		success = true;
	}
	else
	{
		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE=1;

		success = false;
	}

	return success;
}