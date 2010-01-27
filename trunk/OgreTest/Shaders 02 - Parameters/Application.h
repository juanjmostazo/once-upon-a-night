#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include <Ogre.h>
#include "SimpleInputManager.h"
#include "OrbitCameraController.h"

using namespace Ogre;

class Application
	: SimpleInputManager
{
public:
	Application();
	virtual ~Application();

	void initialise();
	void go();
	
	virtual bool keyPressed( const OIS::KeyEvent& e );
	virtual bool mouseMoved( const OIS::MouseEvent& e );


private:
	Ogre::Root* m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;

	Ogre::SceneNode* m_sceneNode;

	OrbitCameraController* m_cameraController;

	bool application_started;

	bool m_exitRequested;
	bool use_shader;

	Vector4 color,radius;

	void defineResources();
	void loadResources();
	void createScene();
	void updateLogic( const float elapsedSeconds );
	void updateGraphics( const float elapsedSeconds );


};

#endif
