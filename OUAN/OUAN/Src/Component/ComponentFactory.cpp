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

void ComponentFactory::init(ApplicationPtr app)
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

	//init Render Component
	pRenderComponentBillboardSetPtr->setBillboardSet(mApp->getRenderSubsystem()->createBillboardSet(gameObject->getName(),tRenderComponentBillboardSetParameters));

	return pRenderComponentBillboardSetPtr;
}
RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	//Create void Render Component
	RenderComponentCameraPtr pRenderComponentCameraPtr = RenderComponentCameraPtr(new RenderComponentCamera()); 

	pRenderComponentCameraPtr->setParent(gameObject);	

	//init Render Component
	//pRenderComponentCameraPtr->setCamera(mApp->getRenderSubsystem()->createCamera(gameObject->getName(),tRenderComponentCameraParameters));
	return pRenderComponentCameraPtr;
}

RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters)
{
	//Create void Render Component
	RenderComponentEntityPtr pRenderComponentEntity = RenderComponentEntityPtr(new RenderComponentEntity()); 

	pRenderComponentEntity->setParent(gameObject);	

	//init Render Component
	pRenderComponentEntity->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),tRenderComponentEntityParameters));

	return pRenderComponentEntity;
}
RenderComponentLightPtr ComponentFactory::createRenderComponentLight(GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters)
{
	//Create void Render Component
	RenderComponentLightPtr pRenderComponentLight = RenderComponentLightPtr(new RenderComponentLight()); 

	pRenderComponentLight->setParent(gameObject);

	//init Render Component
	pRenderComponentLight->setLight(mApp->getRenderSubsystem()->createLight(gameObject->getName(),tRenderComponentLightParameters));

	return pRenderComponentLight;
}
RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters)
{
	//Create void Render Component
	RenderComponentParticleSystemPtr pRenderComponentParticleSystem = RenderComponentParticleSystemPtr(new RenderComponentParticleSystem()); 

	pRenderComponentParticleSystem->setParent(gameObject);

	//init Render Component
	pRenderComponentParticleSystem->setParticleSystem(mApp->getRenderSubsystem()->createParticleSystem(gameObject->getName(),tRenderComponentParticleSystemParameters));

	return pRenderComponentParticleSystem;
}
RenderComponentScenePtr ComponentFactory::createRenderComponentScene(GameObjectPtr gameObject,TRenderComponentSceneParameters tRenderComponentSceneParameters)
{
	//Create void Render Component
	RenderComponentScenePtr pRenderComponentScene = RenderComponentScenePtr(new RenderComponentScene()); 

	pRenderComponentScene->setParent(gameObject);

	//init Render Component
	pRenderComponentScene->setSceneManager(mApp->getRenderSubsystem()->createSceneManager(gameObject->getName(),tRenderComponentSceneParameters));

	return pRenderComponentScene;
}
RenderComponentPositionalPtr ComponentFactory::createRenderComponentPositional(GameObjectPtr gameObject,TRenderComponentPositionalParameters tRenderComponentPositionalParameters)
{
	//Create void Render Component
	RenderComponentPositionalPtr pRenderComponentPositional = RenderComponentPositionalPtr(new RenderComponentPositional()); 

	pRenderComponentPositional->setParent(gameObject);	

	//init Render Component
	pRenderComponentPositional->setSceneNode(mApp->getRenderSubsystem()->createSceneNode(gameObject->getName(),tRenderComponentPositionalParameters));

	return pRenderComponentPositional;
}
RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	//Create void Render Component
	RenderComponentViewportPtr pRenderComponentViewport = RenderComponentViewportPtr(new RenderComponentViewport()); 

	pRenderComponentViewport->setParent(gameObject);

	//init Render Component
	pRenderComponentViewport->setViewport(mApp->getRenderSubsystem()->createViewport(gameObject->getName(),tRenderComponentViewportParameters));

	return pRenderComponentViewport;
}

