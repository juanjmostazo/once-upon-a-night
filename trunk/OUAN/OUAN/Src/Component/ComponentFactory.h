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
		RenderComponentPtr ComponentFactory::createRenderComponent(GameObjectPtr gameObject,TRenderComponentParameters tRenderComponentParameters);
		RenderComponentBillboardSetPtr ComponentFactory::createRenderComponentBillboardSet(GameObjectPtr gameObject,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters);
		RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(std::string name,GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters);
		RenderComponentLightPtr ComponentFactory::createRenderComponentLight(GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters);
		RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters);
		RenderComponentScenePtr ComponentFactory::createRenderComponentScene(GameObjectPtr gameObject,TRenderComponentSceneParameters tRenderComponentSceneParameters);
		RenderComponentPositionalPtr ComponentFactory::createRenderComponentPositional(GameObjectPtr gameObject,TRenderComponentPositionalParameters tRenderComponentPositionalParameters);
		RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters); 
		
		//create and return a physics component
		PhysicsComponentCharacterPtr ComponentFactory::createPhysicsComponentCharacter(GameObjectPtr gameObject,TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentComplexConvexPtr ComponentFactory::createPhysicsComponentComplexConvex(GameObjectPtr gameObject,TPhysicsComponentComplexConvexParameters tPhysicsComponentComplexConvexParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentComplexTrianglePtr ComponentFactory::createPhysicsComponentComplexTriangle(GameObjectPtr gameObject,TPhysicsComponentComplexTriangleParameters tPhysicsComponentComplexTriangleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentSimpleCapsulePtr ComponentFactory::createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentSimpleBoxPtr ComponentFactory::createPhysicsComponentSimpleBox(GameObjectPtr gameObject,TPhysicsComponentSimpleBoxParameters tPhysicsComponentSimpleBoxParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentVolumeCapsulePtr ComponentFactory::createPhysicsComponentVolumeCapsule(GameObjectPtr gameObject,TPhysicsComponentVolumeCapsuleParameters tPhysicsComponentVolumeCapsuleParameters,RenderComponentPositionalPtr tRenderComponentPositional);
		PhysicsComponentVolumeBoxPtr ComponentFactory::createPhysicsComponentVolumeBox(GameObjectPtr gameObject,TPhysicsComponentVolumeBoxParameters tPhysicsComponentVolumeBoxParameters,RenderComponentPositionalPtr tRenderComponentPositional);

		//Logic components
		LogicComponentWorldExistancePtr ComponentFactory::createLogicComponentWorldExistance(TLogicComponentWorldExistanceParameters tLogicComponentWorldExistanceParameters);

		//[TODO: Others]
	};
}

#endif