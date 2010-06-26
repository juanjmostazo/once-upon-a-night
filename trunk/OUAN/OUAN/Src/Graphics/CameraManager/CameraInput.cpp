#include "OUAN_Precompiled.h"

#include "CameraInput.h"
#include "CameraParameters.h"
using namespace OUAN;

CameraInput::CameraInput()
{
	mCameraParameters.reset(new CameraParameters);
}
CameraInput::~CameraInput()
{
}