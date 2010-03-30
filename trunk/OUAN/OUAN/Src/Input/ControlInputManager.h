#ifndef __CONTROL_INPUT_MANAGER__H__
#define __CONTROL_INPUT_MANAGER__H__

#include "InputDefs.h"
#include "FullInputManager.h"

namespace OUAN
{


	class ControlInputManager : public FullInputManager
	{
	public:
		ControlInputManager();
		virtual ~ControlInputManager();

		/// Load configuration
		void init( Ogre::RenderWindow* window, bool showDefaultMousePointer = true );
		/// Clear resources
		void finalise();

		// Since at the moment there will be no need for a polymorphic redefinition 
		// of these methods, I've taken out the "virtual" specifier to reduce unnecessary overhead

		bool isPressedMenu();			// Go to main menu
		bool isPressedPause();			// Go to pause menu

		bool isPressedJump();			// Jump
		bool isPressedDoAction();		// Perform an action
		bool isPressedUseWeapon();		// Use the pillow (dream) or shoot (nightmare)
		bool isPressedWeaponAction();	// Change holder hand (dream) or recharge (nightmare)

		Vector2 getMovement();
		Vector2 getCameraRotation();

		bool isPressedWalk();			// Walk mode
		bool isPressedAutoPoint();		// Automatic pointer
		bool isPressedRotateLeft();		// Rotate color to left
		bool isPressedRotateRight();	// Rotate color to right

		/// Convenience method to provide a quick exit key (essentially for debugging purposes)
		bool isPressedQuickExit();
		/// Convenience method to enable performance debug mode
		bool isPressedToggleDebugPerformance();
		/// Convenience method to enable physics debug mode
		bool isPressedToggleDebugPhysics();
		/// Convenience method to change between cameras
		bool isPressedToggleChangeCamera();
		/// Convenience method to change current camera controller
		bool isPressedToggleChangeCameraController();
		/// Convenience method to change current world
		bool isPressedToggleChangeWorld();
		/// Convenience method to change current level
		bool isPressedToggleChangeLevel();
		/// Detect if the 'toggle-console' key has been pressed
		/// @return true if there has been a 'toggle-console' key press
		bool isPressedToggleConsole();
		/// Detect if the 'toggle-volumes' key has been pressed
		/// @return true if there has been a 'toggle-volumes' key press
		bool isPressedToggleVolumes();

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
		
	protected:

		/// In order to determine getMovement method result
		bool isPressedGoForward();		// Go forward
		bool isPressedGoBack();			// Go back
		bool isPressedGoLeft();			// Go to left
		bool isPressedGoRight();		// Go to right


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

		/// Add to the 'mappings' dictionary a new entry for keyID, where its value will be
		/// a pair consisting of the values given under keyboardMapping and psxPadMapping
		/// @param keyID			key identifier
		/// @param keyboardMapping	keycode for the given mapping
		/// @param psxPadMapping	button id for the given mapping
		/// @param mappings			dictionary containing the input mappings for the given key identifier
		void addPair(std::string keyID,int keyboardMapping, int psxPadMapping, TControlInputMapping& mappings);

		void replacePair(std::string keyID,int& keyboardMapping, int& psxPadMapping, TControlInputMapping& mappings);

		void ControlInputManager::saveDefaultInput();
		void ControlInputManager::savePsxInput();
	};
}
#endif