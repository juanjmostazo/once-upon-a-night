#include "ComponentFactory.h"
#include "../Application.h"
#include "../Game/GameObject/GameObject.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentCamera.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Graphics/RenderComponent/RenderComponentDecal.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../Logic/LogicComponent/LogicComponent.h"
#include "../Logic/LogicComponent/LogicComponentOny.h"
#include "../Logic/LogicComponent/LogicComponentItem.h"
#include "../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../Logic/LogicComponent/LogicComponentUsable.h"
#include "../Logic/LogicComponent/WeaponComponent.h"
#include "../Logic/LogicComponent/AttackComponent.h"

using namespace OUAN;

ComponentFactory* ComponentFactory::mInstance=NULL;

ComponentFactory* ComponentFactory::getInstance()
{
	if (mInstance)
		return mInstance;
	else{
		mInstance=new ComponentFactory();
		return mInstance;
	}
}

void ComponentFactory::init(ApplicationPtr app)
{
	mApp=app;
}

RenderComponentPtr ComponentFactory::createRenderComponent(GameObjectPtr gameObject,TRenderComponentParameters tRenderComponentParameters)
{
	//Create void Render Component
	RenderComponentPtr pRenderComponent = RenderComponentPtr(new RenderComponent()); 

	pRenderComponent->setParent(gameObject);	

	return pRenderComponent;
}

RenderComponentBillboardSetPtr ComponentFactory::createRenderComponentBillboardSet(GameObjectPtr gameObject,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters)
{
	//Create void Render Component
	RenderComponentBillboardSetPtr pRenderComponentBillboardSetPtr = RenderComponentBillboardSetPtr(new RenderComponentBillboardSet()); 

	pRenderComponentBillboardSetPtr->setParent(gameObject);	

	//init Render Component
	pRenderComponentBillboardSetPtr->setBillboardSet(mApp->getRenderSubsystem()->createBillboardSet(gameObject->getName(),tRenderComponentBillboardSetParameters));

	return pRenderComponentBillboardSetPtr;
}
RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters)
{
	//Create and init Render Component Camera
	RenderComponentCameraPtr pRenderComponentCameraPtr = mApp->getCameraManager()->createCamera(gameObject->getName(),tRenderComponentCameraParameters);

	pRenderComponentCameraPtr->setParent(gameObject);	

	return pRenderComponentCameraPtr;
}

RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(std::string name,GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters,QueryFlags flags)
{
	//Create void Render Component
	RenderComponentEntityPtr pRenderComponentEntity = RenderComponentEntityPtr(new RenderComponentEntity()); 


	pRenderComponentEntity->setParent(gameObject);	

	//init Render Component
	pRenderComponentEntity->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),name,tRenderComponentEntityParameters,flags));

	//pRenderComponentEntity->initAnimations(tRenderComponentEntityParameters.tRenderComponentEntityAnimParams);

	return pRenderComponentEntity;
}
RenderComponentLightPtr ComponentFactory::createRenderComponentLight(std::string name,GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters)
{
	//Create void Render Component
	RenderComponentLightPtr pRenderComponentLight = RenderComponentLightPtr(new RenderComponentLight()); 

	pRenderComponentLight->setParent(gameObject);

	//init Render Component
	pRenderComponentLight->setLight(mApp->getRenderSubsystem()->createLight(name,tRenderComponentLightParameters));

	return pRenderComponentLight;
}

RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters)
{
	//Create void Render Component
	RenderComponentParticleSystemPtr pRenderComponentParticleSystem = RenderComponentParticleSystemPtr(new RenderComponentParticleSystem()); 

	pRenderComponentParticleSystem->setParent(gameObject);

	//init Render Component
	pRenderComponentParticleSystem->setParticleSystem(mApp->getRenderSubsystem()->createParticleSystem(gameObject->getName(),tRenderComponentParticleSystemParameters));

	return pRenderComponentParticleSystem;
}

RenderComponentDecalPtr ComponentFactory::createRenderComponentDecal(GameObjectPtr gameObject,TRenderComponentDecalParameters tRenderComponentDecalParameters)
{
	//Create void Render Component
	RenderComponentDecalPtr pRenderComponentDecal = RenderComponentDecalPtr(new RenderComponentDecal()); 

	//init Render Component
	pRenderComponentDecal=mApp->getRenderSubsystem()->createDecal(gameObject,tRenderComponentDecalParameters);

	pRenderComponentDecal->setParent(gameObject);

	return pRenderComponentDecal;
}

