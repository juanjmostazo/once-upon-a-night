#ifndef MAINMENUSTATEH_H
#define MAINMENUSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	typedef std::vector<CEGUI::Event::Connection> TGUIConnections;
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

		bool onPlay(const CEGUI::EventArgs& args);	
		bool onOptions(const CEGUI::EventArgs& args);
		bool onExtras (const CEGUI::EventArgs& args);
		bool onQuit(const CEGUI::EventArgs& args);
	};
}
#endif