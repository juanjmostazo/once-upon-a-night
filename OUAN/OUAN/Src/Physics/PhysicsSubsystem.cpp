#include "OUAN_Precompiled.h"

#include "PhysicsSubsystem.h"
#include "PhysicsComponent/PhysicsComponent.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectPillow.h"
#include "../Game/GameObject/GameObjectFlashLight.h"
#include "../Game/GameObject/GameObjectFlashLight.h"
#include "../Event/EventProcessor.h"
#include "../Event/Event.h"

using namespace OUAN;

PhysicsSubsystem::PhysicsSubsystem()
{
	mNxOgreWorld = NULL;
	mNxOgreScene = NULL;
	mNxOgreRenderSystem = NULL;
	mNxOgreTimeController = NULL;
	mNxOgreControllerManager = NULL;
}

PhysicsSubsystem::~PhysicsSubsystem()
{

}

void PhysicsSubsystem::init(ApplicationPtr app,OUAN::ConfigurationPtr config)
{
	Logger::getInstance()->log("[PHYSICS GENERAL INIT STARTED]");

	loadConfig();

	mApp=app;
	mConfig=config;

	Logger::getInstance()->log("[PHYSICS GENERAL INIT FINISHED]");
}

void PhysicsSubsystem::cleanUp()
{
	Logger::getInstance()->log("[PHYSICS GENERAL CLEANUP STARTED]");
	clear();
	Logger::getInstance()->log("[PHYSICS GENERAL CLEANUP FINISHED]");
}

void PhysicsSubsystem::initLevel(std::string sceneName)
{	
	Logger::getInstance()->log("[PHYSICS LEVEL INIT STARTED]");

	Logger::getInstance()->log("PHYSICS: Creating NxOgre::World");
	mNxOgreWorld = NxOgre::World::createWorld();

	Logger::getInstance()->log("PHYSICS: Loading nxs resources");
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	Logger::getInstance()->log("PHYSICS: Setting up scene description");
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = mGravity * mGravityBodiesFactor;
	sceneDesc.mName = NxOgre::String(sceneName.c_str());

	Logger::getInstance()->log("PHYSICS: Creating scene");
	mNxOgreScene = mNxOgreWorld->createScene(sceneDesc);
	
	Logger::getInstance()->log("PHYSICS: Creating render system");
	mNxOgreRenderSystem = new OGRE3DRenderSystem(mNxOgreScene);

	Logger::getInstance()->log("PHYSICS: Creating time controller");
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	Logger::getInstance()->log("PHYSICS: Creating controller manager");
	mNxOgreControllerManager = new NxOgre::ControllerManager();

	Logger::getInstance()->log("PHYSICS: Setting up scene");
	mNxOgreScene->getMaterial(0)->setStaticFriction(mStaticFriction);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(mDynamicFriction);
	mNxOgreScene->getMaterial(0)->setRestitution(mRestitution);

	Logger::getInstance()->log("PHYSICS: Creating visual debugger");
	mApp->getRenderSubsystem()->createVisualDebugger(mConfig);
	
	//Logger::getInstance()->log("PHYSICS: Creating debug floor");
	//NxOgre::PlaneGeometry* pDebugPlane = new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0));
	//pDebugPlane->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
	//mNxOgreScene->createSceneGeometry(pDebugPlane, Matrix44_Identity);
	//mApp->getRenderSubsystem()->createDebugFloor(mConfig);

	Logger::getInstance()->log("[PHYSICS LEVEL INIT FINISHED]");
}

void PhysicsSubsystem::clear()
{
	Logger::getInstance()->log("[PHYSICS LEVEL CLEAR STARTED]");

	//We destroy the scene, is this needed?
	// TODO: Iterate over 
	// Application::getInstance()->getGameWorldManager()->getGameObjectPhysicsContainer() 
	// and call destroy() method

	if (mNxOgreControllerManager)
	{
		Logger::getInstance()->log("PHYSICS: destroying controller manager");
		delete mNxOgreControllerManager;
		mNxOgreControllerManager=NULL;
	}

	if (mNxOgreRenderSystem)
	{
		Logger::getInstance()->log("PHYSICS: render system");
		try
		{
			delete mNxOgreRenderSystem;
		}
		catch (...)
		{
			throw std::exception ("PhysicsSubsystem::clear - Exception deleting mNxOgreRenderSystem");
		}
		mNxOgreRenderSystem=NULL;
	}
	
	if (mNxOgreWorld)
	{
		Logger::getInstance()->log("PHYSICS: Destroying world & scene");
		mNxOgreWorld->destroyWorld(); //Scene is also destroyed here
		mNxOgreWorld=NULL;
		mNxOgreScene=NULL; 
	}

	//Logger::getInstance()->log("[PHYSICS LEVEL CLEAR FINISHED]");
}

