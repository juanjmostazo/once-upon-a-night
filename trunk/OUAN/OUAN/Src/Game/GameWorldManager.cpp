
#include "GameWorldManager.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Component/ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectTerrain.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectBillboardSet.h"
#include "GameObject/GameObjectParticleSystem.h"
#include "GameObject/GameObjectScene.h"
#include "GameObject/GameObjectOny.h"
#include "GameObject/GameObjectTripollo.h"
#include "GameObject/GameObjectEye.h"
#include "GameObject/GameObjectItem1UP.h"
#include "GameObject/GameObjectItemMaxHP.h"
#include "GameObject/GameObjectPortal.h"
#include "GameObject/GameObjectCamera.h"

#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"

#include <iomanip>
#include <sstream>

using namespace OUAN;

unsigned long GameWorldManager::mNextIdNum=0;
GameWorldManager::GameWorldManager()
{

}
GameWorldManager::~GameWorldManager()
{

}

GameObjectPtr GameWorldManager::getObject(const std::string& objectId)
{
	if(!mGameObjects.empty() && mGameObjects.count(objectId)>0)
		return mGameObjects[objectId];

	return GameObjectPtr();
}

TGameObjectMovableContainer GameWorldManager::getGameObjectMovableContainer()
{
	return mGameObjectMovable;
}

TGameObjectMovableEntityContainer GameWorldManager::getGameObjectMovableEntityContainer()
{
	return mGameObjectMovableEntity;
}

TGameObjectNonMovableContainer GameWorldManager::getGameObjectNonMovableContainer()
{
	return mGameObjectNonMovable;
}

TGameObjectNonMovableEntityContainer GameWorldManager::getGameObjectNonMovableEntityContainer()
{
	return mGameObjectNonMovableEntity;
}

TGameObjectOnyContainer GameWorldManager::getGameObjectOnyContainer()
{
	return mGameObjectOny;
}

TGameObjectPositionalContainer GameWorldManager::getGameObjectPositionalContainer()
{
	return mGameObjectPositional;
}

TGameObjectSceneContainer GameWorldManager::getGameObjectSceneContainer()
{
	return mGameObjectScene;
}

TGameObjectTripolloContainer GameWorldManager::getGameObjectTripolloContainer()
{
	return mGameObjectTripollo;
}

TGameObjectEyeContainer GameWorldManager::getGameObjectEyeContainer()
{
	return mGameObjectEye;

}
TGameObjectTerrainContainer GameWorldManager::getGameObjectTerrainContainer()
{
	return mGameObjectTerrain;
}

TGameObjectBillboardSetContainer GameWorldManager::getGameObjectBillboardSetContainer()
{
	return mGameObjectBillboardSet;
}

TGameObjectParticleSystemContainer GameWorldManager::getGameObjectParticleSystemContainer()
{
	return mGameObjectParticleSystem;
}

TGameObjectPhysicsCharacter GameWorldManager::geTGameObjectPhysicsCharacter()
{
	return mGameObjectPhysicsCharacter;
}

TGameObjectPhysicsComplexConvex GameWorldManager::geTGameObjectPhysicsComplexConvex()
{
	return mGameObjectPhysicsComplexConvex;
}

TGameObjectPhysicsComplexTriangle GameWorldManager::geTGameObjectPhysicsComplexTriangle()
{
	return mGameObjectPhysicsComplexTriangle;
}

TGameObjectPhysicsSimple GameWorldManager::geTGameObjectPhysicsSimple()
{
	return mGameObjectPhysicsSimple;
}

void GameWorldManager::loadLevel (const std::string& levelFileName)
{
	mApp->getLevelLoader()->loadLevel(levelFileName);

	mApp->getRenderSubsystem()->getCameraManager()->setActiveCamera(OUAN::RUNNING_CAMERA_NAME);
}

