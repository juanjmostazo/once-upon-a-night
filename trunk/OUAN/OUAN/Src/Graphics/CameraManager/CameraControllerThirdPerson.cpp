#include "OUAN_Precompiled.h"

#include "CameraControllerThirdPerson.h"
#include "CameraInput.h"
#include "CameraParameters.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../../Physics/PhysicsSubsystem.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RenderSubsystem.h"
#include "../../Loader/Configuration.h"
#include "../../RayCasting/RayCasting.h"
#include "../TrajectoryManager/TrajectoryManager.h"
#include "../TrajectoryManager/Trajectory.h"
#include "TransparentEntityManager.h"
using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson()
{
}
CameraControllerThirdPerson::~CameraControllerThirdPerson()
{
}

void CameraControllerThirdPerson::init(Ogre::SceneManager * pSceneManager,RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,TrajectoryManagerPtr pTrajectoryManager)
{
	loadInfo();
	mCameraState=CS_FREE;
	mRotX=0;
	mRotY=0;

	mCurrentDistance=mInitialDistance;
	mRayCasting=new RayCasting();
	mRayCasting->init(pRenderSubsystem,pPhysicsSubsystem);

	mTrajectoryManager=pTrajectoryManager;

	mSceneManager=pSceneManager;

	mTransparentEntityManager.reset(new TransparentEntityManager());
	mTransparentEntityManager->init();
}

void CameraControllerThirdPerson::clear()
{
	mTransparentEntityManager->clear();
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}

CameraState CameraControllerThirdPerson::getCameraState()
{
	return mCameraState;
}

void CameraControllerThirdPerson::setCameraAutoRotation(Ogre::Vector3 direction,double rotX,double rotY)
{
	mCameraState=CS_AUTO_ROTATION;

	mTargetRotX=rotX;
	if(mTargetRotX<mMinRotX)
		mTargetRotX=mMinRotX;
	if(mTargetRotX>mMaxRotX)
		mTargetRotX=mMaxRotX;
	mTargetRotY=rotY;

	mInitRotX=mRotX;
	mInitRotY=mRotY;

	if(mTargetRotX<mInitRotX)
	{
		mAutoRotationDirectionX=-1;
	}
	else
	{
		mAutoRotationDirectionX=1;
	}
	if(Ogre::Math::Abs(mInitRotX-mTargetRotX)>=180)
		mAutoRotationDirectionX=-mAutoRotationDirectionX;

	if(mTargetRotY<mInitRotY)
	{
		mAutoRotationDirectionY=-1;
	}
	else
	{
		mAutoRotationDirectionY=1;
	}
	if(Ogre::Math::Abs(mInitRotY-mTargetRotY)>=180)
		mAutoRotationDirectionY=-mAutoRotationDirectionY;
}

double CameraControllerThirdPerson::calculateDampenFactor(double perc,double dampenFactor,double dampenPow,double dampenStart)
{
	double dampen;
	if(perc>dampenStart)
	{
		dampen=1-Ogre::Math::Pow((perc-dampenStart)/(1-dampenStart),dampenPow)*dampenFactor;
	}
	else
	{
		dampen=1;
	}
	return dampen;
}

