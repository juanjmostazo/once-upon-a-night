#include "CameraControllerThirdPerson.h"
#include "../RenderComponent/RenderComponentPositional.h"
#include "../RenderSubsystem.h"
#include "../../RayCasting/RayCasting.h"
#include "../../Loader/Configuration.h"
#include "../../Game/GameObject/GameObject.h"

using namespace OUAN;
using namespace Ogre;

CameraControllerThirdPerson::CameraControllerThirdPerson() : CameraController()
{
	//Set CameraControllerThirdPerson Initial Parameters

	loadConfig();
	reset();
}

CameraControllerThirdPerson::~CameraControllerThirdPerson()
{

}

void CameraControllerThirdPerson::reset()
{
	rotX=0;
	rotY=0;
	cameraMoved=false;

	currentCollisionTime=0;
	currentDistance=maxDistance;

	mLastCollisionEntities.clear();
	mSolidMaterial.clear();
	mLastCollisionEntitiesAreTranslucid=false;
}

bool CameraControllerThirdPerson::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(CAMERA_CFG))
	{
		double initial_directionX, initial_directionY, initial_directionZ;

		config.getOption("INITIAL_DIRECTION_X", value); 
		initial_directionX = atof(value.c_str());

		config.getOption("INITIAL_DIRECTION_Y", value); 
		initial_directionY = atof(value.c_str());

		config.getOption("INITIAL_DIRECTION_Z", value); 
		initial_directionZ = atof(value.c_str());

		initialDirection = Vector3(initial_directionX, initial_directionY, initial_directionZ);

		config.getOption("COLLISION_MARGIN", value); 
		collisionMargin = atof(value.c_str());

		config.getOption("MIN_DISTANCE", value); 
		minDistance = atof(value.c_str());

		config.getOption("MAX_DISTANCE", value); 
		maxDistance = atof(value.c_str());

		config.getOption("TARGET_HEIGHT", value); 
		height = atof(value.c_str());

		config.getOption("SPEED_X", value); 
		speedX = atof(value.c_str());

		config.getOption("SPEED_Y", value); 
		speedY = atof(value.c_str());

		config.getOption("COLLISION_MOVE_SPEED", value); 
		collisionMoveSpeed = atof(value.c_str());

		config.getOption("COLLISION_RETURN_SPEED", value); 
		collisionReturningSpeed = atof(value.c_str());

		config.getOption("ROT_X_DISTANCE_ATTENUATION_NEGATIVE", value); 
		rotXDistanceAttenuationNegative = atof(value.c_str());

		config.getOption("ROT_X_DISTANCE_ATTENUATION_POSITIVE", value); 
		rotXDistanceAttenuationPositive = atof(value.c_str());

		config.getOption("MAX_ROT_X", value); 
		maxRotX = atof(value.c_str());

		config.getOption("MIN_ROT_X", value); 
		minRotX = atof(value.c_str());

		config.getOption("MIN_COLLISION_TIME", value); 
		minCollisionTime = atof(value.c_str());

		config.getOption("AUTO_ROT_X_POSITIVE_SPEED", value); 
		autoRotXPositiveSpeed = atof(value.c_str());

		config.getOption("AUTO_ROT_X_NEGATIVE_SPEED", value); 
		autoRotXNegativeSpeed = atof(value.c_str());

		config.getOption("AUTO_ROT_X_CENTER_SPEED", value); 
		autoRotXCenterSpeed = atof(value.c_str());

		config.getOption("MIN_AUTO_ROT_X", value); 
		minAutoRotX = atof(value.c_str());

		config.getOption("MAX_AUTO_ROT_X", value); 
		maxAutoRotX = atof(value.c_str());

		config.getOption("AUTO_ROT_Y_SPEED", value); 
		autoRotYSpeed = atof(value.c_str());

		config.getOption("MAX_Y_MOVEMENT_PER_FRAME", value); 
		maxYMovementPerFrame = atof(value.c_str());

		config.getOption("MIN_CAMERA_CENTER_ROT_X", value); 
		minCameraCenterRotX = atof(value.c_str());

		config.getOption("MAX_CAMERA_CENTER_ROT_X", value); 
		maxCameraCenterRotX = atof(value.c_str());

		success = true;
	} 
	else 
	{
		Ogre::LogManager::getSingleton().logMessage(CAMERA_CFG + " COULD NOT BE LOADED!");
		success = false;
	}

	return success;
}

