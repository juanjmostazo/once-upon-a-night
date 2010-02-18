
#include "GameWorldManager.h"

#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Graphics/RenderSubsystem.h"
#include "ComponentFactory.h"
#include "GameObject.h"
#include "OgreComponent.h"


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
GameObjectPtr GameWorldManager::createGameObject(String name/*const TObjectParameters& objectParams*/)
{
	GameObjectPtr gameObject;
	//Get GameObject to add the mesh file
	gameObject=getObject(name);

	//If the GameObject doesn't exist, we create a new one
	if(!gameObject)
	{
		gameObject = GameObjectPtr(new GameObject(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
		addGameObject(gameObject);

		ComponentFactory* factory=ComponentFactory::getInstance();
	}


	return gameObject ;
}

OgreComponentPtr GameWorldManager::createOgreComponent(GameObjectPtr gameObject)
{
	////Create game object's components
	OgreComponentPtr ogreComponent = ComponentFactory::getInstance()->createOgreComponent(gameObject);
	return ogreComponent;
}

//[TODO: Add other components as they're implemented]
// Example:
// if (!objectParams.physicsFile.empty())
// {
//	 ComponentPtr physicsComponent = ComponentFactory::getInstance()->createPhysicsComponent(objectParams,go,mApp->getPhysicsSubsystem());
// }
// if (!objectParams.aiFile.empty())
// {
//	 ComponentPtr aiComponent = compFactory->createAIComponent(...);
// }

void GameWorldManager::addGameObject(GameObjectPtr gameObject)
{
	if (gameObject.get()) //NULL test for shared pointers
	{
		mGameObjects[gameObject->getId()]=gameObject;
	}
}

void GameWorldManager::update(long elapsedTime)
{
	for (TGameObjectContainerIterator it= mGameObjects.begin();it!=mGameObjects.end();++it)
	{
		it->second->onUpdate(elapsedTime);
	}
}

void GameWorldManager::createGameObjectEntity(TEntityParameters tEntityParameters)
{
	GameObjectPtr pGameObject;
	OgreComponentPtr pOgreComponent;
	Ogre::Entity *pEntity;

	//Create GameObject
	pGameObject=createGameObject(tEntityParameters.name);

	//Initialise Render Component
	pEntity=mApp->getRenderSubsystem()->createEntity(tEntityParameters.name,tEntityParameters.tEntityRenderParameters);

	//Create Ogre Component
	pOgreComponent=createOgreComponent(pGameObject);
	
	//Set Ogre component's Entity
	pOgreComponent->setEntity(pEntity);
}

void GameWorldManager::createSceneNode(TSceneNodeParameters tSceneNodeParameters)
{
	//Create GameObject
	createGameObject(tSceneNodeParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSceneNode(tSceneNodeParameters.name,tSceneNodeParameters.tSceneNodeRenderParameters);
}
void GameWorldManager::createLight(TLightParameters tLightParameters)
{
	//Create GameObject
	createGameObject(tLightParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createLight(tLightParameters.name,tLightParameters.tLightRenderParameters);
}
void GameWorldManager::createParticleSystem(TParticleSystemParameters tParticleSystemParameters)
{
	//Create GameObject
	createGameObject(tParticleSystemParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createParticleSystem(tParticleSystemParameters.name,tParticleSystemParameters.tParticleSystemRenderParameters);
}

void GameWorldManager::createBillboardSet(TBillboardSetParameters tBillboardSetParameters)
{
	//Create GameObject
	createGameObject(tBillboardSetParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createBillboardSet(tBillboardSetParameters.name,tBillboardSetParameters.tBillboardSetRenderParameters);
}
void GameWorldManager::createViewport(TViewportParameters tViewportParameters)
{
	//Create GameObject
	createGameObject(tViewportParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createViewport(tViewportParameters.name,tViewportParameters.tViewPortRenderParameters);
}
void GameWorldManager::createCamera(TCameraParameters tCameraParameters)
{
	//Create GameObject
	createGameObject(tCameraParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createCamera(tCameraParameters.name,tCameraParameters.tCameraRenderParameters);
}
void GameWorldManager::createSceneManager(TSceneManagerParameters tSceneManagerParameters)
{
	//Create GameObject
	createGameObject(tSceneManagerParameters.name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSceneManager(tSceneManagerParameters.name,tSceneManagerParameters.tSceneManagerRenderParameters);
}