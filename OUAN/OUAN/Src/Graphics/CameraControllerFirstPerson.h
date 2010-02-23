#ifndef CAMERACONTROLLERFIRSTPERSON_H
#define CAMERACONTROLLERFIRSTPERSON_H
#include "../OUAN.h"

namespace OUAN
{
	class CameraControllerFirstPerson
	{
	public:
		CameraControllerFirstPerson();
		~CameraControllerFirstPerson();

		void initialise(Ogre::SceneManager * pSceneManager);
		void setCamera(Ogre::Camera* camera);
		void processKeyboardInput(OIS::Keyboard* keyboard,float elapsedTime);
		void processSimpleTranslation(const Ogre::Vector3& translationVector);
		void processMouseInput(const OIS::MouseEvent& e);
		void processRelativeMotion(float xRel, float yRel);
	private:
		Ogre::Camera* camera;
		Ogre::SceneNode *cameraNode;
		Ogre::SceneNode *cameraYawNode;
		Ogre::SceneNode *cameraPitchNode;
		Ogre::SceneNode *cameraRollNode;
		Ogre::SceneNode *cameraOffsetNode;

	};
	#endif
}