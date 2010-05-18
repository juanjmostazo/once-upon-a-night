#include "IntroState.h"
using namespace OUAN;

#include "../Application.h"
#include "../Graphics/VideoPlayer/OgreDirectShow.h"
#include "../Graphics/RenderSubsystem.h"

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
		Ogre::LogManager::getSingletonPtr()->logMessage("ERROR loading movie. A fallback image will be shown instead: " + ex);
		mMovieTexture=NULL;
		mDelay=IMAGE_DELAY;
	}
	//Ogre::Vector2 movDim = mMovieTexture->getMovieDimensions();
	//delete mMovieTexture;
	//mMovieTexture = new OgreUtils::DirectShowMovieTexture(movDim.x, movDim.y);
	//mMovieTexture->loadMovie(MOVIE_PATH);
	mScreen= new Ogre::Rectangle2D(true);
	mScreen->setCorners(-1.0, 1.0, 1.0, -1.0);	//Full screen
	mScreen->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);
	mScreen->setBoundingBox(Ogre::AxisAlignedBox(-100000.0*Ogre::Vector3::UNIT_SCALE, 100000.0*Ogre::Vector3::UNIT_SCALE));
	// Create background material
	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(MOVIE_MATERIAL_NAME, MOVIE_MATERIAL_GROUP);

	material->getTechnique(0)->getPass(0)->createTextureUnitState(mMovieTexture
		?mMovieTexture->getMovieTexture()->getName()
		:DEFAULT_IMG);
	material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
	material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
	material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
	mScreen->setMaterial(MOVIE_MATERIAL_NAME);


	Ogre::SceneNode* screenNode = mApp->getRenderSubsystem()->getSceneManager()->getRootSceneNode()->createChildSceneNode(SCREEN_SCENE_NODE);
	screenNode ->attachObject(mScreen);
	if (mMovieTexture)
		mMovieTexture->playMovie();
}

/// Clean up main menu's resources
void IntroState::cleanUp()
{
	if (Ogre::MaterialManager::getSingleton().resourceExists(MOVIE_MATERIAL_NAME))
	{
		Ogre::MaterialPtr mat;
		Ogre::TextureUnitState* tex;

		mat=Ogre::MaterialManager::getSingleton().getByName(MOVIE_MATERIAL_NAME);
		tex=mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		tex->setTextureName(Ogre::String(""));
	}
	if (mMovieTexture)
	{
		delete mMovieTexture;
		mMovieTexture=NULL;	
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
	if (mApp->mKeyBuffer<=0 &&(e.key==OIS::KC_ESCAPE || alphaKey))
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
	mApp->mKeyBuffer -= elapsedTime;
}

