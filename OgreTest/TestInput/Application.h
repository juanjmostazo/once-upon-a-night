#ifndef __APPLICATION__H__
#define __APPLICATION__H__

#include "ControlInputManager.h"

namespace Ogre
{
	class Root;
	class RenderWindow;
	class SceneManager;
	class Camera;
	class Viewport;

	class SceneNode;
	class Entity;

	class AnimationState;
}

class OrbitCameraController;

class Application
	: ControlInputManager
{
public:
	Application();
	virtual ~Application();

	void initialise();
	void go();

	virtual bool keyPressed( const OIS::KeyEvent& e );
	virtual bool mouseMoved( const OIS::MouseEvent& e );
	virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button );

private:

	void loadResources();
	void createScene();

	void updateLogic( const float elapsedSeconds );
	void updateAnimations( const float elapsedSeconds );

	Ogre::Root* m_root;
	Ogre::RenderWindow* m_window;
	Ogre::SceneManager* m_sceneManager;
	Ogre::Camera* m_camera;
	Ogre::Viewport* m_viewport;

	Ogre::SceneNode* m_sceneNode;
	Ogre::Entity* m_entity;

	Ogre::AnimationState* m_idleAnimation;
	Ogre::AnimationState* m_runAnimation;
	int m_movingDirection;

	OrbitCameraController* m_cameraController;

	bool m_exitRequested;
};

#endif
