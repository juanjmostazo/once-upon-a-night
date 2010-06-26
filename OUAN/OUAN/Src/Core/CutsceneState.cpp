#include "OUAN_Precompiled.h"

#include "CutsceneState.h"
#include "GameStateManager.h"
#include "../Application.h"
using namespace OUAN;

/// Default constructor
CutsceneState::CutsceneState()
:mCoroutine(NULL)
,mCutsceneFile("")
,mCutsceneFunction("")
,mCutsceneLaunched(false)
{

}
/// Destructor
CutsceneState::~CutsceneState()
{

}

void CutsceneState::init(ApplicationPtr app)
{
	mApp=app;
	
	//luabind::resume_function()
}

/// Clean up extras screen's resources
void CutsceneState::cleanUp()
{

}

/// pause state
void CutsceneState::pause()
{

}
/// resume state
void CutsceneState::resume()
{

}

/// process input events
/// @param app	the parent application
void CutsceneState::handleEvents()
{
	if (mApp->mKeyBuffer<0)
	{
		if (mApp->isPressedMenu() || mApp->isPressedJump() )
		{
			skipCutscene();
		}
	}

}
/// Update game according to the current state
/// @param app	the parent app
void CutsceneState::update(long elapsedTime)
{
	if (!mCutsceneLaunched)
	{
		//luabind::resume_function(mCoroutine,"test");

	}
}

void CutsceneState::skipCutscene()
{
	//Advance to final state.
	mApp->getGameStateManager()->popState();
}
void CutsceneState::setCutsceneFile(const std::string& file)
{
	mCutsceneFile=file;
	}