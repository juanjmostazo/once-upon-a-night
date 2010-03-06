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
#include "GameObject/GameObjectVolumeBox.h"
#include "GameObject/GameObjectVolumeCapsule.h"
#include "GameObject/GameObjectViewport.h"
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
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../Event/EventManager.h"

#include <iomanip>
#include <sstream>

using namespace OUAN;

unsigned long GameWorldManager::mNextIdNum=0;

GameWorldManager::GameWorldManager()
{
	world=DREAMS;
}
GameWorldManager::~GameWorldManager()
{

}

void GameWorldManager::update(double elapsedSeconds)
{
	//std::stringstream out;
	//out << elapsedSeconds;
	//std::string elapsedTimeDebug = out.str();
	//Ogre::LogManager::getSingleton().logMessage("Updating " + elapsedTimeDebug);

	TGameObjectContainerIterator it;

	for(it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		it->second->update(elapsedSeconds);
	}
	dispatchEvents();
}

GameObjectPtr GameWorldManager::getObject(const std::string& objectId)
{
	if(!mGameObjects.empty() && mGameObjects.count(objectId)>0){
		return mGameObjects[objectId];
	}

	return GameObjectPtr();
}

TGameObjectMovableContainer GameWorldManager::getGameObjectMovableContainer()
{
	return mGameObjectMovableContainer;
}

TGameObjectMovableEntityContainer GameWorldManager::getGameObjectMovableEntityContainer()
{
	return mGameObjectMovableEntityContainer;
}

TGameObjectNonMovableContainer GameWorldManager::getGameObjectNonMovableContainer()
{
	return mGameObjectNonMovableContainer;
}

TGameObjectNonMovableEntityContainer GameWorldManager::getGameObjectNonMovableEntityContainer()
{
	return mGameObjectNonMovableEntityContainer;
}

TGameObjectOnyContainer GameWorldManager::getGameObjectOnyContainer()
{
	return mGameObjectOnyContainer;
}

TGameObjectPositionalContainer GameWorldManager::getGameObjectPositionalContainer()
{
	return mGameObjectPositionalContainer;
}

TGameObjectSceneContainer GameWorldManager::getGameObjectSceneContainer()
{
	return mGameObjectSceneContainer;
}

TGameObjectTripolloContainer GameWorldManager::getGameObjectTripolloContainer()
{
	return mGameObjectTripolloContainer;
}

TGameObjectEyeContainer GameWorldManager::getGameObjectEyeContainer()
{
	return mGameObjectEyeContainer;

}
TGameObjectTerrainContainer GameWorldManager::getGameObjectTerrainContainer()
{
	return mGameObjectTerrainContainer;
}

TGameObjectBillboardSetContainer GameWorldManager::getGameObjectBillboardSetContainer()
{
	return mGameObjectBillboardSetContainer;
}

TGameObjectParticleSystemContainer GameWorldManager::getGameObjectParticleSystemContainer()
{
	return mGameObjectParticleSystemContainer;
}

TGameObjectViewportContainer GameWorldManager::getGameObjectViewportContainer()
{
	return mGameObjectViewportContainer;
}

TGameObjectVolumeBoxContainer GameWorldManager::getGameObjectVolumeBoxContainer()
{
	return mGameObjectVolumeBoxContainer;
}

TGameObjectVolumeCapsuleContainer GameWorldManager::getGameObjectVolumeCapsuleContainer()
{
	return mGameObjectVolumeCapsuleContainer;
}

TGameObjectPhysicsCharacterContainer GameWorldManager::getGameObjectPhysicsCharacterContainer()
{
	return mGameObjectPhysicsCharacterContainer;
}

TGameObjectPhysicsComplexConvexContainer GameWorldManager::getGameObjectPhysicsComplexConvexContainer()
{
	return mGameObjectPhysicsComplexConvexContainer;
}

TGameObjectPhysicsComplexTriangleContainer GameWorldManager::getGameObjectPhysicsComplexTriangleContainer()
{
	return mGameObjectPhysicsComplexTriangleContainer;
}

TGameObjectPhysicsSimpleContainer GameWorldManager::getGameObjectPhysicsSimpleContainer()
{
	return mGameObjectPhysicsSimpleContainer;
}

