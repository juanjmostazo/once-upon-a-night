#ifndef CameraParametersH_H
#define CameraParametersH_H
#include "../../OUAN.h"
namespace OUAN
{
	class CameraParameters
	{
	private:
		Vector3 mDirection;
		double mDistance;
		std::string mTarget;
		Vector3 mTargetOffset;

	public:
		CameraParameters();
		~CameraParameters();

		//Camera direction from target to camera
		//auto-normalises direction
		void setDirection(Ogre::Vector3 direction);
		Ogre::Vector3 getDirection() const;

		//distance between target and camera
		void setDistance(double distance);
	    double getDistance() const;

		//camera look At
		void setTarget(std::string target);
		std::string  CameraParameters::getTarget() const;

		//Offset for the camera target, which adds to the target position
		void setTargetOffset(Ogre::Vector3 direction);
		Ogre::Vector3 getTargetOffset() const;
	};


}

#endif