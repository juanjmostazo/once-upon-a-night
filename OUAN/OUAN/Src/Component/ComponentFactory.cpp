#include "OUAN_Precompiled.h"

#include "ComponentFactory.h"
#include "../Application.h"
#include "../Game/GameObject/GameObject.h"
#include "../Graphics/RenderSubsystem.h"
#include "../Graphics/RenderComponent/RenderComponent.h"
#include "../Graphics/RenderComponent/RenderComponentBillboardSet.h"
#include "../Graphics/RenderComponent/RenderComponentEntity.h"
#include "../Graphics/RenderComponent/RenderComponentLight.h"
#include "../Graphics/RenderComponent/RenderComponentParticleSystem.h"
#include "../Graphics/RenderComponent/RenderComponentScene.h"
#include "../Graphics/RenderComponent/RenderComponentInitial.h"
#include "../Graphics/RenderComponent/RenderComponentPositional.h"
#include "../Graphics/RenderComponent/RenderComponentQuadHalo.h"
#include "../Graphics/RenderComponent/RenderComponentGlow.h"
#include "../Graphics/RenderComponent/RenderComponentFractalVolume.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Graphics/RenderComponent/RenderComponentDecal.h"
#include "../Graphics/RenderComponent/RenderComponentMessageBox.h"
#include "../Graphics/RenderComponent/RenderComponentWater.h"
#include "../Graphics/RenderComponent/RenderComponentPlane.h"
#include "../Graphics/Volume/BufferManager.h"
#include "../Graphics/TrajectoryManager/Trajectory.h"
#include "../Graphics/TrajectoryManager/TrajectoryManager.h"
#include "../Graphics/TrajectoryManager/TrajectoryComponent.h"
#include "../Graphics/CameraManager/CameraManager.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacter.h"
#include "../Physics/PhysicsComponent/PhysicsComponentCharacterOny.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentComplexTriangle.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentSimpleBox.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeCapsule.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeBox.h"
#include "../Physics/PhysicsComponent/PhysicsComponentVolumeConvex.h"
#include "../Physics/PhysicsComponent/PhysicsComponentWeapon.h"
#include "../Logic/LogicComponent/LogicComponent.h"
#include "../Logic/LogicComponent/LogicComponentOny.h"
#include "../Logic/LogicComponent/LogicComponentItem.h"
#include "../Logic/LogicComponent/LogicComponentBreakable.h"
#include "../Logic/LogicComponent/LogicComponentEnemy.h"
#include "../Logic/LogicComponent/LogicComponentUsable.h"
#include "../Logic/LogicComponent/LogicComponentProp.h"
#include "../Logic/LogicComponent/LogicComponentTrigger.h"
#include "../Logic/LogicComponent/LogicComponentCameraTrigger.h"
#include "../Logic/LogicComponent/WeaponComponent.h"
#include "../Logic/LogicComponent/AttackComponent.h"
#include "../Audio/AudioComponent/AudioComponent.h"

using namespace OUAN;

ComponentFactory::ComponentFactory()
{

}

