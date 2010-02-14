#pragma once
#include "GeneralHeader.h"

class CameraControllerFirstPerson
{
public:
	CameraControllerFirstPerson();
	~CameraControllerFirstPerson();

	void initialise(Ogre::SceneManager * pSceneManager);
	void setCamera(Ogre::Camera* camera);
	void processKeyboardInput(SimpleInputManager* pSimpleInputManager,const float elapsedSeconds,float moveScale,float rotateScale);
	void processMouseInput(const OIS::MouseEvent& e);

	Ogre::Camera* camera;
	Ogre::SceneNode *cameraNode;
	Ogre::SceneNode *cameraYawNode;
	Ogre::SceneNode *cameraPitchNode;
	Ogre::SceneNode *cameraRollNode;
	Ogre::SceneNode *cameraOffsetNode;

};
