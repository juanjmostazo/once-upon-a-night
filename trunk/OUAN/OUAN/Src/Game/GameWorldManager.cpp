
#include "GameWorldManager.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Component/ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectMovable.h"
#include "GameObject/GameObjectMovableEntity.h"
#include "GameObject/GameObjectNonMovable.h"
#include "GameObject/GameObjectNonMovableEntity.h"
#include "GameObject/GameObjectNonMovableTerrain.h"
#include "GameObject/GameObjectNonMovableLight.h"
#include "GameObject/GameObjectPositional.h"
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
#include "../Graphics/RenderComponent/RenderComponentSceneNode.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"

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


TGameObjectMovableContainer GameWorldManager::getGameObjectMovable()
{
	return mGameObjectMovable;
}

TGameObjectMovableEntityContainer GameWorldManager::getGameObjectMovableEntity()
{
	return mGameObjectMovableEntity;
}

TGameObjectNonMovableContainer GameWorldManager::getGameObjectNonMovable()
{
	return mGameObjectNonMovable;
}

TGameObjectNonMovableEntityContainer GameWorldManager::getGameObjectNonMovableEntity()
{
	return mGameObjectNonMovableEntity;
}

TGameObjectOnyContainer GameWorldManager::getGameObjectOny()
{
	return mGameObjectOny;
}

TGameObjectPositionalContainer GameWorldManager::getGameObjectPositional()
{
	return mGameObjectPositional;
}

TGameObjectSceneContainer GameWorldManager::getGameObjectScene()
{
	return mGameObjectScene;
}

TGameObjectTripolloContainer GameWorldManager::getGameObjectTripollo()
{
	return mGameObjectTripollo;
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
	mGameObjectNonMovableLight.clear();
	mGameObjectNonMovableTerrain.clear();
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
	mGameObjectNonMovableLight.clear();
	mGameObjectNonMovableTerrain.clear();
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
	mGameObjectNonMovableLight.clear();
	mGameObjectNonMovableTerrain.clear();
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

void GameWorldManager::addGameObjectNonMovableTerrain(GameObjectNonMovableTerrainPtr pGameObjectNonMovableTerrain)
{
	mGameObjects[pGameObjectNonMovableTerrain->getId()]=pGameObjectNonMovableTerrain;

	mGameObjectPositional.push_back(pGameObjectNonMovableTerrain);
	mGameObjectNonMovable.push_back(pGameObjectNonMovableTerrain);
	mGameObjectNonMovableEntity.push_back(pGameObjectNonMovableTerrain);
	mGameObjectNonMovableTerrain.push_back(pGameObjectNonMovableTerrain);
}
void GameWorldManager::addGameObjectNonMovableLight(GameObjectNonMovableLightPtr pGameObjectNonMovableLight)
{
	mGameObjects[pGameObjectNonMovableLight->getId()]=pGameObjectNonMovableLight;

	mGameObjectPositional.push_back(pGameObjectNonMovableLight);
	mGameObjectNonMovable.push_back(pGameObjectNonMovableLight);
	mGameObjectNonMovableLight.push_back(pGameObjectNonMovableLight);
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

		//Create RenderComponentSceneNode
		pGameObjectOny->setRenderComponentSceneNode(factory->createRenderComponentSceneNode(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentSceneNodeParameters));

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

		//Create RenderComponentSceneNode
		pGameObjectTripollo->setRenderComponentSceneNode(factory->createRenderComponentSceneNode(
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentSceneNodeParameters));

		//Create RenderComponentEntity
		pGameObjectTripollo->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectTripollo,tGameObjectTripolloParameters.tRenderComponentEntityParameters));


	//Add Object to GameWorldManager
	addGameObjectTripollo(pGameObjectTripollo);
}

void GameWorldManager::createGameObjectNonMovableTerrain(TGameObjectNonMovableTerrainParameters tGameObjectNonMovableTerrainParameters)
{
	GameObjectNonMovableTerrainPtr pGameObjectNonMovableTerrain;

	//Create GameObject
	pGameObjectNonMovableTerrain = GameObjectNonMovableTerrainPtr(new GameObjectNonMovableTerrain(
		tGameObjectNonMovableTerrainParameters.name,makeIdString(tGameObjectNonMovableTerrainParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentSceneNode
		pGameObjectNonMovableTerrain->setRenderComponentSceneNode(factory->createRenderComponentSceneNode(
			pGameObjectNonMovableTerrain,tGameObjectNonMovableTerrainParameters.tRenderComponentSceneNodeParameters));

		//Create RenderComponentEntity
		pGameObjectNonMovableTerrain->setRenderComponentEntity(factory->createRenderComponentEntity(
			pGameObjectNonMovableTerrain,tGameObjectNonMovableTerrainParameters.tRenderComponentEntityParameters));

		Ogre::Entity * r=pGameObjectNonMovableTerrain->getRenderComponentEntity()->getEntity();
	//Add Object to GameWorldManager
	addGameObjectNonMovableTerrain(pGameObjectNonMovableTerrain);

}

void GameWorldManager::createGameObjectNonMovableLight(TGameObjectNonMovableLightParameters tGameObjectNonMovableLightParameters)
{

	GameObjectNonMovableLightPtr pGameObjectNonMovableLight;

	//Create GameObject
	pGameObjectNonMovableLight = GameObjectNonMovableLightPtr(new GameObjectNonMovableLight(
		tGameObjectNonMovableLightParameters.name,makeIdString(tGameObjectNonMovableLightParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create RenderComponentSceneNode
		pGameObjectNonMovableLight->setRenderComponentSceneNode(factory->createRenderComponentSceneNode(
			pGameObjectNonMovableLight,tGameObjectNonMovableLightParameters.tRenderComponentSceneNodeParameters));

		//Create RenderComponentLight
		pGameObjectNonMovableLight->setRenderComponentLight(factory->createRenderComponentLight(
			pGameObjectNonMovableLight,tGameObjectNonMovableLightParameters.tRenderComponentLightParameters));

	//Add Object to GameWorldManager
	addGameObjectNonMovableLight(pGameObjectNonMovableLight);
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
//	factory->createRenderComponentSceneNode(pGameObjectMovableEntity,tEntityParameters.TRenderComponentSceneNodeParameters);
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