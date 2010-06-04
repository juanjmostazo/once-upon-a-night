#include "GameOptionsState.h"
#include "../Application.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIOptionsMenu.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "GameStateManager.h"

#include "MainMenuState.h"
#include <sstream>

using namespace OUAN;


/// Default constructor
GameOptionsState::GameOptionsState()
:GameState()
{
	mMusicChannel=-1;
}
/// Destructor
GameOptionsState::~GameOptionsState()
{

}

/// init main menu's resources
void GameOptionsState::init(ApplicationPtr app)
{
	using namespace CEGUI;
	mApp=app;		
	mGUI= boost::dynamic_pointer_cast<GUIOptionsMenu>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_OPTIONS));
	mGUI->initGUI(shared_from_this());

	mScreen= new Ogre::Rectangle2D(true);
	mScreen->setCorners(-1.0, 1.0, 1.0, -1.0);	//Full screen
	mScreen->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
	mScreen->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(OPTIONS_MATERIAL_NAME, OPTIONS_GROUP);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(OPTIONS_IMG);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mScreen->setMaterial(OPTIONS_MATERIAL_NAME);

	RenderSubsystemPtr renderSS =mApp->getRenderSubsystem(); 
	Ogre::SceneNode* screenNode;
	if (!renderSS->getSceneManager()->hasSceneNode(OPTIONS_SCREENNODE))
	{
		screenNode= renderSS->getSceneManager()->getRootSceneNode()->createChildSceneNode(OPTIONS_SCREENNODE);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(OPTIONS_SCREENNODE);
	}
	screenNode ->attachObject(mScreen);

	//mApp->getAudioSubsystem()->load("MUSIC",AUDIO_RESOURCES_GROUP_NAME);
	//mApp->getAudioSubsystem()->playMusic("MUSIC",mMusicChannel,true);
}

/// Clean up main menu's resources
void GameOptionsState::cleanUp()
{
	//mApp->getGUISubsystem()->unbindAllEvents();
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	//if (mMusicChannel!=-1)
	//	mApp->getAudioSubsystem()->stopMusic(mMusicChannel);
	//mApp->getAudioSubsystem()->unload("MUSIC");

	if (Ogre::MaterialManager::getSingleton().resourceExists(OPTIONS_MATERIAL_NAME))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(OPTIONS_MATERIAL_NAME);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(Ogre::String(""));
	}
	if (mScreen)
	{
		std::string sceneNodeName=mScreen->getParentSceneNode()->getName();
		mScreen->detatchFromParent();
		mApp->getRenderSubsystem()->getSceneManager()->destroySceneNode(sceneNodeName);
		delete mScreen;
		mScreen=NULL;
	}
}

/// pause state
void GameOptionsState::pause()
{

}
/// resume state
void GameOptionsState::resume()
{

}

/// process input events
/// @param app	the parent application
void GameOptionsState::handleEvents()
{
}

/// Update game according to the current state
/// @param app	the parent app
void GameOptionsState::update(long elapsedTime)
{
}

void GameOptionsState::backToMenu()
{
	mApp->getGameStateManager()->popState();
	//GameStatePtr nextState(new MainMenuState());
	//mApp->getGameStateManager()->changeState(nextState,mApp);
}
bool GameOptionsState::keyPressed( const OIS::KeyEvent& e )
{
	if (mGUI.get())
	{
		return mGUI->keyPressed(e);
	}
	return false;
}
bool GameOptionsState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (mGUI.get())
	{
		return mGUI->mousePressed(e,id);
	}
	return false;
}

bool GameOptionsState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	if (mGUI.get())
	{
		return mGUI->buttonPressed(e,button);
	}
	return false;
}

