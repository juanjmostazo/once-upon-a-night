#include "OUAN_Precompiled.h"

#include "ControlInputManager.h"

using namespace OUAN;

ControlInputManager::ControlInputManager()
{

}

ControlInputManager::~ControlInputManager()
{
	
}

//////////////////////////////////////////////////////////////

void ControlInputManager::init(Ogre::RenderWindow* window, const std::string& language,bool showDefaultMousePointer)
{
	FullInputManager::init(window, language, showDefaultMousePointer);
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
	bool isKeyboardKey= defaultInputKey > 0;
	bool isMouseButton = defaultInputKey < 0;
	bool isValidJoystickButton = getJoystick(defaultPadId) && padButton >= 0; //Ensure there is a joystick and the button is valid
	
	return 
		(isValidJoystickButton && getJoystick(defaultPadId)->getJoyStickState().buttonDown(padButton))
		|| (isKeyboardKey && getKeyboard()->isKeyDown(static_cast<OIS::KeyCode>(defaultInputKey)))
		|| (isMouseButton && getMouse()->getMouseState().buttonDown(convertMouseButtonId(static_cast<TInputCfgMouseButtonMapper>(defaultInputKey))));
}

bool ControlInputManager::isPressedMenu(int *pad, int* key)
{
	*pad = padSelect;
	*key = mDefaultInputData.keyMenu;
	return isPressed(padSelect,mDefaultInputData.keyMenu);
}

bool ControlInputManager::isPressedPause(int *pad, int* key)
{
	*pad = padStart;
	*key = mDefaultInputData.keyPause;
	return isPressed(padStart,mDefaultInputData.keyPause);
}

//////////////////////////////////////////////////////////////

bool ControlInputManager::isPressedJump(int *pad, int* key)
{
	*pad = padX;
	*key = mDefaultInputData.keyJump;
	return isPressed(padX,mDefaultInputData.keyJump);
}

bool ControlInputManager::isPressedCenterCamera(int *pad, int* key)
{
	*pad = padCircle;
	*key = mDefaultInputData.keyAction;
	return isPressed(padCircle,mDefaultInputData.keyAction);
}

bool ControlInputManager::isPressedUseWeapon(int *pad, int* key)
{
	*pad = padSquare;
	*key = mDefaultInputData.keyUseWeapon;
	return isPressed(padSquare,mDefaultInputData.keyUseWeapon);
}

bool ControlInputManager::isPressedWeaponAction(int *pad, int* key)
{
	*pad = padTriangle;
	*key = mDefaultInputData.keyReloadWeapon;
	return isPressed(padTriangle,mDefaultInputData.keyReloadWeapon);
}

bool ControlInputManager::isPressedGoForward(int *pad, int* key)
{
	*pad = padUp;
	*key = mDefaultInputData.keyForward;
	return isPressed(padUp,mDefaultInputData.keyForward);
}

bool ControlInputManager::isPressedGoBack(int *pad, int* key)
{
	*pad = padDown;
	*key = mDefaultInputData.keyBackwards;
	return isPressed(padDown,mDefaultInputData.keyBackwards);
}

bool ControlInputManager::isPressedGoLeft(int *pad, int* key)
{
	*pad = padLeft;
	*key = mDefaultInputData.keyLeft;
	return isPressed(padLeft, mDefaultInputData.keyLeft);
}

bool ControlInputManager::isPressedGoRight(int *pad, int* key)
{
	*pad = padRight;
	*key = mDefaultInputData.keyRight;
	return isPressed(padRight,mDefaultInputData.keyRight);
}

bool ControlInputManager::isPressedWalk(int *pad, int* key)
{ 
	*pad = padR2;
	*key = mDefaultInputData.keyWalk;
	return isPressed(padR2,mDefaultInputData.keyWalk);
}

bool ControlInputManager::isPressedCameraFixedFirstPerson(int *pad, int* key)
{
	*pad = padL2;
	*key = mDefaultInputData.keyAutoTarget;
	return isPressed(padL2,mDefaultInputData.keyAutoTarget);
}

bool ControlInputManager::isPressedRotateLeft(int *pad, int* key)
{
	*pad = padL1;
	*key = mDefaultInputData.keyRotateLeft;
	return isPressed(padL1,mDefaultInputData.keyRotateLeft);
}

bool ControlInputManager::isPressedRotateRight(int *pad, int* key)
{
	*pad = padR1;
	*key = mDefaultInputData.keyRotateRight;
	return isPressed(padR1,mDefaultInputData.keyRotateRight);
}

