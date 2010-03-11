#ifndef CameraControllerFixedFirstPersonH_H
#define CameraControllerFixedFirstPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFixedFirstPerson : public CameraController
	{
	public:
		CameraControllerFixedFirstPerson();
		~CameraControllerFixedFirstPerson();

		TCameraControllerType getControllerType();

	};
}

#endif