void CameraControllerThirdPerson::init(RenderSubsystemPtr pRenderSubsystem,PhysicsSubsystemPtr pPhysicsSubsystem,RayCastingPtr pRayCasting)
{
	mSceneManager = pRenderSubsystem->getSceneManager();

	mRayCasting = pRayCasting;

	CameraController::init(pRenderSubsystem->getSceneManager());
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraPosition(double distance,bool y_correction)
{
	Ogre::Vector3 newCameraPosition;

	newCameraPosition=distance*initialDirection;

	//Calculate Camera position in relation to the target
	if(rotX<0)
	{
		newCameraPosition = newCameraPosition-rotXDistanceAttenuationNegative*newCameraPosition*rotX/double(minRotX);
	}
	else
	{
		newCameraPosition = newCameraPosition-rotXDistanceAttenuationPositive*newCameraPosition*rotX/double(maxRotX);
	}

	newCameraPosition = Quaternion(Ogre::Degree(rotX), Vector3::UNIT_X) * newCameraPosition;
	newCameraPosition = Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * newCameraPosition;

	//Calculate Camera position in the world
	newCameraPosition = target->getPosition()+newCameraPosition;

	//jumping correction
	//if(target->getParent()->isJumping() && y_correction && Ogre::Math::Abs(newCameraPosition.y-mCamera->getPosition().y)>maxYMovementPerFrame)
	//{
	//	if(newCameraPosition.y>mCamera->getPosition().y)
	//	{
	//		newCameraPosition.y=mCamera->getPosition().y+maxYMovementPerFrame;
	//	}
	//	else if(newCameraPosition.y<mCamera->getPosition().y)
	//	{
	//		newCameraPosition.y=mCamera->getPosition().y-maxYMovementPerFrame;
	//	}
	//	//newCameraPosition.y=mCamera->getPosition().y;
	//}

	//Ogre::LogManager::getSingleton().logMessage("y_correction "+Ogre::StringConverter::toString(y_correction));

	return newCameraPosition;
}

Ogre::Vector3 CameraControllerThirdPerson::calculateCameraLookAt()
{
	Ogre::Vector3 cameraLookAt;

	//Calculate Camera look at
	cameraLookAt=target->getPosition()+Vector3(0,height,0);

	return cameraLookAt;
}

void CameraControllerThirdPerson::makeCollisionEntitiesSolid()
{
	unsigned int i,j,k;
	Ogre::Entity * pEntity;
	Ogre::MaterialPtr material;

	mLastCollisionEntitiesAreTranslucid=false;

	k=0;

	for(j=0;j<mLastCollisionEntities.size();j++)
	{
		pEntity=mLastCollisionEntities[j];
	
		for ( i = 0; i < pEntity->getNumSubEntities(); ++i)
		{
			// Apply the cloned material to the sub entity.
			Ogre::SubEntity* subEnt = pEntity->getSubEntity(i);
			material=mSolidMaterial[k];
			subEnt->setMaterial(material);
			k++;
		}
	}

}

void CameraControllerThirdPerson::makeCollisionEntitiesTranslucid(std::vector<Ogre::Entity*> & collisionEntities)
{
	unsigned int i,j;
	std::string materialName;
	Ogre::Entity * pEntity;
	Ogre::uint32 currentCollisionType;

	mLastCollisionEntities.clear();
	mSolidMaterial.clear();
	mLastCollisionEntitiesAreTranslucid=true;

	for(i=0;i<collisionEntities.size();i++)
	{
		currentCollisionType=collisionEntities[i]->getQueryFlags();

		if(currentCollisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_TRANSLUCID)
		{
			mLastCollisionEntities.push_back(collisionEntities[i]);
		}
	}

	for(j=0;j<mLastCollisionEntities.size();j++)
	{


		pEntity=mLastCollisionEntities[j];

		for ( i = 0; i < pEntity->getNumSubEntities(); ++i)
		{
			// Get the material of this sub entity and build the clone material name
			Ogre::SubEntity* subEnt = pEntity->getSubEntity(i);
			Ogre::MaterialPtr material = subEnt->getMaterial();

			materialName=material->getName()+"-TRANSLUCID";

			// Get/Create the clone material
			Ogre::MaterialPtr clone;
			if (Ogre::MaterialManager::getSingleton().resourceExists(materialName))
			{
				clone = Ogre::MaterialManager::getSingleton().getByName(materialName);
			}
			else
			{
				// Clone the material
				clone = material->clone(materialName);

				// Make it translucid
				Ogre::Technique * technique;
				Ogre::Pass * pass;
					//get technique
				technique = clone->getTechnique(0);
					//set current pass attributes
				pass = technique->getPass(0);
				pass->setSceneBlending(Ogre::SBT_TRANSPARENT_COLOUR);			
				pass->setDepthCheckEnabled(false);
			}

			//Apply the cloned material to the sub entity.
			subEnt->setMaterial(clone);

			//Add material to the material stack 
			mSolidMaterial.push_back(material);
		}
	}
}

bool CameraControllerThirdPerson::calculateCameraCollisions(Ogre::Vector3 & cameraPosition, Ogre::Vector3 & cameraLookAt, Ogre::uint32 & collisionType)
{
	Ogre::Vector3 direction;
	Ogre::Vector3 newCameraPosition;
	double currentDistance;
	Ogre::Entity * pEntity;
	std::vector<Ogre::Entity*> allCollisions;

	currentDistance=cameraLookAt.distance(cameraPosition);

	direction=cameraPosition-cameraLookAt;
	direction.normalise();

	newCameraPosition=cameraPosition;

	mRayCasting->raycastRenderAllGeometry(cameraLookAt,direction,newCameraPosition,pEntity,allCollisions,currentDistance,QUERYFLAGS_CAMERA_COLLISION);

	if(cameraLookAt.distance(newCameraPosition)<currentDistance)
	{

		makeCollisionEntitiesTranslucid(allCollisions);

		collisionType=pEntity->getQueryFlags();
		cameraPosition=newCameraPosition-collisionMargin*direction;

		return true;
	}

	return false;
}

void CameraControllerThirdPerson::rotateX(double rotation)
{
	rotX+=rotation;
	//check if rotation exceeds limits
	if(rotX>maxRotX)
	{
		rotX=maxRotX;
	}
	else if(rotX<minRotX)
	{
		rotX=minRotX;
	}
}

void CameraControllerThirdPerson::rotateY(double rotation)
{
	rotY+=rotation;
}

void CameraControllerThirdPerson::calculateCollisionRotXNegative(double elapsedTime)
{
	if(lastRotX!=0)
	{
		rotateX(-lastRotX);
	}
	else if(rotX>minAutoRotX)
	{
		rotateX(-elapsedTime*autoRotXNegativeSpeed);
	}
	else
	{
		//if(!target->getParent()->isMoving())
		//{
		//	rotateY(elapsedTime*autoRotYSpeed);
		//}
	}
}

void CameraControllerThirdPerson::calculateCollisionRotXPositive(double elapsedTime)
{
	if(lastRotX!=0)
	{
		rotateX(-lastRotX);
	}
	else if(rotX<maxAutoRotX)
	{
		rotateX(elapsedTime*autoRotXPositiveSpeed);
	}
	else
	{
		//if(!target->getParent()->isMoving())
		//{
		//	rotateY(elapsedTime*autoRotYSpeed);
		//}
	}
}

void CameraControllerThirdPerson::update(double elapsedTime)
{
	Vector3 cameraCollisionPosition;
	Vector3 newCameraPosition;
	Vector3 cameraLookAt;
	Ogre::uint32 collisionType;

	if(mLastCollisionEntitiesAreTranslucid)
	{
		makeCollisionEntitiesSolid();
	}

	newCameraPosition=calculateCameraPosition(maxDistance);
	cameraLookAt=calculateCameraLookAt();

	//moving rotX correction
	if(target->getParent()->isMoving() && !target->getParent()->cancelAutoCameraMovement())
	{
		if(rotX>maxCameraCenterRotX)
		{
			rotateX(-elapsedTime*autoRotXCenterSpeed);
		}
		else if(rotX<minCameraCenterRotX)
		{
			rotateX(elapsedTime*autoRotXCenterSpeed);
		}
	}

	cameraCollisionPosition=newCameraPosition;
	//Calculate camera collisions
	if(calculateCameraCollisions(cameraCollisionPosition,cameraLookAt,collisionType) && !target->getParent()->cancelAutoCameraMovement())
	{
		currentCollisionTime+=elapsedTime;
		if(currentCollisionTime>=minCollisionTime)
		{
			mCorrectingCameraPosition=true;
			if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_MOVE_TO_TARGET)
			{
				currentDistance=calculateCameraMoveToTarget(currentDistance,mCamera->getPosition(),cameraCollisionPosition,elapsedTime);
			}
			else if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_ROTX_NEGATIVE)
			{
				calculateCollisionRotXNegative(elapsedTime);
			}
			else if(collisionType & OUAN::QUERYFLAGS_CAMERA_COLLISION_ROTX_POSITIVE)
			{
				calculateCollisionRotXPositive(elapsedTime);
			}
		}
	}
	else
	{
		mCorrectingCameraPosition=false;
		currentCollisionTime=0;
		currentDistance=calculateCameraReturningFromTarget(currentDistance,mCamera->getPosition(),newCameraPosition,elapsedTime);
	}

	//set camera position
	newCameraPosition=calculateCameraPosition(currentDistance);

	mCamera->setPosition(newCameraPosition);

	//set camera to look at target
	mCamera->lookAt(cameraLookAt);
}

