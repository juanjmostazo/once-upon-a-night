#ifndef CameraControllerTrajectoryH_H
#define CameraControllerTrajectoryH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerTrajectory : public CameraController
	{
	public:
		CameraControllerTrajectory();
		~CameraControllerTrajectory();

		TCameraControllerType getControllerType();

		void update(long elapsedTime);

		void setCamera(Ogre::Camera * pCamera);

		void setTrajectory(Trajectory * pTrajectory);
	private:

		//camera relative rotation to X axe
		double rotX;
		//camera relative rotation to Y axe
		double rotY;

		//camera position speed
		double speed;
		//camera rotation speed
		double rotationSpeed;

		Vector3 newTranslation;

		Trajectory * mTrajectory;
	};
}

#endif