RenderComponentScenePtr ComponentFactory::createRenderComponentScene(GameObjectPtr gameObject,TRenderComponentSceneParameters tRenderComponentSceneParameters)
{
	//Create void Render Component
	RenderComponentScenePtr pRenderComponentScene = RenderComponentScenePtr(new RenderComponentScene()); 

	pRenderComponentScene->setParent(gameObject);

	//init Render Component
	pRenderComponentScene->setSceneManager(mApp->getRenderSubsystem()->setSceneParameters(gameObject->getName(),tRenderComponentSceneParameters));
	
	//set Sky materials
	pRenderComponentScene->setSkyMaterials(tRenderComponentSceneParameters);

	return pRenderComponentScene;
}

RenderComponentInitialPtr ComponentFactory::createRenderComponentInitial(RenderComponentPositionalPtr pRenderComponentPositional)
{
	//Create void Render Component
	RenderComponentInitialPtr pRenderComponentInitial = RenderComponentInitialPtr(new RenderComponentInitial()); 

	//init Render Component
	pRenderComponentInitial->setPosition(pRenderComponentPositional->getPosition());
	pRenderComponentInitial->setOrientation(pRenderComponentPositional->getOrientation());

	return pRenderComponentInitial;
}

RenderComponentPositionalPtr ComponentFactory::createRenderComponentPositional(GameObjectPtr gameObject,TRenderComponentPositionalParameters tRenderComponentPositionalParameters)
{
	//Create void Render Component
	RenderComponentPositionalPtr pRenderComponentPositional = RenderComponentPositionalPtr(new RenderComponentPositional()); 

	pRenderComponentPositional->setParent(gameObject);	

	//Init Render Component
	pRenderComponentPositional->setSceneNode(mApp->getRenderSubsystem()->createSceneNode(gameObject->getName(),tRenderComponentPositionalParameters));
	pRenderComponentPositional->setCameraManager(mApp->getCameraManager());

	return pRenderComponentPositional;
}

RenderComponentPositionalPtr ComponentFactory::createRenderComponentPositional(GameObjectPtr gameObject,TRenderComponentPositionalParameters tRenderComponentPositionalParameters,std::string name)
{
	//Create void Render Component
	RenderComponentPositionalPtr pRenderComponentPositional = RenderComponentPositionalPtr(new RenderComponentPositional()); 

	pRenderComponentPositional->setParent(gameObject);	

	//init Render Component
	pRenderComponentPositional->setSceneNode(mApp->getRenderSubsystem()->createSceneNode(name,tRenderComponentPositionalParameters));
	pRenderComponentPositional->setCameraManager(mApp->getCameraManager());

	return pRenderComponentPositional;
}

RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	//Create void Render Component
	RenderComponentViewportPtr pRenderComponentViewport = RenderComponentViewportPtr(new RenderComponentViewport()); 

	pRenderComponentViewport->setParent(gameObject);

	//init Render Component
	pRenderComponentViewport->setViewport(mApp->getCameraManager()->setViewportParameters(gameObject->getName(),tRenderComponentViewportParameters));

	return pRenderComponentViewport;
}

PhysicsComponentCharacterPtr ComponentFactory::createPhysicsComponentCharacter(GameObjectPtr gameObject,TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentCharacterPtr pPhysicsComponentCharacter = 
		PhysicsComponentCharacterPtr(new PhysicsComponentCharacter(COMPONENT_TYPE_PHYSICS_CHARACTER)); 

	pPhysicsComponentCharacter->setParent(gameObject);	
	pPhysicsComponentCharacter->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentCharacter->setMass(tPhysicsComponentCharacterParameters.mass);
	//pPhysicsComponentCharacter->setQueryFlags(flags);
	pPhysicsComponentCharacter->setNxOgreSize(
		NxOgre::Vec2(	tPhysicsComponentCharacterParameters.radius, 
						tPhysicsComponentCharacterParameters.height));

	NxOgre::ControllerDescription mNxOgreControllerDescription;
	mNxOgreControllerDescription.mCallback=mApp->getPhysicsSubsystem().get();
	mNxOgreControllerDescription.mPosition.set(NxOgre::Vec3(tRenderComponentPositional->getSceneNode()->getPosition()));
	pPhysicsComponentCharacter->setNxOgreControllerDescription(mNxOgreControllerDescription);

	return pPhysicsComponentCharacter;
}