bool ControlInputManager::isPressedQuickExit(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyQuickExit;
	return isPressed(-1,mDefaultInputData.keyQuickExit);
}

bool ControlInputManager::isPressedToggleDebugPerformance(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyDebugPerformance;
	return isPressed(-1,mDefaultInputData.keyDebugPerformance);
}

bool ControlInputManager::isPressedToggleDebugPhysics(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyDebugPhysics;
	return isPressed(-1,mDefaultInputData.keyDebugPhysics);
}

bool ControlInputManager::isPressedToggleDebugTrajectory(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyDebugTrajectory;
	return isPressed(-1,mDefaultInputData.keyDebugTrajectory);
}

bool ControlInputManager::isPressedToggleChangeCamera(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyChangeCamera;
	return isPressed(-1,mDefaultInputData.keyChangeCamera);
}

bool ControlInputManager::isPressedToggleChangeCameraController(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyChangeCameraController;
	return isPressed(-1,mDefaultInputData.keyChangeCameraController);
}

bool ControlInputManager::isPressedToggleChangeWorld(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyChangeWorld;
	return isPressed(-1,mDefaultInputData.keyChangeWorld);
}

bool ControlInputManager::isPressedToggleChangeLevel(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyChangeLevel;
	return isPressed(-1,mDefaultInputData.keyChangeLevel);
}

bool ControlInputManager::isPressedToggleConsole(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyToggleConsole;
	return isPressed(-1,mDefaultInputData.keyToggleConsole);
}

bool ControlInputManager::isPressedToggleVolumes(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyToggleVolumes;
	return isPressed(-1,mDefaultInputData.keyToggleVolumes);
}

bool ControlInputManager::isPressedToggleGodMode(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyToggleGodMode;
	return isPressed(-1,mDefaultInputData.keyToggleGodMode);
}

bool ControlInputManager::isPressedToggleChangeWorldDebug(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyToggleChangeWorldDebug;
	return isPressed(-1,mDefaultInputData.keyToggleChangeWorldDebug);
}

bool ControlInputManager::isPressedToggleShowSceneNodes(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyToggleShowSceneNodes;
	return isPressed(-1,mDefaultInputData.keyToggleShowSceneNodes);
}

bool ControlInputManager::isPressedRunCutscene(int *pad, int* key)
{
	*pad = -1;
	*key = mDefaultInputData.keyRunCutscene;
	return isPressed(-1,mDefaultInputData.keyRunCutscene);
}

//////////////////////////////////////////////////////////////

Vector3 ControlInputManager::getMovement()
{
	int pad;
	int key;

	Vector3 nextMovement = Vector3::ZERO;

	double joystickLeftX=0;
	double joystickLeftZ=0;
	double joystickRightX=0;
	double joystickRightZ=0;

	getJoystickStateAxes(joystickLeftX, joystickLeftZ, joystickRightX, joystickRightZ);

	if (isPressedGoForward(&pad,&key))
	{
		nextMovement += Vector3::UNIT_Z;	
	}

	if (isPressedGoBack(&pad,&key))
	{
		nextMovement += Vector3::NEGATIVE_UNIT_Z;	
	}

	if (isPressedGoLeft(&pad,&key))
	{
		nextMovement += Vector3::UNIT_X;	
	}

	if (isPressedGoRight(&pad,&key))
	{
		nextMovement += Vector3::NEGATIVE_UNIT_X;	
	}

	nextMovement.x += joystickLeftX;
	nextMovement.z += joystickLeftZ;

	Ogre::Math::Clamp<double>(nextMovement.x,-1.0f,1.0f);
	Ogre::Math::Clamp<double>(nextMovement.z,-1.0f,1.0f);

	return nextMovement;
}

