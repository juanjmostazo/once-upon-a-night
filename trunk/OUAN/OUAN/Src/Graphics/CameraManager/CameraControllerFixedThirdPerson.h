#ifndef CameraControllerFixedThirdPersonH_H
#define CameraControllerFixedThirdPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFixedThirdPerson : public CameraController
	{
	public:
		CameraControllerFixedThirdPerson();
		~CameraControllerFixedThirdPerson();

		void init(Ogre::SceneManager * pSceneManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

	private:
		double rotY;
		double height;
	};
}

#endif