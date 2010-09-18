#ifndef LEVELLOADINGSTATEH_H
#define LEVELLOADINGSTATEH_H
#include "GameState.h"
namespace OUAN
{
	const std::string LEVELLOAD_IMG="ouan-loading-bg.png";
	const std::string LEVELLOAD_MATERIAL_NAME="OUAN/LevelLoad/Background";
	const std::string LEVELLOAD_GROUP=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const std::string LEVELLOAD_SCREENNODE="LLScreen";
	const std::string LEVELLOAD_BAR_IMG="ouan-loading-bar-fill.png";
	const std::string LEVELLOAD_BAR_MATERIAL_NAME="OUAN/LevelLoad/Bar";
	const std::string LEVELLOAD_BAR_NODE="LLBar";

	class LevelLoadingState;
	typedef boost::shared_ptr<LevelLoadingState> LevelLoadingStatePtr;

	typedef void (LevelLoadingState::*FP_LOADING_STAGE)();
	
	struct TLoadingStage
	{
		FP_LOADING_STAGE stageFunction;
		std::string stageName;
		double stagePercent;
	};

	///State corresponding to the game's main menu
	class LevelLoadingState: public GameState, public boost::enable_shared_from_this<LevelLoadingState>
	{
		private:

			int mMusicChannel;

			Ogre::Rectangle2D* mScreen;
			Ogre::Rectangle2D* mBar;

			double mTotalWidth;
			double mAccumPercent;
			double mGameObjectWidth;

			double leftCorner;
			double topCorner;
			double rightCorner;
			double bottomCorner;
			double currentRightCorner;

			int currentStage;

			std::string mLevelFilename;

			XMLGameObjectContainerIterator mGameObjectIterator;
			bool mIteratorInUse;
			bool mProcessingGameObjects;

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

			/// Default constructor
			LevelLoadingState();
			/// Destructor
			~LevelLoadingState();

			void processStage(const TLoadingStage& stage);

			GameStateType getGameStateType();

			void setLevelFileName(const std::string& levelFilename);

			void unloadAll();
			void initPhysics();
			void resetTrajectories();
			void initParser();
			void processSceneNodes();
			void processGameObjects();
			void processGameObject();
			void processFractalClouds();
			void processBillboardClouds();
			void processTrajectories();
			void processWalkabilityMap();
			void initMaterials();
			void initMusic();
			void initScripts();
			void setCameraTarget();
			void clearParser();
			void resolveLinks();
			void loadFlashlightDecalMaterials();
			//...
	};
}
#endif