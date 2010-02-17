#include <stdlib.h>
#include "ControlInputManager.h"
#include "../Loader/Configuration.h"

using namespace OUAN;

ControlInputManager::ControlInputManager()
{
	loadConfig();
}

ControlInputManager::~ControlInputManager()
{
	
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::loadConfig()
{
	OUAN::Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(PSXPAD_CFG))
	{
		config.getOption("DEFAULT_PAD_ID", value); 
		defaultPadId = atoi(value.c_str());

		config.getOption("PAD_SELECT", value); 
		padSelect = atoi(value.c_str());
		config.getOption("PAD_START", value); 
		padStart = atoi(value.c_str());

		config.getOption("PAD_UP", value); 
		padUp = atoi(value.c_str());
		config.getOption("PAD_DOWN", value); 
		padDown = atoi(value.c_str());
		config.getOption("PAD_LEFT", value); 
		padLeft = atoi(value.c_str());
		config.getOption("PAD_RIGHT", value); 
		padRight = atoi(value.c_str());

		config.getOption("PAD_TRIANGLE", value); 
		padTriangle = atoi(value.c_str());
		config.getOption("PAD_X", value); 
		padX = atoi(value.c_str());
		config.getOption("PAD_SQUARE", value); 
		padSquare = atoi(value.c_str());
		config.getOption("PAD_CIRCLE", value); 
		padCircle = atoi(value.c_str());

		config.getOption("PAD_L1", value); 
		padL1 = atoi(value.c_str());
		config.getOption("PAD_L2", value); 
		padL2 = atoi(value.c_str());
		config.getOption("PAD_R1", value); 
		padR1 = atoi(value.c_str());
		config.getOption("PAD_R2", value); 
		padR2 = atoi(value.c_str());

		success = true;
	} 
	else 
	{
		defaultPadId = -1;
		padSelect = -1, padStart = -1;
		padUp = -1, padDown = -1, padLeft = -1, padRight = -1;
		padTriangle = -1, padX = -1, padSquare = -1, padCircle = -1;
		padL1 = -1, padL2 = -1, padR1 = -1, padR2 = -1;

		success = false;
	}

//	config.~Configuration();
	return success;
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedMenu()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padSelect) ||
		getKeyboard()->isKeyDown(OIS::KC_ESCAPE);
}

bool ControlInputManager::isPressedPause()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padStart) ||
		getKeyboard()->isKeyDown(OIS::KC_RETURN);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedJump()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padX) ||
		getKeyboard()->isKeyDown(OIS::KC_SPACE);
}

bool ControlInputManager::isPressedDoAction()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padCircle) ||
		getMouse()->getMouseState().buttonDown(OIS::MB_Right);
}

bool ControlInputManager::isPressedUseWeapon()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padSquare) ||
		getMouse()->getMouseState().buttonDown(OIS::MB_Left);
}

bool ControlInputManager::isPressedWeaponAction()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padTriangle) ||
		getKeyboard()->isKeyDown(OIS::KC_R);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedGoForward()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padUp) ||
		getKeyboard()->isKeyDown(OIS::KC_W);
}

bool ControlInputManager::isPressedGoBack()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padDown) ||
		getKeyboard()->isKeyDown(OIS::KC_S);
}

bool ControlInputManager::isPressedGoLeft()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padLeft) ||
		getKeyboard()->isKeyDown(OIS::KC_A);
}

bool ControlInputManager::isPressedGoRight()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padRight) ||
		getKeyboard()->isKeyDown(OIS::KC_D);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedWalk()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padR1) ||
		getKeyboard()->isKeyDown(OIS::KC_E);
}

bool ControlInputManager::isPressedAutoPoint()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padL1) ||
		getKeyboard()->isKeyDown(OIS::KC_Q);
}

bool ControlInputManager::isPressedRotateLeft()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padL2) ||
		getKeyboard()->isKeyDown(OIS::KC_Z);
}

bool ControlInputManager::isPressedRotateRight()
{
	return 
		getJoystick(defaultPadId)->getJoyStickState().buttonDown(padR2) ||
		getKeyboard()->isKeyDown(OIS::KC_X);
}

//////////////////////////////////////////////////////////////

void ControlInputManager::getMouseStateRelValues(float* x, float* y, float* z)
{
	FullInputManager::getMouseStateRelValues(x, y, z);
}

void ControlInputManager::getJoystickStateAxes(float* leftX, float* leftY, float* rightX, float* rightY)
{
	FullInputManager::getJoystickStateAxes(defaultPadId, leftX, leftY, rightX, rightY);
}