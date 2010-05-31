#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectTerrainConvex.h"
#include "../Game/GameObject/GameObjectTerrainTriangle.h"
#include "../Game/GameObject/GameObjectLight.h"
#include "../Game/GameObject/GameObjectBillboardSet.h"
#include "../Game/GameObject/GameObjectParticleSystem.h"
#include "../Game/GameObject/GameObjectScene.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectTripolloDreams.h"
#include "../Game/GameObject/GameObjectTripollito.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectTentetieso.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectCamera.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectHeart.h"
#include "../Game/GameObject/GameObjectDiamond.h"
#include "../Game/GameObject/GameObjectDiamondTree.h"
#include "../Game/GameObject/GameObjectClockPiece.h"
#include "../Game/GameObject/GameObjectStoryBook.h"
#include "../Game/GameObject/GameObjectScaredPlant.h"
#include "../Game/GameObject/GameObjectTree.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Event/Event.h"
#include "PhysicsComponent/PhysicsComponent.h"
#include "PhysicsComponent/PhysicsComponentCharacter.h"
#include "PhysicsComponent/PhysicsComponentComplex.h"
#include "PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "PhysicsComponent/PhysicsComponentSimple.h"
#include "PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "PhysicsComponent/PhysicsComponentVolumeBox.h"

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
	unsigned int i;

	if (mApp)
	{
		TGameObjectPhysicsContainer * container = mApp->getGameWorldManager()->getGameObjectPhysicsContainer();
		
		if (!container->empty())
		{
			for (i=0;i<container->size();i++)
			{
				container->at(i)->updatePhysicsComponents(elapsedSeconds);
			}
		}
	}

	mNxOgreTimeController->advance(elapsedSeconds);
}

void PhysicsSubsystem::stabilize()
{
	update(1000.0f);
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

		config.getOption("INITIAL_JUMP_SPEED", value); 
		mInitialJumpSpeed = atof(value.c_str());

		config.getOption("MIN_ALLOWED_Y", value); 
		mMinAllowedY = atof(value.c_str());

		config.getOption("MIN_COLLISION_ANGLE", value); 
		mMinCollisionAngle = atof(value.c_str());

		config.getOption("MIN_SLIDING_ANGLE", value); 
		mMinSlidingAngle = atof(value.c_str());

		config.getOption("MIN_SLIDING_ANGLE_FALL", value); 
		mMinSlidingAngleFall = atof(value.c_str());

		config.getOption("SLIDING_FACTOR", value); 
		mSlidingFactor = atof(value.c_str());

		config.getOption("SLIDING_FACTOR_FALL", value); 
		mSlidingFactorFall = atof(value.c_str());

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

		config.getOption("WALK_SPEED", value); 
		mWalkSpeed = atof(value.c_str());

		config.getOption("SLOPE_LIMIT", value); 
		mSlopeLimit = atof(value.c_str());

		config.getOption("STEP_OFFSET", value); 
		mStepOffset= atof(value.c_str());

		config.getOption("SKIN_WIDTH", value); 
		mSkinWidth = atof(value.c_str());

		config.getOption("GRAVITY_BODIES_FACTOR", value); 
		mGravityBodiesFactor = atof(value.c_str());

		success = true;
	} 
	else 
	{
		//Logger::getInstance()->log(PHYSICS_CFG + " COULD NOT BE LOADED!");

		mGravity = NxOgre::Vec3(0,0,0);
		mStaticFriction = 0;
		mDynamicFriction = 0;
		mRestitution = 0;
		mDisplacementScale = 0;
		mMinDistance = 0;
		mMovementUnitsPerSecond = 0;
		mTurnDegreesPerSecond = 0;
		mInitialJumpSpeed = 0;
		mMinAllowedY = 0;
		mMinSlidingAngle = 0;
		mMinSlidingAngleFall = 0;
		mMinCollisionAngle = 0;
		mSlidingFactor = 0;
		mSlidingFactorFall = 0;
		mSlopeLimit = 0;
		mStepOffset = 0;
		mSkinWidth = 0;
		mGravityBodiesFactor = 0;

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
	double normalAngle = acos(hit.mWorldNormal.y) * TO_DEGREES;
	setGameObjectSlidingFromController(hit.mController, hit.mWorldNormal, normalAngle);

	GameObjectPtr pGameObjectController = getGameObject(hit.mControllerName);
	GameObjectPtr pGameObjectShape = getGameObject(hit.mShapeName);

	bool dTree=pGameObjectController->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	bool dWeapon=pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0;
	if (dTree && dWeapon)
		Logger::getInstance()->log("WEAPON-TO-DIAMONDTREE COLLISION");

	//CORRECTING JUMP BUG TODO: DO THIS PROPERLY
	if( (pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_FLASHLIGHT)!=0) &&
		(pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_PILLOW)!=0) &&
		(normalAngle<=mMinSlidingAngleFall))
	{
		if(pGameObjectController->hasPhysicsComponent())
		{
			pGameObjectController->getPhysicsComponent()->setOnSurface(true);
		}
	}

	sendCollision(pGameObjectController,pGameObjectShape);
	
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(const NxOgre::ControllerControllerHit& hit)
{	
	GameObjectPtr pGameObjectController = getGameObject(hit.mControllerName);
	GameObjectPtr pGameObjectOtherController = getGameObject(hit.mOtherControllerName);

	//Logger::getInstance()->log("ON CONTROLLER");

	sendCollision(pGameObjectController,pGameObjectOtherController);
	
	return NxOgre::Enums::ControllerAction_None;
}

