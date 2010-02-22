#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Game/GameObject/GameObjectTerrain.h"
#include "../Game/GameObject/GameObjectOny.h"
#include "../Game/GameObject/GameObjectTripollo.h"
#include "../Graphics/RenderSubsystem.h"
#include "PhysicsComponent/PhysicsComponent.h"
#include "PhysicsComponent/PhysicsComponentCharacter.h"
#include "PhysicsComponent/PhysicsComponentComplex.h"
#include "PhysicsComponent/PhysicsComponentComplexMovable.h"
#include "PhysicsComponent/PhysicsComponentComplexNonMovable.h"
#include "PhysicsComponent/PhysicsComponentSimple.h"
#include "PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "PhysicsComponent/PhysicsComponentSimpleCube.h"

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

void PhysicsSubsystem::initialise(ApplicationPtr app,OUAN::ConfigurationPtr config)
{
	LogManager::getSingleton().logMessage("Initializing physics subsystem");
	this->mApp=app;
	this->mConfig=config;

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

void PhysicsSubsystem::initialiseLevel(std::string sceneName)
{	
	//Initializing NxOgre::Scene
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = NxOgre::Vec3(0, -9.8f, 0);
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
	mNxOgreScene->getMaterial(0)->setStaticFriction(0.5);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(0.5);
	mNxOgreScene->getMaterial(0)->setRestitution(0.1);

	//Initializing visual debugger
	mApp->getRenderSubsystem()->createVisualDebugger(mConfig);

	//Initializing terrains
	for (unsigned int i=0; i<mApp->getGameWorldManager()->getGameObjectTerrainContainer().size(); i++){
		/*
		std::stringstream out;
		out << i;
		std::string loopIndex = out.str();
		LogManager::getSingleton().logMessage("Looping in terrain " + loopIndex);
		*/
		PhysicsComponentComplexNonMovablePtr physicsComponentComplexNonMovable =
			mApp->getGameWorldManager()->getGameObjectTerrainContainer()[i]->getPhysicsComponentComplexNonMovable();

		mNxOgreScene->createSceneGeometry(
			physicsComponentComplexNonMovable->getTriangleGeometry(),
			NxOgre::Matrix44(NxOgre::Vec3(physicsComponentComplexNonMovable->getSceneNode()->getPosition()))
		);
	}
	
	///**
	//* TO REMOVE::: DEBUG FLOOR FOR PHYSICS
	//*/
	//app->getRenderSubsystem()->createDebugFloor(config);
	
	LogManager::getSingleton().logMessage("[PHYSICS LEVEL LOAD] Done!");
}

void PhysicsSubsystem::update(float elapsedSeconds)
{
	mNxOgreTimeController->advance(elapsedSeconds);
}

void PhysicsSubsystem::cleanUp()
{

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

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	return NxOgre::Enums::ControllerAction_None;
}

