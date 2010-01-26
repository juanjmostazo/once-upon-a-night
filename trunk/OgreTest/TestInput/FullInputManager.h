#ifndef __FULL_INPUT_MANAGER__H__
#define __FULL_INPUT_MANAGER__H__

#include <ois/OIS.h>

namespace Ogre
{
	class RenderWindow;
}

class FullInputManager
	: public OIS::MouseListener
	, public OIS::KeyListener
	, public OIS::JoyStickListener
{
public:
	FullInputManager();
	virtual ~FullInputManager();

	void capture();

	virtual bool mouseMoved( const OIS::MouseEvent& e );
	virtual bool mousePressed( const OIS::MouseEvent& e, OIS::MouseButtonID button );
	virtual bool mouseReleased( const OIS::MouseEvent& e, OIS::MouseButtonID button );

	virtual bool keyPressed( const OIS::KeyEvent& e );
	virtual bool keyReleased( const OIS::KeyEvent& e );

	virtual bool povMoved( const OIS::JoyStickEvent &e, int pov );
    virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis );
    virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
    virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
    virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );

	virtual OIS::Mouse*    getMouse( void );
    virtual OIS::Keyboard* getKeyboard( void );
    virtual OIS::JoyStick* getJoystick( unsigned int index );

	virtual void getMouseStateRelValues(float* x, float* y, float* z);

    virtual int getNumOfJoysticks( void );
	virtual void getJoystickStateAxes(unsigned int index, float* leftX, float* leftY, float* rightX, float* rightY);
	

	void initialise( Ogre::RenderWindow* window, bool showDefaultMousePointer = true );
	void finalise();

protected:
	
	OIS::InputManager* m_inputManager;
	OIS::Keyboard* m_keyboard;
	OIS::Mouse* m_mouse;

	std::vector<OIS::JoyStick*> m_joysticks;
    std::vector<OIS::JoyStick*>::iterator it_joystick;
    std::vector<OIS::JoyStick*>::iterator it_joystickEnd;

	float getJoystickNormalisedAxe(int axeState, int maxAxis, int border);
};

#endif