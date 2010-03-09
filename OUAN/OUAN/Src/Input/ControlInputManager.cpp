#include <sstream>
#include <stdlib.h>
#include "ControlInputManager.h"

using namespace OUAN;

ControlInputManager::ControlInputManager()
{

}

ControlInputManager::~ControlInputManager()
{
	
}

//////////////////////////////////////////////////////////////

void ControlInputManager::init( Ogre::RenderWindow* window, bool showDefaultMousePointer)
{
	FullInputManager::init(window,showDefaultMousePointer);
	loadConfig();
}

void ControlInputManager::finalise()
{
	FullInputManager::finalise();
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	// Load key mappings for mouse-keyboard input
	loadDefaultInputConfig(DEFAULTINPUT_CFG);

	// Same for a pad
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
		//LogManager::getSingleton().logMessage(PSXPAD_CFG + " COULD NOT BE LOADED!");

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

void ControlInputManager::readOption(Configuration cfg,const std::string& key, int& value)
{
	std::string strValue;
	std::istringstream valueReader;
	cfg.getOption(key,strValue);
	valueReader.str(strValue);
	valueReader>>std::hex>>value;
}

OIS::MouseButtonID ControlInputManager::convertMouseButtonId(TInputCfgMouseButtonMapper inputCfgMouseButtonId)
{
	switch(inputCfgMouseButtonId)
	{
	case INPUTCFG_MOUSEBUTTON_LEFT:
		return OIS::MB_Left;
	case INPUTCFG_MOUSEBUTTON_RIGHT:
		return OIS::MB_Right;
	case INPUTCFG_MOUSEBUTTON_MIDDLE:
		return OIS::MB_Middle;
	case INPUTCFG_MOUSEBUTTON_MB3:
		return OIS::MB_Button3;
	case INPUTCFG_MOUSEBUTTON_MB4:
		return OIS::MB_Button4;
	case INPUTCFG_MOUSEBUTTON_MB5:
		return OIS::MB_Button5;
	case INPUTCFG_MOUSEBUTTON_MB6:
		return OIS::MB_Button6;
	case INPUTCFG_MOUSEBUTTON_MB7:
		return OIS::MB_Button7;
	default:
		return OIS::MB_Left;
	}
}

bool ControlInputManager::loadDefaultInputConfig(const std::string& configFilePath)
{
	Configuration config;
	if (config.loadFromFile(configFilePath))
	{
		readOption(config,KEY_MENU,mDefaultInputData.keyMenu);
		readOption(config,KEY_PAUSE,mDefaultInputData.keyPause);

		readOption(config,KEY_USEWEAPON,mDefaultInputData.keyUseWeapon);
		readOption(config,KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon);
		readOption(config,KEY_ACTION,mDefaultInputData.keyAction);
		readOption(config,KEY_JUMP,mDefaultInputData.keyJump);
		readOption(config,KEY_WALK,mDefaultInputData.keyWalk);

		readOption(config,KEY_FORWARD,mDefaultInputData.keyForward);			
		readOption(config,KEY_BACKWARDS,mDefaultInputData.keyBackwards);
		readOption(config,KEY_LEFT,mDefaultInputData.keyLeft);
		readOption(config,KEY_RIGHT,mDefaultInputData.keyRight);

		readOption(config,KEY_AUTOTARGET,mDefaultInputData.keyAutoTarget);
		readOption(config,KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft);
		readOption(config,KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight);

		readOption(config,KEY_QUICKEXIT,mDefaultInputData.keyQuickExit);
		readOption(config,KEY_DEBUG_PERFORMANCE,mDefaultInputData.keyDebugPerformance);
		readOption(config,KEY_DEBUG_PHYSICS,mDefaultInputData.keyDebugPhysics);
		readOption(config,KEY_CHANGE_CAMERA_CONTROLLER,mDefaultInputData.keyChangeCameraController);
		readOption(config,KEY_CHANGE_CAMERA,mDefaultInputData.keyChangeCamera);
		readOption(config,KEY_CHANGE_WORLD,mDefaultInputData.keyChangeWorld);
		readOption(config,KEY_CHANGE_LEVEL,mDefaultInputData.keyChangeLevel);
		return true;
	}
	else
	{
		//LogManager::getSingleton().logMessage(configFilePath + " COULD NOT BE LOADED!");

		mDefaultInputData.keyAction=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyAutoTarget=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyBackwards=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyReloadWeapon=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyForward=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyJump=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyLeft=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyMenu=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyPause=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRight=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRotateLeft=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyRotateRight=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyWalk=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyUseWeapon=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyQuickExit=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyDebugPerformance=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyDebugPhysics=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeCamera=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeCameraController=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeWorld=OIS::KC_UNASSIGNED;
		mDefaultInputData.keyChangeLevel=OIS::KC_UNASSIGNED;
		return false;
	}
}


//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressed(int padButton, int defaultInputKey)
{
	bool isKeyboardKey= defaultInputKey>0;
	bool isMouseButton = defaultInputKey<0;
	bool isValidJoystickButton = getJoystick(defaultPadId) && padButton>=0; //Ensure there is a joystick and the button is valid
	return 
		(isValidJoystickButton && getJoystick(defaultPadId)->getJoyStickState().buttonDown(padButton))
		||(isKeyboardKey && getKeyboard()->isKeyDown(static_cast<OIS::KeyCode>(defaultInputKey)))
		|| (isMouseButton && getMouse()->getMouseState().buttonDown(
		convertMouseButtonId(static_cast<TInputCfgMouseButtonMapper>(defaultInputKey))));
}

bool ControlInputManager::isPressedMenu()
{
	return isPressed(padSelect,mDefaultInputData.keyMenu);
}

bool ControlInputManager::isPressedPause()
{
	return isPressed(padStart,mDefaultInputData.keyPause);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedJump()
{
	return isPressed(padX,mDefaultInputData.keyJump);
}

bool ControlInputManager::isPressedDoAction()
{
	return isPressed(padCircle,mDefaultInputData.keyAction);
}

bool ControlInputManager::isPressedUseWeapon()
{
	return isPressed(padSquare,mDefaultInputData.keyUseWeapon);
}

bool ControlInputManager::isPressedWeaponAction()
{
	return isPressed(padTriangle,mDefaultInputData.keyReloadWeapon);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedGoForward()
{
	return isPressed(padUp,mDefaultInputData.keyForward);
}

bool ControlInputManager::isPressedGoBack()
{
	return isPressed(padDown,mDefaultInputData.keyBackwards);
}

bool ControlInputManager::isPressedGoLeft()
{
	return isPressed(padLeft, mDefaultInputData.keyLeft);
}

bool ControlInputManager::isPressedGoRight()
{
	return isPressed(padRight,mDefaultInputData.keyRight);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedWalk()
{ 
	return isPressed(padR1,mDefaultInputData.keyWalk);
}

bool ControlInputManager::isPressedAutoPoint()
{
	return isPressed(padL1,mDefaultInputData.keyAutoTarget);
}

bool ControlInputManager::isPressedRotateLeft()
{
	return isPressed(padL2,mDefaultInputData.keyRotateLeft);
}

bool ControlInputManager::isPressedRotateRight()
{
	return isPressed(padR2,mDefaultInputData.keyRotateRight);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedQuickExit()
{
	return isPressed(-1,mDefaultInputData.keyQuickExit);
}

bool ControlInputManager::isPressedToggleDebugPerformance()
{
	return isPressed(-1,mDefaultInputData.keyDebugPerformance);
}

bool ControlInputManager::isPressedToggleDebugPhysics()
{
	return isPressed(-1,mDefaultInputData.keyDebugPhysics);
}

bool ControlInputManager::isPressedToggleChangeCamera()
{
	return isPressed(-1,mDefaultInputData.keyChangeCamera);
}

bool ControlInputManager::isPressedToggleChangeCameraController()
{
	return isPressed(-1,mDefaultInputData.keyChangeCameraController);
}

bool ControlInputManager::isPressedToggleChangeWorld()
{
	return isPressed(-1,mDefaultInputData.keyChangeWorld);
}

bool ControlInputManager::isPressedToggleChangeLevel()
{
	return isPressed(-1,mDefaultInputData.keyChangeLevel);
}

//////////////////////////////////////////////////////////////

void ControlInputManager::getMouseStateRelValues(double* x, double* y, double* z)
{
	FullInputManager::getMouseStateRelValues(x, y, z);
}

void ControlInputManager::getJoystickStateAxes(double* leftX, double* leftY, double* rightX, double* rightY)
{
	FullInputManager::getJoystickStateAxes(defaultPadId, leftX, leftY, rightX, rightY);
}