#include "OUAN_Precompiled.h"

#include "GameWorldManager.h"
#include "../Application.h"
#include "../Loader/LevelLoader.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectBee_Butterfly.h"
#include "GameObject/GameObjectBillboardSet.h"
#include "GameObject/GameObjectTraspasable.h"
#include "GameObject/GameObjectCarnivorousPlant.h"
#include "GameObject/GameObjectClockPiece.h"
#include "GameObject/GameObjectCloud.h"
#include "GameObject/GameObjectCryKing.h"
#include "GameObject/GameObjectDiamond.h"
#include "GameObject/GameObjectDiamondTree.h"
#include "GameObject/GameObjectDoor.h"
#include "GameObject/GameObjectInvisibleWall.h"
#include "GameObject/GameObjectNonGrassArea.h"
#include "GameObject/GameObjectBreakableRock.h"
#include "GameObject/GameObjectBoss.h"
#include "GameObject/GameObjectEye.h"
#include "GameObject/GameObjectFlashLight.h"
#include "GameObject/GameObjectHeart.h"
#include "GameObject/GameObjectItem1UP.h"
#include "GameObject/GameObjectItemMaxHP.h"
#include "GameObject/GameObjectLight.h"
#include "GameObject/GameObjectMagicClock.h"
#include "GameObject/GameObjectNest.h"
#include "GameObject/GameObjectNightGoblin.h"
#include "GameObject/GameObjectOny.h"
#include "GameObject/GameObjectParticleSystem.h"
#include "GameObject/GameObjectPillow.h"
#include "GameObject/GameObjectPlane.h"
#include "GameObject/GameObjectPlataform.h"
#include "GameObject/GameObjectPortal.h"
#include "GameObject/GameObjectProvisionalEntity.h"
#include "GameObject/GameObjectScaredPlant.h"
#include "GameObject/GameObjectScene.h"
#include "GameObject/GameObjectScepter.h"
#include "GameObject/GameObjectSignpost.h"
#include "GameObject/GameObjectSkyBody.h"
#include "GameObject/GameObjectSnakeCreeper.h"
#include "GameObject/GameObjectSound.h"
#include "GameObject/GameObjectStoryBook.h"
#include "GameObject/GameObjectTentetieso.h"
#include "GameObject/GameObjectTerrainConvex.h"
#include "GameObject/GameObjectTerrainTriangle.h"
#include "GameObject/GameObjectTree.h"
#include "GameObject/GameObjectTriggerBox.h"
#include "GameObject/GameObjectTriggerCapsule.h"
#include "GameObject/GameObjectTripollo.h"
#include "GameObject/GameObjectViewport.h"
#include "GameObject/GameObjectWoodBox.h"
#include "GameObject/GameObjectWater.h"
#include "GameObject/GameObjectTreeComplex.h"
#include "GameObject/GameObjectTower.h"
#include "GameObject/GameObjectFog.h"
#include "GameObject/GameObjectCameraTrigger.h"
#include "GameObject/GameObjectSwitch.h"
#include "GameObject/GameObjectBomb.h"
#include "GameObject/GameObjectTotem.h"
#include "GameObject/GameObjectLevelEntrance.h"
#include "GameObject/GameObjectBridge.h"

#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Graphics/CameraManager/CameraParameters.h"
#include "../Graphics/ParticleManager/ParticleTemplates.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
#include "../Graphics/TrajectoryManager/WalkabilityMap.h"
#include "../Event/EventManager.h"
#include "../Event/EventProcessor.h"

#include "../Audio/AudioComponent/AudioComponent.h"

#include "../Core/GameStateManager.h"
#include "../Core/GameRunningState.h"

using namespace OUAN;

bool nestChildrenSortPredicate(GameObjectPtr obj1, GameObjectPtr obj2)
{
	return obj1->getSpawnProbability()<obj2->getSpawnProbability();
}

GameWorldManager* GameWorldManager::mInst=NULL;

GameWorldManager::GameWorldManager()
{
	mWorld=DREAMS;
	level=LEVEL_NONE;
	mInst=this;
	mGodMode=false;
	ParticleTemplates::getInstance()->loadConfig();

	mChangeWorldElapsedTime=0;
	mIsChangingWorld=false;

	mDefaultAmbientSound="sound#1";
	mDefaultAmbientSoundIDDreams="birds_chirp";
	mDefaultAmbientSoundIDNightmares="scary";

	mInitialized=false;
}

GameWorldManager::~GameWorldManager()
{
	mInst=NULL;
}

void GameWorldManager::update(double elapsedSeconds)
{
	TGameObjectContainerIterator it;

	dispatchEvents();

	for(it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		//Logger::getInstance()->log("Updating game object " + it->second->getName());
		it->second->update(elapsedSeconds);
	}

	dispatchEvents();

	if(mIsChangingWorld)
	{
		//Logger::getInstance()->log("Updating gameworldmanager " + Ogre::StringConverter::toString(Ogre::Real(mChangeWorldElapsedTime)));
		mChangeWorldElapsedTime+=elapsedSeconds;
		if(mChangeWorldElapsedTime>=mChangeWorldTotalTime)
		{
			changeToWorld(mWorld,1.0f);
			changeWorldFinished(mWorld);
			mIsChangingWorld=false;
			mApp->setWorld(mWorld);
		}
		else
		{
			changeToWorld(mWorld,mChangeWorldElapsedTime/mChangeWorldTotalTime);
		}
	}

	dispatchEvents();
}

void GameWorldManager::setGodMode(bool activated)
{
	mGodMode=activated;
}

bool GameWorldManager::isGodMode()
{
	return mGodMode;
}

GameObjectPtr GameWorldManager::getObject(const std::string& objectId)
{
	if(!mGameObjects.empty() && mGameObjects.count(objectId)>0){
		return mGameObjects[objectId];
	}

	return GameObjectPtr();
}

TGameObjectContainer * GameWorldManager::getAllGameObjects()
{
	return &mGameObjects;
}

TGameObjectMovableContainer * GameWorldManager::getGameObjectMovableContainer()
{
	return &mGameObjectMovableContainer;
}

TGameObjectMovableEntityContainer * GameWorldManager::getGameObjectMovableEntityContainer()
{
	return &mGameObjectMovableEntityContainer;
}

TGameObjectNonMovableContainer * GameWorldManager::getGameObjectNonMovableContainer()
{
	return &mGameObjectNonMovableContainer;
}

TGameObjectNonMovableEntityContainer * GameWorldManager::getGameObjectNonMovableEntityContainer()
{
	return &mGameObjectNonMovableEntityContainer;
}

TGameObjectOnyContainer * GameWorldManager::getGameObjectOnyContainer()
{
	return &mGameObjectOnyContainer;
}

TGameObjectPositionalContainer * GameWorldManager::getGameObjectPositionalContainer()
{
	return &mGameObjectPositionalContainer;
}

TGameObjectSceneContainer * GameWorldManager::getGameObjectSceneContainer()
{
	return &mGameObjectSceneContainer;
}

TGameObjectTripolloContainer * GameWorldManager::getGameObjectTripolloContainer()
{
	return &mGameObjectTripolloContainer;
}

TGameObjectTentetiesoContainer * GameWorldManager::getGameObjectTentetiesoContainer()
{
	return &mGameObjectTentetiesoContainer;
}