void ControlInputManager::getMovementSimple(int & movementX, int & movementZ)
{
	int pad;
	int key;

	movementX = 0;
	movementZ = 0;

	if (isPressedGoForward(&pad,&key))
	{
		movementZ = 1;
	}

	if (isPressedGoBack(&pad,&key))
	{
		movementZ = -1;	
	}

	if (isPressedGoLeft(&pad,&key))
	{
		movementX = 1;	
	}

	if (isPressedGoRight(&pad,&key))
	{
		movementX = -1;	
	}
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
		nextCameraRotation.x+=mouseX;
	}
	else if(joystickRightX!=0)
	{
		nextCameraRotation.x-=joystickRightX*padCameraJoystickScaleFactor;
	}

	if(mouseY!=0)
	{
		nextCameraRotation.y-=mouseY;
	}
	else if(joystickRightY!=0)
	{
		nextCameraRotation.y+=joystickRightY*padCameraJoystickScaleFactor;
	}

	return nextCameraRotation;
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
	addPair(KEY_FORWARD,mDefaultInputData.keyForward,padUp,STRINGKEY_FORWARD,mappings);
	addPair(KEY_BACKWARDS,mDefaultInputData.keyBackwards,padDown,STRINGKEY_BACKWARDS,mappings);
	addPair(KEY_LEFT,mDefaultInputData.keyLeft,padLeft,STRINGKEY_LEFT,mappings);
	addPair(KEY_RIGHT,mDefaultInputData.keyRight,padRight,STRINGKEY_RIGHT,mappings);

	addPair(KEY_JUMP,mDefaultInputData.keyJump,padX,STRINGKEY_JUMP,mappings);
	addPair(KEY_CENTER_CAMERA,mDefaultInputData.keyAction,padCircle,STRINGKEY_CENTER_CAMERA,mappings);
	addPair(KEY_USEWEAPON,mDefaultInputData.keyUseWeapon,padSquare,STRINGKEY_USEWEAPON,mappings);
	addPair(KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon,padTriangle,STRINGKEY_RELOAD,mappings);

	addPair(KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft,padL2,STRINGKEY_LROTATE,mappings);
	addPair(KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight,padR2,STRINGKEY_RROTATE,mappings);
	addPair(KEY_WALK,mDefaultInputData.keyWalk,padR1,STRINGKEY_WALK,mappings);
	addPair(KEY_FIRST_PERSON_CAMERA,mDefaultInputData.keyAutoTarget,padL1,STRINGKEY_FIRST_PERSON_CAMERA,mappings);

	addPair(KEY_PAUSE,mDefaultInputData.keyPause,padStart,STRINGKEY_PAUSE,mappings);
	addPair(KEY_MENU,mDefaultInputData.keyMenu,padSelect,STRINGKEY_INGAME_MENU,mappings);
}

void ControlInputManager::addPair(const std::string& keyID,int keyboardMapping, int psxPadMapping, const std::string& stringKey, TControlInputMapping& mappings)
{
	InputMappingEntry mapping;
	mapping.keyCode=keyboardMapping;
	mapping.padId=psxPadMapping;
	mapping.stringKey=stringKey;
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
		replacePair(KEY_CENTER_CAMERA,mDefaultInputData.keyAction,padCircle,newMapping);
		replacePair(KEY_USEWEAPON,mDefaultInputData.keyUseWeapon,padSquare,newMapping);
		replacePair(KEY_RELOADWEAPON,mDefaultInputData.keyReloadWeapon,padTriangle,newMapping);

		replacePair(KEY_ROTATELEFT,mDefaultInputData.keyRotateLeft,padL2,newMapping);
		replacePair(KEY_ROTATERIGHT,mDefaultInputData.keyRotateRight,padR2,newMapping);
		replacePair(KEY_WALK,mDefaultInputData.keyWalk,padR1,newMapping);
		replacePair(KEY_FIRST_PERSON_CAMERA,mDefaultInputData.keyAutoTarget,padL1,newMapping);

		replacePair(KEY_PAUSE,mDefaultInputData.keyPause,padStart,newMapping);
		replacePair(KEY_MENU,mDefaultInputData.keyMenu,padSelect,newMapping);
	}
	if (saveToFile)
	{
		saveDefaultInput();
		savePsxInput();
	}
}
void ControlInputManager::replacePair(const std::string& keyID,int& keyboardMapping, int& psxPadMapping, TControlInputMapping& mappings)
{
	keyboardMapping=mappings[keyID].keyCode;
	psxPadMapping=mappings[keyID].padId;
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
	ADD_CONFIG_ENTRY(mDefaultInputData.keyAction,KEY_CENTER_CAMERA,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyAutoTarget,KEY_FIRST_PERSON_CAMERA,false);
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
	ADD_CONFIG_ENTRY(mDefaultInputData.keyToggleChangeWorldDebug,KEY_TOGGLE_CHANGEWORLD_DEBUG,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyToggleShowSceneNodes,KEY_TOGGLE_SHOW_SCENE_NODES,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyDebugTrajectory,KEY_DEBUG_TRAJECTORY,false);
	ADD_CONFIG_ENTRY(mDefaultInputData.keyRunCutscene,KEY_RUN_CUTSCENE,false);

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