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
}

#endif