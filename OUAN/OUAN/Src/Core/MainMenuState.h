#ifndef MAINMENUSTATEH_H
#define MAINMENUSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	typedef std::vector<CEGUI::Event::Connection> TGUIConnections;

	const std::string MAINMENU_IMG="ouan-background-logo.png";
	const std::string MAINMENU_MATERIAL_NAME="MainMenuBg";
	const std::string MAINMENU_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string MAINMENU_SCREENNODE="MMScreen";

	///State corresponding to the game's main menu
	class MainMenuState: public GameState, public boost::enable_shared_from_this<MainMenuState>{
	private:
		int mMusicChannel;
		int mClickChannel;
		
		Ogre::Rectangle2D* mScreen;
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

		GUIMainMenuPtr mGUI;

		void gotoPlay();
		void gotoOptions();
		void gotoExtras();
		void quit();		
		
		/// Default constructor
		MainMenuState();
		/// Destructor
		~MainMenuState();

	};
}
#endif