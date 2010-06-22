#include "OUAN_Precompiled.h"

#include "CameraControllerThirdPersonAuto.h"
#include "CameraInput.h"
#include "CameraParameters.h"
#include "../../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../RenderComponent/RenderComponentPositional.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPersonAuto::CameraControllerThirdPersonAuto()
{
}
CameraControllerThirdPersonAuto::~CameraControllerThirdPersonAuto()
{
}

void CameraControllerThirdPersonAuto::init(Ogre::SceneManager * pSceneManager)
{
	loadInfo();

	mLastSurfaceAngle=0;
	mLastSurfacePosition=Vector3::ZERO;

	mDummyCamera=pSceneManager->createCamera("mDummyCamera");
}

TCameraControllerType CameraControllerThirdPersonAuto::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON_AUTO;
}

void CameraControllerThirdPersonAuto::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
{
	applyChanges(pCamera,
				 calculateCameraPosition(pCamera,pCameraInput),
				 calculateTargetPosition(pCameraInput),
				 elapsedTime 
				 );
	updateLastSurface(pCamera,pCameraInput);
}

void CameraControllerThirdPersonAuto::applyChanges(Ogre::Camera *pCamera,Ogre::Vector3 position,Ogre::Vector3 lookAt,double elapsedTime)
{
	double displacement;
	Vector3 direction;


	Vector3 new_position=position;
	Vector3 new_lookAt=lookAt;

	//POSITION
	displacement=position.distance(pCamera->getPosition());
	if(displacement>mMaxDisplacementPerSecond*elapsedTime)
	{
		direction=position-pCamera->getPosition();
		direction.normalise();
		
		new_position=pCamera->getPosition()+direction*mMaxDisplacementPerSecond*elapsedTime;
	}
	pCamera->setPosition(new_position);

	//ORIENTATION
	mDummyCamera->setPosition(pCamera->getPosition());
	mDummyCamera->lookAt(lookAt);

	double new_roll,new_pitch,new_yaw;
	double current_roll,current_pitch,current_yaw;
	new_roll=mDummyCamera->getOrientation().getRoll().valueDegrees();
	new_pitch=mDummyCamera->getOrientation().getPitch().valueDegrees();
	new_yaw=mDummyCamera->getOrientation().getYaw().valueDegrees();

	current_roll=pCamera->getOrientation().getRoll().valueDegrees();
	current_pitch=pCamera->getOrientation().getPitch().valueDegrees();
	current_yaw=pCamera->getOrientation().getYaw().valueDegrees();

	//if(Ogre::Math::Abs(current_roll-new_roll)>mMaxRotationPerSecond*elapsedTime)
	//{

	//}
	//else if(Ogre::Math::Abs(current_pitch-new_pitch)>mMaxRotationPerSecond*elapsedTime)
	//{

	//}
	//else if(Ogre::Math::Abs(current_yaw-new_yaw)>mMaxRotationPerSecond*elapsedTime)
	//{

	//}

	pCamera->setOrientation(mDummyCamera->getOrientation());
	//pCamera->yaw(Ogre::Degree(new_yaw));
	//pCamera->roll(Ogre::Degree(new_roll));
	//pCamera->pitch(Ogre::Degree(new_pitch));

}

Ogre::Vector3 CameraControllerThirdPersonAuto::calculateTargetPosition(CameraInputPtr pCameraInput)
{
	Ogre::Vector3 target;

	Ogre::Vector3 real_target;

	real_target=pCameraInput->mTarget->getSceneNode()->getPosition();

	if(pCameraInput->mTarget->isOnSurface() || real_target.y<mLastSurfacePosition.y)
	{
		target = real_target;
	}
	else
	{
		target = Vector3(real_target.x, mLastSurfacePosition.y,real_target.z);
	}

	target+=pCameraInput->mTargetOffset;

	return target;
}

void CameraControllerThirdPersonAuto::updateLastSurface(Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	if(pCameraInput->mTarget->isOnSurface())
	{
		mLastSurfaceAngle=pCamera->getOrientation().getYaw().valueDegrees();
		mLastSurfacePosition=pCameraInput->mTarget->getSceneNode()->getPosition();
	}
}