TGameObjectEyeContainer * GameWorldManager::getGameObjectEyeContainer()
{
	return &mGameObjectEyeContainer;

}
TGameObjectSnakeCreeperContainer * GameWorldManager::getGameObjectSnakeCreeperContainer()
{
	return &mGameObjectSnakeCreeperContainer;
}
TGameObjectSoundContainer* GameWorldManager::getGameObjectSoundContainer()
{
	return &mGameObjectSoundContainer;
}
TGameObjectContainer* GameWorldManager::getAmbientSoundContainer()
{
	return &mAmbientSoundContainer;
}
TGameObjectScaredPlantContainer * GameWorldManager::getGameObjectScaredPlantContainer()
{
	return &mGameObjectScaredPlantContainer;
}
TGameObjectBee_ButterflyContainer * GameWorldManager::getGameObjectBeeButterflyContainer()
{
	return &mGameObjectBeeButterflyContainer;
}
TGameObjectCarnivorousPlantContainer * GameWorldManager::getGameObjectCarnivorousPlantContainer()
{
	return &mGameObjectCarnivorousPlantContainer;
}
TGameObjectTerrainConvexContainer * GameWorldManager::getGameObjectTerrainConvexContainer()
{
	return &mGameObjectTerrainConvexContainer;
}
TGameObjectTerrainTriangleContainer * GameWorldManager::getGameObjectTerrainTriangleContainer()
{
	return &mGameObjectTerrainTriangleContainer;
}

TGameObjectBillboardSetContainer * GameWorldManager::getGameObjectBillboardSetContainer()
{
	return &mGameObjectBillboardSetContainer;
}

TGameObjectParticleSystemContainer * GameWorldManager::getGameObjectParticleSystemContainer()
{
	return &mGameObjectParticleSystemContainer;
}

TGameObjectPortalContainer * GameWorldManager::getGameObjectPortalContainer()
{
	return &mGameObjectPortalContainer;
}

TGameObjectViewportContainer * GameWorldManager::getGameObjectViewportContainer()
{
	return &mGameObjectViewportContainer;
}

TGameObjectTriggerBoxContainer * GameWorldManager::getGameObjectTriggerBoxContainer()
{
	return &mGameObjectTriggerBoxContainer;
}

TGameObjectTriggerCapsuleContainer * GameWorldManager::getGameObjectTriggerCapsuleContainer()
{
	return &mGameObjectTriggerCapsuleContainer;
}

TGameObjectPhysicsContainer * GameWorldManager::getGameObjectPhysicsContainer()
{
	return &mGameObjectPhysicsContainer;
}

TGameObjectPhysicsCharacterContainer * GameWorldManager::getGameObjectPhysicsCharacterContainer()
{
	return &mGameObjectPhysicsCharacterContainer;
}

TGameObjectPhysicsComplexContainer * GameWorldManager::getGameObjectPhysicsComplexContainer()
{
	return &mGameObjectPhysicsComplexContainer;
}

TGameObjectPhysicsComplexConvexContainer * GameWorldManager::getGameObjectPhysicsComplexConvexContainer()
{
	return &mGameObjectPhysicsComplexConvexContainer;
}

TGameObjectPhysicsComplexTriangleContainer * GameWorldManager::getGameObjectPhysicsComplexTriangleContainer()
{
	return &mGameObjectPhysicsComplexTriangleContainer;
}

TGameObjectPhysicsSimpleContainer * GameWorldManager::getGameObjectPhysicsSimpleContainer()
{
	return &mGameObjectPhysicsSimpleContainer;
}

TGameObjectPhysicsSimpleBoxContainer * GameWorldManager::getGameObjectPhysicsSimpleBoxContainer()
{
	return &mGameObjectPhysicsSimpleBoxContainer;
}

TGameObjectPhysicsSimpleCapsuleContainer * GameWorldManager::getGameObjectPhysicsSimpleCapsuleContainer()
{
	return &mGameObjectPhysicsSimpleCapsuleContainer;
}

TGameObjectPhysicsVolumeContainer * GameWorldManager::getGameObjectPhysicsVolumeContainer()
{
	return &mGameObjectPhysicsVolumeContainer;
}

TGameObjectPhysicsVolumeBoxContainer * GameWorldManager::getGameObjectPhysicsVolumeBoxContainer()
{
	return &mGameObjectPhysicsVolumeBoxContainer;
}

TGameObjectPhysicsVolumeCapsuleContainer * GameWorldManager::getGameObjectPhysicsVolumeCapsuleContainer()
{
	return &mGameObjectPhysicsVolumeCapsuleContainer;
}

TGameObjectLogicContainer * GameWorldManager::getGameObjectLogicContainer()
{
	return &mGameObjectLogicContainer;
}
TGameObjectUsableContainer * GameWorldManager::getGameObjectUsableContainer()
{
	return &mGameObjectUsableContainer;
}
TGameObjectDiamondContainer * GameWorldManager::getGameObjectDiamondContainer()
{
	return &mGameObjectDiamondContainer;
}
TGameObjectDiamondTreeContainer * GameWorldManager::getGameObjectDiamondTreeContainer()
{
	return &mGameObjectDiamondTreeContainer;
}

TGameObjectSignpostContainer* GameWorldManager::getGameObjectSignpostContainer()
{
	return &mGameObjectSignPostContainer;
}
TGameObjectNestContainer* GameWorldManager::getGameObjectNestContainer()
{
	return &mGameObjectNestContainer;
}
void GameWorldManager::clearContainers()
{
	EMPTY_MAP(TGameObjectContainer,mGameObjects);
	EMPTY_VECTOR(TGameObjectMovableContainer,mGameObjectMovableContainer);
	EMPTY_VECTOR(TGameObjectMovableEntityContainer,mGameObjectMovableEntityContainer);
	EMPTY_VECTOR(TGameObjectNonMovableContainer,mGameObjectNonMovableContainer);
	EMPTY_VECTOR(TGameObjectNonMovableEntityContainer,mGameObjectNonMovableEntityContainer);
	EMPTY_VECTOR(TGameObjectLightContainer,mGameObjectLightContainer);
	
	EMPTY_VECTOR(TGameObjectParticleSystemContainer,mGameObjectParticleSystemContainer);
	EMPTY_VECTOR(TGameObjectBillboardSetContainer,mGameObjectBillboardSetContainer);
	EMPTY_VECTOR(TGameObjectTerrainConvexContainer,mGameObjectTerrainConvexContainer);
	EMPTY_VECTOR(TGameObjectTerrainTriangleContainer,mGameObjectTerrainTriangleContainer);

	EMPTY_VECTOR(TGameObjectOnyContainer,mGameObjectOnyContainer);
	EMPTY_VECTOR(TGameObjectPositionalContainer,mGameObjectPositionalContainer);
	EMPTY_VECTOR(TGameObjectSceneContainer,mGameObjectSceneContainer);

	EMPTY_VECTOR(TGameObjectTripolloContainer,mGameObjectTripolloContainer);
	EMPTY_VECTOR(TGameObjectEyeContainer,mGameObjectEyeContainer);
	EMPTY_VECTOR(TGameObjectTriggerBoxContainer,mGameObjectTriggerBoxContainer);
	EMPTY_VECTOR(TGameObjectTriggerCapsuleContainer,mGameObjectTriggerCapsuleContainer);
	EMPTY_VECTOR(TGameObjectBee_ButterflyContainer,mGameObjectBeeButterflyContainer);
	EMPTY_VECTOR(TGameObjectCarnivorousPlantContainer,mGameObjectCarnivorousPlantContainer);
	EMPTY_VECTOR(TGameObjectSnakeCreeperContainer,mGameObjectSnakeCreeperContainer);
	EMPTY_VECTOR(TGameObjectSoundContainer, mGameObjectSoundContainer);
	EMPTY_MAP(TGameObjectContainer, mAmbientSoundContainer);
	EMPTY_VECTOR(TGameObjectTentetiesoContainer,mGameObjectTentetiesoContainer);
	EMPTY_VECTOR(TGameObjectScaredPlantContainer,mGameObjectScaredPlantContainer);

	EMPTY_VECTOR(TGameObjectPortalContainer, mGameObjectPortalContainer);

	EMPTY_VECTOR(TGameObjectPhysicsCharacterContainer,mGameObjectPhysicsCharacterContainer);
	EMPTY_VECTOR(TGameObjectPhysicsComplexConvexContainer,mGameObjectPhysicsComplexConvexContainer);
	EMPTY_VECTOR(TGameObjectPhysicsComplexTriangleContainer,mGameObjectPhysicsComplexTriangleContainer);
	EMPTY_VECTOR(TGameObjectPhysicsSimpleContainer,mGameObjectPhysicsSimpleContainer);
	EMPTY_VECTOR(TGameObjectPhysicsVolumeContainer,mGameObjectPhysicsVolumeContainer);

	EMPTY_VECTOR(TGameObjectUsableContainer,mGameObjectUsableContainer);
	EMPTY_VECTOR(TGameObjectLogicContainer,mGameObjectLogicContainer);

	EMPTY_VECTOR(TGameObjectDiamondTreeContainer, mGameObjectDiamondTreeContainer);
	EMPTY_VECTOR(TGameObjectDiamondContainer, mGameObjectDiamondContainer);

	EMPTY_VECTOR(TGameObjectFlashLightContainer,mGameObjectFlashLightContainer);
	EMPTY_VECTOR(TGameObjectSignpostContainer, mGameObjectSignPostContainer);
	EMPTY_VECTOR(TGameObjectNestContainer, mGameObjectNestContainer);

	mNestLinks.clear();
	mGameObjectPillow.reset();
}
void GameWorldManager::initGame()
{
	mWorld=DREAMS;
	GameWorldManager::setCheckPointLUA(LEVEL_START_CHECKPOINT,0);
	mExecutedLevelEventsPermanent.clear();
	resetAll();
	Logger::getInstance()->log("[GAME WORLD MANAGER LEVEL LOAD FINISHED]");
}

