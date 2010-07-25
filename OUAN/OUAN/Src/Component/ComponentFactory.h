#ifndef COMPONENTFACTORYH_H
#define COMPONENTFACTORYH_H

#include "../OUAN.h"
#include "../Audio/AudioDefs.h"

namespace OUAN
{
	/// Class in charge for
	/// creating components
	class ComponentFactory
	{
	private:
		/// the application
		ApplicationPtr mApp;
		
	public:
		ComponentFactory();
		~ComponentFactory();

		void init(ApplicationPtr app);

		//create and return a render component
		/// @param gameObject the component's parent object and render component parameters
		/// @return pointer to the newly created Ogre component instance
		RenderComponentPtr createRenderComponent(GameObjectPtr gameObject,TRenderComponentParameters tRenderComponentParameters);
		RenderComponentBillboardSetPtr createRenderComponentBillboardSet(std::string name,GameObjectPtr gameObject,
			TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters);
		//RenderComponentCameraPtr createRenderComponentCamera(GameObjectPtr gameObject,
		//	TRenderComponentCameraParameters tRenderComponentCameraParameters);
		RenderComponentEntityPtr createRenderComponentEntity(std::string name,GameObjectPtr gameObject,
			TRenderComponentEntityParameters tRenderComponentEntityParameters);
		RenderComponentLightPtr createRenderComponentLight(std::string name,GameObjectPtr gameObject,
			TRenderComponentLightParameters tRenderComponentLightParameters);
		RenderComponentParticleSystemPtr createRenderComponentParticleSystem(GameObjectPtr gameObject,
			TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters,
			RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentScenePtr createRenderComponentScene(GameObjectPtr gameObject,
			TRenderComponentSceneParameters tRenderComponentSceneParameters);
		RenderComponentInitialPtr createRenderComponentInitial(
			RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentPositionalPtr createRenderComponentPositional(GameObjectPtr gameObject,
			TRenderComponentPositionalParameters tRenderComponentPositionalParameters);
		RenderComponentPositionalPtr createRenderComponentPositional(GameObjectPtr gameObject,
			TRenderComponentPositionalParameters tRenderComponentPositionalParameters,
			std::string name);
		RenderComponentQuadHaloPtr createRenderComponentQuadHalo(GameObjectPtr gameObject,
			TRenderComponentQuadHaloParameters tRenderComponentQuadHaloParameters,
			RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentGlowPtr createRenderComponentGlow(GameObjectPtr gameObject,
			TRenderComponentGlowParameters tRenderComponentGlowParameters,
			RenderComponentPositionalPtr pRenderComponentPositional,
			RenderComponentEntityPtr pRenderComponentEntity);
		RenderComponentFractalVolumePtr createRenderComponentFractalVolume(GameObjectPtr gameObject,
			TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeParameters,
			RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentViewportPtr createRenderComponentViewport(GameObjectPtr gameObject,
			TRenderComponentViewportParameters tRenderComponentViewportParameters); 
		RenderComponentDecalPtr createRenderComponentDecal(GameObjectPtr
			gameObject, TRenderComponentDecalParameters decalParams,
			Ogre::SceneManager* sceneManager);
		RenderComponentWaterPtr createRenderComponentWater(std::string name,GameObjectPtr gameObject,
			TRenderComponentWaterParameters tRenderComponentWaterParameters);
		RenderComponentPlanePtr createRenderComponentPlane(std::string name,GameObjectPtr gameObject,
			TRenderComponentPlaneParameters tRenderComponentPlaneParameters);

		//create and return a physics component
		PhysicsComponentCharacterPtr createPhysicsComponentCharacter(GameObjectPtr gameObject,
			TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentCharacterOnyPtr createPhysicsComponentCharacterOny(GameObjectPtr gameObject,
			TPhysicsComponentCharacterOnyParameters tPhysicsComponentCharacterOnyParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentComplexConvexPtr createPhysicsComponentComplexConvex(GameObjectPtr gameObject,
			TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentComplexTrianglePtr createPhysicsComponentComplexTriangle(GameObjectPtr gameObject,
			TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentSimpleCapsulePtr createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,
			TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentSimpleBoxPtr createPhysicsComponentSimpleBox(GameObjectPtr gameObject,
			TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentVolumeCapsulePtr createPhysicsComponentVolumeCapsule(GameObjectPtr gameObject,
			TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentVolumeBoxPtr createPhysicsComponentVolumeBox(GameObjectPtr gameObject,
			TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentVolumeConvexPtr createPhysicsComponentVolumeConvex(GameObjectPtr gameObject,
			TPhysicsComponentVolumeConvexParameters tPhysicsComponentVolumeConvexParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);
		PhysicsComponentPillowPtr createPhysicsComponentPillow(GameObjectPtr gameObject,
			TPhysicsComponentPillowParameters tPhysicsComponentPillowParameters,
			RenderComponentPositionalPtr tRenderComponentPositional,QueryFlags flags=QUERYFLAGS_NONE);

		//Logic components
		LogicComponentPtr createLogicComponent(GameObjectPtr gameObject, TLogicComponentParameters tLogicComponentParameters);
		LogicComponentOnyPtr createLogicComponentOny(GameObjectPtr gameObject, TLogicComponentOnyParameters logicComponentOnyParameters);
		LogicComponentEnemyPtr createLogicComponentEnemy(GameObjectPtr gameObject, TLogicComponentEnemyParameters logicComponentEnemyParameters);
		LogicComponentItemPtr createLogicComponentItem(GameObjectPtr gameObject, TLogicComponentItemParameters logicComponentItemParameters);
		LogicComponentBreakablePtr createLogicComponentBreakable(GameObjectPtr gameObject, TLogicComponentBreakableParameters logicComponentBreakableParameters);
		LogicComponentUsablePtr createLogicComponentUsable(GameObjectPtr gameObject, TLogicComponentUsableParameters logicComponentParameters);
		LogicComponentPropPtr createLogicComponentProp(GameObjectPtr gameObject, TLogicComponentPropParameters logicComponentParameters);
		LogicComponentTriggerPtr createLogicComponentTrigger(GameObjectPtr gameObject, TLogicComponentTriggerParameters logicComponentParameters);
		LogicComponentCameraTriggerPtr createLogicComponentCameraTrigger(GameObjectPtr gameObject, TLogicComponentCameraTriggerParameters logicComponentParameters);

		WeaponComponentPtr createWeaponComponent(GameObjectPtr gameObject, TWeaponComponentParameters weaponComponentParameters);
		AttackComponentPtr createAttackComponent(GameObjectPtr gameObject, TAttackComponentParameters attackComponentParameters);

		//trajectory component
		TrajectoryComponentPtr createTrajectoryComponent(GameObjectPtr gameObject,TTrajectoryComponentParameters ttrajectoryComponentParameters);
		
		AudioComponentPtr createAudioComponent(GameObjectPtr gameObject, const TAudioComponentMap& audioComponentSounds, AudioSubsystemPtr audioSubsystem);
	};
}

#endif