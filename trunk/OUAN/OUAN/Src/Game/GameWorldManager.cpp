
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


void GameWorldManager::createMeshFile(String meshfile)
{
	//Create GameObject
	createGameObject(meshfile);
	
	//Initialise Render Component
	mApp->getRenderSubsystem()->createMeshFile(meshfile);
}
void GameWorldManager::createEntity(String name,String meshfile,bool castshadows)
{
	GameObjectPtr pGameObject;
	OgreComponentPtr pOgreComponent;
	Ogre::Entity *pEntity;

	//Create GameObject
	pGameObject=createGameObject(name);

	//Initialise Render Component
	pEntity=mApp->getRenderSubsystem()->createEntity(name,meshfile,castshadows);

	//Create Ogre Component
	pOgreComponent=createOgreComponent(pGameObject);
	
	//Set Ogre component's Entity
	pOgreComponent->setEntity(pEntity);
}
void GameWorldManager::createSubEntity(String name,int num,String material,bool visible)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSubEntity(name,num,material,visible);
}
void GameWorldManager::createSceneNode(String name,String parentSceneNodeName,Vector3 position,Quaternion orientation,Vector3 scale,String autotracktarget)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSceneNode(name,parentSceneNodeName,position,orientation,scale,autotracktarget);
}
void GameWorldManager::createLight(String name,Ogre::Light::LightTypes lighttype,ColourValue diffuse,ColourValue specular,Vector3 direction,bool castshadows,Vector3 lightrange,Vector4 attenuation,Real power)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createLight(name,lighttype,diffuse,specular,direction,castshadows,lightrange,attenuation,power);
}
void GameWorldManager::createParticleSystem(String name,String particle,bool castshadows)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createParticleSystem(name,particle,castshadows);
}
void GameWorldManager::createBillboard(String billBoardSetName,ColourValue colour,Vector2 dimensions,Vector3 position,Real rotation,int texcoordindex,Vector4 texrect)
{
	//Create GameObject
	createGameObject(billBoardSetName);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createBillboard(billBoardSetName,colour,dimensions,position,rotation,texcoordindex,texrect);
}
void GameWorldManager::createBillboardSet(String name,String material,Ogre::BillboardOrigin billboardorigin,Ogre::BillboardRotationType billboardrotation,Ogre::BillboardType billboardtype,Real defaultheight,Real defaultwidth,bool pointrendering,Real renderdistance,bool sorting)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createBillboardSet(name,material,billboardorigin,billboardrotation,billboardtype,defaultheight,defaultwidth,pointrendering,renderdistance,sorting);
}
void GameWorldManager::createViewport(String name,ColourValue colour,int compositorcount,int index,bool overlays,bool shadows,bool skies)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createViewport(name,colour,compositorcount,index,overlays,shadows,skies);
}
void GameWorldManager::createCamera(String name,Vector3 position,Quaternion orientation,String autotracktarget,bool autoaspectratio,Vector2 clipdistance,Real fov,Ogre::PolygonMode polygonmode, int viewmode)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createCamera(name,position,orientation,autotracktarget,autoaspectratio,clipdistance,fov,polygonmode,viewmode);
}
void GameWorldManager::createOctreeSceneManager(String name,ColourValue ambient)
{
	//Create GameObject
	createGameObject(name);

	//Initialise Render Component
	mApp->getRenderSubsystem()->createOctreeSceneManager(name,ambient);
}
void GameWorldManager::createSkyBox(bool active, String material, Real distance)
{
	//Create GameObject
	createGameObject("SkyBox");

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSkyBox(active, material, distance);
}
void GameWorldManager::createSkyDome(bool active, String material)
{
	//Create GameObject
	createGameObject("SkyDome");

	//Initialise Render Component
	mApp->getRenderSubsystem()->createSkyDome(active, material);
}