double CameraControllerThirdPerson::calculateCameraReturningFromTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime)
{
	double newCameraDistance;

	newCameraDistance=currentCameraDistance+=collisionReturningSpeed*elapsedTime;
	if(newCameraDistance>=maxDistance)
	{
		newCameraDistance=maxDistance;
	}
	return newCameraDistance;
}

double CameraControllerThirdPerson::calculateCameraMoveToTarget(double currentCameraDistance, Ogre::Vector3 cameraPosition,Ogre::Vector3 newCameraPosition,double elapsedTime)
{

	double newCameraDistance;

	newCameraDistance=currentCameraDistance-=collisionMoveSpeed*elapsedTime;
	if (newCameraDistance<=(cameraPosition.distance(newCameraPosition)))
	{
		newCameraDistance=cameraPosition.distance(newCameraPosition);
	}
	else if (newCameraDistance<=minDistance)
	{
		newCameraDistance=minDistance;
	}

	return newCameraDistance;
}

Ogre::Vector3 CameraControllerThirdPerson::rotateMovementVector(Ogre::Vector3 movement)
{
	return Quaternion(Ogre::Degree(rotY), Vector3::UNIT_Y) * movement;
}

void CameraControllerThirdPerson::processCameraRotation(Ogre::Vector2 cameraRotation)
{

	//process Relative Motion
	if(cameraRotation.x==0 && cameraRotation.y==0) 
	{
		lastRotX=0;
		lastRotY=0;
		cameraMoved=false;
		return;
	}
	else
	{
		cameraMoved=true;
		rotateY(-cameraRotation.x*speedY);
		rotateX(-cameraRotation.y*speedX);
		lastRotX=-cameraRotation.x*speedY;
		lastRotY=-cameraRotation.y*speedX;
	}


	//Ogre::LogManager::getSingleton().logMessage("rotations "+Ogre::StringConverter::toString(Ogre::Real(rotX))+" "+Ogre::StringConverter::toString(Ogre::Real(rotY)));

}
void CameraControllerThirdPerson::setTarget(RenderComponentPositionalPtr target)
{
	this->target=target;
	resetPosition();
}

void CameraControllerThirdPerson::resetPosition()
{
	reset();
	rotY=target->getOrientation().getYaw().valueDegrees();
	mCamera->setPosition(calculateCameraPosition(maxDistance,false));
}

TCameraControllerType CameraControllerThirdPerson::getControllerType()
{
	return OUAN::CAMERA_THIRD_PERSON;
}