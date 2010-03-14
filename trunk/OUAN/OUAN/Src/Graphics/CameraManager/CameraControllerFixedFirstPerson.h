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
		void setTarget(RenderComponentPositional * target);

		void update(double elapsedTime);
		void processRelativeMotion(double xRel,double yRel,double zRel);

	private:
		RenderComponentPositional * target;

		//camera relative rotation to target's X axe
		double rotX;
		//camera relative rotation to target's Y axe
		double rotY;

		//camera position speed
		double speed;

		//minimum and maximum rotation to target's X axe
		double minRotX;
		double maxRotX;

		//minimum and maximum rotation to target's Y axe
		double minRotY;
		double maxRotY;

		//camera height in relation to target
		double height;
	};
}

#endif