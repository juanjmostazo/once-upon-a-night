#ifndef LogicComponentTriggerCameraH_H
#define LogicComponentTriggerCameraH_H

#include "LogicComponent.h"
namespace OUAN
{

	class LogicComponentTriggerCamera: public LogicComponent
	{
	public:
		LogicComponentTriggerCamera(const std::string& type="");
		~LogicComponentTriggerCamera();
		// CameraParameters
		CameraParametersPtr getCameraParameters() const;
		void setCameraParameters(CameraParametersPtr pCameraParameters);

		void processCollision(GameObjectPtr pGameObject);
		void processEnterTrigger(GameObjectPtr pGameObject);
		void processExitTrigger(GameObjectPtr pGameObject);

	protected:

		CameraParametersPtr mCameraParameters;
	};
	
	class TLogicComponentTriggerCameraParameters: public TLogicComponentParameters
	{
	public:
		TLogicComponentTriggerCameraParameters();
		~TLogicComponentTriggerCameraParameters();

		///Camera Parameters
		CameraParametersPtr pCameraParameters;
	};
}

#endif