ComponentFactory::~ComponentFactory()
{
	if (mApp.get())
	{
		mApp.reset();
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

RenderComponentBillboardSetPtr ComponentFactory::createRenderComponentBillboardSet(std::string name,GameObjectPtr gameObject,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters,bool existInDreams, bool existInNightmares)
{
	//Create void Render Component
	RenderComponentBillboardSetPtr pRenderComponentBillboardSetPtr = RenderComponentBillboardSetPtr(new RenderComponentBillboardSet()); 

	pRenderComponentBillboardSetPtr->setParent(gameObject);	

	//init Render Component
	pRenderComponentBillboardSetPtr->setBillboardSet(mApp->getRenderSubsystem()->createBillboardSet(gameObject->getName(),
		name,tRenderComponentBillboardSetParameters),
		existInDreams,existInNightmares);

	return pRenderComponentBillboardSetPtr;
}

//RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters)
//{
//	//Create and init Render Component Camera
//	RenderComponentCameraPtr pRenderComponentCameraPtr = mApp->getCameraManager()->createCamera(gameObject->getName(),tRenderComponentCameraParameters);
//
//	pRenderComponentCameraPtr->setParent(gameObject);	
//
//	return pRenderComponentCameraPtr;
//}

RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(std::string name,GameObjectPtr gameObject,TRenderComponentEntityParameters entityParams,bool existInDreams, bool existInNightmares)
{
	//Create void Render Component
	RenderComponentEntityPtr pRenderComponentEntity = RenderComponentEntityPtr(new RenderComponentEntity()); 

	pRenderComponentEntity->setParent(gameObject);	
	
	TKeyFrameMap keyframes;
	keyframes.clear();
	
	Ogre::Entity* ent=mApp->getRenderSubsystem()->createEntity(gameObject->getName(),name,
		entityParams,(entityParams.mInitManualAnimations)?&keyframes:NULL);
	//init Render Component
	pRenderComponentEntity->setEntity(ent,existInDreams,existInNightmares);

	if (!entityParams.initialAnimation.empty() && ent->getAllAnimationStates())
		pRenderComponentEntity->initAnimationBlender(entityParams.initialAnimation);

	pRenderComponentEntity->initAnimations(entityParams.tRenderComponentEntityAnimParams);

	return pRenderComponentEntity;
}

RenderComponentWaterPtr ComponentFactory::createRenderComponentWater(std::string name,GameObjectPtr gameObject,TRenderComponentWaterParameters tRenderComponentWaterParameters,bool existInDreams, bool existInNightmares)
{
	//Create void Render Component
	RenderComponentWaterPtr pRenderComponentWater = RenderComponentWaterPtr(new RenderComponentWater()); 

	pRenderComponentWater->setParent(gameObject);	

	//init Render Component
	pRenderComponentWater->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),name,tRenderComponentWaterParameters.tRenderComponentEntityParameters),
		existInDreams,existInNightmares);

	pRenderComponentWater->initFresnelReflection(mApp->getCameraManager(),mApp->getGameWorldManager());
	return pRenderComponentWater;
}

RenderComponentLightPtr ComponentFactory::createRenderComponentLight(std::string name,GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters)
{
	//Create void Render Component
	RenderComponentLightPtr pRenderComponentLight = RenderComponentLightPtr(new RenderComponentLight()); 

	pRenderComponentLight->setParent(gameObject);

	std::string sceneNodeName="";
	if (gameObject->hasPositionalComponent() && gameObject->getPositionalComponent().get() 
		&& gameObject->getPositionalComponent()->getSceneNode()->getName().compare(name)!=0)
	{
		sceneNodeName=gameObject->getPositionalComponent()->getSceneNode()->getName();
	}

	//init Render Component
	pRenderComponentLight->setLight(mApp->getRenderSubsystem()->createLight(name,tRenderComponentLightParameters,sceneNodeName));

	return pRenderComponentLight;
}

RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters, RenderComponentPositionalPtr pRenderComponentPositional)
{
	//Create void Render Component
	RenderComponentParticleSystemPtr pRenderComponentParticleSystem = RenderComponentParticleSystemPtr(new RenderComponentParticleSystem()); 

	pRenderComponentParticleSystem->setParent(gameObject);

	//Init Render Component
	pRenderComponentParticleSystem->setParticleSystems(
		mApp->getRenderSubsystem()->createParticleSystems(
			gameObject->getName(),
			tRenderComponentParticleSystemParameters,
			pRenderComponentPositional));

	return pRenderComponentParticleSystem;
}

RenderComponentDecalPtr ComponentFactory::createRenderComponentDecal(GameObjectPtr gameObject,TRenderComponentDecalParameters decalParams, Ogre::SceneManager* sceneManager)
{
	//Create void Render Component
	RenderComponentDecalPtr pRenderComponentDecal = RenderComponentDecalPtr(new RenderComponentDecal(sceneManager)); 

	pRenderComponentDecal->initProjector(
		decalParams.projectorName, decalParams.textureName,
		decalParams.projectorOffset, decalParams.projectorNode);
	pRenderComponentDecal->initFilterProjector(decalParams.filterTextureName);
	pRenderComponentDecal->setVisible(false);
	pRenderComponentDecal->changeColour(decalParams.tintColour);

	pRenderComponentDecal->setParent(gameObject);

	return pRenderComponentDecal;
}