TGameObjectPhysicsSimpleContainer GameWorldManager::getGameObjectPhysicsVolumeContainer()
{
	return mGameObjectPhysicsVolumeContainer;
}

void GameWorldManager::loadLevel (const std::string& levelFileName)
{
	mApp->getLevelLoader()->loadLevel(levelFileName);
	mApp->getRenderSubsystem()->getCameraManager()->setActiveCamera(OUAN::RUNNING_CAMERA_NAME);
	mApp->getRenderSubsystem()->getCameraManager()->setCameraType(OUAN::CAMERA_THIRD_PERSON);	
	mGameOver=false;
}

void GameWorldManager::clearContainers()
{
	for (TGameObjectContainerIterator it=mGameObjects.begin();it!=mGameObjects.end();++it)
	{
		it->second->unregisterHandlers();
	}
	mGameObjects.clear();
	mGameObjectsToAdd.clear();
	mGameObjectsToDelete.clear();

	mGameObjectMovableContainer.clear();
	mGameObjectMovableEntityContainer.clear();
	mGameObjectNonMovableContainer.clear();
	mGameObjectNonMovableEntityContainer.clear();
	mGameObjectLightContainer.clear();
	mGameObjectParticleSystemContainer.clear();
	mGameObjectBillboardSetContainer.clear();
	mGameObjectTerrainContainer.clear();
	mGameObjectOnyContainer.clear();
	mGameObjectPositionalContainer.clear();
	mGameObjectSceneContainer.clear();
	mGameObjectTripolloContainer.clear();
	mGameObjectEyeContainer.clear();
	mGameObjectVolumeBoxContainer.clear();
	mGameObjectVolumeCapsuleContainer.clear();

	mGameObjectPhysicsCharacterContainer.clear();
	mGameObjectPhysicsComplexConvexContainer.clear();
	mGameObjectPhysicsComplexTriangleContainer.clear();
	mGameObjectPhysicsSimpleContainer.clear();
	mGameObjectPhysicsVolumeContainer.clear();
}

void GameWorldManager::unloadLevel()
{
	mNextIdNum=0;//reset id counter ??

	clearContainers();
	//TODO RenderSubsystem CLEAR
	//PHysycs subsystem clear, etc...
}

/// init object
void GameWorldManager::init(ApplicationPtr app)
{
	world=DREAMS;
	mNextIdNum=0;
	mGameOver=false;
	mApp=app;

	clearContainers();
	mThis=shared_from_this();
	mEventManager.reset(new EventManager());

	//landscape.reset() | landscape->initBlank() | ...
}

void GameWorldManager::cleanUp()
{
	// Careful with how game objects
	// (well, their components)
	// will free their resources!!
	mEventManager->clear();
	clearContainers();
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
	mGameObjects[gameObject->getName()]=gameObject;
}
//
//void GameWorldManager::addGameObjectMovableEntity(GameObjectMovableEntityPtr gameObjectMovableEntity)
//{
//	if(!existsObject(gameObjectMovableEntity->getName()))
//	{
//		mGameObjects[gameObjectMovableEntity->getName()]=gameObjectMovableEntity;
//	}
//	//TODO: add to other maps
//}

void GameWorldManager::addGameObjectOny(GameObjectOnyPtr pGameObjectOny)
{
	mGameObjects[pGameObjectOny->getName()]=pGameObjectOny;

	mGameObjectPositionalContainer.push_back(pGameObjectOny);
	mGameObjectMovableContainer.push_back(pGameObjectOny);
	mGameObjectMovableEntityContainer.push_back(pGameObjectOny);

	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectOny);

	mGameObjectOnyContainer.push_back(pGameObjectOny);
}

void GameWorldManager::addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo)
{
	mGameObjects[pGameObjectTripollo->getName()]=pGameObjectTripollo;

	mGameObjectPositionalContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableEntityContainer.push_back(pGameObjectTripollo);

	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectTripollo);

	mGameObjectTripolloContainer.push_back(pGameObjectTripollo);
}

