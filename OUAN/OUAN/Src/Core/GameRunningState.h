#ifndef GAMERUNNINGSTATEH_H
#define GAMERUNNINGSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string OVERLAY_INGAME_HUD = "OUAN/HUDOverlay";
	const std::string OVERLAY_DEBUG_PANEL = "Core/DebugOverlay";
	const std::string SAVED_RTT_FILENAME="../../Resources/Graphics/Textures/savedRTT.png";

	//Take this out to a file
	const std::string TEX_ROULETTE_COLOUR_BLUE="roulette_n_blue.png";
	const std::string TEX_ROULETTE_COLOUR_RED="roulette_n_red.png";
	const std::string TEX_ROULETTE_COLOUR_GREEN="roulette_n_green.png";
	const std::string TEX_ROULETTE_TRANSITION_RG="roulette_n_rg.png";
	const std::string TEX_ROULETTE_TRANSITION_GB="roulette_n_gb.png";
	const std::string TEX_ROULETTE_TRANSITION_BR="roulette_n_br.png";
	const std::string TEX_ROULETTE_TRANSITION_GR="roulette_n_gr.png";
	const std::string TEX_ROULETTE_TRANSITION_RB="roulette_n_rb.png";
	const std::string TEX_ROULETTE_TRANSITION_BG="roulette_n_bg.png";

	const std::string MATERIAL_ROULETTE="OUAN/Hud/Roulette";

	const int TRANSITION_NFRAMES=2;
	const float TRANSITION_DURATION=0.5f;

	const double LOG_REFRESH_TIME=10; //IN SECONDS
	const std::string LOG_NAME="Ogre.log"; //Research Ogre::LogListener class
	const int CONSOLE_MAX_LINES=20;

	typedef enum 
	{
		ROULETTE_TRANSITION_REDGREEN=0,
		ROULETTE_COLOUR_RED,
		ROULETTE_TRANSITION_REDBLUE,
		ROULETTE_TRANSITION_BLUERED,
		ROULETTE_COLOUR_BLUE,
		ROULETTE_TRANSITION_BLUEGREEN,
		ROULETTE_TRANSITION_GREENBLUE,
		ROULETTE_COLOUR_GREEN,
		ROULETTE_TRANSITION_GREENRED
	}TRouletteState;
	const int NUM_ROULETTE_STATES=ROULETTE_TRANSITION_GREENRED-ROULETTE_TRANSITION_REDGREEN+1;

	typedef struct
	{
		std::string textureName;
		bool isAnimated;
		float duration;
		int numFrames;
	} TRouletteInfo;
	typedef std::map<TRouletteState,TRouletteInfo> TRouletteInfoMap;

	///State corresponding to the game's main menu
	class GameRunningState: public GameState{
	private:		
		TRouletteInfoMap mRouletteData;
		TRouletteState mCurrentRouletteState;
		
		void initRouletteData();
		void spinRoulette(bool forward);
		void updateRoulette();		
		bool isRouletteAnimationFinished();
		void updateRouletteHUD();
		
		void setConsoleVisible(bool visible);
		void updateConsole();
		bool isConsoleVisible();

		int mNextLogRefresh;
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

		bool onConsoleCloseClicked(const CEGUI::EventArgs& args);
		void showConsole();
		void hideConsole();

		/// Default constructor
		GameRunningState();
		/// Destructor
		~GameRunningState();
	};
}
#endif