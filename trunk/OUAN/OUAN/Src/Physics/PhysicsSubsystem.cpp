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
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Game/GameObject/GameObjectItem1UP.h"
#include "../Game/GameObject/GameObjectItemMaxHP.h"
#include "../Game/GameObject/GameObjectPortal.h"
#include "../Game/GameObject/GameObjectCamera.h"
#include "../Game/GameObject/GameObjectTriggerBox.h"
#include "../Game/GameObject/GameObjectTriggerCapsule.h"
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
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL INIT STARTED]");

	loadConfig();

	mApp=app;
	mConfig=config;

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL INIT FINISHED]");
}

void PhysicsSubsystem::cleanUp()
{
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL CLEANUP STARTED]");

	clear();

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS GENERAL CLEANUP FINISHED]");
}

void PhysicsSubsystem::initLevel(std::string sceneName)
{	
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL INIT STARTED]");

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating NxOgre::World");
	mNxOgreWorld = NxOgre::World::createWorld();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Loading nxs resources");
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Setting up scene description");
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = mGravity;
	sceneDesc.mName = NxOgre::String(sceneName.c_str());

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating scene");
	mNxOgreScene = mNxOgreWorld->createScene(sceneDesc);
	
	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating render system");
	mNxOgreRenderSystem = new OGRE3DRenderSystem(mNxOgreScene);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating time controller");
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating controller manager");
	mNxOgreControllerManager = new NxOgre::ControllerManager();

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Setting up scene");
	mNxOgreScene->getMaterial(0)->setStaticFriction(mStaticFriction);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(mDynamicFriction);
	mNxOgreScene->getMaterial(0)->setRestitution(mRestitution);

	Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating visual debugger");
	mApp->getRenderSubsystem()->createVisualDebugger(mConfig);
	
	//Ogre::LogManager::getSingleton().logMessage("PHYSICS: Creating debug floor");
	//NxOgre::PlaneGeometry* pDebugPlane = new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0));
	//pDebugPlane->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
	//mNxOgreScene->createSceneGeometry(pDebugPlane, Matrix44_Identity);
	//mApp->getRenderSubsystem()->createDebugFloor(mConfig);

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL INIT FINISHED]");
}

void PhysicsSubsystem::clear()
{
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL CLEAR STARTED]");

	//We destroy the scene, is this needed?
	// TODO: Iterate over 
	// Application::getInstance()->getGameWorldManager()->getGameObjectPhysicsContainer() 
	// and call destroy() method

	if (mNxOgreControllerManager)
	{
		Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying controller manager");
		delete mNxOgreControllerManager;
		mNxOgreControllerManager=0;
	}

	if (mNxOgreRenderSystem)
	{
		Ogre::LogManager::getSingleton().logMessage("PHYSICS: render system");
		delete mNxOgreRenderSystem;
		mNxOgreRenderSystem=0;
	}
	
	//Visual Debugger should be destroyed?
	//mApp->getRenderSubsystem()->

	if (mNxOgreWorld)
	{
		if (mNxOgreScene)
		{
			Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying scene");
			mNxOgreWorld->destroyScene(mNxOgreScene);
			mNxOgreScene=0;
		}

		Ogre::LogManager::getSingleton().logMessage("PHYSICS: destroying world");
		mNxOgreWorld->destroyWorld();
		mNxOgreWorld=0;
	}

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL CLEAR FINISHED]");
}

void PhysicsSubsystem::update(double elapsedSeconds)
{
	/*
	std::stringstream out;
	out << elapsedSeconds;
	std::string elapsedTime = out.str();
	Ogre::Ogre::LogManager::getSingleton().logMessage("Advancing " + elapsedTime + " seconds");
	*/

	mNxOgreTimeController->advance(elapsedSeconds);
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

		config.getOption("MOVEMENT_LIMIT_UNITS_PER_SECOND", value); 
		mMovementLimitUnitsPerSecond = atof(value.c_str());

		config.getOption("TURN_DEGREES_PER_SECOND", value); 
		mTurnDegreesPerSecond = atof(value.c_str());

		config.getOption("INITIAL_JUMP_SPEED", value); 
		mInitialJumpSpeed = atof(value.c_str());

		config.getOption("MIN_ALLOWED_Y", value); 
		mMinAllowedY = atof(value.c_str());

		success = true;
	} 
	else 
	{
		//Ogre::LogManager::getSingleton().logMessage(PHYSICS_CFG + " COULD NOT BE LOADED!");

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

//////////////////////////////////////////////////////////////////
// General physics callbacks

void PhysicsSubsystem::onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, 
	NxOgre::RigidBody* collision_body, NxOgre::Shape* rigidBodyShape, unsigned int collisionEvent)
{
	switch (collisionEvent)
	{
		case NxOgre::Enums::VolumeCollisionType_OnEnter: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onVolumeEvent called! - ENTER"); 
			break;

		case NxOgre::Enums::VolumeCollisionType_OnExit: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onVolumeEvent called! - EXIT"); 
			break;

		case NxOgre::Enums::VolumeCollisionType_OnPresence: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onVolumeEvent called! - PRESENCE"); 
			break;

		default: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onVolumeEvent called! - UNKNOWN"); 
			break;
	}
}