Ogre::Vector3 CameraControllerThirdPersonAuto::calculateCameraPosition(Ogre::Camera * pCamera,CameraInputPtr pCameraInput)
{
	Vector3 targetPosition;
	Vector3 cameraPosition;
	targetPosition=pCameraInput->mTarget->getSceneNode()->getPosition();
	cameraPosition=pCamera->getPosition();

	double distance=calculateDistanceToTarget(pCamera,pCameraInput,true);

	Vector3 direction=Vector3(cameraPosition.x-targetPosition.x,
							0.0f,
							cameraPosition.z-targetPosition.z);
	direction.normalise();
	
	if(distance>pCameraInput->mCameraParameters->mMaxDistance)
	{
		cameraPosition=Vector3(direction.x*pCameraInput->mCameraParameters->mMaxDistance+targetPosition.x,
						   0.0f,
						   direction.z*pCameraInput->mCameraParameters->mMaxDistance+targetPosition.z);
	}
	else if(distance<pCameraInput->mCameraParameters->mMinDistance)
	{
		cameraPosition=Vector3(direction.x*pCameraInput->mCameraParameters->mMinDistance+targetPosition.x,
						   0.0f,
						   direction.z*pCameraInput->mCameraParameters->mMinDistance+targetPosition.z);
	}

	cameraPosition.y=calculateCameraHeight(pCamera,pCameraInput);

	return cameraPosition;
}

void CameraControllerThirdPersonAuto::loadInfo()
{
	CameraController::loadInfo();

	Configuration config;
	std::string value;

	if (config.loadFromFile(CAMERA_CONTROLLER_THIRD_PERSON_AUTO_CFG))
	{
		config.getOption("ROTATION_DEGREES_PER_SECOND", value); 
		mRotationDegreesPerSecond = atof(value.c_str());

		config.getOption("MAX_DISPLACEMENT_PER_SECOND", value); 
		mMaxDisplacementPerSecond = atof(value.c_str());

		config.getOption("MAX_ROTATION_PER_SECOND", value); 
		mMaxRotationPerSecond = atof(value.c_str());
	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CONTROLLER_THIRD_PERSON_AUTO_CFG + " COULD NOT BE LOADED!");
	}
}

Ogre::Vector3 CameraControllerThirdPersonAuto::calculateCircumferenceMovement(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds)
{
	//calculate circumference movement around camera

	double radium;
	double time_fraction;
	
	radium=calculateDistanceToTarget(pCamera,pCameraInput,true);
	if(radium!=0)
	{
		double total_time=elapsedSeconds;
		while(total_time>0)
		{
			total_time-=1;
			if(total_time>0)
			{
				time_fraction=1;
			}
			else
			{
				time_fraction=1-Ogre::Math::Abs(total_time);
			}
			movement = Ogre::Quaternion(Ogre::Degree(((Ogre::Math::TWO_PI)*movement.x*mRotationDegreesPerSecond*time_fraction)/radium),Ogre::Vector3::UNIT_Y) * movement;
		}
	}
	return movement;

}

Ogre::Vector3 CameraControllerThirdPersonAuto::rotateMovementVector(Ogre::Vector3 movement,Ogre::Camera * pCamera,CameraInputPtr pCameraInput,double elapsedSeconds)
{
	//Logger::getInstance()->log("ROTATE MOVEMENT VECTOR");
	//Logger::getInstance()->log("Original movement : "+Ogre::StringConverter::toString(movement));
	//Logger::getInstance()->log("pCameraInput->mTarget->isOnSurface() : "+Ogre::StringConverter::toString(pCameraInput->mTarget->isOnSurface()));

	if(pCameraInput->mTarget->isOnSurface())
	{
		movement = calculateCircumferenceMovement(movement,pCamera,pCameraInput,elapsedSeconds);
	//Logger::getInstance()->log("Rotated movement1 : "+Ogre::StringConverter::toString(movement));

		movement = Ogre::Quaternion(Ogre::Degree(pCamera->getOrientation().getYaw().valueDegrees()-180),Ogre::Vector3::UNIT_Y) * movement;
	}
	else
	{
		movement = Ogre::Quaternion(Ogre::Degree(mLastSurfaceAngle-180),Ogre::Vector3::UNIT_Y) * movement;
	}

	//Logger::getInstance()->log("Rotated movement2 : "+Ogre::StringConverter::toString(movement));
	//Logger::getInstance()->log("radium : "+Ogre::StringConverter::toString(Ogre::Real(radium)));

	return movement;
}