RenderComponentMessageBoxPtr ComponentFactory::createRenderComponentMessageBox(GameObjectPtr gameObject,TRenderComponentMessageBoxParameters msgBoxParams)
{
	//Create void Render Component
	RenderComponentMessageBoxPtr msgBox= RenderComponentMessageBoxPtr(new RenderComponentMessageBox()); 

	msgBox->setBasePanelName(msgBoxParams.basePanelName);
	msgBox->setBasePanel(msgBoxParams.basePanelName);
	if (!msgBoxParams.charPanelName.empty())
	{
		msgBox->setCharPanelName(msgBoxParams.charPanelName);
		msgBox->setCharPanelMaterialName(msgBoxParams.charPanelMaterialName);
		msgBox->setCharPanel(msgBoxParams.charPanelName,
			msgBoxParams.charPanelMaterialName);
	}
	msgBox->setDuration(msgBoxParams.duration);
	
	msgBox->setParent(gameObject);
	msgBox->setMessage(msgBoxParams.mMessage);

	return msgBox;
}

RenderComponentPlanePtr ComponentFactory::createRenderComponentPlane(std::string name,GameObjectPtr gameObject,TRenderComponentPlaneParameters tRenderComponentPlaneParameters)
{
	//Create void Render Component
	RenderComponentPlanePtr pRenderComponentPlane = RenderComponentPlanePtr(new RenderComponentPlane()); 

	//init Render Component
	pRenderComponentPlane->setPlane(mApp->getRenderSubsystem()->createPlane(gameObject->getName(),name,tRenderComponentPlaneParameters));

	pRenderComponentPlane->setParent(gameObject);

	return pRenderComponentPlane;
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

RenderComponentQuadHaloPtr ComponentFactory::createRenderComponentQuadHalo(GameObjectPtr gameObject,TRenderComponentQuadHaloParameters tRenderComponentQuadHaloParameters, RenderComponentPositionalPtr pRenderComponentPositional)
{
	//Create void Render Component
	RenderComponentQuadHaloPtr pRenderComponentQuadHalo = RenderComponentQuadHaloPtr(new RenderComponentQuadHalo()); 

	pRenderComponentQuadHalo->setParent(gameObject);	

	//init Render Component
	ThingRenderable* quadHalo = new ThingRenderable(
		tRenderComponentQuadHaloParameters.haloRadium, 
		tRenderComponentQuadHaloParameters.totalQuads, 
		tRenderComponentQuadHaloParameters.quadSize);

	quadHalo->setMaterial(tRenderComponentQuadHaloParameters.quadMaterial);

	quadHalo->setQueryFlags(OUAN::QUERYFLAGS_NONE);

	pRenderComponentQuadHalo->setQuadHalo(quadHalo);

	pRenderComponentQuadHalo->setSpeedScale(tRenderComponentQuadHaloParameters.speedScale);

	pRenderComponentQuadHalo->setSceneNode(
		pRenderComponentPositional->getSceneNode()->createChildSceneNode(
			"quad_halo#" + Application::getInstance()->getStringUniqueId()));

	pRenderComponentQuadHalo->getSceneNode()->attachObject(quadHalo);

	pRenderComponentQuadHalo->getSceneNode()->setPosition(
		Ogre::Vector3(
			tRenderComponentQuadHaloParameters.offsetX,
			tRenderComponentQuadHaloParameters.offsetY,
			tRenderComponentQuadHaloParameters.offsetZ));

	pRenderComponentQuadHalo->getSceneNode()->setVisible(false);

	return pRenderComponentQuadHalo;
}

RenderComponentGlowPtr ComponentFactory::createRenderComponentGlow(GameObjectPtr gameObject,TRenderComponentGlowParameters tRenderComponentGlowParameters, RenderComponentPositionalPtr pRenderComponentPositional, RenderComponentEntityPtr pRenderComponentEntity)
{
	//Create void Render Component
	RenderComponentGlowPtr pRenderComponentGlow = RenderComponentGlowPtr(new RenderComponentGlow()); 

	pRenderComponentGlow->setParent(gameObject);	

	pRenderComponentGlow->setEntity(
		pRenderComponentEntity->getEntity()->clone(
			pRenderComponentEntity->getEntity()->getName() + "_" + tRenderComponentGlowParameters.material));

	pRenderComponentGlow->getEntity()->setMaterialName(tRenderComponentGlowParameters.material);
	pRenderComponentGlow->getEntity()->setQueryFlags(QUERYFLAGS_NONE);

	pRenderComponentGlow->setParams(
		tRenderComponentGlowParameters.time_scale,
		tRenderComponentGlowParameters.size_scale,
		tRenderComponentGlowParameters.expand_width,
		tRenderComponentGlowParameters.expand_grow,
		tRenderComponentGlowParameters.alpha,
		tRenderComponentGlowParameters.color_r,
		tRenderComponentGlowParameters.color_g,
		tRenderComponentGlowParameters.color_b);

	pRenderComponentGlow->setSceneNode(
		pRenderComponentPositional->getSceneNode()->createChildSceneNode(
		"glow#" + Application::getInstance()->getStringUniqueId()));

	pRenderComponentGlow->getSceneNode()->attachObject(pRenderComponentGlow->getEntity());
	pRenderComponentGlow->getSceneNode()->setVisible(false);

	return pRenderComponentGlow;
}

RenderComponentFractalVolumePtr ComponentFactory::createRenderComponentFractalVolume(GameObjectPtr gameObject,TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeParameters, RenderComponentPositionalPtr pRenderComponentPositional)
{
	//Create void Render Component
	RenderComponentFractalVolumePtr pRenderComponentFractalVolume = RenderComponentFractalVolumePtr(new RenderComponentFractalVolume()); 

	pRenderComponentFractalVolume->setParent(gameObject);	

	//init Render Component
	VolumeRenderable* fractalVolume = 
		new VolumeRenderable(
			tRenderComponentFractalVolumeParameters.vSlices, 
			tRenderComponentFractalVolumeParameters.vSize, 
			tRenderComponentFractalVolumeParameters.texture3D);

	fractalVolume->setQueryFlags(OUAN::QUERYFLAGS_NONE);

	BufferManager::getInstance()->setBuffer(
		tRenderComponentFractalVolumeParameters.texture3D,
		tRenderComponentFractalVolumeParameters.vCut,
		tRenderComponentFractalVolumeParameters.vScale,
		tRenderComponentFractalVolumeParameters.juliaGlobalReal,
		tRenderComponentFractalVolumeParameters.juliaGlobalImag, 
		tRenderComponentFractalVolumeParameters.juliaGlobalTheta,
		tRenderComponentFractalVolumeParameters.initColorR,
		tRenderComponentFractalVolumeParameters.initColorG,
		tRenderComponentFractalVolumeParameters.initColorB,
		tRenderComponentFractalVolumeParameters.endColorR,
		tRenderComponentFractalVolumeParameters.endColorG,
		tRenderComponentFractalVolumeParameters.endColorB);

	pRenderComponentFractalVolume->setFractalVolume(fractalVolume);

	pRenderComponentFractalVolume->setRotationDegrees(
		Ogre::Vector3(
			tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondX,
			tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondY,
			tRenderComponentFractalVolumeParameters.rotationDegreesPerSecondZ));

	pRenderComponentFractalVolume->setSceneNode(
		pRenderComponentPositional->getSceneNode()->createChildSceneNode(
			"fractal_volume#" + Application::getInstance()->getStringUniqueId()));

	pRenderComponentFractalVolume->getSceneNode()->attachObject(fractalVolume);

	pRenderComponentFractalVolume->getSceneNode()->setPosition(
		Ogre::Vector3(
			tRenderComponentFractalVolumeParameters.offsetX,
			tRenderComponentFractalVolumeParameters.offsetY,
			tRenderComponentFractalVolumeParameters.offsetZ));

	pRenderComponentFractalVolume->getSceneNode()->pitch(Ogre::Degree(tRenderComponentFractalVolumeParameters.rotationDegreesInitialX));
	pRenderComponentFractalVolume->getSceneNode()->yaw(Ogre::Degree(tRenderComponentFractalVolumeParameters.rotationDegreesInitialY));
	pRenderComponentFractalVolume->getSceneNode()->roll(Ogre::Degree(tRenderComponentFractalVolumeParameters.rotationDegreesInitialZ));

	pRenderComponentFractalVolume->getSceneNode()->setVisible(false);

	return pRenderComponentFractalVolume;
}

RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters)
{
	//Create void Render Component
	RenderComponentViewportPtr pRenderComponentViewport = RenderComponentViewportPtr(new RenderComponentViewport()); 

	pRenderComponentViewport->setParent(gameObject);

	//init Render Component
	pRenderComponentViewport->setViewport(mApp->getCameraManager()->setViewportParameters(gameObject->getName(),tRenderComponentViewportParameters));

	pRenderComponentViewport->setRenderSubsystem(mApp->getRenderSubsystem());

	pRenderComponentViewport->prepareEffects();
	pRenderComponentViewport->initEffects();

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

	pPhysicsComponentCharacter->create();

	return pPhysicsComponentCharacter;
}