PhysicsComponentComplexConvexPtr ComponentFactory::createPhysicsComponentComplexConvex(GameObjectPtr gameObject,TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex = 
		PhysicsComponentComplexConvexPtr(new PhysicsComponentComplexConvex(COMPONENT_TYPE_PHYSICS_COMPLEX_CONVEX)); 

	pPhysicsComponentComplexConvex->setParent(gameObject);	
	pPhysicsComponentComplexConvex->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentComplexConvex->setMass(tPhysicsComponentComplexConvexParameters.mass);
	//pPhysicsComponentComplexConvex->setQueryFlags(flags);	

	NxOgre::Mesh* convexMesh = NxOgre::MeshManager::getSingleton()->load(
		tPhysicsComponentComplexConvexParameters.nxsFile.c_str());

	pPhysicsComponentComplexConvex->setNxOgreConvex(new NxOgre::Convex(convexMesh));

	return pPhysicsComponentComplexConvex;
}

PhysicsComponentComplexTrianglePtr ComponentFactory::createPhysicsComponentComplexTriangle(GameObjectPtr gameObject,TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{	
	PhysicsComponentComplexTrianglePtr pPhysicsComponentComplexTriangle = 
		PhysicsComponentComplexTrianglePtr(new PhysicsComponentComplexTriangle(COMPONENT_TYPE_PHYSICS_COMPLEX_TRIANGLE)); 

	pPhysicsComponentComplexTriangle->setParent(gameObject);	
	pPhysicsComponentComplexTriangle->setSceneNode(tRenderComponentPositional->getSceneNode());	
	pPhysicsComponentComplexTriangle->setMass(tPhysicsComponentComplexTriangleParameters.mass);
	//pPhysicsComponentComplexTriangle->setQueryFlags(flags);

	NxOgre::Mesh* triangleMesh = NxOgre::MeshManager::getSingleton()->load(
		tPhysicsComponentComplexTriangleParameters.nxsFile.c_str());

	NxOgre::TriangleGeometry* triangleGeometry = new NxOgre::TriangleGeometry(triangleMesh);
	triangleGeometry->setGroup(GROUP_COLLIDABLE_NON_PUSHABLE);

	pPhysicsComponentComplexTriangle->setNxOgreTriangleGeometry(triangleGeometry);



	return pPhysicsComponentComplexTriangle;
}

PhysicsComponentSimpleCapsulePtr ComponentFactory::createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentSimpleCapsulePtr pPhysicsComponentSimpleCapsule = 
		PhysicsComponentSimpleCapsulePtr(new PhysicsComponentSimpleCapsule(COMPONENT_TYPE_PHYSICS_SIMPLE_CAPSULE)); 

	pPhysicsComponentSimpleCapsule->setParent(gameObject);	
	pPhysicsComponentSimpleCapsule->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentSimpleCapsule->setMass(tPhysicsComponentSimpleCapsuleParameters.mass);
	//pPhysicsComponentSimpleCapsule->setQueryFlags(flags);

	pPhysicsComponentSimpleCapsule->setNxOgreSize(
		NxOgre::Vec2(	tPhysicsComponentSimpleCapsuleParameters.radius,
						tPhysicsComponentSimpleCapsuleParameters.height));



	return pPhysicsComponentSimpleCapsule;
}

PhysicsComponentSimpleBoxPtr ComponentFactory::createPhysicsComponentSimpleBox(GameObjectPtr gameObject,TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentSimpleBoxPtr pPhysicsComponentSimpleBox = 
		PhysicsComponentSimpleBoxPtr(new PhysicsComponentSimpleBox(COMPONENT_TYPE_PHYSICS_SIMPLE_BOX)); 

	pPhysicsComponentSimpleBox->setParent(gameObject);	
	pPhysicsComponentSimpleBox->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentSimpleBox->setMass(tPhysicsComponentSimpleBoxParameters.mass);
	//pPhysicsComponentSimpleBox->setQueryFlags(flags);

	pPhysicsComponentSimpleBox->setNxOgreSize(
		NxOgre::Vec3(	tPhysicsComponentSimpleBoxParameters.lengthX,
						tPhysicsComponentSimpleBoxParameters.lengthY,
						tPhysicsComponentSimpleBoxParameters.lengthZ));

	return pPhysicsComponentSimpleBox;
}

PhysicsComponentVolumeCapsulePtr ComponentFactory::createPhysicsComponentVolumeCapsule(GameObjectPtr gameObject,TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentVolumeCapsulePtr pPhysicsComponentVolumeCapsule = 
		PhysicsComponentVolumeCapsulePtr(new PhysicsComponentVolumeCapsule(COMPONENT_TYPE_PHYSICS_VOLUME_CAPSULE)); 

	pPhysicsComponentVolumeCapsule->setParent(gameObject);	
	pPhysicsComponentVolumeCapsule->setSceneNode(tRenderComponentPositional->getSceneNode());
	//pPhysicsComponentVolumeCapsule->setQueryFlags(flags);
	
	pPhysicsComponentVolumeCapsule->setNxOgreSize(
		NxOgre::Vec2(	tPhysicsComponentVolumeCapsuleParameters.radius,
						tPhysicsComponentVolumeCapsuleParameters.height));

	return pPhysicsComponentVolumeCapsule;
}