void PhysicsSubsystem::update(double elapsedSeconds)
{
	/*
	std::stringstream out;
	out << elapsedSeconds;
	std::string elapsedTime = out.str();
	Logger::getInstance()->log("Advancing " + elapsedTime + " seconds");
	*/
	//Logger::getInstance()->log("[PHYSICS UPDATE]");

	if (mApp)
	{
		mApp->getGameWorldManager()->getEventProcessor()->startNewFrame();
		TGameObjectContainer * container = mApp->getGameWorldManager()->getAllGameObjects();
		
		if (!container->empty())
		{
			for (TGameObjectContainer::iterator it=container->begin();it!=container->end();++it)
			{
				//Logger::getInstance()->log("UPDATE PHYSICS "+it->second->getName());
				if (it->second->hasPhysicsComponent() && it->second->isWorthUpdatingPhysicsComponents())
				{
					if(it->second->getType().compare(GAME_OBJECT_TYPE_ONY)!=0)
					{
						it->second->updatePhysicsComponents(elapsedSeconds);
					}
				}
			}
		}
	}

	if(mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacterOny()->isInUse())
	{
		mApp->getGameWorldManager()->getGameObjectOny()->getPhysicsComponentCharacterOny()->update(elapsedSeconds);
	}

	//update pillow
	if(mApp->getGameWorldManager()->getGameObjectPillow()->getPhysicsComponentWeapon()->isInUse())
	{
		mApp->getGameWorldManager()->getGameObjectPillow()->getPhysicsComponentWeapon()->update(elapsedSeconds);
	}

	//update flashlight
	if(mApp->getGameWorldManager()->getGameObjectFlashLight()->getPhysicsComponentWeapon()->isInUse())
	{
		mApp->getGameWorldManager()->getGameObjectFlashLight()->getPhysicsComponentWeapon()->update(elapsedSeconds);
	}

	mNxOgreTimeController->advance(elapsedSeconds);
}

void PhysicsSubsystem::stabilize()
{
	unsigned int i;

	if (mApp)
	{
		TGameObjectPhysicsContainer * container = mApp->getGameWorldManager()->getGameObjectPhysicsContainer();
		
		if (!container->empty())
		{
			for (i=0;i<container->size();i++)
			{
				if(container->at(i)->hasPhysicsComponent())
				{
					GameObjectPtr obj=container->at(i);
					obj->getPhysicsComponent()->stabilize(mStabilizeSeconds);
				}
			}
		}
	}

	//update pillow
	if(mApp->getGameWorldManager()->getGameObjectPillow()->getPhysicsComponentWeapon()->isInUse())
	{
		mApp->getGameWorldManager()->getGameObjectPillow()->getPhysicsComponentWeapon()->update(mStabilizeSeconds);
	}

	//update flashlight
	if(mApp->getGameWorldManager()->getGameObjectFlashLight()->getPhysicsComponentWeapon()->isInUse())
	{
		mApp->getGameWorldManager()->getGameObjectFlashLight()->getPhysicsComponentWeapon()->update(mStabilizeSeconds);
	}

	mNxOgreTimeController->advance(mStabilizeSeconds);
	Logger::getInstance()->log("STABILIZING ENDED");
}

