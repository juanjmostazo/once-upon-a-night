#ifndef RenderComponentLightH_H
#define RenderComponentLightH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentLight : public RenderComponent
	{
	private:
		Ogre::Light * mLight;
	public:

		RenderComponentLight(const std::string& name="");
		~RenderComponentLight();

		Ogre::Light * getLight() const;
		void setLight(Ogre::Light *);
	};
}

#endif