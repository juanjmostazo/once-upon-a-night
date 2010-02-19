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
}

#endif