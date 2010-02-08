//------------------------------------------------------------------------------
//--
//--	Base application framework initialising Ogre3D's rendering engine.
//--
//--	TODO:	Create a library so the same code doesn't have to be copied and pasted
//--			throughout eeevery other test project
//------------------------------------------------------------------------------

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
///
/// The main application class
///
class Application: SimpleInputManager
{
public:
	/// Constructor: Initialise pointers and sets the window name
	/// @param windowName	name of the window
	Application(Ogre::String windowName=DEFAULT_WIN_NAME);
	/// Destructor
	virtual ~Application();

	/// Initialise the application, as well as all of its subsystems
	virtual void initialise();
	/// Start and run the application's game loop
	virtual void go();
	/// Cleans up resources, pointers and all the app's subsystems
	virtual void cleanUp();

	//Event handling

	/// Process a keyboard press event
	/// @param e	keyboard event
	/// @return		true if the event has been handled correctly
	virtual bool keyPressed( const OIS::KeyEvent& e );
	/// Process a keyboard release event
	/// @param e	keyboard event
	/// @return		true if the event has been handled correctly
	virtual bool keyReleased(const OIS::KeyEvent& e);
	/// Process a mouse motion event
	/// @param e	mouse event
	/// @return		true if the event has been handled correctly
	virtual bool mouseMoved(const OIS::MouseEvent &e);

	/// Process a mouse click event
	/// @param e	mouse event
	/// @return		true if the event has been handled correctly
	virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	/// Process a mouse release event
	/// @param e	mouse event
	/// @return		true if the event has been handled correctly
	virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);

	//Scene configuration

	/// Initialise the scene and all of the entities that'll be displayed
	virtual void createScene();

	/// Create cameras
	virtual void createCameras();
	
	/// Create viewports
	virtual void createViewports();

	/// Initialise GUI subsystem using CEGUI
	virtual void setupCEGUI();
	
	///Initialise debug overlays
	virtual void setupOverlay();


	//Game update methods
	/// Update the game logic
	/// @param	elapsedTime	time elapsed since last update
	virtual void updateLogic(float elapsedTime);
	/// Update the game graphics. This will be used on
	/// animated scenes
	/// @param	elapsedTime	time elapsed since last update
	virtual void updateGraphics(float elapsedTime);

	/// Update the stats that'll be displayed on the debug windows
	virtual void updateStats();

protected:
	//Setup methods
	/// Create Ogre's root object
	void createRoot();

	/// Define resource locations
	void defineResources();

	/// Setup the render system: it will launch the
	/// config dialog
	void setupRenderSystem();

	/// Create the application's main window
	void createRenderWindow();

	/// Initialise and load resource groups
	void initialiseResourceGroups();
	
	/// Set up the scene: init cameras, viewports, lights and the scene's entities
	void setupScene();

	/// Set up the input subsystem
	void setupInputSystem();

	//Auxiliary methods

	/// Translate the camera
	virtual void moveCamera();

	/// Capture input and process it asynchronously
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

	// Attributes to control the camera's movement
	Ogre::Vector3			m_TranslateVector;
	Ogre::Real				m_MoveSpeed; 
	Ogre::Degree			m_RotateSpeed; 
	float					m_MoveScale; 
	Ogre::Degree			m_RotScale;


};

#endif
