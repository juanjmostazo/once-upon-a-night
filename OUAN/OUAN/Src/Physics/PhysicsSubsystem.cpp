#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObject.h"
#include "../Game/GameObject/GameObjectTerrain.h"
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
#include "../Game/GameObject/GameObjectVolumeBox.h"
#include "../Game/GameObject/GameObjectVolumeCapsule.h"
#include "../Graphics/RenderSubsystem.h"
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
	Ogre::LogManager::getSingleton().logMessage("Initializing physics subsystem");

	loadConfig();

	mApp=app;
	mConfig=config;

	//Initializing NxOgre::TimeController
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	//Initializing NxOgre::World
	mNxOgreWorld = NxOgre::World::createWorld();

	//Loading NXS resources
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	Ogre::LogManager::getSingleton().logMessage("[PHYSICS INIT LOAD] Done!");
}

void PhysicsSubsystem::resetLevel()
{
	if (mNxOgreControllerManager) delete mNxOgreControllerManager;
	if (mNxOgreRenderSystem) delete mNxOgreRenderSystem;
	
	if (mNxOgreScene != NULL){
		mNxOgreWorld->destroyScene(mNxOgreScene);
	}
}

void PhysicsSubsystem::initLevel(std::string sceneName)
{	
	//Initializing NxOgre::Scene
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = mGravity;
	sceneDesc.mName = NxOgre::String(sceneName.c_str());
	mNxOgreScene = mNxOgreWorld->createScene(sceneDesc);
	
	//Initializing Ogre3DRenderSystem
	mNxOgreRenderSystem = new OGRE3DRenderSystem(mNxOgreScene);

	//Initializing NxOgre::ControllerManager
	mNxOgreControllerManager = new NxOgre::ControllerManager();

	//Initializing NxOgre::TimeController
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	//Initializing scene stuff
	mNxOgreScene->createSceneGeometry(new NxOgre::PlaneGeometry(0, NxOgre::Vec3(0, 1, 0)), Matrix44_Identity);
	mNxOgreScene->getMaterial(0)->setStaticFriction(mStaticFriction);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(mDynamicFriction);
	mNxOgreScene->getMaterial(0)->setRestitution(mRestitution);

	//Initializing visual debugger
	mApp->getRenderSubsystem()->createVisualDebugger(mConfig);

	//Initializing terrains
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectTerrainContainer().size(); i++){
		initPhysicsComponentComplexTriangle(
			mApp->getGameWorldManager()->getGameObjectTerrainContainer()[i]->getPhysicsComponentComplexTriangle());
	}
	//for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectTerrainContainer().size(); i++){
	//	initPhysicsComponentComplexConvex(
	//		mApp->getGameWorldManager()->getGameObjectTerrainContainer()[i]->getPhysicsComponentComplexConvex());
	//}
	
	//////////////////////////////////////////////////////////////////////////////////
	// INIT CHARACTERS

	//Initializing Ony
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectOnyContainer().size(); i++){
		initPhysicsComponentCharacter(
			mApp->getGameWorldManager()->getGameObjectOnyContainer()[i]->getPhysicsComponentCharacter());
	}

	//Initializing Tripollos
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectTripolloContainer().size(); i++){
		initPhysicsComponentCharacter(
			mApp->getGameWorldManager()->getGameObjectTripolloContainer()[i]->getPhysicsComponentCharacter());
	}

	//Initializing Eyes
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectEyeContainer().size(); i++){
		initPhysicsComponentCharacter(
			mApp->getGameWorldManager()->getGameObjectEyeContainer()[i]->getPhysicsComponentCharacter());
	}
	
	//////////////////////////////////////////////////////////////////////////////////
	// INIT VOLUMES

	//Initializing volume boxes
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectVolumeBoxContainer().size(); i++){
		initPhysicsComponentVolumeBox(
			mApp->getGameWorldManager()->getGameObjectVolumeBoxContainer()[i]->getPhysicsComponentVolumeBox());
	}

	//Initializing volume capsules
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectVolumeCapsuleContainer().size(); i++){
		initPhysicsComponentVolumeCapsule(
			mApp->getGameWorldManager()->getGameObjectVolumeCapsuleContainer()[i]->getPhysicsComponentVolumeCapsule());
	}

	///**
	//* TO REMOVE::: DEBUG FLOOR FOR PHYSICS
	//*/
	//app->getRenderSubsystem()->createDebugFloor(config);
	
	Ogre::LogManager::getSingleton().logMessage("[PHYSICS LEVEL LOAD] Done!");
}

