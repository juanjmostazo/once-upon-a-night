#ifndef RenderComponentSceneH_H
#define RenderComponentSceneH_H

#include "RenderComponent.h"

namespace OUAN
{
	class TRenderComponentSkyDomeParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSkyDomeParameters();
		~TRenderComponentSkyDomeParameters();

		bool active;
		Real distance;
		Real curvature;
		Real tiling;
		String materialDreams;
		String materialNightmares;
	};

	class TRenderComponentFogParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentFogParameters();
		~TRenderComponentFogParameters();

		Ogre::FogMode fogMode;
		ColourValue colour;
		Real start;
		Real end;
		Real density;
	};

	class TRenderComponentSceneParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSceneParameters();
		~TRenderComponentSceneParameters();

		ColourValue ambient;
		TRenderComponentSkyDomeParameters tRenderComponentSkyDomeParameters;
		TRenderComponentFogParameters tRenderComponentFogParameters;
	};

	class RenderComponentScene: public RenderComponent
	{
	private:
		Ogre::SceneManager * mSceneManager;
		TRenderComponentSkyDomeParameters tRenderComponentSkyDomeParameters;

		std::string mDreamsMaterial;
		std::string mNightmaresMaterial;
		std::string mChangeWorldMaterial;

	public:

		RenderComponentScene(const std::string& type="");
		~RenderComponentScene();

		Ogre::SceneManager * getSceneManager() const;
		void setSceneManager(Ogre::SceneManager * sceneManager);

		void setSkyMaterials(TRenderComponentSceneParameters tRenderComponentSceneParameters);

		void setMaterial(std::string material);
		void setDreamsMaterials();
		void setNightmaresMaterials();
		void setChangeWorldMaterials();
		void setChangeWorldFactor(double factor);

	};

}

#endif