void GameWorldManager::clearContainers()
{
	mGameObjects.clear();
	mGameObjectsToAdd.clear();
	mGameObjectsToDelete.clear();

	mGameObjectMovable.clear();
	mGameObjectMovableEntity.clear();
	mGameObjectNonMovable.clear();
	mGameObjectNonMovableEntity.clear();
	mGameObjectLight.clear();
	mGameObjectParticleSystem.clear();
	mGameObjectBillboardSet.clear();
	mGameObjectTerrain.clear();
	mGameObjectOny.clear();
	mGameObjectPositional.clear();
	mGameObjectScene.clear();
	mGameObjectTripollo.clear();
	mGameObjectEye.clear();

	mGameObjectPhysicsCharacter.clear();
	mGameObjectPhysicsComplexConvex.clear();
	mGameObjectPhysicsComplexTriangle.clear();
	mGameObjectPhysicsSimple.clear();
}

void GameWorldManager::unloadLevel()
{
	mNextIdNum=0;//reset id counter ??

	clearContainers();
	//TODO RenderSubsystem CLEAR
	//PHysycs subsystem clear, etc...
	//landscape->cleanUp();
}

/// init object
void GameWorldManager::init(ApplicationPtr app)
{
	mNextIdNum=0;
	mApp=app;

	clearContainers();

	//landscape.reset() | landscape->initBlank() | ...
}

void GameWorldManager::cleanUp()
{
	// Careful with how game objects
	// (well, their components)
	// will free their resources!!

	clearContainers();
}


void GameWorldManager::initGlobalWorldData( /*const TGlobalWorldParameters& worldParams*/)
{
	// Set ambient light, skybox, etc.It is possible that all
	// those params end up being part of the "landscape"  object 
	// Jesus mentioned today (Feb 15th) <---- note: This is done by the createGameObjectScene method
	//TODO: Erase this function
}	

std::string GameWorldManager::makeIdString(const std::string& baseString,const int& padding, const unsigned long& value)
{
	std::ostringstream ostr(baseString);
	ostr<<"_"<<std::setw(padding)<<std::setfill('0')<<value;
	std::string s(ostr.str());
	return s;
}

void GameWorldManager::addGameObject(GameObjectPtr gameObject)
{
	mGameObjects[gameObject->getId()]=gameObject;
}
//
//void GameWorldManager::addGameObjectMovableEntity(GameObjectMovableEntityPtr gameObjectMovableEntity)
//{
//	if(!existsObject(gameObjectMovableEntity->getName()))
//	{
//		mGameObjects[gameObjectMovableEntity->getId()]=gameObjectMovableEntity;
//	}
//	//TODO: add to other maps
//}

void GameWorldManager::addGameObjectOny(GameObjectOnyPtr pGameObjectOny)
{
	mGameObjects[pGameObjectOny->getId()]=pGameObjectOny;

	mGameObjectPositional.push_back(pGameObjectOny);
	mGameObjectMovable.push_back(pGameObjectOny);
	mGameObjectMovableEntity.push_back(pGameObjectOny);

	mGameObjectPhysicsCharacter.push_back(pGameObjectOny);

	mGameObjectOny.push_back(pGameObjectOny);
}

void GameWorldManager::addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo)
{
	mGameObjects[pGameObjectTripollo->getId()]=pGameObjectTripollo;

	mGameObjectPositional.push_back(pGameObjectTripollo);
	mGameObjectMovable.push_back(pGameObjectTripollo);
	mGameObjectMovableEntity.push_back(pGameObjectTripollo);

	mGameObjectPhysicsCharacter.push_back(pGameObjectTripollo);

	mGameObjectTripollo.push_back(pGameObjectTripollo);
}

void GameWorldManager::addGameObjectTerrain(GameObjectTerrainPtr pGameObjectTerrain)
{
	mGameObjects[pGameObjectTerrain->getId()]=pGameObjectTerrain;

	mGameObjectPositional.push_back(pGameObjectTerrain);
	mGameObjectNonMovable.push_back(pGameObjectTerrain);
	mGameObjectNonMovableEntity.push_back(pGameObjectTerrain);

	mGameObjectPhysicsComplexTriangle.push_back(pGameObjectTerrain);

	mGameObjectTerrain.push_back(pGameObjectTerrain);
}

void GameWorldManager::addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP)
{
	mGameObjects[pGameObjectItem1UP->getId()]=pGameObjectItem1UP;

	mGameObjectPositional.push_back(pGameObjectItem1UP);
	mGameObjectNonMovable.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableEntity.push_back(pGameObjectItem1UP);

}

