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

		RenderComponentLight(const std::string& type="");
		~RenderComponentLight();

		Ogre::Light * getLight() const;
		void setLight(Ogre::Light *);

		void setVisible(bool visible);

		void setDiffuseColor(ColourValue colour);

		void setDirection(Vector3 direction);

	};

	class TRenderComponentLightParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentLightParameters();
		~TRenderComponentLightParameters();

		Ogre::Light::LightTypes lighttype;
		ColourValue diffuse;
		ColourValue specular;
		Vector3 direction;
		bool castshadows;
		Vector3 lightrange;
		Vector4 attenuation;
		Real power;
	};
}

#endif