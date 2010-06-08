#include "OUAN_Precompiled.h"

#include "ExtrasState.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Audio/AudioSubsystem.h"
#include "../GUI/GUISubsystem.h"
#include "../GUI/GUIExtrasMenu.h"
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
	mApp=app;

	mScreen= new Ogre::Rectangle2D(true);
	mScreen->setCorners(-1.0, 1.0, 1.0, -1.0);	//Full screen
	mScreen->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
	mScreen->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(EXTRAS_MATERIAL_NAME, EXTRAS_GROUP);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(EXTRAS_IMG);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mScreen->setMaterial(EXTRAS_MATERIAL_NAME);

	RenderSubsystemPtr renderSS =mApp->getRenderSubsystem(); 
	Ogre::SceneNode* screenNode;
	if (!renderSS->getSceneManager()->hasSceneNode(EXTRAS_SCREENNODE))
	{
		screenNode= renderSS->getSceneManager()->getRootSceneNode()->createChildSceneNode(EXTRAS_SCREENNODE);
	}
	else
	{
		screenNode= renderSS->getSceneManager()->getSceneNode(EXTRAS_SCREENNODE);
	}
	screenNode ->attachObject(mScreen);

	mGUI=boost::dynamic_pointer_cast<GUIExtrasMenu>(mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_EXTRAS));
	mGUI->initGUI(shared_from_this());
}

/// Clean up main menu's resources
void ExtrasState::cleanUp()
{
	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	if (Ogre::MaterialManager::getSingleton().resourceExists(EXTRAS_MATERIAL_NAME))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(EXTRAS_MATERIAL_NAME);
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

}
void ExtrasState::backToMenu()
{
	/*GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);*/
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	mApp->getGameStateManager()->popState();
}