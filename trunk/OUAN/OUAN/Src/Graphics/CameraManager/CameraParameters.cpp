#include "OUAN_Precompiled.h"

#include "CameraManager.h"
#include "CameraParameters.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;

CameraParameters::CameraParameters()
{

}
CameraParameters::~CameraParameters()
{
}

void CameraParameters::setDirection(Ogre::Vector3 direction)
{
	mDirection = direction;
	if(mDirection!=Vector3::ZERO)
	{
		mDirection.normalise();
	}
}

Ogre::Vector3 CameraParameters::getDirection() const
{
	return mDirection;
}

void CameraParameters::setTargetOffset(Ogre::Vector3 targetOffset)
{
	mTargetOffset = targetOffset;
}

Ogre::Vector3 CameraParameters::getTargetOffset() const
{
	return mTargetOffset;
}

void CameraParameters::setTarget(std::string target)
{
	mTarget = target;
}

std::string CameraParameters::getTarget() const
{
	return mTarget;
}

void CameraParameters::setDistance(double distance)
{
	mDistance = distance;
}

double CameraParameters::getDistance() const
{
	return mDistance;
}