bool PhysicsSubsystem::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(PHYSICS_CFG))
	{
		double gravityX, gravityY, gravityZ;

		config.getOption("GRAVITY_X", value); 
		gravityX = atof(value.c_str());

		config.getOption("GRAVITY_Y", value); 
		gravityY = atof(value.c_str());

		config.getOption("GRAVITY_Z", value); 
		gravityZ = atof(value.c_str());

		mGravity = NxOgre::Vec3(gravityX, gravityY, gravityZ);

		config.getOption("STATIC_FRICTION", value); 
		mStaticFriction = atof(value.c_str());

		config.getOption("DYNAMIC_FRICTION", value); 
		mDynamicFriction = atof(value.c_str());

		config.getOption("RESTITUTION", value); 
		mRestitution = atof(value.c_str());

		config.getOption("DISPLACEMENT_SCALE", value); 
		mDisplacementScale = atof(value.c_str());

		config.getOption("MIN_DISTANCE", value); 
		mMinDistance = atof(value.c_str());

		config.getOption("MOVEMENT_UNITS_PER_SECOND", value); 
		mMovementUnitsPerSecond = atof(value.c_str());
		mMovementUnitsPerSecondInverseScaled = mMovementUnitsPerSecond / mDisplacementScale;

		config.getOption("MOVEMENT_LIMIT_UNITS_PER_SECOND", value); 
		mMovementLimitUnitsPerSecond = atof(value.c_str());
		mMovementLimitUnitsPerSecondInverseScaled = mMovementLimitUnitsPerSecond / mDisplacementScale;

		config.getOption("TURN_DEGREES_PER_SECOND", value); 
		mTurnDegreesPerSecond = atof(value.c_str());

		config.getOption("MIN_ALLOWED_Y", value); 
		mMinAllowedY = atof(value.c_str());

		config.getOption("MIN_COLLISION_ANGLE", value); 
		mMinCollisionAngle = atof(value.c_str());

		config.getOption("MIN_SLIDING_ANGLE", value); 
		mMinSlidingAngle = atof(value.c_str());

		config.getOption("SLIDING_UNITS_PER_SECOND", value); 
		mSlidingUnitsPerSecond = atof(value.c_str());

		config.getOption("DASH_FACTOR", value); 
		mDashFactor = atof(value.c_str());

		config.getOption("MAX_DASH", value); 
		mDashMax = atof(value.c_str());

		config.getOption("DASH_ACCELERATION_INCREMENT", value); 
		mDashAccelerationIncrement = atof(value.c_str());

		config.getOption("DASH_ACCELERATION_FACTOR_MIN", value); 
		mMinDashAccelerationFactor = atof(value.c_str());

		config.getOption("DASH_ACCELERATION_FACTOR_MAX", value); 
		mMaxDashAccelerationFactor = atof(value.c_str());

		config.getOption("ACCELERATION_INCREMENT", value); 
		mAccelerationIncrement = atof(value.c_str());

		config.getOption("ACCELERATION_FACTOR_MIN", value); 
		mMinAccelerationFactor = atof(value.c_str());

		config.getOption("ACCELERATION_FACTOR_MAX", value); 
		mMaxAccelerationFactor = atof(value.c_str());

		config.getOption("MAX_SAME_DIRECTION_ANGLE", value); 
		mMaxSameDirectionAngle = atof(value.c_str());

		config.getOption("WALK_SPEED_FACTOR", value); 
		mWalkSpeedFactor = atof(value.c_str());

		config.getOption("SLOPE_LIMIT", value); 
		mSlopeLimit = atof(value.c_str());

		config.getOption("STEP_OFFSET", value); 
		mStepOffset= atof(value.c_str());

		config.getOption("SKIN_WIDTH", value); 
		mSkinWidth = atof(value.c_str());

		config.getOption("GRAVITY_BODIES_FACTOR", value); 
		mGravityBodiesFactor = atof(value.c_str());

		config.getOption("CYCLIC_MAX_OFFSET", value); 
		mCyclicMaxOffset = atof(value.c_str());

		config.getOption("CYCLIC_SPEED", value); 
		mCyclicSpeed = atof(value.c_str());

		config.getOption("IMPULSE_HEIGHT", value); 
		mImpulseHeight = atof(value.c_str());

		config.getOption("IMPULSE_TIME", value); 
		mImpulseTime = atof(value.c_str());

		config.getOption("FALLING_TIME_LIMIT", value); 
		mFallingTimeLimit = atof(value.c_str());

		config.getOption("TURN_UNITS_PER_SECOND", value); 
		mTurnUnitsPerSecond = atof(value.c_str());

		config.getOption("STABILIZE_SECONDS", value); 
		mStabilizeSeconds = atof(value.c_str());

		config.getOption("STABILIZE_CHARACTER_MOVE_Y", value); 
		mStabilizeCharacterMoveY = atof(value.c_str());


		success = true;
	} 
	else 
	{
		//Logger::getInstance()->log(PHYSICS_CFG + " COULD NOT BE LOADED!");
		success = false;
	}

	//	config.~Configuration();
	return success;
}

NxOgre::World* PhysicsSubsystem::getNxOgreWorld()
{
	return mNxOgreWorld;
}

NxOgre::Scene* PhysicsSubsystem::getNxOgreScene()
{
	return mNxOgreScene;
}

OGRE3DRenderSystem* PhysicsSubsystem::getNxOgreRenderSystem()
{
	return mNxOgreRenderSystem;
}

