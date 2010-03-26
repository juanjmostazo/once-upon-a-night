#include "GameWorldManager.h"
#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "../Component/ComponentFactory.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectBee_Butterfly.h"
#include "GameObject/GameObjectBillboardSet.h"
#include "GameObject/GameObjectBush.h"
#include "GameObject/GameObjectCamera.h"
#include "GameObject/GameObjectCarnivorousPlant.h"
#include "GameObject/GameObjectClockPiece.h"
#include "GameObject/GameObjectCryKing.h"
#include "GameObject/GameObjectDiamond.h"
#include "GameObject/GameObjectDiamondTree.h"
#include "GameObject/GameObjectDoor.h"
#include "GameObject/GameObjectDragon.h"
#include "GameObject/GameObjectEye.h"
#include "GameObject/GameObjectFlashLight.h"
#include "GameObject/GameObjectHeart.h"
#include "GameObject/GameObjectItem1UP.h"
#include "GameObject/GameObjectItemMaxHP.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectMagicClock.h"
#include "GameObject/GameObjectNightGoblin.h"
#include "GameObject/GameObjectOny.h"
#include "GameObject/GameObjectParticleSystem.h"
#include "GameObject/GameObjectPillow.h"
#include "GameObject/GameObjectPlataform.h"
#include "GameObject/GameObjectPortal.h"
#include "GameObject/GameObjectProvisionalEntity.h"
#include "GameObject/GameObjectScaredPlant.h"
#include "GameObject/GameObjectScene.h"
#include "GameObject/GameObjectScepter.h"
#include "GameObject/GameObjectSnakeCreeper.h"
#include "GameObject/GameObjectStoryBook.h"
#include "GameObject/GameObjectTentetieso.h"
#include "GameObject/GameObjectTerrainConvex.h"
#include "GameObject/GameObjectTerrainTriangle.h"
#include "GameObject/GameObjectTree.h"
#include "GameObject/GameObjectTriggerBox.h"
#include "GameObject/GameObjectTriggerCapsule.h"
#include "GameObject/GameObjectTripollito.h"
#include "GameObject/GameObjectTripollo.h"
#include "GameObject/GameObjectViewport.h"

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

TGameObjectTriggerBoxContainer GameWorldManager::getGameObjectTriggerBoxContainer()
{
	return mGameObjectTriggerBoxContainer;
}

TGameObjectTriggerCapsuleContainer GameWorldManager::getGameObjectTriggerCapsuleContainer()
{
	return mGameObjectTriggerCapsuleContainer;
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
	mGameObjectTriggerBoxContainer.clear();
	mGameObjectTriggerCapsuleContainer.clear();

	mGameObjectPhysicsCharacterContainer.clear();
	mGameObjectPhysicsComplexConvexContainer.clear();
	mGameObjectPhysicsComplexTriangleContainer.clear();
	mGameObjectPhysicsSimpleContainer.clear();
	mGameObjectPhysicsVolumeContainer.clear();
}

void GameWorldManager::loadLevel (const std::string& levelFileName)
{
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER LEVEL LOAD STARTED]");

	//Unload current level
	unloadLevel();

	//TODO: this should depend on which level is loaded and be determined by levelLoader

	// Set the initial world before the level loading, and then
	// just as game objects are created, they're initialized with the correct
	// world information.
	//Init physicssubsystem
	mApp->getPhysicsSubsystem()->initLevel(levelFileName);

	//Set world to dreams
	setWorld(DREAMS); 

	//Parse Level File and Create GameObjects
	mApp->getLevelLoader()->loadLevel(levelFileName);

	//Set Active Camera
	mApp->getRenderSubsystem()->getCameraManager()->setActiveCamera(OUAN::RUNNING_CAMERA_NAME);
	mApp->getRenderSubsystem()->getCameraManager()->setCameraType(OUAN::CAMERA_THIRD_PERSON);

	mGameOver=false;
	mGameBeaten=false;

	level=levelFileName;
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER LEVEL LOAD FINISHED]");
}

void GameWorldManager::unloadLevel()
{
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER LEVEL UNLOAD STARTED]");

	mNextIdNum=0;//reset id counter

	mApp->getPhysicsSubsystem()->clear();
	mApp->getRenderSubsystem()->clear();
	
	TGameObjectContainerIterator it;
	TGameObjectContainer container = Application::getInstance()->getGameWorldManager()->getAllGameObjects();

	for(it = container.begin(); it != container.end(); it++)
	{
		it->second.get()->~GameObject();
	}

	clearContainers();
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER LEVEL UNLOAD FINISHED]");
}

/// init object
void GameWorldManager::init(ApplicationPtr app)
{
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER GENERAL INIT STARTED]");
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
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER GENERAL INIT FINISHED]");
}

void GameWorldManager::cleanUp()
{
	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER GENERAL CLEANUP STARTED]");

	// Careful with how game objects
	// (well, their components)
	// will free their resources!!
	mEventManager->clear();
	clearContainers();
	mEventProcessor->cleanUp();

	Ogre::LogManager::getSingleton().logMessage("[GAME WORLD MANAGER GENERAL CLEANUP FINISHED]");
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

void GameWorldManager::addGameObjectBee_Butterfly(GameObjectBee_ButterflyPtr gameObjectBee_Butterfly)
{
	mGameObjects[gameObjectBee_Butterfly->getName()]=gameObjectBee_Butterfly;
}

void GameWorldManager::addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet)
{
	mGameObjects[pGameObjectBillboardSet->getName()]=pGameObjectBillboardSet;

	mGameObjectPositionalContainer.push_back(pGameObjectBillboardSet);
	mGameObjectNonMovableContainer.push_back(pGameObjectBillboardSet);
	mGameObjectBillboardSetContainer.push_back(pGameObjectBillboardSet);
}

void GameWorldManager::addGameObjectBush(GameObjectBushPtr gameObjectBush)
{
	mGameObjects[gameObjectBush->getName()]=gameObjectBush;
}

