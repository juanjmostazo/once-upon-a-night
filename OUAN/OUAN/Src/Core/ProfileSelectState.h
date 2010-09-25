#ifndef PROFILESELECTSTATEH_H
#define PROFILESELECTSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	///State corresponding to the game's profile selection menu
	class ProfileSelectState: public GameState{
	public:
		/// init profile selection screen's resources
		void init(ApplicationPtr app);

		/// Clean up profile selection screen's resources
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
		ProfileSelectState();
		/// Destructor
		~ProfileSelectState();

	private:
		/// If true, this means the player has selected
		/// an empty slot, so the available options will have
		/// to change accordingly; if false, the slot contains
		/// data, so the player will be able to either resume the
		/// new game or delete the profile
		bool mNewGame;

		/// This variable will hold the name the player's entered on the 
		/// "create profile" dialogue
		std::string mNewProfileName;

		/// Selected slot
		int mSelectedSlot;

	};
}
#endif