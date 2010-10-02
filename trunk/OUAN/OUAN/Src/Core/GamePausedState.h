#ifndef GAMEPAUSEDSTATEH_H
#define GAMEPAUSEDSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string GAMEPAUSED_IMG_NAME="pause";
	const std::string GAMEPAUSED_IMG_EXTENSION=".png";
	const std::string GAMEPAUSED_MATERIAL_NAME="PauseBg";
	const std::string GAMEPAUSED_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string GAMEPAUSED_SCREENNODE="GPScreen";


	///State corresponding to the game's extras menu
	class GamePausedState: public GameState{
	private:
		Ogre::Rectangle2D* mScreen;
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
		GamePausedState();
		/// Destructor
		~GamePausedState();

	};
}
#endif