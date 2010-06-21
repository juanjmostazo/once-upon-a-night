#ifndef CameraControllerThirdPersonFreeH_H
#define CameraControllerThirdPersonFreeH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerThirdPersonFree : public CameraController
	{
	public:
		CameraControllerThirdPersonFree();
		~CameraControllerThirdPersonFree();

		void init(Ogre::SceneManager * pSceneManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

		Ogre::Vector3 rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds);
		void setCameraParameters(Ogre::Camera *pCamera,CameraInputPtr pCameraInput);
	
	protected:
		Ogre::Vector3 calculateCameraPosition(Ogre::Camera * pCamera,CameraInputPtr pCameraInput);
		Ogre::Vector3 calculateTargetPosition(CameraInputPtr pCameraInput);
		void processCameraRotation(CameraInputPtr pCameraInput);

		void rotateX(double rotation);
		void rotateY(double rotation);

		//initial direction
		Vector3 initialDirection;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//camera position speed
		double speedX;
		double speedY;

		//camera relative rotation to target's X axe
		double rotX;
		//camera relative rotation to target's Y axe
		double rotY;

		double rotXDistanceAttenuationNegative;
		double rotXDistanceAttenuationPositive;

		double distance;
	};
}

#endif