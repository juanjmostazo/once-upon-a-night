#ifndef EXTRASSTATEH_H
#define EXTRASSTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	const std::string EXTRAS_IMG="background_sky.png";
	const std::string EXTRAS_MATERIAL_NAME="ExtrasBg";
	const std::string EXTRAS_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string EXTRAS_SCREENNODE="ExScreen";
	const std::string EXTRAS_STARS_SCREENNODE="ExScreenC";
	const std::string EXTRAS_CLOUDS_SCREENNODE="ExScreenS";


	const std::string EXTRAS_CLOUDS_MATERIAL_NAME="MenuClouds";
	const std::string EXTRAS_STARS_MATERIAL_NAME="MenuStars";

	///State corresponding to the game's extras menu
	class ExtrasState: public GameState, public boost::enable_shared_from_this<ExtrasState>{
	private:
		GUIExtrasMenuPtr mGUI;

		Ogre::Rectangle2D* mScreen;
		Ogre::Rectangle2D* mStars;
		Ogre::Rectangle2D* mClouds;

		int mClickChannel;

		bool mTransitioning;
		bool mSkipFrame;
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

		void startTransitioning();

	};
}
#endif