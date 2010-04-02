#include "CameraManager.h"
#include "CameraController.h"
#include "CameraControllerFixedFirstPerson.h"
#include "CameraControllerFirstPerson.h"
#include "CameraControllerFixedThirdPerson.h"
#include "CameraControllerThirdPerson.h"
#include "CameraControllerTrajectory.h"
#include "../RenderComponent/RenderComponentCamera.h"
#include "../TrajectoryManager/TrajectoryManager.h"
#include "../TrajectoryManager/Trajectory.h"
#include "../../Game/GameWorldManager.h"
#include "../../Game/GameObject/GameObjectCamera.h"
using namespace OUAN;
using namespace Ogre;

CameraManager::CameraManager()
{

}
CameraManager::~CameraManager()
{

}

void CameraManager::init(RootPtr pRoot,Ogre::SceneManager * pSceneManager,TrajectoryManagerPtr pTrajectoryManager)
{
	mSceneManager=pSceneManager;
	mTrajectoryManager=pTrajectoryManager;

	//Clear all cameras
	camera.clear();

	mCameraControllerFirstPerson= new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->init(pSceneManager);
	mCameraControllerThirdPerson= new CameraControllerThirdPerson();
	mCameraControllerThirdPerson->init(pSceneManager);
	mCameraControllerFixedThirdPerson= new CameraControllerFixedThirdPerson();
	mCameraControllerFixedThirdPerson->init(pSceneManager);
	mCameraControllerFixedFirstPerson= new CameraControllerFixedFirstPerson();
	mCameraControllerFixedFirstPerson->init(pSceneManager);
	mCameraControllerTrajectory= new CameraControllerTrajectory();
	mCameraControllerTrajectory->init(pSceneManager);

	activeCameraController=mCameraControllerThirdPerson;

	createMainCamera();

	//Set Default camera to viewport
	mViewport= pRoot->getAutoCreatedWindow()->addViewport(camera[OUAN::MAIN_CAMERA_NAME]->getCamera());
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

	//Make it the active camera
	setActiveCamera(OUAN::MAIN_CAMERA_NAME);

}

Ogre::Vector3 CameraManager::rotateMovementVector(Ogre::Vector3 movement)
{
	return activeCameraController->rotateMovementVector(movement);
}

void CameraManager::setCameraTrajectory(std::string name)
{

	Ogre::LogManager::getSingleton().logMessage("[Camera Manager] Setting trajectory "+name+" to Camera Controller Trajectory");

	try
	{
		if(mTrajectoryManager->hasTrajectory(name))
		{
			mCameraControllerTrajectory->setTrajectory(mTrajectoryManager->getTrajectoryInstance(name));
		}
		else
		{
			throw "Trajectory "+name+" does not exist";
		}
	}
	catch( std::string error )
	{
		Ogre::LogManager::getSingleton().logMessage("[CameraManager] "+error);
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
	tRenderComponentCameraParameters.clipdistance=Vector2(0.1,20000);
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

	delete mCameraControllerFirstPerson;
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
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
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
		LogManager::getSingleton().logMessage("[Camera Manager] Camera "+name+" activated");
	}
	else
	{
		LogManager::getSingleton().logMessage("[Camera Manager] Camera "+name+" does not exist!");
	}
}

std::string CameraManager::getActiveCameraName()
{
	return activeCameraController->getCamera()->getName();
}

void CameraManager::setCameraType(TCameraControllerType tCameraControllerType)
{
	switch(tCameraControllerType)
	{
		case CAMERA_FIXED_FIRST_PERSON:
			mCameraControllerFixedFirstPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFixedFirstPerson;
			LogManager::getSingleton().logMessage("[Camera Manager] Camera controller Fixed First person activated");
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			mCameraControllerFixedThirdPerson->setCamera(activeCameraController->getCamera());
			mCameraControllerFixedThirdPerson->calculateRotY();
			activeCameraController=mCameraControllerFixedThirdPerson;
			LogManager::getSingleton().logMessage("[Camera Manager] Camera controller Fixed Third Person activated");
			break;
		case CAMERA_FIRST_PERSON:
			mCameraControllerFirstPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFirstPerson;
			LogManager::getSingleton().logMessage("[Camera Manager] Camera controller First Person activated");
			break;
		case CAMERA_THIRD_PERSON:
			mCameraControllerThirdPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerThirdPerson;
			LogManager::getSingleton().logMessage("[Camera Manager] Camera controller Third Person activated");
			break;
		case CAMERA_TRAJECTORY:
			//TODO: ERASE THIS
			setCameraTrajectory("a");
			mCameraControllerTrajectory->resetTrajectory();
			mCameraControllerTrajectory->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerTrajectory;
			LogManager::getSingleton().logMessage("[Camera Manager] Camera controller Trajectory Activated");
			break;
		default:
			LogManager::getSingleton().logMessage("[Camera Manager] Camera type does not exist!");
			break;		
	}
}

void CameraManager::resetActiveCameraPosition()
{
	camera[getActiveCameraName()]->resetCameraParameters();
}

void CameraManager::update(double elapsedTime)
{
	activeCameraController->update(elapsedTime);
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

void CameraManager::setCameraTarget(RenderComponentPositional * target)
{
	mCameraControllerThirdPerson->setTarget(target);
	mCameraControllerFixedThirdPerson->setTarget(target);
	mCameraControllerFixedFirstPerson->setTarget(target);
}

