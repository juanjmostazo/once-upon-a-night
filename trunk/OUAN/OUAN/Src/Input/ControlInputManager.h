#ifndef __CONTROL_INPUT_MANAGER__H__
#define __CONTROL_INPUT_MANAGER__H__

#define PSXPAD_CFG "../../Config/psxpad-cfg.xml" 

#include "FullInputManager.h"

class ControlInputManager : public FullInputManager
{
public:
	ControlInputManager();
	virtual ~ControlInputManager();
	
protected:

	int defaultPadId;
	int padSelect, padStart;
	int padUp, padDown, padLeft, padRight;
	int padTriangle, padX, padSquare, padCircle;
	int padL1, padL2, padR1, padR2;

	virtual bool loadConfig();

	virtual bool isPressedMenu();			// Go to main menu
	virtual bool isPressedPause();			// Go to pause menu

	virtual bool isPressedJump();			// Jump
	virtual bool isPressedDoAction();		// Perform an action
	virtual bool isPressedUseWeapon();		// Use the pillow (dream) or shoot (nightmare)
	virtual bool isPressedWeaponAction();	// Change holder hand (dream) or recharge (nightmare)

	virtual bool isPressedGoForward();		// Go forward
	virtual bool isPressedGoBack();			// Go back
	virtual bool isPressedGoLeft();			// Go to left
	virtual bool isPressedGoRight();		// Go to right

	virtual bool isPressedWalk();			// Walk mode
	virtual bool isPressedAutoPoint();		// Automatic pointer
	virtual bool isPressedRotateLeft();		// Rotate color to left
	virtual bool isPressedRotateRight();	// Rotate color to right

	virtual void getMouseStateRelValues(
		float*, float*, float*);			// Mouse x, y, z coordinate values

	virtual void getJoystickStateAxes(
		float*, float*, float*, float*);	// Joystick left and right axes values (from -1 to 1)
};

#endif