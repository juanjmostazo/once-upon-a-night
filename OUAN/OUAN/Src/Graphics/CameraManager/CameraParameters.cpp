#include "OUAN_Precompiled.h"

#include "CameraParameters.h"
#include "../../Loader/Configuration.h"

using namespace OUAN;

CameraParameters::CameraParameters()
{
	setDefaultParameters();
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

void CameraParameters::setDefaultParameters()
{
	Configuration config;
	std::string value;

	if (config.loadFromFile(CAMERA_CFG))
	{
		double target_offsetX, target_offsetY, target_offsetZ;
		double initial_directionX, initial_directionY, initial_directionZ;

		config.getOption("TARGET_OFFSET_X", value); 
		target_offsetX = atof(value.c_str());
		config.getOption("TARGET_OFFSET_Y", value); 
		target_offsetY = atof(value.c_str());
		config.getOption("TARGET_OFFSET_Z", value); 
		target_offsetZ = atof(value.c_str());

		mTargetOffset = Vector3(target_offsetX, target_offsetY, target_offsetZ);

		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());

		mDirection = Vector3(initial_directionX, initial_directionY, initial_directionZ);
		mDirection.normalise();

		config.getOption("DISTANCE", value); 
		mDistance = atof(value.c_str());
	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CFG + " COULD NOT BE LOADED!");
	}
}