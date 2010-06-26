#ifndef CUTSCENESTATEH_H
#define CUTSCENESTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	class CutsceneState: public GameState, public boost::enable_shared_from_this<CutsceneState>
	{
	private:
		std::string mCutsceneFile;
		std::string mCutsceneFunction;
		bool mCutsceneLaunched;
		lua_State* mCoroutine;
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
		CutsceneState();
		/// Destructor
		~CutsceneState();
		
		void skipCutscene();
		void setCutsceneFile(const std::string& file);
		void setCutsceneFunction (const std::string& function);
	};
}
#endif
