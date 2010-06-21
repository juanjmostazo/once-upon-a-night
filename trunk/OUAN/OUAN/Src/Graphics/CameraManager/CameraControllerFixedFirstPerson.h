#ifndef CameraControllerFixedFirstPersonH_H
#define CameraControllerFixedFirstPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFixedFirstPerson : public CameraController
	{
	public:
		CameraControllerFixedFirstPerson();
		~CameraControllerFixedFirstPerson();

		void init(Ogre::SceneManager * pSceneManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

	protected:
	};
}

#endif