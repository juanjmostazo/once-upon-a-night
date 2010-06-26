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

CameraManager::CameraManager()
{

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
	mCameraInput->mCameraParameters->setDefaultParameters();

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



	mCurrentTrajectory=-1;

	setCameraType(OUAN::CAMERA_THIRD_PERSON);

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
			if(mCurrentTrajectory>=mCameraTrajectoryNames.size()+1)
			{
				Logger::getInstance()->log("[Camera Manager] Set Camera Free");
				CameraParametersPtr cameraParameters;
				cameraParameters.reset(new CameraParameters());
				cameraParameters->setDefaultParameters();
				cameraParameters->setTarget(mGameWorldManager->getGameObjectOny()->getName());
				setCameraFree(cameraParameters,true);
				mCurrentTrajectory=-1;
			}
			else if(mCurrentTrajectory==mCameraTrajectoryNames.size())
			{
				CameraParametersPtr cameraParameters;
				cameraParameters.reset(new CameraParameters());
				cameraParameters->setDefaultParameters();
				cameraParameters->setTarget(mGameWorldManager->getGameObjectTripolloDreamsContainer()->at(3)->getName());
				setCameraTracking(cameraParameters,true);
			}
			else if(mCurrentTrajectory<mCameraTrajectoryNames.size())
			{
				CameraParametersPtr cameraParameters;
				cameraParameters.reset(new CameraParameters());
				cameraParameters->setDefaultParameters();
				cameraParameters->setTarget(mGameWorldManager->getGameObjectOny()->getName());

				setCameraTrajectory(cameraParameters,mCameraTrajectoryNames[mCurrentTrajectory],true,true);
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

void CameraManager::activateChangeWorldFast()
{
	changeWorldFinished(mChangeWorldTotalTime);
	mIsChangingWorld=false;
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