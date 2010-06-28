#include "OUAN_Precompiled.h"

#include "../../Event/EventDefs.h"
#include "../../Event/EventHandler.h"
#include "../../Event/EventManager.h"
#include "CameraManager.h"
#include "CameraParameters.h"
#include "CameraInput.h"
#include "CameraController.h"

#include "CameraControllerFirstPerson.h"
#include "CameraControllerThirdPerson.h"

#include "../RenderSubsystem.h"
#include "../RenderComponent/RenderComponentViewport.h"
#include "../TrajectoryManager/TrajectoryManager.h"
#include "../TrajectoryManager/Trajectory.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObjectTripolloDreams.h"
#include "../../Game/GameObject/GameObjectOny.h"

using namespace OUAN;
using namespace Ogre;

CameraManager* CameraManager::mInst=NULL;

CameraManager::CameraManager()
{
	mInst=this;
}

CameraManager::~CameraManager()
{

}

Ogre::Camera * CameraManager::getCamera() const
{
	return mCamera;
}

void CameraManager::init(RenderSubsystemPtr pRenderSubsystem,TrajectoryManagerPtr pTrajectoryManager,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting,GameWorldManagerPtr pGameWorldManager)
{
	Logger::getInstance()->log("[Camera Manager] INITIALISING CAMERA MANAGER");

	mCameraInput.reset(new CameraInput());

	mSceneManager= pRenderSubsystem->getSceneManager();
	mTrajectoryManager=pTrajectoryManager;

	mGameWorldManager=pGameWorldManager;

	createMainCamera();

	mCameraControllerFirstPerson= new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->init( pRenderSubsystem->getSceneManager());

	mCameraControllerThirdPerson= new CameraControllerThirdPerson();
	mCameraControllerThirdPerson->init(mCameraInput, pRenderSubsystem->getSceneManager(),pRenderSubsystem,pPhysicsSubsystem,pTrajectoryManager,pGameWorldManager);

	//Set Default camera to viewport
	mViewport= pRenderSubsystem->getRoot()->getAutoCreatedWindow()->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

	//TODO REMOVE THIS
	mViewport = pRenderSubsystem->getRoot()->getAutoCreatedWindow()->getViewport(0);

	registerEventHandlers(mGameWorldManager->getEventManager());

	mLastTrigger="";

	mCurrentTrajectory=-1;

	setCameraType(OUAN::CAMERA_THIRD_PERSON);

	loadDefaultCameraParameters();

	mCameraInput->mCameraParameters=mDefaultCameraParameters;

}

void CameraManager::clear()
{	
	mCameraControllerFirstPerson->clear();
	mCameraControllerThirdPerson->clear();
}

void CameraManager::setCameraTrajectory(CameraParametersPtr cameraParameters,std::string trajectory,bool lookAtTarget,bool transition)
{
	setCameraType(CAMERA_THIRD_PERSON);
	mCameraInput->mCameraParameters=cameraParameters;
	mCameraControllerThirdPerson->setCameraTrajectory(mCamera,mCameraInput,trajectory,lookAtTarget,transition);
}

void CameraManager::setCameraFree(CameraParametersPtr cameraParameters,bool transition)
{
	setCameraType(CAMERA_THIRD_PERSON);
	mCameraInput->mCameraParameters=cameraParameters;
	mCameraControllerThirdPerson->setCameraFree(mCamera,mCameraInput,transition);

}

void CameraManager::setCameraTracking(CameraParametersPtr cameraParameters,bool transition)
{
	setCameraType(CAMERA_THIRD_PERSON);
	mCameraInput->mCameraParameters=cameraParameters;
	mCameraControllerThirdPerson->setCameraTracking(mCamera,mCameraInput,transition);
}

void CameraManager::setToDefaultCameraParameters(CameraParametersPtr & cameraParameters) const
{
	cameraParameters->setCameraParameters(mDefaultCameraParameters);
}

void CameraManager::loadDefaultCameraParameters()
{
	Configuration config;
	std::string value;

	mDefaultCameraParameters.reset(new CameraParameters());

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

		mDefaultCameraParameters->setTargetOffset(Vector3(target_offsetX, target_offsetY, target_offsetZ));

		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());

		Vector3 direction;
		direction = Vector3(initial_directionX, initial_directionY, initial_directionZ);
		direction.normalise();

		mDefaultCameraParameters->setDirection(direction);

		config.getOption("DISTANCE", value); 
		double distance = atof(value.c_str());
		mDefaultCameraParameters->setDistance(distance);

		config.getOption("TARGET", value); 
		mDefaultCameraParameters->setTarget(value);
	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CFG + " COULD NOT BE LOADED!");
	}
}