void GameWorldManager::addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP)
{
	mGameObjects[pGameObjectItemMaxHP->getId()]=pGameObjectItemMaxHP;

	mGameObjectPositional.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovable.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableEntity.push_back(pGameObjectItemMaxHP);

}

void GameWorldManager::addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal)
{
	mGameObjects[pGameObjectPortal->getId()]=pGameObjectPortal;

	mGameObjectPositional.push_back(pGameObjectPortal);
	mGameObjectNonMovable.push_back(pGameObjectPortal);
	mGameObjectNonMovableEntity.push_back(pGameObjectPortal);
}

void GameWorldManager::addGameObjectEye(GameObjectEyePtr pGameObjectEye)
{
	mGameObjects[pGameObjectEye->getId()]=pGameObjectEye;

	mGameObjectPositional.push_back(pGameObjectEye);
	mGameObjectNonMovable.push_back(pGameObjectEye);
	mGameObjectNonMovableEntity.push_back(pGameObjectEye);

	mGameObjectPhysicsCharacter.push_back(pGameObjectEye);

	mGameObjectEye.push_back(pGameObjectEye);
}
void GameWorldManager::addGameObjectLight(GameObjectLightPtr pGameObjectLight)
{
	mGameObjects[pGameObjectLight->getId()]=pGameObjectLight;

	mGameObjectPositional.push_back(pGameObjectLight);
	mGameObjectNonMovable.push_back(pGameObjectLight);
	mGameObjectLight.push_back(pGameObjectLight);
}

void GameWorldManager::addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet)
{
	mGameObjects[pGameObjectBillboardSet->getId()]=pGameObjectBillboardSet;

	mGameObjectPositional.push_back(pGameObjectBillboardSet);
	mGameObjectNonMovable.push_back(pGameObjectBillboardSet);
	mGameObjectBillboardSet.push_back(pGameObjectBillboardSet);
}

void GameWorldManager::addGameObjectParticleSystem(GameObjectParticleSystemPtr pGameObjectParticleSystem)
{
	mGameObjects[pGameObjectParticleSystem->getId()]=pGameObjectParticleSystem;

	mGameObjectPositional.push_back(pGameObjectParticleSystem);
	mGameObjectNonMovable.push_back(pGameObjectParticleSystem);
	mGameObjectParticleSystem.push_back(pGameObjectParticleSystem);
}


void GameWorldManager::addGameObjectCamera(GameObjectCameraPtr pGameObjectCamera)
{
	mGameObjects[pGameObjectCamera->getId()]=pGameObjectCamera;
}


//void GameWorldManager::createGameObject(String name, GameObjectPtr gameObject)
//{
//	gameObject = GameObjectPtr(new GameObject(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
//	addGameObject(gameObject);
//
//}
//
//void GameWorldManager::createGameObjectMovable(String name, GameObjectMovablePtr gameObjectMovable)
//{
//	GameObjectMovablePtr pGameObjectMovable;
//	pGameObjectMovable = GameObjectMovablePtr(new GameObjectMovable(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
//	//TODO add to GameObjectMovable map
//	//addGameObject(pGameObjectMovable);
//}

