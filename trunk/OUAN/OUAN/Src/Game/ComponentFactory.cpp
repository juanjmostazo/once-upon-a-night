#include "ComponentFactory.h"
#include "../Application.h"
#include "../Graphics/RenderSubsystem.h"
#include "GameObject/GameObject.h"
#include "RenderComponent/RenderComponent.h"
#include "RenderComponent/RenderComponentBillboardSet.h"
#include "RenderComponent/RenderComponentCamera.h"
#include "RenderComponent/RenderComponentCamera.h"
#include "RenderComponent/RenderComponentEntity.h"
#include "RenderComponent/RenderComponentLight.h"
#include "RenderComponent/RenderComponentParticleSystem.h"
#include "RenderComponent/RenderComponentScene.h"
#include "RenderComponent/RenderComponentSceneNode.h"
#include "RenderComponent/RenderComponentViewport.h"

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
