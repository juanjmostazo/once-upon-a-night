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

		void initialise(ApplicationPtr app);

		//create and return a render component
		/// @param gameObject the component's parent object and render component parameters
		/// @return pointer to the newly created Ogre component instance
		RenderComponentPtr ComponentFactory::createRenderComponent(GameObjectPtr gameObject,TRenderComponentParameters tRenderComponentParameters);
		RenderComponentBillboardSetPtr ComponentFactory::createRenderComponentBillboardSet(GameObjectPtr gameObject,TRenderComponentBillboardSetParameters tRenderComponentBillboardSetParameters);
		RenderComponentCameraPtr ComponentFactory::createRenderComponentCamera(GameObjectPtr gameObject,TRenderComponentCameraParameters tRenderComponentCameraParameters);
		RenderComponentEntityPtr ComponentFactory::createRenderComponentEntity(GameObjectPtr gameObject,TRenderComponentEntityParameters tRenderComponentEntityParameters);
		RenderComponentLightPtr ComponentFactory::createRenderComponentLight(GameObjectPtr gameObject,TRenderComponentLightParameters tRenderComponentLightParameters);
		RenderComponentParticleSystemPtr ComponentFactory::createRenderComponentParticleSystem(GameObjectPtr gameObject,TRenderComponentParticleSystemParameters tRenderComponentParticleSystemParameters);
		RenderComponentScenePtr ComponentFactory::createRenderComponentScene(GameObjectPtr gameObject,TRenderComponentSceneParameters tRenderComponentSceneParameters);
		RenderComponentSceneNodePtr ComponentFactory::createRenderComponentSceneNode(GameObjectPtr gameObject,TRenderComponentSceneNodeParameters tRenderComponentSceneNodeParameters);
		RenderComponentViewportPtr ComponentFactory::createRenderComponentViewport(GameObjectPtr gameObject,TRenderComponentViewportParameters tRenderComponentViewportParameters); 
		
		//create and return a physics component
		PhysicsComponentPtr ComponentFactory::createPhysicsComponent(GameObjectPtr gameObject,TPhysicsComponentParameters tPhysicsComponentParameters);
		PhysicsComponentCharacterPtr ComponentFactory::createPhysicsComponentCharacter(GameObjectPtr gameObject,TPhysicsComponentCharacterParameters tPhysicsComponentCharacterParameters);
		PhysicsComponentComplexPtr ComponentFactory::createPhysicsComponentComplex(GameObjectPtr gameObject,TPhysicsComponentComplexParameters tPhysicsComponentComplexParameters);
		PhysicsComponentComplexMovablePtr ComponentFactory::createPhysicsComponentComplexMovable(GameObjectPtr gameObject,TPhysicsComponentComplexMovableParameters tPhysicsComponentComplexMovableParameters);
		PhysicsComponentComplexNonMovablePtr ComponentFactory::createPhysicsComponentComplexNonMovable(GameObjectPtr gameObject,TPhysicsComponentComplexNonMovableParameters tPhysicsComponentComplexNonMovableParameters);
		PhysicsComponentSimplePtr ComponentFactory::createPhysicsComponentSimple(GameObjectPtr gameObject,TPhysicsComponentSimpleParameters tPhysicsComponentSimpleParameters);
		PhysicsComponentSimpleCapsulePtr ComponentFactory::createPhysicsComponentSimpleCapsule(GameObjectPtr gameObject,TPhysicsComponentSimpleCapsuleParameters tPhysicsComponentSimpleCapsuleParameters);
		PhysicsComponentSimpleCubePtr ComponentFactory::createPhysicsComponentSimpleCube(GameObjectPtr gameObject,TPhysicsComponentSimpleCubeParameters tPhysicsComponentSimpleCubeParameters);

		//[TODO: Others]
	};
}

#endif