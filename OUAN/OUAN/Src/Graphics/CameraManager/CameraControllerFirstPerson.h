#ifndef CAMERACONTROLLERFIRSTPERSON_H
#define CAMERACONTROLLERFIRSTPERSON_H
#include "CameraController.h"

namespace OUAN
{
	class CameraControllerFirstPerson : public CameraController
	{
	public:
		CameraControllerFirstPerson();
		~CameraControllerFirstPerson();

		void init(Ogre::SceneManager * pSceneManager);
		
		void processSimpleTranslation(Ogre::Vector3 translationVector);
		void processMouseInput(const OIS::MouseEvent& e);
		void processRelativeMotion(double xRel, double yRel);

		void processInput(OIS::Keyboard* keyboard,double elapsedTime);
		void setCamera(Ogre::Camera * pCamera);

	private:
		Ogre::SceneNode *cameraNode;
		Ogre::SceneNode *cameraYawNode;
		Ogre::SceneNode *cameraPitchNode;
		Ogre::SceneNode *cameraRollNode;
		Ogre::SceneNode *cameraOffsetNode;

	};
	#endif
}