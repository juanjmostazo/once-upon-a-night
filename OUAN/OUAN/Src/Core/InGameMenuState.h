#ifndef INGAMEMENUSTATEH_H
#define INGAMEMENUSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	///State corresponding to the game's extras menu
	class InGameMenuState: public GameState, public boost::enable_shared_from_this<InGameMenuState>
	{
	private:
		GUIInGamePtr mGUI;
		int mClickChannel;
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

		GameStateType getGameStateType();

		/// Default constructor
		InGameMenuState();
		/// Destructor
		~InGameMenuState();

		void backToGame();
		void goToOptions();
		void backToMenu();
		void quit();
	};
}
#endif