void PhysicsSubsystem::update(double elapsedSeconds)
{
	//Updating Ony
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectOnyContainer().size(); i++){
		updateGameObjectOny(elapsedSeconds,
			mApp->getGameWorldManager()->getGameObjectOnyContainer()[i]);
	}

	//Updating Tripollos
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectTripolloContainer().size(); i++){
		updateGameObjectTripollo(elapsedSeconds,mApp->getGameWorldManager()->getGameObjectTripolloContainer()[i]);
	}

	//Updating Eyes
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectEyeContainer().size(); i++){
		updateGameObjectEye(elapsedSeconds,mApp->getGameWorldManager()->getGameObjectEyeContainer()[i]);
	}
	/*
	std::stringstream out;
	out << elapsedSeconds;
	std::string elapsedTime = out.str();
	Ogre::Ogre::LogManager::getSingleton().logMessage("Advancing " + elapsedTime + " seconds");
	*/
	mNxOgreTimeController->advance(elapsedSeconds);
}

void PhysicsSubsystem::cleanUp()
{
	//resetLevel();
	mNxOgreWorld->destroyWorld(true);
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

		config.getOption("TURN_DEGREES_PER_SECOND", value); 
		mTurnDegreesPerSecond = atof(value.c_str());

		config.getOption("INITIAL_JUMP_SPEED", value); 
		mInitialJumpSpeed = atof(value.c_str());

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

void PhysicsSubsystem::initPhysicsComponentCharacter(PhysicsComponentCharacterPtr pPhysicsComponentCharacter)
{
	// TOFIX Next piece of code should be in ComponentFactory::createPhysicsComponentCharacter
	NxOgre::ControllerDescription mNxOgreControllerDescription = pPhysicsComponentCharacter->getNxOgreControllerDescription(); 
	mNxOgreControllerDescription.mCallback = this;
	pPhysicsComponentCharacter->setNxOgreControllerDescription(mNxOgreControllerDescription);

	pPhysicsComponentCharacter->setNxOgreController(
		mNxOgreControllerManager->createCapsuleController(
			pPhysicsComponentCharacter->getNxOgreControllerDescription(), 
			pPhysicsComponentCharacter->getNxOgreSize(), 
			mNxOgreScene, 
			mNxOgreRenderSystem->createPointRenderable(pPhysicsComponentCharacter->getSceneNode())));
}

void PhysicsSubsystem::initPhysicsComponentComplexConvex(PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex)
{
	//NxOgre::RigidBodyDescription mNxOgreRigidBodyDescription = NxOgre::RigidBodyDescription();
	//mNxOgreRigidBodyDescription.mMass = 0;
	
	pPhysicsComponentComplexConvex->setNxOgreBody(
		mNxOgreRenderSystem->createBody(
		pPhysicsComponentComplexConvex->getNxOgreConvex(),
		pPhysicsComponentComplexConvex->getSceneNode()->getPosition(),
		pPhysicsComponentComplexConvex->getSceneNode()));
	/*
	pPhysicsComponentComplexConvex->setNxOgreBody(
		mNxOgreRenderSystem->createBody(
			pPhysicsComponentComplexConvex->getNxOgreConvex(),
			pPhysicsComponentComplexConvex->getSceneNode()->getPosition(),
			pPhysicsComponentComplexConvex->getSceneNode(),
			mNxOgreRigidBodyDescription));
	*/
}

void PhysicsSubsystem::initPhysicsComponentComplexTriangle(PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle)
{
	mNxOgreScene->createSceneGeometry(
		pPhysicsComponentComplexTriangle->getNxOgreTriangleGeometry(),
		NxOgre::Matrix44(NxOgre::Vec3(pPhysicsComponentComplexTriangle->getSceneNode()->getPosition())));
}

void PhysicsSubsystem::initPhysicsComponentSimpleCapsule(PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule)
{
	pPhysicsComponentSimpleCapsule->setNxOgreBody(
		mNxOgreRenderSystem->createBody(
			new NxOgre::Capsule(	pPhysicsComponentSimpleCapsule->getNxOgreSize().x,
									pPhysicsComponentSimpleCapsule->getNxOgreSize().y),
			pPhysicsComponentSimpleCapsule->getSceneNode()->getPosition(),
			pPhysicsComponentSimpleCapsule->getSceneNode()));
}

void PhysicsSubsystem::initPhysicsComponentSimpleBox(PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox)
{
	pPhysicsComponentSimpleBox->setNxOgreBody(
		mNxOgreRenderSystem->createBody(
			new NxOgre::Box(	pPhysicsComponentSimpleBox->getNxOgreSize().x,
								pPhysicsComponentSimpleBox->getNxOgreSize().y,
								pPhysicsComponentSimpleBox->getNxOgreSize().z),
			pPhysicsComponentSimpleBox->getSceneNode()->getPosition(),
			pPhysicsComponentSimpleBox->getSceneNode()));
}

void PhysicsSubsystem::initPhysicsComponentVolumeCapsule(PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule)
{
	pPhysicsComponentVolumeCapsule->setNxOgreVolume(
		mNxOgreScene->createVolume(
			new NxOgre::Capsule(	pPhysicsComponentVolumeCapsule->getNxOgreSize().x,
									pPhysicsComponentVolumeCapsule->getNxOgreSize().y),
			NxOgre::Matrix44(NxOgre::Vec3(pPhysicsComponentVolumeCapsule->getSceneNode()->getPosition())),
			this, 
			NxOgre::Enums::VolumeCollisionType_All));
}

void PhysicsSubsystem::initPhysicsComponentVolumeBox(PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox)
{
	pPhysicsComponentVolumeBox->setNxOgreVolume(
		mNxOgreScene->createVolume(
			new NxOgre::Box(	pPhysicsComponentVolumeBox->getNxOgreSize().x,
								pPhysicsComponentVolumeBox->getNxOgreSize().y,
								pPhysicsComponentVolumeBox->getNxOgreSize().z),
			NxOgre::Matrix44(NxOgre::Vec3(pPhysicsComponentVolumeBox->getSceneNode()->getPosition())),
			this, 
			NxOgre::Enums::VolumeCollisionType_All));
}

void PhysicsSubsystem::updateGameObjectOny(double elapsedSeconds, GameObjectOnyPtr pGameObjectOny)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
	int movementFlags = pGameObjectOny->getMovementFlags();

	// Initial displacement vector: gravity
	NxOgre::Vec3 mDisplacement(mGravity * elapsedSeconds);

	// Movement forces
	if (movementFlags > 0)
	{
		// Advance stuff
		if ((movementFlags & MOV_FORWARD_OR_BACK) > 0)
		{	
			double way = ((movementFlags & MOV_GO_FORWARD) > 0) ? 1.0f : -1.0f;
			mDisplacement += Ogre::Vector3::UNIT_Z * mMovementUnitsPerSecond * way * elapsedSeconds;
		}

		// Turn stuff
		if ((movementFlags & MOV_LEFT_OR_RIGHT) > 0)
		{
			double offsetYaw = ((movementFlags & MOV_GO_LEFT) > 0) ? mTurnDegreesPerSecond : -mTurnDegreesPerSecond;
			offsetYaw *= elapsedSeconds;

			pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->setDisplayYaw(
				pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->getDisplayYaw() + offsetYaw);
		}

		// Jump stuff
		if ((movementFlags & MOV_JUMP) > 0 && !pGameObjectOny->isJumping())
		{
			Ogre::LogManager::getSingleton().logMessage("Jump!"); 
			pGameObjectOny->setJumping(true);
			pGameObjectOny->setJumpTime(0);
			pGameObjectOny->setJumpSpeed(mInitialJumpSpeed);
		}

		// Calculates the current displacement from position and angle
		mDisplacement = Ogre::Quaternion(
			Ogre::Degree(pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->getDisplayYaw()), 
			Ogre::Vector3::UNIT_Y) * 
			mDisplacement.as<Ogre::Vector3>();
	}

	// If it's jumping, calculate height and apply vertical displacement
	if (pGameObjectOny->isJumping())
	{
		pGameObjectOny->setJumpSpeed(pGameObjectOny->getJumpSpeed() + mGravity.y * pGameObjectOny->getJumpTime());
		pGameObjectOny->setJumpTime(pGameObjectOny->getJumpTime() + elapsedSeconds);
		mDisplacement.y += pGameObjectOny->getJumpSpeed() * elapsedSeconds - 0.5f * mGravity.y * elapsedSeconds * elapsedSeconds;
	}

	////////////////////////////////////////////////////////////////////////////

	// Applying global factor to displacement
	mDisplacement *= mDisplacementScale;

	pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mDisplacement,
		GROUP_COLLIDABLE_MASK,
		mMinDistance,
		collisionFlags);

	if(collisionFlags & NxOgre::Enums::ControllerFlag_Down)
	{
		pGameObjectOny->setJumping(false);
	}
}

