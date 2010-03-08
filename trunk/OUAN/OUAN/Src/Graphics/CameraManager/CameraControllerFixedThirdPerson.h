#ifndef CameraControllerFixedThirdPersonH_H
#define CameraControllerFixedThirdPersonH_H
#include "CameraController.h"
namespace OUAN
{
	class CameraControllerFixedThirdPerson : public CameraController
	{
	public:
		CameraControllerFixedThirdPerson();
		~CameraControllerFixedThirdPerson();

		void update(long elapsedTime);
		void setTarget(RenderComponentPositional * target);

		TCameraControllerType getControllerType();
	private:
		RenderComponentPositional * target;
	};
}

#endif