void GameWorldManager::unloadLevel()
{
	Logger::getInstance()->log("[GAME WORLD MANAGER LEVEL UNLOAD STARTED]");
	
	GameObjectSoundPtr sound = BOOST_PTR_CAST(GameObjectSound,	
		mAmbientSoundContainer[mDefaultAmbientSound]);
	if (sound.get())
	{
		sound->getAudioComponentNightmares()->stopSound(mDefaultAmbientSoundIDNightmares);
		sound->getAudioComponentDreams()->stopSound(mDefaultAmbientSoundIDDreams);
	}
	try
	{
		mApp->getPhysicsSubsystem()->clear();
	}
	catch (const std::exception& e)
	{
		Logger::getInstance()->log(e.what());
	}
	mApp->getRenderSubsystem()->clear();
	mApp->getTrajectoryManager()->clear();

	TGameObjectContainerIterator it;
	TGameObjectContainer * container = Application::getInstance()->getGameWorldManager()->getAllGameObjects();

	for(it = container->begin(); it != container->end(); it++)
	{
		it->second.get()->~GameObject();
	}

	mApp->getCameraManager()->clear();

	clearContainers();
	Logger::getInstance()->log("[GAME WORLD MANAGER LEVEL UNLOAD FINISHED]");
}

bool GameWorldManager::loadConfig()
{
	Configuration config;
	std::string value;
	bool success;

	if (config.loadFromFile(GAMEWORLDMANAGER_CFG))
	{
		config.getOption("CHANGE_WORLD_TIME", value); 
		mChangeWorldTotalTime = atof(value.c_str());

		config.getOption("CHANGE_WORLD_TREES_RANDOM", value); 
		mRandomChangeWorld= Ogre::StringConverter::parseBool(value);

		config.getOption("CHANGE_WORLD_RADIUM", value); 
		CHANGE_WORLD_RADIUM= atof(value.c_str());

		config.getOption("DEFAULT_TRAJECTORY_SPEED", value); 
		DEFAULT_TRAJECTORY_SPEED= atof(value.c_str());
		success = true;

		config.getOption("DEFAULT_MAX_UPDATE_RADIO_UPPER_LIMIT", value); 
		DEFAULT_MAX_UPDATE_RADIO_UPPER_LIMIT= atof(value.c_str());
		Logger::getInstance()->log("DEFAULT_MAX_UPDATE_RADIO_UPPER_LIMIT " + Ogre::StringConverter::toString(Ogre::Real(DEFAULT_MAX_UPDATE_RADIO_UPPER_LIMIT)));

		config.getOption("DEFAULT_MAX_UPDATE_RADIO", value); 
		DEFAULT_MAX_UPDATE_RADIO= atof(value.c_str());
		Logger::getInstance()->log("DEFAULT_MAX_UPDATE_RADIO " + Ogre::StringConverter::toString(Ogre::Real(DEFAULT_MAX_UPDATE_RADIO)));
		
		config.getOption("DEFAULT_MAX_RENDER_RADIO", value); 
		DEFAULT_MAX_RENDER_RADIO= atof(value.c_str());
		Logger::getInstance()->log("DEFAULT_MAX_RENDER_RADIO " + Ogre::StringConverter::toString(Ogre::Real(DEFAULT_MAX_RENDER_RADIO)));

		config.getOption("CHANGE_FLASHLIGHT_COLOUR_SPEED", value); 
		CHANGE_FLASHLIGHT_COLOUR_SPEED= atof(value.c_str());

		config.getOption("CHANGEWORLD_CAMERA_DISTANCE", value); 
		CHANGEWORLD_CAMERA_DISTANCE= atof(value.c_str());
	} 
	else 
	{
		Logger::getInstance()->log(CAMERA_CFG + " COULD NOT BE LOADED!");
		success = false;
	}

	return success;
}

/// init object
void GameWorldManager::init(ApplicationPtr app)
{
	Logger::getInstance()->log("[GAME WORLD MANAGER GENERAL INIT STARTED]");
	mWorld=DREAMS;
	mGameOver=false;
	mApp=app;

	mChangeWorldElapsedTime=0;
	mIsChangingWorld=false;

	clearContainers();
	mThis=shared_from_this();
	mEventManager.reset(new EventManager());
	mEventProcessor.reset(new EventProcessor());
	mEventProcessor->init(mThis);

	loadConfig();

	//landscape.reset() | landscape->initBlank() | ...
	Logger::getInstance()->log("[GAME WORLD MANAGER GENERAL INIT FINISHED]");

	mFirstMsgBox=true;
	mFirstSignpostHit=true;
}

std::string GameWorldManager::getLevelName()
{
	return level;
}


void GameWorldManager::cleanUp()
{
	Logger::getInstance()->log("[GAME WORLD MANAGER GENERAL CLEANUP STARTED]");

	// Careful with how game objects
	// (well, their components)
	// will free their resources!!
	mEventManager->clear();
	clearContainers();
	mEventProcessor->cleanUp();	

	Logger::getInstance()->log("[GAME WORLD MANAGER GENERAL CLEANUP FINISHED]");
}

