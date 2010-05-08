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

		void update(double elapsedTime);

		void setTrajectory(Trajectory * pTrajectory);
		Trajectory * getTrajectory() const;

		void resetTrajectory();

		void setCamera(Ogre::Camera * pCamera);
		void init(Ogre::SceneManager * pSceneManager);

		void detachCamera();
	private:
		Ogre::SceneManager * mSceneManager;
		Ogre::SceneNode * mSceneNode;
		Trajectory * mTrajectory;
	};
}

#endif