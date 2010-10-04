#include "OUAN_Precompiled.h"

#include "IntroState.h"
using namespace OUAN;

#include "../Application.h"
#include "../Graphics/VideoPlayer/OgreDirectShow.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Utils/Utils.h"

#include "MainMenuState.h"
#include "GameStateManager.h"


/// Default constructor
IntroState::IntroState()
:GameState()
,mMovieTexture(NULL)
,mScreen(NULL)
,mDelay(0)
,mTransitioning(false)
,mFrameSkip(false)
,mMovieFinished(false)
{	
}
/// Destructor
IntroState::~IntroState()
{

}

/// init main menu's resources
void IntroState::init(ApplicationPtr app)
{
	GameState::init(app);

	//m_sceneManager->setAmbientLight(ColourValue(0.7,0.8,0.9));
	mMovieTexture=new OgreUtils::DirectShowMovieTexture(640, 480);
	try
	{
		mMovieTexture->loadMovie(VIDEO_PATH+INTRO_MOVIE);
		Ogre::Vector2 movDim = mMovieTexture->getMovieDimensions();
		//This hack is used to retrieve the actual movie dimensions. Apparently, it prevents
		//the app from crashing when loading large files.
		delete mMovieTexture;
		mMovieTexture = new OgreUtils::DirectShowMovieTexture(movDim.x, movDim.y);

		mMovieTexture->loadMovie(VIDEO_PATH+INTRO_MOVIE);
	}
	catch (std::exception& e)
	{
		std::string ex(e.what());
		Logger::getInstance()->log("ERROR loading movie. A fallback image will be shown instead: " + ex);
		mMovieTexture=NULL;
		mDelay=IMAGE_DELAY;
	}
	//Ogre::Vector2 movDim = mMovieTexture->getMovieDimensions();
	//delete mMovieTexture;
	//mMovieTexture = new OgreUtils::DirectShowMovieTexture(movDim.x, movDim.y);
	//mMovieTexture->loadMovie(MOVIE_PATH);
	Utils::TTexturedRectangleDesc desc;
	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_BACKGROUND;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=MOVIE_MATERIAL_NAME;
	desc.materialGroup=MOVIE_MATERIAL_GROUP;
	desc.textureName=mMovieTexture
		?mMovieTexture->getMovieTexture()->getName()
		:DEFAULT_IMG;
	desc.sceneNodeName=SCREEN_SCENE_NODE;
	Utils::createTexturedRectangle(desc,mScreen,mApp->getRenderSubsystem());

	desc.leftCorner=desc.bottomCorner=-1.0;
	desc.rightCorner=desc.topCorner=1.0;
	desc.renderQueue=Ogre::RENDER_QUEUE_9;
	desc.axisAlignedBox=Ogre::AxisAlignedBox::BOX_INFINITE;
	desc.materialName=CLOUDS_MATERIAL_NAME;
	desc.materialGroup=MOVIE_MATERIAL_GROUP;	
	desc.sceneNodeName=CLOUDS_SCENE_NODE;
	Utils::createRectangle(desc,mClouds,mApp->getRenderSubsystem());

	mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setCurrentFrame(0);


	if (mMovieTexture)
		mMovieTexture->playMovie();

	mTransitioning=false;
	mFrameSkip=false;
}

/// Clean up main menu's resources
void IntroState::cleanUp()
{
	GameState::cleanUp();

	Utils::destroyTexturedRectangle(mScreen,MOVIE_MATERIAL_NAME,mApp->getRenderSubsystem());
	if (mMovieTexture)
	{
		delete mMovieTexture;
		mMovieTexture=NULL;	
	}	
	Utils::destroyRectangle(mClouds,mApp->getRenderSubsystem());
}

/// pause state
void IntroState::pause()
{

}
/// resume state
void IntroState::resume()
{
	GameState::resume();
}
bool IntroState::keyPressed(const OIS::KeyEvent& e)
{
	char charKey=static_cast<char>(e.text);
	bool alphaKey= (charKey>='0' && charKey<='9') ||(charKey>='a' && charKey<='z') || (charKey>='A' && charKey<='Z');
	
	if (!mTransitioning && (e.key==OIS::KC_ESCAPE || e.key==OIS::KC_SPACE || alphaKey))
	{
		if (!mMovieFinished)
			mMovieTexture->pauseMovie();
		startTransitioning();

	}

	return true;
}
bool IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (!mTransitioning && (id==OIS::MB_Left || id==OIS::MB_Right))
	{
		if (!mMovieFinished)
			mMovieTexture->pauseMovie();
		startTransitioning();
	}
	return true;
}

/// process input events
/// @param app	the parent application
void IntroState::handleEvents()
{

}

/// Update game according to the current state
/// @param app	the parent app
void IntroState::update(long elapsedTime)
{
	GameState::update(elapsedTime);

	if (mMovieTexture)
	{
		if (!mMovieFinished)
		{
			mMovieTexture->updateMovieTexture(mMovieFinished);
		}
		else if (mMovieFinished && !mTransitioning)
		{	
			mMovieTexture->pauseMovie();
			startTransitioning();
		}
	}
	else
	{
		mDelay-=(elapsedTime*0.000001);
		if (mDelay<=0 && !mTransitioning)
		{
			startTransitioning();
		}
	}
	Ogre::TextureUnitState* tex=mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);

	if (tex && mClouds->isVisible())
	{
		int currentFrame=tex->getCurrentFrame();
		if (mTransitioning)
		{			
			if (currentFrame-1<=0)
			{
				GameStatePtr nextState(new MainMenuState());
				mApp->getGameStateManager()->changeState(nextState,mApp);
			}
			else
			{
				if (!mFrameSkip)
				{
					tex->setCurrentFrame(currentFrame-1);
				}
			}
		}
		else
		{			
			if (currentFrame+1==tex->getNumFrames())
			{
				mClouds->setVisible(false);
			}
			else {
				if (!mFrameSkip)
				{
					tex->setCurrentFrame(currentFrame+1);
				}
			}
		}
	}	
	mFrameSkip=!mFrameSkip;//HACK TO KEEP THE ANIMATION RUNNING LONGER
}

void IntroState::startTransitioning()
{
	mTransitioning=true;
	Ogre::TextureUnitState* tex=mClouds->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0);
	mClouds->setVisible(true);
	tex->setCurrentFrame(tex->getNumFrames()-1);
}