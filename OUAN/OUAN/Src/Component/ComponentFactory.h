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
		
		/// the factory instance
		static ComponentFactory* mInstance;
		/// Default constructor
		ComponentFactory(){}
		~ComponentFactory(){delete mInstance;}
	public:
		///return instance of the factory
		///@return factory's instance
		static ComponentFactory* getInstance();

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
			TRenderComponentEntityParameters tRenderComponentEntityParameters,QueryFlags flags=QUERYFLAGS_NONE);
		RenderComponentLightPtr createRenderComponentLight(GameObjectPtr gameObject,
			TRenderComponentLightParameters tRenderComponentLightParameters);
		RenderComponentParticleSystemPtr createRenderComponentParticleSystem(GameObjectPtr gameObject,
			TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters);
		RenderComponentScenePtr createRenderComponentScene(GameObjectPtr gameObject,
			TRenderComponentSceneParameters tRenderComponentSceneParameters);
		RenderComponentPositionalPtr createRenderComponentPositional(GameObjectPtr gameObject,
			TRenderComponentPositionalParameters tRenderComponentPositionalParameters);
		RenderComponentViewportPtr createRenderComponentViewport(GameObjectPtr gameObject,
			TRenderComponentViewportParameters tRenderComponentViewportParameters); 
		
		//create and return a physics component
		PhysicsComponentCharacterPtr createPhysicsComponentCharacter(GameObjectPtr gameObject,
			TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentComplexConvexPtr createPhysicsComponentComplexConvex(GameObjectPtr gameObject,
			TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentComplexTrianglePtr createPhysicsComponentComplexTriangle(GameObjectPtr gameObject,
			TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentSimpleCapsulePtr createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,
			TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentSimpleBoxPtr createPhysicsComponentSimpleBox(GameObjectPtr gameObject,
			TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentVolumeCapsulePtr createPhysicsComponentVolumeCapsule(GameObjectPtr gameObject,
			TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentVolumeBoxPtr createPhysicsComponentVolumeBox(GameObjectPtr gameObject,
			TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters,
			RenderComponentPositionalPtr tRenderComponentPositional);

		//Logic components
		LogicComponentPtr createLogicComponent(GameObjectPtr gameObject, TLogicComponentParameters logicComponentParameters);


		//[TODO: Others]
	};
}

#endif