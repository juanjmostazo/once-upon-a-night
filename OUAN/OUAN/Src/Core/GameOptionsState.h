#ifndef GAMEOPTIONSSTATEH_H
#define GAMEOPTIONSSTATEH_H

#include "GameState.h"
#include "../OUAN.h"
#include "../Input/InputDefs.h"
#include <boost/enable_shared_from_this.hpp>

namespace OUAN
{
	const std::string OPTIONS_IMG="ouan-nologo-bg.png";
	const std::string OPTIONS_MATERIAL_NAME="OptionsBg";
	const std::string OPTIONS_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string OPTIONS_SCREENNODE="OptionsScreen";

	class GameOptionsState: public GameState, 
		public boost::enable_shared_from_this<GameOptionsState>
	{
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
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );

		/// Default constructor
		GameOptionsState();
		/// Destructor
		~GameOptionsState();

		void backToMenu();

	private:
		int mMusicChannel;
		GUIOptionsMenuPtr mGUI;

		Ogre::Rectangle2D* mScreen;

	};
}
#endif