void GameWorldManager::addGameObjectCamera(GameObjectCameraPtr pGameObjectCamera)
{
	mGameObjects[pGameObjectCamera->getName()]=pGameObjectCamera;
}

void GameWorldManager::addGameObjectCarnivorousPlant(GameObjectCarnivorousPlantPtr gameObjectCarnivorousPlant)
{
	mGameObjects[gameObjectCarnivorousPlant->getName()]=gameObjectCarnivorousPlant;
}

void GameWorldManager::addGameObjectClockPiece(GameObjectClockPiecePtr gameObjectClockPiece)
{
	mGameObjects[gameObjectClockPiece->getName()]=gameObjectClockPiece;
}

void GameWorldManager::addGameObjectCryKing(GameObjectCryKingPtr gameObjectCryKing)
{
	mGameObjects[gameObjectCryKing->getName()]=gameObjectCryKing;
}

void GameWorldManager::addGameObjectDiamond(GameObjectDiamondPtr gameObjectDiamond)
{
	mGameObjects[gameObjectDiamond->getName()]=gameObjectDiamond;
}

void GameWorldManager::addGameObjectDiamondTree(GameObjectDiamondTreePtr gameObjectDiamondTree)
{
	mGameObjects[gameObjectDiamondTree->getName()]=gameObjectDiamondTree;
}

void GameWorldManager::addGameObjectDoor(GameObjectDoorPtr gameObjectDoor)
{
	mGameObjects[gameObjectDoor->getName()]=gameObjectDoor;
}

void GameWorldManager::addGameObjectDragon(GameObjectDragonPtr gameObjectDragon)
{
	mGameObjects[gameObjectDragon->getName()]=gameObjectDragon;
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

void GameWorldManager::addGameObjectFlashLight(GameObjectFlashLightPtr gameObjectFlashLight)
{
	mGameObjects[gameObjectFlashLight->getName()]=gameObjectFlashLight;
}

void GameWorldManager::addGameObjectHeart(GameObjectHeartPtr gameObjectHeart)
{
	mGameObjects[gameObjectHeart->getName()]=gameObjectHeart;
}

void GameWorldManager::addGameObjectItem1UP(GameObjectItem1UPPtr pGameObjectItem1UP)
{
	mGameObjects[pGameObjectItem1UP->getName()]=pGameObjectItem1UP;

	mGameObjectPositionalContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItem1UP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItem1UP);

	mGameObjectPhysicsContainer.push_back(pGameObjectItem1UP);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectItem1UP);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectItem1UP);
}

void GameWorldManager::addGameObjectItemMaxHP(GameObjectItemMaxHPPtr pGameObjectItemMaxHP)
{
	mGameObjects[pGameObjectItemMaxHP->getName()]=pGameObjectItemMaxHP;

	mGameObjectPositionalContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectItemMaxHP);

	mGameObjectPhysicsContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectItemMaxHP);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectItemMaxHP);
}

void GameWorldManager::addGameObjectLight(GameObjectLightPtr pGameObjectLight)
{
	mGameObjects[pGameObjectLight->getName()]=pGameObjectLight;

	mGameObjectPositionalContainer.push_back(pGameObjectLight);
	mGameObjectNonMovableContainer.push_back(pGameObjectLight);
	mGameObjectLightContainer.push_back(pGameObjectLight);
}

void GameWorldManager::addGameObjectMagicClock(GameObjectMagicClockPtr gameObjectMagicClock)
{
	mGameObjects[gameObjectMagicClock->getName()]=gameObjectMagicClock;
}

void GameWorldManager::addGameObjectNightGoblin(GameObjectNightGoblinPtr gameObjectNightGoblin)
{
	mGameObjects[gameObjectNightGoblin->getName()]=gameObjectNightGoblin;
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

void GameWorldManager::addGameObjectParticleSystem(GameObjectParticleSystemPtr pGameObjectParticleSystem)
{
	mGameObjects[pGameObjectParticleSystem->getName()]=pGameObjectParticleSystem;

	mGameObjectPositionalContainer.push_back(pGameObjectParticleSystem);
	mGameObjectNonMovableContainer.push_back(pGameObjectParticleSystem);
	mGameObjectParticleSystemContainer.push_back(pGameObjectParticleSystem);
}

void GameWorldManager::addGameObjectPillow(GameObjectPillowPtr gameObjectPillow)
{
	mGameObjects[gameObjectPillow->getName()]=gameObjectPillow;
}

void GameWorldManager::addGameObjectPlataform(GameObjectPlataformPtr gameObjectPlataform)
{
	mGameObjects[gameObjectPlataform->getName()]=gameObjectPlataform;
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

void GameWorldManager::addGameObjectScaredPlant(GameObjectScaredPlantPtr gameObjectScaredPlant)
{
	mGameObjects[gameObjectScaredPlant->getName()]=gameObjectScaredPlant;
}

void GameWorldManager::addGameObjectScene(GameObjectScenePtr pGameObjectScene)
{
	mGameObjects[pGameObjectScene->getName()]=pGameObjectScene;

	mGameObjectSceneContainer.push_back(pGameObjectScene);
}

void GameWorldManager::addGameObjectScepter(GameObjectScepterPtr gameObjectScepter)
{
	mGameObjects[gameObjectScepter->getName()]=gameObjectScepter;
}

void GameWorldManager::addGameObjectSnakeCreeper(GameObjectSnakeCreeperPtr gameObjectSnakeCreeper)
{
	mGameObjects[gameObjectSnakeCreeper->getName()]=gameObjectSnakeCreeper;
}

void GameWorldManager::addGameObjectStoryBook(GameObjectStoryBookPtr gameObjectStoryBook)
{
	mGameObjects[gameObjectStoryBook->getName()]=gameObjectStoryBook;
}

void GameWorldManager::addGameObjectTentetieso(GameObjectTentetiesoPtr gameObjectTentetieso)
{
	mGameObjects[gameObjectTentetieso->getName()]=gameObjectTentetieso;
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

void GameWorldManager::addGameObjectTree(GameObjectTreePtr gameObjectTree)
{
	mGameObjects[gameObjectTree->getName()]=gameObjectTree;
}

void GameWorldManager::addGameObjectTriggerBox(GameObjectTriggerBoxPtr pGameObjectTriggerBox)
{
	mGameObjects[pGameObjectTriggerBox->getName()]=pGameObjectTriggerBox;

	mGameObjectTriggerBoxContainer.push_back(pGameObjectTriggerBox);

	mGameObjectPhysicsContainer.push_back(pGameObjectTriggerBox);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectTriggerBox);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectTriggerBox);
}

void GameWorldManager::addGameObjectTriggerCapsule(GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule)
{
	mGameObjects[pGameObjectTriggerCapsule->getName()]=pGameObjectTriggerCapsule;

	mGameObjectTriggerCapsuleContainer.push_back(pGameObjectTriggerCapsule);

	mGameObjectPhysicsContainer.push_back(pGameObjectTriggerCapsule);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectTriggerCapsule);
	mGameObjectPhysicsVolumeCapsuleContainer.push_back(pGameObjectTriggerCapsule);
}