NxOgre::TimeController* PhysicsSubsystem::getNxOgreTimeController()
{
	return mNxOgreTimeController;
}

NxOgre::ControllerManager* PhysicsSubsystem::getNxOgreControllerManager()
{
	return mNxOgreControllerManager;	
}

GameObjectPtr PhysicsSubsystem::getGameObject(NxOgre::String name)
{
	return mApp->getGameWorldManager()->getObject(std::string(name.c_str()));
}

//////////////////////////////////////////////////////////////////
// General physics callbacks

bool PhysicsSubsystem::onHitEvent(const NxOgre::RaycastHit& raycastHit)
{
	//Logger::getInstance()->log("On Hit Event");

	GameObjectPtr pGameObject;

	pGameObject=getGameObject(raycastHit.name.c_str());
	if(pGameObject)
	{
		if(pGameObject->getType()!=GAME_OBJECT_TYPE_ONY)
		{
			Logger::getInstance()->log("RAYCAST HIT "+pGameObject->getName());
		}
		////
		//CharacterShapeFrontCollisionEventPtr evt = CharacterShapeFrontCollisionEventPtr(
		//	new CharacterShapeFrontCollisionEvent(
		//		pGameObject, 
		//		pGameObject));

		//mApp->getGameWorldManager()->addEvent(evt);
	}
	else
	{
		//Logger::getInstance()->log("General-Physics-Function onHitEvent called!");
	}

	return true;
}

void PhysicsSubsystem::onContact(const NxOgre::ContactPair& contactPair)
{
	Logger::getInstance()->log("General-Physics-Function onContact called!");
}

//////////////////////////////////////////////////////////////////
// Character physics callbacks

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	//double normalAngle = acos(hit.mWorldNormal.y) * TO_DEGREES;
	//setGameObjectSlidingFromController(hit.mController, hit.mWorldNormal, normalAngle);

	GameObjectPtr pGameObjectController = getGameObject(hit.mControllerName);
	GameObjectPtr pGameObjectShape = getGameObject(hit.mShapeName);

	//if( pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)!=0) 
	//	&& pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_PILLOW)!=0)
		//&& normalAngle<=mSlidingUnitsPerSecond)
	//{
	//	if(pGameObjectController->hasPhysicsComponent())
	//	{
	//		pGameObjectController->getPhysicsComponent()->setOnSurface(true);
	//	}
	//}
	
	//Logger::getInstance()->log("## Collision between " + pGameObjectController->getName() + " and " + pGameObjectShape->getName());

	if(!(pGameObjectShape->getName().compare(pGameObjectController->getName())==0))
	{
		sendCollision(pGameObjectController,pGameObjectShape,hit.mWorldNormal.as<Ogre::Vector3>());
	}
	
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(const NxOgre::ControllerControllerHit& hit)
{	
	GameObjectPtr pGameObjectController = getGameObject(hit.mControllerName);
	GameObjectPtr pGameObjectOtherController = getGameObject(hit.mOtherControllerName);

	//Logger::getInstance()->log("ON CONTROLLER");

	if(!(pGameObjectController->getName().compare(pGameObjectOtherController->getName())==0))
	{
		sendCollision(pGameObjectController,pGameObjectOtherController);
	}
	
	return NxOgre::Enums::ControllerAction_None;
}

void PhysicsSubsystem::onVolumeEvent(NxOgre::Shape * volume,  NxOgre::String collisionName, unsigned int collisionEventType)
{
	//Logger::getInstance()->log("ON VOLUME EVENT volume "+std::string(hit.mVolumeShapeName.c_str()));//+" "+std::string(collisionShape->getName().c_str()));
	//Logger::getInstance()->log("ON VOLUME EVENT character "+std::string(hit.mCollisionShapeName.c_str()));

	GameObjectPtr pGameObjectVolume=getGameObject(volume->getName());
	GameObjectPtr pGameObjectShape=getGameObject(collisionName);
	
	//bool dTree=pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	//bool dWeapon=pGameObjectVolume->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0;
	//if (dTree && dWeapon)
	//{
	//	Logger::getInstance()->log("WEAPON-TO-DIAMONDTREE COLLISION");
	//}

	if(!(pGameObjectVolume->getName().compare(pGameObjectShape->getName())==0))
	{
		switch (collisionEventType)
		{
			case NxOgre::Enums::VolumeCollisionType_OnEnter: 
				sendCollision(pGameObjectShape,pGameObjectVolume);
				sendEnterTrigger(pGameObjectShape,pGameObjectVolume);
				break;
			case NxOgre::Enums::VolumeCollisionType_OnExit: 
				sendExitTrigger(pGameObjectShape,pGameObjectVolume);
				break;
			case NxOgre::Enums::VolumeCollisionType_OnPresence: 
				sendCollision(pGameObjectShape,pGameObjectVolume);													
				break;
			default: 
				break;
		}	 
	}
}