PhysicsComponentVolumeBoxPtr ComponentFactory::createPhysicsComponentVolumeBox(GameObjectPtr gameObject,TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentVolumeBoxPtr pPhysicsComponentVolumeBox = 
		PhysicsComponentVolumeBoxPtr(new PhysicsComponentVolumeBox(COMPONENT_TYPE_PHYSICS_VOLUME_BOX)); 

	pPhysicsComponentVolumeBox->setParent(gameObject);	
	pPhysicsComponentVolumeBox->setSceneNode(tRenderComponentPositional->getSceneNode());
	//pPhysicsComponentVolumeBox->setQueryFlags(flags);
	
	pPhysicsComponentVolumeBox->setNxOgreSize(
		NxOgre::Vec3(	tPhysicsComponentVolumeBoxParameters.lengthX,
						tPhysicsComponentVolumeBoxParameters.lengthY,
						tPhysicsComponentVolumeBoxParameters.lengthZ));

	return pPhysicsComponentVolumeBox;
}

PhysicsComponentVolumeConvexPtr ComponentFactory::createPhysicsComponentVolumeConvex(GameObjectPtr gameObject,TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentVolumeConvexPtr pPhysicsComponentVolumeConvex = 
		PhysicsComponentVolumeConvexPtr(new PhysicsComponentVolumeConvex(COMPONENT_TYPE_PHYSICS_VOLUME_CONVEX)); 

	pPhysicsComponentVolumeConvex->setParent(gameObject);	
	pPhysicsComponentVolumeConvex->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentVolumeConvex->setMass(tPhysicsComponentVolumeConvexParameters.mass);
	//pPhysicsComponentVolumeConvex->setQueryFlags(flags);	

	NxOgre::Mesh* convexMesh = NxOgre::MeshManager::getSingleton()->load(
		tPhysicsComponentVolumeConvexParameters.nxsFile.c_str());
	pPhysicsComponentVolumeConvex->setNxOgreConvexMesh(convexMesh);

	return pPhysicsComponentVolumeConvex;
}

LogicComponentPtr ComponentFactory::createLogicComponent(GameObjectPtr gameObject, TLogicComponentParameters tLogicComponentParameters)
{
	LogicComponentPtr logicComponent=LogicComponentPtr(new LogicComponent());
	logicComponent->setExistsInDreams(tLogicComponentParameters.existsInDreams);
	logicComponent->setExistsInNightmares(tLogicComponentParameters.existsInNightmares);

	logicComponent->setScriptFilename(tLogicComponentParameters.scriptFilename);
	logicComponent->setScriptFunction(tLogicComponentParameters.scriptFunction);
	logicComponent->setState(tLogicComponentParameters.defaultState);
	logicComponent->setParent(gameObject);
	return logicComponent;
}

LogicComponentItemPtr ComponentFactory::createLogicComponentItem(GameObjectPtr gameObject, TLogicComponentItemParameters LogicComponentItemParameters)
{
	LogicComponentItemPtr pLogicComponentItem=LogicComponentItemPtr(new LogicComponentItem());
	pLogicComponentItem->setExistsInDreams(LogicComponentItemParameters.existsInDreams);
	pLogicComponentItem->setExistsInNightmares(LogicComponentItemParameters.existsInNightmares);
	pLogicComponentItem->setIsTaken(false);

	pLogicComponentItem->setScriptFilename(LogicComponentItemParameters.scriptFilename);
	pLogicComponentItem->setScriptFunction(LogicComponentItemParameters.scriptFunction);
	pLogicComponentItem->setState(LogicComponentItemParameters.defaultState);
	pLogicComponentItem->setParent(gameObject);

	return pLogicComponentItem;
}

LogicComponentOnyPtr ComponentFactory::createLogicComponentOny(GameObjectPtr gameObject, TLogicComponentOnyParameters LogicComponentOnyParameters)
{
	LogicComponentOnyPtr pLogicComponentOny=LogicComponentOnyPtr(new LogicComponentOny());
	pLogicComponentOny->setExistsInDreams(LogicComponentOnyParameters.existsInDreams);
	pLogicComponentOny->setExistsInNightmares(LogicComponentOnyParameters.existsInNightmares);
	
	pLogicComponentOny->setHealthPoints(LogicComponentOnyParameters.healthPoints);
	pLogicComponentOny->setInitialHealthPoints(LogicComponentOnyParameters.healthPoints);
	pLogicComponentOny->setNumLives(LogicComponentOnyParameters.numLives);
	pLogicComponentOny->setInitialNumLives(LogicComponentOnyParameters.numLives);


	pLogicComponentOny->setAttackDamage(LogicComponentOnyParameters.attackDamage);

	pLogicComponentOny->setScriptFilename(LogicComponentOnyParameters.scriptFilename);
	pLogicComponentOny->setScriptFunction(LogicComponentOnyParameters.scriptFunction);
	pLogicComponentOny->setState(LogicComponentOnyParameters.defaultState);
	pLogicComponentOny->setParent(gameObject);

	return pLogicComponentOny;
}