void CameraControllerThirdPerson::updateCameraAutoRotation(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	double dampenX=calculateDampenFactor(1-Ogre::Math::Abs(mRotX-mTargetRotX)/Ogre::Math::Abs(mInitRotX-mTargetRotX),
		mAutoRotationDampenFactor,mAutoRotationDampenPow,mAutoRotationDampenStart);
	double nextRotX=elapsedTime*mAutoRotationDirectionX*mAutoRotationSpeedX*dampenX;
	if(Ogre::Math::Abs(mRotX-mTargetRotX)<=Ogre::Math::Abs(nextRotX) ||
	   Ogre::Math::Abs(mRotX-(mTargetRotX+360))<=Ogre::Math::Abs(nextRotX) ||
	   Ogre::Math::Abs(mRotX-(mTargetRotX-360))<=Ogre::Math::Abs(nextRotX) )
	{
		mRotX=mTargetRotX;
	}
	else
	{			
		rotateX(nextRotX);
	}

	double dampenY=calculateDampenFactor(1-Ogre::Math::Abs(mRotY-mTargetRotY)/Ogre::Math::Abs(mInitRotY-mTargetRotY),
		mAutoRotationDampenFactor,mAutoRotationDampenPow,mAutoRotationDampenStart);
	double nextRotY=elapsedTime*mAutoRotationDirectionY*mAutoRotationSpeedY*dampenY;
	if(Ogre::Math::Abs(mRotY-mTargetRotY)<=Ogre::Math::Abs(nextRotY) ||
	   Ogre::Math::Abs(mRotY-(mTargetRotY+360))<=Ogre::Math::Abs(nextRotY) ||
	   Ogre::Math::Abs(mRotY-(mTargetRotY-360))<=Ogre::Math::Abs(nextRotY) )
	{
		mRotY=mTargetRotY;
	}
	else
	{			
		rotateY(nextRotY);
	}

	if(mRotX==mTargetRotX && mRotY==mTargetRotY)
	{	
		mCameraState=CS_FREE;
	}	
	defaultUpdateCamera(pCamera,pCameraInput,elapsedTime);
}

void CameraControllerThirdPerson::startTrajectory(std::string trajectory,Ogre::Camera * pCamera)
{
		Logger::getInstance()->log("[Camera Manager] Setting trajectory "+trajectory+" to Camera Controller Trajectory");

		if(!mSceneManager->hasSceneNode("CameraTrajectory"))
		{
			mDummyNode=mSceneManager->getRootSceneNode()->createChildSceneNode("CameraTrajectory");
		}
		else
		{
			mDummyNode=mSceneManager->getSceneNode("CameraTrajectory");
		}

		try
		{
			if(mTrajectoryManager->hasTrajectory(trajectory))
			{
				mTrajectory=mTrajectoryManager->getTrajectoryInstance("CameraTrajectory");
				mTrajectoryManager->setPredefinedTrajectory(*mTrajectory,trajectory,"blue");
			}
			else
			{
				throw "Trajectory "+trajectory+" does not exist";
			}
		}
		catch( std::string error )
		{
			Logger::getInstance()->log("[CameraManager] "+error);
		}

		mDummyNode->setPosition(mTrajectory->getCurrentNode()->getSceneNode()->getPosition());
		mDummyNode->setOrientation(mTrajectory->getCurrentNode()->getSceneNode()->getOrientation());
}

void CameraControllerThirdPerson::setCameraTrajectory(std::string trajectory,bool transition,Ogre::Camera * pCamera)
{
	if(!transition)
	{
		startTrajectory(trajectory,pCamera);
		mCameraState=CS_TRAJECTORY;
	}
	else
	{
		startTrajectory(trajectory,pCamera);
		setCameraMoveToPosition(
			pCamera->getPosition(),
			pCamera->getOrientation(),
			mTrajectory->getCurrentNode()->getSceneNode()->getPosition(),
			mTrajectory->getCurrentNode()->getSceneNode()->getOrientation(),
			CS_TRAJECTORY
			);
	}
}

void CameraControllerThirdPerson::updateCameraTrajectory(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	//update Trajectory
	mTrajectory->update(elapsedTime);

	//Set camera orientation
	mDummyNode->setOrientation(mTrajectory->getCurrentOrientation());
	pCamera->setOrientation(mDummyNode->getOrientation());

	//Set camera position
	mDummyNode->setPosition(mTrajectory->getCurrentPosition());
	pCamera->setPosition(mDummyNode->getPosition());
}

