#pragma once
#include "GeneralHeader.h"

class CameraControllerTrajectory
{
public:
	CameraControllerTrajectory(void);
	~CameraControllerTrajectory(void);

	void initialise(Ogre::SceneManager * pSceneManager);
	void setCamera(Ogre::Camera* camera);
	void setTrajectory(Trajectory* trajectory);
	void update(const float elapsedSeconds);

private:
	Ogre::Camera* camera;
	Trajectory* trajectory;

};