LogicComponentEnemyPtr ComponentFactory::createLogicComponentEnemy(GameObjectPtr gameObject, TLogicComponentEnemyParameters LogicComponentEnemyParameters)
{
	LogicComponentEnemyPtr pLogicComponentEnemy=LogicComponentEnemyPtr(new LogicComponentEnemy());
	pLogicComponentEnemy->setExistsInDreams(LogicComponentEnemyParameters.existsInDreams);
	pLogicComponentEnemy->setExistsInNightmares(LogicComponentEnemyParameters.existsInNightmares);
	
	pLogicComponentEnemy->setHealthPoints(LogicComponentEnemyParameters.healthPoints);
	pLogicComponentEnemy->setInitialHealthPoints(LogicComponentEnemyParameters.healthPoints);
	pLogicComponentEnemy->setLineOfSight(LogicComponentEnemyParameters.lineOfSight);

	pLogicComponentEnemy->setColourSensitivityMask(LogicComponentEnemyParameters.colourSensitivityMask);

	pLogicComponentEnemy->setScriptFilename(LogicComponentEnemyParameters.scriptFilename);
	pLogicComponentEnemy->setScriptFunction(LogicComponentEnemyParameters.scriptFunction);
	pLogicComponentEnemy->setState(LogicComponentEnemyParameters.defaultState);
	pLogicComponentEnemy->setParent(gameObject);
	return pLogicComponentEnemy;
}
LogicComponentUsablePtr ComponentFactory::createLogicComponentUsable(GameObjectPtr gameObject, 
																	 TLogicComponentUsableParameters logicComponentParameters)
{
	LogicComponentUsablePtr logicComponent = LogicComponentUsablePtr(new LogicComponentUsable());
	logicComponent->setExistsInDreams(logicComponentParameters.existsInDreams);
	logicComponent->setExistsInNightmares(logicComponentParameters.existsInNightmares);
	
	logicComponent->setApproachDistance(logicComponentParameters.approachDistance);
	logicComponent->setActivateDistance(logicComponentParameters.activateDistance);
	
	logicComponent->setScriptFilename(logicComponentParameters.scriptFilename);
	logicComponent->setScriptFunction(logicComponentParameters.scriptFunction);
	logicComponent->setState(logicComponentParameters.defaultState);

	logicComponent->setParent(gameObject);
	return logicComponent;
}


WeaponComponentPtr ComponentFactory::createWeaponComponent(GameObjectPtr gameObject, TWeaponComponentParameters weaponComponentParameters)
{
	WeaponComponentPtr weaponComponent = WeaponComponentPtr(new WeaponComponent());	
	weaponComponent->initWeapons(weaponComponentParameters.mWeaponNames,weaponComponentParameters.mSelectedWeapon);
	weaponComponent->setParent(gameObject);
	return weaponComponent;
}

AttackComponentPtr ComponentFactory::createAttackComponent(GameObjectPtr gameObject, TAttackComponentParameters attackComponentParameters)
{
	AttackComponentPtr attackComponent = AttackComponentPtr(new AttackComponent());
	attackComponent->init(attackComponentParameters.mAttacks,attackComponentParameters.mSelectedAttack);
	attackComponent->setParent(gameObject);
	return attackComponent;
}

TrajectoryComponentPtr ComponentFactory::createTrajectoryComponent(GameObjectPtr gameObject,bool TwoDimensions)
{
	TrajectoryComponentPtr pTrajectoryComponent = TrajectoryComponentPtr(new TrajectoryComponent); 
	Trajectory * pTrajectory;

	pTrajectory=mApp->getTrajectoryManager()->getTrajectoryInstance();
	if(TwoDimensions)
	{
		pTrajectory->setAs2DTrajectory();
	}
	else
	{
		pTrajectory->setAs3DTrajectory();
	}

	pTrajectoryComponent->setTrajectory(pTrajectory);
	pTrajectoryComponent->setParent(gameObject);

	return pTrajectoryComponent;
}