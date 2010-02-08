#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#define SAFEDELETE(ptr) if(ptr){ delete ptr;ptr=NULL;}

#include "SimpleInputManager.h"
#include <CEGUI/CEGUI.h>
#include <OgreCEGUIRenderer.h>

#define DEFAULT_WIN_NAME "Demo Application";
#define MAIN_CAMERA_NAME "Camera"
#define MAIN_CAMERA_SCENENODE_NAME "CameraNode"

const int FPS = 30;
const int SKIP_TICKS = 1000/FPS;
const int MAX_LOOPS=10;

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
	virtual void setupCEGUI();
	virtual void setupOverlay();


	//Game update methods
	virtual void updateLogic(float elapsedTime);
	virtual void updateGraphics(float elapsedTime);
	virtual void updateStats();

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
	bool m_showDebugInfo;

	Ogre::String m_windowName;
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;

	CEGUI::OgreCEGUIRenderer* m_renderer;
	CEGUI::System* m_system;
	CEGUI::Window *m_debugWindow;

	Ogre::Overlay* m_debugOverlay;


	Ogre::Vector3			m_TranslateVector;
	Ogre::Real				m_MoveSpeed; 
	Ogre::Degree			m_RotateSpeed; 
	float					m_MoveScale; 
	Ogre::Degree			m_RotScale;


};

#endif