void GameWorldManager::addGameObjectTerrain(GameObjectTerrainPtr pGameObjectTerrain)
{
	mGameObjects[pGameObjectTerrain->getName()]=pGameObjectTerrain;

	mGameObjectPositionalContainer.push_back(pGameObjectTerrain);
	mGameObjectNonMovableContainer.push_back(pGameObjectTerrain);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectTerrain);

	mGameObjectPhysicsComplexTriangleContainer.push_back(pGameObjectTerrain);
	//mGameObjectPhysicsComplexConvexContainer.push_back(pGameObjectTerrain);

	mGameObjectTerrainContainer.push_back(pGameObjectTerrain);
}

void GameWorldManager::addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP)
{
	mGameObjects[pGameObjectItem1UP->getName()]=pGameObjectItem1UP;

	mGameObjectPositionalContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItem1UP);
}

void GameWorldManager::addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP)
{
	mGameObjects[pGameObjectItemMaxHP->getName()]=pGameObjectItemMaxHP;

	mGameObjectPositionalContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItemMaxHP);
}

void GameWorldManager::addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal)
{
	mGameObjects[pGameObjectPortal->getName()]=pGameObjectPortal;

	mGameObjectPositionalContainer.push_back(pGameObjectPortal);
	mGameObjectNonMovableContainer.push_back(pGameObjectPortal);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectPortal);
}

void GameWorldManager::addGameObjectEye(GameObjectEyePtr pGameObjectEye)
{
	mGameObjects[pGameObjectEye->getName()]=pGameObjectEye;

	mGameObjectPositionalContainer.push_back(pGameObjectEye);
	mGameObjectNonMovableContainer.push_back(pGameObjectEye);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectEye);

	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectEye);

	mGameObjectEyeContainer.push_back(pGameObjectEye);
}
void GameWorldManager::addGameObjectLight(GameObjectLightPtr pGameObjectLight)
{
	mGameObjects[pGameObjectLight->getName()]=pGameObjectLight;

	mGameObjectPositionalContainer.push_back(pGameObjectLight);
	mGameObjectNonMovableContainer.push_back(pGameObjectLight);
	mGameObjectLightContainer.push_back(pGameObjectLight);
}

void GameWorldManager::addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet)
{
	mGameObjects[pGameObjectBillboardSet->getName()]=pGameObjectBillboardSet;

	mGameObjectPositionalContainer.push_back(pGameObjectBillboardSet);
	mGameObjectNonMovableContainer.push_back(pGameObjectBillboardSet);
	mGameObjectBillboardSetContainer.push_back(pGameObjectBillboardSet);
}

void GameWorldManager::addGameObjectParticleSystem(GameObjectParticleSystemPtr pGameObjectParticleSystem)
{
	mGameObjects[pGameObjectParticleSystem->getName()]=pGameObjectParticleSystem;

	mGameObjectPositionalContainer.push_back(pGameObjectParticleSystem);
	mGameObjectNonMovableContainer.push_back(pGameObjectParticleSystem);
	mGameObjectParticleSystemContainer.push_back(pGameObjectParticleSystem);
}


void GameWorldManager::addGameObjectCamera(GameObjectCameraPtr pGameObjectCamera)
{
	mGameObjects[pGameObjectCamera->getName()]=pGameObjectCamera;
}

void GameWorldManager::addGameObjectVolumeBox(GameObjectVolumeBoxPtr pGameObjectVolumeBox)
{
	//TODO - FIX THIS
	pGameObjectVolumeBox->getPhysicsComponentVolumeBox()->setNxOgreSize(NxOgre::Vec3(8,8,4));

	mGameObjects[pGameObjectVolumeBox->getName()]=pGameObjectVolumeBox;

	mGameObjectVolumeBoxContainer.push_back(pGameObjectVolumeBox);

	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectVolumeBox);
}

void GameWorldManager::addGameObjectVolumeCapsule(GameObjectVolumeCapsulePtr pGameObjectVolumeCapsule)
{
	mGameObjects[pGameObjectVolumeCapsule->getName()]=pGameObjectVolumeCapsule;

	mGameObjectVolumeCapsuleContainer.push_back(pGameObjectVolumeCapsule);

	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectVolumeCapsule);
}

