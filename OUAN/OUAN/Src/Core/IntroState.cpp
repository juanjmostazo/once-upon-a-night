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
{	
}
/// Destructor
IntroState::~IntroState()
{

}

/// init main menu's resources
void IntroState::init(ApplicationPtr app)
{
	mApp=app;
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


	if (mMovieTexture)
		mMovieTexture->playMovie();
}

/// Clean up main menu's resources
void IntroState::cleanUp()
{
	Utils::destroyTexturedRectangle(mScreen,MOVIE_MATERIAL_NAME,mApp->getRenderSubsystem());
	if (mMovieTexture)
	{
		delete mMovieTexture;
		mMovieTexture=NULL;	
	}	
}

/// pause state
void IntroState::pause()
{

}
/// resume state
void IntroState::resume()
{

}
bool IntroState::keyPressed( const OIS::KeyEvent& e )
{
	char charKey=static_cast<char>(e.text);
	bool alphaKey= (charKey>='0' && charKey<='9') ||(charKey>='a' && charKey<='z') || (charKey>='A' && charKey<='Z');
	
	if (mApp->getKeyBuffer() <= 0 &&(e.key==OIS::KC_ESCAPE || alphaKey))
	{
		GameStatePtr nextState(new MainMenuState());
		mApp->getGameStateManager()->changeState(nextState,mApp);	
	}

	return true;
}
bool IntroState::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (id==OIS::MB_Left || id==OIS::MB_Right)
	{
		GameStatePtr nextState(new MainMenuState());
		mApp->getGameStateManager()->changeState(nextState,mApp);
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
	if (mMovieTexture)
	{
		bool finished=false;
		mMovieTexture->updateMovieTexture(finished);
		if (finished)
		{			
			GameStatePtr nextState(new MainMenuState());
			mApp->getGameStateManager()->changeState(nextState,mApp);		
		}
	}
	else
	{
		mDelay-=(elapsedTime*0.000001);
		if (mDelay<=0)
		{
			GameStatePtr nextState(new MainMenuState());
			mApp->getGameStateManager()->changeState(nextState,mApp);		
		}
	}

	mApp->reduceKeyBuffer(elapsedTime);
}