double CameraControllerThirdPersonAuto::calculateCameraHeight(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	double h;
	double distance;
	double relative_distance;

	//To avoid division by 0
	if(pCameraInput->mCameraParameters->mMinDistance==pCameraInput->mCameraParameters->mMaxDistance)
		return pCameraInput->mCameraParameters->mMaxH;
	if(pCameraInput->mCameraParameters->mMaxH==pCameraInput->mCameraParameters->mMinH)
		return pCameraInput->mCameraParameters->mMaxH;

	//calculate relative distance between min and max distance
	distance=calculateDistanceToTarget(pCamera,pCameraInput,true);

	relative_distance=(distance-pCameraInput->mCameraParameters->mMinDistance)/(pCameraInput->mCameraParameters->mMaxDistance-pCameraInput->mCameraParameters->mMinDistance);

	//normalize relative distance
	if(relative_distance<0)
		relative_distance=0;

	if(relative_distance>1)
		relative_distance=1;

	//calculate h
	h=pCameraInput->mCameraParameters->mMinH+relative_distance*(pCameraInput->mCameraParameters->mMaxH-pCameraInput->mCameraParameters->mMinH);

	return h;
}

void CameraControllerThirdPersonAuto::setCameraParameters(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	centerCamera(pCamera,pCameraInput);
	updateLastSurface(pCamera,pCameraInput);
}

void CameraControllerThirdPersonAuto::centerCamera(Ogre::Camera *pCamera,CameraInputPtr pCameraInput)
{
	Vector3 cameraPosition;
	Vector3 targetPosition;
	Vector3 direction;

	targetPosition=pCameraInput->mTarget->getSceneNode()->getPosition();

	direction=Vector3(pCameraInput->mCameraParameters->mDirection.x,0,pCameraInput->mCameraParameters->mDirection.z);
	direction.normalise();
	direction = Ogre::Quaternion(Ogre::Degree(pCameraInput->mTarget->getSceneNode()->getOrientation().getYaw().valueDegrees()-180),Ogre::Vector3::UNIT_Y) * direction;

	cameraPosition=Vector3(direction.x*pCameraInput->mCameraParameters->mMaxDistance+targetPosition.x,
						   calculateCameraHeight(pCamera,pCameraInput),
						   direction.z*pCameraInput->mCameraParameters->mMaxDistance+targetPosition.z);

	pCamera->setPosition(cameraPosition);
}

