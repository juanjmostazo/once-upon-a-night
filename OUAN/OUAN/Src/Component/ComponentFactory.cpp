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
#include "../Graphics/RenderComponent/RenderComponentQuadHalo.h"
#include "../Graphics/RenderComponent/RenderComponentFractalVolume.h"
#include "../Graphics/RenderComponent/RenderComponentViewport.h"
#include "../Graphics/RenderComponent/RenderComponentDecal.h"
#include "../Graphics/RenderComponent/RenderComponentWater.h"
#include "../Graphics/Volume/JuliaManager.h"
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
#include "../Logic/LogicComponent/LogicComponentTrigger.h"
#include "../Logic/LogicComponent/WeaponComponent.h"
#include "../Logic/LogicComponent/AttackComponent.h"

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

RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(std::string name,GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters)
{
	//Create void Render Component
	RenderComponentEntityPtr pRenderComponentEntity = RenderComponentEntityPtr(new RenderComponentEntity()); 

	pRenderComponentEntity->setParent(gameObject);	

	//init Render Component
	pRenderComponentEntity->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),name,tRenderComponentEntityParameters));

	pRenderComponentEntity->initAnimations(tRenderComponentEntityParameters.tRenderComponentEntityAnimParams);

	return pRenderComponentEntity;
}

RenderComponentWaterPtr ComponentFactory::createRenderComponentWater(std::string name,GameObjectPtr gameObject,TRenderComponentWaterParameters tRenderComponentWaterParameters)
{
	//Create void Render Component
	RenderComponentWaterPtr pRenderComponentWater = RenderComponentWaterPtr(new RenderComponentWater()); 

	pRenderComponentWater->setParent(gameObject);	

	//init Render Component
	pRenderComponentWater->setEntity(mApp->getRenderSubsystem()->createEntity(gameObject->getName(),name,tRenderComponentWaterParameters.tRenderComponentEntityParameters));

	pRenderComponentWater->initAnimations(tRenderComponentWaterParameters.tRenderComponentEntityParameters.tRenderComponentEntityAnimParams);
	pRenderComponentWater->initFresnelReflection(mApp->getCameraManager(),mApp->getGameWorldManager());
	return pRenderComponentWater;
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

RenderComponentQuadHaloPtr ComponentFactory::createRenderComponentQuadHalo(GameObjectPtr gameObject,TRenderComponentQuadHaloParameters tRenderComponentQuadHaloParameters, RenderComponentPositionalPtr pRenderComponentPositional)
{
	//Create void Render Component
	RenderComponentQuadHaloPtr pRenderComponentQuadHalo = RenderComponentQuadHaloPtr(new RenderComponentQuadHalo()); 

	pRenderComponentQuadHalo->setParent(gameObject);	

	//init Render Component
	ThingRenderable* quadHalo = new ThingRenderable(
		tRenderComponentQuadHaloParameters.haloRadio, 
		tRenderComponentQuadHaloParameters.totalQuads, 
		tRenderComponentQuadHaloParameters.quadSize);

	quadHalo->setMaterial(tRenderComponentQuadHaloParameters.quadMaterial);

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

	Julia julia = JuliaManager::getInstance()->getJulia(
		tRenderComponentFractalVolumeParameters.juliaGlobalReal,
		tRenderComponentFractalVolumeParameters.juliaGlobalImag, 
		tRenderComponentFractalVolumeParameters.juliaGlobalTheta);

	Ogre::TexturePtr texture3D = 
		Application::getInstance()->getRenderSubsystem()->getTexture3D(tRenderComponentFractalVolumeParameters.texture3D);

	Ogre::HardwarePixelBufferSharedPtr buffer = texture3D->getBuffer(0, 0);

	buffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);

	const Ogre::PixelBox &pb = buffer->getCurrentLock();

	double vCutInv = 1.0f / tRenderComponentFractalVolumeParameters.vCut;

	unsigned int* pbptr = static_cast<unsigned int*>(pb.data);
	for(size_t z=pb.front; z<pb.back; z++) 
	{
		for(size_t y=pb.top; y<pb.bottom; y++)
		{
			for(size_t x=pb.left; x<pb.right; x++)
			{
				if(z==pb.front || z==(pb.back-1) || y==pb.top|| y==(pb.bottom-1) || x==pb.left || x==(pb.right-1))
				{
					pbptr[x] = 0; // On border, must be zero
				} 
				else
				{
					float val = julia.eval(
						((float)x/pb.getWidth()-0.5f) * tRenderComponentFractalVolumeParameters.vScale, 
						((float)y/pb.getHeight()-0.5f) * tRenderComponentFractalVolumeParameters.vScale, 
						((float)z/pb.getDepth()-0.5f) * tRenderComponentFractalVolumeParameters.vScale);

					if(val > tRenderComponentFractalVolumeParameters.vCut)
					{
						val = tRenderComponentFractalVolumeParameters.vCut;
					}

					Ogre::PixelUtil::packColour(
						//(float)(tRenderComponentFractalVolumeParameters.colorR < 0 ? x/pb.getWidth() : tRenderComponentFractalVolumeParameters.colorR), 
						//(float)(tRenderComponentFractalVolumeParameters.colorG < 0 ? y/pb.getHeight() : tRenderComponentFractalVolumeParameters.colorG), 
						//(float)(tRenderComponentFractalVolumeParameters.colorB < 0 ? z/pb.getDepth() : tRenderComponentFractalVolumeParameters.colorB), 
						(float)x/pb.getWidth(), 
						(float)y/pb.getHeight(), 
						(float)z/pb.getDepth(),
						(1.0f-(val*vCutInv))*0.7f, 
						Ogre::PF_A8R8G8B8, 
						&pbptr[x]);
				}	
			}

			pbptr += pb.rowPitch;
		}

		pbptr += pb.getSliceSkip();
	}

	buffer->unlock();

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

	pTrajectory=mApp->getTrajectoryManager()->getTrajectoryInstance(gameObject->getName());
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