void GameWorldManager::addGameObjectTripollito(GameObjectTripollitoPtr gameObjectTripollito)
{
	mGameObjects[gameObjectTripollito->getName()]=gameObjectTripollito;
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

void GameWorldManager::addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport)
{
	mGameObjects[pGameObjectViewport->getName()]=pGameObjectViewport;

	mGameObjectViewportContainer.push_back(pGameObjectViewport);
}

void GameWorldManager::createGameObjectBee_Butterfly(TGameObjectBee_ButterflyParameters tGameObjectBee_ButterflyParameters)
{
	GameObjectBee_ButterflyPtr pGameObjectBee_Butterfly;

	//Create GameObject
	pGameObjectBee_Butterfly = GameObjectBee_ButterflyPtr(new GameObjectBee_Butterfly(tGameObjectBee_ButterflyParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectBee_Butterfly->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectBee_Butterfly,
			tGameObjectBee_ButterflyParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectBee_Butterfly->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentPositionalParameters));

		if(pGameObjectBee_Butterfly->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectBee_Butterfly->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectBee_ButterflyParameters.dreamsName,
				pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityDreamsParameters));

			//Create PhysicsComponent Dreams
			pGameObjectBee_Butterfly->setPhysicsComponentCharacterDreams(
				factory->createPhysicsComponentCharacter(
				pGameObjectBee_Butterfly, 
				tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterDreamsParameters, 
				pGameObjectBee_Butterfly->getRenderComponentPositional()));
		}
		if(pGameObjectBee_Butterfly->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectBee_Butterfly->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectBee_ButterflyParameters.nightmaresName,
				pGameObjectBee_Butterfly,tGameObjectBee_ButterflyParameters.tRenderComponentEntityNightmaresParameters));

			//Create PhysicsComponent Nightmares
			pGameObjectBee_Butterfly->setPhysicsComponentCharacterNightmares(
				factory->createPhysicsComponentCharacter(
				pGameObjectBee_Butterfly, 
				tGameObjectBee_ButterflyParameters.tPhysicsComponentCharacterNightmaresParameters, 
				pGameObjectBee_Butterfly->getRenderComponentPositional()));
		}



	//Add reference to this
	pGameObjectBee_Butterfly->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectBee_Butterfly(pGameObjectBee_Butterfly);
}

