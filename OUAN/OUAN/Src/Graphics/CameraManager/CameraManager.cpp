#include "OUAN_Precompiled.h"

#include "CameraManager.h"
#include "CameraController.h"
#include "CameraControllerFixedFirstPerson.h"
#include "CameraControllerFirstPerson.h"
#include "CameraControllerFixedThirdPerson.h"
#include "CameraControllerThirdPerson.h"
#include "CameraControllerTrajectory.h"
#include "../RenderSubsystem.h"
#include "../RenderComponent/RenderComponentCamera.h"
#include "../RenderComponent/RenderComponentViewport.h"
#include "../TrajectoryManager/TrajectoryManager.h"
#include "../TrajectoryManager/Trajectory.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObjectCamera.h"
#include "../../Event/EventDefs.h"

using namespace OUAN;
using namespace Ogre;

CameraManager::CameraManager()
{

}

CameraManager::~CameraManager()
{

}

void CameraManager::init(RenderSubsystemPtr pRenderSubsystem,TrajectoryManagerPtr pTrajectoryManager,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting,GameWorldManagerPtr pGameWorldManager)
{
	mSceneManager= pRenderSubsystem->getSceneManager();
	mTrajectoryManager=pTrajectoryManager;

	mGameWorldManager=pGameWorldManager;

	//Clear all cameras
	camera.clear();

	mCameraControllerFirstPerson= new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->init( pRenderSubsystem->getSceneManager());
	mCameraControllerThirdPerson= new CameraControllerThirdPerson();
	mCameraControllerThirdPerson->init( pRenderSubsystem,pPhysicsSubsystem,pRayCasting,pGameWorldManager);
	mCameraControllerFixedThirdPerson= new CameraControllerFixedThirdPerson();
	mCameraControllerFixedThirdPerson->init( pRenderSubsystem->getSceneManager());
	mCameraControllerFixedFirstPerson= new CameraControllerFixedFirstPerson();
	mCameraControllerFixedFirstPerson->init( pRenderSubsystem->getSceneManager());
	mCameraControllerTrajectory= new CameraControllerTrajectory();
	mCameraControllerTrajectory->init( pRenderSubsystem->getSceneManager());

	activeCameraController=mCameraControllerThirdPerson;

	createMainCamera();

	//Set Default camera to viewport
	mViewport= pRenderSubsystem->getRoot()->getAutoCreatedWindow()->addViewport(camera[OUAN::MAIN_CAMERA_NAME]->getCamera());
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

	//TODO REMOVE THIS
	mViewport = pRenderSubsystem->getRoot()->getAutoCreatedWindow()->getViewport(0);

	//Make it the active camera
	setActiveCamera(OUAN::MAIN_CAMERA_NAME);

	registerEventHandlers(mGameWorldManager->getEventManager());
}

void CameraManager::resetActiveCameraController()
{
	activeCameraController->reset();
}

Ogre::Vector3 CameraManager::rotateMovementVector(Ogre::Vector3 movement)
{
	return activeCameraController->rotateMovementVector(movement);
}

void CameraManager::setCameraTrajectory(std::string name)
{
	Logger::getInstance()->log("[Camera Manager] Setting trajectory "+name+" to Camera Controller Trajectory");

	try
	{
		if(mTrajectoryManager->hasTrajectory(name))
		{
			Trajectory * trajectory;
			trajectory=mTrajectoryManager->getTrajectoryInstance("CameraTrajectory");
			mTrajectoryManager->setPredefinedTrajectory(*trajectory,"a","blue");
			mCameraControllerTrajectory->setTrajectory(trajectory);
		}
		else
		{
			throw "Trajectory "+name+" does not exist";
		}
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[CameraManager] "+error);
	}
}

void CameraManager::createMainCamera()
{
	//Create Main Camera (Default Camera)
	TRenderComponentCameraParameters tRenderComponentCameraParameters;

	tRenderComponentCameraParameters.FOVy=55;
	tRenderComponentCameraParameters.position=Vector3(0,0,0);
	tRenderComponentCameraParameters.orientation=Quaternion();
	tRenderComponentCameraParameters.autotracktarget="None";
	tRenderComponentCameraParameters.viewmode=0;
	tRenderComponentCameraParameters.autoaspectratio=false;
	tRenderComponentCameraParameters.clipdistance=Vector2(0.1,25000);
	tRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;

	createCamera(OUAN::MAIN_CAMERA_NAME,tRenderComponentCameraParameters);
}

Viewport* CameraManager::getViewport() const
{
	return mViewport;
}

void CameraManager::cleanUp()
{
	//Clear all cameras
	camera.clear();
	unregisterEventHandlers(mGameWorldManager->getEventManager());
	delete mCameraControllerFirstPerson;
}

Ogre::Camera * CameraManager::getCamera(std::string name)
{
	return mSceneManager->getCamera(name);
}

TCameraControllerType CameraManager::getActiveCameraControllerType()
{
	return activeCameraController->getControllerType();
}

