#include "OUAN_Precompiled.h"

#include "GameOverState.h"

#include "GameStateManager.h"
#include "MainMenuState.h"
#include "GameRunningState.h"
#include "LevelLoadingState.h"

#include "../Application.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectViewport.h"
#include "../Audio/AudioSubsystem.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Utils/Utils.h"


using namespace OUAN;


/// Default constructor
GameOverState::GameOverState()
:GameState()
{

}
/// Destructor
GameOverState::~GameOverState()
{

}

/// init main menu's resources
void GameOverState::init(ApplicationPtr app)
{
	GameState::init(app);

	mApp->getGameWorldManager()->getGameObjectViewport()->disableAllCompositors();

	Ogre::TexturePtr tex=Ogre::TextureManager::getSingletonPtr()->load("savedRTT.png",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_BACKGROUND;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=GAMEOVER_BG_MATERIAL_NAME;
	desc.materialGroup=Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	desc.textureName= "savedRTT.png";
	desc.sceneNodeName=GAMEOVER_BG_SCREENNODE;
	Utils::createTexturedRectangle(desc,mBackground,mApp->getRenderSubsystem());



	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_OVERLAY;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=GAMEOVER_MATERIAL_NAME;
	desc.materialGroup=GAMEOVER_GROUP;
	desc.textureName=(mApp->getGameWorldManager()->isGameBeaten()
		?GAMEOVER_WIN_IMG_NAME
		:GAMEOVER_LOSE_IMG_NAME)+"_"+mApp->getCurrentLanguage()+GAMEOVER_IMG_EXTENSION;
	desc.sceneNodeName=GAMEOVER_SCREENNODE;
	desc.alphaRejection=true;
	desc.alphaRejectionValue=128;
	desc.alphaRejectionFunction=Ogre::CMPF_GREATER_EQUAL;
	desc.alphaToCoverage=true;
	desc.depthWrite=true;

	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());

}

/// Clean up main menu's resources
void GameOverState::cleanUp()
{
	GameState::cleanUp();

	mApp->getAudioSubsystem()->unloadAll();
	Utils::destroyTexturedRectangle(mScreen,GAMEOVER_MATERIAL_NAME,mApp->getRenderSubsystem());
	Utils::destroyTexturedRectangle(mBackground,GAMEOVER_BG_MATERIAL_NAME,mApp->getRenderSubsystem());
}

/// pause state
void GameOverState::pause()
{

}
/// resume state
void GameOverState::resume()
{
	GameState::resume();
}

/// process input events
/// @param app	the parent application
void GameOverState::handleEvents()
{
	int pad1,pad2;
	int key1,key2;

	if (mApp.get())
	{
		if (mApp->isPressedJump(&pad1,&key1))
		{

			LevelLoadingStatePtr levelLoadingState(new LevelLoadingState());
			levelLoadingState->setLevelFileName(LEVEL_2);
			mApp->getGameStateManager()->changeState(levelLoadingState,mApp);

		}
		else if (mApp->isPressedPause(&pad2,&key2))
		{
			
			GameStatePtr mainMenuState = GameStatePtr(new MainMenuState());
			mApp->getGameStateManager()->changeState(mainMenuState,mApp);
		}
	}
}

/// Update game according to the current state
/// @param app	the parent app
void GameOverState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
}

