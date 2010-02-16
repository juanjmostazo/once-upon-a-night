
#include "GameWorldManager.h"

#include "ComponentFactory.h"
#include "GameObject.h"

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
	//[TODO] Uncomment line
	//mSceneLoader->loadLevel(this,levelFileName);
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


void GameWorldManager::initialiseGlobalWorldData(/*const TGlobalWorldParameters& worldParams*/)
{
	// Set ambient light, skybox, etc.It is possible that all
	// those params end up being part of the "landscape"  object 
	// Jesus mentioned today (Feb 15th)
}

std::string GameWorldManager::makeIdString(const std::string& baseString,const int& padding, const unsigned long& value)
{
	std::ostringstream ostr(baseString);
	ostr<<"_"<<std::setw(padding)<<std::setfill('0')<<value;
	std::string s(ostr.str());
	return s;
	
}
GameObjectPtr GameWorldManager::createGameObject(/*const TObjectParameters& objectParams*/)
{
	std::string name;//remove this
	GameObjectPtr gameObject = GameObjectPtr(new GameObject(name,makeIdString(name,GAMEOBJECT_ID_ZERO_PADDING,nextId())));
	ComponentFactory* factory=ComponentFactory::getInstance();
	
	//[TODO: Uncomment when the objectParams is implemented]
	////Create game object's components
	//ComponentPtr ogreComponent = ComponentFactory::getInstance()->createOgreComponent(objectParams,gameObject,mApp->getRenderSubsystem());
	
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
	return gameObject ;
}

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