PhysicsComponentCharacterOnyPtr ComponentFactory::createPhysicsComponentCharacterOny(GameObjectPtr gameObject,TPhysicsComponentCharacterOnyParameters tPhysicsComponentCharacterOnyParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentCharacterOnyPtr pPhysicsComponentCharacterOny = 
		PhysicsComponentCharacterOnyPtr(new PhysicsComponentCharacterOny(COMPONENT_TYPE_PHYSICS_CHARACTER_ONY)); 

	pPhysicsComponentCharacterOny->setParent(gameObject);	
	pPhysicsComponentCharacterOny->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentCharacterOny->setMass(tPhysicsComponentCharacterOnyParameters.mass);
	//pPhysicsComponentCharacter->setQueryFlags(flags);
	pPhysicsComponentCharacterOny->setNxOgreSize(
		NxOgre::Vec2(
			tPhysicsComponentCharacterOnyParameters.radius, 
			tPhysicsComponentCharacterOnyParameters.height));

	NxOgre::ControllerDescription mNxOgreControllerDescription;
	mNxOgreControllerDescription.mCallback=mApp->getPhysicsSubsystem().get();
	mNxOgreControllerDescription.mPosition.set(NxOgre::Vec3(tRenderComponentPositional->getSceneNode()->getPosition()));
	pPhysicsComponentCharacterOny->setNxOgreControllerDescription(mNxOgreControllerDescription);

	pPhysicsComponentCharacterOny->create();

	return pPhysicsComponentCharacterOny;
}

