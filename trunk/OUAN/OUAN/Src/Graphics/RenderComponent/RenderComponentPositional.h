#ifndef RenderComponentPositionalH_H
#define RenderComponentPositionalH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentPositional: public RenderComponent
	{
	private:
		Ogre::SceneNode * mSceneNode;
	public:

		RenderComponentPositional(const std::string& type="");
		~RenderComponentPositional();

		Ogre::SceneNode * getSceneNode() const;
		void setSceneNode(Ogre::SceneNode *);		
	};

	class TRenderComponentPositionalParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentPositionalParameters();
		~TRenderComponentPositionalParameters();

		String parentSceneNodeName;
		Vector3 position;
		Quaternion orientation;
		Vector3 scale;
		String autotracktarget;
	};

}

#endif