#ifndef __SIMPLE_INPUT_MANAGER__H__
#define __SIMPLE_INPUT_MANAGER__H__

#include <ois/OIS.h>

namespace Ogre
{
	class RenderWindow;
}

class SimpleInputManager
	: public OIS::MouseListener
	, public OIS::KeyListener
{
public:
	SimpleInputManager();
	virtual ~SimpleInputManager();

	void capture();

	virtual bool mouseMoved( const OIS::MouseEvent& e );
	virtual bool mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID button );
	virtual bool mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID button );

	virtual bool keyPressed( const OIS::KeyEvent& e );
	virtual bool keyReleased( const OIS::KeyEvent& e );

	OIS::InputManager* m_inputManager;
	OIS::Keyboard* m_keyboard;
	OIS::Mouse* m_mouse;

protected:
	void initialise( Ogre::RenderWindow* window, bool showDefaultMousePointer = true );
	void finalise();
	

};

#endif