bool PhysicsSubsystem::isOnyCloseFromPosition(NxOgre::Vec3 position, double radius)
{
	return NxOgre::Vec3(mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentPositional()->getPosition()).
		distance(position) < radius;
}

bool PhysicsSubsystem::sendEnterTrigger(GameObjectPtr object1, GameObjectPtr object2)
{
	bool isAllowed = true;

	EnterTriggerEventPtr evt = EnterTriggerEventPtr(
		new EnterTriggerEvent(
		object1, 
		object2));

	mApp->getGameWorldManager()->addEvent(evt);

	return isAllowed;
}

bool PhysicsSubsystem::sendExitTrigger(GameObjectPtr object1, GameObjectPtr object2)
{
	bool isAllowed = true;

	ExitTriggerEventPtr evt = ExitTriggerEventPtr(
		new ExitTriggerEvent(
		object1, 
		object2));

	mApp->getGameWorldManager()->addEvent(evt);

	return isAllowed;
}

bool PhysicsSubsystem::sendCollision(GameObjectPtr object1, GameObjectPtr object2, Ogre::Vector3 normal)
{
	bool isAllowed = true;

	CollisionEventPtr evt = CollisionEventPtr(
		new CollisionEvent(
		object1, 
		object2,
		normal));

	mApp->getGameWorldManager()->addEvent(evt);

	return isAllowed;
}

//////////////////////////////////////////////////////////////////
// Physics Raycasting

bool PhysicsSubsystem::raycastClosestGeometry(const Vector3 &point,const Vector3 &normal,Vector3 &result,double maxDistance,QueryFlags flags)
{
	NxOgre::Vec3 StartPos( point );

	NxOgre::Vec3 Direction( normal );
	NxOgre::Ray CubeRay( StartPos, Direction );

	bool returnResult=false;

	// TODO SOLVE THAT
	//NxOgre::Enums::ShapesType has only static 1<<0 and dynamic 1<<1 flags assigned, the rest are custom.
	NxOgre::RaycastHit mRayResult = getNxOgreScene()->raycastClosestShape( CubeRay, NxOgre::Enums::ShapesType_Static, INT_MAX, maxDistance);

	if(mRayResult.mDistance<=maxDistance)
	{
		result=point+normal*mRayResult.mDistance;
		returnResult=true;
	}

	return returnResult;
}


bool PhysicsSubsystem::raycastClosestBoundings(const Vector3 &point,const Vector3 &normal,Vector3 &result,double maxDistance,QueryFlags flags)
{
	NxOgre::Vec3 StartPos( point );

	NxOgre::Vec3 Direction( normal );
	NxOgre::Ray CubeRay( StartPos, Direction );

	bool returnResult=false;

	// TODO SOLVE THAT
	//NxOgre::Enums::ShapesType has only static 1<<0 and dynamic 1<<1 flags assigned, the rest are custom.
	NxOgre::RaycastHit mRayResult = getNxOgreScene()->raycastClosestBounds( CubeRay, NxOgre::Enums::ShapesType_Static, INT_MAX, maxDistance);

	if(mRayResult.mDistance<=maxDistance)
	{
		result=point+normal*mRayResult.mDistance;
		returnResult=true;
	}


	return returnResult;
}

int PhysicsSubsystem::raycastAllBoundings(const Vector3 &point,const Vector3 &normal,std::vector<GameObjectPtr> &result,double maxDistance,QueryFlags flags)
{
	NxOgre::Vec3 StartPos( point );

	NxOgre::Vec3 Direction( normal );
	NxOgre::Ray CubeRay( StartPos, Direction );

	bool returnResult=false;
	int numResults;

	// TODO SOLVE THAT
	//NxOgre::Enums::ShapesType has only static 1<<0 and dynamic 1<<1 flags assigned, the rest are custom.
	numResults = getNxOgreScene()->raycastAllBounds( CubeRay, this, NxOgre::Enums::ShapesType_All, INT_MAX, maxDistance);

	return numResults;
}

double PhysicsSubsystem::angleFromNormal(Ogre::Vector3 normal)
{
	double angle = normal.angleBetween(Vector3(0,1,0)).valueAngleUnits();
	return angle;
}

