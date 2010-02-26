#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectTerrain.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Game/GameObject/GameObjectEye.h"
#include "../Graphics/RenderSubsystem.h"
#include "PhysicsComponent/PhysicsComponent.h"
#include "PhysicsComponent/PhysicsComponentCharacter.h"
#include "PhysicsComponent/PhysicsComponentComplex.h"
#include "PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "PhysicsComponent/PhysicsComponentSimple.h"
#include "PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "PhysicsComponent/PhysicsComponentSimpleBox.h"

using namespace OUAN;
using namespace Ogre;

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
	LogManager::getSingleton().logMessage("Initializing physics subsystem");

	loadConfig();

	mApp=app;
	mConfig=config;

	//Initializing NxOgre::TimeController
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	//Initializing NxOgre::World
	mNxOgreWorld = NxOgre::World::createWorld();

	//Loading NXS resources
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	LogManager::getSingleton().logMessage("[PHYSICS INIT LOAD] Done!");
}

void PhysicsSubsystem::resetLevel()
{
	delete mNxOgreControllerManager;
	delete mNxOgreRenderSystem;
	
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
	
	///**
	//* TO REMOVE::: DEBUG FLOOR FOR PHYSICS
	//*/
	//app->getRenderSubsystem()->createDebugFloor(config);
	
	LogManager::getSingleton().logMessage("[PHYSICS LEVEL LOAD] Done!");
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
	Ogre::LogManager::getSingleton().logMessage("Advancing " + elapsedTime + " seconds");
	*/
	mNxOgreTimeController->advance(elapsedSeconds);
}

void PhysicsSubsystem::cleanUp()
{

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

		success = true;
	} 
	else 
	{
		//LogManager::getSingleton().logMessage(PHYSICS_CFG + " COULD NOT BE LOADED!");

		mGravity = NxOgre::Vec3(0,0,0);
		mStaticFriction = 0;
		mDynamicFriction = 0;
		mRestitution = 0;
		mDisplacementScale = 0;
		mMinDistance = 0;

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
	pPhysicsComponentComplexConvex->setNxOgreBody(
		mNxOgreRenderSystem->createBody(
			pPhysicsComponentComplexConvex->getNxOgreConvex(),
			pPhysicsComponentComplexConvex->getSceneNode()->getPosition(),
			pPhysicsComponentComplexConvex->getSceneNode()));
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

void PhysicsSubsystem::updateGameObjectOny(double elapsedSeconds, GameObjectOnyPtr pGameObjectOny)
{
	//void move(const Vec3& displacement, unsigned int activeGroups, double minDistance, unsigned int& collisionFlags, Real sharpness=1.0f);
	unsigned int collisionFlags = GROUP_COLLIDABLE_MASK;

	pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mGravity * mDisplacementScale,
		GROUP_COLLIDABLE_MASK,
		mMinDistance,
		collisionFlags);
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

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	return NxOgre::Enums::ControllerAction_None;
}