void PhysicsSubsystem::onVolumeEvent(  NxOgre::Shape * volume,  NxOgre::String collisionName, unsigned int collisionEventType  )
{
	//Logger::getInstance()->log("ON VOLUME EVENT volume "+std::string(hit.mVolumeShapeName.c_str()));//+" "+std::string(collisionShape->getName().c_str()));
	//Logger::getInstance()->log("ON VOLUME EVENT character "+std::string(hit.mCollisionShapeName.c_str()));

	GameObjectPtr pGameObjectVolume=getGameObject(volume->getName());
	GameObjectPtr pGameObjectShape=getGameObject(collisionName);
	
	bool dTree=pGameObjectShape->getType().compare(GAME_OBJECT_TYPE_DIAMONDTREE)==0;
	bool dWeapon=pGameObjectVolume->getType().compare(GAME_OBJECT_TYPE_PILLOW)==0;
	if (dTree && dWeapon)
		Logger::getInstance()->log("WEAPON-TO-DIAMONDTREE COLLISION");

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

//////////////////////////////////////////////////////////////////
// Auxiliar functions

bool PhysicsSubsystem::setGameObjectSlidingFromController(NxOgre::Controller* controller, NxOgre::Vec3 slideDiplacement, double normalAngle)
{
	bool found = false;
	bool isOny = false;

	TGameObjectPhysicsCharacterContainer * container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsCharacterContainer();

	for (unsigned int i=0; !found && i<container->size(); i++)
	{
		if ((*container)[i]->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
		{
			GameObjectOnyPtr tmpObject = boost::dynamic_pointer_cast<GameObjectOny>((*container)[i]);
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				tmpObject->getPhysicsComponentCharacter()->setSlidingValues(slideDiplacement, normalAngle);
				found = true;
				isOny = true;
			}
		}
		//TODO else if block
		//Same with the rest of game objects which hold a PhysicsComponentCharacter
	}	

	return isOny;
}

bool PhysicsSubsystem::areClose(NxOgre::Vec3 position1, NxOgre::Vec3 position2, double radius)
{
	double diffX = position1.x - position2.x;
	double diffY = position1.y - position2.y;
	double diffZ = position1.z - position2.z;
	
	double diffX2 = diffX * diffX;
	double diffY2 = diffY * diffY;
	double diffZ2 = diffZ * diffZ;

	return sqrt(diffX2 + diffY2 + diffZ2) < radius;
}

bool PhysicsSubsystem::isOnyCloseFromPosition(NxOgre::Vec3 position, double radius)
{
	return areClose(
		mApp->getGameWorldManager()->getGameObjectOny()->getRenderComponentPositional()->getPosition(), 
		position, 
		radius);
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

bool PhysicsSubsystem::sendCollision(GameObjectPtr object1, GameObjectPtr object2)
{
	bool isAllowed = true;

	CollisionEventPtr evt = CollisionEventPtr(
		new CollisionEvent(
		object1, 
		object2));

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

