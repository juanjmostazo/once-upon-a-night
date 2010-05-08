#ifndef RenderComponentViewportH_H
#define RenderComponentViewportH_H

#include "RenderComponent.h"

namespace OUAN
{
	class RenderComponentViewport: public RenderComponent
	{
	private:
		Ogre::Viewport * mViewport;
		RenderSubsystemPtr mRenderSubsystem;
	public:

		RenderComponentViewport(const std::string& type="");
		~RenderComponentViewport();

		Ogre::Viewport * getViewport() const;
		void setViewport(Ogre::Viewport *);

		void setEffect(std::string effectName, bool activated);

		void setRenderSubsystem(RenderSubsystemPtr pRenderSubsystem);
		RenderSubsystemPtr getRenderSubsystem() const;

		void initEffects();
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