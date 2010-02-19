
#include "GameWorldManager.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Graphics/RenderSubsystem.h"
#include "ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectMovable.h"
#include "GameObject/GameObjectMovableEntity.h"
#include "RenderComponent/RenderComponent.h"
#include "RenderComponent/RenderComponentEntity.h"

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
}


void GameWorldManager::initialiseGlobalWorldData( /*const TGlobalWorldParameters& worldParams*/)
{
	// Set ambient light, skybox, etc.It is possible that all
	// those params end up being part of the "landscape"  object 
	// Jesus mentioned today (Feb 15th) <---- note: This is done by the createOctreeSceneManager method, as this info is in the Ogitor's file.

}

std::string GameWorldManager::makeIdString(const std::string& baseString,const int& padding, const unsigned long& value)
{
	std::ostringstream ostr(baseString);
	ostr<<"_"<<std::setw(padding)<<std::setfill('0')<<value;
	std::string s(ostr.str());
	return s;
	
}

bool GameWorldManager::existsObject(std::string name)
{
	GameObjectPtr gameObject;
	//Get GameObject to add the mesh file
	gameObject=getObject(name);

	//If the GameObject doesn't exist, we create a new one
	if(!gameObject)
	{
		return true;
	}
	return false;
}

void GameWorldManager::addGameObject(GameObjectPtr gameObject)
{
	if(!existsObject(gameObject->getName()))
	{
		mGameObjects[gameObject->getId()]=gameObject;
	}
}

void GameWorldManager::addGameObjectMovableEntity(GameObjectMovableEntityPtr gameObjectMovableEntity)
{
	if(!existsObject(gameObjectMovableEntity->getName()))
	{
		mGameObjects[gameObjectMovableEntity->getId()]=gameObjectMovableEntity;
	}
	//TODO: add to other maps
}

void GameWorldManager::createGameObject(String name, GameObjectPtr gameObject)
{
	gameObject = GameObjectPtr(new GameObject(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	addGameObject(gameObject);

}

void GameWorldManager::createGameObjectMovable(String name, GameObjectMovablePtr gameObjectMovable)
{
	GameObjectMovablePtr pGameObjectMovable;
	pGameObjectMovable = GameObjectMovablePtr(new GameObjectMovable(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	//TODO add to GameObjectMovable map
	//addGameObject(pGameObjectMovable);
}

void GameWorldManager::createGameObjectMovableEntity(TEntityParameters tEntityParameters)
{
	//TODO: movable entity nonmovable entity instead of this and add to proper gameobject map

	GameObjectMovableEntityPtr pGameObjectMovableEntity;

	//Create GameObject
	pGameObjectMovableEntity = GameObjectMovableEntityPtr(
		new GameObjectMovableEntity(tEntityParameters.name,makeIdString(tEntityParameters.name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));

	ComponentFactory* factory=ComponentFactory::getInstance();

	factory->createRenderComponentSceneNode(pGameObjectMovableEntity,tEntityParameters.TRenderComponentSceneNodeParameters);
	factory->createRenderComponentEntity(pGameObjectMovableEntity,tEntityParameters.TRenderComponentEntityParameters);

//[TODO: Add other components as they're implemented]
// Example:
//
//	 ComponentPtr physicsComponent = ComponentFactory::getInstance()->createPhysicsComponent(objectParams,go,mApp->getPhysicsSubsystem());
//
//	 ComponentPtr aiComponent = compFactory->createAIComponent(...);


	//Add GameObject to GameWorldManager
	//TODO add to GameObjectMovableEntity map
	addGameObjectMovableEntity(pGameObjectMovableEntity);

}
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