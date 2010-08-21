#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include "OUAN.h"
#include "GUI/GUIDefs.h"
#include "Audio/AudioDefs.h"
#include "Input/ControlInputManager.h"

namespace OUAN
{
	const std::string SKIP_INTRO_CMD_SHORT="-s";
	const std::string SKIP_INTRO_CMD_LONG="--skipIntro";

	const std::string OUAN_CONFIG_FILE="../../Config/ouan-cfg.xml";

	const std::string DEFAULT_LANGUAGE="en";
	const std::string MENUSSTRINGS_PATH="../../Resources/Text/";
	const std::string MENUSSTRINGS = "menu-strings.xml";
	const std::string INGAME_STRINGS_PATH="../../Resources/Text/";
	const std::string INGAME_STRINGS = "ingame-strings.xml";
	/// Main application class which will hold all of the game's
	/// subsystems.
	class Application: public ControlInputManager, public boost::enable_shared_from_this<Application>
	{
		public:
			///Constructor
			/// @param windowName the name of the window
			Application(const std::string& windowName=DEFAULT_WIN_NAME);
			/// Destructor
			virtual ~Application();

			/// Singleton getter
			static Application* getInstance();

			/// Load configuration and init all subsystems and global
			/// resources
			/// [TODO] Add optional command line string parameter
			bool init();

			bool init(int argc,char** argv);

			/// Run application
			virtual void go();

			/// Shut down all subsystems and free global resources
			virtual void cleanUp();

			//----------------------------------------------
			//Event handling
			//----------------------------------------------
			
			/// Process keyboard press input event.
			/// @param e	input event
			/// @return <b>true</b> if event was handled correctly
			virtual bool keyPressed( const OIS::KeyEvent& e );
			/// Process keyboard release input event.
			/// @param e	input event
			/// @return <b>true</b> if event was handled correctly
			virtual bool keyReleased(const OIS::KeyEvent& e);
			/// Process a mouse motion input event.
			/// @param e	input event
			/// @return <b>true</b> if event was handled correctly
			virtual bool mouseMoved(const OIS::MouseEvent &e);
			/// Process a mouse click input event.
			/// @param e	input event
			/// @param id	mouse button id
			/// @return <b>true</b> if event was handled correctly
			virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
			/// Process a mouse button released input event
			/// @param e	input event
			/// @param id	mouse button id
			/// @return <b>true</b> if event was handled correctly
			virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
			/// Process a joystick button press input event
			/// @param e		input event
			/// @param button	button identifier
			/// @return <b>true</b> if event was handled correctly
			virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
			/// Process a joystick button release input event.
			/// @param e		input event
			/// @param button	button identifier
			/// @return <b>true</b> if event was handled correctly
			virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );		

			/// Input system initialisation
			void setupInputSystem();

			//Getters		
			GameStateManagerPtr getGameStateManager() const;
			RenderSubsystemPtr getRenderSubsystem() const;
			GUISubsystemPtr getGUISubsystem() const;
			PhysicsSubsystemPtr getPhysicsSubsystem() const;
			GameWorldManagerPtr getGameWorldManager() const;
			CameraManagerPtr getCameraManager() const;
			TrajectoryManagerPtr getTrajectoryManager() const;
			RayCastingPtr getRayCasting() const;
			LevelLoaderPtr getLevelLoader() const;
			LogicSubsystemPtr getLogicSubsystem() const;
			AudioSubsystemPtr getAudioSubsystem() const;
			ConfigurationPtr getConfiguration() const;

			ConfigurationPtr getMenusTextStrings() const;
			ConfigurationPtr getIngameTextStrings() const;

			///Return a data structure containing the audio subsystem config information
			void getAudioConfig(TAudioSubsystemConfigData& audioCfg);
			void setAudioConfig(const TAudioSubsystemConfigData& audioCfg);
			void saveAudioConfig(const TAudioSubsystemConfigData& audioCfg);
			void modifyVolume(const std::string& groupName, double volume);
			void modifyEnable(const std::string& groupName, bool isEnabled);

			///init the game state machine
			void loadInitialState();

			/// Set current debug mode
			/// @param debugMode	mask containing the OR-ed value/values
			///						for the desired debug modes to use
			void setDebugMode(int debugMode);
			/// Retrieve the current debug mode state
			/// @return debug mode status (enabled, physics info, ...)
			int getDebugMode() const;

			/// Determine if there has been a request to shut down the app
			bool mExitRequested;

			int mAudioFrameCnt;
			int mAudioFrameSkip;

			/// Used to properly reset the game after selecting the "exit to menu" option
			/// at the in-game menu
			bool mBackToMenu;

			/// Auxiliar functions
			int getUniqueId();
			std::string getStringUniqueId();

			std::vector<std::string>& getSupportedLanguages();
			void changeCurrentLanguage(const std::string& newLanguage);
			void cycleLanguage();
			const std::string& getCurrentLanguage() const;

			bool isPlayingCutscene() const;
			void setPlayingCutscene(bool playingCutscene);

		protected:

			/// Singleton instance
			static Application* instance;

			/// Pointer to the game state manager
			GameStateManagerPtr mStateManager;	
			/// Pointer to the render subsystem
			RenderSubsystemPtr mRenderSubsystem;
			/// Pointer to the GUI subsystem
			GUISubsystemPtr mGUISubsystem;
			/// Pointer to the physics subsystem
			PhysicsSubsystemPtr mPhysicsSubsystem;
			/// Pointer to the game world manager
			GameWorldManagerPtr mGameWorldManager;
			/// Pointer to the scene loader
			LevelLoaderPtr mLevelLoader;

			/// Pointer to the RayCasting module
			RayCastingPtr mRayCasting;

			/// Camera Manager
			CameraManagerPtr mCameraManager;

			/// Pointer to the trajectory manager
			TrajectoryManagerPtr mTrajectoryManager;

			/// Pointer to the logic subsystem instance
			LogicSubsystemPtr mLogicSubsystem;
	
			/// Pointer to the global configuration map
			ConfigurationPtr mConfiguration;

			/// Pointer to the sound manager
			AudioSubsystemPtr mAudioSubsystem;

			/// Name of the application window
			std::string mWindowName;

			/// Debug mode mask: depending on its value, 
			/// certain debug info or rendering modes will be enabled
			int mDebugMode;

			/// Map containing text strings
			ConfigurationPtr mMenusTextStrings;

			/// Map containing text strings
			ConfigurationPtr mIngameTextStrings;

			/// UniqueId
			int mUniqueId;

			/// If true, jump directly to GameRunningState
			bool mSkipIntro;

			std::string mLanguage;
			std::vector<std::string> mSupportedLanguages;

			bool mPlayingCutscene;
		};
}
#endif
