#ifndef INTROSTATEH_H
#define INTROSTATEH_H
#include "../OUAN.h"
#include "GameState.h"

namespace OgreUtils
{
	class DirectShowMovieTexture;
}
namespace OUAN
{
	const std::string INTRO_MOVIE="Onceuponanight.avi";	
	const std::string VIDEO_PATH="../../Resources/Graphics/Video/";

	//Default image to show when the video file has not been found
	const std::string DEFAULT_IMG="ouan-nologo-bg.png";
	const std::string MOVIE_MATERIAL_NAME="Movie";
	const std::string MOVIE_MATERIAL_GROUP="General";
	const std::string SCREEN_SCENE_NODE="Screen";
	
	const double IMAGE_DELAY=5;//time in seconds the fallback image will be displayed


	///State corresponding to the game's main menu
	class IntroState: public GameState, public boost::enable_shared_from_this<IntroState>{
	private:
		OgreUtils::DirectShowMovieTexture* mMovieTexture;
		Ogre::Rectangle2D* mScreen;
		double mDelay;

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
		bool keyPressed( const OIS::KeyEvent& e );
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);

		GameStateType getGameStateType();

		/// Default constructor
		IntroState();
		/// Destructor
		~IntroState();

	};
}
#endif
