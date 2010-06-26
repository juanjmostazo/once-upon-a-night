#ifndef CameraTriggerH_H
#define CameraTriggerH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraTrigger
	{

	public:
		CameraTrigger();
		~CameraTrigger();

		//type
		CameraTriggerType mCameraTriggerType;

		//transition
		bool mTransition;

		//free/tracking
		CameraParametersPtr mCameraParameters;

		//trajectory
		std::string mTrajectory;
		bool mTrajectoryLookAtTarget;


		//auto rotation
		double mRotX;
		double mRotY;

	};


}

#endif