PhysicsComponentCharacterPtr ComponentFactory::createPhysicsComponentCharacter(GameObjectPtr gameObject,TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,RenderComponentPositionalPtr renderComponentPositional)
{
	PhysicsComponentCharacterPtr pPhysicsComponentCharacter = 
		PhysicsComponentCharacterPtr(new PhysicsComponentCharacter()); 

	pPhysicsComponentCharacter->setParent(gameObject);	

	pPhysicsComponentCharacter->setSceneNode(renderComponentPositional->getSceneNode());

	pPhysicsComponentCharacter->setNxOgreSize(
		NxOgre::Vec2(tPhysicsComponentCharacterParameters.radius, tPhysicsComponentCharacterParameters.height));

	NxOgre::ControllerDescription mNxOgreControllerDescription;
	mNxOgreControllerDescription.mPosition.set(NxOgre::Vec3(renderComponentPositional->getSceneNode()->getPosition()));
	pPhysicsComponentCharacter->setNxOgreControllerDescription(mNxOgreControllerDescription);

	return pPhysicsComponentCharacter;
}

PhysicsComponentComplexMovablePtr ComponentFactory::createPhysicsComponentComplexMovable(GameObjectPtr gameObject,TPhysicsComponentComplexMovableParameters tPhysicsComponentComplexMovableParameters,RenderComponentPositionalPtr renderComponentPositional)
{
	PhysicsComponentComplexMovablePtr pPhysicsComponentComplexMovable = 
		PhysicsComponentComplexMovablePtr(new PhysicsComponentComplexMovable()); 

	pPhysicsComponentComplexMovable->setParent(gameObject);	

	return pPhysicsComponentComplexMovable;
}

PhysicsComponentComplexNonMovablePtr ComponentFactory::createPhysicsComponentComplexNonMovable(GameObjectPtr gameObject,TPhysicsComponentComplexNonMovableParameters tPhysicsComponentComplexNonMovableParameters,RenderComponentPositionalPtr renderComponentPositional)
{	
	PhysicsComponentComplexNonMovablePtr pPhysicsComponentComplexNonMovable = 
		PhysicsComponentComplexNonMovablePtr(new PhysicsComponentComplexNonMovable()); 

	pPhysicsComponentComplexNonMovable->setParent(gameObject);	

	//Ogre::LogManager::getSingleton().logMessage(NXS_PATH);
	//Ogre::LogManager::getSingleton().logMessage(tPhysicsComponentComplexNonMovableParameters.nxsFile.c_str());

	NxOgre::Mesh* triangleMesh = NxOgre::MeshManager::getSingleton()->load(
		tPhysicsComponentComplexNonMovableParameters.nxsFile.c_str());

	NxOgre::TriangleGeometry* triangleGeometry = new NxOgre::TriangleGeometry(triangleMesh);
	triangleGeometry->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);

	pPhysicsComponentComplexNonMovable->setNxOgreTriangleGeometry(triangleGeometry);
	pPhysicsComponentComplexNonMovable->setSceneNode(renderComponentPositional->getSceneNode());

	return pPhysicsComponentComplexNonMovable;
}

PhysicsComponentSimpleCapsulePtr ComponentFactory::createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters,RenderComponentPositionalPtr renderComponentPositional)
{
	PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule = 
		PhysicsComponentSimpleCapsulePtr(new PhysicsComponentSimpleCapsule()); 

	pPhysicsComponentSimpleCapsule->setParent(gameObject);	

	return pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleCubePtr ComponentFactory::createPhysicsComponentSimpleCube(GameObjectPtr gameObject,TPhysicsComponentSimpleCubeParameters tPhysicsComponentSimpleCubeParameters,RenderComponentPositionalPtr renderComponentPositional)
{
	PhysicsComponentSimpleCubePtr pPhysicsComponentSimpleCube = 
		PhysicsComponentSimpleCubePtr(new PhysicsComponentSimpleCube()); 

	pPhysicsComponentSimpleCube->setParent(gameObject);	

	return pPhysicsComponentSimpleCube;
}