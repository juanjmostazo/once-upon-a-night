#ifndef MAINMENUSTATEH_H
#define MAINMENUSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	///State corresponding to the game's main menu
	class MainMenuState: public GameState{
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
		
		/// Default constructor
		MainMenuState();
		/// Destructor
		~MainMenuState();

		bool onQuit(const CEGUI::EventArgs& args);
		bool onNew(const CEGUI::EventArgs& args);
		bool onTest(const CEGUI::EventArgs& args);
	private:
		CEGUI::Event::Connection mOnQuitConnection;
		CEGUI::Event::Connection mOnNewConnection;
		CEGUI::Event::Connection mOnTestConnection;
	};
}
#endif