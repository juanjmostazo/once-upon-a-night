#ifndef __CONTROL_INPUT_MANAGER__H__
#define __CONTROL_INPUT_MANAGER__H__

#include "InputDefs.h"
#include "FullInputManager.h"

namespace OUAN
{
	const std::string STRINGKEY_FORWARD="BUTTON_TEXT_FORWARD";
	const std::string STRINGKEY_BACKWARDS="BUTTON_TEXT_BACKWARDS";
	const std::string STRINGKEY_LEFT="BUTTON_TEXT_LEFT";
	const std::string STRINGKEY_RIGHT="BUTTON_TEXT_RIGHT";

	const std::string STRINGKEY_JUMP="BUTTON_TEXT_JUMP";
	const std::string STRINGKEY_USEWEAPON="BUTTON_TEXT_USEWEAPON";
	const std::string STRINGKEY_CENTER_CAMERA="BUTTON_TEXT_ACTION";
	const std::string STRINGKEY_RELOAD="BUTTON_TEXT_RELOAD";

	const std::string STRINGKEY_LROTATE="BUTTON_TEXT_LROTATE";
	const std::string STRINGKEY_RROTATE="BUTTON_TEXT_RROTATE";
	const std::string STRINGKEY_WALK="BUTTON_TEXT_WALK";
	const std::string STRINGKEY_FIRST_PERSON_CAMERA="BUTTON_TEXT_AUTOTARGET";

	const std::string STRINGKEY_PAUSE="BUTTON_TEXT_PAUSE";
	const std::string STRINGKEY_INGAME_MENU="BUTTON_TEXT_MENU";

	class ControlInputManager : public FullInputManager
	{
	public:
		ControlInputManager();
		virtual ~ControlInputManager();

		/// Load configuration
		void init(Ogre::RenderWindow* window, const std::string& language, bool showDefaultMousePointer = true );
		/// Clear resources
		void finalise();

		void capture();

		// Since at the moment there will be no need for a polymorphic redefinition 
		// of these methods, I've taken out the "virtual" specifier to reduce unnecessary overhead

		bool isPressedMenu(int *pad, int *key);			// Go to main menu
		bool isPressedPause(int *pad, int *key);		// Go to pause menu

		bool isPressedJump(int *pad, int *key);			// Jump
		bool isPressedCenterCamera(int *pad, int *key);		// Perform an action
		bool isPressedUseWeapon(int *pad, int *key);	// Use the pillow (dream) or shoot (nightmare)
		bool isPressedAutoTarget(int *pad, int *key);	// Change holder hand (dream) or recharge (nightmare)

		bool isPressedWalk(int *pad, int *key);			// Walk mode
		bool isPressedCameraFixedFirstPerson(int *pad, int *key);	// Automatic pointer
		bool isPressedRotateLeft(int *pad, int *key);	// Rotate color to left
		bool isPressedRotateRight(int *pad, int *key);	// Rotate color to right

		/// Convenience method to provide a quick exit key (essentially for debugging purposes)
		bool isPressedQuickExit(int *pad, int *key);
		/// Convenience method to enable performance debug mode
		bool isPressedToggleDebugPerformance(int *pad, int *key);
		/// Convenience method to enable physics debug mode
		bool isPressedToggleDebugPhysics(int *pad, int *key);
		/// Convenience method to enable trajectory debug mode
		bool isPressedToggleDebugTrajectory(int *pad, int *key);
		/// Convenience method to change between cameras
		bool isPressedToggleChangeCamera(int *pad, int *key);
		/// Convenience method to change current camera controller
		bool isPressedToggleChangeCameraController(int *pad, int *key);
		/// Convenience method to change current world
		bool isPressedToggleChangeWorld(int *pad, int *key);
		/// Convenience method to change current level
		bool isPressedToggleChangeLevel(int *pad, int *key);
		/// Detect if the 'toggle-console' key has been pressed
		/// @return true if there has been a 'toggle-console' key press
		bool isPressedToggleConsole(int *pad, int *key);
		/// Detect if the 'toggle-volumes' key has been pressed
		/// @return true if there has been a 'toggle-volumes' key press
		bool isPressedToggleVolumes(int *pad, int *key);
		/// Detect if the 'toggle-godmode' key has been pressed
		/// @return true if there has been a 'toggle-godmode' key press
		bool isPressedToggleGodMode(int *pad, int *key);
		/// Detect if the 'toggle-changeworlddebug' key has been pressed
		/// @return true if there has been a 'toggle-changeworlddebug' key press
		bool isPressedToggleChangeWorldDebug(int *pad, int *key);
		/// Detect if the 'toggle-showscenenodes' key has been pressed
		/// @return true if there has been a 'toggle-showscenenodes' key press
		bool isPressedToggleShowSceneNodes(int *pad, int *key);
		/// Launch testing cutscene
		/// @return true if there's been a 'run-cutscene' key press
		bool isPressedRunCutscene(int *pad, int *key);


		bool isDownMenu(int *pad, int *key);			// Go to main menu
		bool isDownPause(int *pad, int *key);		// Go to pause menu

		bool isDownJump(int *pad, int *key);			// Jump
		bool isDownCenterCamera(int *pad, int *key);		// Perform an action
		bool isDownUseWeapon(int *pad, int *key);	// Use the pillow (dream) or shoot (nightmare)
		bool isDownAutoTarget(int *pad, int *key);	// Change holder hand (dream) or recharge (nightmare)

		bool isDownWalk(int *pad, int *key);			// Walk mode
		bool isDownCameraFixedFirstPerson(int *pad, int *key);	// Automatic pointer
		bool isDownRotateLeft(int *pad, int *key);	// Rotate color to left
		bool isDownRotateRight(int *pad, int *key);	// Rotate color to right

