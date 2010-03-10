#ifndef GAMEOPTIONSSTATEH_H
#define GAMEOPTIONSSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	//TODO: TAKE ME OUT OF HERE 
	typedef enum{
		DEVICE_KEYB_MOUSE=0,
		DEVICE_PAD_PSX,
	} TInputDevice;
	typedef std::map<std::string,std::pair<int*,int*>> TControlInputMapping;
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

		bool keyPressed( const OIS::KeyEvent& e );

		/// Default constructor
		GameOptionsState();
		/// Destructor
		~GameOptionsState();

		bool onBackToMenu(const CEGUI::EventArgs& args);
		bool onRadioButtonStateChange(const CEGUI::EventArgs& args);

	private:
		ConfigurationPtr mNewConfig;
		bool mExpectingPress;
		std::string mCurrentlyEditedMapping;
		TInputDevice mCurrentlyEditedDevice;
	};
}
#endif