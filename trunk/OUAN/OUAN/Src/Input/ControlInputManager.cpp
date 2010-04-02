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
}

void ControlInputManager::finalise()
{
	mInputTextStrings.reset();
	FullInputManager::finalise();
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
TInputCfgMouseButtonMapper ControlInputManager::convertMouseButtonId(OIS::MouseButtonID mouseButtonId)
{
	switch(mouseButtonId)
	{
	case OIS::MB_Left:
		return INPUTCFG_MOUSEBUTTON_LEFT;
	case OIS::MB_Right:
		return INPUTCFG_MOUSEBUTTON_RIGHT;
	case OIS::MB_Middle:
		return INPUTCFG_MOUSEBUTTON_MIDDLE;
	case OIS::MB_Button3:
		return INPUTCFG_MOUSEBUTTON_MB3;
	case OIS::MB_Button4:
		return INPUTCFG_MOUSEBUTTON_MB4;
	case OIS::MB_Button5:
		return INPUTCFG_MOUSEBUTTON_MB5;
	case OIS::MB_Button6:
		return INPUTCFG_MOUSEBUTTON_MB6;
	case OIS::MB_Button7:
		return INPUTCFG_MOUSEBUTTON_MB7;
	default:
		return INPUTCFG_MOUSEBUTTON_LEFT;
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

Vector2 ControlInputManager::getMovement()
{
	Vector2 nextMovement = Vector2::ZERO;

	double joystickLeftX=0;
	double joystickLeftY=0;
	double joystickRightX=0;
	double joystickRightY=0;

	getJoystickStateAxes(joystickLeftX, joystickLeftY, joystickRightX, joystickRightY);

	if (isPressedGoForward())
	{
		nextMovement+=Vector2::UNIT_Y;	
	}

	if (isPressedGoBack())
	{
		nextMovement+=Vector2::NEGATIVE_UNIT_Y;	
	}

	if (isPressedGoLeft())
	{
		nextMovement+=Vector2::UNIT_X;	
	}

	if (isPressedGoRight())
	{
		nextMovement+=Vector2::NEGATIVE_UNIT_X;	
	}

	if(joystickLeftY!=0 || joystickLeftX!=0)
	{
		nextMovement.x+=joystickLeftX;
		nextMovement.y+=joystickLeftY;
	}

	return nextMovement;
}
Vector2 ControlInputManager::getCameraRotation()
{
	Vector2 nextCameraRotation = Vector2::ZERO;

	double joystickLeftX=0;
	double joystickLeftY=0;
	double joystickRightX=0;
	double joystickRightY=0;

	getJoystickStateAxes(joystickLeftX, joystickLeftY, joystickRightX, joystickRightY);

	double mouseX;
	double mouseY;
	double mouseZ;

	getMouseStateRelValues(mouseX,mouseY,mouseZ);

	if(mouseX!=0)
	{
		nextCameraRotation.x-=mouseX;
	}
	else if(joystickRightX!=0)
	{
		nextCameraRotation.x-=joystickRightX*padCameraJoystickScaleFactor;
	}

	if(mouseY!=0)
	{
		nextCameraRotation.y+=mouseY;
	}
	else if(joystickRightY!=0)
	{
		nextCameraRotation.y+=joystickRightY*padCameraJoystickScaleFactor;
	}

	return nextCameraRotation;
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

bool ControlInputManager::isPressedToggleConsole()
{
	return isPressed(-1,mDefaultInputData.keyToggleConsole);
}

bool ControlInputManager::isPressedToggleVolumes()
{
	return isPressed(-1,mDefaultInputData.keyToggleVolumes);
}

//////////////////////////////////////////////////////////////

void ControlInputManager::getMouseStateRelValues(double & x, double & y, double & z)
{
	FullInputManager::getMouseStateRelValues(x, y, z);
}

void ControlInputManager::getJoystickStateAxes(double & leftX, double & leftY, double & rightX, double & rightY)
{
	FullInputManager::getJoystickStateAxes(defaultPadId, leftX, leftY, rightX, rightY);
}

void ControlInputManager::getInputMappings (TControlInputMapping& mappings)
{
	mappings.clear();
	addPair(KEY_FORWARD,mDefaultInputData.keyForward,padUp,mappings);
	addPair(KEY_BACKWARDS,mDefaultInputData.keyBackwards,padDown,mappings);
	addPair(KEY_LEFT,mDefaultInputData.keyLeft,padLeft,mappings);
	addPair(KEY_RIGHT,mDefaultInputData.keyRight,padRight,mappings);

	addPair(KEY_JUMP,mDefaultInputData.keyJump,padX,mappings);
	addPair(KEY_ACTION,mDefaultInputData.keyAction,padCircle,mappings);
	addPair(KEY_USEWEAPON,mDefaultInputData.keyUseWeapon,padSquare,mappings);
	addPair(KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon,padTriangle,mappings);

	addPair(KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft,padL2,mappings);
	addPair(KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight,padR2,mappings);
	addPair(KEY_WALK,mDefaultInputData.keyWalk,padR1,mappings);
	addPair(KEY_AUTOTARGET,mDefaultInputData.keyAutoTarget,padL1,mappings);

	addPair(KEY_PAUSE,mDefaultInputData.keyPause,padStart,mappings);
	addPair(KEY_MENU,mDefaultInputData.keyMenu,padSelect,mappings);
}

void ControlInputManager::addPair(std::string keyID,int keyboardMapping, int psxPadMapping, TControlInputMapping& mappings)
{
	std::pair<int,int> mapping;
	mapping.first=keyboardMapping;
	mapping.second=psxPadMapping;
	mappings[keyID]=mapping;
}

// Macro to easily add case guards (quick, but a bit hacky)
#define ADD_CASE(x) case INPUTCFG_MOUSEBUTTON_##x: \
	{					\
	std::string option=""; \
	mInputTextStrings->getOption(MOUSE_BUTTON_NAME_##x,option); \
	return option; \
	}

std::string ControlInputManager::getMouseButtonName(int keyCode) const
{
	switch(static_cast<TInputCfgMouseButtonMapper>(keyCode))
	{
		ADD_CASE(LEFT);
		ADD_CASE(RIGHT);
		ADD_CASE(MIDDLE);
		ADD_CASE(MB3);
		ADD_CASE(MB4);
		ADD_CASE(MB5);
		ADD_CASE(MB6);
		ADD_CASE(MB7);
		default: return "";
	}	
}
#undef ADD_CASE

std::string ControlInputManager::getAsString(OIS::KeyCode kc) const
{
	std::string keyCode="";
	std::string keyName="";
	std::ostringstream valueWriter;
	if (m_keyboard)
	{	
		valueWriter<<std::hex<<std::setfill('0')<<std::setw(2)<<static_cast<int>(kc);
		std::string tmp=valueWriter.str();
		std::transform(tmp.begin(), tmp.end(), tmp.begin(), toupper);
		keyCode="0x"+tmp;
		mInputTextStrings->getOption(keyCode,keyName);
	}
	return keyName;
}

void ControlInputManager::replaceConfig(TControlInputMapping& newMapping, bool saveToFile)
{
	if (!newMapping.empty())
	{
		replacePair(KEY_FORWARD,mDefaultInputData.keyForward,padUp,newMapping);
		replacePair(KEY_BACKWARDS,mDefaultInputData.keyBackwards,padDown,newMapping);
		replacePair(KEY_LEFT,mDefaultInputData.keyLeft,padLeft,newMapping);
		replacePair(KEY_RIGHT,mDefaultInputData.keyRight,padRight,newMapping);

		replacePair(KEY_JUMP,mDefaultInputData.keyJump,padX,newMapping);
		replacePair(KEY_ACTION,mDefaultInputData.keyAction,padCircle,newMapping);
		replacePair(KEY_USEWEAPON,mDefaultInputData.keyUseWeapon,padSquare,newMapping);
		replacePair(KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon,padTriangle,newMapping);

		replacePair(KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft,padL2,newMapping);
		replacePair(KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight,padR2,newMapping);
		replacePair(KEY_WALK,mDefaultInputData.keyWalk,padR1,newMapping);
		replacePair(KEY_AUTOTARGET,mDefaultInputData.keyAutoTarget,padL1,newMapping);

		replacePair(KEY_PAUSE,mDefaultInputData.keyPause,padStart,newMapping);
		replacePair(KEY_MENU,mDefaultInputData.keyMenu,padSelect,newMapping);
	}
	if (saveToFile)
	{
		saveDefaultInput();
		savePsxInput();
	}
}
void ControlInputManager::replacePair(std::string keyID,int& keyboardMapping, int& psxPadMapping, TControlInputMapping& mappings)
{
	keyboardMapping=mappings[keyID].first;
	psxPadMapping=mappings[keyID].second;
}

// ...and yet another hacky preprocessor macro for lazy coders: 
// it just does text replacement on compile time, so I can save time
// copy-pasting without having to declare a function (with the overhead it implies)
// remember: this is not a function!

#define ADD_CONFIG_ENTRY(var,key,psx) \
	convertString.str(""); \
	if (psx) \
		convertString<<var; \
	else \
		convertString<<(var<0?"-0x":"0x")<<std::hex<<std::setfill('0')<<std::setw(2)<<abs(var); \
	c.setOption(key,convertString.str());

void ControlInputManager::saveDefaultInput()
{
	Configuration c;
	std::stringstream convertString;
	ADD_CONFIG_ENTRY(mDefaultInputData.keyAction,KEY_ACTION,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyAutoTarget,KEY_AUTOTARGET,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyBackwards,KEY_BACKWARDS,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyForward,KEY_FORWARD,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyJump,KEY_JUMP,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyLeft,KEY_LEFT,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyMenu,KEY_MENU,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyPause,KEY_PAUSE,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyReloadWeapon,KEY_RELOADWEAPON,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyRight,KEY_RIGHT,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyRotateLeft,KEY_ROTATELEFT,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyRotateRight,KEY_ROTATERIGHT,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyUseWeapon,KEY_USEWEAPON,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyWalk,KEY_WALK,false);
	// Non-user-configurable keys
	ADD_CONFIG_ENTRY(mDefaultInputData.keyQuickExit,KEY_QUICKEXIT,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyDebugPerformance,KEY_DEBUG_PERFORMANCE,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyDebugPhysics,KEY_DEBUG_PHYSICS,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyChangeCameraController,KEY_CHANGE_CAMERA_CONTROLLER,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyChangeCamera,KEY_CHANGE_CAMERA,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyChangeWorld,KEY_CHANGE_WORLD,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyChangeLevel,KEY_CHANGE_LEVEL,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyToggleConsole,KEY_TOGGLE_CONSOLE,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyToggleVolumes,KEY_TOGGLE_VOLUMES,false);

	c.saveToFile(DEFAULTINPUT_CFG);
}

void ControlInputManager::savePsxInput()
{
	Configuration c;
	std::stringstream convertString;
	ADD_CONFIG_ENTRY(defaultPadId,DEFAULT_PAD_ID,true); //THE SEMICOLON HERE ADDS AN EMPTY INSTRUCTION! (Hopefully, it's removed by the compiler)
	ADD_CONFIG_ENTRY(padUp,PAD_BUTTON_NAME_UP,true);
	ADD_CONFIG_ENTRY(padDown,PAD_BUTTON_NAME_DOWN,true);
	ADD_CONFIG_ENTRY(padLeft,PAD_BUTTON_NAME_LEFT,true);
	ADD_CONFIG_ENTRY(padRight,PAD_BUTTON_NAME_RIGHT,true);
	ADD_CONFIG_ENTRY(padTriangle,PAD_BUTTON_NAME_TRIANGLE,true);
	ADD_CONFIG_ENTRY(padCircle,PAD_BUTTON_NAME_CIRCLE,true);
	ADD_CONFIG_ENTRY(padSquare,PAD_BUTTON_NAME_SQUARE,true);
	ADD_CONFIG_ENTRY(padX, PAD_BUTTON_NAME_X,true);
	ADD_CONFIG_ENTRY(padL1, PAD_BUTTON_NAME_L1,true);
	ADD_CONFIG_ENTRY(padL2, PAD_BUTTON_NAME_L2,true);
	ADD_CONFIG_ENTRY(padR1, PAD_BUTTON_NAME_R1,true);
	ADD_CONFIG_ENTRY(padR2, PAD_BUTTON_NAME_R2,true);
	ADD_CONFIG_ENTRY(padSelect, PAD_BUTTON_NAME_SELECT,true);
	ADD_CONFIG_ENTRY(padStart, PAD_BUTTON_NAME_START,true);

	ADD_CONFIG_ENTRY(padLeftJoystickX,PAD_LEFT_JOYSTICK_Y,true);
	ADD_CONFIG_ENTRY(padLeftJoystickY,PAD_LEFT_JOYSTICK_X,true);

	ADD_CONFIG_ENTRY(padRightJoystickX,PAD_RIGHT_JOYSTICK_Y,true);
	ADD_CONFIG_ENTRY(padRightJoystickY,PAD_RIGHT_JOYSTICK_X,true);


	c.saveToFile(PSXPAD_CFG);
}
#undef ADD_CONFIG_ENTRY 

#define TEST_PAD_BUTTON(var,key) \
	if (var==button) \
	{\
		mInputTextStrings->getOption(key,padButtonName); \
		return padButtonName; \
	}
std::string ControlInputManager::getPadButtonName(int button) const
{
	std::string padButtonName="";
	TEST_PAD_BUTTON(padUp,PAD_BUTTON_NAME_UP);
	TEST_PAD_BUTTON(padDown,PAD_BUTTON_NAME_DOWN);
	TEST_PAD_BUTTON(padLeft,PAD_BUTTON_NAME_LEFT);
	TEST_PAD_BUTTON(padRight,PAD_BUTTON_NAME_RIGHT);

	TEST_PAD_BUTTON(padSquare,PAD_BUTTON_NAME_SQUARE);
	TEST_PAD_BUTTON(padCircle,PAD_BUTTON_NAME_CIRCLE);
	TEST_PAD_BUTTON(padTriangle,PAD_BUTTON_NAME_TRIANGLE);
	TEST_PAD_BUTTON(padX,PAD_BUTTON_NAME_X);

	TEST_PAD_BUTTON(padL1,PAD_BUTTON_NAME_L1);
	TEST_PAD_BUTTON(padL2,PAD_BUTTON_NAME_L2);
	TEST_PAD_BUTTON(padR1,PAD_BUTTON_NAME_R1);
	TEST_PAD_BUTTON(padR2,PAD_BUTTON_NAME_R2);

	TEST_PAD_BUTTON(padStart,PAD_BUTTON_NAME_START);
	TEST_PAD_BUTTON(padSelect,PAD_BUTTON_NAME_SELECT);
	
	return padButtonName;
}
#undef TEST_PAD_BUTTON