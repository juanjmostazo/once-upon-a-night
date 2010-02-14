#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include "GeneralHeader.h"

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

	CameraControllerFirstPerson* m_cameraControllerFirstPerson;

	bool application_started;

	bool m_exitRequested;

	void defineResources();
	void loadResources();
	void createScene();
	void updateLogic( const float elapsedSeconds );
	void updateGraphics( const float elapsedSeconds );
	void changeCamera(String camera);

};

#endif
