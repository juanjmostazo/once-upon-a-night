#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include "OUAN.h"
#include "Input/ControlInputManager.h"
#include <boost/smart_ptr/enable_shared_from_this.hpp>

namespace OUAN
{
	/// Main application class which will hold all of the game's
		/// subsystems.
		class Application: public ControlInputManager, public boost::enable_shared_from_this<Application>
		{
		public:
			///Constructor
			/// @param windowName the name of the window
			Application(const std::string& windowName=DEFAULT_WIN_NAME);
			/// Destructor
			virtual ~Application();

			/// Load configuration and initialise all subsystems and global
			/// resources
			/// [TODO] Add optional command line string parameter
			virtual void initialise();

			/// Run application
			virtual void go();

			/// Shut down all subsystems and free global resources
			virtual void cleanUp();

			//----------------------------------------------
			//Event handling
			//----------------------------------------------
			
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

			/// Input system initialisation
			void setupInputSystem();

			//Getters		
			GameStateManagerPtr getGameStateManager() const;
			RenderSubsystemPtr getRenderSubsystem() const;
			GUISubsystemPtr getGUISubsystem() const;
			//OUAN::GUISubsystemPtr getGUISubsystem() const;
			//OUAN::AudioSubsystemPtr getAudioSubsystem() const;

			///Initialise the game state machine
			void loadInitialState();

			/// Determine if there has been a request to shut down the app
			bool mExitRequested;
		protected:


			/// Pointer to the game state manager
			GameStateManagerPtr mStateManager;	
			/// Pointer to the render subsystem
			RenderSubsystemPtr mRenderSubsystem;
			/// Pointer to the GUI subsystem
			GUISubsystemPtr mGUISubsystem;

			/// Pointer to the global configuration map
			ConfigurationPtr mConfiguration;

			/// Name of the application window
			std::string mWindowName;
		};
}
#endif