void GameWorldManager::addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport)
{
	mGameObjects[pGameObjectViewport->getName()]=pGameObjectViewport;

	mGameObjectViewportContainer.push_back(pGameObjectViewport);

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
	pGameObjectOny = GameObjectOnyPtr(new GameObjectOny(tGameObjectOnyParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectOny->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectOny->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectOnyParameters.name,
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectOny->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectOny,
			tGameObjectOnyParameters.tPhysicsComponentCharacterParameters,
			pGameObjectOny->getRenderComponentPositional()));

	//Set Ony as camera target
	pGameObjectOny->getRenderComponentPositional()->setAsCameraTarget();

	pGameObjectOny->changeWorld(world);

	//Add reference to this
	pGameObjectOny->setGameWorldManager(mThis);
	pGameObjectOny->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectOny(pGameObjectOny);
}

void GameWorldManager::createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters)
{
	GameObjectTripolloPtr pGameObjectTripollo;

	//Create GameObject
	pGameObjectTripollo = GameObjectTripolloPtr(new GameObjectTripollo(tGameObjectTripolloParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectTripollo->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectTripollo->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectTripolloParameters.dreamsName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectTripollo->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectTripolloParameters.nightmaresName,
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectTripollo->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectTripollo,
			tGameObjectTripolloParameters.tPhysicsComponentCharacterParameters,
			pGameObjectTripollo->getRenderComponentPositional()));
	
	pGameObjectTripollo->changeWorld(world);

	// Add a reference to this
	pGameObjectTripollo->setGameWorldManager(mThis);
	pGameObjectTripollo->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectTripollo(pGameObjectTripollo);
}

void GameWorldManager::createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters)
{
	GameObjectEyePtr pGameObjectEye;

	//Create GameObject
	pGameObjectEye = GameObjectEyePtr(new GameObjectEye(tGameObjectEyeParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectEye->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectEye->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectEyeParameters.name,
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectEye->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectEye,
			tGameObjectEyeParameters.tPhysicsComponentCharacterParameters,
			pGameObjectEye->getRenderComponentPositional()));

	pGameObjectEye->changeWorld(world);

	// Add a reference to this
	pGameObjectEye->setGameWorldManager(mThis);
	pGameObjectEye->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectEye(pGameObjectEye);
}

void GameWorldManager::createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters)
{
	GameObjectItem1UPPtr pGameObjectItem1UP;

	//Create GameObject
	pGameObjectItem1UP = GameObjectItem1UPPtr(new GameObjectItem1UP(tGameObjectItem1UPParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectItem1UP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItem1UP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItem1UPParameters.name,
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters));
	
	pGameObjectItem1UP->changeWorld(world);
	
	// Add a reference to this
	pGameObjectItem1UP->setGameWorldManager(mThis);
	pGameObjectItem1UP->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectItem1UP(pGameObjectItem1UP);
}

void GameWorldManager::createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters)
{
	GameObjectPortalPtr pGameObjectPortal;

	//Create GameObject
	pGameObjectPortal = GameObjectPortalPtr(new GameObjectPortal(tGameObjectPortalParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectPortal->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectPortal->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectPortalParameters.name,
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityParameters));

	pGameObjectPortal->changeWorld(world);

	// Add a reference to this
	pGameObjectPortal->setGameWorldManager(mThis);
	pGameObjectPortal->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectPortal(pGameObjectPortal);
}

void GameWorldManager::createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters)
{
	GameObjectItemMaxHPPtr pGameObjectItemMaxHP;

	//Create GameObject
	pGameObjectItemMaxHP = GameObjectItemMaxHPPtr(new GameObjectItemMaxHP(tGameObjectItemMaxHPParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectItemMaxHP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItemMaxHP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItemMaxHPParameters.name,
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters));

	pGameObjectItemMaxHP->changeWorld(world);

	// Add a reference to this
	pGameObjectItemMaxHP->setGameWorldManager(mThis);
	pGameObjectItemMaxHP->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectItemMaxHP(pGameObjectItemMaxHP);
}

