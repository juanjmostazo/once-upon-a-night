#ifndef CameraControllerFirstPersonH_H
#define CameraControllerFirstPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFirstPerson : public CameraController
	{
	public:
		CameraControllerFirstPerson();
		~CameraControllerFirstPerson();

		void init(Ogre::SceneManager * pSceneManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

	protected:
		void processCameraRotation(Ogre::Vector2 cameraRotation);
		void processSimpleTranslation(Ogre::Vector3 translation);

		double rotX;
		double rotY;
		double speed;
		double rotationSpeed;
		Vector3 newTranslation;
	};
}

#endif