PhysicsComponentComplexConvexPtr ComponentFactory::createPhysicsComponentComplexConvex(GameObjectPtr gameObject,TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentComplexConvexPtr pPhysicsComponentComplexConvex = 
		PhysicsComponentComplexConvexPtr(new PhysicsComponentComplexConvex(COMPONENT_TYPE_PHYSICS_COMPLEX_CONVEX)); 

	pPhysicsComponentComplexConvex->setParent(gameObject);	
	pPhysicsComponentComplexConvex->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentComplexConvex->setMass(tPhysicsComponentComplexConvexParameters.mass);

	pPhysicsComponentComplexConvex->setBalancingParams(
		tPhysicsComponentComplexConvexParameters.balanceRadiumX,
		tPhysicsComponentComplexConvexParameters.balanceRadiumY,
		tPhysicsComponentComplexConvexParameters.balanceRadiumZ,
		tPhysicsComponentComplexConvexParameters.balanceRadiumTime);

	//pPhysicsComponentComplexConvex->setQueryFlags(flags);	

	NxOgre::Mesh* convexMesh = NxOgre::MeshManager::getSingleton()->load(
		tPhysicsComponentComplexConvexParameters.nxsFile.c_str());

	pPhysicsComponentComplexConvex->setNxOgreConvex(new NxOgre::Convex(convexMesh));

	pPhysicsComponentComplexConvex->create();

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

	pPhysicsComponentComplexTriangle->create();

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

	pPhysicsComponentSimpleCapsule->create();

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

	pPhysicsComponentSimpleBox->setInitialVelocity(
		NxOgre::Vec3(
			tPhysicsComponentSimpleBoxParameters.initVelocityX,
			tPhysicsComponentSimpleBoxParameters.initVelocityY,
			tPhysicsComponentSimpleBoxParameters.initVelocityZ));

	pPhysicsComponentSimpleBox->create();

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

	pPhysicsComponentVolumeCapsule->create();

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

	pPhysicsComponentVolumeBox->create();

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

	pPhysicsComponentVolumeConvex->create();

	return pPhysicsComponentVolumeConvex;
}

