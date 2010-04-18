#ifndef RenderComponentDecalH_H
#define RenderComponentDecalH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentDecal: public RenderComponent
	{
	private:
		Ogre::SceneNode * mProjectorNode;
		Ogre::Frustum * mDecalFrustrum;
	public:

		RenderComponentDecal(const std::string& type="");
		~RenderComponentDecal();

		//Ogre::Decal * getDecal() const;
		//void setDecal(Ogre::Decal *);

		void setVisible(bool visible);
	};

	class TRenderComponentDecalParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentDecalParameters();
		~TRenderComponentDecalParameters();

		String particle;
		bool castshadows;
		bool visible;
	};

}

#endif