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

		double mOriginalHeight;
		double mOriginalWidth;
	public:

		RenderComponentViewport(const std::string& type="");
		~RenderComponentViewport();

		Ogre::Viewport * getViewport() const;
		void setViewport(Ogre::Viewport *);

		void setEffect(std::string effectName, bool activated);

		void setRenderSubsystem(RenderSubsystemPtr pRenderSubsystem);
		RenderSubsystemPtr getRenderSubsystem() const;

		void setBloomAmount(double perc);

		void prepareEffects();
		void initEffects();

		void disableAllCompositors();
		void rescaleViewport(double left, double top, double width, double height);
		void clearViewport(unsigned int buffers=Ogre::FBT_COLOUR|Ogre::FBT_DEPTH, const ColourValue &colour=ColourValue::Black, Real depth=1.0f, unsigned short stencil=0);
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