RenderComponentCameraPtr CameraManager::createCamera(std::string name,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	RenderComponentCameraPtr pRenderComponentCamera;
	Ogre::Camera * pCamera;

	//Create void RenderComponentCamera
	pRenderComponentCamera = RenderComponentCameraPtr(new RenderComponentCamera());

	// Set Camera parameters and create it
	try
	{
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		// Set RenderComponentCamera's Camera
		pRenderComponentCamera->setCamera(pCamera);

		// Set RenderComponentCamera Parameters
		pRenderComponentCamera->setCameraParameters(tRenderComponentCameraParameters);

		// Add RenderComponentCamera to Container
		camera[name]=pRenderComponentCamera;
	}
	catch(Ogre::Exception &/*e*/)
	{
		Logger::getInstance()->log("[LevelLoader] Error creating "+name+" Camera!");
	}
	return pRenderComponentCamera;
}

void CameraManager::clear()
{
	mSceneManager->destroyAllCameras(); 
	//Clear all cameras
	camera.clear();
	//We guarantee that at least main camera exists
	createMainCamera();

	mCameraControllerThirdPerson->clear();

	//Make it the active camera
	setActiveCamera(OUAN::MAIN_CAMERA_NAME);
}

Camera * CameraManager::getActiveCamera()
{
	return activeCameraController->getCamera();
}

void CameraManager::setActiveCamera(std::string name)
{
	Camera * pCamera;
	pCamera=camera[name]->getCamera();
	if(pCamera)
	{
		activeCameraController->setCamera(pCamera);
		mViewport->setCamera(pCamera);
		Logger::getInstance()->log("[Camera Manager] Camera "+name+" activated");
	}
	else
	{
		Logger::getInstance()->log("[Camera Manager] Camera "+name+" does not exist!");
	}
}

std::string CameraManager::getActiveCameraName()
{
	return activeCameraController->getCamera()->getName();
}

void CameraManager::setCameraType(TCameraControllerType tCameraControllerType)
{
	mCameraControllerTrajectory->detachCamera();

	switch(tCameraControllerType)
	{
		case CAMERA_FIXED_FIRST_PERSON:
			mCameraControllerFixedFirstPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFixedFirstPerson;
			Logger::getInstance()->log("[Camera Manager] Camera controller Fixed First person activated");
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			mCameraControllerFixedThirdPerson->setCamera(activeCameraController->getCamera());
			mCameraControllerFixedThirdPerson->calculateRotY();
			activeCameraController=mCameraControllerFixedThirdPerson;
			Logger::getInstance()->log("[Camera Manager] Camera controller Fixed Third Person activated");
			break;
		case CAMERA_FIRST_PERSON:
			mCameraControllerFirstPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFirstPerson;
			Logger::getInstance()->log("[Camera Manager] Camera controller First Person activated");
			break;
		case CAMERA_THIRD_PERSON:
			mCameraControllerThirdPerson->setCamera(activeCameraController->getCamera());
			mCameraControllerThirdPerson->reset();
			activeCameraController=mCameraControllerThirdPerson;
			Logger::getInstance()->log("[Camera Manager] Camera controller Third Person activated");
			break;
		case CAMERA_TRAJECTORY:
			//TODO: ERASE THIS
			setCameraTrajectory("a");
			mCameraControllerTrajectory->resetTrajectory();
			mCameraControllerTrajectory->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerTrajectory;
			Logger::getInstance()->log("[Camera Manager] Camera controller Trajectory Activated");
			break;
		default:
			Logger::getInstance()->log("[Camera Manager] Camera type does not exist!");
			break;		
	}
}

void CameraManager::resetActiveCameraPosition()
{
	camera[getActiveCameraName()]->resetCameraParameters();
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
	activeCameraController->update(elapsedTime);

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

void CameraManager::processCameraRotation(Ogre::Vector2 cameraRotation)
{
	activeCameraController->processCameraRotation(cameraRotation);
}

void CameraManager::processSimpleTranslation(Ogre::Vector3 nextMovement)
{
	activeCameraController->processSimpleTranslation(nextMovement);
}

void CameraManager::changeCamera()
{
	TCameraIterator it;

	it = camera.find(getActiveCameraName());
	it++;

	if( it==camera.end())
	{
		it=camera.begin();
	}

	resetActiveCameraPosition();

	setActiveCamera(it->first);
}

void CameraManager::changeCameraController()
{
	switch(activeCameraController->getControllerType())
	{
		case CAMERA_THIRD_PERSON:
			setCameraType(CAMERA_FIXED_THIRD_PERSON);
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			setCameraType(CAMERA_FIXED_FIRST_PERSON);
			break;
		case CAMERA_FIXED_FIRST_PERSON:
			setCameraType(CAMERA_FIRST_PERSON);
			break;
		case CAMERA_FIRST_PERSON:
			if(!mTrajectoryManager->hasTrajectory("a"))
			{
				setCameraType(CAMERA_THIRD_PERSON);
			}
			else
			{
				//TODO: ERASE THIS
				setCameraTrajectory("a");
				mCameraControllerTrajectory->resetTrajectory();
				setCameraType(CAMERA_TRAJECTORY);
			}
			break;
		case CAMERA_TRAJECTORY:
			setCameraType(CAMERA_THIRD_PERSON);
			break;
	}
}

void CameraManager::setCameraTarget(RenderComponentPositionalPtr target)
{
	mCameraControllerThirdPerson->setTarget(target);
	mCameraControllerFixedThirdPerson->setTarget(target);
	mCameraControllerFixedFirstPerson->setTarget(target);
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
	mCameraControllerThirdPerson->setOriginalMaxDistance();
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
	mCameraControllerThirdPerson->setChangeWorldMaxDistance();
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
