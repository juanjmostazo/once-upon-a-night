#ifndef RenderComponentSceneH_H
#define RenderComponentSceneH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentScene: public RenderComponent
	{
	private:
		Ogre::SceneManager * mSceneManager;
	public:

		RenderComponentScene(const std::string& name="");
		~RenderComponentScene();

		Ogre::SceneManager * getSceneManager() const;
		void setSceneManager(Ogre::SceneManager *);


	};

	class TRenderComponentSkyDomeParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSkyDomeParameters();
		~TRenderComponentSkyDomeParameters();

		bool active;
		String material;
	};

	class TRenderComponentSkyBoxParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentSkyBoxParameters();
		~TRenderComponentSkyBoxParameters();

		bool active;
		String material;
		Real distance;
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
}

#endif