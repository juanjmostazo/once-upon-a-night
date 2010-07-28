#include "OUAN_Precompiled.h"

#include "ExtrasState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIExtrasMenu.h"
#include "../Utils/Utils.h"
#include "GameStateManager.h"

#include "MainMenuState.h"

using namespace OUAN;


/// Default constructor
ExtrasState::ExtrasState()
:GameState()
,mClickChannel(-1)
{

}
/// Destructor
ExtrasState::~ExtrasState()
{

}

/// init main menu's resources
void ExtrasState::init(ApplicationPtr app)
{
	GameState::init(app);

	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_BACKGROUND;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=EXTRAS_MATERIAL_NAME;
	desc.materialGroup=EXTRAS_GROUP;
	desc.textureName=EXTRAS_IMG;
	desc.sceneNodeName=EXTRAS_SCREENNODE;

	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());

	mGUI=BOOST_PTR_CAST(GUIExtrasMenu,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_EXTRAS));
	mGUI->initGUI(shared_from_this());
}

/// Clean up main menu's resources
void ExtrasState::cleanUp()
{
	GameState::cleanUp();

	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	Utils::destroyTexturedRectangle(mScreen, EXTRAS_MATERIAL_NAME,mApp->getRenderSubsystem());	
}

/// pause state
void ExtrasState::pause()
{

}
/// resume state
void ExtrasState::resume()
{

}

/// process input events
/// @param app	the parent application
void ExtrasState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void ExtrasState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
}

void ExtrasState::backToMenu()
{
	/*GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);*/
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	mApp->getGameStateManager()->popState();
}