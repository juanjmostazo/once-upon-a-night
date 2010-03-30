#ifndef HUDBASEH_H
#define HUDBASEH_H
#include <Ogre.h>

namespace OUAN
{
	class HUDBase
	{
	protected:
		Ogre::Overlay* mOverlay;
		std::string mOverlayName;
	public:
		HUDBase();
		virtual ~HUDBase();
		virtual void init(const std::string& overlayName);
		virtual void destroy();
		void show();
		void showElement(const std::string& elementName);
		void hide();
		void hideElement(const std::string& elementName);
	};
}
#endif