void PhysicsSubsystem::updateGameObjectTripollo(double elapsedSeconds, GameObjectTripolloPtr pGameObjectTripollo)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	pGameObjectTripollo->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mGravity * mDisplacementScale,
		GROUP_COLLIDABLE_MASK,
		mMinDistance,
		collisionFlags);
}

void PhysicsSubsystem::updateGameObjectEye(double elapsedSeconds, GameObjectEyePtr pGameObjectEye)
{
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;
	
	pGameObjectEye->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mGravity * mDisplacementScale,
		GROUP_COLLIDABLE_MASK,
		mMinDistance,
		collisionFlags);
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

void PhysicsSubsystem::onVolumeEvent(NxOgre::Volume* volume, NxOgre::Shape* volumeShape, 
									 void* controller, unsigned int collisionEvent)
{
	NxOgre::Controller* characterController = static_cast<NxOgre::Controller*>(controller);

	switch (collisionEvent)
	{
		case NxOgre::Enums::VolumeCollisionType_OnEnter: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function character-onVolumeEvent called! - ENTER"); 
			break;

		case NxOgre::Enums::VolumeCollisionType_OnExit: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function character-onVolumeEvent called! - EXIT"); 
			break;

		case NxOgre::Enums::VolumeCollisionType_OnPresence: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function character-onVolumeEvent called! - PRESENCE"); 
			break;

		default: 
			Ogre::LogManager::getSingleton().logMessage("General-Physics-Function character-onVolumeEvent called! - UNKNOWN"); 
			break;
	}
}

//////////////////////////////////////////////////////////////////
// Specific physics character callbacks

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	//Too many log entries, maybe bacause of the TriangleMesh Terrain
	//Ogre::LogManager::getSingleton().logMessage("Specific-Character-Function onShape called!");
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	Ogre::LogManager::getSingleton().logMessage("Specific-Character-Function onController called!");
	return NxOgre::Enums::ControllerAction_None;
}