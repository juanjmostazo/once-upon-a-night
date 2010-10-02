#include "OUAN_Precompiled.h"

#include "GamePausedState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameStateManager.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"
#include "../Utils/Utils.h"

using namespace OUAN;


/// Default constructor
GamePausedState::GamePausedState()
:GameState()
{

}
/// Destructor
GamePausedState::~GamePausedState()
{

}

/// init main menu's resources
void GamePausedState::init(ApplicationPtr app)
{
	GameState::init(app);

	CameraParametersPtr params= CameraParametersPtr(new CameraParameters());
	mApp->getCameraManager()->setToDefaultCameraParameters(params);
	mApp->getCameraManager()->setCameraTrajectory(params,"camera-map",false,true);

	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_OVERLAY;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=GAMEPAUSED_MATERIAL_NAME;
	desc.materialGroup=GAMEPAUSED_GROUP;
	desc.textureName=GAMEPAUSED_IMG_NAME+"_"+mApp->getCurrentLanguage()+GAMEPAUSED_IMG_EXTENSION;
	desc.sceneNodeName=GAMEPAUSED_SCREENNODE;
	desc.alphaRejection=true;
	desc.alphaRejectionValue=128;
	desc.alphaRejectionFunction=Ogre::CMPF_GREATER;
	desc.alphaToCoverage=true;
	desc.depthWrite=true;

	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());
}

/// Clean up main menu's resources
void GamePausedState::cleanUp()
{
	GameState::cleanUp();
	Utils::destroyTexturedRectangle(mScreen,GAMEPAUSED_MATERIAL_NAME,mApp->getRenderSubsystem());
	mApp->getCameraManager()->setDefaultThirdPersonCamera(false);
}

/// pause state
void GamePausedState::pause()
{

}
/// resume state
void GamePausedState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void GamePausedState::handleEvents()
{
	int pad;
	int key;

	if (mApp.get() && mApp->isPressedPause(&pad,&key))
	{
		mApp->getGameStateManager()->popState();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GamePausedState::update(long elapsedTime)
{
	GameState::update(elapsedTime);

	mApp->getCameraManager()->update(elapsedTime*0.000001);
}