void GameWorldManager::resetAll()
{
	mInitialized=false;

	Logger::getInstance()->log("[GAME WORLD MANAGER RESET ALL STARTED]");

	mEventManager->clearEvents();

	TGameObjectContainerIterator it;

	for(it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		//Logger::getInstance()->log("Reseting game object " + it->second->getName());
		it->second->reset();
	}

	if (getGameObjectOny().get())
	{
		getGameObjectOny()->setInitialWeaponComponent(mWorld);
	}

	mGameOver=false;
	mGameBeaten=false;

	getGameObjectPillow()->setParentWeaponComponent(getGameObjectOny()->getWeaponComponent());
	getGameObjectFlashLight()->setParentWeaponComponent(getGameObjectOny()->getWeaponComponent());

	GameObjectSoundPtr sound = BOOST_PTR_CAST(GameObjectSound,
		mAmbientSoundContainer[mDefaultAmbientSound]);
	if (sound.get())
	{
		sound->getAudioComponentNightmares()->playSound(mDefaultAmbientSoundIDNightmares);
		sound->getAudioComponentNightmares()->setPauseSound(mDefaultAmbientSoundIDNightmares,true);
		sound->getAudioComponentDreams()->playSound(mDefaultAmbientSoundIDDreams);
		sound->getAudioComponentNightmares()->setPauseSound(mDefaultAmbientSoundIDNightmares,false);
	}
	//stabilize world
	mApp->getPhysicsSubsystem()->stabilize();
	dispatchEvents();

	//set world
	setChangeWorldTimes();
	setWorld(mCheckPointWorld);
	dispatchEvents();

	mApp->getCameraManager()->setDefaultThirdPersonCamera(false);

	mFirstMsgBox=true;
	mFirstSignpostHit=true;

	mExecutedLevelEvents.clear();

	mInitialized=true;

	Logger::getInstance()->log("[GAME WORLD MANAGER RESET ALL FINISHED]");
}

bool GameWorldManager::isInitialized()
{
	return mInitialized;
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
	mGameObjectBeeButterflyContainer.push_back(gameObjectBee_Butterfly);
	mGameObjectLogicContainer.push_back(gameObjectBee_Butterfly);
}

void GameWorldManager::addGameObjectBillboardSet(GameObjectBillboardSetPtr pGameObjectBillboardSet)
{
	mGameObjects[pGameObjectBillboardSet->getName()]=pGameObjectBillboardSet;

	mGameObjectPositionalContainer.push_back(pGameObjectBillboardSet);
	mGameObjectNonMovableContainer.push_back(pGameObjectBillboardSet);
	mGameObjectBillboardSetContainer.push_back(pGameObjectBillboardSet);
}

void GameWorldManager::addGameObjectBridge(GameObjectBridgePtr gameObjectBridge)
{
	mGameObjects[gameObjectBridge->getName()]=gameObjectBridge;
}


void GameWorldManager::addGameObjectTraspasable(GameObjectTraspasablePtr gameObjectTraspasable)
{
	mGameObjects[gameObjectTraspasable->getName()]=gameObjectTraspasable;
}

void GameWorldManager::addGameObjectCarnivorousPlant(GameObjectCarnivorousPlantPtr gameObjectCarnivorousPlant)
{
	mGameObjects[gameObjectCarnivorousPlant->getName()]=gameObjectCarnivorousPlant;
	mGameObjectCarnivorousPlantContainer.push_back(gameObjectCarnivorousPlant);
	mGameObjectLogicContainer.push_back(gameObjectCarnivorousPlant);
}

void GameWorldManager::addGameObjectClockPiece(GameObjectClockPiecePtr pGameObjectClockPiece)
{
	mGameObjects[pGameObjectClockPiece->getName()]=pGameObjectClockPiece;

	mGameObjectPositionalContainer.push_back(pGameObjectClockPiece);
	mGameObjectNonMovableContainer.push_back(pGameObjectClockPiece);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectClockPiece);

	mGameObjectPhysicsContainer.push_back(pGameObjectClockPiece);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectClockPiece);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectClockPiece);
}

void GameWorldManager::addGameObjectCloud(GameObjectCloudPtr gameObjectCloud)
{
	mGameObjects[gameObjectCloud->getName()]=gameObjectCloud;
}

void GameWorldManager::addGameObjectCryKing(GameObjectCryKingPtr gameObjectCryKing)
{
	mGameObjects[gameObjectCryKing->getName()]=gameObjectCryKing;
}

void GameWorldManager::addGameObjectDiamond(GameObjectDiamondPtr pGameObjectDiamond)
{
	mGameObjects[pGameObjectDiamond->getName()]=pGameObjectDiamond;

	mGameObjectPositionalContainer.push_back(pGameObjectDiamond);
	mGameObjectNonMovableContainer.push_back(pGameObjectDiamond);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectDiamond);

	mGameObjectPhysicsContainer.push_back(pGameObjectDiamond);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectDiamond);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectDiamond);

	mGameObjectDiamondContainer.push_back(pGameObjectDiamond);
}

void GameWorldManager::addGameObjectDiamondTree(GameObjectDiamondTreePtr gameObjectDiamondTree)
{
	mGameObjects[gameObjectDiamondTree->getName()]=gameObjectDiamondTree;
	mGameObjectDiamondTreeContainer.push_back(gameObjectDiamondTree);
	mGameObjectPhysicsContainer.push_back(gameObjectDiamondTree);
	mGameObjectPhysicsCharacterContainer.push_back(gameObjectDiamondTree);
}

void GameWorldManager::addGameObjectDoor(GameObjectDoorPtr gameObjectDoor)
{
	mGameObjects[gameObjectDoor->getName()]=gameObjectDoor;
}
void GameWorldManager::addGameObjectBreakableRock(GameObjectBreakableRockPtr gameObjectBreakableRock)
{
	mGameObjects[gameObjectBreakableRock->getName()]=gameObjectBreakableRock;
}

void GameWorldManager::addGameObjectInvisibleWall(GameObjectInvisibleWallPtr gameObjectInvisibleWall)
{
	mGameObjects[gameObjectInvisibleWall->getName()]=gameObjectInvisibleWall;
}

void GameWorldManager::addGameObjectNonGrassArea(GameObjectNonGrassAreaPtr gameObjectNonGrassArea)
{
	mGameObjects[gameObjectNonGrassArea->getName()]=gameObjectNonGrassArea;
}

void GameWorldManager::addGameObjectBoss(GameObjectBossPtr gameObjectBoss)
{
	mGameObjects[gameObjectBoss->getName()]=gameObjectBoss;
	mGameObjectLogicContainer.push_back(gameObjectBoss);
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
	mGameObjectLogicContainer.push_back(pGameObjectEye);
}

void GameWorldManager::addGameObjectFlashLight(GameObjectFlashLightPtr gameObjectFlashLight)
{
	mGameObjects[gameObjectFlashLight->getName()]=gameObjectFlashLight;

	mGameObjectFlashLightContainer.push_back(gameObjectFlashLight);
}

void GameWorldManager::addGameObjectHeart(GameObjectHeartPtr pGameObjectHeart)
{
	mGameObjects[pGameObjectHeart->getName()]=pGameObjectHeart;

	mGameObjectPositionalContainer.push_back(pGameObjectHeart);
	mGameObjectNonMovableContainer.push_back(pGameObjectHeart);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectHeart);

	mGameObjectPhysicsContainer.push_back(pGameObjectHeart);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectHeart);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectHeart);
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
void GameWorldManager::addGameObjectNest(GameObjectNestPtr gameObjectNest)
{
	mGameObjects[gameObjectNest->getName()]=gameObjectNest;
	mGameObjectNestContainer.push_back(gameObjectNest);
	mGameObjectPositionalContainer.push_back(gameObjectNest);
	mGameObjectNonMovableContainer.push_back(gameObjectNest);
	mGameObjectNonMovableEntityContainer.push_back(gameObjectNest);

	mGameObjectPhysicsContainer.push_back(gameObjectNest);
	mGameObjectPhysicsCharacterContainer.push_back(gameObjectNest);
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
	mGameObjectPillow=gameObjectPillow;
}

void GameWorldManager::addGameObjectPlane(GameObjectPlanePtr gameObjectPlane)
{
	mGameObjects[gameObjectPlane->getName()]=gameObjectPlane;
}


