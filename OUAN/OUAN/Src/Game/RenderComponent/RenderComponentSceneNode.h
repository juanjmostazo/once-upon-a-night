#ifndef RenderComponentSceneNodeH_H
#define RenderComponentSceneNodeH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentSceneNode: public RenderComponent
	{
	private:
		Ogre::SceneNode * mSceneNode;
	public:

		RenderComponentSceneNode(const std::string& name="");
		~RenderComponentSceneNode();

		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode *);

	};
}

#endif