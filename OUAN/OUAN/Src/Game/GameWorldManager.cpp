#include "GameWorldManager.h"
#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Component/ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectTerrainConvex.h"
#include "GameObject/GameObjectTerrainTriangle.h"
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
#include "GameObject/GameObjectProvisionalEntity.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
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
#include "../Event/EventProcessor.h"

#include <iomanip>
#include <sstream>

using namespace OUAN;

unsigned long GameWorldManager::mNextIdNum=0;

GameWorldManager::GameWorldManager()
{
	world=DREAMS;
	level=LEVEL_NONE;
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
		//Ogre::LogManager::getSingleton().logMessage("Updating game object " + it->second->getName());
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

TGameObjectContainer GameWorldManager::getAllGameObjects()
{
	return mGameObjects;
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
TGameObjectTerrainConvexContainer GameWorldManager::getGameObjectTerrainConvexContainer()
{
	return mGameObjectTerrainConvexContainer;
}
TGameObjectTerrainTriangleContainer GameWorldManager::getGameObjectTerrainTriangleContainer()
{
	return mGameObjectTerrainTriangleContainer;
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

TGameObjectPhysicsContainer GameWorldManager::getGameObjectPhysicsContainer()
{
	return mGameObjectPhysicsContainer;
}

TGameObjectPhysicsCharacterContainer GameWorldManager::getGameObjectPhysicsCharacterContainer()
{
	return mGameObjectPhysicsCharacterContainer;
}

TGameObjectPhysicsComplexContainer GameWorldManager::getGameObjectPhysicsComplexContainer()
{
	return mGameObjectPhysicsComplexContainer;
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

TGameObjectPhysicsSimpleBoxContainer GameWorldManager::getGameObjectPhysicsSimpleBoxContainer()
{
	return mGameObjectPhysicsSimpleBoxContainer;
}

TGameObjectPhysicsSimpleCapsuleContainer GameWorldManager::getGameObjectPhysicsSimpleCapsuleContainer()
{
	return mGameObjectPhysicsSimpleCapsuleContainer;
}

TGameObjectPhysicsVolumeContainer GameWorldManager::getGameObjectPhysicsVolumeContainer()
{
	return mGameObjectPhysicsVolumeContainer;
}

TGameObjectPhysicsVolumeBoxContainer GameWorldManager::getGameObjectPhysicsVolumeBoxContainer()
{
	return mGameObjectPhysicsVolumeBoxContainer;
}

TGameObjectPhysicsVolumeCapsuleContainer GameWorldManager::getGameObjectPhysicsVolumeCapsuleContainer()
{
	return mGameObjectPhysicsVolumeCapsuleContainer;
}

void GameWorldManager::loadLevel (const std::string& levelFileName)
{
	//Unload current level
	unloadLevel();

	// Set the initial world before the level loading, and then
	// just as game objects are created, they're initialized with the correct
	// world information.
	//Init physicssubsystem
	mApp->getPhysicsSubsystem()->initLevel(levelFileName);

	//Parse Level File and Create GameObjects
	mApp->getLevelLoader()->loadLevel(levelFileName);

	//Set Active Camera
	mApp->getRenderSubsystem()->getCameraManager()->setActiveCamera(OUAN::RUNNING_CAMERA_NAME);
	mApp->getRenderSubsystem()->getCameraManager()->setCameraType(OUAN::CAMERA_THIRD_PERSON);	

	mGameOver=false;

	level=levelFileName;
}

void GameWorldManager::clearContainers()
{
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
	mGameObjectTerrainConvexContainer.clear();
	mGameObjectTerrainTriangleContainer.clear();
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
	mNextIdNum=0;//reset id counter

	clearContainers();

	/***
	* This is done in
	* void GameRunningState::cleanUp(),
	* no need to do it here
	*/
	
	/***
	* IMPORTANT: UNCOMMENTING NEXT LINES
	* WILL CRASH mVisualDebuggerNode in RenderSubsystem
	* Why???
	*/

	mApp->getPhysicsSubsystem()->clear();
	mApp->getRenderSubsystem()->clear();
	//TODO: Clear more subsystems
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
	mEventProcessor.reset(new EventProcessor());
	mEventProcessor->init(mThis);

	//landscape.reset() | landscape->initBlank() | ...
}

void GameWorldManager::cleanUp()
{
	// Careful with how game objects
	// (well, their components)
	// will free their resources!!
	mEventManager->clear();
	clearContainers();
	mEventProcessor->cleanUp();
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

void GameWorldManager::addGameObjectOny(GameObjectOnyPtr pGameObjectOny)
{
	mGameObjects[pGameObjectOny->getName()]=pGameObjectOny;

	mGameObjectPositionalContainer.push_back(pGameObjectOny);
	mGameObjectMovableContainer.push_back(pGameObjectOny);
	mGameObjectMovableEntityContainer.push_back(pGameObjectOny);

	mGameObjectPhysicsContainer.push_back(pGameObjectOny);
	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectOny);

	mGameObjectOnyContainer.push_back(pGameObjectOny);
}

void GameWorldManager::addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo)
{
	mGameObjects[pGameObjectTripollo->getName()]=pGameObjectTripollo;

	mGameObjectPositionalContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableEntityContainer.push_back(pGameObjectTripollo);

	mGameObjectPhysicsContainer.push_back(pGameObjectTripollo);
	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectTripollo);

	mGameObjectTripolloContainer.push_back(pGameObjectTripollo);
}

void GameWorldManager::addGameObjectTerrainConvex(GameObjectTerrainConvexPtr pGameObjectTerrainConvex)
{
	mGameObjects[pGameObjectTerrainConvex->getName()]=pGameObjectTerrainConvex;

	mGameObjectPositionalContainer.push_back(pGameObjectTerrainConvex);
	mGameObjectNonMovableContainer.push_back(pGameObjectTerrainConvex);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectTerrainConvex);

	mGameObjectPhysicsContainer.push_back(pGameObjectTerrainConvex);	
	mGameObjectPhysicsComplexContainer.push_back(pGameObjectTerrainConvex);	
	mGameObjectPhysicsComplexConvexContainer.push_back(pGameObjectTerrainConvex);	

	mGameObjectTerrainConvexContainer.push_back(pGameObjectTerrainConvex);
}

void GameWorldManager::addGameObjectTerrainTriangle(GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle)
{
	mGameObjects[pGameObjectTerrainTriangle->getName()]=pGameObjectTerrainTriangle;

	mGameObjectPositionalContainer.push_back(pGameObjectTerrainTriangle);
	mGameObjectNonMovableContainer.push_back(pGameObjectTerrainTriangle);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectTerrainTriangle);

	mGameObjectPhysicsContainer.push_back(pGameObjectTerrainTriangle);	
	mGameObjectPhysicsComplexContainer.push_back(pGameObjectTerrainTriangle);	
	mGameObjectPhysicsComplexTriangleContainer.push_back(pGameObjectTerrainTriangle);	

	mGameObjectTerrainTriangleContainer.push_back(pGameObjectTerrainTriangle);
}