//#include "OUAN_Precompiled.h"
//
//#include "CameraControllerThirdPersonAuto.h"
//#include "TransparentEntityManager.h"
//#include "../RenderComponent/RenderComponentPositional.h"
//#include "../RenderSubsystem.h"
//#include "../../RayCasting/RayCasting.h"
//#include "../../Loader/Configuration.h"
//#include "../../Game/GameObject/GameObject.h"
//#include "../../Game/GameObject/GameObjectViewport.h"
//#include "../../Game/GameWorldManager.h"
//
//using namespace OUAN;
//using namespace Ogre;
//
//CameraControllerThirdPersonAuto::CameraControllerThirdPersonAuto() : CameraController()
//{
//	//Set CameraControllerThirdPersonAuto Initial Parameters
//
//	loadConfig();
//
//	rotX=0;
//	rotY=0;
//	cameraMoved=false;
//
//	currentCollisionTime=0;
//	currentDistance=maxDistance;
//	mCurrentCollisionMargin=0;
//
//}
//
//CameraControllerThirdPersonAuto::~CameraControllerThirdPersonAuto()
//{
//
//}
//
//void CameraControllerThirdPersonAuto::setChangeWorldMaxDistance()
//{
//	maxDistance=maxDistanceChangeWorld;
//	targetHeight=changeWorldHeight;
//}
//void CameraControllerThirdPersonAuto::setOriginalMaxDistance()
//{
//	maxDistance=originalMaxDistance;
//	targetHeight=orignalHeight;
//}
//
//void CameraControllerThirdPersonAuto::calculateCurrentHeight(double elapsedTime)
//{
//	if(currentHeight<(targetHeight-heightMargin))
//	{
//		currentHeight+=elapsedTime*heightSpeed;
//	}
//	else if(currentHeight>(targetHeight+heightMargin))
//	{
//		currentHeight-=elapsedTime*heightSpeed;
//	}
//	else
//	{
//		currentHeight=targetHeight;
//	}
//}
//
//
//void CameraControllerThirdPersonAuto::init(RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting,GameWorldManagerPtr pGameWorldManager)
//{
//	mSceneManager = pRenderSubsystem->getSceneManager();
//
//	mRenderSubsystem = pRenderSubsystem;
//
//	mRayCasting = pRayCasting;
//
//	mTransparentEntityManager.reset(new TransparentEntityManager());
//	mTransparentEntityManager->init();
//
//	mGameWorldManager = pGameWorldManager;
//
//	CameraController::init(pRenderSubsystem->getSceneManager());
//}
//
//Ogre::Vector3 CameraControllerThirdPersonAuto::calculateCameraPosition(double distance,bool y_correction,bool applyCollisionMargin)
//{
//	Ogre::Vector3 newCameraPosition;
//
//	newCameraPosition=distance*initialDirection;
//
//	//Calculate Camera position in relation to the target
//	if(rotX<0)
//	{
//		newCameraPosition = newCameraPosition-rotXDistanceAttenuationNegative*newCameraPosition*rotX/double(minRotX);
//	}
//	else
//	{
//		newCameraPosition = newCameraPosition-rotXDistanceAttenuationPositive*newCameraPosition*rotX/double(maxRotX);
//	}
//
//	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;
//	newCameraPosition = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newCameraPosition;
//
//	//Calculate Camera position in the world
//	newCameraPosition = target->getPosition()+newCameraPosition;
//
//	if(applyCollisionMargin)
//	{
//		newCameraPosition+=Vector3(0,mCurrentCollisionMargin,0);
//	}
//
//	//jumping correction
//	//if(target->getParent()->isJumping() && y_correction && Ogre::Math::Abs(newCameraPosition.y-mCamera->getPosition().y)>maxYMovementPerFrame)
//	//{
//	//	if(newCameraPosition.y>mCamera->getPosition().y)
//	//	{
//	//		newCameraPosition.y=mCamera->getPosition().y+maxYMovementPerFrame;
//	//	}
//	//	else if(newCameraPosition.y<mCamera->getPosition().y)
//	//	{
//	//		newCameraPosition.y=mCamera->getPosition().y-maxYMovementPerFrame;
//	//	}
//	//	//newCameraPosition.y=mCamera->getPosition().y;
//	//}
//
//	//Logger::getInstance()->log("y_correction "+Ogre::StringConverter::toString(y_correction));
//
//	return newCameraPosition;
//}
//
//Ogre::Vector3 CameraControllerThirdPersonAuto::calculateCameraLookAt()
//{
//	Ogre::Vector3 cameraLookAt;
//
//	//Calculate Camera look at
//	cameraLookAt=target->getPosition()+Vector3(0,currentHeight,0);
//
//	return cameraLookAt;
//}
//
//bool CameraControllerThirdPersonAuto::calculateCameraCollisions(Ogre::Vector3 & cameraPosition, Ogre::Vector3 & cameraLookAt, Ogre::uint32 & collisionType)
//{
//	Ogre::Vector3 direction;
//	Ogre::Vector3 newCameraPosition;
//	double currentDistance;
//	Ogre::Entity * pEntity;
//	std::vector<Ogre::Entity*> allCollisions;
//	std::vector<Ogre::Entity*> transparentEntities;
//	unsigned int i;
//
//	bool hasBeenCollision=false;
//
//	currentDistance=cameraLookAt.distance(cameraPosition);
//
//	direction=cameraPosition-cameraLookAt;
//	direction.normalise();
//
//	newCameraPosition=cameraPosition;
//
//	allCollisions.clear();
//	transparentEntities.clear();
//
//	mRayCasting->raycastRenderAllGeometry(cameraLookAt,direction,newCameraPosition,pEntity,allCollisions,currentDistance,QUERYFLAGS_CAMERA_COLLISION);
//
//	if(cameraLookAt.distance(newCameraPosition)<currentDistance)
//	{
//		collisionType=pEntity->getQueryFlags();
//		cameraPosition=newCameraPosition;
//		hasBeenCollision=true;
//
//		for(i=0;i<allCollisions.size();i++)
//		{
//			if((allCollisions[i]->getQueryFlags() & OUAN::QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID) && allCollisions[i]->isVisible())
//			{
//				transparentEntities.push_back(allCollisions[i]);
//			}
//		}
//	}
//
//	mTransparentEntityManager->addCurrentCollisionTransparentEntities(transparentEntities);
//
//	return hasBeenCollision;
//}
//
//void CameraControllerThirdPersonAuto::rotateX(double rotation)
//{
//	rotX+=rotation;
//	//check if rotation exceeds limits
//	if(rotX>maxRotX)
//	{
//		rotX=maxRotX;
//	}
//	else if(rotX<minRotX)
//	{
//		rotX=minRotX;
//	}
//}
//
//void CameraControllerThirdPersonAuto::rotateY(double rotation)
//{
//	rotY+=rotation;
//}
//
//void CameraControllerThirdPersonAuto::calculateCollisionRotXNegative(double elapsedTime)
//{
//	if(lastRotX!=0)
//	{
//		rotateX(-lastRotX);
//	}
//	else if(rotX>minAutoRotX)
//	{
//		rotateX(-elapsedTime*autoRotXNegativeSpeed);
//	}
//	else
//	{
//		//if(!target->getParent()->isMoving())
//		//{
//		//	rotateY(elapsedTime*autoRotYSpeed);
//		//}
//	}
//}
//
//void CameraControllerThirdPersonAuto::calculateCollisionRotXPositive(double elapsedTime)
//{
//	if(lastRotX!=0)
//	{
//		rotateX(-lastRotX);
//	}
//	else if(rotX<maxAutoRotX)
//	{
//		rotateX(elapsedTime*autoRotXPositiveSpeed);
//	}
//	else
//	{
//		//if(!target->getParent()->isMoving())
//		//{
//		//	rotateY(elapsedTime*autoRotYSpeed);
//		//}
//	}
//}
//
//void CameraControllerThirdPersonAuto::calculateMotionBlur(double elapsedTime)
//{
//	if((Ogre::Math::Abs(lastRotX)>=mMinCameraRotationMotionBlurActivation) || (Ogre::Math::Abs(lastRotY)>=mMinCameraRotationMotionBlurActivation))
//	{
//		mGameWorldManager->getGameObjectViewport()->setEffect(mRenderSubsystem->MOTION_BLUR,false);
//		//Logger::getInstance()->log("MOTION BLUR ACTIVATED x "+Ogre::StringConverter::toString(Ogre::Math::Abs(lastRotX))+" y "+Ogre::StringConverter::toString(Ogre::Math::Abs(lastRotY)));
//
//	}
//	else if((Ogre::Math::Abs(lastRotX)<=mMinCameraRotationMotionBlurDisactivation) || (Ogre::Math::Abs(lastRotY)<=mMinCameraRotationMotionBlurDisactivation))
//	{
//		mGameWorldManager->getGameObjectViewport()->setEffect(mRenderSubsystem->MOTION_BLUR,false);
//		//Logger::getInstance()->log("MOTION BLUR DIS-ACTIVATED x "+Ogre::StringConverter::toString(Ogre::Math::Abs(lastRotX))+" y "+Ogre::StringConverter::toString(Ogre::Math::Abs(lastRotY)));
//	}
//}
//
//void CameraControllerThirdPersonAuto::update(Ogre::Camera *pCamera,CameraInputPtr pCameraInput,double elapsedTime)
//{
//	Vector3 cameraCollisionPosition;
//	Vector3 newCameraPosition;
//	Vector3 cameraLookAt;
//	Ogre::uint32 collisionType;
//
//	//calculateCurrentHeight(elapsedTime);
//
//	newCameraPosition=calculateCameraPosition(maxDistance);
//	cameraLookAt=calculateCameraLookAt();
//
//	//moving rotX correction
//	if(target->getParent()->isMoving() && !target->getParent()->cancelAutoCameraMovement())
//	{
//		if(rotX>maxCameraCenterRotX)
//		{
//			rotateX(-elapsedTime*autoRotXCenterSpeed);
//		}
//		else if(rotX<minCameraCenterRotX)
//		{
//			rotateX(elapsedTime*autoRotXCenterSpeed);
//		}
//	}
//
//	cameraCollisionPosition=newCameraPosition;
//	//Calculate camera collisions
//	if(calculateCameraCollisions(cameraCollisionPosition,cameraLookAt,collisionType))
//	{
//		currentCollisionTime+=elapsedTime;
//		if(currentCollisionTime>=minCollisionTime)
//		{
//			mCorrectingCameraPosition=true;
//			if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET)
//			{
//				mCurrentCollisionMargin=mMaxCollisionYMargin;
//				currentDistance=calculateCameraMoveToTarget(currentDistance,pCamera->getPosition(),cameraCollisionPosition,elapsedTime);
//			}
//			else if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_ROTX_NEGATIVE)
//			{
//				if(!target->getParent()->cancelAutoCameraMovement())
//				{
//					calculateCollisionRotXNegative(elapsedTime);
//				}
//			}
//			else if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_ROTX_POSITIVE)
//			{
//				if(!target->getParent()->cancelAutoCameraMovement())
//				{
//					calculateCollisionRotXPositive(elapsedTime);
//				}
//			}
//		}
//	}
//	else
//	{
//		mCorrectingCameraPosition=false;
//		currentCollisionTime=0;
//		if(currentDistance<=maxDistance)
//		{
//			currentDistance=calculateCameraReturningFromTarget(currentDistance,pCamera->getPosition(),newCameraPosition,elapsedTime);
//		}
//		else
//		{
//			currentDistance=calculateCameraMoveToTarget(currentDistance,pCamera->getPosition(),newCameraPosition,elapsedTime);
//		}
//	}
//
//	//set camera position
//	newCameraPosition=calculateCameraPosition(currentDistance,true,true);
//
//	pCamera->setPosition(newCameraPosition);
//
//	//set camera to look at target
//	pCamera->lookAt(cameraLookAt);
//
//	mTransparentEntityManager->update(elapsedTime);
//
//	calculateMotionBlur(elapsedTime);
//}
//
//void CameraControllerThirdPersonAuto::clear()
//{
//	mTransparentEntityManager->clear();
//}
//
//double CameraControllerThirdPersonAuto::calculateCameraReturningFromTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime)
//{
//	double newCameraDistance;
//
//	newCameraDistance=currentCameraDistance+=collisionReturningSpeed*elapsedTime;
//	if(newCameraDistance>=maxDistance)
//	{
//		newCameraDistance=maxDistance;
//	}
//
//	mCurrentCollisionMargin-=collisionReturningSpeed*elapsedTime;
//	if(mCurrentCollisionMargin<=0)
//	{
//		mCurrentCollisionMargin=0;
//	}
//	return newCameraDistance;
//}
//
//double CameraControllerThirdPersonAuto::calculateCameraMoveToTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime)
//{
//
//	double newCameraDistance;
//
//	newCameraDistance=currentCameraDistance-=collisionMoveSpeed*elapsedTime;
//	if (newCameraDistance<=(cameraPosition.distance(newCameraPosition)))
//	{
//		newCameraDistance=cameraPosition.distance(newCameraPosition);
//	}
//	else if (newCameraDistance<=minDistance)
//	{
//		newCameraDistance=minDistance;
//	}
//
//	return newCameraDistance;
//}
//
//
//void CameraControllerThirdPersonAuto::processCameraRotation(Ogre::Vector2 cameraRotation)
//{
//
//	//process Relative Motion
//	if(cameraRotation.x==0 && cameraRotation.y==0) 
//	{
//		lastRotX=0;
//		lastRotY=0;
//		cameraMoved=false;
//		return;
//	}
//	else
//	{
//		cameraMoved=true;
//		rotateY(-cameraRotation.x*speedY);
//		rotateX(-cameraRotation.y*speedX);
//		lastRotX=-cameraRotation.x*speedY;
//		lastRotY=-cameraRotation.y*speedX;
//	}
//
//
//	//Logger::getInstance()->log("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));
//
//}
//void CameraControllerThirdPersonAuto::setTarget(RenderComponentPositionalPtr target)
//{
//	this->target=target;
//	reset();
//}
//
//void CameraControllerThirdPersonAuto::reset()
//{
//	rotX=0;
//	rotY=0;
//	cameraMoved=false;
//
//	currentCollisionTime=0;
//	currentDistance=maxDistance;
//	mCurrentCollisionMargin=0;
//
//
//	rotY=target->getOrientation().getYaw().valueDegrees();
//
//	//mCamera->setPosition(calculateCameraPosition(maxDistance));
//	//mCamera->lookAt(calculateCameraLookAt());
//}
//
//TCameraControllerType CameraControllerThirdPersonAuto::getControllerType()
//{
//	return OUAN::CAMERA_THIRD_PERSON;
//}