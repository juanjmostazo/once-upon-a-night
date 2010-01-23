#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

#include "Input/FullInputManager.h"

const int AI_FPS=40;
const int SKIP_TICKS=1000/AI_FPS;
const int MAX_FRAMESKIP=5;

const float DEFAULT_MOVE_SPEED = 1;
const float DEFAULT_ROTATE_SPEED=0.3f;
const float MOUSE_MOVE_ROTATION_INCREMENT=0.1f;

const int DEFAULT_MIPMAPS_NUMBER=5;

const std::string DEFAULT_WIN_NAME="Demo Application";
const std::string MAIN_CAMERA_NAME="Camera";
const std::string DEFAULT_RESOURCES_PATH="../../Config/resources.cfg";

//Fetch the plugins file conditionally, depending on whether we're on debug mode or not
#ifdef OUAN_DEBUG
	const std::string DEFAULT_PLUGINS_PATH="../../Config/plugins-dbg.cfg";
#else
	const std::string DEFAULT_PLUGINS_PATH="../../Config/plugins.cfg";
#endif

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
	class Camera;
	class Viewport;
	class FrameListener;
}

class FullInputManager;
//-- 
class Application: FullInputManager
{
public:
	Application(Ogre::String windowName=DEFAULT_WIN_NAME);
	virtual ~Application();

	virtual void initialise();
	virtual void go();
	virtual void cleanUp();

	//Event handling
	virtual bool keyPressed( const OIS::KeyEvent& e );
	virtual bool keyReleased(const OIS::KeyEvent& e);
	virtual bool mouseMoved(const OIS::MouseEvent &e);
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );
	virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button );

	//Scene configuration
	virtual void createScene();
	virtual void createCameras();
	virtual void createViewports();

	//Game update methods
	virtual void updateLogic(long elapsedTime);
	virtual void updateGraphics(float interpolation);

protected:
	//Rendering engine setup methods
	void createRoot();
	void defineResources();
	void setupRenderSystem();
	void createRenderWindow();
	void initialiseResourceGroups();
	void setupScene();
	void setupInputSystem();

	//Rendering engine auxiliary methods
	virtual void moveCamera();
	virtual void getInput();


	bool m_exitRequested;

	Ogre::String m_windowName;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;

	//Attributes used to handle the default
	//camera movements
	Ogre::Vector3			m_TranslateVector;
	Ogre::Real				m_MoveSpeed; 
	Ogre::Degree			m_RotateSpeed; 
	float					m_MoveScale; 
	Ogre::Degree			m_RotScale;


};

#endif