void GameWorldManager::addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP)
{
	mGameObjects[pGameObjectItem1UP->getName()]=pGameObjectItem1UP;

	mGameObjectPositionalContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItem1UP);

	mGameObjectPhysicsContainer.push_back(pGameObjectItem1UP);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectItem1UP);
	mGameObjectPhysicsSimpleCapsuleContainer.push_back(pGameObjectItem1UP);
}

void GameWorldManager::addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP)
{
	mGameObjects[pGameObjectItemMaxHP->getName()]=pGameObjectItemMaxHP;

	mGameObjectPositionalContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItemMaxHP);

	mGameObjectPhysicsContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectPhysicsSimpleCapsuleContainer.push_back(pGameObjectItemMaxHP);
}

void GameWorldManager::addGameObjectPortal(GameObjectPortalPtr pGameObjectPortal)
{
	mGameObjects[pGameObjectPortal->getName()]=pGameObjectPortal;

	mGameObjectPositionalContainer.push_back(pGameObjectPortal);
	mGameObjectNonMovableContainer.push_back(pGameObjectPortal);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectPortal);

	mGameObjectPhysicsContainer.push_back(pGameObjectPortal);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectPortal);
	mGameObjectPhysicsSimpleBoxContainer.push_back(pGameObjectPortal);
}

