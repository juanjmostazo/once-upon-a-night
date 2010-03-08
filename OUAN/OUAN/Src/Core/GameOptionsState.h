#ifndef GAMEOPTIONSSTATEH_H
#define GAMEOPTIONSSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
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

		/// Default constructor
		GameOptionsState();
		/// Destructor
		~GameOptionsState();

		bool onBackToMenu(const CEGUI::EventArgs& args);

	private:
		ConfigurationPtr mNewConfig;
	};
}
#endif