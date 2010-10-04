#include "OUAN_Precompiled.h"

#include "MainMenuState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIMainMenu.h"
#include "../Utils/Utils.h"
#include "GameStateManager.h"
#include "GameRunningState.h"
#include "GameOptionsState.h"
#include "LevelLoadingState.h"
#include "ExtrasState.h"

#include "../Audio/AudioDefs.h"
#include "../Audio/AudioSubsystem.h"

using namespace OUAN;

/// Default constructor
MainMenuState::MainMenuState()
:GameState()
,mTransitioningToLoading(false)
,mCurrentCloudFrame(0)
,mCurrentStarsFrame(0)
,mSkipFrame(false)
{
	mMusicChannel=mClickChannel-1;
}
/// Destructor
MainMenuState::~MainMenuState()
{

}

/// init main menu's resources
void MainMenuState::init(ApplicationPtr app)
{
	GameState::init(app);

	mApp->mBackToMenu=false;
	//mApp->getGUISubsystem()->loadScheme("OUANLookSkin.scheme","OUANLook");
	mGUI= BOOST_PTR_CAST(GUIMainMenu,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_MAINMENU));

	mGUI->initGUI(shared_from_this());

	initRects();	
	if (!mApp->getAudioSubsystem()->isLoaded("MUSIC"))
		mApp->getAudioSubsystem()->load("MUSIC",AUDIO_RESOURCES_GROUP_NAME);
	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);
	mApp->getAudioSubsystem()->pauseChannelGroup(SM_CHANNEL_MUSIC_GROUP,false);
	if (!mApp->getAudioSubsystem()->isMusicPlaying(mMusicChannel))
		mApp->getAudioSubsystem()->playMusic("MUSIC",mMusicChannel,true);

}
void MainMenuState::initRects()
{
	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_BACKGROUND;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=MAINMENU_BG_MATERIAL_NAME;
	desc.materialGroup=MAINMENU_GROUP;
	desc.textureName=MAINMENU_BG_IMG;
	desc.sceneNodeName=MAINMENU_BG_SCREENNODE;

	Utils::createRectangle(desc,mScreen,mApp->getRenderSubsystem());
	
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_3;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=MAINMENU_STARS_MATERIAL_NAME;
	desc.materialGroup=MAINMENU_GROUP;
	desc.textureName=MAINMENU_STARS_IMG;
	desc.sceneNodeName=MAINMENU_STARS_SCREENNODE;
	desc.texAnimNumFrames=MAINMENU_STARS_FRAMENUM;
	desc.textureAnimation=true;
	desc.texAnimDuration=2.0;
	desc.alphaBlending=true;

	Utils::createRectangle(desc,mStars,mApp->getRenderSubsystem());

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_9;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=MAINMENU_LOGO_MATERIAL_NAME;
	desc.materialGroup=MAINMENU_GROUP;
	desc.textureName=MAINMENU_LOGO_IMG;
	desc.sceneNodeName=MAINMENU_LOGO_SCREENNODE;
	desc.textureAnimation=false;
	desc.alphaBlending=true;

	Utils::createRectangle(desc,mLogo,mApp->getRenderSubsystem());

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_MAX;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=MAINMENU_CLOUDS_MATERIAL_NAME;
	desc.materialGroup=MAINMENU_GROUP;
	desc.textureName=MAINMENU_CLOUDS_IMG;
	desc.sceneNodeName=MAINMENU_CLOUDS_SCREENNODE;
	desc.texAnimNumFrames=MAINMENU_CLOUDS_FRAMENUM;
	desc.textureAnimation=true;
	desc.texAnimDuration=0;

	Utils::createRectangle(desc,mClouds,mApp->getRenderSubsystem());


	mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setCurrentFrame(0);
		
	mTransitioningToLoading=false;
}
void MainMenuState::destroyRects()
{
	Utils::destroyRectangle(mScreen,mApp->getRenderSubsystem());
	Utils::destroyRectangle(mStars,mApp->getRenderSubsystem());
	Utils::destroyRectangle(mClouds,mApp->getRenderSubsystem());
	Utils::destroyRectangle(mLogo,mApp->getRenderSubsystem());
}

