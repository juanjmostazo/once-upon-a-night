#ifndef GAMEOVERSTATEH_H
#define GAMEOVERSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string OVERLAY_GAMEOVER_SCREEN="OUAN/GameOverOverlay";
	/// State that'll be loaded when the player's died and exhausted
	/// all of its lives
	class GameOverState: public GameState{
	public:
		/// init game over state's resources
		void init(ApplicationPtr app);

		/// free game over state's resources
		void cleanUp();

		/// pause state
		void pause();
		/// resume state
		void resume();

		GameStateType getGameStateType();

		/// process input events
		/// @param app	the parent application
		void handleEvents();
		/// Update game according to the current state
		/// @param app	the parent app
		void update(long elapsedTime);

		/// Default constructor
		GameOverState();
		/// Destructor
		~GameOverState();

		bool render();

	};
}
#endif