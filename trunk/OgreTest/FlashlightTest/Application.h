#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

#include "SimpleInputManager.h"

#define DEFAULT_WIN_NAME "Demo Application";
#define MAIN_CAMERA_NAME "Camera"
#define MAIN_CAMERA_SCENENODE_NAME "CameraNode"

const int AI_FPS=40;
const int SKIP_TICKS=1000/AI_FPS;
const int MAX_FRAMESKIP=5;

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
	class Camera;
	class Viewport;
	class FrameListener;
}

class SimpleInputManager;
//-- 
class Application: SimpleInputManager
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

	//Scene configuration
	virtual void createScene();
	virtual void createCameras();
	virtual void createViewports();

	//Game update methods
	virtual void updateLogic(long elapsedTime);
	virtual void updateGraphics(float interpolation);

protected:
	//Setup methods
	void createRoot();
	void defineResources();
	void setupRenderSystem();
	void createRenderWindow();
	void initialiseResourceGroups();
	void setupScene();
	void setupInputSystem();

	//Auxiliary methods
	virtual void moveCamera();
	virtual void getInput();

	bool m_exitRequested;
	Ogre::String m_windowName;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;


	Ogre::Vector3			m_TranslateVector;
	Ogre::Real				m_MoveSpeed; 
	Ogre::Degree			m_RotateSpeed; 
	float					m_MoveScale; 
	Ogre::Degree			m_RotScale;


};

#endif
