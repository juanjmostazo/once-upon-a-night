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

		void init(Ogre::SceneManager * pSceneManager);
		void update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime);
		void loadInfo();
		TCameraControllerType getControllerType();

	protected:
	};
}

#endif