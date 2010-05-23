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

	class TRenderComponentSkyBoxParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSkyBoxParameters();
		~TRenderComponentSkyBoxParameters();

		bool active;
		Real distance;
		String materialDreams;
		String materialNightmares;

	};

	class TRenderComponentSceneParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSceneParameters();
		~TRenderComponentSceneParameters();

		ColourValue ambient;
		TRenderComponentSkyBoxParameters tRenderComponentSkyBoxParameters;
		TRenderComponentSkyDomeParameters tRenderComponentSkyDomeParameters;
	};

	class RenderComponentScene: public RenderComponent
	{
	private:
		Ogre::SceneManager * mSceneManager;
		TRenderComponentSkyDomeParameters tRenderComponentSkyDomeParameters;
		TRenderComponentSkyBoxParameters tRenderComponentSkyBoxParameters;

		ChangeWorldMaterialPtr mSkyDomeChangeWorldMaterialDreams;
		ChangeWorldMaterialPtr mSkyDomeChangeWorldMaterialNightmares;
		ChangeWorldMaterialPtr mSkyBoxChangeWorldMaterialDreams;
		ChangeWorldMaterialPtr mSkyBoxChangeWorldMaterialNightmares;
	public:

		RenderComponentScene(const std::string& type="");
		~RenderComponentScene();

		Ogre::SceneManager * getSceneManager() const;
		void setSceneManager(Ogre::SceneManager * sceneManager);

		void setSkyMaterials(TRenderComponentSceneParameters tRenderComponentSceneParameters,TChangeWorldMaterialParameters tChangeWorldMaterialParameters);

		/// React to a world change to the one given as a parameter
		/// @param world world to change to
		void changeToWorld(int newWorld, double perc);

		void setOriginalMaterials(int world);
		void setChangeWorldMaterials(int world);
		void initChangeWorldMaterials(TChangeWorldMaterialParameters tChangeWorldMaterialParameters);
		void randomizeChangeWorldMaterials();

		void update(double elapsedSeconds);

	};

}

#endif