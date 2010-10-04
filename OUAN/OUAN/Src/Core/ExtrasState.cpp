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
,mTransitioning(false)
,mSkipFrame(false)
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

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_3;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=EXTRAS_STARS_MATERIAL_NAME;
	desc.materialGroup=EXTRAS_GROUP;
	desc.sceneNodeName=EXTRAS_STARS_SCREENNODE;

	Utils::createRectangle(desc,mStars,mApp->getRenderSubsystem());

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_MAX;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=EXTRAS_CLOUDS_MATERIAL_NAME;
	desc.materialGroup=EXTRAS_GROUP;	
	desc.sceneNodeName=EXTRAS_CLOUDS_SCREENNODE;
	Utils::createRectangle(desc,mClouds,mApp->getRenderSubsystem());

		mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setCurrentFrame(0);


	mGUI=BOOST_PTR_CAST(GUIExtrasMenu,mApp->getGUISubsystem()->createGUI(GUI_LAYOUT_EXTRAS));
	mGUI->initGUI(shared_from_this());

	mTransitioning=false;
	mSkipFrame=false;
}

/// Clean up main menu's resources
void ExtrasState::cleanUp()
{
	GameState::cleanUp();

	mGUI->destroy();
	mApp->getGUISubsystem()->destroyGUI();
	Utils::destroyTexturedRectangle(mScreen, EXTRAS_MATERIAL_NAME,mApp->getRenderSubsystem());	
	Utils::destroyRectangle(mStars,mApp->getRenderSubsystem());
	Utils::destroyRectangle(mClouds,mApp->getRenderSubsystem());
}

/// pause state
void ExtrasState::pause()
{

}
/// resume state
void ExtrasState::resume()
{
	GameState::resume();
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
	Ogre::TextureUnitState* tex=mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

	if (tex && mClouds->isVisible())
	{
		int currentFrame=tex->getCurrentFrame();
		if (mTransitioning)
		{			
			if (currentFrame-1==0)
			{
				backToMenu();
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

void ExtrasState::backToMenu()
{
	/*GameStatePtr nextState(new MainMenuState());
	mApp->getGameStateManager()->changeState(nextState,mApp);*/
	mApp->getAudioSubsystem()->playSound("CLICK",mClickChannel);
	mApp->getGameStateManager()->popState();
}

void ExtrasState::startTransitioning()
{
	mTransitioning=true;
	mClouds->setVisible(true);
	mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setCurrentFrame(mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getNumFrames()-1);
}