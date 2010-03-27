#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
	//Set CameraControllerThirdPerson Initial Parameters

	distance=Ogre::Vector3(0,15,-45);
	initialDistance=distance;
	height=5;
	rotX=0;
	rotY=0;

	speed=0.2;
	returningspeed=2.5;

	maxRotX=50;
	minRotX=-50;

	cameraMoved=false;
	cameraIsReturning=false;
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{
	mSceneManager->destroyQuery(mRaySceneQuery);
}

void CameraControllerThirdPerson::init(Ogre::SceneManager * pSceneManager)
{
	mSceneManager = pSceneManager;
	mRaySceneQuery = mSceneManager->createRayQuery(Ray());

	//mRaySceneQuery->setQueryTypeMask(Ogre::SceneManager::WORLD_GEOMETRY_TYPE_MASK ); 

	CameraController::init(pSceneManager);
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraCollisions(Ogre::Vector3 currentCameraPosition, Ogre::Vector3 currentCameraLookAt)
{
	Vector3 newCameraPosition;
	Real target_distance;
	Vector3 direction;

	direction=currentCameraPosition-currentCameraLookAt;

	direction.normalise();

	//TODO: FINISH IMPLEMENTING THIS
	Ray ray;
	ray.setOrigin(currentCameraLookAt);
	ray.setDirection(direction);

	// Perform the scene query
	mRaySceneQuery->setRay(ray);
	mRaySceneQuery->setSortByDistance(true);
	RaySceneQueryResult &raySceneQueryResult=mRaySceneQuery->execute();

	Ogre::LogManager::getSingleton().logMessage("RAYSCENE QUERY");
	Ogre::LogManager::getSingleton().logMessage("Camera Initial Position "+Ogre::StringConverter::toString(currentCameraPosition));
	Ogre::LogManager::getSingleton().logMessage("Camera Look at: "+Ogre::StringConverter::toString(currentCameraLookAt));
	Ogre::LogManager::getSingleton().logMessage("Direction: "+Ogre::StringConverter::toString(direction));

	// Get the results, return the camera new position
	Ogre::LogManager::getSingleton().logMessage("Nº Ray intersections: "+Ogre::StringConverter::toString(raySceneQueryResult.size()));

	RaySceneQueryResult::iterator itr = raySceneQueryResult.begin();

	//Intitialise target distance
	target_distance=currentCameraPosition.distance(currentCameraLookAt);

	Ogre::LogManager::getSingleton().logMessage("Initial distance: "+Ogre::StringConverter::toString(target_distance));

	// Get the results, set the camera height
	while (itr != raySceneQueryResult.end() && itr->movable)
	{
		if(itr->movable->isVisible() && itr->movable->getName().compare("ony#0")!=0)
		{
			if(itr->distance)
			{
				if(itr->distance<target_distance)
				{
					target_distance=itr->distance;
				}

				Ogre::LogManager::getSingleton().logMessage("-name: "+itr->movable->getName()+" distance: "+Ogre::StringConverter::toString(itr->distance));
			}
		}
		itr++;
	}

	newCameraPosition=currentCameraLookAt+target_distance*direction;

	Ogre::LogManager::getSingleton().logMessage("New Camera Position: "+Ogre::StringConverter::toString(newCameraPosition));

	return newCameraPosition;

}

void CameraControllerThirdPerson::update(double elapsedTime)
{
	Vector3 newCameraPosition;
	Vector3 newTargetPosition;
	Vector3 cameraLookAt;
	Quaternion newTargetOrientation;

	newTargetPosition=target->getPosition();
	newTargetOrientation=target->getOrientation();

	if(cameraMoved)
	{
		cameraIsReturning=false;
	}

	//If target has moved we return the camera position to the back of the target
	if((newTargetPosition!=lastTargetPosition || newTargetOrientation!=lastTargetOrientation) || cameraIsReturning)
	{
		returningToInitialPosition();
		cameraIsReturning=true;
	}
	else
	{
		cameraIsReturning=false;
	}

	//CALCULATE POSITION WITHOUT COLLISIONS
	//Calculate Camera position in relation to the target
	newCameraPosition = initialDistance;
	newCameraPosition = Quaternion(Ogre::Degree(rotY+target->getYaw()), Vector3::UNIT_Y) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = target->getPosition()+newCameraPosition;

	//Calculate Camera look at
	cameraLookAt=newTargetPosition+Vector3(0,height,0);

	//Calculate camera collisions
	newCameraPosition=calculateCameraCollisions(newCameraPosition,cameraLookAt);

	//set camera position
	mCamera->setPosition(newCameraPosition);

	//set camera to look at target
	mCamera->lookAt(cameraLookAt);

	lastTargetPosition=newTargetPosition;
	lastTargetOrientation=newTargetOrientation;
}

void CameraControllerThirdPerson::processRelativeMotion(double xRel,double yRel,double zRel)
{

	//process Relative Motion
	if(xRel==0 && yRel==0) 
	{
		cameraMoved=false;
		return;
	}
	else
	{
		cameraMoved=true;
		rotY-=xRel*speed;
		rotX-=yRel*speed;
	}

	//check if rotation exceeds limits
	if(rotX>maxRotX)
	{
		rotX=maxRotX;
	}
	else if(rotX<minRotX)
	{
		rotX=minRotX;
	}
	//Ogre::LogManager::getSingleton().logMessage("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));

}
void CameraControllerThirdPerson::setTarget(RenderComponentPositional * target)
{
	this->target=target;
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}

void CameraControllerThirdPerson::returningToInitialPosition()
{
	//If we reach the initial position we set rotation to 0 in order to avoid accumulated error
	if(Ogre::Math::Abs(rotX)<returningspeed)
	{
		rotX=0;
		cameraIsReturning=false;
	}

	if(Ogre::Math::Abs(rotY)<=returningspeed)
	{
		rotY=0;
		cameraIsReturning=false;
	}

	//Return camera to initial position
	if(rotX>0)
	{
		rotX-=returningspeed;
	}
	else if(rotX<0)
	{
		rotX+=returningspeed;
	}

	if(rotY>0)
	{
		rotY-=returningspeed;
	}
	else if(rotY<0)
	{
		rotY+=returningspeed;
	}


}