/// Clean up main menu's resources
void MainMenuState::cleanUp()
{
	GameState::cleanUp();

	while(mApp->getAudioSubsystem()->isSfxPlaying(mClickChannel));

	//Unsubscribe from events
	mGUI->destroy();

	if (mMusicChannel!=-1)
	{
		mApp->getAudioSubsystem()->stopMusic(mMusicChannel);
	}

	mApp->getAudioSubsystem()->unload("MUSIC");
	mApp->getAudioSubsystem()->unload("CLICK");
	mApp->getGUISubsystem()->destroyGUI();

	//mApp->getGUISubsystem()->unbindAllEvents();
	destroyRects();
}

/// pause state
void MainMenuState::pause()
{
	//mApp->getGUISubsystem()->hideGUI();
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	destroyRects();

}
/// resume state
void MainMenuState::resume()
{
	GameState::resume();
	//mApp->getGUISubsystem()->showGUI();
	mGUI= BOOST_PTR_CAST(GUIMainMenu,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_MAINMENU));
	mGUI->initGUI(shared_from_this());
	if (!mApp->getAudioSubsystem()->isLoaded("MUSIC"))
		mApp->getAudioSubsystem()->load("MUSIC",AUDIO_RESOURCES_GROUP_NAME);

	if (!mApp->getAudioSubsystem()->isLoaded("CLICK"))
		mApp->getAudioSubsystem()->load("CLICK",AUDIO_RESOURCES_GROUP_NAME);
	if (!mApp->getAudioSubsystem()->isMusicPlaying(mMusicChannel))
		mApp->getAudioSubsystem()->playMusic("MUSIC",mMusicChannel,true);
	
	initRects();
}

/// process input events
/// @param app	the parent application
void MainMenuState::handleEvents()
{
	int pad;
	int key;

	if (mApp->isPressedJump(&pad,&key))
	{
		mApp->cycleLanguage();
		mGUI->setStrings();
	}
}

/// Update game according to the current state
/// @param app	the parent app
void MainMenuState::update(long elapsedTime)
{
	GameState::update(elapsedTime);
		mApp->getAudioSubsystem()->update(elapsedTime*0.000001);

	Ogre::TextureUnitState* tex=mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

	if (tex && mClouds->isVisible())
	{
		int currentFrame=tex->getCurrentFrame();
		if (mTransitioningToLoading)
		{			
			if (currentFrame-1==0)
			{
				gotoPlay();
			}
			else
				if (!mSkipFrame)
				{
					tex->setCurrentFrame(currentFrame-1);
				}
				
		}
		else
		{			
			if (currentFrame+1==tex->getNumFrames())
			{
				mClouds->setVisible(false);
			}
			else 
				if (!mSkipFrame)
				{
					tex->setCurrentFrame(currentFrame+1);
				}
		}
	}	
	mSkipFrame=!mSkipFrame;//HACK TO KEEP THE ANIMATION RUNNING LONGER
}

void MainMenuState::gotoPlay()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	//TODO: Change to ProfileSelectState when it's implemented
	//GameStatePtr nextState(new GameRunningState());
	//GameStatePtr nextState(new LevelLoadingState());
	LevelLoadingStatePtr levelLoadingState(new LevelLoadingState());
	levelLoadingState->setLevelFileName(LEVEL_2);
	mApp->getGameStateManager()->changeState(levelLoadingState,mApp);	
}

void MainMenuState::gotoOptions()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	GameStatePtr nextState(new GameOptionsState());
	//mApp->getGameStateManager()->changeState(nextState,mApp);
	mApp->getGameStateManager()->pushState(nextState,mApp);
}

void MainMenuState::gotoExtras()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	GameStatePtr nextState(new ExtrasState());
	//mApp->getGameStateManager()->changeState(nextState,mApp);
	mApp->getGameStateManager()->pushState(nextState,mApp);
}

void MainMenuState::quit()
{
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	mApp->mExitRequested=true;
}

void MainMenuState::startTransitionToLoading()
{
	mTransitioningToLoading=true;
	mClouds->setVisible(true);
	mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setCurrentFrame(mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getNumFrames()-1);
}
