#ifndef COMPONENTFACTORYH_H
#define COMPONENTFACTORYH_H

#include "../OUAN.h"

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
		RenderComponentBillboardSetPtr createRenderComponentBillboardSet(GameObjectPtr gameObject,
			TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters);
		RenderComponentCameraPtr createRenderComponentCamera(GameObjectPtr gameObject,
			TRenderComponentCameraParameters tRenderComponentCameraParameters);
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
		RenderComponentFractalVolumePtr createRenderComponentFractalVolume(GameObjectPtr gameObject,
			TRenderComponentFractalVolumeParameters tRenderComponentFractalVolumeParameters,
			RenderComponentPositionalPtr pRenderComponentPositional);
		RenderComponentViewportPtr createRenderComponentViewport(GameObjectPtr gameObject,
			TRenderComponentViewportParameters tRenderComponentViewportParameters); 
		RenderComponentDecalPtr createRenderComponentDecal(GameObjectPtr gameObject,
			TRenderComponentDecalParameters tRenderComponentDecalParameters);

		RenderComponentWaterPtr createRenderComponentWater(std::string name,GameObjectPtr gameObject,
			TRenderComponentWaterParameters tRenderComponentWaterParameters);

		//create and return a physics component
		PhysicsComponentCharacterPtr createPhysicsComponentCharacter(GameObjectPtr gameObject,
			TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,
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

		//Logic components
		LogicComponentPtr createLogicComponent(GameObjectPtr gameObject, TLogicComponentParameters tLogicComponentParameters);
		LogicComponentOnyPtr createLogicComponentOny(GameObjectPtr gameObject, TLogicComponentOnyParameters logicComponentOnyParameters);
		LogicComponentEnemyPtr createLogicComponentEnemy(GameObjectPtr gameObject, TLogicComponentEnemyParameters logicComponentEnemyParameters);
		LogicComponentItemPtr createLogicComponentItem(GameObjectPtr gameObject, TLogicComponentItemParameters logicComponentItemParameters);
		LogicComponentUsablePtr createLogicComponentUsable(GameObjectPtr gameObject, TLogicComponentUsableParameters logicComponentParameters);
		LogicComponentTriggerPtr createLogicComponentTrigger(GameObjectPtr gameObject, TLogicComponentTriggerParameters logicComponentParameters);

		WeaponComponentPtr createWeaponComponent(GameObjectPtr gameObject, TWeaponComponentParameters weaponComponentParameters);
		AttackComponentPtr createAttackComponent(GameObjectPtr gameObject, TAttackComponentParameters attackComponentParameters);

		//trajectory component
		TrajectoryComponentPtr createTrajectoryComponent(GameObjectPtr gameObject,bool TwoDimensions);

		//[TODO: Others]
	};
}

#endif