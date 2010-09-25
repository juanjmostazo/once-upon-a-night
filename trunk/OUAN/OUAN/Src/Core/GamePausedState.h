#ifndef GAMEPAUSEDSTATEH_H
#define GAMEPAUSEDSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string OVERLAY_PAUSE_SCREEN="OUAN/PauseOverlay";
	///State corresponding to the game's extras menu
	class GamePausedState: public GameState{
	public:
		/// init extras screen's resources
		void init(ApplicationPtr app);

		/// Clean up extras screen's resources
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

		/// Render pause screen to the display device
		/// @return true if the rendering operation succeeded.
		bool render();

		/// Default constructor
		GamePausedState();
		/// Destructor
		~GamePausedState();

	};
}
#endif