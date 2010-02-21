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
#include "../Graphics/RenderComponent/RenderComponentSceneNode.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Physics/PhysicsComponent/PhysicsComponent.h"
#include "../Physics/PhysicsComponent/PhysicsComponentMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentMovableEntity.h"
#include "../Physics/PhysicsComponent/PhysicsComponentNonMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentOny.h"
#include "../Physics/PhysicsComponent/PhysicsComponentTripollo.h"
#include "../Physics/PhysicsComponent/PhysicsComponentTerrain.h"

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
RenderComponentSceneNodePtr ComponentFactory::createRenderComponentSceneNode(GameObjectPtr gameObject,TRenderComponentSceneNodeParameters tRenderComponentSceneNodeParameters)
{
	//Create void Render Component
	RenderComponentSceneNodePtr pRenderComponentSceneNode = RenderComponentSceneNodePtr(new RenderComponentSceneNode()); 

	pRenderComponentSceneNode->setParent(gameObject);	

	//Initialise Render Component
	pRenderComponentSceneNode->setSceneNode(mApp->getRenderSubsystem()->createSceneNode(gameObject->getName(),tRenderComponentSceneNodeParameters));

	return pRenderComponentSceneNode;
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

PhysicsComponentPtr ComponentFactory::createPhysicsComponent(GameObjectPtr gameObject,TPhysicsComponentParameters tPhysicsComponentParameters)
{
	PhysicsComponentPtr pPhysicsComponent = PhysicsComponentPtr(new PhysicsComponent()); 

	pPhysicsComponent->setParent(gameObject);	

	return pPhysicsComponent;
}

PhysicsComponentMovablePtr ComponentFactory::createPhysicsComponentMovable(GameObjectPtr gameObject,TPhysicsComponentMovableParameters tPhysicsComponentMovableParameters)
{
	PhysicsComponentMovablePtr pPhysicsComponentMovable = PhysicsComponentMovablePtr(new PhysicsComponentMovable()); 

	pPhysicsComponentMovable->setParent(gameObject);	

	return pPhysicsComponentMovable;
}

PhysicsComponentMovableEntityPtr ComponentFactory::createPhysicsComponentMovableEntity(GameObjectPtr gameObject,TPhysicsComponentMovableEntityParameters tPhysicsComponentMovableEntityParameters)
{
	PhysicsComponentMovableEntityPtr pPhysicsComponentMovableEntity = PhysicsComponentMovableEntityPtr(new PhysicsComponentMovableEntity()); 

	pPhysicsComponentMovableEntity->setParent(gameObject);	

	return pPhysicsComponentMovableEntity;
}

PhysicsComponentNonMovablePtr ComponentFactory::createPhysicsComponentNonMovable(GameObjectPtr gameObject,TPhysicsComponentNonMovableParameters tPhysicsComponentNonMovableParameters)
{
	PhysicsComponentNonMovablePtr pPhysicsComponentNonMovable = PhysicsComponentNonMovablePtr(new PhysicsComponentNonMovable()); 

	pPhysicsComponentNonMovable->setParent(gameObject);	

	return pPhysicsComponentNonMovable;
}

PhysicsComponentOnyPtr ComponentFactory::createPhysicsComponentOny(GameObjectPtr gameObject,TPhysicsComponentOnyParameters tPhysicsComponentOnyParameters)
{
	PhysicsComponentOnyPtr pPhysicsComponentOny = PhysicsComponentOnyPtr(new PhysicsComponentOny()); 

	pPhysicsComponentOny->setParent(gameObject);	

	return pPhysicsComponentOny;
}

PhysicsComponentTripolloPtr ComponentFactory::createPhysicsComponentTripollo(GameObjectPtr gameObject,TPhysicsComponentTripolloParameters tPhysicsComponentTripolloParameters)
{
	PhysicsComponentTripolloPtr pPhysicsComponentTripollo = PhysicsComponentTripolloPtr(new PhysicsComponentTripollo()); 

	pPhysicsComponentTripollo->setParent(gameObject);	

	return pPhysicsComponentTripollo;
}

PhysicsComponentTerrainPtr ComponentFactory::createPhysicsComponentTerrain(GameObjectPtr gameObject,TPhysicsComponentTerrainParameters tPhysicsComponentTerrainParameters)
{
	PhysicsComponentTerrainPtr pPhysicsComponentTerrain = PhysicsComponentTerrainPtr(new PhysicsComponentTerrain()); 

	pPhysicsComponentTerrain->setParent(gameObject);

	NxOgre::ArchiveResourceIdentifier identifier;
	identifier.setArchive(("nxs:" + tPhysicsComponentTerrainParameters.nxsFile).c_str());

	Ogre::LogManager::getSingleton().logMessage("Trying to load: 'nxs:" + tPhysicsComponentTerrainParameters.nxsFile + "'");

	pPhysicsComponentTerrain->setMesh(NxOgre::MeshManager::getSingleton()->load(identifier));	

	if (tPhysicsComponentTerrainParameters.nxsType.compare("TRIANGLE") == 0){
		NxOgre::TriangleGeometry* triangleGeometry = new NxOgre::TriangleGeometry(pPhysicsComponentTerrain->getMesh());
		triangleGeometry->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);
	}

	return pPhysicsComponentTerrain;
}