void GameWorldManager::addGameObjectPlataform(GameObjectPlataformPtr pGameObjectPlataform)
{
	mGameObjects[pGameObjectPlataform->getName()]=pGameObjectPlataform;
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

	mGameObjectPortalContainer.push_back(pGameObjectPortal);

	mGameObjectUsableContainer.push_back(pGameObjectPortal);
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
	mGameObjectPositionalContainer.push_back(gameObjectScaredPlant);
	mGameObjectNonMovableContainer.push_back(gameObjectScaredPlant);
	mGameObjectNonMovableEntityContainer.push_back(gameObjectScaredPlant);

	mGameObjectPhysicsContainer.push_back(gameObjectScaredPlant);
	mGameObjectPhysicsCharacterContainer.push_back(gameObjectScaredPlant);
	mGameObjectScaredPlantContainer.push_back(gameObjectScaredPlant);
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
void GameWorldManager::addGameObjectSignPost(GameObjectSignpostPtr gameObjectSignPost)
{
	mGameObjects[gameObjectSignPost->getName()]=gameObjectSignPost;
	mGameObjectSignPostContainer.push_back(gameObjectSignPost);
	mGameObjectPositionalContainer.push_back(gameObjectSignPost);
	mGameObjectNonMovableContainer.push_back(gameObjectSignPost);
	mGameObjectNonMovableEntityContainer.push_back(gameObjectSignPost);

	mGameObjectPhysicsContainer.push_back(gameObjectSignPost);
	mGameObjectPhysicsCharacterContainer.push_back(gameObjectSignPost);
}
void GameWorldManager::addGameObjectSnakeCreeper(GameObjectSnakeCreeperPtr gameObjectSnakeCreeper)
{
	mGameObjects[gameObjectSnakeCreeper->getName()]=gameObjectSnakeCreeper;
	mGameObjectSnakeCreeperContainer.push_back(gameObjectSnakeCreeper);
	mGameObjectLogicContainer.push_back(gameObjectSnakeCreeper);
}

void GameWorldManager::addGameObjectSound(GameObjectSoundPtr gameObjectSound)
{
	mGameObjects[gameObjectSound->getName()]=gameObjectSound;
	mGameObjectSoundContainer.push_back(gameObjectSound);
	mGameObjectPositionalContainer.push_back(gameObjectSound);
	if (gameObjectSound->getSoundType()==SOUNDTYPE_AMBIENT)
	{
		mAmbientSoundContainer[gameObjectSound->getName()]=gameObjectSound;
	}
}

void GameWorldManager::addGameObjectStoryBook(GameObjectStoryBookPtr pGameObjectStoryBook)
{
	mGameObjects[pGameObjectStoryBook->getName()]=pGameObjectStoryBook;

	mGameObjectPositionalContainer.push_back(pGameObjectStoryBook);
	mGameObjectNonMovableContainer.push_back(pGameObjectStoryBook);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectStoryBook);

	mGameObjectPhysicsContainer.push_back(pGameObjectStoryBook);
	mGameObjectPhysicsVolumeContainer.push_back(pGameObjectStoryBook);
	mGameObjectPhysicsVolumeBoxContainer.push_back(pGameObjectStoryBook);
}

void GameWorldManager::addGameObjectTentetieso(GameObjectTentetiesoPtr pGameObjectTentetieso)
{
	mGameObjects[pGameObjectTentetieso->getName()]=pGameObjectTentetieso;

	mGameObjectPositionalContainer.push_back(pGameObjectTentetieso);
	mGameObjectMovableContainer.push_back(pGameObjectTentetieso);
	mGameObjectMovableEntityContainer.push_back(pGameObjectTentetieso);

	mGameObjectPhysicsContainer.push_back(pGameObjectTentetieso);
	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectTentetieso);

	mGameObjectTentetiesoContainer.push_back(pGameObjectTentetieso);
	mGameObjectLogicContainer.push_back(pGameObjectTentetieso);
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

void GameWorldManager::addGameObjectTree(GameObjectTreePtr pGameObjectTree)
{
	mGameObjects[pGameObjectTree->getName()]=pGameObjectTree;

	mGameObjectPositionalContainer.push_back(pGameObjectTree);
	mGameObjectNonMovableContainer.push_back(pGameObjectTree);
	mGameObjectNonMovableEntityContainer.push_back(pGameObjectTree);

	mGameObjectPhysicsContainer.push_back(pGameObjectTree);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectTree);
	mGameObjectPhysicsSimpleBoxContainer.push_back(pGameObjectTree);
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

void GameWorldManager::addGameObjectTripollo(GameObjectTripolloPtr pGameObjectTripollo)
{
	mGameObjects[pGameObjectTripollo->getName()]=pGameObjectTripollo;

	mGameObjectPositionalContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableContainer.push_back(pGameObjectTripollo);
	mGameObjectMovableEntityContainer.push_back(pGameObjectTripollo);

	mGameObjectPhysicsContainer.push_back(pGameObjectTripollo);
	mGameObjectPhysicsCharacterContainer.push_back(pGameObjectTripollo);

	mGameObjectTripolloContainer.push_back(pGameObjectTripollo);
	mGameObjectLogicContainer.push_back(pGameObjectTripollo);
}

void GameWorldManager::addGameObjectViewport(GameObjectViewportPtr pGameObjectViewport)
{
	mGameObjects[pGameObjectViewport->getName()]=pGameObjectViewport;

	mGameObjectViewportContainer.push_back(pGameObjectViewport);
}

void GameWorldManager::addGameObjectWoodBox(GameObjectWoodBoxPtr pGameObjectWoodBox)
{
	mGameObjects[pGameObjectWoodBox->getName()]=pGameObjectWoodBox;

	mGameObjectMovableContainer.push_back(pGameObjectWoodBox);
	mGameObjectMovableEntityContainer.push_back(pGameObjectWoodBox);
	mGameObjectPhysicsContainer.push_back(pGameObjectWoodBox);
	mGameObjectPhysicsSimpleContainer.push_back(pGameObjectWoodBox);
	mGameObjectPhysicsSimpleBoxContainer.push_back(pGameObjectWoodBox);
}

void GameWorldManager::addGameObjectWater(GameObjectWaterPtr pGameObjectWater)
{
	mGameObjects[pGameObjectWater->getName()]=pGameObjectWater;
	mGameObjectPhysicsContainer.push_back(pGameObjectWater);
}

void GameWorldManager::addGameObjectSkyBody(GameObjectSkyBodyPtr gameObject)
{
	mGameObjects[gameObject->getName()]=gameObject;
	mGameObjectLogicContainer.push_back(gameObject);
	mGameObjectNonMovableContainer.push_back(gameObject);
	mGameObjectNonMovableEntityContainer.push_back(gameObject);
	mGameObjectPositionalContainer.push_back(gameObject);
}

void GameWorldManager::addGameObjectTreeComplex(GameObjectTreeComplexPtr pGameObjectTreeComplex)
{
	mGameObjects[pGameObjectTreeComplex->getName()]=pGameObjectTreeComplex;
}

void GameWorldManager::addGameObjectFog(GameObjectFogPtr pGameObjectFog)
{
	mGameObjects[pGameObjectFog->getName()]=pGameObjectFog;
}

void GameWorldManager::addGameObjectTower(GameObjectTowerPtr pGameObjectTower)
{
	mGameObjects[pGameObjectTower->getName()]=pGameObjectTower;
}

void GameWorldManager::addGameObjectCameraTrigger(GameObjectCameraTriggerPtr pGameObjectCameraTrigger)
{
	mGameObjects[pGameObjectCameraTrigger->getName()]=pGameObjectCameraTrigger;
}

void GameWorldManager::addGameObjectSwitch(GameObjectSwitchPtr pGameObjectSwitch)
{
	mGameObjects[pGameObjectSwitch->getName()]=pGameObjectSwitch;
}

void GameWorldManager::addGameObjectTotem(GameObjectTotemPtr pGameObjectTotem)
{
	mGameObjects[pGameObjectTotem->getName()]=pGameObjectTotem;
}