void GameWorldManager::createGameObjectTerrain(TGameObjectTerrainParameters tGameObjectTerrainParameters)
{
	GameObjectTerrainPtr pGameObjectTerrain;

	//Create GameObject
	pGameObjectTerrain = GameObjectTerrainPtr(new GameObjectTerrain(tGameObjectTerrainParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectTerrain->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTerrain,tGameObjectTerrainParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTerrain->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectTerrainParameters.name,
			pGameObjectTerrain,tGameObjectTerrainParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectTerrain->setPhysicsComponentComplexTriangle(factory->createPhysicsComponentComplexTriangle(
			pGameObjectTerrain,
			tGameObjectTerrainParameters.tPhysicsComponentComplexTriangleParameters,
			pGameObjectTerrain->getRenderComponentPositional()));
		/*
		pGameObjectTerrain->setPhysicsComponentComplexConvex(factory->createPhysicsComponentComplexConvex(
			pGameObjectTerrain,
			tGameObjectTerrainParameters.tPhysicsComponentComplexConvexParameters,
			pGameObjectTerrain->getRenderComponentPositional()));
		*/
	pGameObjectTerrain->changeWorld(world);

	// Add a reference to this
	pGameObjectTerrain->setGameWorldManager(mThis);
	pGameObjectTerrain->registerHandlers();
	//Add Object to GameWorldManager
	addGameObjectTerrain(pGameObjectTerrain);
}

void GameWorldManager::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters)
{
	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(tGameObjectLightParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectLight->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentLight
		pGameObjectLight->setRenderComponentLight(factory->createRenderComponentLight(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentLightParameters));
	
	pGameObjectLight->changeWorld(world);

	// Add a reference to this
	pGameObjectLight->setGameWorldManager(mThis);
	pGameObjectLight->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectLight(pGameObjectLight);
}

void GameWorldManager::createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters)
{
	GameObjectBillboardSetPtr pGameObjectBillboardSet;

	//Create GameObject
	pGameObjectBillboardSet = GameObjectBillboardSetPtr(new GameObjectBillboardSet(tGameObjectBillboardSetParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectBillboardSet->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentBillboardSet
		pGameObjectBillboardSet->setRenderComponentBillboardSet(factory->createRenderComponentBillboardSet(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters));
	
	pGameObjectBillboardSet->changeWorld(world);
	// Add a reference to this
	pGameObjectBillboardSet->setGameWorldManager(mThis);
	pGameObjectBillboardSet->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectBillboardSet(pGameObjectBillboardSet);
}

void GameWorldManager::createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters)
{
	GameObjectParticleSystemPtr pGameObjectParticleSystem;

	//Create GameObject
	pGameObjectParticleSystem = GameObjectParticleSystemPtr(new GameObjectParticleSystem(tGameObjectParticleSystemParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectParticleSystem->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentParticleSystem
		pGameObjectParticleSystem->setRenderComponentParticleSystem(factory->createRenderComponentParticleSystem(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters));

	pGameObjectParticleSystem->changeWorld(world);

	// Add a reference to this
	pGameObjectParticleSystem->setGameWorldManager(mThis);
	pGameObjectParticleSystem->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectParticleSystem(pGameObjectParticleSystem);
}

void GameWorldManager::createGameObjectCamera(TGameObjectCameraParameters tGameObjectCameraParameters)
{
	GameObjectCameraPtr pGameObjectCamera;

	//Create GameObject
	pGameObjectCamera = GameObjectCameraPtr(new GameObjectCamera(tGameObjectCameraParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

	//Create RenderComponentCamera
	pGameObjectCamera->setRenderComponentCamera(factory->createRenderComponentCamera(
		pGameObjectCamera,tGameObjectCameraParameters.tRenderComponentCameraParameters));


	pGameObjectCamera->changeWorld(world);

	// Add a reference to this
	pGameObjectCamera->setGameWorldManager(mThis);
	pGameObjectCamera->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectCamera(pGameObjectCamera);
}

void GameWorldManager::createGameObjectVolumeBox(TGameObjectVolumeBoxParameters tGameObjectVolumeBoxParameters)
{
	GameObjectVolumeBoxPtr pGameObjectVolumeBox;

	//Create GameObject
	pGameObjectVolumeBox = GameObjectVolumeBoxPtr(new GameObjectVolumeBox(tGameObjectVolumeBoxParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectVolumeBox->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectVolumeBox,tGameObjectVolumeBoxParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectVolumeBox->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectVolumeBoxParameters.name,
			pGameObjectVolumeBox,tGameObjectVolumeBoxParameters.tRenderComponentEntityParameters));

		//Make RenderComponentEntity not visible
		pGameObjectVolumeBox->getRenderComponentEntity()->setVisible(false);

		//Create PhysicsComponent
		pGameObjectVolumeBox->setPhysicsComponentVolumeBox(factory->createPhysicsComponentVolumeBox(
			pGameObjectVolumeBox,
			tGameObjectVolumeBoxParameters.tPhysicsComponentVolumeBoxParameters,
			pGameObjectVolumeBox->getRenderComponentPositional()));
	
	pGameObjectVolumeBox->changeWorld(world);

	// Add a reference to this
	pGameObjectVolumeBox->setGameWorldManager(mThis);
	pGameObjectVolumeBox->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectVolumeBox(pGameObjectVolumeBox);
}

void GameWorldManager::createGameObjectVolumeCapsule(TGameObjectVolumeCapsuleParameters tGameObjectVolumeCapsuleParameters)
{
	GameObjectVolumeCapsulePtr pGameObjectVolumeCapsule;

	//Create GameObject
	pGameObjectVolumeCapsule = GameObjectVolumeCapsulePtr(new GameObjectVolumeCapsule(tGameObjectVolumeCapsuleParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentPositional
		pGameObjectVolumeCapsule->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectVolumeCapsule,tGameObjectVolumeCapsuleParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectVolumeCapsule->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectVolumeCapsuleParameters.name,
			pGameObjectVolumeCapsule,tGameObjectVolumeCapsuleParameters.tRenderComponentEntityParameters));

		//Make RenderComponentEntity not visible
		pGameObjectVolumeCapsule->getRenderComponentEntity()->setVisible(false);

		//Create PhysicsComponent
		pGameObjectVolumeCapsule->setPhysicsComponentVolumeCapsule(factory->createPhysicsComponentVolumeCapsule(
			pGameObjectVolumeCapsule,
			tGameObjectVolumeCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters,
			pGameObjectVolumeCapsule->getRenderComponentPositional()));
	
	pGameObjectVolumeCapsule->changeWorld(world);

	// Add a reference to this
	pGameObjectVolumeCapsule->setGameWorldManager(mThis);
	pGameObjectVolumeCapsule->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectVolumeCapsule(pGameObjectVolumeCapsule);
}

void GameWorldManager::createGameObjectViewport(TGameObjectViewportParameters tGameObjectViewportParameters)
{
	GameObjectViewportPtr pGameObjectViewport;

	//Create GameObject
	pGameObjectViewport = GameObjectViewportPtr(new GameObjectViewport(tGameObjectViewportParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

	//Create RenderComponentViewport
	pGameObjectViewport->setRenderComponentViewport(factory->createRenderComponentViewport(
			pGameObjectViewport,tGameObjectViewportParameters.tRenderComponentViewportParameters));
	
	pGameObjectViewport->changeWorld(world);

	// Add a reference to this
	pGameObjectViewport->setGameWorldManager(mThis);
	pGameObjectViewport->registerHandlers();

	//Add Object to GameWorldManager
	addGameObjectViewport(pGameObjectViewport);
}

bool GameWorldManager::isGameOver()const
{
	return mGameOver;
}

void GameWorldManager::setGameOver(bool gameOver)
{
	mGameOver=gameOver;
}

void GameWorldManager::setWorld(int newWorld)
{
	world=newWorld;
}



int GameWorldManager::getCurrentWorld()
{
	return world;
}

void GameWorldManager::changeWorld()
{	
	if (world==DREAMS)
		world=NIGHTMARES;
	else if (world==NIGHTMARES)
		world=DREAMS;
	ChangeWorldEventPtr evt= ChangeWorldEventPtr(new ChangeWorldEvent(world));
	addEvent(evt);
}

void GameWorldManager::addEvent(OUAN::EventPtr event)
{
	mEventManager->addEvent(event);
}
void GameWorldManager::dispatchEvents()
{
	mEventManager->dispatchEvents();
}
EventManagerPtr GameWorldManager::getEventManager()
{
	return mEventManager;
}