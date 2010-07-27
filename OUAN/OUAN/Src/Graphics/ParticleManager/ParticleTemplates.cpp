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
		config.getOption("PORTAL_CHANGE_WORLD", PORTAL_CHANGE_WORLD); 

		config.getOption("ONY_LAND_DREAMS", ONY_LAND_DREAMS); 
		config.getOption("ONY_LAND_NIGHTMARES", ONY_LAND_NIGHTMARES); 
		config.getOption("ONY_LAND_WAVE", ONY_LAND_WAVE); 
		config.getOption("ONY_RUN_GRASS", ONY_RUN_GRASS); 
		config.getOption("ONY_RUN_SAND", ONY_RUN_SAND); 
		config.getOption("ONY_RUN_WATER", ONY_RUN_WATER); 
		config.getOption("ONY_RUN_SURPRISE", ONY_RUN_SURPRISE); 

		config.getOption("PILLOW_ATTACK", PILLOW_ATTACK); 
		config.getOption("FLASH_LIGHT_ATTACK", FLASH_LIGHT_ATTACK); 

		config.getOption("DEFAULT_PARTICLE_SYSTEM_POOL_SIZE", value); 
		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE = atoi(value.c_str());

		success = true;
	}
	else
	{
		PORTAL_CHANGE_WORLD="";

		ONY_LAND_DREAMS="";
		ONY_LAND_NIGHTMARES="";
		ONY_LAND_WAVE="";

		ONY_RUN_GRASS="";
		ONY_RUN_SAND="";
		ONY_RUN_WATER="";
		ONY_RUN_SURPRISE="";

		PILLOW_ATTACK="";
		FLASH_LIGHT_ATTACK="";

		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE=1;

		success = false;
	}

	return success;
}