void CameraControllerThirdPerson::updateCameraMoveToPosition(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Quaternion orientation;
	Vector3 position;
	Vector3 direction;
	double dampen;
	double perc;

	perc=1-pCamera->getPosition().distance(mTransitionTargetPosition)/mTransitionInitialPosition.distance(mTransitionTargetPosition);

	direction=mTransitionTargetPosition-pCamera->getPosition();
	direction.normalise();
	dampen=calculateDampenFactor(perc,mTransitionDampenFactor,mTransitionDampenPow,mTransitionDampenStart);

	if(mTransitionTargetPosition.distance(pCamera->getPosition())<mTransitionSpeed*dampen)
	{
		position=mTransitionTargetPosition;
		orientation=mTransitionTargetRotation;
		mCameraState=mTargetState;
	}
	else
	{
		position=pCamera->getPosition()+direction*mTransitionSpeed*dampen;
		orientation=Quaternion::Slerp(perc,mTransitionInitialRotation,mTransitionTargetRotation,true);
	}

	pCamera->setOrientation(orientation);
	pCamera->setPosition(position);
}

void CameraControllerThirdPerson::setCameraMoveToPosition(Ogre::Vector3 position1,Ogre::Quaternion rotation1,Ogre::Vector3 position2,Ogre::Quaternion rotation2,CameraState targetState)
{
	mTransitionInitialRotation=rotation1;
	mTransitionTargetRotation=rotation2;
	mTransitionInitialPosition=position1;
	mTransitionTargetPosition=position2;
	mTargetState=targetState;
	mCameraState=CS_MOVE_TO_POSITION;
}

void CameraControllerThirdPerson::updateCameraFree(double elapsedTime,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	processCameraRotation(pCameraInput);
	defaultUpdateCamera(pCamera,pCameraInput,elapsedTime);
}

void CameraControllerThirdPerson::updateCurrentDistance(double elapsedTime)
{
	double dampen;
	if(mCurrentDistance<mInitialDistance)
	{
		dampen=mReturningSpeed*calculateDampenFactor(mCurrentDistance/mInitialDistance,mReturningDampenFactor,mReturningDampenPow,mReturningDampenStart);
		if(mCurrentDistance+dampen*mReturningSpeed*elapsedTime>mInitialDistance)
		{
			mCurrentDistance=mInitialDistance;
		}
		else
		{
			mCurrentDistance=mCurrentDistance+dampen*mReturningSpeed*elapsedTime;
		}
	}
}

