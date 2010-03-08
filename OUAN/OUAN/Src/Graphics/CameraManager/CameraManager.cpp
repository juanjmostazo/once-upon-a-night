#include "CameraManager.h"
#include "CameraController.h"
#include "CameraControllerFirstPerson.h"
#include "CameraControllerFixedThirdPerson.h"
#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentCamera.h"

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
	this->mSceneManager=pSceneManager;

	clear();

	mCameraControllerFirstPerson= new CameraControllerFirstPerson();
	mCameraControllerFirstPerson->init(pSceneManager);
	mCameraControllerThirdPerson= new CameraControllerThirdPerson();
	mCameraControllerThirdPerson->init(pSceneManager);
	mCameraControllerFixedThirdPerson= new CameraControllerFixedThirdPerson();
	mCameraControllerFixedThirdPerson->init(pSceneManager);

	activeCameraController=mCameraControllerThirdPerson;

	Ogre::Camera * pCamera=pSceneManager->createCamera(OUAN::MAIN_CAMERA_NAME);

	mViewport= pRoot->getAutoCreatedWindow()->addViewport(pCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue::Black);

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

Ogre::Camera*  CameraManager::createCamera(std::string name,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	Camera *pCamera=0;
	// Set Camera parameters and create it
	try
	{
		//Copy camera initial parameters
		mCameraInitialParams[name].autoaspectratio=tRenderComponentCameraParameters.autoaspectratio;
		mCameraInitialParams[name].autotracktarget=tRenderComponentCameraParameters.autotracktarget;
		mCameraInitialParams[name].clipdistance=tRenderComponentCameraParameters.clipdistance;
		mCameraInitialParams[name].FOVy=tRenderComponentCameraParameters.FOVy;
		mCameraInitialParams[name].orientation=tRenderComponentCameraParameters.orientation;
		mCameraInitialParams[name].polygonmode=tRenderComponentCameraParameters.polygonmode;
		mCameraInitialParams[name].position=tRenderComponentCameraParameters.position;
		mCameraInitialParams[name].viewmode=tRenderComponentCameraParameters.viewmode;
	
		// Create the Camera
		pCamera = mSceneManager->createCamera(name);

		//Set Camera Parameters
		setCameraParameters(pCamera,tRenderComponentCameraParameters);

	}
	catch(Ogre::Exception &/*e*/)
	{
		LogManager::getSingleton().logMessage("[LevelLoader] Error creating "+name+" Camera!");
	}
	return pCamera;
}

void CameraManager::setCameraParameters(Camera * pCamera,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{

	//Set Camera Parameters
	pCamera->setPolygonMode(tRenderComponentCameraParameters.polygonmode);
	pCamera->setPosition(tRenderComponentCameraParameters.position);
	pCamera->setOrientation(tRenderComponentCameraParameters.orientation);
	pCamera->setAutoAspectRatio(tRenderComponentCameraParameters.autoaspectratio);
	pCamera->setNearClipDistance(tRenderComponentCameraParameters.clipdistance.x);
	pCamera->setFarClipDistance(tRenderComponentCameraParameters.clipdistance.y);
	
	//set FOV
	//In Ogitor default value is 1, which in Ogitor is 55 degree. FOV has to be in (0,180)
	Real FOVy=tRenderComponentCameraParameters.FOVy*55.0f;
	if(FOVy>180.0) FOVy=179.99;
	else if(FOVy<=0) FOVy=0.01;
	pCamera->setFOVy(Angle(FOVy));

	//set autotracktarget
	if(tRenderComponentCameraParameters.autotracktarget.compare("None")!=0)
	{
		//TODO test this
		SceneNode *trackTarget;
		trackTarget=mSceneManager->getSceneNode(tRenderComponentCameraParameters.autotracktarget);
		pCamera->setAutoTracking(true,trackTarget);
	}
}

void CameraManager::clear()
{
	Camera * pCamera;
	TCameraParamsContainerIterator it;

	for(it = mCameraInitialParams.begin(); it != mCameraInitialParams.end(); it++)
	{
		pCamera=mSceneManager->getCamera(it->first);
		if(pCamera)
		{
			mSceneManager->destroyCamera(pCamera);
		}
	}

	mCameraInitialParams.clear();
}

Camera * CameraManager::getActiveCamera()
{
	return activeCameraController->getCamera();
}

void CameraManager::setActiveCamera(std::string name)
{
	Camera * pCamera;
	pCamera=mSceneManager->getCamera(name);
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
			activeCameraController=mCameraControllerFirstPerson;
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			activeCameraController=mCameraControllerThirdPerson;
			break;
		case CAMERA_FIRST_PERSON:
			break;
		case CAMERA_THIRD_PERSON:
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
	TRenderComponentCameraParameters initialParameters;
	Camera * pCamera;
	std::string activeCameraName=getActiveCameraName();

	//Get camera and its parameters
	initialParameters=mCameraInitialParams[activeCameraName];
	pCamera=mSceneManager->getCamera(activeCameraName);

	//Set Camera Initial Parameters
	setCameraParameters(pCamera,initialParameters);
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

void CameraManager::processSimpleTranslation(Ogre::Vector3 unitTranslationVector)
{
	activeCameraController->processSimpleTranslation(unitTranslationVector);
}

void CameraManager::changeCamera()
{
	TCameraParamsContainerIterator it;

	it = mCameraInitialParams.find(getActiveCameraName());
	it++;

	if( it==mCameraInitialParams.end())
	{
		it=mCameraInitialParams.begin();
	}

	resetActiveCameraPosition();

	setActiveCamera(it->first);
}

void CameraManager::changeCameraController()
{
	switch(activeCameraController->getControllerType())
	{
		case CAMERA_FIXED_FIRST_PERSON:
			activeCameraController=mCameraControllerThirdPerson;
			break;
		case CAMERA_FIXED_THIRD_PERSON:
			activeCameraController=mCameraControllerFirstPerson;
			break;
	}
}

void CameraManager::setCameraTarget(RenderComponentPositional * target)
{
	mCameraControllerThirdPerson->setTarget(target);
}