#include "PhysicsSubsystem.h"
#include "../Application.h"
#include "../Loader/Configuration.h"
#include "../Game/GameWorldManager.h"
#include "../Graphics/RenderSubsystem.h"

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
	this->mApp=app;

	//Initializing NxOgre::World
	mNxOgreWorld = NxOgre::World::createWorld();
	
	//Initializing NxOgre::Scene
	NxOgre::SceneDescription sceneDesc;
	sceneDesc.mGravity = NxOgre::Vec3(0, -9.8f, 0);
	sceneDesc.mName = "NxOgreScene";
	mNxOgreScene = mNxOgreWorld->createScene(sceneDesc);

	//Initializing NxOgre::TimeController
	mNxOgreTimeController = NxOgre::TimeController::getSingleton();

	//Initializing Ogre3DRenderSystem
	mNxOgreRenderSystem = new OGRE3DRenderSystem(mNxOgreScene);

	//Loading NXS resources
	NxOgre::ResourceSystem::getSingleton()->openArchive("nxs", NXS_PATH);

	//Initializing NxOgre::ControllerManager
	mNxOgreControllerManager = new NxOgre::ControllerManager();

	mNxOgreScene->getMaterial(0)->setStaticFriction(0.5);
	mNxOgreScene->getMaterial(0)->setDynamicFriction(0.5);
	mNxOgreScene->getMaterial(0)->setRestitution(0.1);

	//Initialise visual debugger
	app->getRenderSubsystem()->createVisualDebugger(config);
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
