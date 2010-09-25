#ifndef STORYBOOKSTATEH_H
#define STORYBOOKSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{	
	///State corresponding to the game's extras menu
	class StorybookState: public GameState, public boost::enable_shared_from_this<StorybookState>{
	private:
		GUIStoryBookPtr mGUI;

		int mWhisperChannel,mClickChannel;
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

		/// Default constructor
		StorybookState();
		/// Destructor
		~StorybookState();

	};
}
#endif