void CameraManager::createMainCamera()
{
	// Set Camera parameters and create it
	try
	{
		// Create the Camera
		mCamera = mSceneManager->createCamera(OUAN::MAIN_CAMERA_NAME);

		mCamera->setFOVy(Ogre::Radian(Ogre::Math::DegreesToRadians(55)));
		mCamera->setPosition(Vector3(0,0,0));
		mCamera->setOrientation(Quaternion());
		mCamera->setNearClipDistance(0.1);
		mCamera->setFarClipDistance(25000);
	}
	catch(Ogre::Exception &/*e*/)
	{
		Logger::getInstance()->log("[LevelLoader] Error creating main Camera!");
	}
}

Viewport* CameraManager::getViewport() const
{
	return mViewport;
}

void CameraManager::cleanUp()
{

	unregisterEventHandlers(mGameWorldManager->getEventManager());
	//TODO DELETE MORE THINGS
	delete mCameraControllerFirstPerson;
}

TCameraControllerType CameraManager::getCameraControllerType() const
{
	return mActiveCameraController->getControllerType();
}

void CameraManager::setCameraType(TCameraControllerType tCameraControllerType)
{
	switch(tCameraControllerType)
	{
		case CAMERA_FIRST_PERSON:
			mActiveCameraController=mCameraControllerFirstPerson;
			//Logger::getInstance()->log("[Camera Manager] Camera controller First Person activated");
			break;
		case CAMERA_THIRD_PERSON:
			mActiveCameraController=mCameraControllerThirdPerson;
			mCameraControllerThirdPerson->setCameraFree(mCamera,mCameraInput,false);
			//Logger::getInstance()->log("[Camera Manager] Camera controller Third Person activated");
			break;
		default:
			Logger::getInstance()->log("[Camera Manager] Camera type does not exist!");
			break;		
	}
}

Ogre::Viewport* CameraManager::setViewportParameters(Ogre::String name,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	//// Set the Viewport parameters
	mViewport->setBackgroundColour(tRenderComponentViewportParameters.colour);
	mViewport->setOverlaysEnabled(tRenderComponentViewportParameters.overlays);
	mViewport->setShadowsEnabled(tRenderComponentViewportParameters.shadows);
	mViewport->setSkiesEnabled(tRenderComponentViewportParameters.skies);

	return mViewport;
}

void CameraManager::update(double elapsedTime)
{
	//mPhysicsComponentCharacter->getMovement
		//ETC...



	mActiveCameraController->update(mCamera,mCameraInput,elapsedTime);

	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime+=elapsedTime;
		if(mChangeWorldElapsedTime>=mChangeWorldTotalTime)
		{
			changeToWorld(mWorld,1);
			changeWorldFinished(mWorld);
			mIsChangingWorld=false;
		}
		else
		{
			changeToWorld(mWorld,mChangeWorldElapsedTime/mChangeWorldTotalTime);
		}
	}
}

void CameraManager::processCameraRotation(Ogre::Vector2 rotation)
{
	mCameraInput->mRotation=rotation;
}

void CameraManager::processSimpleTranslation(Ogre::Vector3 translation)
{
	mCameraInput->mTranslation=translation;
}

void CameraManager::changeCameraController()
{
	switch(mActiveCameraController->getControllerType())
	{
		case CAMERA_THIRD_PERSON:
			setCameraType(CAMERA_FIRST_PERSON);
			break;
		case CAMERA_FIRST_PERSON:
			setCameraType(CAMERA_THIRD_PERSON);
			break;
	}

}

void CameraManager::changeAutoCamera()
{
	switch(mActiveCameraController->getControllerType())
	{
		case CAMERA_THIRD_PERSON:
			mCurrentTrajectory++;
			if(mCurrentTrajectory>=mCameraTrajectoryNames.size())
			{
				setDefaultThirdPersonCamera(true);
				mCurrentTrajectory=-1;
			}
			else if(mCurrentTrajectory<mCameraTrajectoryNames.size())
			{
				CameraParametersPtr cameraParameters;
				cameraParameters.reset(new CameraParameters());
				cameraParameters->setCameraParameters(mDefaultCameraParameters);
				cameraParameters->setTarget(mGameWorldManager->getGameObjectOny()->getName());

				setCameraTrajectory(cameraParameters,mCameraTrajectoryNames[mCurrentTrajectory],false,true);
			}
			break;
		case CAMERA_FIRST_PERSON:
			break;
	}
}

void CameraManager::setCameraAutoRotation(double rotX,double rotY,bool transition)
{
	mCameraControllerThirdPerson->setCameraAutoRotation(rotX,rotY,transition);
}

void CameraManager::centerToTargetBack(bool transition)
{
	mCameraControllerThirdPerson->centerToTargetBack(mCamera,mCameraInput,transition);
}

