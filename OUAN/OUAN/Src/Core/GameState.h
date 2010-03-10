#ifndef GAMESTATEH_H
#define GAMESTATEH_H

#include "../OUAN.h"
namespace OUAN
{
	typedef	boost::shared_ptr<GameState> GameStatePtr;
	///Abstract class to provide the interface that all game state classes
	///must implement, i.e, initialization/cleanup methods, handling the 
	//main steps of the game loop, and changing the parent application's
	//current state to another one.
	class GameState
	{
	protected:///Default constructor
		GameState();
		ApplicationPtr mApp;
	public:
		///Destructor
		virtual ~GameState();
		/// init the game's resources for the current state
		virtual void init(ApplicationPtr app)=0;
		/// Free those game resources specific to the current state
		virtual void cleanUp()=0;

		/// Pause current state
		virtual void pause()=0;
		/// Resume current state
		virtual void resume()=0;

		/// Handle input events
		/// @param	app	the parent app
		virtual void handleEvents()=0;
		/// Update game according to the current state
		/// @param app	the parent app
		virtual void update(long elapsedTime)=0;
		/// Renders game's visuals to the screen
		/// @param app the parent app
		virtual bool render();

		/// Changes the app's current state from this instance to the 
		/// state passed as an argument
		/// @param app	the parent application
		/// @param nextState state to change to
		void changeState(GameStatePtr nextState);

		/// Process keyboard press input event.
		/// @param e	input event
		/// @return <b>true</b> if event was handled correctly
		virtual bool keyPressed( const OIS::KeyEvent& e );
		/// Process keyboard release input event.
		/// @param e	input event
		/// @return <b>true</b> if event was handled correctly
		virtual bool keyReleased(const OIS::KeyEvent& e);
		/// Process a mouse motion input event.
		/// @param e	input event
		/// @return <b>true</b> if event was handled correctly
		virtual bool mouseMoved(const OIS::MouseEvent &e);
		/// Process a mouse click input event.
		/// @param e	input event
		/// @param id	mouse button id
		/// @return <b>true</b> if event was handled correctly
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		/// Process a mouse button released input event
		/// @param e	input event
		/// @param id	mouse button id
		/// @return <b>true</b> if event was handled correctly
		virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		/// Process a joystick button press input event
		/// @param e		input event
		/// @param button	button identifier
		/// @return <b>true</b> if event was handled correctly
		virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		/// Process a joystick button release input event.
		/// @param e		input event
		/// @param button	button identifier
		/// @return <b>true</b> if event was handled correctly
		virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );	

		/// Return the application pointer
		/// @return the application pointer
		ApplicationPtr getApp() const;
	};
}

#endif