void GameWorldManager::addGameObjectBomb(GameObjectBombPtr pGameObjectBomb)
{
	mGameObjects[pGameObjectBomb->getName()]=pGameObjectBomb;
}

void GameWorldManager::addGameObjectLevelEntrance(GameObjectLevelEntrancePtr pGameObjectLevelEntrance)
{
	mGameObjects[pGameObjectLevelEntrance->getName()]=pGameObjectLevelEntrance;
}

void GameWorldManager::createTrajectory(TTrajectoryParameters tTrajectoryParameters)
{
	mApp->getTrajectoryManager()->createTrajectory(tTrajectoryParameters);
}

void GameWorldManager::createSceneNode(std::string name,TRenderComponentPositionalParameters tRenderComponentPositionalParameters)
{
	mApp->getRenderSubsystem()->createSceneNode(name,tRenderComponentPositionalParameters);
}

void GameWorldManager::createWalkabilityMap(TWalkabilityMapParameters tWalkabilityMapParameters)
{
	mApp->getTrajectoryManager()->createWalkabilityMap(tWalkabilityMapParameters);
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
	mWorld=newWorld;

	ChangeWorldEventPtr evt = ChangeWorldEventPtr(new ChangeWorldEvent(mWorld));
	evt->fast=true;
	evt->time=mChangeWorldTotalTime;
	evt->change_world_elapsed_time=mChangeWorldElapsedTime;
	evt->random_trees=mRandomChangeWorld;

	addEvent(evt);
}

int GameWorldManager::getMyInstanceWorld()
{
	return mInst->getWorld();
}


int GameWorldManager::getWorld()
{
	return mWorld;
}

void GameWorldManager::changeWorld()
{	
	int newWorld;

	if (mWorld==DREAMS)
	{
		newWorld=NIGHTMARES;
	}
	else if (mWorld==NIGHTMARES)
	{
		newWorld=DREAMS;
	}

	ChangeWorldEventPtr evt = ChangeWorldEventPtr(new ChangeWorldEvent(newWorld));

	evt->fast=false;
	evt->time=mChangeWorldTotalTime;
	evt->change_world_elapsed_time=mChangeWorldElapsedTime;
	evt->random_trees=mRandomChangeWorld;

	addEvent(evt);
}

double GameWorldManager::getChangeWorldElapsedTime() const
{
	return mChangeWorldElapsedTime;
}


void GameWorldManager::activateChangeWorldFast()
{
	changeWorldFinished(mWorld);
	mIsChangingWorld=false;
}

void GameWorldManager::activateChangeWorld()
{
	if (mWorld==DREAMS)
	{
		mWorld=NIGHTMARES;
	}
	else if (mWorld==NIGHTMARES)
	{
		mWorld=DREAMS;
	}

	if(!mIsChangingWorld)
	{
		mChangeWorldElapsedTime=0;
		mIsChangingWorld=true;
		changeWorldStarted(mWorld);
	}
	else
	{
		mChangeWorldElapsedTime=mChangeWorldTotalTime-mChangeWorldElapsedTime;
	}
}

void GameWorldManager::changeWorldFinished(int newWorld)
{
	GameObjectFlashLightPtr flashlight=getGameObjectFlashLight();
	GameObjectSoundPtr sound;

	bool isGameRunningState=mApp->getGameStateManager()->getCurrentGameStateType()==GAME_STATE_RUNNING;;
	if(isGameRunningState)
	{
		CameraParametersPtr pCameraParameters;
		pCameraParameters.reset(new CameraParameters());
		Application::getInstance()->getCameraManager()->setToDefaultCameraParameters(pCameraParameters);
		pCameraParameters->setTarget(getGameObjectOny()->getName());
		Application::getInstance()->getCameraManager()->setCameraFree(pCameraParameters,true);
	}

	switch(newWorld)
	{
		//TODO: Fade ambient sounds.
	case DREAMS:
		sound=BOOST_PTR_CAST(GameObjectSound,
			mAmbientSoundContainer[mDefaultAmbientSound]);
		if (sound.get())
		{
			sound->getAudioComponentNightmares()->setPauseSound(mDefaultAmbientSoundIDNightmares,true);
			sound->getAudioComponentDreams()->setPauseSound(mDefaultAmbientSoundIDDreams,false);
		}
		break;
	case NIGHTMARES:
		sound=BOOST_PTR_CAST(GameObjectSound,
			mAmbientSoundContainer[mDefaultAmbientSound]);
		if (sound.get())
		{
			sound->getAudioComponentDreams()->setPauseSound(mDefaultAmbientSoundIDDreams,true);
			sound->getAudioComponentNightmares()->setPauseSound(mDefaultAmbientSoundIDNightmares,false);
		}
		//if (flashlight.get())
		//	flashlight->createProjector(&mGameObjects);
		break;
	default:
		break;
	}
	if (sound.get())
		sound.reset();
}

void GameWorldManager::changeWorldStarted(int newWorld)
{
	switch(newWorld)
	{
	case DREAMS:
		break;
	case NIGHTMARES:
		break;
	default:
		break;
	}
}

void GameWorldManager::changeToWorld(int newWorld, double perc)
{
	TGameObjectContainerIterator it;
	
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		if(perc*mChangeWorldTotalTime>=it->second->getChangeWorldDelay() && it->second->getWorld()!=newWorld && !it->second->isChangingWorld())
		{
			it->second->activateChangeWorld();
			Logger::getInstance()->log("[changeWorldStarted] CHANGING "+it->second->getName());
		}
	}

	//switch(newWorld)
	//{
	//case DREAMS:
	//	break;
	//case NIGHTMARES:
	//	break;
	//default:
	//	break;
	//}
}

void GameWorldManager::setDreamsRender()
{
	TGameObjectContainerIterator it;
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		it->second->setDreamsRender();
	}
}

void GameWorldManager::setNightmaresRender()
{
	TGameObjectContainerIterator it;
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		it->second->setNightmaresRender();
	}
}

void GameWorldManager::setChangeWorldRender()
{
	TGameObjectContainerIterator it;
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		it->second->setChangeWorldRender();
	}
}

void GameWorldManager::setChangeWorldFactor(double factor)
{
	TGameObjectContainerIterator it;
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		it->second->setChangeWorldFactor(factor);
	}
}

void GameWorldManager::win()
{
	setGameOver(true);
	setGameBeaten(true);
	Logger::getInstance()->log("GameWorldManager::win exec");
}

void GameWorldManager::lose()
{
	setGameOver(true);
	setGameBeaten(false);
	Logger::getInstance()->log("GameWorldManager::lose exec");
}

void GameWorldManager::onyDied()
{
	Logger::getInstance()->log("GameWorldManager::onyDied exec");
	resetAll();
}

bool GameWorldManager::isOnyDying() const
{	
	if (!mGameObjectOnyContainer.empty() && mGameObjectOnyContainer[0].get())
	{
		return mGameObjectOnyContainer[0]->isDying();
	}

	return false;
}

bool GameWorldManager::isOnyHit() const
{	
	if (!mGameObjectOnyContainer.empty() && mGameObjectOnyContainer[0].get())
	{
		return mGameObjectOnyContainer[0]->isHit();
	}

	return false;
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
	if (!mGameObjectOnyContainer.empty())
	{
		return mGameObjectOnyContainer[0];
	}

	GameObjectOnyPtr nullPtr;
	nullPtr.reset();
	return nullPtr;
}

Ogre::Vector3 GameWorldManager::getGameObjectOnyPosition()
{
	if (!mGameObjectOnyContainer.empty())
	{
		return mGameObjectOnyContainer[0]->getRenderComponentPositional()->getPosition();
	}

	return Ogre::Vector3(0,0,0);
}

