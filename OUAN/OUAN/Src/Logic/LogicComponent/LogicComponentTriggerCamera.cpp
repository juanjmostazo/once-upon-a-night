#include "OUAN_Precompiled.h"

#include "LogicComponentTriggerCamera.h"
#include "../LogicSubsystem.h"
#include "../../Application.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObject.h"
#include "../../Graphics/CameraManager/CameraParameters.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;

LogicComponentTriggerCamera::LogicComponentTriggerCamera(const std::string& type)
:LogicComponent(COMPONENT_TYPE_LOGIC_TRIGGER_CAMERA)
{
}

LogicComponentTriggerCamera::~LogicComponentTriggerCamera()
{

}

void LogicComponentTriggerCamera::processCollision(GameObjectPtr pGameObject)
{

}

void LogicComponentTriggerCamera::processEnterTrigger(GameObjectPtr pGameObject)
{
	if(pGameObject->getType().compare(GAME_OBJECT_TYPE_ONY)==0)
	{
		ChangeCameraParametersEventPtr evt;
		evt.reset( new ChangeCameraParametersEvent());

		evt->pCameraParameters=mCameraParameters;
		evt->transition=true;

		getParent()->getGameWorldManager()->addEvent(evt);
	}
}

void LogicComponentTriggerCamera::processExitTrigger(GameObjectPtr pGameObject)
{

}

CameraParametersPtr LogicComponentTriggerCamera::getCameraParameters() const
{
	return mCameraParameters;
}

void LogicComponentTriggerCamera::setCameraParameters(CameraParametersPtr pCameraParameters)
{
	mCameraParameters=pCameraParameters;
}

TLogicComponentTriggerCameraParameters::TLogicComponentTriggerCameraParameters() : TLogicComponentParameters()
{

}

TLogicComponentTriggerCameraParameters::~TLogicComponentTriggerCameraParameters()
{

}
