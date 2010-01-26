#include "ControlInputManager.h"

ControlInputManager::ControlInputManager()
{
	
}

ControlInputManager::~ControlInputManager()
{
	
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedMenu()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_SELECT) ||
		getKeyboard()->isKeyDown(OIS::KC_ESCAPE);
}

bool ControlInputManager::isPressedPause()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_START) ||
		getKeyboard()->isKeyDown(OIS::KC_RETURN);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedJump()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_X) ||
		getKeyboard()->isKeyDown(OIS::KC_SPACE);
}

bool ControlInputManager::isPressedDoAction()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_CIRCLE) ||
		getMouse()->getMouseState().buttonDown(OIS::MB_Right);
}

bool ControlInputManager::isPressedUseWeapon()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_SQUARE) ||
		getMouse()->getMouseState().buttonDown(OIS::MB_Left);
}

bool ControlInputManager::isPressedWeaponAction()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_TRIANGLE) ||
		getKeyboard()->isKeyDown(OIS::KC_R);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedGoForward()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_UP) ||
		getKeyboard()->isKeyDown(OIS::KC_W);
}

bool ControlInputManager::isPressedGoBack()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_DOWN) ||
		getKeyboard()->isKeyDown(OIS::KC_S);
}

bool ControlInputManager::isPressedGoLeft()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_LEFT) ||
		getKeyboard()->isKeyDown(OIS::KC_A);
}

bool ControlInputManager::isPressedGoRight()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_RIGHT) ||
		getKeyboard()->isKeyDown(OIS::KC_D);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedWalk()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_R1) ||
		getKeyboard()->isKeyDown(OIS::KC_E);
}

bool ControlInputManager::isPressedAutoPoint()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_L1) ||
		getKeyboard()->isKeyDown(OIS::KC_Q);
}

bool ControlInputManager::isPressedRotateLeft()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_L2) ||
		getKeyboard()->isKeyDown(OIS::KC_Z);
}

bool ControlInputManager::isPressedRotateRight()
{
	return 
		getJoystick(DEFAULT_PAD_ID)->getJoyStickState().buttonDown(PAD_R2) ||
		getKeyboard()->isKeyDown(OIS::KC_X);
}

//////////////////////////////////////////////////////////////

void ControlInputManager::getMouseStateRelValues(float* x, float* y, float* z)
{
	FullInputManager::getMouseStateRelValues(x, y, z);
}

void ControlInputManager::getJoystickStateAxes(float* leftX, float* leftY, float* rightX, float* rightY)
{
	FullInputManager::getJoystickStateAxes(DEFAULT_PAD_ID, leftX, leftY, rightX, rightY);
}