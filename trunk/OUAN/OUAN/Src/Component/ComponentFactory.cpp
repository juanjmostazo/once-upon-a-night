#include "ComponentFactory.h"
#include "../Application.h"
#include "../Game/GameObject/GameObject.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexNonMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCube.h"

using namespace OUAN;

ComponentFactory* ComponentFactory::mInstance=NULL;

ComponentFactory* ComponentFactory::getInstance()
{
	if (mInstance)
		return mInstance;
	else{
		mInstance=new ComponentFactory();
		return mInstance;
	}
}

void ComponentFactory::initialise(ApplicationPtr app)
{
	mApp=app;
}

RenderComponentPtr ComponentFactory::createRenderComponent(GameObjectPtr gameObject,TRenderComponentParameters tRenderComponentParameters)
{
	//Create void Render Component
	RenderComponentPtr pRenderComponent = RenderComponentPtr(new RenderComponent()); 

	pRenderComponent->setParent(gameObject);	

	return pRenderComponent;
}

RenderComponentBillboardSetPtr ComponentFactory::createRenderComponentBillboardSet(GameObjectPtr gameObject,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters)
{
	//Create void Render Component
	RenderComponentBillboardSetPtr pRenderComponentBillboardSetPtr = RenderComponentBillboardSetPtr(new RenderComponentBillboardSet()); 

	pRenderComponentBillboardSetPtr->setParent(gameObject);	

	//Initialise Render Component
	pRenderComponentBillboardSetPtr->setBillboardSet(mApp->getRenderSubsystem()->createBillboardSet(gameObject->getName(),tRenderComponentBillboardSetParameters));


	return pRenderComponentBillboardSetPtr;
}
RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	//Create void Render Component
	RenderComponentCameraPtr pRenderComponentCameraPtr = RenderComponentCameraPtr(new RenderComponentCamera()); 

	pRenderComponentCameraPtr->setParent(gameObject);	

	//Initialise Render Component
	pRenderComponentCameraPtr->setCamera(mApp->getRenderSubsystem()->createCamera(gameObject->getName(),tRenderComponentCameraParameters));
	return pRenderComponentCameraPtr;
}

RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters)
{
	//Create void Render Component
	RenderComponentEntityPtr pRenderComponentEntity = RenderComponentEntityPtr(new RenderComponentEntity()); 

	pRenderComponentEntity->setParent(gameObject);	

	//Initialise Render Component
	pRenderComponentEntity->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),tRenderComponentEntityParameters));

	return pRenderComponentEntity;
}
RenderComponentLightPtr ComponentFactory::createRenderComponentLight(GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters)
{
	//Create void Render Component
	RenderComponentLightPtr pRenderComponentLight = RenderComponentLightPtr(new RenderComponentLight()); 

	pRenderComponentLight->setParent(gameObject);

	//Initialise Render Component
	pRenderComponentLight->setLight(mApp->getRenderSubsystem()->createLight(gameObject->getName(),tRenderComponentLightParameters));

	return pRenderComponentLight;
}
RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters)
{
	//Create void Render Component
	RenderComponentParticleSystemPtr pRenderComponentParticleSystem = RenderComponentParticleSystemPtr(new RenderComponentParticleSystem()); 

	pRenderComponentParticleSystem->setParent(gameObject);

	//Initialise Render Component
	pRenderComponentParticleSystem->setParticleSystem(mApp->getRenderSubsystem()->createParticleSystem(gameObject->getName(),tRenderComponentParticleSystemParameters));

	return pRenderComponentParticleSystem;
}
RenderComponentScenePtr ComponentFactory::createRenderComponentScene(GameObjectPtr gameObject,TRenderComponentSceneParameters tRenderComponentSceneParameters)
{
	//Create void Render Component
	RenderComponentScenePtr pRenderComponentScene = RenderComponentScenePtr(new RenderComponentScene()); 

	pRenderComponentScene->setParent(gameObject);

	//Initialise Render Component
	pRenderComponentScene->setSceneManager(mApp->getRenderSubsystem()->createSceneManager(gameObject->getName(),tRenderComponentSceneParameters));

	return pRenderComponentScene;
}
RenderComponentPositionalPtr ComponentFactory::createRenderComponentPositional(GameObjectPtr gameObject,TRenderComponentPositionalParameters tRenderComponentPositionalParameters)
{
	//Create void Render Component
	RenderComponentPositionalPtr pRenderComponentPositional = RenderComponentPositionalPtr(new RenderComponentPositional()); 

	pRenderComponentPositional->setParent(gameObject);	

	//Initialise Render Component
	pRenderComponentPositional->setSceneNode(mApp->getRenderSubsystem()->createSceneNode(gameObject->getName(),tRenderComponentPositionalParameters));

	return pRenderComponentPositional;
}
RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	//Create void Render Component
	RenderComponentViewportPtr pRenderComponentViewport = RenderComponentViewportPtr(new RenderComponentViewport()); 

	pRenderComponentViewport->setParent(gameObject);

	//Initialise Render Component
	pRenderComponentViewport->setViewport(mApp->getRenderSubsystem()->createViewport(gameObject->getName(),tRenderComponentViewportParameters));

	return pRenderComponentViewport;
}

PhysicsComponentCharacterPtr ComponentFactory::createPhysicsComponentCharacter(GameObjectPtr gameObject,TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters)
{
	PhysicsComponentCharacterPtr pPhysicsComponentCharacter = PhysicsComponentCharacterPtr(new PhysicsComponentCharacter()); 

	pPhysicsComponentCharacter->setParent(gameObject);	

	return pPhysicsComponentCharacter;
}

PhysicsComponentComplexMovablePtr ComponentFactory::createPhysicsComponentComplexMovable(GameObjectPtr gameObject,TPhysicsComponentComplexMovableParameters tPhysicsComponentComplexMovableParameters)
{
	PhysicsComponentComplexMovablePtr pPhysicsComponentComplexMovable = PhysicsComponentComplexMovablePtr(new PhysicsComponentComplexMovable()); 

	pPhysicsComponentComplexMovable->setParent(gameObject);	

	return pPhysicsComponentComplexMovable;
}

PhysicsComponentComplexNonMovablePtr ComponentFactory::createPhysicsComponentComplexNonMovable(GameObjectPtr gameObject,TPhysicsComponentComplexNonMovableParameters tPhysicsComponentComplexNonMovableParameters)
{
	// Get SceneNode from gameObject->getComponent(COMPONENT_NAME_RENDER_POSITIONAL);
	PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable = PhysicsComponentComplexNonMovablePtr(new PhysicsComponentComplexNonMovable()); 

	pPhysicsComponentComplexNonMovable->setParent(gameObject);	

	return pPhysicsComponentComplexNonMovable;
}

PhysicsComponentSimpleCapsulePtr ComponentFactory::createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters)
{
	PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule = PhysicsComponentSimpleCapsulePtr(new PhysicsComponentSimpleCapsule()); 

	pPhysicsComponentSimpleCapsule->setParent(gameObject);	

	return pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCubePtr ComponentFactory::createPhysicsComponentSimpleCube(GameObjectPtr gameObject,TPhysicsComponentSimpleCubeParameters tPhysicsComponentSimpleCubeParameters)
{
	PhysicsComponentSimpleCubePtr pPhysicsComponentSimpleCube = PhysicsComponentSimpleCubePtr(new PhysicsComponentSimpleCube()); 

	pPhysicsComponentSimpleCube->setParent(gameObject);	

	return pPhysicsComponentSimpleCube;
}