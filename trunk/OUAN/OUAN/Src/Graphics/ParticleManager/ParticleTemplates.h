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

	protected:
		/// Singleton instance
		static ParticleTemplates* instance;
	};
}

#endif