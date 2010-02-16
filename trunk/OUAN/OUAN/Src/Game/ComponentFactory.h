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
		/// the factory instance
		static ComponentFactory* mInstance;
		/// Default constructor
		ComponentFactory(){}
		~ComponentFactory(){delete mInstance;}
	public:
		///return instance of the factory
		///@return factory's instance
		static ComponentFactory* getInstance();

		///create and return an ogre component
		/// @param params the params to initialise the component
		/// @param gameObject the component's parent object
		/// @param renderSubsystem  pointer to the rendering subsystem,
		///							which will create everything it needs
		///							to represent the component
		/// @return pointer to the newly created Ogre component instance
		// [TODO: Uncomment this]
		//ComponentPtr createOgreComponent(TObjectParameters params,GameObjectPtr,RenderSubsystemPtr);
		
		
		
		//create and return a physics component
		//ComponentPtr createPhysicsComponent(TObjectParameters,GameObjectPtr,PhysicsSubsystemPtr);
		//[TODO: Others]
	};
}

#endif