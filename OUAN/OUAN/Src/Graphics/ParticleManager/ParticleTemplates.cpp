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

		success = true;
	}
	else
	{
		PORTAL_CHANGE_WORLD="";

		success = false;
	}

	return success;
}