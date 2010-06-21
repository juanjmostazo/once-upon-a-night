#ifndef CameraParametersH_H
#define CameraParametersH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraParameters
	{
	private:

	public:
		CameraParameters();
		~CameraParameters();

		Vector3 mDirection;
		double mMaxDistance;
		double mMinDistance;
		double mMaxH;
		double mMinH;
		bool mFollowZoom;
		bool mFollowPan;
		bool mPlayerAutoCenter;
	};


}

#endif