#ifndef RenderComponentGlowH_H
#define RenderComponentGlowH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentGlow : public RenderComponent
	{
	private:
		Ogre::SceneNode* mSceneNode;
		Ogre::Entity* mEntity;

	public:
		RenderComponentGlow(const std::string& type="");
		~RenderComponentGlow();

		Ogre::SceneNode* getSceneNode() const;
		void setSceneNode(Ogre::SceneNode* sceneNode);

		Ogre::Entity* getEntity() const;
		void setEntity(Ogre::Entity* entity);

		void setVisible(bool visible);
	};

	class TRenderComponentGlowParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentGlowParameters();
		~TRenderComponentGlowParameters();

		std::string material;
		double time_scale;
		double size_scale;
		double expand_width;
		double expand_grow;
		double alpha;
		double color_r;
		double color_g;
		double color_b;
	};
}

#endif