		/// Convenience method to provide a quick exit key (essentially for debugging purposes)
		bool isDownQuickExit(int *pad, int *key);
		/// Convenience method to enable performance debug mode
		bool isDownToggleDebugPerformance(int *pad, int *key);
		/// Convenience method to enable physics debug mode
		bool isDownToggleDebugPhysics(int *pad, int *key);
		/// Convenience method to enable trajectory debug mode
		bool isDownToggleDebugTrajectory(int *pad, int *key);
		/// Convenience method to change between cameras
		bool isDownToggleChangeCamera(int *pad, int *key);
		/// Convenience method to change current camera controller
		bool isDownToggleChangeCameraController(int *pad, int *key);
		/// Convenience method to change current world
		bool isDownToggleChangeWorld(int *pad, int *key);
		/// Convenience method to change current level
		bool isDownToggleChangeLevel(int *pad, int *key);
		/// Detect if the 'toggle-console' key has been Down
		/// @return true if there has been a 'toggle-console' key press
		bool isDownToggleConsole(int *pad, int *key);
		/// Detect if the 'toggle-volumes' key has been Down
		/// @return true if there has been a 'toggle-volumes' key press
		bool isDownToggleVolumes(int *pad, int *key);
		/// Detect if the 'toggle-godmode' key has been Down
		/// @return true if there has been a 'toggle-godmode' key press
		bool isDownToggleGodMode(int *pad, int *key);
		/// Detect if the 'toggle-changeworlddebug' key has been Down
		/// @return true if there has been a 'toggle-changeworlddebug' key press
		bool isDownToggleChangeWorldDebug(int *pad, int *key);
		/// Detect if the 'toggle-showscenenodes' key has been Down
		/// @return true if there has been a 'toggle-showscenenodes' key press
		bool isDownToggleShowSceneNodes(int *pad, int *key);
		/// Launch testing cutscene
		/// @return true if there's been a 'run-cutscene' key press
		bool isDownRunCutscene(int *pad, int *key);

		Vector3 getMovement();
		void getMovementSimple(int & movementX, int & movementZ);
		Vector2 getCameraRotation();

		void getMouseStateRelValues(
			double & x, double & y, double & z);			// Mouse x, y, z coordinate values

		void getJoystickStateAxes(
			double & leftX, double & leftY, double & rightX, double & rightY);	// Joystick left and right axes values (from -1 to 1)

		/// Fill a dictionary containing the keyboard and pad mappings
		/// for a set of key ids
		void getInputMappings (TControlInputMapping& mappings);			

		std::string getMouseButtonName(int keyCode) const;
		std::string getAsString(OIS::KeyCode kc) const;
		std::string getPadButtonName(int button) const;
		TInputCfgMouseButtonMapper convertMouseButtonId(OIS::MouseButtonID mouseButtonId);
		
		void replaceConfig(TControlInputMapping& newMapping, bool saveToFile);

		void updateDownKeys();
		
	protected:
		/// In order to determine getMovement method result
		bool isPressedGoForward(int *pad, int *key);		// Go forward
		bool isPressedGoBack(int *pad, int *key);			// Go back
		bool isPressedGoLeft(int *pad, int *key);			// Go to left
		bool isPressedGoRight(int *pad, int *key);		// Go to right

		bool isDownGoForward(int *pad, int *key);		// Go forward
		bool isDownGoBack(int *pad, int *key);			// Go back
		bool isDownGoLeft(int *pad, int *key);			// Go to left
		bool isDownGoRight(int *pad, int *key);		// Go to right

		/// Get OIS' mouse button ID equivalent for the specified mouseButtonId as read from
		/// the default input configuration.
		/// @param inputCfgMouseButtonId default input configuration mouse button id.
		/// @return OIS' mouse button identifier.
		OIS::MouseButtonID convertMouseButtonId(TInputCfgMouseButtonMapper inputCfgMouseButtonId);

		/// Convenience method used to reduce massive copy-paste and replace when modifying
		/// the isPressedSOMEACTION() methods to add configurable keyboard/mouse input
		/// The default joystick will check the given button is pressed, and depending on the kind of value
		/// of the defaultInputKey parameter, the keyboard or mouse devices will be queried accordingly.
		/// Positive values will represent keyboard presses, whereas the negative ones will be mapped to
		/// mouse button clicks.
		/// 
		/// @param padButton		joystick button to query
		/// @param defaultInputKey	value from the config file which will be appropriately mapped to an
		///							OIS::KeyCode value or an OIS::MouseButtonID.
		/// @return true if the given joystick button/ default input key was pressed; false otherwise
		bool isPressed(int padButton, int defaultInputKey);
		bool isDown(int padButton, int defaultInputKey);

		/// Add to the 'mappings' dictionary a new entry for keyID, where its value will be
		/// a pair consisting of the values given under keyboardMapping and psxPadMapping
		/// @param keyID			key identifier
		/// @param keyboardMapping	keycode for the given mapping
		/// @param psxPadMapping	button id for the given mapping
		/// @param string key		index to locate the key's appropriate translation string
		/// @param mappings			dictionary containing the input mappings for the given key identifier
		void addPair(const std::string& keyID,int keyboardMapping, int psxPadMapping, const std::string& stringKey, TControlInputMapping& mappings);

		void replacePair(const std::string& keyID,int& keyboardMapping, int& psxPadMapping, TControlInputMapping& mappings);

		void ControlInputManager::saveDefaultInput();
		void ControlInputManager::savePsxInput();
	};
}
#endif