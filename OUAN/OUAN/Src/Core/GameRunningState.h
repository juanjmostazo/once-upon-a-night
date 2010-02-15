#ifndef GAMERUNNINGSTATEH_H
#define GAMERUNNINGSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	///State corresponding to the game's main menu
	class GameRunningState: public GameState{
	public:
		/// Initialise main menu's resources
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

		/// Process keyboard press input event.
		/// @param e	input event
		/// @return <b>true</b> if event was handled correctly
		bool keyPressed( const OIS::KeyEvent& e );
		/// Process a mouse motion input event.
		/// @param e	input event
		/// @return <b>true</b> if event was handled correctly
		bool mouseMoved(const OIS::MouseEvent &e);

		/// Default constructor
		GameRunningState();
		/// Destructor
		~GameRunningState();
	};
}
#endif