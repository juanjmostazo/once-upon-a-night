
#include "GameWorldManager.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Component/ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectTerrain.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectScene.h"
#include "GameObject/GameObjectOny.h"
#include "GameObject/GameObjectTripollo.h"
#include "../Graphics/RenderSubsystem.h"
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
#include "../Physics/PhysicsComponent/PhysicsComponentComplexMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexNonMovable.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCube.h"

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

TGameObjectTerrainContainer GameWorldManager::getGameObjectTerrainContainer()
{
	return mGameObjectTerrain;
}

void GameWorldManager::loadLevel (const std::string& levelFileName)
{
	mApp->getLevelLoader()->loadLevel(levelFileName);
}

void GameWorldManager::unloadLevel()
{
	mNextIdNum=0;//reset id counter ??
	mGameObjects.clear();
	mGameObjectsToAdd.clear();
	mGameObjectsToDelete.clear();

	mGameObjectMovable.clear();
	mGameObjectMovableEntity.clear();
	mGameObjectNonMovable.clear();
	mGameObjectNonMovableEntity.clear();
	mGameObjectLight.clear();
	mGameObjectTerrain.clear();
	mGameObjectOny.clear();
	mGameObjectPositional.clear();
	mGameObjectScene.clear();
	mGameObjectTripollo.clear();

	//TODO RenderSubsystem CLEAR
	//PHysycs subsystem clear, etc...
	//landscape->cleanUp();
}

/// Initialise object
void GameWorldManager::initialise(ApplicationPtr app)
{
	mNextIdNum=0;
	mApp=app;
	mGameObjects.clear();
	mGameObjectsToAdd.clear();
	mGameObjectsToDelete.clear();

	mGameObjectMovable.clear();
	mGameObjectMovableEntity.clear();
	mGameObjectNonMovable.clear();
	mGameObjectNonMovableEntity.clear();
	mGameObjectLight.clear();
	mGameObjectTerrain.clear();
	mGameObjectOny.clear();
	mGameObjectPositional.clear();
	mGameObjectScene.clear();
	mGameObjectTripollo.clear();
	//landscape.reset() | landscape->initialiseBlank() | ...
}

void GameWorldManager::cleanUp()
{
	// Careful with how game objects
	// (well, their components)
	// will free their resources!!
	mGameObjects.clear();
	mGameObjectsToAdd.clear();
	mGameObjectsToDelete.clear();

	mGameObjectMovable.clear();
	mGameObjectMovableEntity.clear();
	mGameObjectNonMovable.clear();
	mGameObjectNonMovableEntity.clear();
	mGameObjectLight.clear();
	mGameObjectTerrain.clear();
	mGameObjectOny.clear();
	mGameObjectPositional.clear();
	mGameObjectScene.clear();
	mGameObjectTripollo.clear();
}


void GameWorldManager::initialiseGlobalWorldData( /*const TGlobalWorldParameters& worldParams*/)
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
	mGameObjectOny.push_back(pGameObjectOny);
}

void GameWorldManager::addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo)
{
	mGameObjects[pGameObjectTripollo->getId()]=pGameObjectTripollo;

	mGameObjectPositional.push_back(pGameObjectTripollo);
	mGameObjectMovable.push_back(pGameObjectTripollo);
	mGameObjectMovableEntity.push_back(pGameObjectTripollo);
	mGameObjectTripollo.push_back(pGameObjectTripollo);
}

void GameWorldManager::addGameObjectTerrain(GameObjectTerrainPtr pGameObjectTerrain)
{
	mGameObjects[pGameObjectTerrain->getId()]=pGameObjectTerrain;

	mGameObjectPositional.push_back(pGameObjectTerrain);
	mGameObjectNonMovable.push_back(pGameObjectTerrain);
	mGameObjectNonMovableEntity.push_back(pGameObjectTerrain);
	mGameObjectTerrain.push_back(pGameObjectTerrain);
}
void GameWorldManager::addGameObjectLight(GameObjectLightPtr pGameObjectLight)
{
	mGameObjects[pGameObjectLight->getId()]=pGameObjectLight;

	mGameObjectPositional.push_back(pGameObjectLight);
	mGameObjectNonMovable.push_back(pGameObjectLight);
	mGameObjectLight.push_back(pGameObjectLight);
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

	//Add Object to GameWorldManager
	addGameObjectTripollo(pGameObjectTripollo);
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

		//Create PhysicsComponentTerrain
		pGameObjectTerrain->setPhysicsComponentComplexNonMovable(factory->createPhysicsComponentComplexNonMovable(
			pGameObjectTerrain,
			tGameObjectTerrainParameters.tPhysicsComponentComplexNonMovableParameters,
			pGameObjectTerrain->getRenderComponentPositional()));

	//Add Object to GameWorldManager
	addGameObjectTerrain(pGameObjectTerrain);
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