bool PhysicsSubsystem::onHitEvent(const NxOgre::RaycastHit& raycastHit)
{
	Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onHitEvent called!");
	return true;
}

void PhysicsSubsystem::onContact(const NxOgre::ContactPair& contactPair)
{
	Ogre::LogManager::getSingleton().logMessage("General-Physics-Function onContact called!");
}

//////////////////////////////////////////////////////////////////
// Character physics callbacks

void PhysicsSubsystem::onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, void* controller, unsigned int collisionEvent)
{
	NxOgre::Controller* cController = static_cast<NxOgre::Controller*>(controller);

	int collisionType = COLLISION_TYPE_TRIGGER_UNKNOWN;	
	switch (collisionEvent)
	{
		case NxOgre::Enums::VolumeCollisionType_OnEnter: collisionType = COLLISION_TYPE_TRIGGER_ENTER; break;
		case NxOgre::Enums::VolumeCollisionType_OnExit: collisionType = COLLISION_TYPE_TRIGGER_EXIT; break;
		case NxOgre::Enums::VolumeCollisionType_OnPresence: collisionType = COLLISION_TYPE_TRIGGER_PRESENCE; break;
		default: collisionType = COLLISION_TYPE_TRIGGER_UNKNOWN; break;
	}	 

	CharacterInTriggerEventPtr evt = CharacterInTriggerEventPtr(
		new CharacterInTriggerEvent(
			getGameObjectFromController(cController), 
			getGameObjectFromVolume(volume),
			collisionType));

	mApp->getGameWorldManager()->addEvent(evt);
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	//TODO INVESTIGATE HOW IT WORKS, seems that its called every frame
	//Ogre::LogManager::getSingleton().logMessage("Specific-Character-Function onShape called!");
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	CharactersCollisionEventPtr evt = CharactersCollisionEventPtr(
		new CharactersCollisionEvent(
		getGameObjectFromController(controller), 
		getGameObjectFromController(other)));

	mApp->getGameWorldManager()->addEvent(evt);

	return NxOgre::Enums::ControllerAction_None;
}

//////////////////////////////////////////////////////////////////
// Fetch functions

GameObjectPtr PhysicsSubsystem::getGameObjectFromController(NxOgre::Controller* controller)
{
	GameObjectPtr object;
	bool found = false;
	/*
	TGameObjectPhysicsCharacterContainer container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsCharacterContainer();

	for (unsigned int i=0; !found && i<container.size(); i++)
	{
		if (container[i]->getType().compare(GAME_OBJECT_TYPE_ONY) == 0)
		{
			GameObjectOnyPtr tmpObject = container[i];
			if (tmpObject->getPhysicsComponentCharacter()->getNxOgreController() == controller)
			{
				object= tmpObject;
				found = true;
			}
		}
		//TODO else if block
		//Same with the rest of game objects which hold a PhysicsComponentCharacter
	}	
	*/
	return object;
}

GameObjectPtr PhysicsSubsystem::getGameObjectFromVolume(NxOgre::Volume* volume)
{
	GameObjectPtr object;
	bool found = false;
	/*
	TGameObjectPhysicsVolumeContainer container = 
		mApp->getGameWorldManager()->getGameObjectPhysicsVolumeContainer();

	for (unsigned int i=0; !found && i<container.size(); i++)
	{
		if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIGGERBOX) == 0)
		{
			GameObjectTriggerBoxPtr tmpObject = container[i];
			if (tmpObject->getPhysicsComponentVolumeBox()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
		else if (container[i]->getType().compare(GAME_OBJECT_TYPE_TRIGGERCAPSULE) == 0)
		{
			GameObjectTriggerCapsulePtr tmpObject = container[i];
			if (tmpObject->getPhysicsComponentVolumeCapsule()->getNxOgreVolume() == volume)
			{
				object= tmpObject;
				found = true;
			}
		}
	}	
	*/
	return object;
}