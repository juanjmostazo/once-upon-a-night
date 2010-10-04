#ifndef MAINMENUSTATEH_H
#define MAINMENUSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	typedef std::vector<CEGUI::Event::Connection> TGUIConnections;

	const std::string MAINMENU_BG_IMG="background_sky.png";
	const std::string MAINMENU_BG_MATERIAL_NAME="MenuBackground";
	const std::string MAINMENU_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string MAINMENU_BG_SCREENNODE="MMScreen";

	const std::string MAINMENU_CLOUDS_IMG="clouds.png";
	const std::string MAINMENU_CLOUDS_MATERIAL_NAME="MenuClouds";
	const std::string MAINMENU_CLOUDS_SCREENNODE="MMClScreen";
	const int MAINMENU_CLOUDS_FRAMENUM=39;

	const std::string MAINMENU_STARS_IMG="background_stars.png";
	const std::string MAINMENU_STARS_MATERIAL_NAME="MenuStars";
	const std::string MAINMENU_STARS_SCREENNODE="MMStScreen";
	const int MAINMENU_STARS_FRAMENUM=13;

	const std::string MAINMENU_LOGO_IMG="ouan_logo.png";
	const std::string MAINMENU_LOGO_MATERIAL_NAME="MenuLogo";
	const std::string MAINMENU_LOGO_SCREENNODE="LogoScreen";

	///State corresponding to the game's main menu
	class MainMenuState: public GameState, public boost::enable_shared_from_this<MainMenuState>{
	private:
		int mMusicChannel;
		int mClickChannel;

		int mCurrentCloudFrame;
		int mCurrentStarsFrame;

		bool mTransitioningToLoading;
		bool mSkipFrame;
		
		Ogre::Rectangle2D* mScreen;
		Ogre::Rectangle2D* mClouds;
		Ogre::Rectangle2D* mStars;
		Ogre::Rectangle2D* mLogo;
	public:
		/// init main menu's resources
		void init(ApplicationPtr app);

		void initRects();
		void destroyRects();

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

		GUIMainMenuPtr mGUI;

		void gotoPlay();
		void gotoOptions();
		void gotoExtras();
		void quit();	

		void startTransitionToLoading();
		
		/// Default constructor
		MainMenuState();
		/// Destructor
		~MainMenuState();

	};
}
#endif