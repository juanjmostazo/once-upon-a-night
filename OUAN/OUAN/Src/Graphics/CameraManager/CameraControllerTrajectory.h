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
	private:

		Trajectory * mTrajectory;
	};
}

#endif