void CameraControllerThirdPerson::defaultUpdateCamera(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{
	Vector3 cameraPosition;
	Vector3 cameraLookAt;

	updateCurrentDistance(elapsedTime);

	cameraPosition=calculateCameraPosition(pCamera,pCameraInput);
	cameraLookAt=calculateTargetPosition(pCameraInput);

	pCamera->setPosition(cameraPosition);

	//set camera to look at target
	pCamera->lookAt(cameraLookAt);

	mCurrentDistance=cameraPosition.distance(cameraLookAt);
}

void CameraControllerThirdPerson::setCameraFree(Ogre::Camera * pCamera,CameraInputPtr pCameraInput,bool transition)
{
	if(!transition)
	{
		mCameraState=CS_FREE;
	}
	else
	{
		Ogre::Camera * dummyCamera;
		dummyCamera= mSceneManager->createCamera("dummyCamera");
		defaultUpdateCamera(dummyCamera,pCameraInput,0);
		setCameraMoveToPosition(
			pCamera->getPosition(),
			pCamera->getOrientation(),
			dummyCamera->getPosition(),
			dummyCamera->getOrientation(),
			CS_FREE
			);
		mSceneManager->destroyCamera(dummyCamera);
	}
}

void CameraControllerThirdPerson::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{
	switch(mCameraState)
	{
	case CS_FREE:
		updateCameraFree(elapsedTime,pCamera,pCameraInput);
		break;
	case CS_AUTO_ROTATION:
		updateCameraAutoRotation(elapsedTime,pCamera,pCameraInput);
		break;
	case CS_TRAJECTORY:
		updateCameraTrajectory(elapsedTime,pCamera,pCameraInput);
		break;
	case CS_MOVE_TO_POSITION:
		updateCameraMoveToPosition(elapsedTime,pCamera,pCameraInput);
		break;
	default:
		break;
	}

	mTransparentEntityManager->update(elapsedTime);
}

Ogre::Vector3 CameraControllerThirdPerson::calculateTargetPosition(CameraInputPtr pCameraInput)
{
	return pCameraInput->mTarget->getSceneNode()->getPosition()+pCameraInput->mTargetOffset;
}


void CameraControllerThirdPerson::processCameraRotation(CameraInputPtr pCameraInput)
{
	rotateY(-pCameraInput->mRotation.x*mRotationSpeedY);
	rotateX(-pCameraInput->mRotation.y*mRotationSpeedX);
}

void CameraControllerThirdPerson::rotateX(double rotation)
{
	mRotX+=rotation;
	//check if rotation exceeds limits
	if(mRotX>mMaxRotX)
	{
		mRotX=mMaxRotX;
	}
	else if(mRotX<mMinRotX)
	{
		mRotX=mMinRotX;
	}
}

void CameraControllerThirdPerson::rotateY(double rotation)
{
	mRotY+=rotation;
	if(mRotY>360)
		mRotY-=360;
	if(mRotY<0)
		mRotY+=360;
}

Ogre::Vector3 CameraControllerThirdPerson::rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds)
{
	movement = Ogre::Quaternion(Ogre::Degree(pCamera->getOrientation().getYaw().valueDegrees()-180),Ogre::Vector3::UNIT_Y) * movement;

	return movement;
}

void CameraControllerThirdPerson::setCameraParameters(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	Vector3 cameraPosition;
	Vector3 cameraLookAt;
	cameraPosition=calculateCameraPosition(pCamera,pCameraInput);
	cameraLookAt=calculateTargetPosition(pCameraInput);

	pCamera->setPosition(cameraPosition);

	//set camera to look at target
	pCamera->lookAt(cameraLookAt);
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraPositionAtDistance(double distance,CameraInputPtr pCameraInput)
{
	Ogre::Vector3 targetPosition;
	Ogre::Vector3 newCameraPosition;

	targetPosition=calculateTargetPosition(pCameraInput);

	newCameraPosition=distance*mInitialDirection;

	newCameraPosition = Quaternion(Ogre::Degree(mRotX), Vector3::UNIT_X) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(mRotY), Vector3::UNIT_Y) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = targetPosition+newCameraPosition;

	return newCameraPosition;
}

Ogre::Vector3 CameraControllerThirdPerson::calculateDirection(Ogre::Vector3 v1,Ogre::Vector3 v2)
{
	Ogre::Vector3 direction;
	direction=v2-v1;
	direction.normalise();
	return direction;
}