void GameWorldManager::addGameObjectEye(GameObjectEyePtr pGameObjectEye)
{
	mGameObjects[pGameObjectEye->getName()]=pGameObjectEye;

	mGameObjectPositionalContainer.push_back(pGameObjectEye);
	mGameObjectNonMovableContainer.push_back(pGameObjectEye);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectEye);

	mGameObjectPhysicsContainer.push_back(pGameObjectEye);
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

void GameWorldManager::addGameObjectProvisionalEntity(GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity)
{
	mGameObjects[pGameObjectProvisionalEntity->getName()]=pGameObjectProvisionalEntity;
	mGameObjectPositionalContainer.push_back(pGameObjectProvisionalEntity);
	mGameObjectNonMovableContainer.push_back(pGameObjectProvisionalEntity);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectProvisionalEntity);

	mGameObjectPhysicsContainer.push_back(pGameObjectProvisionalEntity);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectProvisionalEntity);
	mGameObjectPhysicsSimpleBoxContainer.push_back(pGameObjectProvisionalEntity);
}

void GameWorldManager::addGameObjectVolumeBox(GameObjectVolumeBoxPtr pGameObjectVolumeBox)
{
	mGameObjects[pGameObjectVolumeBox->getName()]=pGameObjectVolumeBox;

	mGameObjectVolumeBoxContainer.push_back(pGameObjectVolumeBox);

	mGameObjectPhysicsContainer.push_back(pGameObjectVolumeBox);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectVolumeBox);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectVolumeBox);
}

void GameWorldManager::addGameObjectVolumeCapsule(GameObjectVolumeCapsulePtr pGameObjectVolumeCapsule)
{
	mGameObjects[pGameObjectVolumeCapsule->getName()]=pGameObjectVolumeCapsule;

	mGameObjectVolumeCapsuleContainer.push_back(pGameObjectVolumeCapsule);

	mGameObjectPhysicsContainer.push_back(pGameObjectVolumeCapsule);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectVolumeCapsule);
	mGameObjectPhysicsVolumeCapsuleContainer.push_back(pGameObjectVolumeCapsule);
}

void GameWorldManager::addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport)
{
	mGameObjects[pGameObjectViewport->getName()]=pGameObjectViewport;

	mGameObjectViewportContainer.push_back(pGameObjectViewport);
}

void GameWorldManager::addGameObjectScene(GameObjectScenePtr pGameObjectScene)
{
	mGameObjects[pGameObjectScene->getName()]=pGameObjectScene;

	mGameObjectSceneContainer.push_back(pGameObjectScene);
}

void GameWorldManager::createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters)
{
	GameObjectOnyPtr pGameObjectOny;

	//Create GameObject
	pGameObjectOny = GameObjectOnyPtr(new GameObjectOny(tGameObjectOnyParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectOny->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectOnyParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectOny->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectOny->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectOnyParameters.dreamsName,
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectOny->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectOnyParameters.nightmaresName,
			pGameObjectOny,tGameObjectOnyParameters.tRenderComponentEntityNightmaresParameters));
		
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

		//Create LogicComponentWorldExistance
		pGameObjectTripollo->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectTripolloParameters.tLogicComponentWorldExistanceParameters));

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

		//Create LogicComponentWorldExistance
		pGameObjectEye->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectEyeParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectEye->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectEye->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectEyeParameters.name,
			pGameObjectEye,tGameObjectEyeParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectEye->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectEye,
			tGameObjectEyeParameters.tPhysicsComponentCharacterParameters,
			pGameObjectEye->getRenderComponentPositional()));

	pGameObjectEye->changeWorld(world);

	// Add a reference to this
	pGameObjectEye->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectItem1UP->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectItem1UPParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectItem1UP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItem1UP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItem1UPParameters.name,
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters));
	
		//Create PhysicsComponent
		pGameObjectItem1UP->setPhysicsComponentSimpleCapsule(
			factory->createPhysicsComponentSimpleCapsule(
				pGameObjectItem1UP, 
				tGameObjectItem1UPParameters.tPhysicsComponentSimpleCapsuleParameters, 
				pGameObjectItem1UP->getRenderComponentPositional()));

	pGameObjectItem1UP->changeWorld(world);
	
	// Add a reference to this
	pGameObjectItem1UP->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectPortal->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectPortalParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectPortal->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectPortal->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectPortalParameters.dreamsName,
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectPortal->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectPortalParameters.nightmaresName,
			pGameObjectPortal,tGameObjectPortalParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectPortal->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
			pGameObjectPortal, 
			tGameObjectPortalParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectPortal->getRenderComponentPositional()));

	pGameObjectPortal->changeWorld(world);

	// Add a reference to this
	pGameObjectPortal->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectItemMaxHP->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectItemMaxHPParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectItemMaxHP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItemMaxHP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItemMaxHPParameters.name,
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectItemMaxHP->setPhysicsComponentSimpleCapsule(
			factory->createPhysicsComponentSimpleCapsule(
			pGameObjectItemMaxHP, 
			tGameObjectItemMaxHPParameters.tPhysicsComponentSimpleCapsuleParameters, 
			pGameObjectItemMaxHP->getRenderComponentPositional()));

		//Create LogicComponentWorldExistance
		pGameObjectItemMaxHP->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectItemMaxHPParameters.tLogicComponentWorldExistanceParameters));

	pGameObjectItemMaxHP->changeWorld(world);

	// Add a reference to this
	pGameObjectItemMaxHP->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectItemMaxHP(pGameObjectItemMaxHP);
}

