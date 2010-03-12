#include "CameraManager.h"
#include "CameraController.h"
#include "CameraControllerFixedFirstPerson.h"
#include "CameraControllerFirstPerson.h"
#include "CameraControllerFixedThirdPerson.h"
#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentCamera.h"
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

void CameraManager::init(RootPtr pRoot,Ogre::SceneManager * pSceneManager)
{
	mSceneManager=pSceneManager;

	clear();

	mCameraControllerFirstPerson= new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->init(pSceneManager);
	mCameraControllerThirdPerson= new CameraControllerThirdPerson();
	mCameraControllerThirdPerson->init(pSceneManager);
	mCameraControllerFixedThirdPerson= new CameraControllerFixedThirdPerson();
	mCameraControllerFixedThirdPerson->init(pSceneManager);
	mCameraControllerFixedFirstPerson= new CameraControllerFixedFirstPerson();
	mCameraControllerFixedFirstPerson->init(pSceneManager);

	activeCameraController=mCameraControllerThirdPerson;

	//Create Main Camera (Default Camera)
	TRenderComponentCameraParameters tRenderComponentCameraParameters;

	tRenderComponentCameraParameters.FOVy=55;
	tRenderComponentCameraParameters.position=Vector3(0,0,0);
	tRenderComponentCameraParameters.orientation=Quaternion();
	tRenderComponentCameraParameters.autotracktarget="None";
	tRenderComponentCameraParameters.viewmode=0;
	tRenderComponentCameraParameters.autoaspectratio=false;
	tRenderComponentCameraParameters.clipdistance=Vector2(0.1,10000);
	tRenderComponentCameraParameters.polygonmode=Ogre::PM_SOLID;

	createCamera(OUAN::MAIN_CAMERA_NAME,tRenderComponentCameraParameters);

	//Set Default camera to viewport
	mViewport= pRoot->getAutoCreatedWindow()->addViewport(camera[OUAN::MAIN_CAMERA_NAME]->getCamera());
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

	//Make it the active camera
	setActiveCamera(OUAN::MAIN_CAMERA_NAME);

}

Viewport* CameraManager::getViewport() const
{
	return mViewport;
}


void CameraManager::cleanUp()
{
	clear();

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
	camera.clear();
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
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			mCameraControllerFixedThirdPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFixedThirdPerson;
			break;
		case CAMERA_FIRST_PERSON:
			mCameraControllerFirstPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerFirstPerson;
			break;
		case CAMERA_THIRD_PERSON:
			mCameraControllerThirdPerson->setCamera(activeCameraController->getCamera());
			activeCameraController=mCameraControllerThirdPerson;
			break;
		case CAMERA_TRAJECTORY:
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

void CameraManager::update(long elapsedTime)
{
	activeCameraController->update(elapsedTime);
}

void CameraManager::processMouseInput(const OIS::MouseEvent &e)
{
	activeCameraController->processMouseInput(e);
}

void CameraManager::processRelativeMotion(double xRel,double yRel,double zRel)
{
	activeCameraController->processRelativeMotion(xRel,yRel,zRel);
}

void CameraManager::processSimpleTranslation(int movementFlags)
{
	activeCameraController->processSimpleTranslation(movementFlags);
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