Ogre::Vector3 CameraControllerThirdPerson::processMoveCameraCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Vector3 targetPosition;
	Vector3 direction;
	Vector3 testPosition;
	double distance;
	Vector3 perpendicularY,perpendicularX;
	Vector3 collisionPosition;
	Ogre::Entity * pEntity;
	std::vector<Ogre::Entity*> collisionEntities;
	bool collisionBottomLeft,collisionBottomRight,collisionTopLeft,collisionTopRight;

	targetPosition = calculateTargetPosition(pCameraInput);

	//Center viewport
	direction = calculateDirection(targetPosition,cameraPosition);
	perpendicularY = Quaternion(Ogre::Degree(90), Vector3::UNIT_Y) * direction;
	perpendicularX = Quaternion(Ogre::Degree(90), Vector3::UNIT_X) * direction;
	//Botton-Left Viewport
	testPosition = cameraPosition-perpendicularY*mCollisionOffsetY-perpendicularX*mCollisionOffsetX;
	direction = calculateDirection(targetPosition,testPosition);
	distance = targetPosition.distance(testPosition);
	collisionBottomLeft=mRayCasting->raycastRenderAllGeometry(targetPosition,direction,
		collisionPosition,pEntity,collisionEntities,distance,QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET);
	
	collisionPosition=collisionPosition+perpendicularY*mCollisionOffsetY+perpendicularX*mCollisionOffsetX;
	if(collisionBottomLeft && targetPosition.distance(collisionPosition)<targetPosition.distance(cameraPosition))
	{
		cameraPosition=collisionPosition;
	}

	//Top-Left Viewport
	testPosition = cameraPosition+perpendicularY*mCollisionOffsetY-perpendicularX*mCollisionOffsetX;
	direction = calculateDirection(targetPosition,testPosition);
	distance = targetPosition.distance(testPosition);
	collisionTopLeft=mRayCasting->raycastRenderAllGeometry(targetPosition,direction,
		collisionPosition,pEntity,collisionEntities,distance,QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET);
	
	collisionPosition=collisionPosition-perpendicularY*mCollisionOffsetY+perpendicularX*mCollisionOffsetX;
	if(collisionTopLeft && targetPosition.distance(collisionPosition)<targetPosition.distance(cameraPosition))
	{
		cameraPosition=collisionPosition;
	}

	//Top-Right Viewport
	testPosition = cameraPosition+perpendicularY*mCollisionOffsetY+perpendicularX*mCollisionOffsetX;
	direction = calculateDirection(targetPosition,testPosition);
	distance = targetPosition.distance(testPosition);

	collisionTopRight=mRayCasting->raycastRenderAllGeometry(targetPosition,direction,
		collisionPosition,pEntity,collisionEntities,distance,QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET);

	collisionPosition=collisionPosition-perpendicularY*mCollisionOffsetY-perpendicularX*mCollisionOffsetX;
	if(collisionTopRight && targetPosition.distance(collisionPosition)<targetPosition.distance(cameraPosition))
	{
		cameraPosition=collisionPosition;
	}

	//Bottom-Right Viewport
	testPosition = cameraPosition-perpendicularY*mCollisionOffsetY+perpendicularX*mCollisionOffsetX;
	direction = calculateDirection(targetPosition,testPosition);
	distance = targetPosition.distance(testPosition);

	collisionBottomRight=mRayCasting->raycastRenderAllGeometry(targetPosition,direction,
		collisionPosition,pEntity,collisionEntities,distance,QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET);

	collisionPosition=collisionPosition+perpendicularY*mCollisionOffsetY-perpendicularX*mCollisionOffsetX;
	if(collisionBottomRight && targetPosition.distance(collisionPosition)<targetPosition.distance(cameraPosition))
	{
		cameraPosition=collisionPosition;
	}

	mHasCollisioned=collisionBottomLeft || collisionBottomRight || collisionTopLeft || collisionTopRight;
	return cameraPosition;
}

void CameraControllerThirdPerson::processTransparentCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Vector3 targetPosition;
	Vector3 direction;
	Vector3 testPosition;
	double distance;
	Vector3 perpendicularY,perpendicularX;
	Vector3 collisionPosition;
	Ogre::Entity * pEntity;
	std::vector<Ogre::Entity*> collisionEntities;
	bool collision;

	targetPosition = calculateTargetPosition(pCameraInput);

	//Center viewport
	direction = calculateDirection(targetPosition,cameraPosition);

	//Bottom-Right Viewport
	direction = calculateDirection(targetPosition,cameraPosition);
	distance = targetPosition.distance(cameraPosition);

	collision=mRayCasting->raycastRenderAllGeometry(targetPosition,direction,
		collisionPosition,pEntity,collisionEntities,distance,QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID);

	mTransparentEntityManager->addCurrentCollisionTransparentEntities(collisionEntities);

} 