void CameraManager::setCameraTrajectoryNames(std::vector<std::string> trajectoryNames)
{
	mCameraTrajectoryNames=trajectoryNames;
}

bool CameraManager::cameraTrajectoryEnded()
{
	return mCameraControllerThirdPerson->cameraTrajectoryEnded();
}

void CameraManager::setLastTrigger(std::string lastTrigger)
{
	mLastTrigger=lastTrigger;
}
std::string CameraManager::getLastTrigger() const
{
	return mLastTrigger;
}

void CameraManager::activateChangeWorldFast()
{
	changeWorldFinished(mChangeWorldTotalTime);
	mIsChangingWorld=false;
}

void CameraManager::setDefaultThirdPersonCamera(bool transition)
{
	GameObjectOnyPtr pGameObjectOny;
	//Set Ony as Camera Target
	CameraParametersPtr cameraParameters;
	cameraParameters.reset(new CameraParameters());
	cameraParameters->setCameraParameters(mDefaultCameraParameters);
	pGameObjectOny=mGameWorldManager->getGameObjectOny();
	cameraParameters->setTarget(pGameObjectOny->getName());
	mCameraInput->mCameraParameters->setCameraParameters(cameraParameters);

	mCameraControllerThirdPerson->centerToTargetBack(mCamera,mCameraInput,transition);

	setCameraFree(cameraParameters,transition);
}

void CameraManager::activateChangeWorld()
{
	if(mIsChangingWorld)
	{
		mChangeWorldElapsedTime=mChangeWorldTotalTime-mChangeWorldElapsedTime;
	}
	else
	{
		changeWorldStarted(mWorld);
		mChangeWorldElapsedTime=0;
		mIsChangingWorld=true;
	}

}

void CameraManager::changeWorldFinished(int newWorld)
{
	switch(newWorld)
	{
	case DREAMS:

		break;
	case NIGHTMARES:

		break;
	default:
		break;
	}
}

void CameraManager::changeWorldStarted(int newWorld)
{
	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void CameraManager::changeToWorld(int newWorld, double perc)
{
	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void CameraManager::registerEventHandlers(EventManagerPtr evtMgr)
{
	boost::shared_ptr<CameraManager> this_;
	this_.reset(this);
	if (evtMgr.get())
	{
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<CameraManager,ChangeWorldEvent>(this_,&CameraManager::processChangeWorld));
		evtMgr->registerHandler(eh,EVENT_TYPE_CHANGEWORLD);
	}
}

void CameraManager::unregisterEventHandlers(EventManagerPtr evtMgr)
{
	boost::shared_ptr<CameraManager> this_;
	this_.reset(this);
	if (evtMgr.get())
	{
		EventHandlerPtr eh = EventHandlerPtr(new EventHandler<CameraManager,ChangeWorldEvent>(this_,&CameraManager::processChangeWorld));
		evtMgr->unregisterHandler(eh,EVENT_TYPE_CHANGEWORLD);
	}
}

void CameraManager::processChangeWorld(ChangeWorldEventPtr evt)
{
	mWorld=evt->getNewWorld();
	mChangeWorldTotalTime=evt->time;

	if (evt->fast)
	{
		activateChangeWorldFast();
	}
	else
	{
		activateChangeWorld();
	}
}

Ogre::Vector3 CameraManager::rotateMovementVector(Ogre::Vector3 movement,double elapsedSeconds)
{
	return mActiveCameraController->rotateMovementVector(movement,mCamera,mCameraInput,elapsedSeconds);
}

void CameraManager::setTrajectoryCamera(const std::string& camName)
{
	CameraParametersPtr params= CameraParametersPtr(new CameraParameters());
	mInst->setToDefaultCameraParameters(params);
	params->setCameraParameters(params);
	mInst->setCameraTrajectory(params,camName,false,false);
	mInst->mCameraControllerThirdPerson->getTrajectory()->setLoopTrajectory(false);
}
void CameraManager::setAnyTrackingCamera()
{
	CameraParametersPtr params= CameraParametersPtr(new CameraParameters());
	mInst->setToDefaultCameraParameters(params);
	params->setCameraParameters(params);
	params->setTarget(mInst->mGameWorldManager->getGameObjectOny()->getName());
	mInst->setCameraTracking(params,true);
}

void CameraManager::setCameraFixedFirstPerson(bool transition)
{	
	if(mCameraControllerThirdPerson->getCameraState()==CS_FIXED_FIRST_PERSON)
	{
		mInst->setDefaultThirdPersonCamera(transition);
	}
	else
	{
		mCameraControllerThirdPerson->setCameraFixedFirstPerson(mCamera,mCameraInput,transition);
	}
}

bool CameraManager::isCameraTrajectoryEnded()
{
	return mInst->cameraTrajectoryEnded();
}