void GameWorldManager::createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters)
{
	GameObjectOnyPtr pGameObjectOny;

	//Create GameObject
	pGameObjectOny = GameObjectOnyPtr(new GameObjectOny(
		tGameObjectOnyParameters.name,makeIdString(tGameObjectOnyParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectOny->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectOny->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectOny->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectOny,
			tGameObjectOnyParameters.tPhysicsComponentCharacterParameters,
			pGameObjectOny->getRenderComponentPositional()));

	//Add Object to GameWorldManager
	addGameObjectOny(pGameObjectOny);
}

void GameWorldManager::createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters)
{

	GameObjectTripolloPtr pGameObjectTripollo;

	//Create GameObject
	pGameObjectTripollo = GameObjectTripolloPtr(new GameObjectTripollo(
		tGameObjectTripolloParameters.name,makeIdString(tGameObjectTripolloParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectTripollo->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTripollo->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectTripollo->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectTripollo,
			tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters,
			pGameObjectTripollo->getRenderComponentPositional()));

	//Add Object to GameWorldManager
	addGameObjectTripollo(pGameObjectTripollo);
}

void GameWorldManager::createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters)
{

	GameObjectEyePtr pGameObjectEye;

	//Create GameObject
	pGameObjectEye = GameObjectEyePtr(new GameObjectEye(
		tGameObjectEyeParameters.name,makeIdString(tGameObjectEyeParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectEye->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectEye->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectEye->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectEye,
			tGameObjectEyeParameters.tPhysicsComponentCharacterParameters,
			pGameObjectEye->getRenderComponentPositional()));

	//Add Object to GameWorldManager
	addGameObjectEye(pGameObjectEye);
}

void GameWorldManager::createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters)
{

	GameObjectItem1UPPtr pGameObjectItem1UP;

	//Create GameObject
	pGameObjectItem1UP = GameObjectItem1UPPtr(new GameObjectItem1UP(
		tGameObjectItem1UPParameters.name,makeIdString(tGameObjectItem1UPParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectItem1UP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItem1UP->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters));

	//Add Object to GameWorldManager
	addGameObjectItem1UP(pGameObjectItem1UP);
}

void GameWorldManager::createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters)
{

	GameObjectPortalPtr pGameObjectPortal;

	//Create GameObject
	pGameObjectPortal = GameObjectPortalPtr(new GameObjectPortal(
		tGameObjectPortalParameters.name,makeIdString(tGameObjectPortalParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectPortal->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectPortal->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityParameters));

	//Add Object to GameWorldManager
	addGameObjectPortal(pGameObjectPortal);
}

void GameWorldManager::createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters)
{

	GameObjectItemMaxHPPtr pGameObjectItemMaxHP;

	//Create GameObject
	pGameObjectItemMaxHP = GameObjectItemMaxHPPtr(new GameObjectItemMaxHP(
		tGameObjectItemMaxHPParameters.name,makeIdString(tGameObjectItemMaxHPParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectItemMaxHP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItemMaxHP->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters));

	//Add Object to GameWorldManager
	addGameObjectItemMaxHP(pGameObjectItemMaxHP);
}

void GameWorldManager::createGameObjectTerrain(TGameObjectTerrainParameters tGameObjectTerrainParameters)
{
	GameObjectTerrainPtr pGameObjectTerrain;

	//Create GameObject
	pGameObjectTerrain = GameObjectTerrainPtr(new GameObjectTerrain(
		tGameObjectTerrainParameters.name,makeIdString(tGameObjectTerrainParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectTerrain->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTerrain,tGameObjectTerrainParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTerrain->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectTerrain,tGameObjectTerrainParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectTerrain->setPhysicsComponentComplexTriangle(factory->createPhysicsComponentComplexTriangle(
			pGameObjectTerrain,
			tGameObjectTerrainParameters.tPhysicsComponentComplexTriangleParameters,
			pGameObjectTerrain->getRenderComponentPositional()));

	//Add Object to GameWorldManager
	addGameObjectTerrain(pGameObjectTerrain);
}

void GameWorldManager::createGameObjectCamera(TGameObjectCameraParameters tGameObjectCameraParameters)
{
	GameObjectCameraPtr pGameObjectCamera;

	//Create GameObject
	pGameObjectCamera = GameObjectCameraPtr(new GameObjectCamera(
		tGameObjectCameraParameters.name,makeIdString(tGameObjectCameraParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentCamera
		pGameObjectCamera->setRenderComponentCamera(factory->createRenderComponentCamera(
			pGameObjectCamera,tGameObjectCameraParameters.tRenderComponentCameraParameters));

	//Add Object to GameWorldManager
	addGameObjectCamera(pGameObjectCamera);
}

void GameWorldManager::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters)
{

	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(
		tGameObjectLightParameters.name,makeIdString(tGameObjectLightParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectLight->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentLight
		pGameObjectLight->setRenderComponentLight(factory->createRenderComponentLight(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentLightParameters));

	//Add Object to GameWorldManager
	addGameObjectLight(pGameObjectLight);
}

void GameWorldManager::createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters)
{
	GameObjectBillboardSetPtr pGameObjectBillboardSet;

	//Create GameObject
	pGameObjectBillboardSet = GameObjectBillboardSetPtr(new GameObjectBillboardSet(
		tGameObjectBillboardSetParameters.name,makeIdString(tGameObjectBillboardSetParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectBillboardSet->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentBillboardSet
		pGameObjectBillboardSet->setRenderComponentBillboardSet(factory->createRenderComponentBillboardSet(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters));

	//Add Object to GameWorldManager
	addGameObjectBillboardSet(pGameObjectBillboardSet);
}

void GameWorldManager::createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters)
{
	GameObjectParticleSystemPtr pGameObjectParticleSystem;

	//Create GameObject
	pGameObjectParticleSystem = GameObjectParticleSystemPtr(new GameObjectParticleSystem(
		tGameObjectParticleSystemParameters.name,makeIdString(tGameObjectParticleSystemParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectParticleSystem->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentParticleSystem
		pGameObjectParticleSystem->setRenderComponentParticleSystem(factory->createRenderComponentParticleSystem(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters));

	//Add Object to GameWorldManager
	addGameObjectParticleSystem(pGameObjectParticleSystem);
}


//void GameWorldManager::createGameObjectMovableEntity(TEntityParameters tEntityParameters)
//{
//	//TODO: movable entity nonmovable entity instead of this and add to proper gameobject map
//
//	GameObjectMovableEntityPtr pGameObjectMovableEntity;
//
//	//Create GameObject
//	pGameObjectMovableEntity = GameObjectMovableEntityPtr(
//		new GameObjectMovableEntity(tEntityParameters.name,makeIdString(tEntityParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
//
//	ComponentFactory* factory=ComponentFactory::getInstance();
//
//	factory->createRenderComponentPositional(pGameObjectMovableEntity,tEntityParameters.TRenderComponentPositionalParameters);
//	factory->createRenderComponentEntity(pGameObjectMovableEntity,tEntityParameters.TRenderComponentEntityParameters);
//
////[TODO: Add other components as they're implemented]
//// Example:
////
////	 ComponentPtr physicsComponent = ComponentFactory::getInstance()->createPhysicsComponent(objectParams,go,mApp->getPhysicsSubsystem());
////
////	 ComponentPtr aiComponent = compFactory->createAIComponent(...);
//
//
//	//Add GameObject to GameWorldManager
//	//TODO add to GameObjectMovableEntity map
//	addGameObjectMovableEntity(pGameObjectMovableEntity);
//
//}
//
//void GameWorldManager::createSceneNode(TSceneNodeParameters tSceneNodeParameters)
//{
//	//Create GameObject
//	//createGameObject(tSceneNodeParameters.name);
//	//TODO
//}	
//void GameWorldManager::createLight(TLightParameters tLightParameters)
//{
//	//Create GameObject
//	//createGameObject(tLightParameters.name);
//
//	//TODO
//}
//void GameWorldManager::createParticleSystem(TParticleSystemParameters tParticleSystemParameters)
//{
//	//Create GameObject
//	//createGameObject(tParticleSystemParameters.name);
//
//	//TODO
//}
//
//void GameWorldManager::createBillboardSet(TBillboardSetParameters tBillboardSetParameters)
//{
//	//Create GameObject
//	//createGameObject(tBillboardSetParameters.name);
//	//TODO
//}
//void GameWorldManager::createViewport(TViewportParameters tViewportParameters)
//{
//	//Create GameObject
//	//createGameObject(tViewportParameters.name);
//	//TODO
//
//}
//void GameWorldManager::createCamera(TCameraParameters tCameraParameters)
//{
//	//Create GameObject
//	//createGameObject(tCameraParameters.name);
//	//TODO
//
//}
//void GameWorldManager::createSceneManager(TSceneManagerParameters tSceneManagerParameters)
//{
//	//Create GameObject
//	//createGameObject(tSceneManagerParameters.name);
//	//TODO
//
//}
//
//void GameWorldManager::update(long elapsedTime)
//{
//	for (TGameObjectContainerIterator it= mGameObjects.begin();it!=mGameObjects.end();++it)
//	{
//		it->second->update(elapsedTime);
//	}
//}