void GameWorldManager::createGameObjectBillboardSet(TGameObjectBillboardSetParameters tGameObjectBillboardSetParameters)
{
	GameObjectBillboardSetPtr pGameObjectBillboardSet;

	//Create GameObject
	pGameObjectBillboardSet = GameObjectBillboardSetPtr(new GameObjectBillboardSet(tGameObjectBillboardSetParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectBillboardSet->setLogicComponent(
			factory->createLogicComponent(
				pGameObjectBillboardSet,
				tGameObjectBillboardSetParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectBush(TGameObjectBushParameters tGameObjectBushParameters)
{
	GameObjectBushPtr pGameObjectBush;

	//Create GameObject
	pGameObjectBush = GameObjectBushPtr(new GameObjectBush(tGameObjectBushParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectBush->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectBush,
			tGameObjectBushParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectBush->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectBush,tGameObjectBushParameters.tRenderComponentPositionalParameters));

		if(pGameObjectBush->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectBush->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectBushParameters.dreamsName,
				pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectBush->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectBush->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectBushParameters.nightmaresName,
				pGameObjectBush,tGameObjectBushParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectBush->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
			pGameObjectBush, 
			tGameObjectBushParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectBush->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectBush->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectBush(pGameObjectBush);
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

void GameWorldManager::createGameObjectCarnivorousPlant(TGameObjectCarnivorousPlantParameters tGameObjectCarnivorousPlantParameters)
{
	GameObjectCarnivorousPlantPtr pGameObjectCarnivorousPlant;

	//Create GameObject
	pGameObjectCarnivorousPlant = GameObjectCarnivorousPlantPtr(new GameObjectCarnivorousPlant(tGameObjectCarnivorousPlantParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectCarnivorousPlant->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectCarnivorousPlant,
			tGameObjectCarnivorousPlantParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectCarnivorousPlant->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentPositionalParameters));

		if(pGameObjectCarnivorousPlant->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectCarnivorousPlant->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectCarnivorousPlantParameters.dreamsName,
				pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectCarnivorousPlant->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectCarnivorousPlant->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectCarnivorousPlantParameters.nightmaresName,
				pGameObjectCarnivorousPlant,tGameObjectCarnivorousPlantParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectCarnivorousPlant->setPhysicsComponentCharacter(
			factory->createPhysicsComponentCharacter(
			pGameObjectCarnivorousPlant, 
			tGameObjectCarnivorousPlantParameters.tPhysicsComponentCharacterParameters, 
			pGameObjectCarnivorousPlant->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectCarnivorousPlant->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectCarnivorousPlant(pGameObjectCarnivorousPlant);
}

void GameWorldManager::createGameObjectClockPiece(TGameObjectClockPieceParameters tGameObjectClockPieceParameters)
{
	GameObjectClockPiecePtr pGameObjectClockPiece;

	//Create GameObject
	pGameObjectClockPiece = GameObjectClockPiecePtr(new GameObjectClockPiece(tGameObjectClockPieceParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectClockPiece->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectClockPiece,
			tGameObjectClockPieceParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectClockPiece->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectClockPiece,tGameObjectClockPieceParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectClockPiece->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectClockPieceParameters.name,
			pGameObjectClockPiece,tGameObjectClockPieceParameters.tRenderComponentEntityParameters));
	
		//Create PhysicsComponent
		pGameObjectClockPiece->setPhysicsComponentVolumeBox(
			factory->createPhysicsComponentVolumeBox(
				pGameObjectClockPiece, 
				tGameObjectClockPieceParameters.tPhysicsComponentVolumeBoxParameters, 
				pGameObjectClockPiece->getRenderComponentPositional()));


	//Add reference to this
	pGameObjectClockPiece->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectClockPiece(pGameObjectClockPiece);
}

void GameWorldManager::createGameObjectCryKing(TGameObjectCryKingParameters tGameObjectCryKingParameters)
{
	GameObjectCryKingPtr pGameObjectCryKing;

	//Create GameObject
	pGameObjectCryKing = GameObjectCryKingPtr(new GameObjectCryKing(tGameObjectCryKingParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectCryKing->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectCryKing,
			tGameObjectCryKingParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectCryKing->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentPositionalParameters));

		if(pGameObjectCryKing->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectCryKing->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectCryKingParameters.dreamsName,
				pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectCryKing->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectCryKing->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectCryKingParameters.nightmaresName,
				pGameObjectCryKing,tGameObjectCryKingParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectCryKing->setPhysicsComponentCharacter(
			factory->createPhysicsComponentCharacter(
			pGameObjectCryKing, 
			tGameObjectCryKingParameters.tPhysicsComponentCharacterParameters, 
			pGameObjectCryKing->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectCryKing->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectCryKing(pGameObjectCryKing);
}

void GameWorldManager::createGameObjectDiamond(TGameObjectDiamondParameters tGameObjectDiamondParameters)
{
	GameObjectDiamondPtr pGameObjectDiamond;

	//Create GameObject
	pGameObjectDiamond = GameObjectDiamondPtr(new GameObjectDiamond(tGameObjectDiamondParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectDiamond->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectDiamond,
			tGameObjectDiamondParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectDiamond->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectDiamond,tGameObjectDiamondParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectDiamond->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectDiamondParameters.name,
			pGameObjectDiamond,tGameObjectDiamondParameters.tRenderComponentEntityParameters));
	
		//Create PhysicsComponent
		pGameObjectDiamond->setPhysicsComponentVolumeBox(
			factory->createPhysicsComponentVolumeBox(
				pGameObjectDiamond, 
				tGameObjectDiamondParameters.tPhysicsComponentVolumeBoxParameters, 
				pGameObjectDiamond->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDiamond->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectDiamond(pGameObjectDiamond);
}

void GameWorldManager::createGameObjectDiamondTree(TGameObjectDiamondTreeParameters tGameObjectDiamondTreeParameters)
{
	GameObjectDiamondTreePtr pGameObjectDiamondTree;

	//Create GameObject
	pGameObjectDiamondTree = GameObjectDiamondTreePtr(new GameObjectDiamondTree(tGameObjectDiamondTreeParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectDiamondTree->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectDiamondTree,
			tGameObjectDiamondTreeParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectDiamondTree->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentPositionalParameters));

		if(pGameObjectDiamondTree->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectDiamondTree->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectDiamondTreeParameters.dreamsName,
				pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectDiamondTree->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectDiamondTree->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectDiamondTreeParameters.nightmaresName,
				pGameObjectDiamondTree,tGameObjectDiamondTreeParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectDiamondTree->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
			pGameObjectDiamondTree, 
			tGameObjectDiamondTreeParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectDiamondTree->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDiamondTree->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectDiamondTree(pGameObjectDiamondTree);
}

void GameWorldManager::createGameObjectDoor(TGameObjectDoorParameters tGameObjectDoorParameters)
{
	GameObjectDoorPtr pGameObjectDoor;

	//Create GameObject
	pGameObjectDoor = GameObjectDoorPtr(new GameObjectDoor(tGameObjectDoorParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectDoor->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectDoor,
			tGameObjectDoorParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectDoor->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentPositionalParameters));

		if(pGameObjectDoor->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectDoor->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectDoorParameters.dreamsName,
				pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectDoor->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectDoor->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectDoorParameters.nightmaresName,
				pGameObjectDoor,tGameObjectDoorParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectDoor->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
			pGameObjectDoor, 
			tGameObjectDoorParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectDoor->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDoor->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectDoor(pGameObjectDoor);
}

void GameWorldManager::createGameObjectDragon(TGameObjectDragonParameters tGameObjectDragonParameters)
{
	GameObjectDragonPtr pGameObjectDragon;

	//Create GameObject
	pGameObjectDragon = GameObjectDragonPtr(new GameObjectDragon(tGameObjectDragonParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectDragon->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectDragon,
			tGameObjectDragonParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectDragon->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectDragon->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectDragonParameters.dreamsName,
			pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectDragon->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectDragonParameters.nightmaresName,
			pGameObjectDragon,tGameObjectDragonParameters.tRenderComponentEntityNightmaresParameters));
		
		//Create PhysicsComponent
		pGameObjectDragon->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectDragon,
			tGameObjectDragonParameters.tPhysicsComponentCharacterParameters,
			pGameObjectDragon->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectDragon->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectDragon(pGameObjectDragon);
}


void GameWorldManager::createGameObjectEye(TGameObjectEyeParameters tGameObjectEyeParameters)
{
	GameObjectEyePtr pGameObjectEye;

	//Create GameObject
	pGameObjectEye = GameObjectEyePtr(new GameObjectEye(tGameObjectEyeParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectEye->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectEye,
			tGameObjectEyeParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectFlashLight(TGameObjectFlashLightParameters tGameObjectFlashLightParameters)
{
	GameObjectFlashLightPtr pGameObjectFlashLight;

	//Create GameObject
	pGameObjectFlashLight = GameObjectFlashLightPtr(new GameObjectFlashLight(tGameObjectFlashLightParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectFlashLight->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectFlashLight,
			tGameObjectFlashLightParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectFlashLight->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectFlashLight,tGameObjectFlashLightParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectFlashLight->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectFlashLightParameters.name,
			pGameObjectFlashLight,tGameObjectFlashLightParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectFlashLight->setPhysicsComponentSimpleCapsule(
			factory->createPhysicsComponentSimpleCapsule(
			pGameObjectFlashLight, 
			tGameObjectFlashLightParameters.tPhysicsComponentSimpleCapsuleParameters, 
			pGameObjectFlashLight->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectFlashLight->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectFlashLight(pGameObjectFlashLight);
}

void GameWorldManager::createGameObjectItem1UP(TGameObjectItem1UPParameters tGameObjectItem1UPParameters)
{
	GameObjectItem1UPPtr pGameObjectItem1UP;

	//Create GameObject
	pGameObjectItem1UP = GameObjectItem1UPPtr(new GameObjectItem1UP(tGameObjectItem1UPParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponentWorldExistance
		pGameObjectItem1UP->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectItem1UP,
			tGameObjectItem1UPParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectItem1UP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItem1UP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItem1UPParameters.name,
			pGameObjectItem1UP,tGameObjectItem1UPParameters.tRenderComponentEntityParameters));
	
		//Create PhysicsComponent
		pGameObjectItem1UP->setPhysicsComponentVolumeBox(
			factory->createPhysicsComponentVolumeBox(
				pGameObjectItem1UP, 
				tGameObjectItem1UPParameters.tPhysicsComponentVolumeBoxParameters, 
				pGameObjectItem1UP->getRenderComponentPositional()));

	pGameObjectItem1UP->changeWorld(world);
	
	// Add a reference to this
	pGameObjectItem1UP->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectItem1UP(pGameObjectItem1UP);
}

void GameWorldManager::createGameObjectItemMaxHP(TGameObjectItemMaxHPParameters tGameObjectItemMaxHPParameters)
{
	GameObjectItemMaxHPPtr pGameObjectItemMaxHP;

	//Create GameObject
	pGameObjectItemMaxHP = GameObjectItemMaxHPPtr(new GameObjectItemMaxHP(tGameObjectItemMaxHPParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectItemMaxHP->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectItemMaxHP,
			tGameObjectItemMaxHPParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectItemMaxHP->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectItemMaxHP->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectItemMaxHPParameters.name,
			pGameObjectItemMaxHP,tGameObjectItemMaxHPParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectItemMaxHP->setPhysicsComponentVolumeBox(
			factory->createPhysicsComponentVolumeBox(
			pGameObjectItemMaxHP, 
			tGameObjectItemMaxHPParameters.tPhysicsComponentVolumeBoxParameters, 
			pGameObjectItemMaxHP->getRenderComponentPositional()));

		//Create LogicComponent
		pGameObjectItemMaxHP->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectItemMaxHP,
			tGameObjectItemMaxHPParameters.logicComponentParameters));

	pGameObjectItemMaxHP->changeWorld(world);

	// Add a reference to this
	pGameObjectItemMaxHP->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectItemMaxHP(pGameObjectItemMaxHP);
}

void GameWorldManager::createGameObjectLight(TGameObjectLightParameters tGameObjectLightParameters)
{
	GameObjectLightPtr pGameObjectLight;

	//Create GameObject
	pGameObjectLight = GameObjectLightPtr(new GameObjectLight(tGameObjectLightParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectLight->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectLight,
			tGameObjectLightParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectMagicClock(TGameObjectMagicClockParameters tGameObjectMagicClockParameters)
{
	GameObjectMagicClockPtr pGameObjectMagicClock;

	//Create GameObject
	pGameObjectMagicClock = GameObjectMagicClockPtr(new GameObjectMagicClock(tGameObjectMagicClockParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectMagicClock->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectMagicClock,
			tGameObjectMagicClockParameters.logicComponentParameters));

	//Add reference to this
	pGameObjectMagicClock->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectMagicClock(pGameObjectMagicClock);
}

void GameWorldManager::createGameObjectNightGoblin(TGameObjectNightGoblinParameters tGameObjectNightGoblinParameters)
{
	GameObjectNightGoblinPtr pGameObjectNightGoblin;

	//Create GameObject
	pGameObjectNightGoblin = GameObjectNightGoblinPtr(new GameObjectNightGoblin(tGameObjectNightGoblinParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectNightGoblin->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectNightGoblin,
			tGameObjectNightGoblinParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectNightGoblin->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectNightGoblin->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectNightGoblinParameters.dreamsName,
			pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectNightGoblin->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectNightGoblinParameters.nightmaresName,
			pGameObjectNightGoblin,tGameObjectNightGoblinParameters.tRenderComponentEntityNightmaresParameters));
		
		//Create PhysicsComponent
		pGameObjectNightGoblin->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectNightGoblin,
			tGameObjectNightGoblinParameters.tPhysicsComponentCharacterParameters,
			pGameObjectNightGoblin->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectNightGoblin->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectNightGoblin(pGameObjectNightGoblin);
}

void GameWorldManager::createGameObjectOny(TGameObjectOnyParameters tGameObjectOnyParameters)
{
	GameObjectOnyPtr pGameObjectOny;

	//Create GameObject
	pGameObjectOny = GameObjectOnyPtr(new GameObjectOny(tGameObjectOnyParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectOny->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectOny,
			tGameObjectOnyParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectParticleSystem(TGameObjectParticleSystemParameters tGameObjectParticleSystemParameters)
{
	GameObjectParticleSystemPtr pGameObjectParticleSystem;

	//Create GameObject
	pGameObjectParticleSystem = GameObjectParticleSystemPtr(new GameObjectParticleSystem(tGameObjectParticleSystemParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectParticleSystem->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectParticleSystem,
			tGameObjectParticleSystemParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectPillow(TGameObjectPillowParameters tGameObjectPillowParameters)
{
	GameObjectPillowPtr pGameObjectPillow;

	//Create GameObject
	pGameObjectPillow = GameObjectPillowPtr(new GameObjectPillow(tGameObjectPillowParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectPillow->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectPillow,
			tGameObjectPillowParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectPillow->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectPillow,tGameObjectPillowParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectPillow->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectPillowParameters.name,
			pGameObjectPillow,tGameObjectPillowParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectPillow->setPhysicsComponentSimpleCapsule(
			factory->createPhysicsComponentSimpleCapsule(
			pGameObjectPillow, 
			tGameObjectPillowParameters.tPhysicsComponentSimpleCapsuleParameters, 
			pGameObjectPillow->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectPillow->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectPillow(pGameObjectPillow);
}

void GameWorldManager::createGameObjectPlataform(TGameObjectPlataformParameters tGameObjectPlataformParameters)
{
	GameObjectPlataformPtr pGameObjectPlataform;

	//Create GameObject
	pGameObjectPlataform = GameObjectPlataformPtr(new GameObjectPlataform(tGameObjectPlataformParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectPlataform->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectPlataform,
			tGameObjectPlataformParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectPlataform->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentPositionalParameters));

		if(pGameObjectPlataform->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntityDreams
			pGameObjectPlataform->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectPlataformParameters.dreamsName,
				pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectPlataform->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntityNightmares
			pGameObjectPlataform->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectPlataformParameters.nightmaresName,
				pGameObjectPlataform,tGameObjectPlataformParameters.tRenderComponentEntityNightmaresParameters));
		}
		//Create PhysicsComponent
		pGameObjectPlataform->setPhysicsComponentComplexConvex(factory->createPhysicsComponentComplexConvex(
			pGameObjectPlataform,
			tGameObjectPlataformParameters.tPhysicsComponentComplexConvexParameters,
			pGameObjectPlataform->getRenderComponentPositional()));
	//Add reference to this
	pGameObjectPlataform->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectPlataform(pGameObjectPlataform);
}

void GameWorldManager::createGameObjectPortal(TGameObjectPortalParameters tGameObjectPortalParameters)
{
	GameObjectPortalPtr pGameObjectPortal;

	//Create GameObject
	pGameObjectPortal = GameObjectPortalPtr(new GameObjectPortal(tGameObjectPortalParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectPortal->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectPortal,
			tGameObjectPortalParameters.logicComponentParameters));

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


void GameWorldManager::createGameObjectProvisionalEntity(TGameObjectProvisionalEntityParameters tGameObjectProvisionalEntityParameters)
{
	GameObjectProvisionalEntityPtr pGameObjectProvisionalEntity;

	//Create GameObject
	pGameObjectProvisionalEntity = GameObjectProvisionalEntityPtr(new GameObjectProvisionalEntity(tGameObjectProvisionalEntityParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectProvisionalEntity->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectProvisionalEntity,
			tGameObjectProvisionalEntityParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectProvisionalEntity->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentPositionalParameters));

		if(pGameObjectProvisionalEntity->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectProvisionalEntity->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.dreamsName,
				pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectProvisionalEntity->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectProvisionalEntity->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectProvisionalEntityParameters.nightmaresName,
				pGameObjectProvisionalEntity,tGameObjectProvisionalEntityParameters.tRenderComponentEntityNightmaresParameters));
		}

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

void GameWorldManager::createGameObjectScaredPlant(TGameObjectScaredPlantParameters tGameObjectScaredPlantParameters)
{
	GameObjectScaredPlantPtr pGameObjectScaredPlant;

	//Create GameObject
	pGameObjectScaredPlant = GameObjectScaredPlantPtr(new GameObjectScaredPlant(tGameObjectScaredPlantParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectScaredPlant->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectScaredPlant,
			tGameObjectScaredPlantParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectScaredPlant->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectScaredPlant,tGameObjectScaredPlantParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectScaredPlant->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectScaredPlantParameters.name,
			pGameObjectScaredPlant,tGameObjectScaredPlantParameters.tRenderComponentEntityDreamsParameters));

		//Create PhysicsComponent
		pGameObjectScaredPlant->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectScaredPlant,
			tGameObjectScaredPlantParameters.tPhysicsComponentCharacterParameters,
			pGameObjectScaredPlant->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScaredPlant->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectScaredPlant(pGameObjectScaredPlant);
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

void GameWorldManager::createGameObjectScepter(TGameObjectScepterParameters tGameObjectScepterParameters)
{
	GameObjectScepterPtr pGameObjectScepter;

	//Create GameObject
	pGameObjectScepter = GameObjectScepterPtr(new GameObjectScepter(tGameObjectScepterParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectScepter->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectScepter,
			tGameObjectScepterParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectScepter->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectScepter,tGameObjectScepterParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity 
		pGameObjectScepter->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectScepterParameters.name,
			pGameObjectScepter,tGameObjectScepterParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectScepter->setPhysicsComponentSimpleCapsule(
			factory->createPhysicsComponentSimpleCapsule(
			pGameObjectScepter, 
			tGameObjectScepterParameters.tPhysicsComponentSimpleCapsuleParameters, 
			pGameObjectScepter->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectScepter->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectScepter(pGameObjectScepter);
}

void GameWorldManager::createGameObjectSnakeCreeper(TGameObjectSnakeCreeperParameters tGameObjectSnakeCreeperParameters)
{
	GameObjectSnakeCreeperPtr pGameObjectSnakeCreeper;

	//Create GameObject
	pGameObjectSnakeCreeper = GameObjectSnakeCreeperPtr(new GameObjectSnakeCreeper(tGameObjectSnakeCreeperParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectSnakeCreeper->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectSnakeCreeper,
			tGameObjectSnakeCreeperParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectSnakeCreeper->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentPositionalParameters));

		if(pGameObjectSnakeCreeper->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntity Dreams
			pGameObjectSnakeCreeper->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectSnakeCreeperParameters.dreamsName,
				pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectSnakeCreeper->getLogicComponent()->existsInNightmares())
		{
			//Create RenderComponentEntity Nightmares
			pGameObjectSnakeCreeper->setRenderComponentEntityNightmares(
				factory->createRenderComponentEntity(tGameObjectSnakeCreeperParameters.nightmaresName,
				pGameObjectSnakeCreeper,tGameObjectSnakeCreeperParameters.tRenderComponentEntityNightmaresParameters));
		}

		//Create PhysicsComponent
		pGameObjectSnakeCreeper->setPhysicsComponentCharacter(
			factory->createPhysicsComponentCharacter(
			pGameObjectSnakeCreeper, 
			tGameObjectSnakeCreeperParameters.tPhysicsComponentCharacterParameters, 
			pGameObjectSnakeCreeper->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectSnakeCreeper->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectSnakeCreeper(pGameObjectSnakeCreeper);
}

void GameWorldManager::createGameObjectStoryBook(TGameObjectStoryBookParameters tGameObjectStoryBookParameters)
{
	GameObjectStoryBookPtr pGameObjectStoryBook;

	//Create GameObject
	pGameObjectStoryBook = GameObjectStoryBookPtr(new GameObjectStoryBook(tGameObjectStoryBookParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectStoryBook->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectStoryBook,
			tGameObjectStoryBookParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectStoryBook->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectStoryBook,tGameObjectStoryBookParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectStoryBook->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectStoryBookParameters.name,
			pGameObjectStoryBook,tGameObjectStoryBookParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectStoryBook->setPhysicsComponentVolumeBox(
			factory->createPhysicsComponentVolumeBox(
			pGameObjectStoryBook, 
			tGameObjectStoryBookParameters.tPhysicsComponentVolumeBoxParameters, 
			pGameObjectStoryBook->getRenderComponentPositional()));

		//Create LogicComponent
		pGameObjectStoryBook->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectStoryBook,
			tGameObjectStoryBookParameters.logicComponentParameters));


	//Add reference to this
	pGameObjectStoryBook->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectStoryBook(pGameObjectStoryBook);
}

void GameWorldManager::createGameObjectTentetieso(TGameObjectTentetiesoParameters tGameObjectTentetiesoParameters)
{
	GameObjectTentetiesoPtr pGameObjectTentetieso;

	//Create GameObject
	pGameObjectTentetieso = GameObjectTentetiesoPtr(new GameObjectTentetieso(tGameObjectTentetiesoParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTentetieso->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTentetieso,
			tGameObjectTentetiesoParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTentetieso->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectTentetieso->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectTentetiesoParameters.dreamsName,
			pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectTentetieso->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectTentetiesoParameters.nightmaresName,
			pGameObjectTentetieso,tGameObjectTentetiesoParameters.tRenderComponentEntityNightmaresParameters));
		
		//Create PhysicsComponent
		pGameObjectTentetieso->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectTentetieso,
			tGameObjectTentetiesoParameters.tPhysicsComponentCharacterParameters,
			pGameObjectTentetieso->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTentetieso->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectTentetieso(pGameObjectTentetieso);
}

void GameWorldManager::createGameObjectTerrainConvex(TGameObjectTerrainConvexParameters tGameObjectTerrainConvexParameters)
{
	GameObjectTerrainConvexPtr pGameObjectTerrainConvex;

	//Create GameObject
	pGameObjectTerrainConvex = GameObjectTerrainConvexPtr(new GameObjectTerrainConvex(tGameObjectTerrainConvexParameters.name));
	
	//Create Game Components
	ComponentFactory * factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTerrainConvex->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTerrainConvex,
			tGameObjectTerrainConvexParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTerrainConvex->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentPositionalParameters));

		if(pGameObjectTerrainConvex->getLogicComponent()->existsInDreams())
		{
			//Create RenderComponentEntityDreams
			pGameObjectTerrainConvex->setRenderComponentEntityDreams(
				factory->createRenderComponentEntity(tGameObjectTerrainConvexParameters.dreamsName,
				pGameObjectTerrainConvex,tGameObjectTerrainConvexParameters.tRenderComponentEntityDreamsParameters));
		}
		if(pGameObjectTerrainConvex->getLogicComponent()->existsInNightmares())
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

		//Create LogicComponent
		pGameObjectTerrainTriangle->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTerrainTriangle,
			tGameObjectTerrainTriangleParameters.logicComponentParameters));

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

void GameWorldManager::createGameObjectTree(TGameObjectTreeParameters tGameObjectTreeParameters)
{
	GameObjectTreePtr pGameObjectTree;

	//Create GameObject
	pGameObjectTree = GameObjectTreePtr(new GameObjectTree(tGameObjectTreeParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTree->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTree,
			tGameObjectTreeParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTree->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTree,tGameObjectTreeParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTree->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectTreeParameters.name,
			pGameObjectTree,tGameObjectTreeParameters.tRenderComponentEntityParameters));

		//Create PhysicsComponent
		pGameObjectTree->setPhysicsComponentSimpleBox(
			factory->createPhysicsComponentSimpleBox(
			pGameObjectTree, 
			tGameObjectTreeParameters.tPhysicsComponentSimpleBoxParameters, 
			pGameObjectTree->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTree->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectTree(pGameObjectTree);
}

void GameWorldManager::createGameObjectTriggerBox(TGameObjectTriggerBoxParameters tGameObjectTriggerBoxParameters)
{
	GameObjectTriggerBoxPtr pGameObjectTriggerBox;

	//Create GameObject
	pGameObjectTriggerBox = GameObjectTriggerBoxPtr(new GameObjectTriggerBox(tGameObjectTriggerBoxParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTriggerBox->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTriggerBox,
			tGameObjectTriggerBoxParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTriggerBox->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTriggerBox,tGameObjectTriggerBoxParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTriggerBox->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectTriggerBoxParameters.name,
			pGameObjectTriggerBox,tGameObjectTriggerBoxParameters.tRenderComponentEntityParameters));

		//Make RenderComponentEntity not visible
		pGameObjectTriggerBox->getRenderComponentEntity()->setVisible(false);

		//Create PhysicsComponent
		pGameObjectTriggerBox->setPhysicsComponentVolumeBox(factory->createPhysicsComponentVolumeBox(
			pGameObjectTriggerBox,
			tGameObjectTriggerBoxParameters.tPhysicsComponentVolumeBoxParameters,
			pGameObjectTriggerBox->getRenderComponentPositional()));
	
	pGameObjectTriggerBox->changeWorld(world);

	// Add a reference to this
	pGameObjectTriggerBox->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectTriggerBox(pGameObjectTriggerBox);
}

void GameWorldManager::createGameObjectTriggerCapsule(TGameObjectTriggerCapsuleParameters tGameObjectTriggerCapsuleParameters)
{
	GameObjectTriggerCapsulePtr pGameObjectTriggerCapsule;

	//Create GameObject
	pGameObjectTriggerCapsule = GameObjectTriggerCapsulePtr(new GameObjectTriggerCapsule(tGameObjectTriggerCapsuleParameters.name));

	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTriggerCapsule->setLogicComponent(
			factory->createLogicComponent(
			pGameObjectTriggerCapsule,
			tGameObjectTriggerCapsuleParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTriggerCapsule->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTriggerCapsule,tGameObjectTriggerCapsuleParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntity
		pGameObjectTriggerCapsule->setRenderComponentEntity(
			factory->createRenderComponentEntity(tGameObjectTriggerCapsuleParameters.name,
			pGameObjectTriggerCapsule,tGameObjectTriggerCapsuleParameters.tRenderComponentEntityParameters));

		//Make RenderComponentEntity not visible
		pGameObjectTriggerCapsule->getRenderComponentEntity()->setVisible(false);

		//Create PhysicsComponent
		pGameObjectTriggerCapsule->setPhysicsComponentVolumeCapsule(factory->createPhysicsComponentVolumeCapsule(
			pGameObjectTriggerCapsule,
			tGameObjectTriggerCapsuleParameters.tPhysicsComponentVolumeCapsuleParameters,
			pGameObjectTriggerCapsule->getRenderComponentPositional()));
	
	pGameObjectTriggerCapsule->changeWorld(world);

	// Add a reference to this
	pGameObjectTriggerCapsule->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectTriggerCapsule(pGameObjectTriggerCapsule);
}

void GameWorldManager::createGameObjectTripollito(TGameObjectTripollitoParameters tGameObjectTripollitoParameters)
{
	GameObjectTripollitoPtr pGameObjectTripollito;

	//Create GameObject
	pGameObjectTripollito = GameObjectTripollitoPtr(new GameObjectTripollito(tGameObjectTripollitoParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTripollito->setLogicComponent(
			factory->createLogicComponent(pGameObjectTripollito,
			tGameObjectTripollitoParameters.logicComponentParameters));

		//Create RenderComponentPositional
		pGameObjectTripollito->setRenderComponentPositional(factory->createRenderComponentPositional(
			pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentPositionalParameters));

		//Create RenderComponentEntityDreams
		pGameObjectTripollito->setRenderComponentEntityDreams(
			factory->createRenderComponentEntity(tGameObjectTripollitoParameters.dreamsName,
			pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentEntityDreamsParameters));

		//Create RenderComponentEntityNightmares
		pGameObjectTripollito->setRenderComponentEntityNightmares(
			factory->createRenderComponentEntity(tGameObjectTripollitoParameters.nightmaresName,
			pGameObjectTripollito,tGameObjectTripollitoParameters.tRenderComponentEntityNightmaresParameters));

		//Create PhysicsComponent
		pGameObjectTripollito->setPhysicsComponentCharacter(factory->createPhysicsComponentCharacter(
			pGameObjectTripollito,
			tGameObjectTripollitoParameters.tPhysicsComponentCharacterParameters,
			pGameObjectTripollito->getRenderComponentPositional()));

	//Add reference to this
	pGameObjectTripollito->setGameWorldManager(mThis);

	//Add Object to GameWorldManager
	addGameObjectTripollito(pGameObjectTripollito);
}

void GameWorldManager::createGameObjectTripollo(TGameObjectTripolloParameters tGameObjectTripolloParameters)
{
	GameObjectTripolloPtr pGameObjectTripollo;

	//Create GameObject
	pGameObjectTripollo = GameObjectTripolloPtr(new GameObjectTripollo(tGameObjectTripolloParameters.name));
	
	//Create Game Components
	ComponentFactory* factory=ComponentFactory::getInstance();

		//Create LogicComponent
		pGameObjectTripollo->setLogicComponent(
			factory->createLogicComponent(pGameObjectTripollo,
			tGameObjectTripolloParameters.logicComponentParameters));

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

bool GameWorldManager::isGameBeaten() const
{
	return mGameBeaten;
}
void GameWorldManager::setGameBeaten(bool gameBeaten)
{
	mGameBeaten=gameBeaten;
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
ApplicationPtr GameWorldManager::getParent()
{
	return mApp;
}