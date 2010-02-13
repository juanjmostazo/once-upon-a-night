#pragma once
#include "GeneralHeader.h"

class CameraFirstPersonController
{
public:
	CameraFirstPersonController(void);
	~CameraFirstPersonController(void);

	void setCamera(Ogre::Camera* camera);
	void processKeyboardInput(SimpleInputManager* pSimpleInputManager,const float elapsedSeconds,float moveScale,float rotateScale);
	void processMouseInput(const OIS::MouseEvent& e);

private:
	Ogre::Camera* camera;
	Ogre::SceneNode *cameraNode;
	Ogre::SceneNode *cameraYawNode;
	Ogre::SceneNode *cameraPitchNode;
	Ogre::SceneNode *cameraRollNode;

};
