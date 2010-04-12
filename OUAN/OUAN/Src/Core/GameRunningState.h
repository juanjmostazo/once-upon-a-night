#ifndef GAMERUNNINGSTATEH_H
#define GAMERUNNINGSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
#include "../Graphics/hud/HUDInGame.h"
namespace OUAN
{
	const std::string OVERLAY_DEBUG_PANEL = "Core/DebugOverlay";
	const std::string SAVED_RTT_FILENAME="../../Resources/Graphics/Textures/savedRTT.png";

	class HUDInGame;
	typedef boost::shared_ptr<HUDInGame> HUDInGamePtr;

	///State corresponding to the game's main menu
	class GameRunningState: public GameState, public boost::enable_shared_from_this<GameRunningState>
	{
	private:		
		GUIConsolePtr mGUI;
		HUDInGamePtr mHUD;

		//Refactored code into functions to improve legibility
		void checkDebuggingKeys();
		void toggleDebugPerformance();
		void toggleDebugPhysics();
		void toggleChangeLevel();
		void changeCameraController();
		void toggleVolumes();

		TWeaponMode convertRouletteValue(TRouletteState rouletteValue);
		TWeaponMode getCurrentWeaponMode();

	public:
		/// init main menu's resources
		void init(ApplicationPtr app);

		/// Clean up main menu's resources
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
		
		/// Renders game's visuals to the screen
		/// @param app the parent app
		bool render();
	
		/// Default constructor
		GameRunningState();
		/// Destructor
		~GameRunningState();
	};
}
#endif