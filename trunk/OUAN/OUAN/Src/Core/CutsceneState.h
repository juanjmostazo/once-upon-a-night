#ifndef CUTSCENESTATEH_H
#define CUTSCENESTATEH_H

#include "../OUAN.h"
#include "GameState.h"
namespace OUAN
{
	class CutsceneState;
	typedef boost::shared_ptr<CutsceneState> CutsceneStatePtr;

	class CutsceneState: public GameState, public boost::enable_shared_from_this<CutsceneState>
	{
	private:
		std::string mCutsceneFile;
		std::string mCutsceneFunction;
		bool mCutsceneLaunched;
		bool mSkippingCutscene;
		lua_State* mCoroutine;
		static CutsceneState* mInst;
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

		bool render();

		/// Default constructor
		CutsceneState();
		/// Destructor
		~CutsceneState();
		
		void setCutsceneFile(const std::string& file);
		void setCutsceneFunction (const std::string& function);

		static bool isSkippingCutscene();
	};
}
#endif
