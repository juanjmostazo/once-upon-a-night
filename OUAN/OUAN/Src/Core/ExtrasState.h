#ifndef EXTRASSTATEH_H
#define EXTRASSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
#include <boost/enable_shared_from_this.hpp>
namespace OUAN
{
	///State corresponding to the game's extras menu
	class ExtrasState: public GameState, public boost::enable_shared_from_this<ExtrasState>{
	private:
		GUIExtrasMenuPtr mGUI;
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
		ExtrasState();
		/// Destructor
		~ExtrasState();
		void backToMenu();

	};
}
#endif