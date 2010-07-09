#ifndef RenderComponentQuadHaloH_H
#define RenderComponentQuadHaloH_H

#include "RenderComponent.h"

#include "../Volume/ThingRenderable.h"

namespace OUAN
{
	class RenderComponentQuadHalo : public RenderComponent
	{
	private:
		ThingRenderable* mQuadHalo;
		Ogre::SceneNode* mSceneNode;
		double mSpeedScale;

	public:
		RenderComponentQuadHalo(const std::string& type="");
		~RenderComponentQuadHalo();
		
		ThingRenderable* getQuadHalo() const;
		void setQuadHalo(ThingRenderable* quadHalo);

		Ogre::SceneNode* getSceneNode() const;
		void setSceneNode(Ogre::SceneNode* sceneNode);

		double getSpeedScale() const;
		void setSpeedScale(double speedScale);

		void setVisible(bool visible);
		void update(double elapsedSeconds);
	};
	
	class TRenderComponentQuadHaloParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentQuadHaloParameters();
		~TRenderComponentQuadHaloParameters();

		std::string quadMaterial;
		double haloRadium;
		double totalQuads;
		double quadSize;
		double speedScale;
		double offsetX;
		double offsetY;
		double offsetZ;
	};
}

#endif