void GameWorldManager::createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters)
{
	GameObjectTerrainConvexPtr pGameObjectTerrainConvex;

	//Create GameObject
	pGameObjectTerrainConvex = GameObjectTerrainConvexPtr(new GameObjectTerrainConvex(tGameObjectTerrainConvexParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectTerrainConvex->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectTerrainConvexParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectTerrainConvex->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentPositionalParameters));

		if(pGameObjectTerrainConvex->getLogicComponentWorldExistance()->getExistsInDreams())
		{
			//Create RenderComponentEntityDreams
			pGameObjectTerrainConvex->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.dreamsName,
				pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectTerrainConvex->getLogicComponentWorldExistance()->getExistsInNightmares())
		{
			//Create RenderComponentEntityNightmares
			pGameObjectTerrainConvex->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.nightmaresName,
				pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityNightmaresParameters));
		}
		//Create PhysicsComponent
		pGameObjectTerrainConvex->setPhysicsComponentComplexConvex(factory->createPhysicsComponentComplexConvex(
			pGameObjectTerrainConvex,
			tGameObjectTerrainConvexParameters.tPhysicsComponentComplexConvexParameters,
			pGameObjectTerrainConvex->getRenderComponentPositional()));

	pGameObjectTerrainConvex->changeWorld(world);

	// Add a reference to this
	pGameObjectTerrainConvex->setGameWorldManager(mThis);
	//Add Object to GameWorldManager
	addGameObjectTerrainConvex(pGameObjectTerrainConvex);
}