PhysicsComponentWeaponPtr ComponentFactory::createPhysicsComponentWeapon(GameObjectPtr gameObject,TPhysicsComponentWeaponParameters tPhysicsComponentWeaponParameters,RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags)
{
	PhysicsComponentWeaponPtr pPhysicsComponentWeapon = 
		PhysicsComponentWeaponPtr(new PhysicsComponentWeapon(COMPONENT_TYPE_PHYSICS_CHARACTER)); 

	pPhysicsComponentWeapon->setParent(gameObject);	
	pPhysicsComponentWeapon->setSceneNode(tRenderComponentPositional->getSceneNode());
	pPhysicsComponentWeapon->setMass(tPhysicsComponentWeaponParameters.mass);
	//pPhysicsComponentWeapon->setQueryFlags(flags);
	pPhysicsComponentWeapon->setNxOgreSize(
		NxOgre::Vec2(0,0));

	pPhysicsComponentWeapon->setNxOgreMaxSize(
		NxOgre::Vec2(	tPhysicsComponentWeaponParameters.radius, 
						tPhysicsComponentWeaponParameters.height));

	NxOgre::ControllerDescription mNxOgreControllerDescription;
	mNxOgreControllerDescription.mCallback=mApp->getPhysicsSubsystem().get();
	mNxOgreControllerDescription.mPosition.set(NxOgre::Vec3(tRenderComponentPositional->getSceneNode()->getPosition()));
	pPhysicsComponentWeapon->setNxOgreControllerDescription(mNxOgreControllerDescription);
	pPhysicsComponentWeapon->setMovementFactor(tPhysicsComponentWeaponParameters.movementFactor);
	pPhysicsComponentWeapon->setInflateSpeed(tPhysicsComponentWeaponParameters.inflateSpeed);

	//pPhysicsComponentWeapon->create();

	return pPhysicsComponentWeapon;
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

LogicComponentBreakablePtr ComponentFactory::createLogicComponentBreakable(GameObjectPtr gameObject, TLogicComponentBreakableParameters logicComponentBreakableParameters)
{
	LogicComponentBreakablePtr pLogicComponentBreakable=LogicComponentBreakablePtr(new LogicComponentBreakable());
	pLogicComponentBreakable->setExistsInDreams(logicComponentBreakableParameters.existsInDreams);
	pLogicComponentBreakable->setExistsInNightmares(logicComponentBreakableParameters.existsInNightmares);
	pLogicComponentBreakable->setIsBroken(false);

	pLogicComponentBreakable->setScriptFilename(logicComponentBreakableParameters.scriptFilename);
	pLogicComponentBreakable->setScriptFunction(logicComponentBreakableParameters.scriptFunction);
	pLogicComponentBreakable->setState(logicComponentBreakableParameters.defaultState);
	pLogicComponentBreakable->setParent(gameObject);

	return pLogicComponentBreakable;
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

	pLogicComponentOny->setScriptFilename(LogicComponentOnyParameters.scriptFilename);
	pLogicComponentOny->setScriptFunction(LogicComponentOnyParameters.scriptFunction);
	pLogicComponentOny->setState(LogicComponentOnyParameters.defaultState);
	pLogicComponentOny->setParent(gameObject);

	pLogicComponentOny->setCollectableItems(LogicComponentOnyParameters.collectedItems);

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
	pLogicComponentEnemy->setEnemyType(LogicComponentEnemyParameters.enemyType);
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
LogicComponentPropPtr ComponentFactory::createLogicComponentProp(GameObjectPtr gameObject, 
																	 TLogicComponentPropParameters logicComponentParameters)
{
	LogicComponentPropPtr logicComponent = LogicComponentPropPtr(new LogicComponentProp());
	logicComponent->setExistsInDreams(logicComponentParameters.existsInDreams);
	logicComponent->setExistsInNightmares(logicComponentParameters.existsInNightmares);

	logicComponent->setApproachDistance(logicComponentParameters.approachDistance);
	logicComponent->setDelay(logicComponentParameters.delay);
	
	logicComponent->setScriptFilename(logicComponentParameters.scriptFilename);
	logicComponent->setScriptFunction(logicComponentParameters.scriptFunction);
	logicComponent->setState(logicComponentParameters.defaultState);
	logicComponent->setTimeSpent(0);

	logicComponent->setParent(gameObject);
	return logicComponent;
}
LogicComponentTriggerPtr ComponentFactory::createLogicComponentTrigger(GameObjectPtr gameObject, 
																	 TLogicComponentTriggerParameters logicComponentParameters)
{
	LogicComponentTriggerPtr logicComponent = LogicComponentTriggerPtr(new LogicComponentTrigger());
	logicComponent->setExistsInDreams(logicComponentParameters.existsInDreams);
	logicComponent->setExistsInNightmares(logicComponentParameters.existsInNightmares);

	logicComponent->setDreamsEnterActionFunction(logicComponentParameters.mDreamsEnterActionFunction);
	logicComponent->setDreamsEnterConditionFunction(logicComponentParameters.mDreamsEnterConditionFunction);
	logicComponent->setDreamsExitConditionFunction(logicComponentParameters.mDreamsExitConditionFunction);
	logicComponent->setDreamsExitActionFunction(logicComponentParameters.mDreamsExitActionFunction);
	logicComponent->setNightmaresEnterActionFunction(logicComponentParameters.mNightmaresEnterActionFunction);
	logicComponent->setNightmaresEnterConditionFunction(logicComponentParameters.mNightmaresEnterConditionFunction);
	logicComponent->setNightmaresExitConditionFunction(logicComponentParameters.mNightmaresExitConditionFunction);
	logicComponent->setNightmaresExitActionFunction(logicComponentParameters.mNightmaresExitActionFunction);
	logicComponent->setTriggerScript(logicComponentParameters.mTriggerScript);

	logicComponent->setState(logicComponentParameters.defaultState);

	logicComponent->setParent(gameObject);
	return logicComponent;
}

LogicComponentCameraTriggerPtr ComponentFactory::createLogicComponentCameraTrigger(GameObjectPtr gameObject, TLogicComponentCameraTriggerParameters logicComponentParameters)
{
	LogicComponentCameraTriggerPtr logicComponent = LogicComponentCameraTriggerPtr(new LogicComponentCameraTrigger());
	
	logicComponent->setExistsInDreams(logicComponentParameters.existsInDreams);
	logicComponent->setExistsInNightmares(logicComponentParameters.existsInNightmares);

	logicComponent->setCameraTrigger(logicComponentParameters.pCameraTrigger);

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

TrajectoryComponentPtr ComponentFactory::createTrajectoryComponent(GameObjectPtr gameObject,TTrajectoryComponentParameters ttrajectoryComponentParameters)
{
	TrajectoryComponentPtr pTrajectoryComponent = TrajectoryComponentPtr(new TrajectoryComponent); 
	Trajectory * pTrajectory;

	pTrajectory=mApp->getTrajectoryManager()->getTrajectoryInstance(gameObject->getName());
	if(ttrajectoryComponentParameters.twoDimensions)
	{
		pTrajectory->setAs2DTrajectory();
	}
	else
	{
		pTrajectory->setAs3DTrajectory();
	}
	pTrajectory->setDefaultSpeed(ttrajectoryComponentParameters.defaultSpeed);

	pTrajectoryComponent->setTrajectory(pTrajectory);
	pTrajectoryComponent->setParent(gameObject);


	return pTrajectoryComponent;
}
AudioComponentPtr ComponentFactory::createAudioComponent(GameObjectPtr gameObject, const TAudioComponentMap& audioComponentSounds, AudioSubsystemPtr audioSubsystem)
{
	AudioComponentPtr audioComponentPtr=AudioComponentPtr(new AudioComponent(audioSubsystem));
	audioComponentPtr->setSounds(audioComponentSounds);
	audioComponentPtr->setParent(gameObject);
	return audioComponentPtr;
}