GameObjectViewportPtr GameWorldManager::getGameObjectViewport()
{
	if (!mGameObjectViewportContainer.empty())
	{
		return mGameObjectViewportContainer[0];
	}

	GameObjectViewportPtr nullPtr;
	nullPtr.reset();
	return nullPtr;

}
GameObjectFlashLightPtr GameWorldManager::getGameObjectFlashLight()
{
	if (!mGameObjectFlashLightContainer.empty())
	{
		return mGameObjectFlashLightContainer[0];
	}

	GameObjectFlashLightPtr nullPtr;
	nullPtr.reset();
	return nullPtr;
}
GameObjectPillowPtr GameWorldManager::getGameObjectPillow()
{
	return mGameObjectPillow;
}


ApplicationPtr GameWorldManager::getParent()
{
	return mApp;
}

void GameWorldManager::clearEvents()
{
	mEventManager->clearEvents();
}

EventProcessorPtr GameWorldManager::getEventProcessor()
{
	return mEventProcessor;
}

double GameWorldManager::getDistance(const std::string& obj1Name, const std::string& obj2Name)
{
	double distance=-1;
	GameObjectPtr obj1= mInst->getObject(obj1Name);
	GameObjectPtr obj2= mInst->getObject(obj2Name);

	if (obj1.get() && obj2.get())
	{
		distance=obj1->computeDistanceTo(obj2);
	}
	//std::ostringstream distanceText;
	//distanceText.str("");
	//distanceText<<"Distance between "<<obj1Name<<" and "<<obj2Name<<": "<<distance<<std::endl;
	//Logger::getInstance()->log(distanceText.str());
	return distance;
}

double GameWorldManager::getClosestChangeWorldDistance(Vector3 objectPosition)
{
	double currentChangeWorldDistance;
	double minChangeWorldDistance;

	unsigned int i;
	for(i=0;i<mGameObjectPortalContainer.size();i++)
	{
		if(i==0)
		{
			minChangeWorldDistance=mGameObjectPortalContainer[i]->getRenderComponentPositional()->getPosition().distance(objectPosition);
		}
		else
		{	
			currentChangeWorldDistance=mGameObjectPortalContainer[i]->getRenderComponentPositional()->getPosition().distance(objectPosition);

			if(currentChangeWorldDistance<minChangeWorldDistance)
			{
				minChangeWorldDistance=currentChangeWorldDistance;
			}
		}

	}

	return minChangeWorldDistance;
}

double GameWorldManager::getPlayerDistance(const std::string& objName)
{
	//Logger::getInstance()->log("getPlayerDistance "+objName);
	if (mInst->getGameObjectOny().get())
	{
		return getDistance(mInst->getGameObjectOny()->getName(),objName);
	}

	return -1;
}

void GameWorldManager::useWeapon()
{
	if (getGameObjectOny().get())
	{
		getGameObjectOny()->beginAttack();
	}
}
void GameWorldManager::stopUsingWeapon()
{
	if (getGameObjectOny().get())
	{
		getGameObjectOny()->switchOff();
	}
}

void GameWorldManager::useObject()
{
	if(!mGameObjectUsableContainer.empty())
	{
		// In case of collision, only the first object will be activated
		for (TGameObjectUsableContainer::iterator it=mGameObjectUsableContainer.begin();
			it!=mGameObjectUsableContainer.end();++it)
		{
			if ((*it)->canBeActivated())
			{
				ActivatedItemEventPtr evt = ActivatedItemEventPtr(new ActivatedItemEvent(*it));
				addEvent(evt);
				break;
			}
		}
	}
}

void GameWorldManager::postUpdate()
{
	TGameObjectContainerIterator it;

	for(it = mGameObjects.begin(); it != mGameObjects.end(); it++)
	{
		//Logger::getInstance()->log("Updating game object " + it->second->getName());
		it->second->postUpdate();
	}

	dispatchEvents();
}
void GameWorldManager::toggleTreeVisibility()
{
	TGameObjectContainerIterator it;
	GameObjectTreePtr treeD;
	
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		treeD=BOOST_PTR_CAST(GameObjectTree,it->second);		
		if (treeD && treeD.get())
		{		
			if (mWorld==DREAMS && treeD->getLogicComponent()->existsInDreams())
				treeD->getRenderComponentEntity()->getEntity()->setVisible(!treeD->getRenderComponentEntity()->getEntity()->isVisible());
			else if (mWorld==NIGHTMARES && treeD->getLogicComponent()->existsInNightmares())
				treeD->getRenderComponentEntity()->getEntity()->setVisible(!treeD->getRenderComponentEntity()->getEntity()->isVisible());
		}
	}
}

void GameWorldManager::victory()
{
	GameOverEventPtr evt= GameOverEventPtr(new GameOverEvent(true));
	mInst->addEvent(evt);
}

void GameWorldManager::setCheckPointLUA(std::string checkpoint,int checkpointNumber)
{
	Trajectory * pTrajectory;
	try
	{
		if(mInst->getParent()->getTrajectoryManager()->hasTrajectory(checkpoint))
		{
			pTrajectory=mInst->getParent()->getTrajectoryManager()->getTrajectoryInstance("checkpoint");
			mInst->getParent()->getTrajectoryManager()->setPredefinedTrajectory(*pTrajectory,checkpoint,"blue");
		}
		else
		{
			throw "CheckPoint "+checkpoint+" does not exist";
		}
		mInst->setCheckPointPosition(pTrajectory->getCurrentNode()->getSceneNode()->getPosition());
		mInst->setCheckPointOrientation(pTrajectory->getCurrentNode()->getSceneNode()->getOrientation());

		mInst->setCheckPointNumber(checkpointNumber);

		mInst->setCheckPointWorld(mInst->getWorld());

		mInst->checkpointLevelEvents();
	}
	catch( std::string error )
	{
		Logger::getInstance()->log("[CameraManager] "+error);
	}
}

int GameWorldManager::getCheckPointNumberLUA()
{
	return mInst->getCheckPointNumber();
}

void GameWorldManager::setCheckPointNumber(int checkpointNumber)
{
	mCheckPointNumber=checkpointNumber;
}

int GameWorldManager::getCheckPointNumber() const
{
	return mCheckPointNumber;
}

void GameWorldManager::setCheckPointPosition(Vector3 checkpoint)
{
	Logger::getInstance()->log("[setCheckPointPosition] "+Ogre::StringConverter::toString(checkpoint));
	mCheckPointPosition=checkpoint;
}

Vector3 GameWorldManager::getCheckPointPosition() const
{
	return mCheckPointPosition;
}

void GameWorldManager::setCheckPointOrientation(Quaternion checkpoint)
{
	mCheckPointOrientation=checkpoint;
}

Quaternion GameWorldManager::getCheckPointOrientation() const
{
	return mCheckPointOrientation;
}

void GameWorldManager::setCheckPointWorld(int world)
{
	mCheckPointWorld=world;
}

int GameWorldManager::getCheckPointWorld() const
{
	return mCheckPointWorld;
}

void GameWorldManager::setChangeWorldTimes()
{
	TGameObjectContainerIterator it;
	
	for (it = mGameObjects.begin();it!=mGameObjects.end();it++)
	{
		it->second->calculateChangeWorldTotalTime(mChangeWorldTotalTime);
	}
}

double GameWorldManager::getChangeWorldTotalTime() const
{
	return mChangeWorldTotalTime;
}

void GameWorldManager::playSoundFromGameObject(const std::string& objectName, const std::string& soundID)
{
	GameObjectPtr go;
	if (mGameObjects.find(objectName)!=mGameObjects.end())
	{
		if ((go=mGameObjects[objectName]).get())
		{
			go->playSound(soundID);
		}
	}
}
void GameWorldManager::setLevelname(const std::string& levelFilename)
{
	level=levelFilename;
}

