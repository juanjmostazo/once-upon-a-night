#ifndef CameraControllerH_H
#define CameraControllerH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		virtual void init(Ogre::SceneManager * pSceneManager);

		virtual void setCamera(Ogre::Camera * pCamera);
		virtual TCameraControllerType getControllerType();

		Ogre::Camera * getCamera();

		virtual void update(double elapsedTime);
		virtual void processCameraRotation(Ogre::Vector2 cameraRotation);
		virtual void processSimpleTranslation(Ogre::Vector3 nextMovement);
		virtual void setTarget(RenderComponentPositionalPtr target);
		virtual Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement);

	protected:
		Ogre::Camera *mCamera;
	};
}

#endif