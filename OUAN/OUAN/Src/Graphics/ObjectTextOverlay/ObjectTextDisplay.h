#ifndef OBJECT_TEXT_DISPLAYH_H
#define OBJECT_TEXT_DISPLAYH_H
#include <Ogre.h>
namespace OUAN
{
	// Code taken from
	// http://www.ogre3d.org/wiki/index.php/ObjectTextDisplay
	class ObjectTextDisplay
	{
	public:
		ObjectTextDisplay(const Ogre::MovableObject* p, const Ogre::Camera* c);
		virtual ~ObjectTextDisplay();
		void enable(bool enable);
		void setText(const Ogre::String& text);
		void update();

	protected:
		const Ogre::MovableObject* m_p;
		const Ogre::Camera* m_c;
		bool m_enabled;
		Ogre::Overlay* m_pOverlay;
		Ogre::OverlayElement* m_pText;
		Ogre::OverlayContainer* m_pContainer;
		Ogre::String m_text;
		Ogre::String m_ShapeName;
		Ogre::String m_ShapeTextName;
		Ogre::String m_ContainerName;
	};
}
#endif