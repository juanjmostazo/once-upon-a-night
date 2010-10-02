#ifndef GAMEOVERSTATEH_H
#define GAMEOVERSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string GAMEOVER_WIN_IMG_NAME="congratulations";
	const std::string GAMEOVER_LOSE_IMG_NAME="game_over";
	const std::string GAMEOVER_IMG_EXTENSION=".png";
	const std::string GAMEOVER_MATERIAL_NAME="GameOverMaterial";
	const std::string GAMEOVER_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string GAMEOVER_SCREENNODE="GOScreen";

	const std::string GAMEOVER_BG_MATERIAL_NAME="gobmaterial";
	const std::string GAMEOVER_BG_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string GAMEOVER_BG_SCREENNODE="GOBgScreen";
	/// State that'll be loaded when the player's died and exhausted
	/// all of its lives
	class GameOverState: public GameState{
		private:
			Ogre::Rectangle2D* mScreen;
			Ogre::Rectangle2D* mBackground;

		public:
			/// init game over state's resources
			void init(ApplicationPtr app);

			/// free game over state's resources
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
			GameOverState();
			/// Destructor
			~GameOverState();

	};
}
#endif