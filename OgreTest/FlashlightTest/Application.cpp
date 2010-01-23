#include <Ogre.h>

#include "Application.h"

Application::Application(Ogre::String windowName)
: m_root( NULL )
, m_window( NULL )
, m_sceneManager( NULL )
, m_camera( NULL )
, m_viewport( NULL )
, m_exitRequested( false )
, m_TranslateVector(Ogre::Vector3::ZERO)
, m_MoveSpeed(1)
, m_RotateSpeed(0.3f)
, m_windowName(windowName)
{
}

Application::~Application()
{
}
void Application::cleanUp()
{
	SimpleInputManager::finalise();
	SAFEDELETE(m_root);	
}
//Application initialisation
void Application::initialise()
{
	createRoot();
	defineResources();
	setupRenderSystem();
	createRenderWindow();
	initialiseResourceGroups();
	setupScene();
	setupInputSystem();
}
//Run the app
void Application::go()
{
	Ogre::Timer loopTimer;
	bool continueRunning = true;

	long nextGameTicks = loopTimer.getMillisecondsCPU();
	int loops;
	float interpolation;

	while ( continueRunning )
	{
		Ogre::WindowEventUtilities::messagePump();
		SimpleInputManager::capture();

		//The synchronization method follows the 'Constant Game Speed independent of
		//Variable FPS' algorithm described on the article by
		//Koen Witters at http://dev.koonsolo.com/7/dewitters-gameloop/
		//According to it, AI will be updated at a fixed rate, whereas
		//the rendering process will happen as fast as the hardware allows for it.
		//The only drawback is the need for interpolation and prediction 
		//in the rendering method

		// Update logic stuff
		loops=0;
		long elapsedTime=0;
		long currentTime=loopTimer.getMillisecondsCPU();
		while(currentTime>nextGameTicks && loops<MAX_FRAMESKIP)
		{
			elapsedTime=currentTime-elapsedTime;
			updateLogic(elapsedTime);
			nextGameTicks+=SKIP_TICKS;
			loops++;
			currentTime=loopTimer.getMillisecondsCPU();
		}
		interpolation=float(loopTimer.getMillisecondsCPU()+SKIP_TICKS-nextGameTicks)/float(SKIP_TICKS);
		// Update graphics stuff
		updateGraphics(interpolation);


		bool windowClosed = m_window->isClosed();
		continueRunning &= ! windowClosed;
		bool renderFrameSuccess = m_root->renderOneFrame();
		continueRunning &= renderFrameSuccess;

		continueRunning &= ! m_exitRequested;
	}
}
//------------------------
// Input event handling
//------------------------
bool Application::keyPressed( const OIS::KeyEvent& e )
{
	if ( e.key == OIS::KC_ESCAPE )
	{
		m_exitRequested = true;
	}	
	return true;
}
bool Application::keyReleased(const OIS::KeyEvent& e)
{	
	return true;
}
bool Application::mouseMoved(const OIS::MouseEvent &e)
{
	m_camera->yaw(Ogre::Degree(e.state.X.rel * -0.1f));
	m_camera->pitch(Ogre::Degree(e.state.Y.rel * -0.1f));
	return true;
}
bool Application::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}

bool Application::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	return true;
}
//------------------------
// Game setup
//------------------------
void Application::createRoot()
{
	m_root = new Ogre::Root();
}
void Application::defineResources()
{
	Ogre::String sectionName, typeName, resName;
	Ogre::ConfigFile cFile;
	cFile.load("resources.cfg");

	Ogre::ConfigFile::SectionIterator secIt = cFile.getSectionIterator();
	while (secIt.hasMoreElements())
	{
		sectionName = secIt.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for (it=settings->begin();it!=settings->end();++it)
		{
			typeName= it->first;
			resName = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(resName,typeName,sectionName);
		}
	}
}
void Application::setupRenderSystem()
{
	if(!m_root->showConfigDialog())
		throw Ogre::Exception(52,"User canceled the config dialog!", "Application::setupRenderSystem()");
}
void Application::createRenderWindow()
{
	m_root->initialise(true,m_windowName);
	m_window=m_root->getAutoCreatedWindow();
}

void Application::initialiseResourceGroups()
{
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
void Application::setupScene()
{
	m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
	createCameras();
	createViewports();	
	createScene();
}
void Application::setupInputSystem()
{
	SimpleInputManager::initialise( m_window );
}
//------------------------
//Scene setup
//------------------------
void Application::createCameras()
{
	m_camera = m_sceneManager->createCamera(MAIN_CAMERA_NAME);
}
void Application::createViewports()
{
	m_viewport = m_root->getAutoCreatedWindow()->addViewport(m_camera);
	m_viewport->setBackgroundColour(Ogre::ColourValue::Black);
}
void Application::createScene()
{}
void Application::moveCamera()
{
	if(m_keyboard->isKeyDown(OIS::KC_LSHIFT))
		m_camera->moveRelative(m_TranslateVector);
	else
		m_camera->moveRelative(m_TranslateVector / 10);
}
void Application::getInput()
{
	if(m_keyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;

	if(m_keyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;

	if(m_keyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;

	if(m_keyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;
	
	if(m_keyboard->isKeyDown(OIS::KC_Q))
		m_TranslateVector.y = -m_MoveScale;

	if(m_keyboard->isKeyDown(OIS::KC_E))
		m_TranslateVector.y = m_MoveScale;
}

//-------------------------
// Game update
//-------------------------
void	Application::updateGraphics(float interpolation)
{}
void Application::updateLogic(long elapsedTime)
{
	m_MoveScale = m_MoveSpeed   * (float)elapsedTime*0.001;
	m_RotScale  = m_RotateSpeed * (float)elapsedTime*0.001;

	m_TranslateVector = Ogre::Vector3::ZERO;

	getInput();
	moveCamera();
}