Ogre::Vector3 CameraControllerThirdPerson::resolveCollisions(Ogre::Vector3 cameraPosition,Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	cameraPosition=processMoveCameraCollisions(cameraPosition,pCamera,pCameraInput);
	processTransparentCollisions(cameraPosition,pCamera,pCameraInput);

	//returns nearest collision distance
	return cameraPosition;
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraPosition(Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Ogre::Vector3 newCameraPosition;

	newCameraPosition=calculateCameraPositionAtDistance(mCurrentDistance,pCameraInput);
	newCameraPosition=resolveCollisions(newCameraPosition,pCamera,pCameraInput);

	return newCameraPosition;
}

void CameraControllerThirdPerson::centerCamera(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	double targetYaw;
	targetYaw=pCameraInput->mTarget->getSceneNode()->getOrientation().getYaw().valueDegrees();
	if(targetYaw>360)
		targetYaw-=360;
	if(targetYaw<0)
		targetYaw+=360;
	setCameraAutoRotation(mInitialDirection,0,targetYaw);
}

void CameraControllerThirdPerson::loadInfo()
{
	CameraController::loadInfo();

	Configuration config;
	std::string value;

	if (config.loadFromFile(CAMERA_CONTROLLER_THIRD_PERSON_FREE_CFG))
	{
		double initial_directionX, initial_directionY, initial_directionZ;
		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());
		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());
		mInitialDirection = Vector3(initial_directionX, initial_directionY, initial_directionZ);
		mInitialDirection.normalise();
		config.getOption("MIN_ROT_X", value); 
		mMinRotX = atof(value.c_str());
		config.getOption("MAX_ROT_X", value); 
		mMaxRotX = atof(value.c_str());
		config.getOption("SPEED_X", value); 
		mRotationSpeedX = atof(value.c_str());
		config.getOption("SPEED_Y", value); 
		mRotationSpeedY = atof(value.c_str());
		config.getOption("INITIAL_DISTANCE", value); 
		mInitialDistance = atof(value.c_str());
		config.getOption("COLLISION_OFFSET_Y", value); 
		mCollisionOffsetY = atof(value.c_str());
		config.getOption("COLLISION_OFFSET_X", value); 
		mCollisionOffsetX = atof(value.c_str());
		config.getOption("AUTO_ROTATION_SPEED_X", value); 
		mAutoRotationSpeedX = atof(value.c_str());
		config.getOption("AUTO_ROTATION_SPEED_Y", value); 
		mAutoRotationSpeedY = atof(value.c_str());
		config.getOption("AUTO_ROTATION_DAMPEN_FACTOR", value); 
		mAutoRotationDampenFactor = atof(value.c_str());
		config.getOption("AUTO_ROTATION_DAMPEN_START", value); 
		mAutoRotationDampenStart = atof(value.c_str());
		config.getOption("AUTO_ROTATION_DAMPEN_POW", value); 
		mAutoRotationDampenPow = atof(value.c_str());

		config.getOption("TRANSITION_SPEED", value); 
		mTransitionSpeed = atof(value.c_str());
		config.getOption("TRANSITION_DAMPEN_FACTOR", value); 
		mTransitionDampenFactor = atof(value.c_str());
		config.getOption("TRANSITION_DAMPEN_START", value); 
		mTransitionDampenStart = atof(value.c_str());
		config.getOption("TRANSITION_DAMPEN_POW", value); 
		mTransitionDampenPow = atof(value.c_str());

		config.getOption("RETURNING_SPEED", value); 
		mReturningSpeed = atof(value.c_str());
		config.getOption("RETURNING_DAMPEN_FACTOR", value); 
		mReturningDampenFactor = atof(value.c_str());
		config.getOption("RETURNING_DAMPEN_START", value); 
		mReturningDampenStart = atof(value.c_str());
		config.getOption("RETURNING_DAMPEN_POW", value); 
		mReturningDampenPow = atof(value.c_str());

	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CONTROLLER_THIRD_PERSON_FREE_CFG + " COULD NOT BE LOADED!");
	}
}