void GameWorldManager::createGameObjectTerrainTriangle(TGameObjectTerrainTriangleParameters tGameObjectTerrainTriangleParameters)
{
	GameObjectTerrainTrianglePtr pGameObjectTerrainTriangle;

	//Create GameObject
	pGameObjectTerrainTriangle = GameObjectTerrainTrianglePtr(new GameObjectTerrainTriangle(tGameObjectTerrainTriangleParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectTerrainTriangle->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectTerrainTriangleParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectTerrainTriangle->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectTerrainTriangle->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectTerrainTriangleParameters.dreamsName,
			pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectTerrainTriangle->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectTerrainTriangleParameters.nightmaresName,
			pGameObjectTerrainTriangle,tGameObjectTerrainTriangleParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectTerrainTriangle->setPhysicsComponentComplexTriangle(factory->createPhysicsComponentComplexTriangle(
			pGameObjectTerrainTriangle,
			tGameObjectTerrainTriangleParameters.tPhysicsComponentComplexTriangleParameters,
			pGameObjectTerrainTriangle->getRenderComponentPositional()));

	pGameObjectTerrainTriangle->changeWorld(world);

	// Add a reference to this
	pGameObjectTerrainTriangle->setGameWorldManager(mThis);
	//Add Object to GameWorldManager
	addGameObjectTerrainTriangle(pGameObjectTerrainTriangle);
}

void GameWorldManager::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters)
{
	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(tGameObjectLightParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectLight->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectLightParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectLight->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentLight
		pGameObjectLight->setRenderComponentLight(factory->createRenderComponentLight(
			pGameObjectLight,tGameObjectLightParameters.tRenderComponentLightParameters));
	
	pGameObjectLight->changeWorld(world);

	// Add a reference to this
	pGameObjectLight->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectBillboardSet->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectBillboardSetParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectBillboardSet->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentBillboardSet
		pGameObjectBillboardSet->setRenderComponentBillboardSet(factory->createRenderComponentBillboardSet(
			pGameObjectBillboardSet,tGameObjectBillboardSetParameters.tRenderComponentBillboardSetParameters));
	
	pGameObjectBillboardSet->changeWorld(world);

	// Add a reference to this
	pGameObjectBillboardSet->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectParticleSystem->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectParticleSystemParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectParticleSystem->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentParticleSystem
		pGameObjectParticleSystem->setRenderComponentParticleSystem(factory->createRenderComponentParticleSystem(
			pGameObjectParticleSystem,tGameObjectParticleSystemParameters.tRenderComponentParticleSystemParameters));

	pGameObjectParticleSystem->changeWorld(world);

	// Add a reference to this
	pGameObjectParticleSystem->setGameWorldManager(mThis);

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

		//Create LogicComponentWorldExistance
		pGameObjectVolumeBox->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectVolumeBoxParameters.tLogicComponentWorldExistanceParameters));

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

		//Create LogicComponentWorldExistance
		pGameObjectVolumeCapsule->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectVolumeCapsuleParameters.tLogicComponentWorldExistanceParameters));

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


	//Add Object to GameWorldManager
	addGameObjectViewport(pGameObjectViewport);
}

void GameWorldManager::createGameObjectScene(TGameObjectSceneParameters tGameObjectSceneParameters)
{

	GameObjectScenePtr pGameObjectScene;

	//Create GameObject
	pGameObjectScene = GameObjectScenePtr(new GameObjectScene(tGameObjectSceneParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

	//Create RenderComponentViewport
	pGameObjectScene->setRenderComponentScene(factory->createRenderComponentScene(
			pGameObjectScene,tGameObjectSceneParameters.tRenderComponentSceneParameters));
	
	pGameObjectScene->changeWorld(world);

	// Add a reference to this
	pGameObjectScene->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectScene(pGameObjectScene);

}

void GameWorldManager::createGameObjectProvisionalEntity(TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters)
{
	GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity;

	//Create GameObject
	pGameObjectProvisionalEntity = GameObjectProvisionalEntityPtr(new GameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectProvisionalEntity->setLogicComponentWorldExistance(
			factory->createLogicComponentWorldExistance(
			tGameObjectProvisionalEntityParameters.tLogicComponentWorldExistanceParameters));

		//Create RenderComponentPositional
		pGameObjectProvisionalEntity->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity Dreams
		pGameObjectProvisionalEntity->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.dreamsName,
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntity Nightmares
		pGameObjectProvisionalEntity->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.nightmaresName,
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectProvisionalEntity->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
				pGameObjectProvisionalEntity, 
				tGameObjectProvisionalEntityParameters.tPhysicsComponentSimpleBoxParameters,
				pGameObjectProvisionalEntity->getRenderComponentPositional()));

	pGameObjectProvisionalEntity->changeWorld(world);
	
	// Add a reference to this
	pGameObjectProvisionalEntity->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectProvisionalEntity(pGameObjectProvisionalEntity);
}

void GameWorldManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	mApp->getRenderSubsystem()->getTrajectoryManager()->createTrajectory(tTrajectoryParameters);
}

bool GameWorldManager::isGameOver()const
{
	return mGameOver;
}

void GameWorldManager::setGameOver(bool gameOver)
{
	mGameOver=gameOver;
}

std::string GameWorldManager::getCurrentLevel() const
{
	return level;
}

void GameWorldManager::setWorld(int newWorld)
{
	world=newWorld;
}

int GameWorldManager::getCurrentWorld() const
{
	return world;
}

void GameWorldManager::changeWorld()
{	
	if (world==DREAMS)
	{
		world=NIGHTMARES;
	}
	else if (world==NIGHTMARES)
	{
		world=DREAMS;
	}

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

GameObjectOnyPtr GameWorldManager::getGameObjectOny()
{
	return mGameObjectOnyContainer[0];

}