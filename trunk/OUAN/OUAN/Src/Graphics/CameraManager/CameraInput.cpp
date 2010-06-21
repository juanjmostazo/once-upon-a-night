#include "OUAN_Precompiled.h"

#include "CameraInput.h"
#include "CameraParameters.h"
#include "../TrajectoryManager/Trajectory.h"
#include "../../Loader/Configuration.h"
using namespace OUAN;

CameraInput::CameraInput()
{
}
CameraInput::~CameraInput()
{
}

void CameraInput::init()
{
	mTrajectory= new Trajectory();
	mCameraParameters.reset(new CameraParameters);

	loadConfig();
}

void CameraInput::loadConfig()
{
	Configuration config;
	std::string value;

	if (config.loadFromFile(CAMERA_CFG))
	{
		double target_offsetX, target_offsetY, target_offsetZ;

		config.getOption("TARGET_OFFSET_X", value); 
		target_offsetX = atof(value.c_str());
		config.getOption("TARGET_OFFSET_Y", value); 
		target_offsetY = atof(value.c_str());
		config.getOption("TARGET_OFFSET_Z", value); 
		target_offsetZ = atof(value.c_str());

		mTargetOffset = Vector3(target_offsetX, target_offsetY, target_offsetZ);

		double initial_directionX, initial_directionY, initial_directionZ;

		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());

		mCameraParameters->mDirection = Vector3(initial_directionX, initial_directionY, initial_directionZ);

		config.getOption("MAX_DISTANCE", value); 
		mCameraParameters->mMaxDistance = atof(value.c_str());

		config.getOption("MIN_DISTANCE", value); 
		mCameraParameters->mMinDistance = atof(value.c_str());

		config.getOption("MAX_H", value); 
		mCameraParameters->mMaxH = atof(value.c_str());

		config.getOption("MIN_H", value); 
		mCameraParameters->mMinH = atof(value.c_str());

	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CFG + " COULD NOT BE LOADED!");
	}
}