std::string GameWorldManager::getLevelname()
{
	return level;
}

bool GameWorldManager::isChangingWorldLUA()
{
	return mInst->isChangingWorld();
}

bool GameWorldManager::isChangingWorld()
{
	return mIsChangingWorld;
}

void GameWorldManager::addNestLink(const std::string& object, const std::string& nest)
{
	mNestLinks[object]=nest;
}
// Append child diamonds to a diamond tree, and link the parent to its children)
void GameWorldManager::resolveNestLinks()
{
	TNestLinkMap::const_iterator it;
	GameObjectNestPtr nest;
	GameObjectPtr obj;
	for (it=mNestLinks.begin();it!=mNestLinks.end();++it)
	{
		nest= BOOST_PTR_CAST(GameObjectNest,mGameObjects[it->second]);
		obj= BOOST_PTR_CAST(GameObject,mGameObjects[it->first]);
		obj->setParentNest(nest->getName());
		obj->setParentNestInstance(nest);
		obj->disable();
		nest->addChild(obj);
		std::vector<GameObjectPtr> nestChildren=*(nest->getChildren());
		std::sort(nestChildren.begin(),nestChildren.end(), nestChildrenSortPredicate);
	}
}
LogicComponentOny* GameWorldManager::getOny()
{
	return mInst->getGameObjectOny()->getLogicComponentOny().get();
}

LogicComponent* GameWorldManager::getCryKing()
{
	return mInst->getGameObject("cryking#0")->getLogicComponent().get();
}

LogicComponent* GameWorldManager::getBomb()
{
	return mInst->getGameObject("bomb#0")->getLogicComponent().get();
}


void GameWorldManager::loadFlashlightDecalMaterials()
{
	if (getGameObjectFlashLight().get())
		getGameObjectFlashLight()->loadDecalMaterials(mGameObjects);
}
GameObject* GameWorldManager::getGameObject(const std::string& objectName)
{
	return mInst->getObject(objectName).get();
}
bool GameWorldManager::isFirstMsgBox() const
{
	return mFirstMsgBox;
}
void GameWorldManager::setFirstMsgBox(bool firstMsgBox)
{
	mFirstMsgBox=firstMsgBox;
}
bool GameWorldManager::isFirstSignpostHit() const
{
	return mFirstSignpostHit;
}
void GameWorldManager::setFirstSignpostHit(bool firstSignpostHit)
{
	mFirstSignpostHit=firstSignpostHit;
}
void GameWorldManager::increaseOnyDiamonds(int amount)
{	
	GameObjectOnyPtr ony;
	if ((ony= getGameObjectOny()).get())
		ony->addDiamonds(amount);
}

void GameWorldManager::addExecutedLevelEventLUA(std::string cutscene)
{
	mInst->addExecutedLevelEvent(cutscene);
}

void GameWorldManager::addExecutedLevelEvent(std::string cutscene)
{
	mExecutedLevelEvents.insert(cutscene);

	Logger::getInstance()->log("LEVEL EVENT: "+cutscene);

	if(cutscene.compare(BOMB_EXPLODED_NEAR_BRIGDGE_ROCK)==0)
	{
		GameObjectPtr obj = getObject("invisible-wall#BOMBS_PUZZLE");

		GameObjectInvisibleWallPtr wall = BOOST_PTR_CAST(GameObjectInvisibleWall,obj);
		wall->desactivateWall();
	}
	else if(cutscene.compare(CUTSCENE_7_1_TRIPOLLOS_PLATFORM)==0 ||
		cutscene.compare(CUTSCENE_7_2_TRIPOLLOS_PLATFORM)==0 ||
		cutscene.compare(CUTSCENE_7_3_TRIPOLLOS_PLATFORM)==0)
	{
		GameObjectPtr obj = getObject("totem#0");

		GameObjectTotemPtr totem= 
				BOOST_PTR_CAST(GameObjectTotem,obj);
		totem->levelDown();
	}
	else if(cutscene.compare(TRIPOLLO_PLATFORM_PUZZLE_END)==0)
	{
		GameObjectPtr obj = getObject("changeworld#platform_big");

		GameObjectPortalPtr portal= 
				BOOST_PTR_CAST(GameObjectPortal,obj);
		portal->getPhysicsComponentSimpleBox()->destroy();
		portal->getPhysicsComponentSimpleBox()->create();
	}
	else if(cutscene.compare(CUTSCENE_8_1_PLATFORMS_TO_FINAL_BOSS)==0)
	{
		GameObjectPlataformPtr plataform;
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower3_1"));
		plataform->activate();
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower3_2"));
		plataform->activate();
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower3_3"));
		plataform->activate();
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower3_4"));
		plataform->activate();
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower3_6"));
		plataform->activate();
	}
	else if(cutscene.compare(EVENT_FIRST_CHANGE_WORLD_ACTIVATED)==0)
	{
		launchCutScene("cutscenes_level2.lua","cutScene2");
	}
	else if(hasExecutedLevelEvent(TRIPOLLO_1_STATUE_DEFEATED) &&
			hasExecutedLevelEvent(TRIPOLLO_2_STATUE_DEFEATED) &&
			hasExecutedLevelEvent(TRIPOLLO_3_STATUE_DEFEATED) &&
			hasExecutedLevelEvent(TRIPOLLO_4_STATUE_DEFEATED) &&
			hasExecutedLevelEvent(TRIPOLLO_5_STATUE_DEFEATED) &&
			!hasExecutedLevelEvent(CUTSCENE_8_0_TRIPOLLO_STATUES_END)
		)
	{
		launchCutScene("cutscenes_level2.lua","cutScene8_0");
	}
	else if(cutscene.compare(CUTSCENE_8_0_TRIPOLLO_STATUES_END)==0)
	{
		GameObjectPlataformPtr plataform;
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower2_1"));
		plataform->activate();
		plataform=BOOST_PTR_CAST(GameObjectPlataform,getObject("plataform#tower2_2"));
		plataform->activate();
	}

}

void GameWorldManager::launchCutScene(const std::string& scriptFile,const std::string& scriptFunction)
{
		GameRunningStatePtr state=BOOST_PTR_CAST(GameRunningState,Application::getInstance()->getGameStateManager()->getCurrentState());
		state->launchCutScene(scriptFile,scriptFunction);
}

bool GameWorldManager::hasExecutedLevelEventLUA(std::string cutscene)
{
	return mInst->hasExecutedLevelEvent(cutscene);
}

bool GameWorldManager::hasExecutedLevelEvent(std::string cutscene)
{
	return mExecutedLevelEvents.count(cutscene)>0 || mExecutedLevelEventsPermanent.count(cutscene)>0;
}

void GameWorldManager::restartBombPositionLUA()
{
	mInst->restartBombPosition();
}

void GameWorldManager::restartBombPosition()
{
	GameObjectBombPtr bomb= 
		BOOST_PTR_CAST(GameObjectBomb,getObject("bomb#0"));
	bomb->restartToInitialPoint();
}

void GameWorldManager::initBombPuzzleLUA()
{
	mInst->initBombPuzzle();
}

void GameWorldManager::initBombPuzzle()
{
	GameObjectBombPtr bomb= 
		BOOST_PTR_CAST(GameObjectBomb,getObject("bomb#0"));
	bomb->initBombPuzzle();
}


void GameWorldManager::checkpointLevelEvents()
{
	std::set<std::string>::iterator it;

	for(it=mExecutedLevelEvents.begin();it!=mExecutedLevelEvents.end();it++)
	{
		mExecutedLevelEventsPermanent.insert(it->data());
	}
	mExecutedLevelEvents.clear();
}

void GameWorldManager::rescaleViewport(double left, double top, double width, double height)
{
	getGameObjectViewport()->rescaleViewport(left,top,width,height);
}