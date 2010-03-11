#ifndef GAMEOPTIONSSTATEH_H
#define GAMEOPTIONSSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	//TODO: TAKE ME OUT OF HERE 
	const std::string BUTTON_TEXT_FORWARD="Forward: ";
	const std::string BUTTON_TEXT_BACKWARDS="Backwards: ";
	const std::string BUTTON_TEXT_LEFT="Left: ";
	const std::string BUTTON_TEXT_RIGHT="Right: ";

	const std::string BUTTON_TEXT_JUMP="Jump: ";
	const std::string BUTTON_TEXT_USEWEAPON="Use weapon: ";
	const std::string BUTTON_TEXT_ACTION="Action: ";
	const std::string BUTTON_TEXT_RELOAD="Reload: ";

	const std::string BUTTON_TEXT_LROTATE="Rot. left: ";
	const std::string BUTTON_TEXT_RROTATE="Rot. right: ";
	const std::string BUTTON_TEXT_WALK="Walk: ";
	const std::string BUTTON_TEXT_AUTOTARGET="Auto-target: ";

	const std::string BUTTON_TEXT_PAUSE="Pause: ";
	const std::string BUTTON_TEXT_INGAME_MENU="Menu: ";
	//---
	const std::string BUTTON_NAME_FORWARD="OUANOptions/Controls/ForwardBtn";
	const std::string BUTTON_NAME_BACKWARDS="OUANOptions/Controls/BackwardsBtn";
	const std::string BUTTON_NAME_LEFT="OUANOptions/Controls/LeftBtn";
	const std::string BUTTON_NAME_RIGHT="OUANOptions/Controls/RightBtn";

	const std::string BUTTON_NAME_JUMP="OUANOptions/Controls/JumpBtn";
	const std::string BUTTON_NAME_ACTION="OUANOptions/Controls/ActionBtn";
	const std::string BUTTON_NAME_USEWEAPON="OUANOptions/Controls/WeaponBtn";
	const std::string BUTTON_NAME_RELOAD="OUANOptions/Controls/ReloadBtn";

	const std::string BUTTON_NAME_LROTATE="OUANOptions/Controls/RotateLeftBtn";
	const std::string BUTTON_NAME_RROTATE="OUANOptions/Controls/RotateRightBtn";
	const std::string BUTTON_NAME_WALK="OUANOptions/Controls/WalkBtn";
	const std::string BUTTON_NAME_AUTOTARGET="OUANOptions/Controls/AutoTargetBtn";

	const std::string BUTTON_NAME_PAUSE="OUANOptions/Controls/PauseBtn";
	const std::string BUTTON_NAME_MENU="OUANOptions/Controls/MenuBtn";

	typedef struct 
	{
		std::string keyMapping;
		std::string buttonText;
	} TButtonData;

	typedef std::map<std::string, TButtonData> TButtonDataMapping;
	///State corresponding to the game options selection menu
	class GameOptionsState: public GameState{
	public:
		/// init game options screen's resources
		void init(ApplicationPtr app);

		/// Clean up game options screen's resources
		void cleanUp();

		/// pause state
		void pause();
		/// resume state
		void resume();

		/// process input events
		/// @param app	the parent application
		void handleEvents();
		/// Update game according to the current state
		/// @param app	the parent app
		void update(long elapsedTime);

		bool keyPressed( const OIS::KeyEvent& e );
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );

		/// Default constructor
		GameOptionsState();
		/// Destructor
		~GameOptionsState();

		bool onBackToMenu(const CEGUI::EventArgs& args);
		bool onRadioButtonStateChange(const CEGUI::EventArgs& args);
		bool onApply (const CEGUI::EventArgs& args);
		bool onCancel (const CEGUI::EventArgs& args);
		bool onDeviceSelectionChanged(const CEGUI::EventArgs& args);
		bool onRadioButtonDown(const CEGUI::EventArgs& args);

	private:
		TControlInputMapping mCurrentConfig;
		TControlInputMapping mNewConfig;
		bool mExpectingPress;
		std::string mCurrentlyEditedMapping;
		TInputDevice mCurrentlyEditedDevice;

		TButtonDataMapping mButtonData;

		void initTextButtons();
		void bindEvents();
		void initButton(const std::string& buttonName, const std::string& buttonText, 
			const std::string& mappingName, TButtonDataMapping& buttonData);
	};
}
#endif