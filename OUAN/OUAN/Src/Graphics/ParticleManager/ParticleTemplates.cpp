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
		config.getOption("PILLOW_ATTACK", PILLOW_ATTACK); 

		config.getOption("DEFAULT_PARTICLE_SYSTEM_POOL_SIZE", value); 
		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE = atoi(value.c_str());

		success = true;
	}
	else
	{
		PORTAL_CHANGE_WORLD="";
		ONY_LAND_DREAMS="";
		ONY_LAND_NIGHTMARES="";
		PILLOW_ATTACK="";

		DEFAULT_PARTICLE_SYSTEM_POOL_SIZE=1;

		success = false;
	}

	return success;
}