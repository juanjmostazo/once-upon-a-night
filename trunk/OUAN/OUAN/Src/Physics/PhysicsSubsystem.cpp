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

void PhysicsSubsystem::initLevel(std::string sceneName)
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

void PhysicsSubsystem::update(float elapsedSeconds)
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

void PhysicsSubsystem::updateGameObjectOny(float elapsedSeconds, GameObjectOnyPtr pGameObjectOny)
{
	unsigned int collisionFlags = COLLIDABLE_MASK;

	pGameObjectOny->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mNxOgreScene->getGravity() * 0.001f,
		COLLIDABLE_MASK,
		0.001f,
		collisionFlags,
		1.0f
	);
}

void PhysicsSubsystem::updateGameObjectTripollo(float elapsedSeconds, GameObjectTripolloPtr pGameObjectTripollo)
{
	unsigned int collisionFlags = COLLIDABLE_MASK;

	pGameObjectTripollo->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mNxOgreScene->getGravity() * 0.001f,
		COLLIDABLE_MASK,
		0.001f,
		collisionFlags,
		1.0f
		);
}

void PhysicsSubsystem::updateGameObjectEye(float elapsedSeconds, GameObjectEyePtr pGameObjectEye)
{
	unsigned int collisionFlags = COLLIDABLE_MASK;

	pGameObjectEye->getPhysicsComponentCharacter()->getNxOgreController()->move(
		mNxOgreScene->getGravity() * 0.001f,
		COLLIDABLE_MASK,
		0.001f,
		collisionFlags,
		1.0f
		);
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onShape(const NxOgre::ControllerShapeHit& hit)
{
	return NxOgre::Enums::ControllerAction_None;
}

NxOgre::Enums::ControllerAction PhysicsSubsystem::onController(NxOgre::Controller* controller, NxOgre::Controller* other)
{	
	return NxOgre::Enums::ControllerAction_None;
}