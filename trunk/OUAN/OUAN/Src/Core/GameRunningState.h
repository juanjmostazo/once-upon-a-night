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

	const std::string TEX_HEALTH_HUD_NAME_FULL="HUDHealth03.png";
	const std::string TEX_HEALTH_HUD_NAME_X2="HUDHealth02.png";
	const std::string TEX_HEALTH_HUD_NAME_X1="HUDHealth01.png";
	const std::string TEX_HEALTH_HUD_NAME_EMPTY="HUDHealth00.png";

	const std::string OVERLAY_INGAME_HUD_LIVES_TEXT="OUAN/NumLives";

	const std::string MATERIAL_ROULETTE="OUAN/Hud/Roulette";
	const std::string MATERIAL_HEALTH="OUAN/Hud/Health";

	const int TRANSITION_NFRAMES=2;
	const float TRANSITION_DURATION=0.5f;

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

	const int NUM_HEALTH_POINTS=3;

	///State corresponding to the game's main menu
	class GameRunningState: public GameState, public boost::enable_shared_from_this<GameRunningState>
	{
	private:		
		TRouletteInfoMap mRouletteData;
		TRouletteState mCurrentRouletteState;

		std::string mHealthHudTextures[NUM_HEALTH_POINTS+1];
		
		void initRouletteData();
		void initHealthHud();
		void spinRoulette(bool forward);
		void updateRoulette();		
		bool isRouletteAnimationFinished();
		void updateRouletteHUD();
		void updateHealthHUD();

		GUIConsolePtr mGUI;

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