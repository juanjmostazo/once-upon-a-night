#ifndef RenderComponentViewportH_H
#define RenderComponentViewportH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentViewport: public RenderComponent
	{
	private:
		Ogre::Viewport * mViewport;
	public:

		RenderComponentViewport(const std::string& name="");
		~RenderComponentViewport();

		Ogre::Viewport * getViewport() const;
		void setViewport(Ogre::Viewport *);


	};

	class TRenderComponentViewportParameters: public TRenderComponentParameters
	{
	public:
		TRenderComponentViewportParameters();
		~TRenderComponentViewportParameters();

		ColourValue colour;
		int compositorcount;
		int index;
		bool overlays;
		bool shadows;
		bool skies;
	};
}

#endif