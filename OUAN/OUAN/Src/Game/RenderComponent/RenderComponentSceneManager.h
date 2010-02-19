#ifndef RenderComponentSceneManagerH_H
#define RenderComponentSceneManagerH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentSceneManager: public RenderComponent
	{
	private:
		Ogre::SceneManager * mSceneManager;
	public:

		RenderComponentSceneManager(const std::string& name="");
		~RenderComponentSceneManager();

		Ogre::SceneManager * getSceneManager() const;
		void setSceneManager(Ogre::SceneManager *);


	};
}

#endif